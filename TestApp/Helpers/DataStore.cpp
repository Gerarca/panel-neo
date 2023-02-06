//	DataStore.cpp
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "DataStore.h"
#include "ParamParser.hpp"
#include "DSC_Parameters.hpp"
#include "TextString.hpp"
#include "TComPtr.hpp"
#include "DSC_Config.hpp"
#include "Debug.hpp"
#include <cstdio>
#include "Application.h"

using namespace std;
using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

#if defined(WINDOWS)
#elif defined(LINUX)
#define _snprintf snprintf
#else
#error "Undefined platform information!"
#endif

//---------------------------------------------------------------------------

#define ITOA_BUFFER_SIZE	20

//---------------------------------------------------------------------------

//disable some well-understood warnings
#if defined(MS_VS_COMPILER)
#pragma warning(push)
#pragma warning(disable: 4996)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------

CDataStore::CDataStore(VOID)
{
	DEBUG_PRINTF("[CDataStore::CDataStore] %p\n", this);
}

//---------------------------------------------------------------------------

CDataStore::~CDataStore(VOID)
{
	DEBUG_PRINTF("[CDataStore::~CDataStore] %p\n", this);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

IRESULT ICALL CDataStore::Query(IN char const* pszInterface, OUT VOID** ptrInterface)
{
	//validate arguments
	if ((NULL == pszInterface) || (NULL == ptrInterface))
	{
		//validate arguments
		return IRESULT_E_BAD_ARGUMENTS;
	}

	//check for DSC_IDataStore
	CLock lock = CComponent::GetSyncLock();
	if (0 == strcmp(pszInterface, NAME_DSC_IDataStore))
	{
		//increase ref count and return the pointer to this component
		DSC_IDataStore* ptr = static_cast<DSC_IDataStore*>(this);
		ptr->Acquire(NULL);

		//return the result
		*ptrInterface = ptr;
		return IRESULT_S_OK;
	}

	//query the base
	return CComponent::Query(pszInterface, ptrInterface);
}

//---------------------------------------------------------------------------

IRESULT ICALL CDataStore::Acquire(OUT ICOUNT* ptrCount)
{
	return CComponent::Acquire(ptrCount);
}

//---------------------------------------------------------------------------

IRESULT ICALL CDataStore::Release(OUT ICOUNT* ptrCount)
{
	return CComponent::Release(ptrCount);
}

//---------------------------------------------------------------------------

IRESULT ICALL CDataStore::SelectData(IN char const* pszParams, OUT DSC_ITextString** ptrResult) const
{
	//clear the OUT arg
	if (NULL != ptrResult)
	{
		//release the old interface?
		if (NULL != *ptrResult)
		{
			//release the old interface
			(*ptrResult)->Release(NULL);
			*ptrResult = NULL;
		}
	}

	//validate args
	if ((NULL == pszParams) || (NULL == ptrResult))
	{
		//bad argument
		return IRESULT_E_BAD_ARGUMENTS;
	}

	//parse the params string
	CParamParser parser = string(pszParams);
	if ((FALSE != parser.Contains(QUERY_CATEGORY)) &&
		(FALSE != parser.Contains(QUERY_SELECTOR)) &&
		(FALSE != parser.Contains(ITV2_PARAM_CONNECTION)) &&
		(FALSE != parser.Contains(ITV2_PARAM_IDENTIFIER)))
	{
		//check the query category and selector
		string category = parser[QUERY_CATEGORY].ValueText;
		string selector = parser[QUERY_SELECTOR].ValueText;
		if ((0 == category.compare(QUERY_CATEGORY_ITV2)) && 
			(0 == selector.compare(QUERY_SELECTOR_ACCOUNT_INFO)))
		{
			//prepare the indexing key and find the account info
			CAccountKey key(parser[ITV2_PARAM_IDENTIFIER].ValueText);

			//try to find the account info
			CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
			int index = m_lstAccounts.IndexOf(key);
			if (0 <= index)
			{
				//get the account info
				CAccount account = m_lstAccounts[index];

				//prepare the response
				parser.SetValue(ITV2_PARAM_INTEGRATION_ID, account.IntegrationID, TRUE);
				parser.SetValue(ITV2_PARAM_ACCESS_CODE, account.AccessCode, TRUE);

				string connection = parser[ITV2_PARAM_CONNECTION].ValueText;
				if (0 == connection.compare(APP_UDP_CONNECTION))
				{
					parser.SetValue(ITV2_PARAM_CHANNEL_FUNCTION, account.UdpChannelFunction, TRUE);
				}
				else if (0 == connection.compare(APP_TCP_CONNECTION))
				{
					parser.SetValue(ITV2_PARAM_CHANNEL_FUNCTION, account.TcpChannelFunction, TRUE);
				}
				else
				{
					parser.SetValue(ITV2_PARAM_CHANNEL_FUNCTION, ITV2_PARAM_FUNCTION_NO_FUNCTION, TRUE);
				}

				char value[ITOA_BUFFER_SIZE + 1];
				memset(value, 0, ITOA_BUFFER_SIZE + 1);
				UINT32 time = account.KeyChangeTime;
				_snprintf(value, ITOA_BUFFER_SIZE, "%ld", time);
				parser.SetValue(ITV2_PARAM_KEY_CHANGE_TIME, value, TRUE);

				//build the result string
				string result = parser.Build();
				TComPtr<DSC_ITextString> text(new CTextString, TRUE);
				IRESULT temp = text->set_String(result.c_str());
				if (IS_FAILURE(temp))
				{
					//return the error
					return temp;
				}

				//return the result
				*ptrResult = text.Fetch();
				return IRESULT_S_OK;
			}
		}
	}
	return IRESULT_E_FAILURE;
}

//---------------------------------------------------------------------------

IRESULT ICALL CDataStore::InsertData(
	IN char const* pszParams, OUT DSC_SIZE_T* ptrResult)
{
	//clear the OUT arg
	if (NULL != ptrResult) *ptrResult = 0;

	//validate args
	if ((NULL == pszParams) || (NULL == ptrResult))
	{
		//bad argument
		return IRESULT_E_BAD_ARGUMENTS;
	}

	//failure
	return IRESULT_E_NOT_IMPLEMENTED;
}

//---------------------------------------------------------------------------

IRESULT ICALL CDataStore::UpdateData(
	IN char const* pszParams, OUT DSC_SIZE_T* ptrResult)
{
	//clear the OUT arg
	if (NULL != ptrResult) *ptrResult = 0;

	//validate args
	if ((NULL == pszParams) || (NULL == ptrResult))
	{
		//bad argument
		return IRESULT_E_BAD_ARGUMENTS;
	}

	//parse the params string
	*ptrResult = 0;
	CParamParser parser = string(pszParams);
	if ((FALSE != parser.Contains(QUERY_CATEGORY)) &&
		(FALSE != parser.Contains(ITV2_PARAM_CONNECTION)) &&
		(FALSE != parser.Contains(ITV2_PARAM_IDENTIFIER)))
	{
		//check the query category and selector
		string category = parser[QUERY_CATEGORY].ValueText;
		if (0 == category.compare(QUERY_CATEGORY_ITV2))
		{
			//prepare the indexing key and find the account info
			CAccountKey key(parser[ITV2_PARAM_IDENTIFIER].ValueText);

			//try to find the account info
			CLock lock = m_clsPropLock;
			int index = m_lstAccounts.IndexOf(key);
			if (0 <= index)
			{
				//get the account info
				CAccount account = m_lstAccounts[index];

				//update access code?
				if (FALSE != parser.Contains(ITV2_PARAM_ACCESS_CODE))
				{
					//update access code
					account.AccessCode = parser[ITV2_PARAM_ACCESS_CODE].ValueText;
					*ptrResult = *ptrResult + 1;
				}

				//data store has been updated
				return IRESULT_S_OK;
			}
		}
	}
	return IRESULT_E_FAILURE;
}

//---------------------------------------------------------------------------

IRESULT ICALL CDataStore::DeleteData(
	IN char const* pszParams, OUT DSC_SIZE_T* ptrResult)
{
	//clear the OUT arg
	if (NULL != ptrResult) *ptrResult = 0;

	//validate args
	if ((NULL == pszParams) || (NULL == ptrResult))
	{
		//bad argument
		return IRESULT_E_BAD_ARGUMENTS;
	}

	//failure
	return IRESULT_E_NOT_IMPLEMENTED;
}

//---------------------------------------------------------------------------

BOOL CDataStore::AddAccount(string const& strIdentifier, 
	string const& strIntegrationID, string const& strAccessCode, 
	string const& strUdpChannelFunction, string const& strTcpChannelFunction, 
	UINT32 numKeyChangeTime)
{
	CAccountKey key(strIdentifier);

	CAccount account;
	account.Identifier = strIdentifier;
	account.IntegrationID = strIntegrationID;
	account.AccessCode = strAccessCode;
	account.UdpChannelFunction = strUdpChannelFunction;
	account.TcpChannelFunction = strTcpChannelFunction;
	account.KeyChangeTime = numKeyChangeTime;

	CLock lock = m_clsPropLock;
	return (NULL != m_lstAccounts.Add(key, account, TRUE))? TRUE : FALSE;
}

//---------------------------------------------------------------------------

VOID CDataStore::RemoveAccount(string const& strIdentifier)
{
	CAccountKey key(strIdentifier);

	CLock lock = m_clsPropLock;
	m_lstAccounts.Remove(key);
}

//---------------------------------------------------------------------------

#if defined(MS_VS_COMPILER)
#pragma warning(pop)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------
