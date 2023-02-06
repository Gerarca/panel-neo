//	SessionKey.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "SessionKey.h"

//---------------------------------------------------------------------------

CSessionKey::CSessionKey(VOID)
{
	Clear();
}

//---------------------------------------------------------------------------

CSessionKey::CSessionKey(SessionType flgSessionType, CAddressInfo const& clsPeerAddress)
{
	Clear();
	m_flgSessionType = flgSessionType;
	m_clsPeerAddress = clsPeerAddress;
}

//---------------------------------------------------------------------------

CSessionKey::CSessionKey(CSessionKey const& refSessionKey)
{
	Clear();
	operator =(refSessionKey);
}

//---------------------------------------------------------------------------

CSessionKey::~CSessionKey(VOID)
{
}

//---------------------------------------------------------------------------

VOID CSessionKey::Clear(VOID)
{
	m_flgSessionType = SessionTypes::NONE;
	m_clsPeerAddress.Clear();
}

//---------------------------------------------------------------------------

SessionType CSessionKey::GetSessionType(VOID)
{
	return m_flgSessionType;
}

//---------------------------------------------------------------------------

CSessionKey& CSessionKey::operator =(CSessionKey const& value)
{
	m_flgSessionType = value.m_flgSessionType;
	m_clsPeerAddress = value.m_clsPeerAddress;
	return *this;
}

//---------------------------------------------------------------------------

BOOL CSessionKey::operator ==(CSessionKey const& value) const
{
	//compare all fields
	if ((m_flgSessionType == value.m_flgSessionType) &&
		(m_clsPeerAddress == value.m_clsPeerAddress))
	{
		return TRUE;
	}

	//not
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSessionKey::operator !=(CSessionKey const& value) const
{
	return (FALSE == operator ==(value))? TRUE : FALSE;
}

//---------------------------------------------------------------------------

BOOL CSessionKey::operator >(CSessionKey const& value) const
{
	//compare session type
	if (m_flgSessionType > value.m_flgSessionType)
	{
		return TRUE;
	}

	//compare remote address
	if (m_clsPeerAddress > value.m_clsPeerAddress)
	{
		return TRUE;
	}

	//not
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSessionKey::operator <(CSessionKey const& value) const
{
	//compare session type
	if (m_flgSessionType < value.m_flgSessionType)
	{
		return TRUE;
	}

	//compare remote address
	if (m_clsPeerAddress < value.m_clsPeerAddress)
	{
		return TRUE;
	}

	//not
	return FALSE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

CSessionKeyComparer::CSessionKeyComparer(VOID)
{
}

//---------------------------------------------------------------------------

CSessionKeyComparer::~CSessionKeyComparer(VOID)
{
}

//---------------------------------------------------------------------------

int CSessionKeyComparer::Compare(CSessionKey const& refA, CSessionKey const& refB) const
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

	//the addresses are equal
	return IS_EQUAL;
}

//---------------------------------------------------------------------------

	TComparer<CSessionKey>* CSessionKeyComparer::Clone(VOID)
	{
		return new CSessionKeyComparer(*this);
	}

//---------------------------------------------------------------------------
