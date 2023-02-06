#include "Application.h"
#include "SocketEventArgs.h"
#include "Debug.hpp"
#include "DSC_IProgrammingDataContainer.hpp"
#include "DSC_IBuzzerDataContainer.hpp"
#include "DSC_IKeyPressedDataContainer.hpp"
#include "DSC_ILCDCursorDataContainer.hpp"
#include "DSC_ILCDUpdateDataContainer.hpp"
#include "DSC_ILEDStatusDataContainer.hpp"
#include "DSC_ITextString.hpp"
#include "DSC_IAssignmentList.hpp"
#include "DSC_ICommandOutputDataContainer.hpp"
#include "DSC_IEventBufferEntryDataContainer.hpp"
#include "DSC_ITroubleList.hpp"
#include "DSC_IAccessCode.hpp"
#include "DSC_IAccessCodeAttributes.hpp"
#include "DSC_IRepository.hpp"
#include "DSC_IPartition.hpp"
#include "DSC_IZone.hpp"
#include "DSC_IZoneAttributes.hpp"
#include "UtfConverter.hpp"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

#if defined(WINDOWS)
#include <conio.h>
#elif defined(LINUX)
#include <unistd.h>
#include <cstdio>
#include "LinuxIO.h"
#define Sleep(a) usleep(a * 1000)
#else
#error "Undefined platform information!"
#endif

//---------------------------------------------------------------------------

VOID CApplication::OnUdpActivateEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs)
{
	PrintfLogMessage("CApplication::OnUdpActivateEvent", "%p\n", ptrSender);

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
	//DEBUG_ASSERT(NULL != ptrArgs);
}

//---------------------------------------------------------------------------

VOID CApplication::OnUdpShutdownEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs)
{
	PrintfLogMessage("CApplication::OnUdpShutdownEvent", "%p\n", ptrSender);

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
	DEBUG_ASSERT(NULL != ptrArgs);

	//close all UDP sessions and channels
	BEGIN_CRITICAL_SECTION(m_objUDPSessionsLock);

		//process all sessions
		while (0 < m_lstUDPSessions.Count())
		{
			//get the session
			CSessionData const& session = m_lstUDPSessions.GetAt(0);

			//prepare for closing the channel
			TComPtr<DSC_IChannel> channel = session.get_IChannel();
			if (FALSE == channel.IsNull())	//channel exists?
			{
				//close the channel (it should remove the session)
				if (IS_FAILURE(channel->CloseChannel()))
				{
					PrintfLogMessage("CApplication::OnUdpShutdownEvent", 
						"%p: Cannot close the channel %p!\n", 
						ptrSender, static_cast<DSC_IChannel*>(channel));
				}
			}
			else
			{
				//missing channel
				PrintfLogMessage("CApplication::OnUdpShutdownEvent", 
					"%p: There is no channel associated with the session!\n", ptrSender);

				//remove the session
				m_lstUDPSessions.RemoveAt(0);
			}
		}

	END_CRITICAL_SECTION();
}

//---------------------------------------------------------------------------

VOID CApplication::OnUdpMainLoopEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs)
{
	//PrintfLogMessage("[CApplication::OnUdpMainLoopEvent]\n");

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);

	//pulse all UDP channels
	BEGIN_CRITICAL_SECTION(m_objUDPSessionsLock);

		//process all sessions
		for (size_t i = m_lstUDPSessions.Count(); 0 < i; --i)
		{
			//get the sessions one by one
			CSessionData const& session = m_lstUDPSessions.GetAt(i - 1);

			//process session timeouts
			if (FALSE != ProcSessionTimeout(const_cast<CSessionData&>(session)))
			{
				//the session has timed out
				PrintfLogMessage("CApplication::OnUdpMainLoopEvent",
					"%p: The session has timed out!\n", ptrSender);

				//prepare for closing the channel
				TComPtr<DSC_IChannel> channel = session.get_IChannel();
				if (FALSE == channel.IsNull())
				{
					//close the channel (it should remove the session)
					if (IS_FAILURE(channel->CloseChannel()))
					{
						PrintfLogMessage("CApplication::OnUdpMainLoopEvent",
							"%p: Cannot close the channel %p!\n", 
							ptrSender, static_cast<DSC_IChannel*>(channel));
					}
				}
				else
				{
					//missing channel
					PrintfLogMessage("CApplication::OnUdpMainLoopEvent",
						"%p: There is no channel associated with the session!\n", ptrSender);

					//remove the session
					m_lstUDPSessions.RemoveAt(i - 1);
				}
			}
		}

	END_CRITICAL_SECTION();

	//pulse security base
	ProcessInternalStates();
}

//---------------------------------------------------------------------------

//VOID CApplication::OnUdpReadIdleEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs)
//{
//	PrintfLogMessage("[CApplication::OnUdpReadIdleEvent]\n");
//
//	//sanity check
//	DEBUG_ASSERT(NULL != ptrSender);
//
//}

//---------------------------------------------------------------------------

//VOID CApplication::OnUdpSendIdleEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs)
//{
//	PrintfLogMessage("[CApplication::OnUdpSendIdleEvent]\n");
//
//	//sanity check
//	DEBUG_ASSERT(NULL != ptrSender);
//
//}

//---------------------------------------------------------------------------

