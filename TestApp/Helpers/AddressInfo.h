//	AddressInfo.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

#ifndef _ADDRESS_INFO_H_
#define _ADDRESS_INFO_H_

//---------------------------------------------------------------------------

#include "DSC_Types.hpp"
#include "Socket.h"

//---------------------------------------------------------------------------

#define ADDRESS_BUFFER_SIZE		50

//---------------------------------------------------------------------------

class CAddressInfo 
{
//public members
public:
	AddressFamily	Family;
	TCHAR			Address[ADDRESS_BUFFER_SIZE + 1];
	int				Port;

//constructor and destructor
public:
	CAddressInfo(VOID);
	CAddressInfo(CAddressInfo const& refAddressInfo);
	virtual ~CAddressInfo(VOID);

//public methods
public:
	VOID Clear(VOID);

//operators
public:
	CAddressInfo& operator =(CAddressInfo const& value);

	BOOL operator ==(CAddressInfo const& value) const;
	BOOL operator !=(CAddressInfo const& value) const;
	BOOL operator >(CAddressInfo const& value) const;
	BOOL operator <(CAddressInfo const& value) const;
};

//---------------------------------------------------------------------------

class CAddressInfoComparer
{
//constructor & destructor
public:
	CAddressInfoComparer(VOID);
	virtual ~CAddressInfoComparer(VOID);

//public methods
public:
	virtual int Compare(CAddressInfo const& refA, CAddressInfo const& refB);
};

//---------------------------------------------------------------------------
#endif	//_ADDRESS_INFO_H_