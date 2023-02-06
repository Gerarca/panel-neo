//---------------------------------------------------------------------------
//
//	TextString.cpp
//
//	The DSC_ITextString implmentations.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "TextString.hpp"
#include "Tokenizer.hpp"
#include "Debug.hpp"

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

	CTextString::CTextString(VOID)
	{
		//DEBUG_PRINTF("[CTextString::CTextString] %p\n", this);
	}

//---------------------------------------------------------------------------

	CTextString::~CTextString(VOID)
	{
		//DEBUG_PRINTF("[CTextString::~CTextString] %p\n", this);
	}

//---------------------------------------------------------------------------

	IRESULT ICALL CTextString::Query(IN char const* pszInterface, OUT VOID** ptrInterface)
	{
		//validate arguments
		if ((NULL == pszInterface) || (NULL == ptrInterface))
		{
			//validate arguments
			return IRESULT_E_BAD_ARGUMENTS;
		}

		//check for DSC_ITextString
		CLock lock = CComponent::GetSyncLock();
		if (0 == strcmp(pszInterface, NAME_DSC_ITextString))
		{
			//increase ref count and return the pointer to this component
			DSC_ITextString* ptr = static_cast<DSC_ITextString*>(this);
			ptr->Acquire(NULL);

			//return the result
			*ptrInterface = ptr;
			return IRESULT_S_OK;
		}

		//query the base
		return CComponent::Query(pszInterface, ptrInterface);
	}

//---------------------------------------------------------------------------

	IRESULT ICALL CTextString::Acquire(ICOUNT* ptrCount)
	{
		return CComponent::Acquire(ptrCount);
	}

//---------------------------------------------------------------------------

	IRESULT ICALL CTextString::Release(ICOUNT* ptrCount)
	{
		return CComponent::Release(ptrCount);
	}

//---------------------------------------------------------------------------

	IRESULT ICALL CTextString::get_Length(OUT DSC_SIZE_T* ptrLength) const
	{
		if (NULL != ptrLength)
		{
			CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
			*ptrLength = static_cast<DSC_SIZE_T>(m_strTextString.length());
			return IRESULT_S_OK;
		}
		return IRESULT_E_BAD_ARGUMENTS;
	}

//---------------------------------------------------------------------------

	IRESULT ICALL CTextString::get_String(OUT char const** ptrString) const
	{
		if (NULL != ptrString)
		{
			CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
			*ptrString = m_strTextString.c_str();
			return IRESULT_S_OK;
		}
		return IRESULT_E_BAD_ARGUMENTS;
	}

//---------------------------------------------------------------------------

	IRESULT ICALL CTextString::set_String(IN char const* pszString)
	{
		//enter critical section
		CLock lock = m_clsPropLock;

		//validate the arguments
		if (NULL == pszString)
		{
			//clear the string
			m_strTextString.clear();
		}
		else
		{
			//copy the string
			m_strTextString = pszString;
		}
		return IRESULT_S_OK;
	}

//---------------------------------------------------------------------------

	IRESULT ICALL CTextString::CreateTextString(
		IN char const* pszText, OUT DSC_ITextString** ptrText)
	{
		//clear the OUT arg
		if (NULL != ptrText)
		{
			//release the old interface?
			if (NULL != *ptrText)
			{
				//release the old interface
				(*ptrText)->Release(NULL);
				*ptrText = NULL;
			}
		}

		if ((NULL != pszText) && (NULL != ptrText))
		{
			//create the result string
			TComPtr<DSC_ITextString> text(new CTextString, TRUE);
			IRESULT temp = text->set_String(pszText);
			if (IS_FAILURE(temp))
			{
				//return the error
				return temp;
			}

			//return the result
			*ptrText = text.Fetch();
			return IRESULT_S_OK;
		}
		return IRESULT_E_BAD_ARGUMENTS;
	}

//---------------------------------------------------------------------------

#if defined(MS_VS_COMPILER)
#pragma warning(pop)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------
