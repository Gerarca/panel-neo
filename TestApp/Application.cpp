#include "Application.h"
#include "Debug.hpp"
#include "ParamParser.hpp"
#include "HexHelper.hpp"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

#if defined(WINDOWS)
#include <conio.h>
#elif defined(LINUX)
#include <unistd.h>
#include <cstdio>
#include <stdarg.h>
#include "LinuxIO.h"
#define Sleep(a) usleep(a * 1000)
#else
#error "Undefined platform information!"
#endif

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

CApplication::CApplication(VOID) : 
	m_clsDiagnosticsTime(0), m_clsStartTime(0),

	//m_clsChannelEventHandlers(this),
	m_lstUDPSessions(new CSessionKeyComparer),
	m_lstTCPSessions(new CSessionKeyComparer),

	//UDP
	OnUdpActivateHandler(this, &CApplication::OnUdpActivateEvent),
	OnUdpShutdownHandler(this, &CApplication::OnUdpShutdownEvent),
	OnUdpMainLoopHandler(this, &CApplication::OnUdpMainLoopEvent),
	//OnUdpReadIdleHandler(this, &CApplication::OnUdpReadIdleEvent),
	//OnUdpSendIdleHandler(this, &CApplication::OnUdpSendIdleEvent),
	OnUdpReceivedHandler(this, &CApplication::OnUdpReceivedEvent),

	//TCP
	OnTcpActivateHandler(this, &CApplication::OnTcpActivateEvent),
	OnTcpShutdownHandler(this, &CApplication::OnTcpShutdownEvent),
	OnTcpMainLoopHandler(this, &CApplication::OnTcpMainLoopEvent),

	OnTcpConnectionOpenHandler(this, &CApplication::OnTcpConnectionOpenEvent),
	OnTcpConnectionClosedHandler(this, &CApplication::OnTcpConnectionClosedEvent),
	OnTcpConnectionThreadHandler(this, &CApplication::OnTcpConnectionThreadEvent),
	OnTcpConnectionRxIdleHandler(this, &CApplication::OnTcpConnectionRxIdleEvent),
	OnTcpConnectionTxIdleHandler(this, &CApplication::OnTcpConnectionTxIdleEvent),
	OnTcpConnectionRxDataHandler(this, &CApplication::OnTcpConnectionRxDataEvent)

	////ITV2 Channel
	//OnChannelClosingHandler(this, &CApplication::OnChannelClosingEvent),
	//OnChannelTimeoutHandler(this, &CApplication::OnChannelTimeoutEvent),
	//OnPacketReceivedHandler(this, &CApplication::OnPacketReceivedEvent),
	//OnGeneralFailureHandler(this, &CApplication::OnGeneralFailureEvent),
	//OnSendDataPacketHandler(this, &CApplication::OnSendDataPacketEvent)
{
	PrintfLogMessage("CApplication::CApplication", "%p\n", this);

	//pre-set the default license data
	m_ptrDefaultLicense = CHexHelper::ToBytes(APP_ITV2_FEATURE_LICENSES, "", "", " ");

	//connect events
	ConnectUdpEvents(m_clsUdpListener);
	ConnectTcpEvents(m_clsTcpServer);
}

//---------------------------------------------------------------------------

CApplication::~CApplication(VOID)
{
	PrintfLogMessage("CApplication::~CApplication", "%p\n", this);

	//cleanup the event sink
	if (FALSE == m_ptrChannelEventSink.IsNull())
	{
		DSC_IChannelEventSink* sink = static_cast<DSC_IChannelEventSink*>(m_ptrChannelEventSink);
		CChannelEventHandlers* ptr = dynamic_cast<CChannelEventHandlers*>(sink);
		if (NULL != ptr)
		{
			ptr->ClearOwner();
		}
	}

	//cleanup the event sink
	if (FALSE == m_ptrSecurityEventSink.IsNull())
	{
		DSC_ISecurityEventSink* sink = static_cast<DSC_ISecurityEventSink*>(m_ptrSecurityEventSink);
		CSecurityEventHandlers* ptr = dynamic_cast<CSecurityEventHandlers*>(sink);
		if (NULL != ptr)
		{
			ptr->ClearOwner();
		}
	}
}

//---------------------------------------------------------------------------

