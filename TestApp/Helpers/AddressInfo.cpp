//	AddressInfo.cpp
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "AddressInfo.h"

#if defined(WINDOWS)
#include <tchar.h>
#elif defined(LINUX)
#define _tcsncpy(a,b,c) strncpy(a,b,c)
#define _tcsicmp(a,b)   strcasecmp(a,b)
#else
#error "Undefined platform information!"
#endif

using namespace std;

//---------------------------------------------------------------------------

CAddressInfo::CAddressInfo(VOID)
{
	Clear();
}

//---------------------------------------------------------------------------

CAddressInfo::CAddressInfo(CAddressInfo const& refAddressInfo)
{
	Clear();
	operator =(refAddressInfo);
}

//---------------------------------------------------------------------------

CAddressInfo::~CAddressInfo(VOID)
{
}

//---------------------------------------------------------------------------

VOID CAddressInfo::Clear(VOID)
{
	Family = AddressFamilies::ADDR_UNSPEC;
	memset(Address, 0, sizeof(Address));
	Port = 0;
}

//---------------------------------------------------------------------------

CAddressInfo& CAddressInfo::operator =(CAddressInfo const& value)
{
	Family = value.Family;
	_tcsncpy(Address, value.Address, ADDRESS_BUFFER_SIZE);
	Port = value.Port;
	return *this;
}

//---------------------------------------------------------------------------

BOOL CAddressInfo::operator ==(CAddressInfo const& value) const
{
	//compare all fields
	if ((Family == value.Family) && (Port == value.Port) &&
		(IS_EQUAL == _tcsicmp(Address, value.Address)))
	{
		return TRUE;
	}

	//not
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CAddressInfo::operator !=(CAddressInfo const& value) const
{
	return (FALSE == operator ==(value))? TRUE : FALSE;
}

//---------------------------------------------------------------------------

BOOL CAddressInfo::operator >(CAddressInfo const& value) const
{
	//compare the address family
	if (Family > value.Family)
	{
		return TRUE;
	}

	//compare address string
	if (0 < _tcsicmp(Address, value.Address))
	{
		return TRUE;
	}

	//compare port number
	if (Port > value.Port)
	{
		return TRUE;
	}

	//not
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CAddressInfo::operator <(CAddressInfo const& value) const
{
	//compare the address family
	if (Family < value.Family)
	{
		return TRUE;
	}

	//compare address string
	if (0 > _tcsicmp(Address, value.Address))
	{
		return TRUE;
	}

	//compare port number
	if (Port < value.Port)
	{
		return TRUE;
	}

	//not
	return FALSE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

CAddressInfoComparer::CAddressInfoComparer(VOID)
{
}

//---------------------------------------------------------------------------

CAddressInfoComparer::~CAddressInfoComparer(VOID)
{
}

//---------------------------------------------------------------------------

int CAddressInfoComparer::Compare(CAddressInfo const& refA, CAddressInfo const& refB)
{
	//compare
	if (refA > refB)
	{
		return IS_GREATER;
	}
	else if (refA < refB)
	{
		return IS_LESSER;
	}

	//address infos are equal
	return IS_EQUAL;
}

//---------------------------------------------------------------------------
