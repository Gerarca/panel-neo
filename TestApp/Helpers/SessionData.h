//	SessionData.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

//---------------------------------------------------------------------------

#include "TComPtr.hpp"
#include "AddressInfo.h"
#include "DSC_IChannel.hpp"
#include "Lock.hpp"
#include "TCPProxy.h"
#include "UDPPoint.h"
#include <ctime>

using namespace std;
using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

//---------------------------------------------------------------------------

#ifndef _SESSION_DATA_H_
#define _SESSION_DATA_H_

//---------------------------------------------------------------------------

class CSessionData 
{
//private members
private:
	CCriticalSection		m_clsPropLock;
	UINT32					m_numSysTicks;
	UINT32					m_numIdleTime;
	time_t					m_clsIdleTime;

	CAddressInfo			m_clsPeerAddr;	//remote address
	CTCPProxy*				m_ptrTCPProxy;
	CUDPPoint*				m_ptrUDPPoint;
	TComPtr<DSC_IChannel>	m_clsIChannel;

//constructor and destructor
public:
	CSessionData(VOID);
	CSessionData(CSessionData const& refSessionData);
	virtual ~CSessionData(VOID);

//public methods
public:

	CAddressInfo get_PeerAddr(VOID) const;
	VOID set_PeerAddr(CAddressInfo const& value);

	CTCPProxy* get_TCPProxy(VOID) const;
	CTCPProxy* set_TCPProxy(CTCPProxy* value);

	CUDPPoint* get_UDPPoint(VOID) const;
	CUDPPoint* set_UDPPoint(CUDPPoint* value);

	TComPtr<DSC_IChannel> get_IChannel(VOID) const;
	VOID set_IChannel(TComPtr<DSC_IChannel> const& value);

	VOID Clear(VOID);
	VOID SetSysTicks(UINT32 numTicks);
	BOOL TestSysTicks(VOID);
	VOID SetIdleTime(UINT32 numSecs);
	BOOL TestIdleTime(VOID);

//operators
public:
	CSessionData& operator =(CSessionData const& value);
};

//---------------------------------------------------------------------------
#endif	//_SESSION_DATA_H_
