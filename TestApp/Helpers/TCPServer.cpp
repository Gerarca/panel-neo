//	TCPServer.cpp
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "TCPServer.h"
#include <ctime>

#if defined(WINDOWS)
#include <process.h>
#elif defined(LINUX)
#else
#error "Undefined platform information!"
#endif

using namespace std;

//---------------------------------------------------------------------------

//disable some well-understood warnings
#if defined(MS_VS_COMPILER)
#pragma warning(push)
#pragma warning(disable: 4355)
#elif defined(GCC_COMPILER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------

CTCPServer::CTCPServer(AddressFamily flgFamily) : m_flgFamily(flgFamily),
	OnConnectionOpenEventHandler(this, &CTCPServer::OnConnectionOpenEvent),
	OnConnectionClosedEventHandler(this, &CTCPServer::OnConnectionClosedEvent),
	OnConnectionThreadEventHandler(this, &CTCPServer::OnConnectionThreadEvent),
	OnConnectionRxIdleEventHandler(this, &CTCPServer::OnConnectionRxIdleEvent),
	OnConnectionTxIdleEventHandler(this, &CTCPServer::OnConnectionTxIdleEvent),
	OnConnectionRxDataEventHandler(this, &CTCPServer::OnConnectionRxDataEvent)
{
	DEBUG_PRINTF("[CTCPServer::CTCPServer] %p\n", this);
}

//---------------------------------------------------------------------------

CTCPServer::~CTCPServer(VOID)
{
	DEBUG_PRINTF("[CTCPServer::~CTCPServer] %p\n", this);

	//make sure to shutdown the thread first or 
	//otherwise bad things will happen!
	Shutdown();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BOOL CTCPServer::Activate(LPCTSTR pszAddr, int numPort)
{
	//sanity check
	CSocket* psocket = CTcpUdpBase::GetSocket();
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
			goto Activate_Failure;
		}
	
		//try binding new socket
		if (FALSE == psocket->Bind(pszAddr, numPort))
		{
			//cannot bind
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

	//make sure the server is shutdown
	CTcpUdpBase::Shutdown(THREAD_STOP_COUNT);
	return FALSE;
}

//---------------------------------------------------------------------------

VOID CTCPServer::Shutdown(VOID)
{
	//try to shutdown the server thread
	while (FALSE == CTcpUdpBase::Shutdown(THREAD_STOP_COUNT))
	{
		//wait until all proxies shut down, etc.
		Platform::THREAD_SLEEP(THREAD_STOP_SLEEP);
	}
}

//---------------------------------------------------------------------------

VOID CTCPServer::Broadcast(BYTE bufData[], size_t numSize, size_t numTimeout)
{
	//send the data to all the clients
	CLock lock = m_objClientsLock;
	size_t count = m_lstClients.Count();
	for (size_t i = 0; i < count; ++i)
	{
		//do casting magic to get the proxy pointer without 
		//removing it from the list of clients
		TMemPtr<CTCPProxy> const* client = m_lstClients.GetAt(i);
		CTCPProxy* proxy = *const_cast<TMemPtr<CTCPProxy>*>(client);
		if (NULL != proxy)
		{
			proxy->Send(bufData, numSize, numTimeout);	//send data
		}
	}
}

//---------------------------------------------------------------------------

VOID CTCPServer::ShutProxy(CTCPProxy* ptrProxy)
{
	//find the proxy on the list
	CLock lock = m_objClientsLock;
	int index = m_lstClients.IndexOf(ptrProxy);
	if (0 <= index)	//is proxy still present?
	{
		//shutdown the proxy asynchronously
		try { ptrProxy->Shutdown(0); } catch (...) {}
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID CTCPServer::OnConnectionOpenEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	//fire event
	try { ConnectionOpenEvent(ptrSender, ptrArgs); } catch (...) {}
}

//---------------------------------------------------------------------------

VOID CTCPServer::OnConnectionClosedEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	//fire event
	try { ConnectionClosedEvent(ptrSender, ptrArgs); } catch (...) {}

	//post-processing
	if (NULL != ptrSender)
	{
		//disconnect events
		DisconnectEvents(ptrSender);

		//move the proxy pointer (TMemPtr's operator= does that) from the
		//clients list to the zombies list to avoid deleting the proxy here
		CLock lock = m_objClientsLock;
		m_lstZombies.Add(m_lstClients[ptrSender]);
		m_lstClients.Remove(ptrSender);	//the proxy won't be deleted now
	}
}

//---------------------------------------------------------------------------

VOID CTCPServer::OnConnectionThreadEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	//fire event
	try { ConnectionThreadEvent(ptrSender, ptrArgs); } catch (...) {}
}

