//	Account.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

//---------------------------------------------------------------------------

#include "DSC_Types.hpp"
#include "Lock.hpp"
#include "TProperty.hpp"
#include <string>

using namespace std;

//---------------------------------------------------------------------------

#ifndef _ITV2_ACCOUNT_H_
#define _ITV2_ACCOUNT_H_

//---------------------------------------------------------------------------

class CAccountKey
{
//private members
private:
	CCriticalSection	m_clsPropLock;
	string				m_strIdentifier;		//identifier info

//constructor
public:
	CAccountKey(VOID);
	CAccountKey(string const& strIdentifier);
	CAccountKey(CAccountKey const& refAccountKey);

//destructor
public:
	virtual ~CAccountKey(VOID);

//properties
public:
	TProperty<CAccountKey, string> Identifier;

//getters and setters
private:
	string get_Identifier(VOID) const;
	VOID set_Identifier(string const& value);

//operators
public:
	CAccountKey& operator =(CAccountKey const& refAccountKey);

	BOOL operator ==(CAccountKey const& refAccountKey) const;
	BOOL operator !=(CAccountKey const& refAccountKey) const;
	BOOL operator >(CAccountKey const& refAccountKey) const;
	BOOL operator <(CAccountKey const& refAccountKey) const;
};

//---------------------------------------------------------------------------

class CAccount
{
//constants
private:

//private members
private:
	CCriticalSection	m_clsPropLock;

	string				m_strIdentifier;		//identifier
	string				m_strIntegrationID;		//Integration Identification Number
	string				m_strAccessCode;		//Integration Access Code
	string				m_strUdpChannelFunction;
	string				m_strTcpChannelFunction;
	UINT32				m_numKeyChangeTime;

//constructor
public:
	CAccount(VOID);
	CAccount(CAccount const& refAccount);

//destructor
public:
	virtual ~CAccount(VOID);

//properties
public:
	TProperty<CAccount, string> Identifier;
	TProperty<CAccount, string> IntegrationID;
	TProperty<CAccount, string> AccessCode;
	TProperty<CAccount, string> UdpChannelFunction;
	TProperty<CAccount, string> TcpChannelFunction;
	TProperty<CAccount, UINT32> KeyChangeTime;

//getters and setters
private:
	string get_Identifier(VOID) const;
	VOID set_Identifier(string const& value);

	string get_IntegrationID(VOID) const;
	VOID set_IntegrationID(string const& value);

	string get_AccessCode(VOID) const;
	VOID set_AccessCode(string const& value);

	string get_UdpChannelFunction(VOID) const;
	VOID set_UdpChannelFunction(string const& value);

	string get_TcpChannelFunction(VOID) const;
	VOID set_TcpChannelFunction(string const& value);

	UINT32 get_KeyChangeTime(VOID) const;
	VOID set_KeyChangeTime(UINT32 const& value);

//operators
public:
	CAccount& operator =(CAccount const& refAccount);
};

//---------------------------------------------------------------------------
#endif	//_ITV2_ACCOUNT_H_
