//	UDPPoint.cpp
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "UDPPoint.h"
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

CUDPPoint::CUDPPoint(AddressFamily flgFamily) : m_flgFamily(flgFamily)
{
	DEBUG_PRINTF("[CUDPPoint::CUDPPoint] %p\n", this);

	//reset timeouts
	ResetReadIdleTimeout();
	ResetSendIdleTimeout();
}

//---------------------------------------------------------------------------

CUDPPoint::~CUDPPoint(VOID)
{
	DEBUG_PRINTF("[CUDPPoint::~CUDPPoint] %p\n", this);

	//make sure to shutdown the thread first or 
	//otherwise bad things will happen!
	CTcpUdpBase::Shutdown(THREAD_STOP_COUNT);
}

//---------------------------------------------------------------------------

size_t CUDPPoint::GetMaxBufferSize(VOID)
{
	return POINT_MAX_BUFSIZE;
}

//---------------------------------------------------------------------------

BOOL CUDPPoint::SetAllowBroadcast(BOOL flgEnable)
{
	//sanity check
	CSocket* psocket = CTcpUdpBase::GetSocket();
	if (NULL == psocket)
	{
		return FALSE;
	}

	//set the option
	return psocket->SetBroadcast(flgEnable);
}

//---------------------------------------------------------------------------

BOOL CUDPPoint::SetExclusiveUse(BOOL flgEnable)
{
	//sanity check
	CSocket* psocket = CTcpUdpBase::GetSocket();
	if (NULL == psocket)
	{
		return FALSE;
	}

	//set the option
	return psocket->SetExclusive(flgEnable);
}

//---------------------------------------------------------------------------

BOOL CUDPPoint::SetAddressReuse(BOOL flgEnable)
{
	//sanity check
	CSocket* psocket = CTcpUdpBase::GetSocket();
	if (NULL == psocket)
	{
		return FALSE;
	}

	//set the option
	return psocket->SetAddrReuse(flgEnable);
}

//---------------------------------------------------------------------------

BOOL CUDPPoint::SetLingerOption(
	BOOL flgEnable, BOOL flgLinger, size_t numTimeout)
{
	//sanity check
	CSocket* psocket = CTcpUdpBase::GetSocket();
	if (NULL == psocket)
	{
		return FALSE;
	}

	//set the option
	return psocket->SetLingerOption(
		flgEnable, flgLinger, numTimeout);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BOOL CUDPPoint::Activate(LPCTSTR pszAddr, int numPort)
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
		if (INVALID_SOCKET != psocket->GetDescriptor())
		{
			//socket must be closed first
			return FALSE;	//do not touch the socket here!
		}

		//create new socket
		if (FALSE == psocket->Create(
			m_flgFamily, ProtocolTypes::PROTO_UDP, FALSE))
		{
			//cannot create a socket
			goto Activate_Failure;
		}
	
		//try binding the socket
		if (FALSE == psocket->Bind(pszAddr, numPort))
		{
			//cannot bind the socket
			goto Activate_Failure;
		}
	
		//start the therad
		if (FALSE != CTcpUdpBase::Activate())
		{
			//success
			return TRUE;
		}
	}
	catch (...) {}

Activate_Failure:

	//close the socket and exit
	CTcpUdpBase::Shutdown(THREAD_STOP_COUNT);
	return FALSE;
}

//---------------------------------------------------------------------------

int CUDPPoint::SendTo(CAddressInfo const& refAddress, 
	BYTE const* bufData, size_t numSize, size_t numTimeout)
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
			try { sent = psocket->SendTo(refAddress.Family, 
				refAddress.Address, refAddress.Port, &bufData[total], numSize - total); }
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
		Platform::THREAD_SLEEP(POINT_SEND_WAIT);
	}

	//return the total number of bytes sent
	return total;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BOOL CUDPPoint::ThreadStart(VOID* ptrParam)
{
	//get address info
	if (FALSE == CTcpUdpBase::GetLocalAddress(&m_clsLocalAddress))
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
	args.m_clsRemoteAddress.Clear();

    //fire event
    try { ActivateEvent(this, &args); } catch (...) {}

	//done!
	return TRUE;
}

//---------------------------------------------------------------------------

BOOL CUDPPoint::ThreadStop(VOID* ptrParam)
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
	args.m_clsRemoteAddress.Clear();

    //fire event
    try { ShutdownEvent(this, &args); } catch (...) {}
	return TRUE;
}

//---------------------------------------------------------------------------

BOOL CUDPPoint::ThreadProc(VOID* ptrParam)
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

	//check if there is anything to read
	SocketStatus status = CTcpUdpBase::Poll(SocketQueries::QUERY_READ);
	if (SocketStatuses::IS_SUCCESS == status)
	{
		//read data
		CAddressInfo remote;
		int read = 0;
		try { read = psocket->ReadFrom(m_bufRxData, POINT_MAX_BUFSIZE,
			&(remote.Family), remote.Address, ADDRESS_BUFFER_SIZE, &(remote.Port)); }
		catch (...) { read = SOCKET_INVALID_VALUE; }
		if (0 < read)
		{
			//reset read idle timeout
			ResetReadIdleTimeout();

			//update remote address
			args.m_clsRemoteAddress = remote;

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
		else
		{
			//check if it's really an error (UDP socket's 'recvfrom' may
			//return SOCKET_ERROR if 'sendto' fails, but that does not 
			//necessarily mean the socket becomes unusable due to an error)

			//not an interruption error?
			read = CTcpUdpBase::GetErrorCode();
			if (EINTR != read)
			{
				//other error?
				if (0 != read)
				{
					//socket error
					return FALSE;	//end the thread
				}
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
		Platform::THREAD_SLEEP(POINT_READ_WAIT);
	}

	//fire event
	try { MainLoopEvent(this, &args); } catch (...) {}
	return TRUE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID CUDPPoint::ResetReadIdleTimeout(VOID)
{
	//reset rx idle timeout
	CLock lock = m_objTimeoutLock;
	int timeout = CTcpUdpBase::GetReadIdleTimeout();
	m_objReadIdleTimeout = (0 < timeout)? 
		time(NULL) + timeout : (numeric_limits<time_t>::max)();
}

//---------------------------------------------------------------------------

VOID CUDPPoint::ResetSendIdleTimeout(VOID)
{
	//reset tx idle timeout
	CLock lock = m_objTimeoutLock;
	int timeout = CTcpUdpBase::GetSendIdleTimeout();
	m_objSendIdleTimeout = (0 < timeout)? 
		time(NULL) + timeout : (numeric_limits<time_t>::max)();
}

//---------------------------------------------------------------------------

VOID CUDPPoint::TestReadIdleTimeout(VOID)
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
		args.m_clsRemoteAddress.Clear();

		//signal idle
		try { ReadIdleEvent(this, &args); } catch (...) {}
	}
}

//---------------------------------------------------------------------------

VOID CUDPPoint::TestSendIdleTimeout(VOID)
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
		args.m_clsRemoteAddress.Clear();

		//signal idle
		try { SendIdleEvent(this, &args); } catch (...) {}
	}
}

//---------------------------------------------------------------------------