//---------------------------------------------------------------------------

VOID CTCPServer::OnConnectionRxIdleEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	try { ConnectionRxIdleEvent(ptrSender, ptrArgs); } catch (...) {}
}

//---------------------------------------------------------------------------

VOID CTCPServer::OnConnectionTxIdleEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	try { ConnectionTxIdleEvent(ptrSender, ptrArgs); } catch (...) {}
}

//---------------------------------------------------------------------------

VOID CTCPServer::OnConnectionRxDataEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	try { ConnectionRxDataEvent(ptrSender, ptrArgs); } catch (...) {}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BOOL CTCPServer::ThreadStart(VOID* ptrParam)
{
    //fire event
    try { ActivateEvent(this, NULL); } catch (...) {}

	//get address info
	if (FALSE == CTcpUdpBase::GetLocalAddress(&m_clsLocalAddress))
	{
		//cannot get local address
		DEBUG_CHECK(FALSE);
		RELEASE_CHECK(FALSE);
		return FALSE;
	}

	//sanity check
	CSocket* psocket = CTcpUdpBase::GetSocket();
	if (NULL == psocket)
	{
		return FALSE;
	}

	//start listening
	return psocket->Listen();
}

//---------------------------------------------------------------------------

BOOL CTCPServer::ThreadStop(VOID* ptrParam)
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

	//shutdown and delete all active clients
	BEGIN_CRITICAL_SECTION(m_objClientsLock);
		for (size_t i = m_lstClients.Count(); 0 < i; --i)
		{
			//do casting magic to get the proxy pointer without 
			//removing it from the list of clients
			TMemPtr<CTCPProxy> const* client = m_lstClients.GetAt(i - 1);
			CTCPProxy* proxy = *const_cast<TMemPtr<CTCPProxy>*>(client);
			proxy->Shutdown(0);	//do not wait for the thread to stop
		}
	END_CRITICAL_SECTION();

	//wait for all clients to close
	time_t timeout = time(NULL) + SERVER_CLIENT_TIMEOUT;
	size_t closing = 0;
	while (0 <= difftime(timeout, time(NULL)))
	{
		//check if clients are gone
		BEGIN_CRITICAL_SECTION(m_objClientsLock);
			size_t count = m_lstClients.Count();
			if (0 == count)
			{
				//all clients are gone
				break;
			}
			else if (closing != count)
			{
				//extend the timeout as long as the clients keep closing
				closing = count;
				timeout = time(NULL) + SERVER_CLIENT_TIMEOUT;
			}
		END_CRITICAL_SECTION();

		//switch threads
		Platform::THREAD_SLEEP(THREAD_STOP_SLEEP);
	}

	//delete all zombies
	BEGIN_CRITICAL_SECTION(m_objClientsLock);
		m_lstZombies.Clear();
	END_CRITICAL_SECTION();

	//prepare event args
	CSocketEventArgs args;
	args.m_clsLocalAddress = m_clsLocalAddress;

    //fire event
    try { ShutdownEvent(this, &args); } catch (...) {}
	return TRUE;
}

//---------------------------------------------------------------------------

