//	UDPPoint.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

//---------------------------------------------------------------------------

#include "TcpUdpBase.h"
#include "Lock.hpp"
#include "TEvent.hpp"
#include "SocketEventArgs.h"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

//---------------------------------------------------------------------------

#ifndef _UDP_POINT_H_
#define _UDP_POINT_H_

//---------------------------------------------------------------------------

#define POINT_SEND_WAIT		10	//[ms]
#define POINT_READ_WAIT		1	//[ms]
#define POINT_MAX_BUFSIZE	8200

//---------------------------------------------------------------------------

class CUDPPoint : public CTcpUdpBase
{
//private members
private:

	AddressFamily		m_flgFamily;
	CAddressInfo		m_clsLocalAddress;
	CAddressInfo		m_clsRemoteAddress;
	BYTE				m_bufRxData[POINT_MAX_BUFSIZE];

	time_t				m_objReadIdleTimeout;
	time_t				m_objSendIdleTimeout;
	CCriticalSection	m_objTimeoutLock;

//constructor and destructor
public:

	CUDPPoint(AddressFamily flgFamily = AddressFamilies::ADDR_IP4);
	virtual ~CUDPPoint(VOID);

//events
public:

	TEvent<CUDPPoint, CSocketEventArgs>	ActivateEvent;
	TEvent<CUDPPoint, CSocketEventArgs>	ShutdownEvent;
	TEvent<CUDPPoint, CSocketEventArgs>	MainLoopEvent;
	TEvent<CUDPPoint, CSocketEventArgs>	ReadIdleEvent;	//receiver idle timeout
	TEvent<CUDPPoint, CSocketEventArgs>	SendIdleEvent;	//transmitter idle timeout
	TEvent<CUDPPoint, CSocketEventArgs>	ReceivedEvent;

//properties
public:

	size_t GetMaxBufferSize(VOID);

	BOOL SetAllowBroadcast(BOOL flgEnable);
	BOOL SetExclusiveUse(BOOL flgEnable);
	BOOL SetAddressReuse(BOOL flgEnable);
	BOOL SetLingerOption(BOOL flgEnable, BOOL flgLinger, size_t numTimeout);

//public methods
public:

    BOOL Activate(LPCTSTR pszAddr, int numPort);
	int SendTo(CAddressInfo const& refAddress, 
		BYTE const* bufData, size_t numSize, size_t numTimeout);

//private methods
private:

	virtual BOOL ThreadStart(VOID* ptrParam);	//called from ThreadMain before main loop
	virtual BOOL ThreadStop(VOID* ptrParam);	//called from ThreadMain after main loop
	virtual BOOL ThreadProc(VOID* ptrParam);	//called from ThreadMain main loop

	VOID ResetReadIdleTimeout(VOID);
	VOID ResetSendIdleTimeout(VOID);
	VOID TestReadIdleTimeout(VOID);
	VOID TestSendIdleTimeout(VOID);
};

//---------------------------------------------------------------------------
#endif	//_UDP_POINT_H_
