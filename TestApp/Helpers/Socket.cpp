//	Socket.cpp
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "Socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#if defined(WINDOWS)
#include <tchar.h>
#elif defined(LINUX)
#else
#error "Undefined platform information!"
#endif

//---------------------------------------------------------------------------

CSocket::CSocket(VOID) : m_flgFamily(AddressFamilies::ADDR_UNSPEC), 
	m_flgProtocol(ProtocolTypes::PROTO_UNSPEC), m_clsSocket(INVALID_SOCKET)
{
	ClearSockInfo();
}

//---------------------------------------------------------------------------

CSocket::~CSocket(VOID)
{
	//close the socket
	Close();
}

//---------------------------------------------------------------------------

BOOL CSocket::Initialize(VOID)
{
#if defined(WINDOWS)
	//prepare min OS version info
	OSVERSIONINFOEX bufVerInfo;
	memset(&bufVerInfo, 0, sizeof(OSVERSIONINFOEX));
	bufVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	bufVerInfo.dwMajorVersion = SOCKET_OS_MAJOR_VER;
	bufVerInfo.dwMinorVersion = SOCKET_OS_MINOR_VER;
	bufVerInfo.wServicePackMajor = SOCKET_OS_SP_MAJOR_VER;
	bufVerInfo.wServicePackMinor = SOCKET_OS_SP_MINOR_VER;

	//set condition mask
	DWORDLONG numConditionMask = 0;
	VER_SET_CONDITION(numConditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);
	VER_SET_CONDITION(numConditionMask, VER_MINORVERSION, VER_GREATER_EQUAL);
	VER_SET_CONDITION(numConditionMask, VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);
	VER_SET_CONDITION(numConditionMask, VER_SERVICEPACKMINOR, VER_GREATER_EQUAL);

	//verify OS version
	if (!VerifyVersionInfo(&bufVerInfo, VER_MAJORVERSION | VER_MINORVERSION | 
		VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR, numConditionMask))
	{
		//OS version requirement not met
		return FALSE;
	}
	
	//initialize sockets library
	WSADATA	bufData;
	return (SOCKET_ERROR != WSAStartup(
		SOCKET_LIB_VERSION, &bufData))? TRUE : FALSE;
#elif defined(LINUX)
	return TRUE;
#else
#error "Undefined platform information!"
#endif
}

//---------------------------------------------------------------------------

VOID CSocket::CleanupAll(VOID)
{
#if defined(WINDOWS)
	//cleanup sockets library
	WSACleanup();
#elif defined(LINUX)
#else
#error "Undefined platform information!"
#endif
}

//---------------------------------------------------------------------------

SOCKET CSocket::GetDescriptor(VOID)
{
	return m_clsSocket;
}

//---------------------------------------------------------------------------

AddressFamily CSocket::GetAddressFamily(VOID)
{
	return m_flgFamily;
}

//---------------------------------------------------------------------------

ProtocolType CSocket::GetProtocolType(VOID)
{
	return m_flgProtocol;
}

//---------------------------------------------------------------------------

