//	TcpUdpBase.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

//---------------------------------------------------------------------------

#include "Socket.h"
#include "AddressInfo.h"
#include "TMemPtr.hpp"
#include "Lock.hpp"
#include "Thread.hpp"

//---------------------------------------------------------------------------

#ifndef _TCP_UDP_BASE_H_
#define _TCP_UDP_BASE_H_

//---------------------------------------------------------------------------

class CTcpUdpBase : protected CThread
{
//private members
private:

	TMemPtr<CSocket>	m_ptrSocket;

    int					m_numReadIdleTimeout;	//[s]
	int					m_numSendIdleTimeout;	//[s]
	CCriticalSection	m_objTimeoutLock;

	VOID*				m_ptrOwner;
	VOID*				m_ptrTag;

//constructor and destructor
public:

	CTcpUdpBase(VOID);
	virtual ~CTcpUdpBase(VOID);

//properties
public:

	CSocket* GetSocket(VOID);
	VOID SetSocket(CSocket* value);

	int GetErrorCode(VOID);

	AddressFamily GetAddressFamily(VOID);
	ProtocolType GetProtocolType(VOID);

	BOOL GetLocalAddress(CAddressInfo* ptrAddrInfo);
	BOOL GetRemoteAddress(CAddressInfo* ptrAddrInfo);

	int GetReadIdleTimeout(VOID);
	VOID SetReadIdleTimeout(int value);

	int GetSendIdleTimeout(VOID);
	VOID SetSendIdleTimeout(int value);

	VOID* GetOwner(VOID);
	VOID SetOwner(VOID* value);

	VOID* GetTag(VOID);
	VOID SetTag(VOID* value);

//public methods
public:

	ThreadState GetState(VOID) const;	//return the thread state

	virtual BOOL IsActive(VOID);
    virtual BOOL Activate(VOID);
    virtual BOOL Shutdown(int numTimeout);

	SocketStatus Poll(SocketQuery flgQuery);

//protected methods
protected:
};

//---------------------------------------------------------------------------
#endif	//_TCP_UDP_BASE_H_
