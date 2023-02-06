//	TCPServer.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

//---------------------------------------------------------------------------

#include "TCPProxy.h"
#include "TDictionary.hpp"
#include "TEventHandler.hpp"

//---------------------------------------------------------------------------

#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

//---------------------------------------------------------------------------

#define SERVER_THREAD_WAIT			1		//[ms]
#define SERVER_ACCEPT_WAIT			1		//[ms]
#define SERVER_CLIENT_TIMEOUT		3		//[sec] (longer than THREAD_STOP_COUNT * THREAD_STOP_SLEEP)

//---------------------------------------------------------------------------

class CTCPServer : public CTcpUdpBase
{
//constants
private:

	const TEventHandler<CTCPProxy, CSocketEventArgs, CTCPServer> OnConnectionOpenEventHandler;
	const TEventHandler<CTCPProxy, CSocketEventArgs, CTCPServer> OnConnectionClosedEventHandler;
	const TEventHandler<CTCPProxy, CSocketEventArgs, CTCPServer> OnConnectionThreadEventHandler;
	const TEventHandler<CTCPProxy, CSocketEventArgs, CTCPServer> OnConnectionRxIdleEventHandler;
	const TEventHandler<CTCPProxy, CSocketEventArgs, CTCPServer> OnConnectionTxIdleEventHandler;
	const TEventHandler<CTCPProxy, CSocketEventArgs, CTCPServer> OnConnectionRxDataEventHandler;

//private members
private:

	AddressFamily		m_flgFamily;
	CAddressInfo		m_clsLocalAddress;

	CCriticalSection								m_objClientsLock;
	TDictionary<CTCPProxy*, TMemPtr<CTCPProxy> >	m_lstClients;
	TList<TMemPtr<CTCPProxy> >						m_lstZombies;	//proxies that are no longer active

//constructor and destructor
public:

	CTCPServer(AddressFamily flgFamily = AddressFamilies::ADDR_IP4);
	virtual ~CTCPServer(VOID);

//events
public:

	TEvent<CTCPServer, CSocketEventArgs>	ActivateEvent;
	TEvent<CTCPServer, CSocketEventArgs>	ShutdownEvent;
	TEvent<CTCPServer, CSocketEventArgs>	MainLoopEvent;

	TEvent<CTCPProxy, CSocketEventArgs>		ConnectionOpenEvent;
	TEvent<CTCPProxy, CSocketEventArgs>		ConnectionClosedEvent;
	TEvent<CTCPProxy, CSocketEventArgs>		ConnectionThreadEvent;
	TEvent<CTCPProxy, CSocketEventArgs>		ConnectionRxIdleEvent;
	TEvent<CTCPProxy, CSocketEventArgs>		ConnectionTxIdleEvent;
	TEvent<CTCPProxy, CSocketEventArgs>		ConnectionRxDataEvent;

//properties
public:

//public methods
public:

	BOOL Activate(LPCTSTR pszAddr, int numPort);
	VOID Shutdown(VOID);
	VOID Broadcast(BYTE bufData[], size_t numSize, size_t numTimeout);
	VOID ShutProxy(CTCPProxy* ptrProxy);

//event handlers
private:

	VOID OnConnectionOpenEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnConnectionClosedEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnConnectionThreadEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnConnectionRxIdleEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnConnectionTxIdleEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnConnectionRxDataEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);

//private methods
private:
	virtual BOOL ThreadStart(VOID* ptrParam);	//called from ThreadMain before main loop
	virtual BOOL ThreadStop(VOID* ptrParam);	//called from ThreadMain after main loop
	virtual BOOL ThreadProc(VOID* ptrParam);	//called from ThreadMain main loop

    VOID ConnectEvents(CTCPProxy* ptrProxy);
    VOID DisconnectEvents(CTCPProxy* ptrProxy);
};

//---------------------------------------------------------------------------
#endif	//_TCP_SERVER_H_
