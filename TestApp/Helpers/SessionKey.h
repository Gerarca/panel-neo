//	SessionKey.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

#ifndef _SESSION_KEY_H_
#define _SESSION_KEY_H_

//---------------------------------------------------------------------------

#include "AddressInfo.h"
#include "TComparer.hpp"

//---------------------------------------------------------------------------

namespace SessionTypes {
enum value {
	NONE = 0,
	TCP,
	UDP
}; }
typedef DSC_ENUM_T SessionType;

//---------------------------------------------------------------------------

class CSessionKey 
{
//private members
private:
	SessionType    	m_flgSessionType;
	CAddressInfo	m_clsPeerAddress;

//constructor and destructor
public:
	CSessionKey(VOID);
	CSessionKey(SessionType flgSessionType, CAddressInfo const& clsPeerAddress);
	CSessionKey(CSessionKey const& refSessionKey);
	virtual ~CSessionKey(VOID);

//public mathods
public:
	VOID Clear(VOID);
	SessionType GetSessionType(VOID);

//operators
public:

	CSessionKey& operator =(CSessionKey const& value);

	BOOL operator ==(CSessionKey const& value) const;
	BOOL operator !=(CSessionKey const& value) const;
	BOOL operator >(CSessionKey const& value) const;
	BOOL operator <(CSessionKey const& value) const;
};

//---------------------------------------------------------------------------

class CSessionKeyComparer : public TComparer<CSessionKey>
{
//private members
private:
	CAddressInfoComparer	m_clsAddressInfoComparer;

//constructor & destructor
public:
	CSessionKeyComparer(VOID);
	virtual ~CSessionKeyComparer(VOID);

//public methods
public:
	virtual int Compare(CSessionKey const& refA, CSessionKey const& refB) const;
	virtual TComparer<CSessionKey>* Clone(VOID);
};

//---------------------------------------------------------------------------
#endif	//_SESSION_KEY_H_