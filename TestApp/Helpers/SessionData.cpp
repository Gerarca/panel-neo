//	SessionData.cpp
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "SessionData.h"

//---------------------------------------------------------------------------

CSessionData::CSessionData(VOID) :	
	m_numSysTicks(0), m_numIdleTime(0), m_clsIdleTime(0),
	m_ptrTCPProxy(NULL), m_ptrUDPPoint(NULL)
{
	Clear();
}

//---------------------------------------------------------------------------

CSessionData::CSessionData(CSessionData const& refSessionData) : 
	m_numSysTicks(0), m_numIdleTime(0), m_clsIdleTime(0),
	m_ptrTCPProxy(NULL), m_ptrUDPPoint(NULL)
{
	Clear();
	operator =(refSessionData);
}

//---------------------------------------------------------------------------

CSessionData::~CSessionData(VOID)
{
}

//---------------------------------------------------------------------------

CAddressInfo CSessionData::get_PeerAddr(VOID) const
{
	CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
	return m_clsPeerAddr;
}

VOID CSessionData::set_PeerAddr(CAddressInfo const& value)
{
	CLock lock = m_clsPropLock;
	m_clsPeerAddr = value;
}

//---------------------------------------------------------------------------

CTCPProxy* CSessionData::get_TCPProxy(VOID) const
{
	CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
	return m_ptrTCPProxy;
}

CTCPProxy* CSessionData::set_TCPProxy(CTCPProxy* value)
{
	CLock lock = m_clsPropLock;
	CTCPProxy* old = m_ptrTCPProxy;
	m_ptrTCPProxy = value;
	return old;
}

//---------------------------------------------------------------------------

CUDPPoint* CSessionData::get_UDPPoint(VOID) const
{
	CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
	return m_ptrUDPPoint;
}

CUDPPoint* CSessionData::set_UDPPoint(CUDPPoint* value)
{
	CLock lock = m_clsPropLock;
	CUDPPoint* old = m_ptrUDPPoint;
	m_ptrUDPPoint = value;
	return old;
}

//---------------------------------------------------------------------------

TComPtr<DSC_IChannel> CSessionData::get_IChannel(VOID) const
{
	CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
	return m_clsIChannel;
}

VOID CSessionData::set_IChannel(TComPtr<DSC_IChannel> const& value)
{
	CLock lock = m_clsPropLock;
	m_clsIChannel = value;
}

//---------------------------------------------------------------------------

VOID CSessionData::Clear(VOID)
{
	CLock lock = m_clsPropLock;
	m_numSysTicks = 0;
	m_numIdleTime = 0;
	m_clsIdleTime = 0;
	m_clsPeerAddr.Clear();
	m_ptrTCPProxy = NULL;
	m_ptrUDPPoint = NULL;
	m_clsIChannel.Clear();
}

//---------------------------------------------------------------------------

VOID CSessionData::SetSysTicks(UINT32 numTicks)
{
	//set the timeout
	CLock lock = m_clsPropLock;
	m_numSysTicks = numTicks;
}

//---------------------------------------------------------------------------

BOOL CSessionData::TestSysTicks(VOID)
{
	CLock lock = m_clsPropLock;
	if (0 < m_numSysTicks)
	{
		//count the pulse
		if (0 < --m_numSysTicks)
		{
			//m_clsSysTicks is not 0 yet
			return FALSE;
		}
	}
	//m_clsSysTicks reached 0
	return TRUE;
}

//---------------------------------------------------------------------------

VOID CSessionData::SetIdleTime(UINT32 numSecs)
{
	//set the timeout
	CLock lock = m_clsPropLock;
	m_numIdleTime = numSecs;
	m_clsIdleTime = (0 < m_numIdleTime)? time(NULL) + m_numIdleTime : 0;
}

//---------------------------------------------------------------------------

BOOL CSessionData::TestIdleTime(VOID)
{
	CLock lock = m_clsPropLock;
	if (0 < m_numIdleTime)
	{
		//initialize first?
		if (0 == m_clsIdleTime)
		{
			//init the timeout
			m_clsIdleTime = (0 < m_numIdleTime)? time(NULL) + m_numIdleTime : 0;
		}
		else if (0 >= difftime(m_clsIdleTime, time(NULL)))
		{
			//reset the timeout
			m_clsIdleTime = (0 < m_numIdleTime)? time(NULL) + m_numIdleTime : 0;

			//timeout reached
			return TRUE;
		}
	}
	//no timeout
	return FALSE;
}

//---------------------------------------------------------------------------

CSessionData& CSessionData::operator =(CSessionData const& value)
{
	//copy the data
	CLock lock = m_clsPropLock;
	SetSysTicks(value.m_numSysTicks);
	SetIdleTime(value.m_numIdleTime);
	set_PeerAddr(value.get_PeerAddr());
	set_TCPProxy((const_cast<CSessionData&>(value)).get_TCPProxy());
	set_UDPPoint((const_cast<CSessionData&>(value)).get_UDPPoint());
	set_IChannel(value.get_IChannel());
	return *this;
}

//---------------------------------------------------------------------------
