//	TcpUdpBase.cpp
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "TcpUdpBase.h"

#if defined(WINDOWS)
#include <tchar.h>
#elif defined(LINUX)
#else
#error "Undefined platform information!"
#endif

//---------------------------------------------------------------------------

CTcpUdpBase::CTcpUdpBase(VOID) :  
	m_numReadIdleTimeout(0), m_numSendIdleTimeout(0),
	m_ptrOwner(NULL), m_ptrTag(NULL)
{
	//initialize member variables
	m_ptrSocket.Create();
}

//---------------------------------------------------------------------------

CTcpUdpBase::~CTcpUdpBase(VOID)
{
	//make sure to call CTcpUdpBase::Shutdown(...) 
	//from the destructor of the derived class
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

CSocket* CTcpUdpBase::GetSocket(VOID)
{
	return static_cast<CSocket*>(m_ptrSocket);
}

VOID CTcpUdpBase::SetSocket(CSocket* value)
{
	m_ptrSocket.Attach(value, 1);
}

//---------------------------------------------------------------------------

int CTcpUdpBase::GetErrorCode(VOID)
{
	try 
	{
		//check the socket
		if (FALSE == m_ptrSocket.IsNull())
		{
			//get socket error
			int error_code = m_ptrSocket->GetSocketError();
			if (SOCKET_ERROR == error_code)
			{
				//get last error code
				error_code = m_ptrSocket->GetErrorCode();
			}

			//return error code
			return error_code;
		}
	}
	catch (...) 
	{
		DEBUG_ASSERT(FALSE);
	}
	//failure
	return SOCKET_ERROR;
}

//---------------------------------------------------------------------------

AddressFamily CTcpUdpBase::GetAddressFamily(VOID)
{
	//check the socket
	if (FALSE == m_ptrSocket.IsNull())
	{
		//return the address family
		return m_ptrSocket->GetAddressFamily();
	}

	//failure
	return AddressFamilies::ADDR_UNSPEC;
}

//---------------------------------------------------------------------------

ProtocolType CTcpUdpBase::GetProtocolType(VOID)
{
	//check the socket
	if (FALSE == m_ptrSocket.IsNull())
	{
		//return the protocol type
		return m_ptrSocket->GetProtocolType();
	}

	//failure
	return ProtocolTypes::PROTO_UNSPEC;
}

//---------------------------------------------------------------------------

BOOL CTcpUdpBase::GetLocalAddress(CAddressInfo* ptrAddrInfo)
{
	//sanity check
	if (NULL == ptrAddrInfo)
	{
		return FALSE;
	}

	//clear the result
	ptrAddrInfo->Clear();

	//check the socket
	if (FALSE == m_ptrSocket.IsNull())
	{
		//get address
		return m_ptrSocket->GetLocalHost(&(ptrAddrInfo->Family), 
			ptrAddrInfo->Address, ADDRESS_BUFFER_SIZE, &(ptrAddrInfo->Port));
	}

	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CTcpUdpBase::GetRemoteAddress(CAddressInfo* ptrAddrInfo)
{
	//sanity check
	if (NULL == ptrAddrInfo)
	{
		return FALSE;
	}

	//clear the result
	ptrAddrInfo->Clear();

	//check the socket
	if (FALSE == m_ptrSocket.IsNull())
	{
		//get address
		return m_ptrSocket->GetRemoteHost(&(ptrAddrInfo->Family), 
			ptrAddrInfo->Address, ADDRESS_BUFFER_SIZE, &(ptrAddrInfo->Port));
	}

	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

int CTcpUdpBase::GetReadIdleTimeout(VOID)
{
	CLock lock = m_objTimeoutLock;
	return m_numReadIdleTimeout;
}

VOID CTcpUdpBase::SetReadIdleTimeout(int value)
{
	CLock lock = m_objTimeoutLock;
	m_numReadIdleTimeout = (value > 0)? value : 0;
}

//---------------------------------------------------------------------------

int CTcpUdpBase::GetSendIdleTimeout(VOID)
{
	CLock lock = m_objTimeoutLock;
	return m_numSendIdleTimeout;
}

VOID CTcpUdpBase::SetSendIdleTimeout(int value)
{
	CLock lock = m_objTimeoutLock;
	m_numSendIdleTimeout = (value > 0)? value : 0;
}

//---------------------------------------------------------------------------

VOID* CTcpUdpBase::GetOwner(VOID)
{
	return m_ptrOwner;
}

VOID CTcpUdpBase::SetOwner(VOID* value)
{
	m_ptrOwner = value;
}

//---------------------------------------------------------------------------

VOID* CTcpUdpBase::GetTag(VOID)
{
	return m_ptrTag;
}

VOID CTcpUdpBase::SetTag(VOID* value)
{
	m_ptrTag = value;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

ThreadState CTcpUdpBase::GetState(VOID) const
{
	return CThread::GetState();
}

//---------------------------------------------------------------------------

BOOL CTcpUdpBase::IsActive(VOID)
{
	ThreadState state = CThread::GetState();
	return ((ThreadStates::Unknown != state) &&
		(ThreadStates::Stopped != state))? TRUE : FALSE;
}

//---------------------------------------------------------------------------

BOOL CTcpUdpBase::Activate(VOID)
{
	//start the therad
	if (FALSE != CThread::Start())
	{
		//success
		return TRUE;
	} 

	//make sure everything is shutdown
	Shutdown(THREAD_STOP_COUNT);
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CTcpUdpBase::Shutdown(int numTimeout)
{
	//stop the thread
	if (FALSE == CThread::Stop(numTimeout))
	{
		//the thread hasn't stopped yet
		return FALSE;
	}

	//check the socket
	if (FALSE == m_ptrSocket.IsNull())
	{
		//shutdown and close the socket
		try { m_ptrSocket->Shutdown(ShutdownOptions::OPT_BOTH); }
		catch (...) {}
		try { m_ptrSocket->Close(); }
		catch (...) {}
	}

	//done
	return TRUE;
}

//---------------------------------------------------------------------------

SocketStatus CTcpUdpBase::Poll(SocketQuery flgQuery)
{
	try
	{
		//check the socket
		if (FALSE == m_ptrSocket.IsNull())
		{
			//query the socket
			return m_ptrSocket->Query(flgQuery, SOCKET_QUERY_WAIT);
		}
	}
	catch (...)
	{
		DEBUG_ASSERT(FALSE);
	}
	//failure
	return SocketStatuses::IS_FAILURE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
