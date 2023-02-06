//	DataStore.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

//---------------------------------------------------------------------------

#include "DSC_IDataStore.hpp"
#include "Component.hpp"
#include "Lock.hpp"
#include "TDictionary.hpp"
#include "Account.h"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

//---------------------------------------------------------------------------

#ifndef _DATA_STORE_H_
#define _DATA_STORE_H_

//---------------------------------------------------------------------------

//disable some well-understood warnings
#if defined(MS_VS_COMPILER)
#pragma warning(push)
#pragma warning(disable: 4250)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------

class CDataStore : public CComponent, public DSC_IDataStore
{
//private members
private:
	CCriticalSection					m_clsPropLock;
	TDictionary<CAccountKey, CAccount>	m_lstAccounts;

//constructor and destructor
public:
	CDataStore(VOID);
	virtual ~CDataStore(VOID);

//properties
public:

//public methods
public:
	//The Query method returns a pointer to the interface specified by
	//the name. The method may pass back NULL if the specified interface
	//name is unknown.
	virtual IRESULT ICALL Query(IN char const* pszInterface, OUT VOID** ptrInterface);
	virtual IRESULT ICALL Acquire(OUT ICOUNT* ptrCount);
	virtual IRESULT ICALL Release(OUT ICOUNT* ptrCount);

	virtual IRESULT ICALL SelectData(IN char const* pszParams, OUT DSC_ITextString** ptrResult) const;
	virtual IRESULT ICALL InsertData(IN char const* pszParams, OUT DSC_SIZE_T* ptrResult);
	virtual IRESULT ICALL UpdateData(IN char const* pszParams, OUT DSC_SIZE_T* ptrResult);
	virtual IRESULT ICALL DeleteData(IN char const* pszParams, OUT DSC_SIZE_T* ptrResult);

	BOOL AddAccount(
		string const& strIdentifier, 
		string const& strIntegrationID, string const& strAccessCode, 
		string const& strUdpChannelFunction, string const& strTcpChannelFunction,
		UINT32 numKeyChangeTime);
	VOID RemoveAccount(string const& strIdentifier);

//private methods
private:
};

//---------------------------------------------------------------------------

#if defined(MS_VS_COMPILER)
#pragma warning(pop)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------
#endif	//_DATA_STORE_H_