int CSocket::GetErrorCode(VOID)
{
#if defined(WINDOWS)
	return WSAGetLastError();
#elif defined(LINUX)
	return errno;
#else
#error "Undefined platform information!"
#endif
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BOOL CSocket::Create(
	AddressFamily flgFamily, ProtocolType flgProto, BOOL flgUnBlock)
{
	//check if socket is already created
	if (INVALID_SOCKET != m_clsSocket)
	{
		//cleanup is required
		return FALSE;
	}
	
	//argument check
	if (((AddressFamilies::ADDR_IP4 != flgFamily) && 
			(AddressFamilies::ADDR_IP6 != flgFamily)) ||
		((ProtocolTypes::PROTO_TCP != flgProto) && 
			(ProtocolTypes::PROTO_UDP != flgProto)))
	{
		//wrong parameters
		return FALSE;
	}
	
	//set socket type based on the protocol
	int type = (ProtocolTypes::PROTO_TCP == flgProto)? 
		SOCK_STREAM : SOCK_DGRAM;
	
	//create socket
	m_clsSocket = socket(flgFamily, type, flgProto);
	if (INVALID_SOCKET == m_clsSocket)
	{
		//cannot create socket
		return FALSE;
	}
	
	//save socket info
	m_flgFamily = flgFamily;
	m_flgProtocol = flgProto;
	
	//set receiving timeout on the socket so it won't block forever
#if defined(WINDOWS)
	int ms = SOCKET_RECV_TIMEOUT;
#elif defined(LINUX)
	struct timeval ms;
	ms.tv_sec = (SOCKET_RECV_TIMEOUT / 1000);
	ms.tv_usec = ((SOCKET_RECV_TIMEOUT % 1000) * 1000);
#else
#error "Undefined platform information!"
#endif
	if (SOCKET_ERROR == setsockopt(m_clsSocket,
		SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof(ms))) 
	{
		Close();
		return FALSE;
	}
	
	//set sending timeout on the socket so it won't block forever
#if defined(WINDOWS)
	ms = SOCKET_SEND_TIMEOUT;
#elif defined(LINUX)
	ms.tv_sec = (SOCKET_SEND_TIMEOUT / 1000);
	ms.tv_usec = ((SOCKET_SEND_TIMEOUT % 1000) * 1000);
#else
#error "Undefined platform information!"
#endif
	if (SOCKET_ERROR == setsockopt(m_clsSocket,
		SOL_SOCKET, SO_SNDTIMEO, (char*)&ms, sizeof(ms))) 
	{
		Close();
		return FALSE;
	}
	
	//disable or enable blocking
	return SetNonBlocked(flgUnBlock);
}

//---------------------------------------------------------------------------

BOOL CSocket::Shutdown(ShutdownOption flgOption)
{
	if (INVALID_SOCKET != m_clsSocket) 
	{
		//shutdown the socket
		if (SOCKET_ERROR != shutdown(m_clsSocket, flgOption))
		{
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSocket::Close(VOID)
{
	if (INVALID_SOCKET != m_clsSocket) 
	{
		//close socket
		if (SOCKET_ERROR != closesocket(m_clsSocket))
		{
			//clear socket info
			ClearSockInfo();
			return TRUE;
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BOOL CSocket::SetNonBlocked(BOOL flgEnable)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		u_long arg = (flgEnable)? 1 : 0;
		if (SOCKET_ERROR != ioctlsocket(m_clsSocket, FIONBIO, &arg))
		{
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSocket::SetBroadcast(BOOL flgEnable)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		BOOL value = flgEnable;
		if (SOCKET_ERROR != setsockopt(m_clsSocket, 
			SOL_SOCKET, SO_BROADCAST, (char*)&value, sizeof(value)))
		{
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSocket::SetExclusive(BOOL flgEnable)
{
#if defined(WINDOWS)
	if (INVALID_SOCKET != m_clsSocket)
	{
		BOOL value = flgEnable;
		if (SOCKET_ERROR != setsockopt(m_clsSocket,
			SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char*)&value, sizeof(value)))
		{
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
#elif defined(LINUX)
	return TRUE;
#else
#error "Undefined platform information!"
#endif
}

//---------------------------------------------------------------------------

BOOL CSocket::SetAddrReuse(BOOL flgEnable)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		BOOL value = flgEnable;
		if (SOCKET_ERROR != setsockopt(m_clsSocket, 
			SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value)))
		{
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSocket::SetKeepAlive(BOOL flgEnable)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		BOOL value = flgEnable;
		if (SOCKET_ERROR != setsockopt(m_clsSocket, 
			SOL_SOCKET, SO_KEEPALIVE, (char*)&value, sizeof(value)))
		{
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSocket::SetNoDelay(BOOL flgEnable)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		BOOL value = flgEnable;
		if (SOCKET_ERROR != setsockopt(m_clsSocket, 
			IPPROTO_TCP, TCP_NODELAY, (char*)&value, sizeof(value)))
		{
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSocket::SetLingerOption(
	BOOL flgEnable, BOOL flgLinger, size_t numTimeout)
{
#if defined(WINDOWS)
	if (INVALID_SOCKET != m_clsSocket)
	{
		//disable or enable linger
		BOOL value = (FALSE == flgEnable) ? TRUE : FALSE;
		if (SOCKET_ERROR != setsockopt(m_clsSocket,
			SOL_SOCKET, SO_DONTLINGER, (char*)&value, sizeof(value)))
		{
			//setup linger data
			if (FALSE != flgEnable)
			{
				//setup the linger data
				LINGER data;
				data.l_onoff = (FALSE != flgLinger) ? 1 : 0;
				data.l_linger = (u_short)numTimeout;

				//depending on the time value (0 or >0), hard or graceful close
				if (SOCKET_ERROR == setsockopt(m_clsSocket,
					SOL_SOCKET, SO_LINGER, (char*)&data, sizeof(data)))
				{
					//failure
					return FALSE;
				}
			}
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
#elif defined(LINUX)
	return TRUE;
#else
#error "Undefined platform information!"
#endif
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

int CSocket::GetSocketError(VOID)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		int value = 0;
#if defined(WINDOWS)
		int size = sizeof(value);
#elif defined(LINUX)
		socklen_t size = sizeof(value);
#else
#error "Undefined platform information!"
#endif
		if (SOCKET_ERROR != getsockopt(m_clsSocket,
			SOL_SOCKET, SO_ERROR, (char*)&value, &size))
		{
			//success
			return value;
		}
	}
	//failure
	return SOCKET_ERROR;
}

//---------------------------------------------------------------------------

int CSocket::GetMaxMsgSize(VOID)
{
#if defined(WINDOWS)
	if (INVALID_SOCKET != m_clsSocket)
	{
		u_int value = 0;
		int size = sizeof(value);
		if (SOCKET_ERROR != getsockopt(m_clsSocket,
			SOL_SOCKET, SO_MAX_MSG_SIZE, (char*)&value, &size))
		{
			//success
			return (int)value;
		}
	}
	//failure
	return SOCKET_ERROR;
#elif defined(LINUX)
	if (INVALID_SOCKET != m_clsSocket)
	{
		int value = 0;
		socklen_t size = sizeof(value);
		if (SOCKET_ERROR != getsockopt(m_clsSocket,
			SOL_SOCKET, SO_SNDBUF, (char*)&value, &size))
		{
			//success
			return (int)value;
		}
	}
	//failure
	return SOCKET_ERROR;
#else
#error "Undefined platform information!"
#endif
}

//---------------------------------------------------------------------------

int CSocket::GetPendingCount(VOID)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		u_long arg = SOCKET_ERROR;
		if (SOCKET_ERROR != ioctlsocket(m_clsSocket, FIONREAD, &arg))
		{
			//return the count of bytes pending read but only up to INT_MAX
			if (arg > INT_MAX) arg = INT_MAX;
			return static_cast<int>(arg);
		}
	}
	//failure
	return SOCKET_ERROR;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BOOL CSocket::Connect(LPCTSTR pszAddr, int numPort)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		//alocate address space
		SOCKADDR addr;
		memset(&addr, 0, sizeof(addr));
		
		//get address
		if (FALSE != GetAddrData(m_flgFamily, pszAddr, numPort, &addr))
		{
			//connect socket
			if (SOCKET_ERROR != connect(m_clsSocket, &addr, sizeof(addr))) 
			{
				//success
				return TRUE;
			}
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSocket::Bind(LPCTSTR pszAddr, int numPort)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		//alocate address space
		SOCKADDR addr;
		memset(&addr, 0, sizeof(addr));
		
		//get address
		if (FALSE != GetAddrData(m_flgFamily, pszAddr, numPort, &addr))
		{
			//bind socket
			if (SOCKET_ERROR != bind(m_clsSocket, &addr, sizeof(addr))) 
			{
				//success
				return TRUE;
			}
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BOOL CSocket::GetLocalHost(
	AddressFamily* ptrFamily, LPTSTR pszAddr, size_t numLen, int* ptrPort)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		SOCKADDR addr;
#if defined(WINDOWS)
		int size = sizeof(addr);
#elif defined(LINUX)
		socklen_t size = sizeof(addr);
#else
#error "Undefined platform information!"
#endif
		memset(&addr, 0, size);

		//get remote address
		if (SOCKET_ERROR != getsockname(m_clsSocket, &addr, &size))
		{
			//translate the address
			return GetAddrText(&addr, ptrFamily, pszAddr, numLen, ptrPort);
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSocket::GetRemoteHost(
	AddressFamily* ptrFamily, LPTSTR pszAddr, size_t numLen, int* ptrPort)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		SOCKADDR addr;
#if defined(WINDOWS)
		int size = sizeof(addr);
#elif defined(LINUX)
		socklen_t size = sizeof(addr);
#else
#error "Undefined platform information!"
#endif
		memset(&addr, 0, size);

		//get remote address
		if (SOCKET_ERROR != getpeername(m_clsSocket, &addr, &size))
		{
			//translate the address
			return GetAddrText(&addr, ptrFamily, pszAddr, numLen, ptrPort);
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

SocketStatus CSocket::Query(
	SocketQuery flgQuery, size_t numTimeout) //the timeout is in [ms]
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		//validate the timeout
		if (numTimeout < 0) numTimeout = 0;
		
		//calculate timeout
		timeval numFineTimeout;
		numFineTimeout.tv_sec = (long)(       //seconds
			numTimeout / SOCKET_MSEC_PER_SEC);
		numFineTimeout.tv_usec = (long)(      //micro seconds
			numTimeout % SOCKET_MSEC_PER_SEC) * SOCKET_uSEC_PER_MSEC;
		
		//prepare socket set
		fd_set lstSockets;
		FD_ZERO(&lstSockets);
		FD_SET(m_clsSocket, &lstSockets);
		
		int numResult = 0;
		switch (flgQuery)
		{
			case SocketQueries::QUERY_READ:
			case SocketQueries::QUERY_ACCEPT:
				numResult = select(static_cast<int>(m_clsSocket + 1), 
					&lstSockets, NULL, NULL, &numFineTimeout);
				if (0 < numResult) 
				{
					return SocketStatuses::IS_SUCCESS;	//ready to receive data
				} else if (0 == numResult)
				{
					return SocketStatuses::IS_TIMEOUT;	//timeout
				}
				break;

			case SocketQueries::QUERY_SEND: 
			case SocketQueries::QUERY_CONNECT:
				numResult = select(static_cast<int>(m_clsSocket + 1), 
					NULL, &lstSockets, NULL, &numFineTimeout);
				if (0 < numResult)
				{
					return SocketStatuses::IS_SUCCESS;	//ready to transmit data
				} else if (0 == numResult)
				{
					return SocketStatuses::IS_TIMEOUT;	//timeout
				}
				break;

			case SocketQueries::QUERY_ERRORS: 
				numResult = select(static_cast<int>(m_clsSocket + 1), 
					NULL, NULL, &lstSockets, &numFineTimeout);
				if (0 < numResult) 
				{
					return SocketStatuses::IS_SUCCESS;	//errors present
				} else if (0 == numResult)
				{
					return SocketStatuses::IS_TIMEOUT;	//timeout
				}
				break;
		}
	}
	//failure
	return SocketStatuses::IS_FAILURE;
}

//---------------------------------------------------------------------------

int CSocket::Send(BYTE const* bufData, size_t numSize)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		return static_cast<int>(send(m_clsSocket, 
			(const char*)bufData , static_cast<int>(numSize), 0));
	}
	return SOCKET_ERROR;
}

//---------------------------------------------------------------------------

int CSocket::SendTo(AddressFamily flgFamily,
	LPCTSTR pszAddr, int numPort, BYTE const* bufData, size_t numSize)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		//get address
		SOCKADDR addr;
		memset(&addr, 0, sizeof(addr));
		if (FALSE != GetAddrData(flgFamily, pszAddr, numPort, &addr))
		{
			return static_cast<int>(sendto(m_clsSocket, 
				(const char*)bufData, static_cast<int>(numSize), 
				0, &addr, static_cast<int>(sizeof(addr))));
		}
	}
	return SOCKET_ERROR;
}

//---------------------------------------------------------------------------

int CSocket::Read(BYTE* bufData, size_t numSize)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		return static_cast<int>(recv(m_clsSocket, 
			(char*)bufData , static_cast<int>(numSize), 0));
	}
	return SOCKET_ERROR;
}

//---------------------------------------------------------------------------

int CSocket::ReadFrom(BYTE* bufData, size_t numSize, 
	AddressFamily* ptrFamily, LPTSTR pszAddr, size_t numLen, int* ptrPort)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		//prepare address buffer
		SOCKADDR addr;
#if defined(WINDOWS)
		int size = sizeof(addr);
#elif defined(LINUX)
		socklen_t size = sizeof(addr);
#else
#error "Undefined platform information!"
#endif
		memset(&addr, 0, size);

		//is address given?
		if (NULL != pszAddr)
		{
			//receive data and get sender's address
			int read = static_cast<int>(recvfrom(m_clsSocket,
				(char*)bufData, static_cast<int>(numSize), 
				0, &addr, &size));
			if (0 <= read)
			{
				//translate the address
				GetAddrText(&addr, ptrFamily, pszAddr, numLen, ptrPort);

				//return the result
				return read;
			}
		}
		else
		{
			//receive data
			return static_cast<int>(recv(m_clsSocket, 
				(char*)bufData, static_cast<int>(numSize), 0));
		}
	}
	return SOCKET_ERROR;
}

//---------------------------------------------------------------------------

BOOL CSocket::Listen(VOID)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		if (SOCKET_ERROR != listen(m_clsSocket, SOCKET_MAX_BACKLOG))
		{
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

//try accepting the connection
//if ptrSocket is NULL, the method will at least try to obtain the address
//if ptrSocket->m_clsSocket is not INVALID_SOCKET, new connection cannot be accepted
BOOL CSocket::Accept(CSocket* ptrSocket,
	AddressFamily* ptrFamily, LPTSTR pszAddr, size_t numLen, int* ptrPort)
{
	if (INVALID_SOCKET != m_clsSocket)
	{
		//prepare info storage for the new socket
		SOCKET clsNewSock;
		SOCKADDR bufNewAddr;
#if defined(WINDOWS)
		int numNewAddr = sizeof(SOCKADDR);
#elif defined(LINUX)
		socklen_t numNewAddr = sizeof(SOCKADDR);
#else
#error "Undefined platform information!"
#endif
		memset(&bufNewAddr, 0, numNewAddr);

		//accept new conection
		clsNewSock = accept(m_clsSocket, &bufNewAddr, &numNewAddr);
		if (INVALID_SOCKET != clsNewSock)
		{
			//translate the address
			GetAddrText(&bufNewAddr, ptrFamily, pszAddr, numLen, ptrPort);

			//check if socket can be processed further
			if (NULL != ptrSocket)
			{
				//is the arg socket busy?
				if (INVALID_SOCKET != ptrSocket->m_clsSocket)
				{
					//close new connection if it cannot be stored
					closesocket(clsNewSock);
					return FALSE;
				}

				//pass back the descriptor and family information
				ptrSocket->m_clsSocket = clsNewSock;
				ptrSocket->m_flgFamily = (AddressFamily)bufNewAddr.sa_family;
				ptrSocket->m_flgProtocol = m_flgProtocol;	//the same protocol type
			}
			else
			{
				//close new connection if it cannot be stored
				closesocket(clsNewSock);
			}

			//success
			return TRUE;
		}
	}
	//cannot accept the connection
	return FALSE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID CSocket::ClearSockInfo(VOID)
{
	m_flgFamily = AddressFamilies::ADDR_UNSPEC;
	m_flgProtocol = ProtocolTypes::PROTO_UNSPEC;
	m_clsSocket = INVALID_SOCKET;
}

//---------------------------------------------------------------------------

BOOL CSocket::GetAddrData(AddressFamily flgFamily,
	LPCTSTR pszAddr, int numPort, SOCKADDR* ptrAddr)
{
	if ((NULL != pszAddr) && (NULL != ptrAddr))
	{
		//clear the sockaddr
		memset(ptrAddr, 0, sizeof(SOCKADDR));
		ptrAddr->sa_family = AF_UNSPEC;
		
		//convert port number to a string
		TCHAR bufPort[SOCKET_PORT_BUFSIZE + 1];
		memset(bufPort, 0, sizeof(bufPort));

#if defined(WINDOWS)
		_sntprintf_s(bufPort, SOCKET_PORT_BUFSIZE, "%d", numPort);
#elif defined(LINUX)
		snprintf(bufPort, SOCKET_PORT_BUFSIZE, "%d", numPort);
#else
#error "Undefined platform information!"
#endif
		
		//prepare hints
		ADDRINFOT bufHints;
		memset(&bufHints, 0, sizeof(bufHints));
		bufHints.ai_family = flgFamily;
		
		//get the address
		PADDRINFOT ptrResult = NULL;
		if (!GetAddrInfo(pszAddr, bufPort, &bufHints, &ptrResult))
		{
			if (NULL != ptrResult)
			{
				//copy the first available address
				memcpy(ptrAddr, ptrResult->ai_addr, sizeof(SOCKADDR));
				
				//free the memory allocated be the GetAddrInfo
				FreeAddrInfo(ptrResult);
			}
			
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSocket::GetAddrText(SOCKADDR* ptrAddr, 
	AddressFamily* ptrFamily, LPTSTR pszAddr, size_t numLen, int* ptrPort)
{
	//reset the result
	if (NULL != pszAddr) memset(pszAddr, 0, numLen * sizeof(TCHAR));
	if (NULL != ptrFamily) *ptrFamily = AddressFamilies::ADDR_UNSPEC;
	if (NULL != ptrPort) *ptrPort = 0;
	
	//check if address info is available
	if (NULL != ptrAddr)
	{
		//port number string
		TCHAR bufPort[SOCKET_PORT_BUFSIZE + 1];
		memset(bufPort, 0, sizeof(bufPort));
		
		//update buffer size if necessary
		if (NULL == pszAddr) numLen = 0;
		
		//get string representation of address and port
#if defined(WINDOWS)
		if (!GetNameInfo(ptrAddr, 
			sizeof(SOCKADDR), pszAddr, static_cast<DWORD>(numLen), 
			bufPort, static_cast<DWORD>(SOCKET_PORT_BUFSIZE), NI_NUMERICHOST | NI_NUMERICSERV))
#elif defined(LINUX)
		if (!GetNameInfo(ptrAddr,
			sizeof(SOCKADDR), pszAddr, static_cast<socklen_t>(numLen),
			bufPort, static_cast<socklen_t>(SOCKET_PORT_BUFSIZE), NI_NUMERICHOST | NI_NUMERICSERV))
#else
#error "Undefined platform information!"
#endif
		{
			//update address family
			if (NULL != ptrFamily)
			{
				*ptrFamily = (AddressFamily)ptrAddr->sa_family;
			}
			
			//get port info if requierd
			if (NULL != ptrPort)
			{
				*ptrPort = _ttoi(bufPort);
			}
			
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------