VOID CApplication::Execute(VOID)
{
	try
	{
		//store the start time so the runtime 
		//duration can be calculated when logging
		m_clsStartTime = time(NULL);

		//create data store
		m_ptrDataStore.Store(new CDataStore, TRUE);

		//create account(s)
		m_ptrDataStore->AddAccount(
			APP_DEFAULT_ACCOUNT, APP_INTEGRATION_ID, APP_ACCESS_CODE, 
			APP_UDP_FUNCTION, APP_TCP_FUNCTION, APP_KEY_CHANGE_TIME);

		//test database
#ifndef NDEBUG
		TestDatabaseQuery();
#endif

		//create the SDK interface
		if (IS_FAILURE(CreateObject(NAME_DSC_IInteractive, m_ptrInteractive)))
		{
			PrintfLogMessage("CApplication::Execute", "The Interactive SDK couldn't be created!\n");
			goto Execute_Exit;
		}

		//get the license manager
		DEBUG_ASSERT(FALSE == m_ptrInteractive.IsNull());
		if (IS_FAILURE(m_ptrInteractive->get_LicenseManager(m_ptrLicenseManager)))
		{
			PrintfLogMessage("CApplication::Execute", "The license manager object couldn't be created!\n");
			goto Execute_Exit;
		}

		//preset the license key
		DEBUG_ASSERT(FALSE == m_ptrLicenseManager.IsNull());
		if (IS_FAILURE(m_ptrLicenseManager->set_LicenseKey(
			m_ptrDefaultLicense, static_cast<DSC_SIZE_T>(m_ptrDefaultLicense.Count()))))
		{
			PrintfLogMessage("CApplication::Execute", "Cannot pre-set the default license data!\n");
			goto Execute_Exit;
		}

		//create the diagnostics interface
		if (IS_FAILURE(m_ptrInteractive->CreateDiagnostics(m_ptrDiagnostics)))
		{
			PrintfLogMessage("CApplication::Execute", "The diagnostics object couldn't be created!\n");
			goto Execute_Exit;
		}

		//create the block cipher object
		if (IS_FAILURE(m_ptrInteractive->CreateBlockCipher(
			DSC_CipherTypes::ITV2_AES128, m_ptrBlockCipher)))
		{
			PrintfLogMessage("CApplication::Execute", "The ITV2 AES128 block cipher object couldn't be created!\n");
			goto Execute_Exit;
		}

		//create channel event sink
		m_ptrChannelEventSink.Store(new CChannelEventHandlers(this), TRUE);

		//create security event sink
		m_ptrSecurityEventSink.Store(new CSecurityEventHandlers(this), TRUE);

		//create security base (one per each account)
		TComPtr<DSC_ISecurityBase> security;
		if (IS_FAILURE(m_ptrInteractive->CreateSecurityBase(
			DSC_ProtocolTypes::ITV2, security)))
		{
			PrintfLogMessage("CApplication::Execute", "The Security Base object couldn't be created!\n");
			goto Execute_Exit;
		}
		if (FALSE != security.IsNull())
		{
			//failed to create the UDP channel
			DEBUG_PRINT("[CApplication::Execute] Failed to create the Security Base!\n");
			return;
		}

		//add the security base interface to the list
		BEGIN_CRITICAL_SECTION(m_objSecurityBasesLock)
			if (NULL == m_lstSecurityBases.Add(APP_DEFAULT_ACCOUNT, 
				TComPtr<DSC_ISecurityBase>(security.Fetch(), FALSE)))
			{
				PrintfLogMessage("CApplication::Execute", "The Security Base object couldn't be added to the list!\n");
				goto Execute_Exit;
			}
		END_CRITICAL_SECTION()

		//connect the event sink to the security base
		ConnectSecurityEvents(security);

#if defined(ENABLE_COMMAND_UNIT_TEST)
		//create temporary channel object in order 
		//to perform unit testing of commands
		TComPtr<DSC_IChannel> temp_channel;
		if (IS_FAILURE(m_ptrInteractive->CreateChannel(
			DSC_ProtocolTypes::ITV2, temp_channel)))
		{
			PrintfLogMessage("CApplication::Execute", "The Channel object couldn't be created!\n");
			goto Execute_Exit;
		}
		temp_channel.Clear();	//done
#endif	//ENABLE_COMMAND_UNIT_TEST

		//activate the UDP listener
		if (FALSE == m_clsUdpListener.Activate(APP_UDP_ADDR, APP_UDP_PORT))
		{
			PrintfLogMessage("CApplication::Execute", "The UDP listener couldn't be activated!\n");
			goto Execute_Exit;
		}
		
		//activate the TCP server
		if (FALSE == m_clsTcpServer.Activate(APP_TCP_ADDR, APP_TCP_PORT))
		{
			PrintfLogMessage("CApplication::Execute", "The TCP server couldn't be activated!\n");
			goto Execute_Exit;
		}

		ui_vars.menulevel          = APP_MAIN_MENU;
		ui_vars.previous_menulevel = ui_vars.menulevel;
		ui_vars.interactive.Store(m_ptrInteractive.Fetch(), FALSE);
		ui_vars.diagnostics.Store(m_ptrDiagnostics.Fetch(), FALSE);
		ui_vars.instance.Store(m_lstSecurityBases[APP_DEFAULT_ACCOUNT].Fetch(), FALSE);
		if (IS_FAILURE(m_ptrInteractive->CreateAccessCredentials(DSC_AccessCredentialsTypes::Numeric, ui_vars.installer_credentials)))
		{
			PrintfLogMessage("CApplication::CreateAccessCredentials", "Failed to create installer credentials!\n");
			goto Execute_Exit;
		}

		if (IS_FAILURE(ui_vars.installer_credentials->set_AccessCredentialsString("5555")))
		{
			PrintfLogMessage("CApplication::set_AccessCodeCredentialValue", "Failed to set installer credential value!\n");
			goto Execute_Exit;
		}

		if (IS_FAILURE(ui_vars.instance->set_InstallerCredentials(ui_vars.installer_credentials)))
		{
			PrintfLogMessage("CApplication::set_InstallerCredentials", "Failed to set installer credentials!\n");
			goto Execute_Exit;
		}

		if (IS_FAILURE(ui_vars.interactive->CreateAccessCredentials(DSC_AccessCredentialsTypes::Numeric, ui_vars.user_credentials)))
		{
			PrintfLogMessage("CApplication::CreateAccessCredentials", "Failed to create user credentials!\n");
			goto Execute_Exit;
		}

		if (IS_FAILURE(ui_vars.user_credentials->set_AccessCredentialsString("1234")))
		{
			PrintfLogMessage("CApplication::CreateAccessCredentials", "Failed to set user credentials!\n");
			goto Execute_Exit;
		}

		DisplayMainMenu();
		while ((FALSE != m_clsUdpListener.IsActive()) && (FALSE != m_clsTcpServer.IsActive()))
		{
			if (FALSE == doUserInterface())
			{
				break;
			}
			else if (0 >= difftime(m_clsDiagnosticsTime, time(NULL)))
			{
				//check diagnostics
				CheckDiagnostics(m_ptrDiagnostics);

				//reset the diagnostics time
				m_clsDiagnosticsTime = time(NULL) + APP_DIAGNOSTICS_TIME;
			}

			//take a nap
			Sleep(APP_LOOP_SLEEP);
		}
	}
	catch (...)
	{
		PrintfLogMessage("CApplication::Execute", "Error!\n");
	}

Execute_Exit:

	//shutdown the listener and the server
	m_clsUdpListener.Shutdown(THREAD_STOP_COUNT);
	m_clsTcpServer.Shutdown();

	//wait for the shutdown
	while ((FALSE != m_clsUdpListener.IsActive()) ||
		(FALSE != m_clsTcpServer.IsActive()))
	{
		//take a nap
		Sleep(APP_LOOP_SLEEP);
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#ifndef NDEBUG
	VOID CApplication::TestDatabaseQuery(VOID)
	{
		CParamParser parser;
		if (FALSE == parser.SetValue(QUERY_CATEGORY, QUERY_CATEGORY_ITV2))
		{
			//failure
			DEBUG_ASSERT(FALSE);
			return;
		}
		if (FALSE == parser.SetValue(QUERY_SELECTOR, QUERY_SELECTOR_ACCOUNT_INFO))
		{
			//failure
			DEBUG_ASSERT(FALSE);
			return;
		}
		if (FALSE == parser.SetValue(ITV2_PARAM_CONNECTION, APP_UDP_CONNECTION))
		{
			//failure
			DEBUG_ASSERT(FALSE);
			return;
		}
		if (FALSE == parser.SetValue(ITV2_PARAM_IDENTIFIER, APP_DEFAULT_ACCOUNT))
		{
			//failure
			DEBUG_ASSERT(FALSE);
			return;
		}
			
		//request the data
		string query = parser.Build();
		TComPtr<DSC_ITextString> text; 
		if (IS_FAILURE(m_ptrDataStore->SelectData(query.c_str(), text)))
		{
			//failure
			DEBUG_ASSERT(FALSE);
			return;
		}

		//get the c string
		char const* c_text = NULL;
		if (IS_FAILURE(text->get_String(&c_text)))
		{
			//failure
			DEBUG_ASSERT(FALSE);
			return;
		}

		//print the result
		PrintfLogMessage("CApplication::TestDatabaseQuery", "Query result: \"%s\"\n", c_text);
	}
#endif

//---------------------------------------------------------------------------

CSessionKey* CApplication::GetSessionKey(DSC_IChannel* ptrChannel) const
{
	//get the tag info
	VOID* tag = NULL;
	if (IS_SUCCESS(ptrChannel->get_Tag(&tag)))
	{
		//get sesion key
		CSessionKey* key = reinterpret_cast<CSessionKey*>(tag);
		if (NULL != key)
		{
			//return the session key
			return key;
		}
	}
	else
	{
		//call failed
		DEBUG_ASSERT(FALSE);
		RELEASE_CHECK(FALSE);
	}

	//session key missing
	PrintfLogMessage("CApplication::GetSessionKey", 
		"The session key is missing for the channel %p!\n", ptrChannel);
	return NULL;
}

//---------------------------------------------------------------------------

BOOL CApplication::SetSessionKey(DSC_IChannel* ptrChannel, CSessionKey const* ptrKey)
{
	//get the tag info
	VOID* tag = NULL;
	if (IS_SUCCESS(ptrChannel->get_Tag(&tag)))
	{
		//set the new session key
		if (IS_SUCCESS(ptrChannel->set_Tag(const_cast<CSessionKey*>(ptrKey))))
		{
			//cast the tag to the old sesion key
			CSessionKey* key = reinterpret_cast<CSessionKey*>(tag);
			if (NULL != key)	//old key present?
			{
				//delete the old session key
				delete key;
			}

			//done
			return TRUE;
		}
		else
		{
			//call failed
			DEBUG_ASSERT(FALSE);
			RELEASE_CHECK(FALSE);
		}
	}
	else
	{
		//call failed
		DEBUG_ASSERT(FALSE);
		RELEASE_CHECK(FALSE);
	}

	//failure
	PrintfLogMessage("CApplication::SetSessionKey", "Cannot set the session key!\n");
	return FALSE;
}

//---------------------------------------------------------------------------

CSessionData* CApplication::FindSessionData(
	TDictionary<CSessionKey, CSessionData> const& lstSessionData, 
	CSessionKey const& clsSessionKey)
{
	int index = lstSessionData.IndexOf(clsSessionKey);
	if (0 <= index)
	{
		//get the session data
		CSessionData const* session = lstSessionData[index];
		return const_cast<CSessionData*>(session);	//de-const the pointer
	}
	//session data not found
	return NULL;
}

//---------------------------------------------------------------------------

BOOL CApplication::ProcSessionTimeout(CSessionData& clsSession)
{
	//check session idle timeout
	if (FALSE != clsSession.TestIdleTime())
	{
		//the session has timed out
		return TRUE;
	}
	else if (FALSE != clsSession.TestSysTicks())
	{
		//reset the time
		clsSession.SetSysTicks(APP_SYSTEM_PULSE);

		//get channel
		TComPtr<DSC_IChannel> channel = clsSession.get_IChannel();
		if (FALSE == channel.IsNull())
		{
			//pulse the channel
			if (IS_FAILURE(channel->ProcessState()))
			{
				//failure
				PrintfLogMessage("CApplication::TestSessionTimeouts", "Failed to pulse the channel!\n");
			}
		}
	}
	//the session has not timed out
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CApplication::SetChannelProperties(DSC_IChannel* ptrChannel, 
	char const* pszConnInfo, CSessionKey const& clsSessionKey)
{
	DEBUG_ASSERT(NULL != ptrChannel);
	if (NULL == ptrChannel)
	{
		PrintfLogMessage("CApplication::SetChannelProperties", "Channel is missing!\n");
		return FALSE;
	}

	//set properties
	if (IS_FAILURE(ptrChannel->set_ConnectionInfo(pszConnInfo)))
	{
		PrintfLogMessage("CApplication::SetChannelProperties", "Failed to set the connection info!\n");
		return FALSE;
	}

	//setup properties
	if (IS_FAILURE(ptrChannel->set_DataStore(m_ptrDataStore)))
	{
		PrintfLogMessage("CApplication::SetChannelProperties", "Failed to set the data store reference!\n");
		return FALSE;
	}

	if (IS_FAILURE(ptrChannel->SetBlockCipher(DSC_CipherTypes::ITV2_AES128, m_ptrBlockCipher)))
	{
		PrintfLogMessage("CApplication::SetChannelProperties", "Failed to set the block cipher reference!\n");
		return FALSE;
	}

	if (IS_FAILURE(ptrChannel->set_TxRetryDelay(APP_ITV2_ACK_TIMEOUT)))
	{
		PrintfLogMessage("CApplication::SetChannelProperties", "Failed to set the TX Retry Delay info!\n");
		return FALSE;
	}

	if (IS_FAILURE(ptrChannel->set_TxRetryCount(APP_ITV2_RETRY_COUNT)))
	{
		PrintfLogMessage("CApplication::SetChannelProperties", "Failed to set the TX Retry Count info!\n");
		return FALSE;
	}

	if (IS_FAILURE(ptrChannel->set_RxIdleTimeout(APP_ITV2_RX_IDLE_TIME)))
	{
		PrintfLogMessage("CApplication::SetChannelProperties", "Failed to set the RX Idle Timeout info!\n");
		return FALSE;
	}

	if (IS_FAILURE(ptrChannel->set_TxIdleTimeout(APP_ITV2_TX_IDLE_TIME)))
	{
		PrintfLogMessage("CApplication::SetChannelProperties", "Failed to set the TX Idle Timeout info!\n");
		return FALSE;
	}

	//if (IS_FAILURE(ptrChannel->set_Tag(new CSessionKey(clsSessionKey))))
	if (FALSE == SetSessionKey(ptrChannel, new CSessionKey(clsSessionKey)))
	{
		PrintfLogMessage("CApplication::SetChannelProperties", "Failed to set the session key tag!\n");
		return FALSE;
	}

	//success
	return TRUE;
}

//---------------------------------------------------------------------------

BOOL CApplication::WriteDataToChannel(
	DSC_IChannel* ptrChannel, BYTE const* bufData, size_t numSize)
{
	//is the channel present?
	if (NULL != ptrChannel)
	{
		//write data
		DSC_SIZE_T count = 0;
		if (IS_FAILURE(ptrChannel->ReceiveRawData(
			bufData, static_cast<DSC_SIZE_T>(numSize), &count)))
		{
			//failure to write data
			PrintfLogMessage("CApplication::WriteDataToChannel", 
				"The channel %p failed to receive data!\n", ptrChannel);
		}
		else if (count != numSize)
		{
			//not all data was written
			PrintfLogMessage("CApplication::WriteDataToChannel", 
				"Not all data was written to the channel %d!\n", ptrChannel);
		}
		else
		{
			//success
			return TRUE;
		}
	}
	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

VOID CApplication::ProcessInternalStates(VOID)
{
	BEGIN_CRITICAL_SECTION(m_objSecurityBasesLock)
		size_t count = m_lstSecurityBases.Count();
		for (size_t i = 0; i < count; ++i)
		{
			TComPtr<DSC_ISecurityBase> ptr = m_lstSecurityBases.GetAt(i);
			if (IS_FAILURE(ptr->ProcessState()))
			{
				DEBUG_ASSERT(FALSE);
			}
		}
	END_CRITICAL_SECTION()
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID CApplication::ConnectUdpEvents(CUDPPoint& clsUdpPoint)
{
	clsUdpPoint.ActivateEvent += &OnUdpActivateHandler;
	clsUdpPoint.ShutdownEvent += &OnUdpShutdownHandler;
	clsUdpPoint.MainLoopEvent += &OnUdpMainLoopHandler;
	//clsUdpPoint.ReadIdleEvent += &OnUdpReadIdleHandler;
	//clsUdpPoint.SendIdleEvent += &OnUdpSendIdleHandler;
	clsUdpPoint.ReceivedEvent += &OnUdpReceivedHandler;
}

//---------------------------------------------------------------------------

VOID CApplication::DisconnectUdpEvents(CUDPPoint& clsUdpPoint)
{
	clsUdpPoint.ActivateEvent -= &OnUdpActivateHandler;
	clsUdpPoint.ShutdownEvent -= &OnUdpShutdownHandler;
	clsUdpPoint.MainLoopEvent -= &OnUdpMainLoopHandler;
	//clsUdpPoint.ReadIdleEvent -= &OnUdpReadIdleHandler;
	//clsUdpPoint.SendIdleEvent -= &OnUdpSendIdleHandler;
	clsUdpPoint.ReceivedEvent -= &OnUdpReceivedHandler;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID CApplication::ConnectTcpEvents(CTCPServer& clsTcpServer)
{
	clsTcpServer.ActivateEvent += &OnTcpActivateHandler;
	clsTcpServer.ShutdownEvent += &OnTcpShutdownHandler;
	clsTcpServer.MainLoopEvent += &OnTcpMainLoopHandler;

	clsTcpServer.ConnectionOpenEvent += &OnTcpConnectionOpenHandler;
	clsTcpServer.ConnectionClosedEvent += &OnTcpConnectionClosedHandler;
	clsTcpServer.ConnectionThreadEvent += &OnTcpConnectionThreadHandler;
	clsTcpServer.ConnectionRxIdleEvent += &OnTcpConnectionRxIdleHandler;
	clsTcpServer.ConnectionTxIdleEvent += &OnTcpConnectionTxIdleHandler;
	clsTcpServer.ConnectionRxDataEvent += &OnTcpConnectionRxDataHandler;
}

//---------------------------------------------------------------------------

VOID CApplication::DisconnectTcpEvents(CTCPServer& clsTcpServer)
{
	clsTcpServer.ActivateEvent -= &OnTcpActivateHandler;
	clsTcpServer.ShutdownEvent -= &OnTcpShutdownHandler;
	clsTcpServer.MainLoopEvent -= &OnTcpMainLoopHandler;

	clsTcpServer.ConnectionOpenEvent -= &OnTcpConnectionOpenHandler;
	clsTcpServer.ConnectionClosedEvent -= &OnTcpConnectionClosedHandler;
	clsTcpServer.ConnectionThreadEvent -= &OnTcpConnectionThreadHandler;
	clsTcpServer.ConnectionRxIdleEvent -= &OnTcpConnectionRxIdleHandler;
	clsTcpServer.ConnectionTxIdleEvent -= &OnTcpConnectionTxIdleHandler;
	clsTcpServer.ConnectionRxDataEvent -= &OnTcpConnectionRxDataHandler;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID CApplication::ConnectChannelEvents(DSC_IChannel* ptrChannel)
{
	if (NULL != ptrChannel)
	{
		//fetch the data sink interface
		TComPtr<DSC_IChannelEventSink> ptr;
		//if (IS_FAILURE(m_clsChannelEventHandlers.Query(NAME_DSC_IChannelEventSink, ptr)))
		//{
		//	DEBUG_ASSERT(FALSE);
		//}
		if (IS_FAILURE(m_ptrChannelEventSink->Query(NAME_DSC_IChannelEventSink, ptr)))
		{
			DEBUG_ASSERT(FALSE);
		}

		//pass the interface to the channel
		if (IS_FAILURE(ptrChannel->add_EventSink(ptr)))
		{
			PrintfLogMessage("CApplication::ConnectChannelEvents", 
				"Failed to attach the event sink to the channel %p!\n", ptrChannel);
			DEBUG_ASSERT(FALSE);
		}
	}
}

//---------------------------------------------------------------------------

VOID CApplication::DisconnectChannelEvents(DSC_IChannel* ptrChannel)
{
	if (NULL != ptrChannel)
	{
		//fetch the data sink interface
		TComPtr<DSC_IChannelEventSink> ptr;
		//if (IS_FAILURE(m_clsChannelEventHandlers.Query(NAME_DSC_IChannelEventSink, ptr)))
		//{
		//	DEBUG_ASSERT(FALSE);
		//}
		if (IS_FAILURE(m_ptrChannelEventSink->Query(NAME_DSC_IChannelEventSink, ptr)))
		{
			DEBUG_ASSERT(FALSE);
		}

		//pass the interface to the channel
		if (IS_FAILURE(ptrChannel->remove_EventSink(ptr)))
		{
			PrintfLogMessage("CApplication::ConnectChannelEvents", 
				"Failed to detach the event sink from the channel %p!\n", ptrChannel);
			DEBUG_ASSERT(FALSE);
		}
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID CApplication::ConnectSecurityEvents(DSC_ISecurityBase* ptrSecurity)
{
	if (NULL != ptrSecurity)
	{
		//fetch the data sink interface
		TComPtr<DSC_ISecurityEventSink> ptr;
		if (IS_FAILURE(m_ptrSecurityEventSink->Query(NAME_DSC_ISecurityEventSink, ptr)))
		{
			DEBUG_ASSERT(FALSE);
		}

		//pass the interface to the channel
		if (IS_FAILURE(ptrSecurity->add_EventSink(ptr)))
		{
			PrintfLogMessage("CApplication::ConnectSecurityEvents", 
				"Failed to attach the event sink to the secutiry base %p!\n", ptrSecurity);
			DEBUG_ASSERT(FALSE);
		}
	}
}

//---------------------------------------------------------------------------

VOID CApplication::DisconnectSecurityEvents(DSC_ISecurityBase* ptrSecurity)
{
	if (NULL != ptrSecurity)
	{
		//fetch the data sink interface
		TComPtr<DSC_ISecurityEventSink> ptr;
		if (IS_FAILURE(m_ptrSecurityEventSink->Query(NAME_DSC_ISecurityEventSink, ptr)))
		{
			DEBUG_ASSERT(FALSE);
		}

		//pass the interface to the channel
		if (IS_FAILURE(ptrSecurity->remove_EventSink(ptr)))
		{
			PrintfLogMessage("CApplication::ConnectSecurityEvents", 
				"Failed to detach the event sink from the security base %p!\n", ptrSecurity);
			DEBUG_ASSERT(FALSE);
		}
	}
}

//---------------------------------------------------------------------------

//VOID CApplication::ConvertTimeStamp(time_t numUnixTime, DATE_TIME* ptrDateTime)
//{
//	DEBUG_ASSERT(NULL != ptrDateTime);
//
//	//negative time is not supported
//	if (0 > numUnixTime) numUnixTime = 0;
//
//	//get hours, minutes and seconds
//	ptrDateTime->Second = numUnixTime % 60; numUnixTime /= 60;
//	ptrDateTime->Minute = numUnixTime % 60; numUnixTime /= 60;
//	ptrDateTime->Hour = numUnixTime % 24; numUnixTime /= 24;
//	//now the numUnixTime contains the number of days
//
//	//convert the number of days to date assuming
//	//0 days corresponds to January 1st, 1970
//    UINT32 a = static_cast<UINT32>((4 * numUnixTime + 102032) / 146097 + 15);
//    UINT32 b = static_cast<UINT32>(numUnixTime + 2442113 + a - (a / 4));
//    UINT32 c = static_cast<UINT32>((20 * b - 2442) / 7305);
//    UINT32 d = static_cast<UINT32>(b - 365 * c - (c / 4));
//    UINT32 e = static_cast<UINT32>(d * 1000 / 30601);
//    UINT32 f = static_cast<UINT32>(d - e * 30 - e * 601 / 1000);
//  
//    //January and February are counted as months 
//	//13 and 14 of the previous year
//    if (13 >= e)
//    {
//       c -= 4716;
//       e -= 1;
//    }
//    else
//    {
//       c -= 4715;
//       e -= 13;
//    }
//  
//    //store year, month and day
//    ptrDateTime->Year = c;
//    ptrDateTime->Month = e;
//    ptrDateTime->Day = f;
//}

//---------------------------------------------------------------------------

VOID CApplication::PrintfLogMessage(const char* pszSource, const char* pszFormat, ...) const
{
	//get time duration since the start of the app
	time_t duration = static_cast<time_t>(
		difftime(time(NULL), m_clsStartTime));

	//get days, hours, minutes and seconds
	int seconds = static_cast<int>(duration % 60); duration /= 60;
	int minutes = static_cast<int>(duration % 60); duration /= 60;
	int hours = static_cast<int>(duration % 24); duration /= 24;
	int days = static_cast<int>(duration);

	//print the time stamp and the source info
	printf("[%d:%02d:%02d:%02d][%s] ", days, hours, minutes, seconds, pszSource);

	//print the args
	va_list args;
	va_start(args, pszFormat);
	vprintf(pszFormat, args);
	va_end(args);
}

//---------------------------------------------------------------------------

VOID CApplication::CheckDiagnostics(DSC_IDiagnostics* ptrDiagnostics)
{
	//sanity check
	DEBUG_ASSERT(NULL != ptrDiagnostics);
	if (NULL == ptrDiagnostics)
	{
		return;
	}

	//data
	ICOUNT mem_count = 0;
	ICOUNT ref_count = 0;
	time_t now = time(NULL);

	//show time stamp
	printf("\n");
	PrintfLogMessage("CApplication::CheckDiagnostics", "%s", ctime(&now));
	printf("---------------------------------------------------------------------------\n");

#if CODE_TEXT_BLOCK
	//get ref count values
	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::Interactive, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("Interactive -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}
#endif

#if CODE_TEXT_BLOCK
	//get ref count values
	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::BlockCipher, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("BlockCipher -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::Channel, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("Channel -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::ChannelEventSink, &mem_count, &ref_count)))
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("ChannelEventSink -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::Component, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("Component -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::DataBuffer, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("DataBuffer -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::DataStore, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("DataStore -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::Diagnostics, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("Diagnostics -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::LicenseManager, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("LicenseManager -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::ProtocolData, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("ProtocolData -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::SystemIndices, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("SystemIndices -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::TextString, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("TextString -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}
#endif

#if CODE_TEXT_BLOCK
	//get ref count values
	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::AccessCode, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("AccessCode -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::AccessCodeAttributes, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("AccessCodeAttributes -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::AccessCodeManager, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("AccessCodeManager -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::AccessCredentials, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("AccessCredentials -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::AlarmTypeContainer, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("AlarmTypeContainer -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::AssignmentData, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("AssignmentData -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::AssignmentList, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("AssignmentList -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::BuzzerDataContainer, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("BuzzerDataContainer -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::CommandOutputDataContainer, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("CommandOutputDataContainer -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::EventBufferEntryDataContainer, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("EventBufferEntryDataContainer -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}
#endif

#if CODE_TEXT_BLOCK
	//get ref count values
	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::KeyPressedDataContainer, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("KeyPressedDataContainer -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::LCDCursorDataContainer, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("LCDCursorDataContainer -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::LCDUpdateDataContainer, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("LCDUpdateDataContainer -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::LEDStatusDataContainer, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("LEDStatusDataContainer -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::LifeStyleSettings, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("LifeStyleSettings -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::Partition, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("Partition -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::PartitionManager, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("PartitionManager -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::PartitionStateData, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("PartitionStateData -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::ProgrammingDataContainer, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("ProgrammingDataContainer -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::Repository, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("Repository -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}
#endif

#if CODE_TEXT_BLOCK
	//get ref count values
	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::RequestResult, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("RequestResult -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::SecurityBase, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("SecurityBase -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::SecurityEventSink, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("SecurityEventSink -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::SpecificFunctions, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("SpecificFunctions -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::SystemCapabilities, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("SystemCapabilities -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::SystemInformation, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("SystemInformation -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::SystemManager, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("SystemManager -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::TroubleData, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("TroubleData -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::TroubleList, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("TroubleList -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::VirtualKeypad, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("VirtualKeypad -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}
#endif

#if CODE_TEXT_BLOCK
	//get ref count values
	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::VirtualKeypadManager, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("VirtualKeypadManager -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::VirtualZone, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("VirtualZone -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::VirtualZoneManager, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("VirtualZoneManager -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::VirtualZoneStatus, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("VirtualZoneStatus -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::Zone, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("Zone -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::ZoneAttributes, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("ZoneAttributes -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}

	if (IS_SUCCESS(ptrDiagnostics->GetObjectTypeCounts(
		DSC_ObjectTypes::ZoneManager, &mem_count, &ref_count))) 
	{
		if ((0 < mem_count) || (0 < ref_count))
			printf("ZoneManager -> Mem Count: %d, Ref Count: %d\n", mem_count, ref_count);
	}
	else
	{
		DEBUG_ASSERT(FALSE);
	}
#endif

	printf("---------------------------------------------------------------------------\n\n");
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
