//	TCPProxy.h
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

#ifndef _TCP_PROXY_H_
#define _TCP_PROXY_H_

//---------------------------------------------------------------------------

#define PROXY_SEND_WAIT		10	//[ms]
#define PROXY_READ_WAIT		1	//[ms]
#define PROXY_MAX_BUFSIZE	8200

//---------------------------------------------------------------------------

class CTCPProxy : public CTcpUdpBase
{
//private members
private:

	CAddressInfo		m_clsLocalAddress;
	CAddressInfo		m_clsRemoteAddress;
	BYTE				m_bufRxData[PROXY_MAX_BUFSIZE];

	time_t				m_objReadIdleTimeout;
	time_t				m_objSendIdleTimeout;
	CCriticalSection	m_objTimeoutLock;

//constructor and destructor
public:

	CTCPProxy(VOID);
	virtual ~CTCPProxy(VOID);

//events
public:

	TEvent<CTCPProxy, CSocketEventArgs>	ActivateEvent;
	TEvent<CTCPProxy, CSocketEventArgs>	ShutdownEvent;
	TEvent<CTCPProxy, CSocketEventArgs>	MainLoopEvent;
	TEvent<CTCPProxy, CSocketEventArgs>	ReadIdleEvent;	//receiver idle timeout
	TEvent<CTCPProxy, CSocketEventArgs>	SendIdleEvent;	//transmitter idle timeout
	TEvent<CTCPProxy, CSocketEventArgs>	ReceivedEvent;

//properties
public:

	size_t GetMaxBufferSize(VOID);

//public methods
public:

	BOOL Activate(VOID);
	BOOL IsConnected(VOID);
	int Send(BYTE const* bufData, size_t numSize, size_t numTimeout);

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
#endif	//_TCP_PROXY_H_
