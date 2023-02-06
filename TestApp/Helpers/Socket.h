//	Socket.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "DSC_Config.hpp"

//---------------------------------------------------------------------------

#if defined(WINDOWS)
//prevent inclusion of winsock.h in windows.h if winsock2.h is to be used
#define _WINSOCKAPI_ 

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Winsock2.h>
#include <Ws2TcpIp.h>

#if (_WIN32_WINNT == 0x0500)
#include <tpipv6.h>
#endif
#elif defined(LINUX)
#include "DSC_Types.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <netdb.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define closesocket close
#define ioctlsocket ioctl

typedef struct sockaddr SOCKADDR;
typedef int         SOCKET;
typedef const char* LPCTSTR;
typedef char*       LPTSTR;
typedef char        TCHAR;

typedef unsigned long      DWORD;
typedef char               CHAR;
typedef unsigned short     WORD;
typedef unsigned char      BYTE;

#define GetAddrInfo  getaddrinfo
#define FreeAddrInfo freeaddrinfo
#define GetNameInfo  getnameinfo

typedef struct addrinfo  ADDRINFOT;
typedef struct addrinfo* PADDRINFOT;

#define _ttoi(a)                atoi(a)
#else
#error "Undefined platform information!"
#endif

//---------------------------------------------------------------------------

//required minimum OS version (XP SP2)
#define SOCKET_OS_MAJOR_VER		5
#define SOCKET_OS_MINOR_VER		1
#define SOCKET_OS_SP_MAJOR_VER	2
#define SOCKET_OS_SP_MINOR_VER	0

//default windows sockets library version
#define SOCKET_LIB_VERSION		0x202  

//socket constants
#define SOCKET_ADDR_BUFSIZE		46		//to hold text representation of IP/6 addresses
#define SOCKET_PORT_BUFSIZE		12		//to hold text representation of port numbers
#define SOCKET_MAX_BACKLOG		5		//maximum number of queued requests; default: 5
#define SOCKET_SEND_TIMEOUT		2000	//timout [ms] when sending data
#define SOCKET_RECV_TIMEOUT		2000	//timout [ms] when receiving data
#define SOCKET_MSEC_PER_SEC		1000
#define SOCKET_uSEC_PER_MSEC	1000

#define SOCKET_QUERY_WAIT		1		//[ms]
#define SOCKET_INVALID_VALUE	(-1)	//must be negative!

//---------------------------------------------------------------------------

namespace AddressFamilies {
enum value {
	ADDR_UNSPEC = AF_UNSPEC,
	ADDR_IP4 = AF_INET,
	ADDR_IP6 = AF_INET6
}; }
typedef DSC_ENUM_T AddressFamily;

namespace ProtocolTypes {
enum value {
	PROTO_UNSPEC = IPPROTO_MAX,	//unknown protocol
	PROTO_TCP = IPPROTO_TCP,
	PROTO_UDP = IPPROTO_UDP
}; }
typedef DSC_ENUM_T ProtocolType;

namespace SocketStatuses {
enum value {
	IS_SUCCESS,
	IS_FAILURE,
	IS_TIMEOUT
}; }
typedef DSC_ENUM_T SocketStatus;

namespace SocketQueries {
enum value {
	QUERY_SEND,
	QUERY_READ,
	QUERY_CONNECT,
	QUERY_ACCEPT,
	QUERY_ERRORS
}; }
typedef DSC_ENUM_T SocketQuery;

namespace ShutdownOptions {
enum value {
	OPT_SEND,
	OPT_READ,
	OPT_BOTH
}; }
typedef DSC_ENUM_T ShutdownOption;

//---------------------------------------------------------------------------

class CSocket
{
//private members
private:
	AddressFamily	m_flgFamily;	//address family
	ProtocolType	m_flgProtocol;	//protocol type
	SOCKET			m_clsSocket;	//socket descriptor

//constructor and destructor
public:
	CSocket(VOID);
	virtual ~CSocket(VOID);

//static methods
public:
	static BOOL Initialize(VOID);  //initialize sockets (Win crap)
	static VOID CleanupAll(VOID);  //deinitialize sockets (Win crap)

//public methods
public:
	SOCKET GetDescriptor(VOID);		//get socket descriptor
	AddressFamily GetAddressFamily(VOID);	//get address family
	ProtocolType GetProtocolType(VOID);	//get protocol type
	int GetErrorCode(VOID);			//get last thread-related error code

	BOOL Create(					//create new socket
		AddressFamily flgFamily, ProtocolType flgProto, BOOL flgUnBlock);
	BOOL Shutdown(ShutdownOption flgOption);	//shutdown the socket
	BOOL Close(VOID);				//close the socket

	BOOL SetNonBlocked(BOOL flgEnable);  //enable or disable blocking
	BOOL SetBroadcast(BOOL flgEnable);   //enable or disable broadcast
	BOOL SetExclusive(BOOL flgEnable);   //enable or disable exclusive socket use
	BOOL SetAddrReuse(BOOL flgEnable);   //enable or disable socket address reuse
	BOOL SetKeepAlive(BOOL flgEnable);   //enable or disable keep-alive feature (TCP only)
	BOOL SetNoDelay(BOOL flgEnable);     //disable or enable the Nagle algorithm (TCP only)

	BOOL SetLingerOption(                 //enable or disable linger control (TCP only)
		BOOL flgEnable, BOOL flgLinger, size_t numTimeout);

	int GetSocketError(VOID);             //get and clear socket-related error
	int GetMaxMsgSize(VOID);              //get max message size (UDP only)
	int GetPendingCount(VOID);            //get the count of bytes pending read

	BOOL Connect(LPCTSTR pszAddr, int numPort); //establish connection
	BOOL Bind(LPCTSTR pszAddr, int numPort);    //bind socket

	BOOL GetLocalHost(                      //get local host address info
		AddressFamily* ptrFamily, LPTSTR pszAddr, size_t numLen, int* ptrPort);
	BOOL GetRemoteHost(                     //get remote host address info
		AddressFamily* ptrFamily, LPTSTR pszAddr, size_t numLen, int* ptrPort);

	SocketStatus Query(SocketQuery flgQuery, size_t numTimeout);

	int Send(BYTE const* bufData, size_t numSize);	//send data
	int SendTo(AddressFamily flgFamily,			//send data to address
		LPCTSTR pszAddr, int numPort, BYTE const* bufData, size_t numSize);

	int Read(BYTE* bufData, size_t numSize);	//receive data
	int ReadFrom(BYTE* bufData, size_t numSize,//receive data from address
		AddressFamily* ptrFamily, LPTSTR pszAddr, size_t numLen, int* ptrPort);

	BOOL Listen(VOID);					//listen to incomming connections
	BOOL Accept(CSocket* ptrSocket,		//accept incomming connection
		AddressFamily* ptrFamily, LPTSTR pszAddr, size_t numLen, int* ptrPort);

//private methods
private:
	VOID ClearSockInfo(VOID);
	BOOL GetAddrData(AddressFamily flgFamily, 
	LPCTSTR pszAddr, int numPort, SOCKADDR* ptrAddr);
	BOOL GetAddrText(SOCKADDR* ptrAddr, 
		AddressFamily* ptrFamily, LPTSTR pszAddr, size_t numLen, int* ptrPort);
};

//---------------------------------------------------------------------------
#endif  //_SOCKET_H_