BOOL CTCPServer::ThreadProc(VOID* ptrParam)
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

	//check if there is any incomming connection ready
	SocketStatus status = CTcpUdpBase::Poll(SocketQueries::QUERY_ACCEPT);
	if (SocketStatuses::IS_SUCCESS == status)
	{
		//client address info
		CAddressInfo addr;

		//create new client proxy
		TMemPtr<CTCPProxy> proxy;
		if (FALSE != proxy.Create())
		{
			//setup proxy and connect events
			proxy->SetReadIdleTimeout(CTcpUdpBase::GetReadIdleTimeout());
			proxy->SetSendIdleTimeout(CTcpUdpBase::GetSendIdleTimeout());
			ConnectEvents(proxy);

			//accept new connection
			try 
			{ 
				//try accepting the socket
				if (FALSE != psocket->Accept(proxy->GetSocket(), 
					&addr.Family, addr.Address, ADDRESS_BUFFER_SIZE, &addr.Port))
				{
					//After accepting the connection, the proxy must be 
					//1) added to the list of clients, and 2) activated.
					//The order of those 2 operations matter! - If the proxy
					//was activated first, the event OnConnectionClosedEvent 
					//might fire before the proxy is added to the list - and 
					//then the already inactive proxy would have been added 
					//to the list permannently because OnConnectionClosedEvent 
					//would never fire again for such a 'zombie' proxy!
					//Moreover, any new proxy created within the same memory 
					//block (which is very likely!) couldn't be added to the 
					//list because of the same key as the 'zombie' proxy.
					//Therefore it is important to add proxy to the list first
					//and then try to activate it - to guarantee its later
					//removal from the list by the OnConnectionClosedEvent.

					//add new proxy to the list
					CLock lock = m_objClientsLock;
					TMemPtr<CTCPProxy>* added = m_lstClients.Add(proxy, proxy);
					//because the TMemPtr is used as a container for the TCPProxy,
					//the content of the variable 'proxy' is transferred over to 
					//the object in the list and the 'proxy' container is left empty

					//check if the proxy was added successfully
					if (NULL != added)
					{
						//activate new proxy (after adding to the list
						//the content of the 'proxy' object is no longer
						//valid - it has been transferred to the list)
						if (FALSE == (*added)->Activate())
						{
							//activation failed
							proxy = m_lstClients[*added];
							//transfer the content of the TMemPtr in the list
							//back to the 'proxy' to make sure the object is not
							//destroyed prematurely

							//remove the proxy container from the list
							//(it doesn't destroy the TCPProxy that was 
							//already transferred back to 'proxy')
							m_lstClients.Remove(proxy);
						}
					}
				}
			}
			catch (...) 
			{
				DEBUG_ASSERT(FALSE);
				RELEASE_CHECK(FALSE);
			}

			//disconnect events if necessary
			DisconnectEvents(proxy);
		}
		else
		{
			//get address info and reject new connection
			try { psocket->Accept(NULL, 
				&addr.Family, addr.Address, ADDRESS_BUFFER_SIZE, &addr.Port); }
			catch (...) 
			{
				DEBUG_ASSERT(FALSE);
				RELEASE_CHECK(FALSE);
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
		//delete all zombies
		CLock lock = m_objClientsLock;
		m_lstZombies.Clear();

		//switch threads
		Platform::THREAD_SLEEP(SERVER_THREAD_WAIT);
	}

	//fire event
	try { MainLoopEvent(this, &args); } catch (...) {}
	return TRUE;
}

//---------------------------------------------------------------------------

VOID CTCPServer::ConnectEvents(CTCPProxy* ptrProxy)
{
	if (NULL != ptrProxy)
	{
		ptrProxy->SetOwner(this);
		ptrProxy->ActivateEvent += &OnConnectionOpenEventHandler;
		ptrProxy->ShutdownEvent += &OnConnectionClosedEventHandler;
		ptrProxy->MainLoopEvent += &OnConnectionThreadEventHandler;
		ptrProxy->ReadIdleEvent += &OnConnectionRxIdleEventHandler;
		ptrProxy->SendIdleEvent += &OnConnectionTxIdleEventHandler;
		ptrProxy->ReceivedEvent += &OnConnectionRxDataEventHandler;
	}
}

//---------------------------------------------------------------------------

VOID CTCPServer::DisconnectEvents(CTCPProxy* ptrProxy)
{
	if (NULL != ptrProxy)
	{
		ptrProxy->ActivateEvent -= &OnConnectionOpenEventHandler;
		ptrProxy->ShutdownEvent -= &OnConnectionClosedEventHandler;
		ptrProxy->MainLoopEvent -= &OnConnectionThreadEventHandler;
		ptrProxy->ReadIdleEvent -= &OnConnectionRxIdleEventHandler;
		ptrProxy->SendIdleEvent -= &OnConnectionTxIdleEventHandler;
		ptrProxy->ReceivedEvent -= &OnConnectionRxDataEventHandler;
		ptrProxy->SetOwner(NULL);
	}
}

//---------------------------------------------------------------------------

#if defined(MS_VS_COMPILER)
#pragma warning(pop)
#elif defined(GCC_COMPILER)
#pragma GCC diagnostic pop
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------
