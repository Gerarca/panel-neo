//	TCPProxy.cpp
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "TCPProxy.h"
#include "SocketEventArgs.h"
#include <ctime>
#include <limits>

#if defined(WINDOWS)
#include <tchar.h>
#include <process.h>
#elif defined(LINUX)
#else
#error "Undefined platform information!"
#endif

using namespace std;

//---------------------------------------------------------------------------

CTCPProxy::CTCPProxy(VOID) : CTcpUdpBase()
{
	DEBUG_PRINTF("[CTCPProxy::CTCPProxy] %p\n", this);

	//reset timeouts
	ResetReadIdleTimeout();
	ResetSendIdleTimeout();
}

//---------------------------------------------------------------------------

CTCPProxy::~CTCPProxy(VOID)
{
	DEBUG_PRINTF("[CTCPProxy::~CTCPProxy] %p\n", this);

	//make sure to shutdown the thread first or 
	//otherwise bad things will happen!
	CTcpUdpBase::Shutdown(THREAD_STOP_COUNT);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

size_t CTCPProxy::GetMaxBufferSize(VOID)
{
	return PROXY_MAX_BUFSIZE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BOOL CTCPProxy::Activate(VOID)
{
	//sanity check
	CSocket* psocket = CTcpUdpBase::GetSocket();
	if (NULL == psocket)
	{
		return FALSE;
	}

	try
	{
		//clear addresses
		m_clsLocalAddress.Clear();
		m_clsRemoteAddress.Clear();

		//check if socket is already present
		if (INVALID_SOCKET == psocket->GetDescriptor())
		{
			//socket must be present
			return FALSE;
		}

		//start the therad
		if (FALSE != CTcpUdpBase::Activate())
		{
			//success
			return TRUE;
		}
	}
	catch (...) {}

	//make sure the proxy is shutdown
	CTcpUdpBase::Shutdown(THREAD_STOP_COUNT);
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CTCPProxy::IsConnected(VOID)
{
	//temp data buffer
	BYTE data = 0;

	//sanity check
	CSocket* psocket = CTcpUdpBase::GetSocket();
	if (NULL == psocket)
	{
		return FALSE;
	}

	//try sending 0 bytes
	return (0 <= psocket->Send(&data, 0))? TRUE : FALSE;
}

//---------------------------------------------------------------------------

int CTCPProxy::Send(BYTE const* bufData, size_t numSize, size_t numTimeout)
{
	//sanity check
	CSocket* psocket = CTcpUdpBase::GetSocket();
	if (NULL == psocket)
	{
		return SOCKET_INVALID_VALUE;
	}

    //initialize variables
    int sent = 0;
    int total = 0;
    SocketStatus status;
	
	//send data
	time_t timeout = (0 < numTimeout)? 
		time(NULL) + numTimeout : (numeric_limits<time_t>::max)();
	while (0 <= difftime(timeout, time(NULL)))
	{
		//check if ready to send
		status = CTcpUdpBase::Poll(SocketQueries::QUERY_SEND);
		if (SocketStatuses::IS_SUCCESS == status)
		{
			//send data
			try { sent = psocket->Send(&bufData[total], numSize - total); }
			catch (...) { sent = SOCKET_INVALID_VALUE; }
			if (0 <= sent)
			{
				//reset tx idle timeout
				ResetSendIdleTimeout();

				//count sent bytes
				total += sent;
				if (total >= static_cast<int>(numSize))
				{
					//all data sent
					break;
				}
			} 
			else
			{
				//not an interruption error?
				if (EINTR != CTcpUdpBase::GetErrorCode())
				{
					//failed to send data
					break;
				}
			}
		}
		else if (SocketStatuses::IS_FAILURE == status)
		{
			//not an interruption error?
			if (EINTR != CTcpUdpBase::GetErrorCode())
			{
				//stop trying to send data
				break;
			}
		}
		//switch threads and wait
		Platform::THREAD_SLEEP(PROXY_SEND_WAIT);
	}

	//return the total number of bytes sent
	return total;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BOOL CTCPProxy::ThreadStart(VOID* ptrParam)
{
	//get address info
	if ((FALSE == CTcpUdpBase::GetLocalAddress(&m_clsLocalAddress)) ||
		(FALSE == CTcpUdpBase::GetRemoteAddress(&m_clsRemoteAddress)))
	{
		//cannot get local or remote address
		DEBUG_CHECK(FALSE);
		RELEASE_CHECK(FALSE);
		return FALSE;
	}

	//reset timeouts
	ResetReadIdleTimeout();
	ResetSendIdleTimeout();

	//prepare event args
	CSocketEventArgs args;
	args.m_clsLocalAddress = m_clsLocalAddress;
	args.m_clsRemoteAddress = m_clsRemoteAddress;

    //fire event
    try { ActivateEvent(this, &args); } catch (...) {}

	//done!
	return TRUE;
}

//---------------------------------------------------------------------------

BOOL CTCPProxy::ThreadStop(VOID* ptrParam)
{
	//shutdown and close the socket
	CSocket* psocket = CTcpUdpBase::GetSocket();
	if (NULL != psocket)
	{
		try { psocket->Shutdown(ShutdownOptions::OPT_BOTH); }
		catch (...) {}
		try { psocket->Close(); }
		catch (...) {}
	}

	//prepare event args
	CSocketEventArgs args;
	args.m_clsLocalAddress = m_clsLocalAddress;
	args.m_clsRemoteAddress = m_clsRemoteAddress;

    //fire event
    try { ShutdownEvent(this, &args); } catch (...) {}
	return TRUE;
}

//---------------------------------------------------------------------------

BOOL CTCPProxy::ThreadProc(VOID* ptrParam)
{
	//sanity check
	CSocket* psocket = CTcpUdpBase::GetSocket();
	if (NULL == psocket)
	{
		return FALSE;
	}

	//prepare event args
	CSocketEventArgs args;
	args.m_clsLocalAddress = m_clsLocalAddress;
	args.m_clsRemoteAddress = m_clsRemoteAddress;

	//check if there is anything to read
	SocketStatus status = CTcpUdpBase::Poll(SocketQueries::QUERY_READ);
	if (SocketStatuses::IS_SUCCESS == status)
	{
		//read data
		int read = 0;
		try { read = psocket->Read(m_bufRxData, PROXY_MAX_BUFSIZE); }
		catch (...) { read = SOCKET_INVALID_VALUE; }
		if (0 < read)
		{
			//reset read idle timeout
			ResetReadIdleTimeout();

			//allocate data buffer
			if (FALSE == args.m_bufDataBuffer.Create(read))
			{
				//failed to allocate required memory
				DEBUG_CHECK(FALSE);
				RELEASE_CHECK(FALSE);
				return FALSE;
			}

			//copy data
			memcpy(args.m_bufDataBuffer, m_bufRxData, read);

			//fire event
			try { ReceivedEvent(this, &args); } catch (...) {}
		} 
		else if (0 == read)
		{
			//connection closed
			return FALSE;	//end the thread
		}
		else	//error
		{
			//not an interruption error?
			if (EINTR != CTcpUdpBase::GetErrorCode())
			{
				//socket error
				return FALSE;	//end the thread
			}
		}
	}
	else if (SocketStatuses::IS_FAILURE == status)
	{
		//not an interruption error?
		if (EINTR != CTcpUdpBase::GetErrorCode())
		{
			//stop polling the socket
			return FALSE;	//end the thread
		}
	}
	else	//SockStatuses::IS_TIMEOUT
	{
		//check read idle timeout
		TestReadIdleTimeout();
		
		//check send idle timeout
		TestSendIdleTimeout();

		//switch threads - take your time because there was no new data
		Platform::THREAD_SLEEP(PROXY_READ_WAIT);
	}

	//fire event
	try { MainLoopEvent(this, &args); } catch (...) {}
	return TRUE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID CTCPProxy::ResetReadIdleTimeout(VOID)
{
	//reset rx idle timeout
	CLock lock = m_objTimeoutLock;
	int timeout = CTcpUdpBase::GetReadIdleTimeout();
	m_objReadIdleTimeout = (0 < timeout)? 
		time(NULL) + timeout : (numeric_limits<time_t>::max)();
}

//---------------------------------------------------------------------------

VOID CTCPProxy::ResetSendIdleTimeout(VOID)
{
	//reset tx idle timeout
	CLock lock = m_objTimeoutLock;
	int timeout = CTcpUdpBase::GetSendIdleTimeout();
	m_objSendIdleTimeout = (0 < timeout)? 
		time(NULL) + timeout : (numeric_limits<time_t>::max)();
}

//---------------------------------------------------------------------------

VOID CTCPProxy::TestReadIdleTimeout(VOID)
{
	//check idle timeout
	CLock lock = m_objTimeoutLock;
	if (0 >= difftime(m_objReadIdleTimeout, time(NULL)))
	{
		//reset rx idle timeout
		int timeout = CTcpUdpBase::GetReadIdleTimeout();
		m_objReadIdleTimeout = (0 < timeout)? 
			time(NULL) + timeout : (numeric_limits<time_t>::max)();

		//prepare event args
		CSocketEventArgs args;
		args.m_clsLocalAddress = m_clsLocalAddress;
		args.m_clsRemoteAddress = m_clsRemoteAddress;

		//signal idle
		try { ReadIdleEvent(this, &args); } catch (...) {}
	}
}

//---------------------------------------------------------------------------

VOID CTCPProxy::TestSendIdleTimeout(VOID)
{
	//check idle timeout
	CLock lock = m_objTimeoutLock;
	if (0 >= difftime(m_objSendIdleTimeout, time(NULL)))
	{
		//reset tx idle timeout
		int timeout = CTcpUdpBase::GetSendIdleTimeout();
		m_objSendIdleTimeout = (0 < timeout)? 
			time(NULL) + timeout : (numeric_limits<time_t>::max)();
		
		//prepare event args
		CSocketEventArgs args;
		args.m_clsLocalAddress = m_clsLocalAddress;
		args.m_clsRemoteAddress = m_clsRemoteAddress;

		//signal idle
		try { SendIdleEvent(this, &args); } catch (...) {}
	}
}

//---------------------------------------------------------------------------