VOID CApplication::OnUdpReceivedEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs)
{
//	PrintfLogMessage("[CApplication::OnUdpReceivedEvent]\n");

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
	DEBUG_ASSERT(NULL != ptrArgs);

	//create session key
	CSessionKey key(SessionTypes::UDP, ptrArgs->m_clsRemoteAddress);

	//get channel
	TComPtr<DSC_IChannel> channel;
	BEGIN_CRITICAL_SECTION(m_objUDPSessionsLock);
	
		//find session
		CSessionData* session = FindSessionData(m_lstUDPSessions, key);
		if (NULL != session)
		{
			//get channel
			channel = session->get_IChannel();
			if (FALSE == channel.IsNull())
			{
				//reset the idle timeout
				session->SetIdleTime(APP_UDP_IDLE_TIMEOUT);
			}
			else
			{
				//failure
				PrintfLogMessage("CApplication::OnUdpReceivedEvent",
					"%p: Failed to get the channel!\n", ptrSender);

				//remove this session so it can be replaced
				m_lstUDPSessions.Remove(key);
			}
		}

		//check if the channel is missing and create new session if needed
		if (FALSE != channel.IsNull())	//channel missing?
		{
			//create new session
			CSessionData data;
			data.set_PeerAddr(ptrArgs->m_clsRemoteAddress);
			data.set_UDPPoint(ptrSender);
			data.SetSysTicks(APP_SYSTEM_PULSE);
			data.SetIdleTime(APP_UDP_IDLE_TIMEOUT);

			//create new channel
			if (IS_SUCCESS(m_ptrInteractive->CreateChannel(DSC_ProtocolTypes::ITV2, channel)))
			{
				PrintfLogMessage("CApplication::OnUdpReceivedEvent",
					"%p: New channel %p has been created!\n", 
					ptrSender, static_cast<DSC_IChannel*>(channel));

				//setup properties
				if (FALSE != SetChannelProperties(channel, APP_UDP_CONNECTION, key))
				{
					PrintfLogMessage("CApplication::OnUdpReceivedEvent",
						"%p: New channel %p properties have been set!\n", 
						ptrSender, static_cast<DSC_IChannel*>(channel));

					//store channel
					data.set_IChannel(channel);

					//add session to the list
					CSessionData* session = m_lstUDPSessions.Add(key, data);
					if (NULL != session)
					{
						//connect channel events
						ConnectChannelEvents(channel);

						PrintfLogMessage("CApplication::OnUdpReceivedEvent",
							"%p: New session has been added to the list!\n", ptrSender);
					}
					else
					{
						PrintfLogMessage("CApplication::OnUdpReceivedEvent",
							"%p: Failed to add new session info to the list!\n", ptrSender);

						//free the session key object (the channel events haven't been 
						//hooked up yet so the key has to be freed here)
						if (FALSE == SetSessionKey(channel, NULL))
						{
							PrintfLogMessage("CApplication::OnUdpReceivedEvent",
								"%p: Failed to clear the session key tag!\n", ptrSender);
						}

						//close the channel
						if (IS_FAILURE(channel->CloseChannel()))
						{
							PrintfLogMessage("CApplication::OnUdpReceivedEvent",
								"%p: Cannot close the channel!\n", ptrSender);
						}

						//clear the channel
						channel.Clear();
					}
				}
				else
				{
					//cannot set the channel properties
					PrintfLogMessage("CApplication::OnUdpReceivedEvent",
						"%p: Failed to set the channel's properties!\n", ptrSender);

					//clear the channel
					channel.Clear();
				}
			}
			else
			{
				//failed to create the UDP channel
				PrintfLogMessage("CApplication::OnUdpReceivedEvent",
					"%p: Failed to create the channel!\n", ptrSender);
			}
		}

	END_CRITICAL_SECTION();

	//write data to channel
	if (FALSE == WriteDataToChannel(channel, 
		ptrArgs->m_bufDataBuffer, ptrArgs->m_bufDataBuffer.Count()))
	{
		//failure to write data
		PrintfLogMessage("CApplication::OnUdpReceivedEvent",
			"%p: Failed to write data to the channel %p!\n", 
			ptrSender, static_cast<DSC_IChannel*>(channel));
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID CApplication::OnTcpActivateEvent(CTCPServer* ptrSender, CSocketEventArgs const* ptrArgs)
{
	PrintfLogMessage("CApplication::OnTcpActivateEvent", "%p\n", ptrSender);

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
}

//---------------------------------------------------------------------------

VOID CApplication::OnTcpShutdownEvent(CTCPServer* ptrSender, CSocketEventArgs const* ptrArgs)
{
	PrintfLogMessage("CApplication::OnTcpShutdownEvent", "%p\n", ptrSender);

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
}

//---------------------------------------------------------------------------

VOID CApplication::OnTcpMainLoopEvent(CTCPServer* ptrSender, CSocketEventArgs const* ptrArgs)
{
	//PrintfLogMessage("[CApplication::OnTcpMainLoopEvent]\n");

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);

	//pulse security base
	ProcessInternalStates();
}

//---------------------------------------------------------------------------

VOID CApplication::OnTcpConnectionOpenEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent", "%p\n", ptrSender);

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
	DEBUG_ASSERT(NULL != ptrArgs);

	//create session key
	CSessionKey key(SessionTypes::TCP, ptrArgs->m_clsRemoteAddress);

	//get channel
	TComPtr<DSC_IChannel> channel;
	BEGIN_CRITICAL_SECTION(m_objTCPSessionsLock);
	
		//find existing session
		CSessionData* session = FindSessionData(m_lstTCPSessions, key);
		if (NULL != session)
		{
			//get channel
			channel = session->get_IChannel();
			if (FALSE == channel.IsNull())
			{
				//replace the existing proxy (the connection could have been
				//forcefully disconnected - the old proxy object is no longer
				//valid and should be shut down)
				CTCPProxy* tcp = session->set_TCPProxy(ptrSender);
				if (NULL != tcp)
				{
					PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent",
						"%p: Shut down the obsolete connection %p!\n", ptrSender, tcp);

					//shut down the obsolete proxy
					m_clsTcpServer.ShutProxy(tcp);
				}

				//reset the idle timeout
				session->SetIdleTime(APP_TCP_IDLE_TIMEOUT);
			}
			else
			{
				//failure
				PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent",
					"%p: Failed to get the channel!\n", ptrSender);

				//remove this session so it can be replaced
				m_lstTCPSessions.Remove(key);
			}
		}

		//check if the channel is missing and create new session if needed
		if (FALSE != channel.IsNull())	//channel missing?
		{
			//create new session
			CSessionData data;
			data.set_PeerAddr(ptrArgs->m_clsRemoteAddress);
			data.set_TCPProxy(ptrSender);
			data.SetSysTicks(APP_SYSTEM_PULSE);
			data.SetIdleTime(APP_TCP_IDLE_TIMEOUT);

			//create new channel
			if (IS_SUCCESS(m_ptrInteractive->CreateChannel(DSC_ProtocolTypes::ITV2, channel)))
			{
				PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent",
					"%p: New channel %p has been created!\n", 
					ptrSender, static_cast<DSC_IChannel*>(channel));

				//setup properties
				if (FALSE != SetChannelProperties(channel, APP_TCP_CONNECTION, key))
				{
					PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent",
						"%p: New channel's properties have been set!\n", ptrSender);

					//store channel
					data.set_IChannel(channel);

					//add session to the list
					CSessionData* session = m_lstTCPSessions.Add(key, data);
					if (NULL != session)
					{
						//connect channel events
						ConnectChannelEvents(channel);

						PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent",
							"%p: New session has been added to the list!\n", ptrSender);
					}
					else
					{
						PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent",
							"%p: Failed to add new session info to the list!\n", ptrSender);

						//free the session key object (the channel events haven't been 
						//hooked up yet so the key has to be freed here)
						if (FALSE == SetSessionKey(channel, NULL))
						{
							PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent",
								"%p: Failed to clear the session key tag!\n", ptrSender);
						}

						//close the channel
						if (IS_FAILURE(channel->CloseChannel()))
						{
							PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent",
								"%p: Cannot close the channel %p!\n", 
								ptrSender, static_cast<DSC_IChannel*>(channel));
						}

						//clear the channel
						channel.Clear();
					}
				}
				else
				{
					//cannot set the channel properties
					PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent",
						"%p: Failed to set the channel's properties!\n", ptrSender);

					//clear the channel
					channel.Clear();
				}
			}
			else
			{
				//failed to create the TCP channel
				PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent",
					"%p: Failed to create the channel!\n", ptrSender);
			}
		}

	END_CRITICAL_SECTION();

	//channel missing?
	if (FALSE != channel.IsNull())
	{
		//failed to create/update session - shutdown the proxy asynchronously
		PrintfLogMessage("CApplication::OnTcpConnectionOpenEvent", "%p: Failure!\n", ptrSender);
		try { ptrSender->Shutdown(0); } catch (...) {}
	}
}

//---------------------------------------------------------------------------

VOID CApplication::OnTcpConnectionClosedEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	PrintfLogMessage("CApplication::OnTcpConnectionClosedEvent",  "%p\n", ptrSender);

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
	DEBUG_ASSERT(NULL != ptrArgs);

	//create session key
	CSessionKey key(SessionTypes::TCP, ptrArgs->m_clsRemoteAddress);

	//delete session
	BEGIN_CRITICAL_SECTION(m_objTCPSessionsLock);
	
		//find session
		CSessionData* session = FindSessionData(m_lstTCPSessions, key);
		if (NULL != session)
		{
			//validate session to make sure this proxy belongs to 
			//the current session and is not an obsolete object
			CTCPProxy* tcp = session->get_TCPProxy();
			if (ptrSender == tcp)
			{
				//clear the TCP proxy info because it is closing
				session->set_TCPProxy(NULL);

				//prepare for closing the channel
				TComPtr<DSC_IChannel> channel = session->get_IChannel();
				if (FALSE == channel.IsNull())
				{
					//close the channel (it should remove the session as well)
					if (IS_FAILURE(channel->CloseChannel()))
					{
						PrintfLogMessage("CApplication::OnTcpConnectionClosedEvent",
							"%p: Cannot close the channel %p!\n", 
							ptrSender, static_cast<DSC_IChannel*>(channel));
					}
				}
				else
				{
					//missing channel
					PrintfLogMessage("CApplication::OnTcpConnectionClosedEvent",
						"%p: There is no channel associated with the session!\n", ptrSender);

					//remove the session
					m_lstTCPSessions.Remove(key);
				}
			}
		}

	END_CRITICAL_SECTION();
}

//---------------------------------------------------------------------------

VOID CApplication::OnTcpConnectionThreadEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	//PrintfLogMessage("[CApplication::OnTcpConnectionThreadEvent]\n");

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);

	//create session key
	CSessionKey key(SessionTypes::TCP, ptrArgs->m_clsRemoteAddress);

	//process session
	BEGIN_CRITICAL_SECTION(m_objTCPSessionsLock);
	
		//find session
		CSessionData* session = FindSessionData(m_lstTCPSessions, key);
		if (NULL != session)
		{
			//process session timeouts
			if (FALSE != ProcSessionTimeout(*session))
			{
				//the session has timed out
				PrintfLogMessage("CApplication::OnTcpConnectionThreadEvent",
					"%p: The session has timed out!\n", ptrSender);

				//prepare for closing the channel
				TComPtr<DSC_IChannel> channel = session->get_IChannel();
				if (FALSE == channel.IsNull())
				{
					//close the channel
					if (IS_FAILURE(channel->CloseChannel()))
					{
						PrintfLogMessage("CApplication::OnTcpConnectionThreadEvent",
							"%p: Cannot close the channel %p!\n", 
							ptrSender, static_cast<DSC_IChannel*>(channel));
					}
				}
				else
				{
					//missing channel
					PrintfLogMessage("CApplication::OnTcpConnectionThreadEvent",
						"%p: There is no channel associated with the session!\n", ptrSender);

					//remove the session
					m_lstTCPSessions.Remove(key);
				}
			}
		}

	END_CRITICAL_SECTION();
}

//---------------------------------------------------------------------------

VOID CApplication::OnTcpConnectionRxIdleEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	PrintfLogMessage("CApplication::OnTcpConnectionRxIdleEvent", "%p\n", ptrSender);

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
}

//---------------------------------------------------------------------------

VOID CApplication::OnTcpConnectionTxIdleEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	PrintfLogMessage("CApplication::OnTcpConnectionTxIdleEvent", "%p\n", ptrSender);

	//BYTE test = 0; //1 element array
	//int sent = ptrSender->Send(&test, 0, 5);

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
}

//---------------------------------------------------------------------------

VOID CApplication::OnTcpConnectionRxDataEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs)
{
	//PrintfLogMessage("[CApplication::OnTcpConnectionRxDataEvent]\n");

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
	DEBUG_ASSERT(NULL != ptrArgs);

	//create session key
	CSessionKey key(SessionTypes::TCP, ptrArgs->m_clsRemoteAddress);

	//get channel
	TComPtr<DSC_IChannel> channel;
	BEGIN_CRITICAL_SECTION(m_objTCPSessionsLock);
	
		//find session
		CSessionData* session = FindSessionData(m_lstTCPSessions, key);
		if (NULL != session)
		{
			//get the channel
			channel = session->get_IChannel();
			if (FALSE != channel.IsNull())
			{
				PrintfLogMessage("CApplication::OnTcpConnectionRxDataEvent",
					"%p: Missing required channel!\n", ptrSender);
			}

			//reset the idle timeout
			session->SetIdleTime(APP_TCP_IDLE_TIMEOUT);
		}
		else
		{
			PrintfLogMessage("CApplication::OnTcpConnectionRxDataEvent",
				"%p: Missing required session info!\n", ptrSender);
		}

	END_CRITICAL_SECTION();

	//write data to channel
	if (FALSE == WriteDataToChannel(channel, 
		ptrArgs->m_bufDataBuffer, ptrArgs->m_bufDataBuffer.Count()))
	{
		//failure to write data
		PrintfLogMessage("CApplication::OnTcpConnectionRxDataEvent",
			"%p: Failed to write data to channel %p!\n", 
			ptrSender, static_cast<DSC_IChannel*>(channel));
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID CApplication::OnEventNotificationEvent(DSC_IChannel* ptrSender, 
		char const* pszText, DSC_ChannelEvent flgEvent)
{
	PrintfLogMessage("CApplication::OnEventNotificationEvent", "%p\n", ptrSender);

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
	DEBUG_ASSERT(NULL != pszText);

	try
	{
		//get the id
		string id = string(pszText);

		//check the event code
		if ((DSC_ChannelEvents::ChannelClosing == flgEvent) ||
			(DSC_ChannelEvents::ChannelDeleted == flgEvent))
		{
			//disconnect channel events
			DisconnectChannelEvents(ptrSender);

			//get sesion key
			CSessionKey* key = GetSessionKey(ptrSender);
			if (NULL == key)
			{
				PrintfLogMessage("CApplication::OnEventNotificationEvent",
					"%p: Cannot delete the session because the session key is missing!\n", ptrSender);
				return;
			}

			//check session type
			SessionType type = key->GetSessionType();
			if (SessionTypes::UDP == type)
			{
				BEGIN_CRITICAL_SECTION(m_objUDPSessionsLock);

					//look for session
					CSessionData* session = FindSessionData(m_lstUDPSessions, *key);
					if (NULL != session)
					{
						//remove the session but do not shut down the UDP!
						CUDPPoint* udp = session->get_UDPPoint();
						if (NULL != udp)
						{
							//clear the session comms info before shutdown
							session->set_UDPPoint(NULL);	//clear point
							//try { udp->Shutdown(0); } catch (...) {}	//shut down asynchronously
						}

						//remove the session from the list
						m_lstUDPSessions.Remove(*key);
					}

				END_CRITICAL_SECTION();
			}
			else if (SessionTypes::TCP == type)
			{
				BEGIN_CRITICAL_SECTION(m_objTCPSessionsLock);

					//look for session
					CSessionData* session = FindSessionData(m_lstTCPSessions, *key);
					if (NULL != session)
					{
						//init the connection shutdown if needed
						CTCPProxy* tcp = session->set_TCPProxy(NULL);
						if (NULL != tcp)
						{
							//clear the session comms info before shutdown
							m_clsTcpServer.ShutProxy(tcp);
						}

						//remove the session from the list
						m_lstTCPSessions.Remove(*key);
					}

				END_CRITICAL_SECTION();
			}
			else
			{
				PrintfLogMessage("CApplication::OnEventNotificationEvent",
					"%p: Unknown session type!\n", ptrSender);
			}

			//delete the key object that was held by the channel
			if (FALSE == SetSessionKey(ptrSender, NULL))
			{
				DEBUG_ASSERT(FALSE);
			}
		}
		else if (DSC_ChannelEvents::PeerIdentified == flgEvent)
		{
			//find the security base to link to
			BEGIN_CRITICAL_SECTION(m_objSecurityBasesLock)
				int index = m_lstSecurityBases.IndexOf(id);
				if (0 <= index)
				{
					//link the channel
					TComPtr<DSC_ISecurityBase> security = m_lstSecurityBases.GetAt(index);
					if (FALSE == security.IsNull())
					{
						//link
						if (IS_SUCCESS(security->add_Channel(ptrSender)))
						{
							//done
							return;
						}
					}
				}
			END_CRITICAL_SECTION()

			//failure
			PrintfLogMessage("CApplication::OnEventNotificationEvent",
				"%p: Security base \"%s\" not found!\n", ptrSender, pszText);
		}
		else if (DSC_ChannelEvents::ChannelRxIdle == flgEvent)
		{
			PrintfLogMessage("CApplication::OnEventNotificationEvent",
				"%p: The \"%s\" channel's RX is idle!\n", ptrSender, id.c_str());
		}
		else if (DSC_ChannelEvents::ChannelTxIdle == flgEvent)
		{
			PrintfLogMessage("CApplication::OnEventNotificationEvent",
				"%p: The \"%s\" channel's TX  is idle!\n", ptrSender, id.c_str());
		}
	}
	catch (...) 
	{
		//error(s) are no good
		DEBUG_CHECK(FALSE);
		RELEASE_CHECK(FALSE);
	}
}

//---------------------------------------------------------------------------

VOID CApplication::OnErrorNotificationEvent(DSC_IChannel* ptrSender, 
	char const* pszText, DSC_ChannelEvent flgEvent, DSC_ChannelError numError)
{
	PrintfLogMessage("CApplication::OnChannelFailureEvent",
		"%p: Event: \"%d\", Error: \"%d\"\n", ptrSender, flgEvent, numError);

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
	DEBUG_ASSERT(NULL != pszText);

	try
	{
	}
	catch (...) 
	{
		//error(s) are no good
		DEBUG_CHECK(FALSE);
		RELEASE_CHECK(FALSE);
	}
}

//---------------------------------------------------------------------------

VOID CApplication::OnStateNotificationEvent(DSC_IChannel* ptrSender, 
	char const* pszText, DSC_ChannelEvent flgEvent, DSC_CHANNEL_STATE_FLAGS flgStateFlags)
{
	PrintfLogMessage("CApplication::OnChannelUpatedEvent",
		"%p: Event: \"%d\", State: \"0x%08x\"\n", ptrSender, flgEvent, flgStateFlags);

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
	DEBUG_ASSERT(NULL != pszText);

	try
	{
	}
	catch (...) 
	{
		//error(s) are no good
		DEBUG_CHECK(FALSE);
		RELEASE_CHECK(FALSE);
	}
}

//---------------------------------------------------------------------------

VOID CApplication::OnSendDataPacketEvent(DSC_IChannel* ptrSender, 
		char const* pszText, DSC_ChannelEvent flgEvent, 
		BYTE const* bufData, size_t numSize)
{
	//PrintfLogMessage("[CApplication::OnSendDataPacketEvent]\n");

	//sanity check
	DEBUG_ASSERT(NULL != ptrSender);
	DEBUG_ASSERT(NULL != pszText);
	DEBUG_ASSERT(NULL != bufData);

	try
	{
		//get sesion key
		CSessionKey* key = GetSessionKey(ptrSender);
		if (NULL == key)
		{
			PrintfLogMessage("CApplication::OnSendDataPacketEvent",
				"%p: Cannot send the data packet because the session key is missing!\n", ptrSender);
			return;
		}

		//check session type
		SessionType type = key->GetSessionType();
		if (SessionTypes::UDP == type)
		{
			BEGIN_CRITICAL_SECTION(m_objUDPSessionsLock);

				//look for session
				CSessionData* session = FindSessionData(m_lstUDPSessions, *key);
				if (NULL != session)
				{
					//send data using the udp connector
					CUDPPoint* udp = session->get_UDPPoint();
					if (NULL != udp)
					{
						int sent = udp->SendTo(session->get_PeerAddr(), bufData, numSize, APP_SEND_TIMEOUT);
						if (static_cast<size_t>(sent) != numSize)
						{
							PrintfLogMessage("CApplication::OnSendDataPacketEvent",
								"%p: Failed to send all UDP data!\n", ptrSender);
						}
					}
					else
					{
						PrintfLogMessage("CApplication::OnSendDataPacketEvent",
							"%p: Missing UDP connection point!\n", ptrSender);
					}
				}
				else
				{
					PrintfLogMessage("CApplication::OnSendDataPacketEvent",
						"%p: Failed to find UDP session!\n", ptrSender);
				}

			END_CRITICAL_SECTION();
		}
		else if (SessionTypes::TCP == type)
		{
			BEGIN_CRITICAL_SECTION(m_objTCPSessionsLock);

				//look for session
				CSessionData* session = FindSessionData(m_lstTCPSessions, *key);
				if (NULL != session)
				{
					//send data using the tcp connector
					CTCPProxy* tcp = session->get_TCPProxy();
					if (NULL != tcp)
					{
						int sent = tcp->Send(bufData, numSize, APP_SEND_TIMEOUT);
						if (static_cast<size_t>(sent) != numSize)
						{
							PrintfLogMessage("CApplication::OnSendDataPacketEvent",
								"%p: Failed to send all TCP data!\n", ptrSender);
						}
					}
					else
					{
						PrintfLogMessage("CApplication::OnSendDataPacketEvent",
							"%p: Missing TCP connection proxy!\n", ptrSender);
					}
				}
				else
				{
					PrintfLogMessage("CApplication::OnSendDataPacketEvent",
						"%p: Failed to find TCP session!\n", ptrSender);
				}

			END_CRITICAL_SECTION();
		}
		else
		{
			PrintfLogMessage("CApplication::OnSendDataPacketEvent",
				"%p: Unknown session type!\n", ptrSender);
		}
	}
	catch (...) 
	{
		//error(s) are no good
		DEBUG_CHECK(FALSE);
		RELEASE_CHECK(FALSE);
	}
}

//---------------------------------------------------------------------------

VOID CApplication::OnGeneralNotificationEvent(DSC_ISecurityBase* ptrSender, 
	DSC_SecurityEventCategory flgEventCategory, DSC_SecurityEventType flgEventType,
	DSC_DataContainer flgDataContainer, DSC_IComponent* ptrDataContainer)
{
	//process the security general notification
	PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
		"%p: Category: \"%d\", Type: \"%d\", Container: \"%d\"\n", 
		ptrSender, flgEventCategory, flgEventType, flgDataContainer);

	//sanity check
	if ((DSC_DataContainers::Unknown == flgDataContainer) || (NULL == ptrDataContainer))
	{
		return;
	}

	switch(flgEventCategory)
	{
		case DSC_SecurityEventCategories::Programming:
			{
				switch (flgEventType)
				{
					case DSC_SecurityEventTypes::Programming:
						{
							if (DSC_DataContainers::ProgrammingInformation == flgDataContainer)
							{
								PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
									"Programming Notification:\n");

								TComPtr<DSC_IProgrammingDataContainer> container;
								if (IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IProgrammingDataContainer, container)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_ProgrammingSource source;
								if(IS_FAILURE(container->get_ProgrammingSource(&source)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_ProgrammingMode mode;
								if(IS_FAILURE(container->get_ProgrammingMode(&mode)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_ProgrammingState state;
								if(IS_FAILURE(container->get_ProgrammingState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
									"Source = %d Mode = %d State = %d\n", source, mode, state);
							}
						}
						break;
					default:
						{
							PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
								"Unknown Event Type = %d\n", flgEventType);
						}
						break;
				}
			}
			break;
		case DSC_SecurityEventCategories::SystemState:
			{
				switch (flgEventType)
				{
					case DSC_SecurityEventTypes::BuzzerType:
						{
							if (DSC_DataContainers::BuzzerInformation == flgDataContainer)
							{
								PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
									"Buzzer Notification:\n");

								TComPtr<DSC_IBuzzerDataContainer> container;
								if (IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IBuzzerDataContainer, container)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_SYSTEM_INDEX partition;
								if(IS_FAILURE(container->get_Partition(&partition)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_PartitionBuzzerState state;
								if(IS_FAILURE(container->get_BuzzerState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								UINT32 duration;
								if(IS_FAILURE(container->get_Duration(&duration)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
									"Partition = %d State = %d Duration = %d\n", partition, state, duration);
							}
						}
						break;
					case DSC_SecurityEventTypes::TimeDate:
						{
							if(DSC_DataContainers::TextString == flgDataContainer)
							{
								PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
									"TimeDate Notification:\n");

								TComPtr<DSC_ITextString> container;
								if(IS_FAILURE(ptrDataContainer->Query(NAME_DSC_ITextString, container)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								char const* text;
								if(IS_FAILURE(container->get_String(&text)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								PrintfLogMessage("CApplication::OnGeneralNotificationEvent", 
									"DateTime = %s\n", text);
							}
						}
						break;
					case DSC_SecurityEventTypes::Assignment:
						{
							if(DSC_DataContainers::AssignmentList == flgDataContainer)
							{
								PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
									"Assignment Notification:\n");

								TComPtr<DSC_IAssignmentList> container;
								if(IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IAssignmentList, container)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_SIZE_T count;
								if(IS_FAILURE(container->get_NumberOfAssignments(&count)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								bool flg_done = false; 
								for(DSC_SIZE_T i = 0; i < count; ++i)
								{
									TComPtr<DSC_IAssignmentData> assignment;
									if(IS_FAILURE(container->get_AssignmentData(i, assignment)))
									{
										DEBUG_ASSERT(FALSE);
										continue;
									}

									DSC_AssignmentType type;
									if(IS_FAILURE(assignment->get_Type(&type)))
									{
										DEBUG_ASSERT(FALSE);
										continue;
									}

									switch(type)
									{
										case DSC_AssignmentTypes::Partition:
											{
												if(false == flg_done)
												{
													PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
														"Partition(s) Assignment Update\n");
													flg_done = true;
												}

												DSC_SYSTEM_INDEX partition;
												if(IS_FAILURE(assignment->get_PartitionNumber(&partition)))
												{
													DEBUG_ASSERT(FALSE);
													continue;
												}

												DSC_AssignmentState state;
												if(IS_FAILURE(assignment->get_State(&state)))
												{
													DEBUG_ASSERT(FALSE);
													continue;
												}

												PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
													"Partition %d %s %s System\n", partition, 
													((DSC_AssignmentStates::Assigned == state) ? "Assigned" : "UnAssigned"),
													((DSC_AssignmentStates::Assigned == state) ? "To" : "From"));
											}
											break;
										case DSC_AssignmentTypes::VirtualZone_Zone:
											{
												if(false == flg_done)
												{
													PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
														"VirtualZone(s) Assignment Update\n");
													flg_done = true;
												}

												DSC_SYSTEM_INDEX virtual_zone;
												if(IS_FAILURE(assignment->get_VirtualZoneNumber(&virtual_zone)))
												{
													DEBUG_ASSERT(FALSE);
													continue;
												}

												DSC_AssignmentState state;
												if(IS_FAILURE(assignment->get_State(&state)))
												{
													DEBUG_ASSERT(FALSE);
													continue;
												}

												DSC_SYSTEM_INDEX zone;
												if(IS_FAILURE(assignment->get_ZoneNumber(&zone)))
												{
													DEBUG_ASSERT(FALSE);
													continue;
												}

												PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
													"VirtualZone %d %s %s Zone %d\n", virtual_zone, 
													((DSC_AssignmentStates::Assigned == state) ? "Assigned" : "UnAssigned"),
													((DSC_AssignmentStates::Assigned == state) ? "To" : "From"),
													zone);
											}
											break;
										case DSC_AssignmentTypes::Zone_Partition:
											{
												if(false == flg_done)
												{
													PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
														"Zone(s) Assignment Update\n");
													flg_done = true;
												}

												DSC_SYSTEM_INDEX zone;
												if(IS_FAILURE(assignment->get_ZoneNumber(&zone)))
												{
													DEBUG_ASSERT(FALSE);
													continue;
												}

												DSC_AssignmentState state;
												if(IS_FAILURE(assignment->get_State(&state)))
												{
													DEBUG_ASSERT(FALSE);
													continue;
												}

												DSC_SYSTEM_INDEX partition;
												if(IS_FAILURE(assignment->get_PartitionNumber(&partition)))
												{
													DEBUG_ASSERT(FALSE);
													continue;
												}

												PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
													"Zone = %d %s %s Partition %d\n", zone, 
													((DSC_AssignmentStates::Assigned == state) ? "Assigned" : "UnAssigned"),
													((DSC_AssignmentStates::Assigned == state) ? "To" : "From"),
													partition);
											}
											break;
										default:
											{
												PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
													"Unknown Assignment Type = %d\n", type);
											}
											break;
									}
								}
							}
						}
						break;
					default:
						{
							PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
								"Unknown Event Type = %d\n", flgEventType);
						}
						break;
				}
			}
			break;
		case DSC_SecurityEventCategories::CommandOutput:
			{
				switch(flgEventType)
				{
					case DSC_SecurityEventTypes::CommandOutputUpdate:
						{
							if(DSC_DataContainers::CommandOutput == flgDataContainer)
							{
								PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
									"CommandOutput Notification:\n");

								TComPtr<DSC_ICommandOutputDataContainer> container;
								if(IS_FAILURE(ptrDataContainer->Query(NAME_DSC_ICommandOutputDataContainer, container)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_SYSTEM_INDEX output_number;
								if(IS_FAILURE(container->get_CommandOutputNumber(&output_number)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_CommandOutputReportingState state;
								if(IS_FAILURE(container->get_CommandOutputState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								TComPtr<DSC_ISystemIndices> partitions;
								if(IS_FAILURE(container->get_CommandOutputPartitions(partitions)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_SIZE_T count;
								if(IS_FAILURE(partitions->get_Size(&count)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								for(DSC_SIZE_T i = 0; i < count; ++i)
								{
									DSC_SYSTEM_INDEX index;
									if(IS_FAILURE(partitions->get_Index(i, &index)))
									{
										DEBUG_ASSERT(FALSE);
										continue;
									}
									PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
										"Partition %d CommandOutput %d State = %d\n", index, output_number, state);
								}
							}
						}
						break;
					default:
						{
							PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
								"Unknown Event Type = %d\n", flgEventType);
						}
						break;
				}
			}
			break;
		case DSC_SecurityEventCategories::EventBuffer:
			{
				switch (flgEventType)
				{
					case DSC_SecurityEventTypes::EventBufferUpdate:
						{
							if(DSC_DataContainers::EventBufferEntry == flgDataContainer)
							{
								PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
									"EventBuffer Notification:\n");

								TComPtr<DSC_IEventBufferEntryDataContainer> container;
								if(IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IEventBufferEntryDataContainer, container)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_SYSTEM_INDEX partition_number;
								if(IS_FAILURE(container->get_Partition(&partition_number)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								BYTE type;
								if(IS_FAILURE(container->get_EventType(&type)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								UINT16 code;
								if(IS_FAILURE(container->get_EventCode(&code)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
									"Partition %d EventType = %02X EventCode = %02X\n", partition_number, type, code);
							}
						}
						break;
					default:
						{
							PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
								"Unknown Event Type = %d\n", flgEventType);
						}
						break;
				}
			}
			break;
		case DSC_SecurityEventCategories::DeviceModule:
			{
				switch (flgEventType)
				{
					case DSC_SecurityEventTypes::Trouble:
						{
							if(DSC_DataContainers::TroubleList == flgDataContainer)
							{
								PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
									"Device/Module Trouble Notification:\n");

								TComPtr<DSC_ITroubleList> container;
								if(IS_FAILURE(ptrDataContainer->Query(NAME_DSC_ITroubleList, container)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_SIZE_T count;
								if(IS_FAILURE(container->get_NumberOfTroubles(&count)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								for(DSC_SIZE_T i = 0; i < count; ++i)
								{
									TComPtr<DSC_ITroubleData> trouble;
									if(IS_FAILURE(container->get_TroubleData(i, trouble)))
									{
										DEBUG_ASSERT(FALSE);
										continue;
									}

									DSC_DeviceModuleType device_type;
									if(IS_FAILURE(trouble->get_DeviceModuleType(&device_type)))
									{
										DEBUG_ASSERT(FALSE);
										continue;
									}

									DSC_TroubleType trouble_type;
									if(IS_FAILURE(trouble->get_TroubleType(&trouble_type)))
									{
										DEBUG_ASSERT(FALSE);
										continue;
									}

									DSC_SYSTEM_INDEX device_number;
									if(IS_FAILURE(trouble->get_DeviceModuleNumber(&device_number)))
									{
										DEBUG_ASSERT(FALSE);
										continue;
									}

									DSC_TroubleState state;
									if(IS_FAILURE(trouble->get_TroubleStatus(&state)))
									{
										DEBUG_ASSERT(FALSE);
										continue;
									}

									PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
										"DeviceType = %d DeviceNumber = %d TroubleType = %d TroubleState = %d\n", 
										device_type, device_number, trouble_type, state);
								}
							}

						}
						break;
					default:
						{
							PrintfLogMessage("CApplication::OnGeneralNotificationEvent",
								"Unknown Event Type = %d\n", flgEventType);
						}
						break;
				}
			}
			break;
		case DSC_SecurityEventCategories::VirtualKeypad:
			{
			}
			break;
		default:
			{
			}
			break;
	}
}

//---------------------------------------------------------------------------

VOID CApplication::OnDataUpdateNotificationEvent(DSC_ISecurityBase* ptrSender, 
	DSC_DataContainer flgDataContainer, DSC_IComponent* ptrDataContainer, 
	DSC_SecurityDataSelector const* tblDataSelectors, size_t numDataSelectors,
	DSC_DataContainer flgAuxDataContainer, DSC_IComponent* ptrAuxDataContainer)
{
	//process the security data update notification
	PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
		"Data Update Notification - Container: \"%d\", Number Of Selectors: \"%d\", AuxContainer: \"%d\"\n", 
		flgDataContainer, numDataSelectors, flgAuxDataContainer);

	//sanity check
	if ((DSC_DataContainers::Unknown == flgDataContainer) ||
		(NULL == ptrDataContainer) || (NULL == tblDataSelectors) || (0 == numDataSelectors))
	{
		//nothing to process
		return;	//done
	}

	//show the updates info
	switch (flgDataContainer)
	{
		case DSC_DataContainers::AccessCode:
			{
				PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
					"AccessCode Notification:\n");

				TComPtr<DSC_IAccessCode> container;
				if(IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IAccessCode, container)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				DSC_SYSTEM_INDEX index;
				if(IS_FAILURE(container->get_SystemIndex(&index)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				for(size_t i = 0; i < numDataSelectors; ++i)
				{
					switch(tblDataSelectors[i])
					{
						case DSC_SecurityDataSelectors::SystemIndex:
							{
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"System Index = %d\n", index);
							}
							break;
						case DSC_SecurityDataSelectors::Label:
							{
								TComPtr<DSC_ITextString> label;
								if(IS_FAILURE(container->get_Label(label)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								char const* text;
								if(IS_FAILURE(label->get_String(&text)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"AccessCode %d Label = %s\n", index, text);
							}
							break;
						case DSC_SecurityDataSelectors::Value:
							{
								TComPtr<DSC_ITextString> value;
								if(IS_FAILURE(container->get_Label(value)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								char const* text;
								if(IS_FAILURE(value->get_String(&text)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"AccessCode %d Value = %s\n", index, text);
							}
							break;
						case DSC_SecurityDataSelectors::Length:
							{
								DSC_SIZE_T length;
								if(IS_FAILURE(container->get_AccessCodeLength(&length)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"AccessCode %d Length = %d\n", index, length);
							}
							break;
						default:
							{
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Unknown Security Data Selector %d\n", tblDataSelectors[i]);
							}
							break;
					}
				}
			}
			break;
		case DSC_DataContainers::AccessCodeAttributes:
			{
				PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
					"AccessCodeAttributes Notification:\n");

				TComPtr<DSC_IAccessCodeAttributes> container;
				if(IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IAccessCodeAttributes, container)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				DSC_SYSTEM_INDEX index;
				if(IS_FAILURE(container->get_SystemIndex(&index)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				// example of how to get access code to get its system index
				// NOTE: technically don't need to do all this, since the system index 
				//       from AccessCodeAttribues is the system index of the owner 
				//       AccessCode
				TComPtr<DSC_IRepository> repository;
				if(IS_FAILURE(ptrSender->get_Repository(repository)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				TComPtr<DSC_IAccessCode> access_code;
				if(IS_FAILURE(repository->GetAccessCodeBySystemIndex(index, access_code)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				DSC_SYSTEM_INDEX access_code_index;
				if(IS_FAILURE(access_code->get_SystemIndex(&access_code_index)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				//NOTE: TComPtr will automatically cleanup the interface reference counts when it goes out of scope
				//      but to do it manually you call Clear() on the TComPtr
				access_code.Clear();
				repository.Clear();

				for(size_t i = 0; i < numDataSelectors; ++i)
				{
					switch(tblDataSelectors[i])
					{
						case DSC_SecurityDataSelectors::Attributes:
							{
							}
							break;
						case DSC_SecurityDataSelectors::AccessCode_BellSquawk:
							{
								DSC_AccessCodeAttributesBellSquawkState state;
								if(IS_FAILURE(container->get_BellSquawk(&state)))
								{
									DEBUG_ASSERT(FALSE);
									continue;
								}

								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"AccessCode %d Bell Squawk = %d\n", access_code_index, state);
							}
							break;
						case DSC_SecurityDataSelectors::AccessCode_CanBypassZone:
							{
								DSC_AccessCodeAttributesCanBypassZoneState state;
								if(IS_FAILURE(container->get_CanBypassZone(&state)))
								{
									DEBUG_ASSERT(FALSE);
									continue;
								}

								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"AccessCode %d Can Bypass Zone = %d\n", access_code_index, state);
							}
							break;
						case DSC_SecurityDataSelectors::AccessCode_DuressCode:
							{
								DSC_AccessCodeAttributesDuressCodeState state;
								if(IS_FAILURE(container->get_DuressCode(&state)))
								{
									DEBUG_ASSERT(FALSE);
									continue;
								}

								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"AccessCode %d Duress Code = %d\n", access_code_index, state);
							}
							break;
						case DSC_SecurityDataSelectors::AccessCode_OneTimeUse:
							{
								DSC_AccessCodeAttributesOneTimeUseState state;
								if(IS_FAILURE(container->get_OneTimeUse(&state)))
								{
									DEBUG_ASSERT(FALSE);
									continue;
								}

								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"AccessCode %d One Time Use = %d\n", access_code_index, state);
							}
							break;
						case DSC_SecurityDataSelectors::AccessCode_RemoteAccessEnabled:
							{
								DSC_AccessCodeAttributesRemoteAccessState state;
								if(IS_FAILURE(container->get_RemoteAccessEnabled(&state)))
								{
									DEBUG_ASSERT(FALSE);
									continue;
								}

								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"AccessCode %d Remote Access = %d\n", access_code_index, state);
							}
							break;
						case DSC_SecurityDataSelectors::AccessCode_Supervisor:
							{
								DSC_AccessCodeAttributesSupervisorState state;
								if(IS_FAILURE(container->get_Supervisor(&state)))
								{
									DEBUG_ASSERT(FALSE);
									continue;
								}

								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"AccessCode %d Supervisor = %d\n", access_code_index, state);
							}
							break;
						default:
							{
								PrintfLogMessage(
									"CApplication::OnDataUpdateNotificationEvent","Unknown Security Data Selector %d\n", tblDataSelectors[i]);
							}
							break;
					}
				}
			}
			break;
		case DSC_DataContainers::Partition:
			{
				PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
					"Partition Notification:\n");

				TComPtr<DSC_IPartition> container;
				if (IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IPartition, container)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				DSC_SYSTEM_INDEX index;
				if (IS_FAILURE(container->get_SystemIndex(&index)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				TComPtr<DSC_IPartitionStateData> state_data;
				if(IS_FAILURE(container->get_PartitionStateData(state_data)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				for (size_t i = 0; i < numDataSelectors; ++i)
				{
					switch (tblDataSelectors[i])
					{
						case DSC_SecurityDataSelectors::SystemIndex:
							{
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"System Index = %d\n", index);
							}
							break;
						case DSC_SecurityDataSelectors::Label:
							{
								TComPtr<DSC_ITextString> label;
								if (IS_FAILURE(container->get_Label(label)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								char const* text;
								if (IS_FAILURE(label->get_String(&text)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Label = %s\n", index, text);
							}
							break;
						case DSC_SecurityDataSelectors::PartitionArmingLevelStatus:
                            {
								DSC_PartitionArmedState state;
								if(IS_FAILURE(state_data->get_PartitionArmedState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								if (DSC_PartitionArmedStates::UserArmed != state)
								{
									PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
										"Partition %d Arming Level Status = %d\n", index, state);
								}
								else
								{
									TComPtr<DSC_ITextString> auxContainer;
									if (IS_FAILURE(ptrAuxDataContainer->Query(NAME_DSC_ITextString, auxContainer)))
									{
										DEBUG_ASSERT(FALSE);
										break;
									}

									char const* text;
									if (IS_FAILURE(auxContainer->get_String(&text)))
									{
										DEBUG_ASSERT(FALSE);
										break;
									}
									PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
										"Partition %d Arming Level Status = %d By User %s\n", index, state, text);
								}
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionEntryDelayStatus:
                            {
								DSC_PartitionEntryDelayState state;
								if(IS_FAILURE(state_data->get_PartitionEntryDelayState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Entry Delay Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionExitDelayStatus:
                            {
								DSC_PartitionExitDelayState state;
								if(IS_FAILURE(state_data->get_PartitionExitDelayState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Exit Delay Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionBusyStatus:
                            {
								DSC_PartitionBusyState state;
								if(IS_FAILURE(state_data->get_PartitionBusyState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Busy Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionBypassStatus:
                            {
								DSC_PartitionBypassState state;
								if(IS_FAILURE(state_data->get_PartitionBypassState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Bypass Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionBlankStatus:
                            {
								DSC_PartitionBlankState state;
								if(IS_FAILURE(state_data->get_PartitionBlankState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Blank Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionTroubleStatus:
                            {
								DSC_PartitionTroubleState state;
								if(IS_FAILURE(state_data->get_PartitionTroubleState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Trouble Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionAlarmInMemoryStatus:
                            {
								DSC_PartitionAlarmMemoryState state;
								if(IS_FAILURE(state_data->get_PartitionAlarmMemoryState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Alarm In Memory Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionAudibleBellStatus:
                            {
								DSC_PartitionAudibleBellState state;
								if(IS_FAILURE(state_data->get_PartitionAudibleBellState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Audible Bell Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionAudibleBellType:
                            {
								DSC_PartitionAudibleBellType type;
								if(IS_FAILURE(state_data->get_PartitionAudibleBellType(&type)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Audible Bell Type = %d\n", index, type);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionQuickExitStatus:
                            {
								DSC_PartitionQuickExitState state;
								if(IS_FAILURE(state_data->get_PartitionQuickExitState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Quick Exit Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionReadyStatus:
                            {
								DSC_PartitionReadyState state;
								if(IS_FAILURE(state_data->get_PartitionReadyState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Ready Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionBuzzerStatus:
                            {
								DSC_PartitionBuzzerState state;
								if(IS_FAILURE(state_data->get_PartitionBuzzerState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Buzzer Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionAlarmStatus:
                            {
								DSC_PartitionAlarmState state;
								if(IS_FAILURE(state_data->get_PartitionAlarmState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Alarm Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::PartitionDoorChimeStatus:
                            {
								DSC_DoorChimeEnabledState state;
								if(IS_FAILURE(container->get_DoorChimeEnabledState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Partition %d Door Chime Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::AlarmTypes:
							{
								TComPtr<DSC_IAlarmTypeContainer> alarms;
								if (IS_FAILURE(container->get_AlarmTypes(alarms)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_SIZE_T count;
								if (IS_FAILURE(alarms->get_NumberOfAlarmTypes(&count)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								for (DSC_SIZE_T i = 0; i < count; ++i)
								{
									DSC_AlarmType type;
									if (IS_FAILURE(alarms->get_AlarmType(i, &type)))
									{
										DEBUG_ASSERT(FALSE);
										continue;
									}
									PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
										"Partition %d AlarmType = %d\n", index, type);
								}
							}
							break;
						default:
							{
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Unknown Security Data Selector %d\n", tblDataSelectors[i]);
							}
							break;
					}
				}
			}
			break;
		case DSC_DataContainers::Zone:
			{
				PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
					"Zone Notification:\n");

				TComPtr<DSC_IZone> container;
				if (IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IZone, container)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				DSC_SYSTEM_INDEX index;
				if (IS_FAILURE(container->get_SystemIndex(&index)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				for (size_t i = 0; i < numDataSelectors; ++i)
				{
					switch (tblDataSelectors[i])
					{
						case DSC_SecurityDataSelectors::SystemIndex:
							{
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"System Index = %d\n", index);
							}
							break;
						case DSC_SecurityDataSelectors::Label:
							{
								TComPtr<DSC_ITextString> label;
								if (IS_FAILURE(container->get_Label(label)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								char const* text;
								if (IS_FAILURE(label->get_String(&text)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Label = %s\n", index, text);
							}
							break;
						case DSC_SecurityDataSelectors::OpenClose:
                            {
								DSC_ZoneOpenCloseState state;
								if(IS_FAILURE(container->get_OpenCloseState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Open/Close Status = %d\n", index, state);
                            }
                            break;
                        case DSC_SecurityDataSelectors::Bypass:
                            {
								DSC_ZoneBypassState state;
								if(IS_FAILURE(container->get_BypassState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Bypass Status = %d\n", index, state);
                            }
                            break;
                        case DSC_SecurityDataSelectors::AlarmInMemory:
                            {
								DSC_ZoneAlarmInMemoryState state;
								if(IS_FAILURE(container->get_AlarmInMemoryState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Alarm In Memory Status = %d\n", index, state);
                            }
                            break;
                        case DSC_SecurityDataSelectors::Alarm:
                            {
								DSC_ZoneAlarmState state;
								if(IS_FAILURE(container->get_AlarmState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Alarm Status = %d\n", index, state);
                            }
                            break;
                        case DSC_SecurityDataSelectors::Delinquency:
                            {
								DSC_ZoneDelinquencyState state;
								if(IS_FAILURE(container->get_DelinquencyState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Delinquency Status = %d\n", index, state);
                            }
                            break;
                        case DSC_SecurityDataSelectors::LowBattery:
                            {
								DSC_ZoneLowBatteryState state;
								if(IS_FAILURE(container->get_LowBatteryState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Low Battery Status = %d\n", index, state);
                            }
                            break;
                        case DSC_SecurityDataSelectors::Fault:
                            {
								DSC_ZoneFaultState state;
								if(IS_FAILURE(container->get_FaultState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Fault Status = %d\n", index, state);
                            }
                            break;
                        case DSC_SecurityDataSelectors::Tamper:
                            {
								DSC_ZoneTamperState state;
								if(IS_FAILURE(container->get_TamperState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Tamper Status = %d\n", index, state);
                            }
                            break;
                        case DSC_SecurityDataSelectors::LowSensitivity:
                            {
								DSC_ZoneLowSensitivityState state;
								if(IS_FAILURE(container->get_LowSensitivityState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Low Sensitivity Status = %d\n", index, state);
                            }
                            break;
                        case DSC_SecurityDataSelectors::Masked:
                            {
								DSC_ZoneMaskedState state;
								if(IS_FAILURE(container->get_MaskedState(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Masked Status = %d\n", index, state);
                            }
                            break;
						case DSC_SecurityDataSelectors::AlarmTypes:
							{
								DSC_SYSTEM_INDEX partition_index = DSC_INVALID_SYSTEM_INDEX;
								if(DSC_DataContainers::Partition == flgAuxDataContainer)
								{
									TComPtr<DSC_IPartition> partition;
									if(IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IPartition, partition)))
									{
										DEBUG_ASSERT(FALSE);
									}
									else
									{
										if(IS_FAILURE(partition->get_SystemIndex(&partition_index)))
										{
											DEBUG_ASSERT(FALSE);
										}
									}
								}

								TComPtr<DSC_IAlarmTypeContainer> alarms;
								if(IS_FAILURE(container->get_AlarmTypes(alarms)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_SIZE_T count;
								if(IS_FAILURE(alarms->get_NumberOfAlarmTypes(&count)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								for(DSC_SIZE_T i = 0; i < count; ++i)
								{
									DSC_AlarmType type;
									if(IS_FAILURE(alarms->get_AlarmType(i, &type)))
									{
										DEBUG_ASSERT(FALSE);
										continue;
									}
									PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
										"Partition %d Zone %d AlarmType = %d\n", partition_index, index, type);
								}
							}
							break;
						default:
							{
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Unknown Security Data Selector %d\n", tblDataSelectors[i]);
							}
							break;
					}
				}
			}
			break;
		case DSC_DataContainers::ZoneAttributes:
			{
				PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
					"ZoneAttributes Notification:\n");

				TComPtr<DSC_IZoneAttributes> container;
				if(IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IZoneAttributes, container)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				DSC_SYSTEM_INDEX index;
				if(IS_FAILURE(container->get_SystemIndex(&index)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				// example of how to get zone to get its system index
				// NOTE: technically don't need to do all this, since the system index 
				//       from ZoneAttributes is the system index of the owner 
				//       Zone
				TComPtr<DSC_IRepository> repository;
				if(IS_FAILURE(ptrSender->get_Repository(repository)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				TComPtr<DSC_IZone> zone;
				if(IS_FAILURE(repository->GetZoneBySystemIndex(index, zone)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				DSC_SYSTEM_INDEX zone_index;
				if(IS_FAILURE(zone->get_SystemIndex(&zone_index)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}
				//NOTE: TComPtr will automatically cleanup the interface reference counts when it goes out of scope
				//      but to do it manually you call Clear() on the TComPtr
				zone.Clear();
				repository.Clear();

				for(size_t i = 0; i < numDataSelectors; ++i)
				{
					switch(tblDataSelectors[i])
					{
						case DSC_SecurityDataSelectors::Attributes:
							{
							}
							break;
						case DSC_SecurityDataSelectors::Zone_BypassEnable:
							{
								DSC_ZoneAttributesBypassEnableState state;
								if(IS_FAILURE(container->get_BypassEnable(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Bypass Enable Status = %d\n", zone_index, state);
							}
							break;
						case DSC_SecurityDataSelectors::Zone_ChimeFunction:
							{
								DSC_ZoneAttributesChimeFunctionState state;
								if(IS_FAILURE(container->get_ChimeFunction(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Zone %d Chime Function Status = %d\n", zone_index, state);
							}
							break;
						default:
							{
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Unknown Security Data Selector %d\n", tblDataSelectors[i]);
							}
							break;
					}
				}
			}
			break;
		case DSC_DataContainers::VirtualZone:
			{
				PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
					"VirtualZone Notification:\n");

				TComPtr<DSC_IVirtualZone> container;
				if (IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IVirtualZone, container)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				DSC_SYSTEM_INDEX index;
				if (IS_FAILURE(container->get_SystemIndex(&index)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				for (size_t i = 0; i < numDataSelectors; ++i)
				{
					switch (tblDataSelectors[i])
					{
						case DSC_SecurityDataSelectors::SystemIndex:
							{
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"System Index: %d\n", index);
							}
							break;
						case DSC_SecurityDataSelectors::ZoneNumber:
							{
								DSC_SYSTEM_INDEX zone_number;
								if (IS_FAILURE(container->get_ZoneNumber(&zone_number)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"VirtualZone %d ZoneNumber = %d\n", index, zone_number);
							}
							break;
						default:
							{
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Unknown Security Data Selector %d\n", tblDataSelectors[i]);
							}
							break;
					}
				}
			}
			break;
		case DSC_DataContainers::VirtualZoneStatus:
			{
				PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
					"VirtualZoneStatus Notification:\n");

				TComPtr<DSC_IVirtualZoneStatus> container;
				if (IS_FAILURE(ptrDataContainer->Query(NAME_DSC_IVirtualZoneStatus, container)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				DSC_SYSTEM_INDEX index;
				if(IS_FAILURE(container->get_SystemIndex(&index)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				// example of how to get virtualzone to get its system index
				// NOTE: technically don't need to do all this, since the system index 
				//       from VirtualZoneAttributes is the system index of the owner 
				//       VirtualZone
				TComPtr<DSC_IRepository> repository;
				if(IS_FAILURE(ptrSender->get_Repository(repository)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				TComPtr<DSC_IVirtualZone> virtual_zone;
				if(IS_FAILURE(repository->GetVirtualZoneBySystemIndex(index, virtual_zone)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				DSC_SYSTEM_INDEX virtual_zone_index;
				if(IS_FAILURE(virtual_zone->get_SystemIndex(&virtual_zone_index)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}
				//NOTE: TComPtr will automatically cleanup the interface reference counts when it goes out of scope
				//      but to do it manually you call Clear() on the TComPtr
				virtual_zone.Clear();
				repository.Clear();

				for(size_t i = 0; i < numDataSelectors; ++i)
				{
					switch(tblDataSelectors[i])
					{
						case DSC_SecurityDataSelectors::VirtualZoneStatus:
							{
							}
							break;
						case DSC_SecurityDataSelectors::VirtualZone_ACTrouble:
							{
								DSC_VirtualZoneStatusACTroubleState state;
								if(IS_FAILURE(container->get_ACTrouble(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"VirtualZone %d AC Trouble Status = %d\n", virtual_zone_index, state);
							}
							break;
						case DSC_SecurityDataSelectors::VirtualZone_Fault:
							{
								DSC_VirtualZoneStatusFaultState state;
								if(IS_FAILURE(container->get_Fault(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"VirtualZone %d Fault Status = %d\n", virtual_zone_index, state);
							}
							break;
						case DSC_SecurityDataSelectors::VirtualZone_LowBattery:
							{
								DSC_VirtualZoneStatusLowBatteryState state;
								if(IS_FAILURE(container->get_LowBattery(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"VirtualZone %d Low Battery Status = %d\n", virtual_zone_index, state);
							}
							break;
						case DSC_SecurityDataSelectors::VirtualZone_Masked:
							{
								DSC_VirtualZoneStatusMaskedState state;
								if(IS_FAILURE(container->get_Masked(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"VirtualZone %d Masked Status = %d\n", virtual_zone_index, state);
							}
							break;
						case DSC_SecurityDataSelectors::VirtualZone_Open:
							{
								DSC_VirtualZoneStatusOpenState state;
								if(IS_FAILURE(container->get_Open(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"VirtualZone %d Open Status = %d\n", virtual_zone_index, state);
							}
							break;
						case DSC_SecurityDataSelectors::VirtualZone_Tamper:
							{
								DSC_VirtualZoneStatusTamperState state;
								if(IS_FAILURE(container->get_Tamper(&state)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"VirtualZone %d Tamper Status = %d\n", virtual_zone_index, state);
							}
							break;
						default:
							{
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Unknown Security Data Selector %d\n", tblDataSelectors[i]);
							}
							break;
					}
				}
			}
			break;
		case DSC_DataContainers::SystemManager:
			{
				PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
					"SystemManager Notification:\n");

				TComPtr<DSC_ISystemManager> container;
				if (IS_FAILURE(ptrDataContainer->Query(NAME_DSC_ISystemManager, container)))
				{
					DEBUG_ASSERT(FALSE);
					break;
				}

				for(size_t i = 0; i < numDataSelectors; ++i)
				{
					switch(tblDataSelectors[i])
					{
						case DSC_SecurityDataSelectors::SystemManager_TroublePresent:
							{
								BOOL trouble;  
								if(IS_FAILURE(container->get_TroublePresent(&trouble)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"SystemManager Trouble Present = %d\n", trouble);
							}
							break;
						case DSC_SecurityDataSelectors::AlarmTypes:
							{
								TComPtr<DSC_IAlarmTypeContainer> alarms;
								if (IS_FAILURE(container->get_AlarmTypes(alarms)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								DSC_SIZE_T count;
								if (IS_FAILURE(alarms->get_NumberOfAlarmTypes(&count)))
								{
									DEBUG_ASSERT(FALSE);
									break;
								}

								for (DSC_SIZE_T i = 0; i < count; ++i)
								{
									DSC_AlarmType type;
									if (IS_FAILURE(alarms->get_AlarmType(i, &type)))
									{
										DEBUG_ASSERT(FALSE);
										continue;
									}
									PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
										"SystemManager AlarmType = %d\n", type);
								}
							}
							break;
						default:
							{
								PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
									"Unknown Security Data Selector %d\n", tblDataSelectors[i]);
							}
							break;
					}
				}
			}
			break;
		default:
			{
				PrintfLogMessage("CApplication::OnDataUpdateNotificationEvent",
					"Unknown Data Container %d\n", flgDataContainer);
			}
			break;
	}
}

//---------------------------------------------------------------------------
