//	TCPClient.cpp
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "TCPClient.h"
#include <ctime>
#include <limits>

#if defined(WINDOWS)
#elif defined(LINUX)
#include <cerrno>
#define WSAEWOULDBLOCK EWOULDBLOCK
#else
#error "Undefined platform information!"
#endif

//---------------------------------------------------------------------------

CTCPClient::CTCPClient(AddressFamily flgFamily) : m_flgFamily(flgFamily)
{
}

//---------------------------------------------------------------------------

CTCPClient::~CTCPClient(VOID)
{
}

//---------------------------------------------------------------------------

BOOL CTCPClient::Connect(LPCTSTR pszAddr, int numPort, size_t numTimeout)
{
	//sanity check
	CSocket* psocket = CTCPProxy::GetSocket();
	if (NULL == psocket)
	{
		return FALSE;
	}

	try
	{
		//check if socket is already present
		if (INVALID_SOCKET != psocket->GetDescriptor())
		{
			//socket must be closed first
			return FALSE;	//do not touch the socket here!
		}

		//create new non-blocking socket
		if (FALSE == psocket->Create(
			m_flgFamily, ProtocolTypes::PROTO_TCP, TRUE))
		{
			//cannot create a socket
			goto Connect_Failure;
		}
	
		//try connecting
		BOOL connected = FALSE;
		if (FALSE != psocket->Connect(pszAddr, numPort))
		{
			//connected
			connected = TRUE;
		}
		else
		{
			//check if wait is necessary
			if (WSAEWOULDBLOCK == psocket->GetErrorCode())
			{
				//calculate timeout
				time_t timeout = (0 < numTimeout)? 
					time(NULL) + numTimeout : (numeric_limits<time_t>::max)();

				//continue waiting
				while (0 <= difftime(timeout, time(NULL)))
				{
					//check if connected
					if (SocketStatuses::IS_SUCCESS == 
						CTCPProxy::Poll(SocketQueries::QUERY_CONNECT))
					{
						//connected
						connected = TRUE;
						break;
					}
				
					//switch threads and wait
					Platform::THREAD_SLEEP(CLIENT_CONNECT_WAIT);
				}
			}
		}
	
		//check if client is connected
		if (FALSE != connected)
		{
			//change socket to blocking
			if (FALSE != psocket->SetNonBlocked(FALSE))
			{
				//start thread
				return CTCPProxy::Activate();
			}
		}
	}
	catch (...)
	{
		//do nothing
	}

Connect_Failure:

	//close the socket and exit
	CTCPProxy::Shutdown(THREAD_STOP_COUNT);
	return FALSE;
}

//---------------------------------------------------------------------------
