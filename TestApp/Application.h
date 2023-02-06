#pragma once

//---------------------------------------------------------------------------
#include "DSC_Config.hpp"

#if defined(WINDOWS)
#if defined(_WINDLL)
#include "DSC_WinDLL.hpp"
#else
#include "DSC_WinLIB.hpp"
#endif
#elif defined(LINUX)
#include "DSC_LinuxLIB.hpp"
#else
#error "Undefined platform information!"
#endif
#include "DSC_IInteractive.hpp"
#include "DSC_Parameters.hpp"
#include "DSC_ChannelEvents.hpp"
#include "UDPPoint.h"
#include "SessionKey.h"
#include "SessionData.h"
#include "TCPServer.h"
#include "DataStore.h"
#include "Lock.hpp"
#include "Application_UI.h"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

//---------------------------------------------------------------------------

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//---------------------------------------------------------------------------

//use this to trick the VS2010 compiler to allow collapsing 
//segments of C++ source code for easier readibility
#define CODE_TEXT_BLOCK		(FALSE == FALSE)

#define APP_LOOP_SLEEP			100	//[ms]
#define APP_SYSTEM_PULSE		20	//unit time depends on the thread loop's execution interval
#define APP_DIAGNOSTICS_TIME	60	//time interval between diagnostics checks in [s]

//if the TCP connection remains idle for more than 120sec
//the Quazar might have already closed the connection or
//it was forcefully disconnected - shut down the proxy and end the session
//#define APP_TCP_IDLE_TIMEOUT	130	//the time in [s] for TCP 'no traffic' timeout
#define APP_TCP_IDLE_TIMEOUT	320	//the time in [s] for TCP 'no traffic' timeout

//if the UDP connection remains idle for more than 5 min
//the Quazar might not be able to send UDP packets - end the session
#define APP_UDP_IDLE_TIMEOUT	360

#define APP_ITV2_ACK_TIMEOUT	5	//[s]
#define APP_ITV2_RETRY_COUNT	4

#define APP_ITV2_RX_IDLE_TIME	30	//timeout in [s]
#define APP_ITV2_TX_IDLE_TIME	0	//timeout in [s]
//#define APP_ITV2_TX_IDLE_TIME	0	//timeout in [s]	//disable sending server's Poll

//invalid license data
#define APP_ITV2_FEATURE_LICENSES		"00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"

//---------------------------------------------------------------------------

#define APP_UDP_ADDR			"127.0.0.1"
#define APP_UDP_PORT			3073
#define APP_UDP_CHECK_INTERVAL	10	//[s]
#define APP_UDP_CONNECTION		"UDP"

#define APP_TCP_ADDR			"127.0.0.1"
#define APP_TCP_PORT			3072
#define APP_SEND_TIMEOUT		5	//[s]
#define APP_TCP_CONNECTION		"TCP"

//Type 1 encryption
#define APP_DEFAULT_ACCOUNT		"123456789012"
#define APP_INTEGRATION_ID		"123456789012"
#define APP_ACCESS_CODE			"12345678"
#define APP_UDP_FUNCTION		ITV2_PARAM_FUNCTION_POLLING_ONLY
#define APP_TCP_FUNCTION		ITV2_PARAM_FUNCTION_NOTIFICATIONS
#define APP_KEY_CHANGE_TIME		0

////Type 2 encryption
//#define APP_DEFAULT_ACCOUNT		"123456789012"
//#define APP_INTEGRATION_ID		"123456789012"
//#define APP_ACCESS_CODE			"12345678123456781234567812345678"
//#define APP_UDP_FUNCTION		ITV2_PARAM_FUNCTION_POLLING_ONLY
//#define APP_TCP_FUNCTION		ITV2_PARAM_FUNCTION_NOTIFICATIONS
//#define APP_KEY_CHANGE_TIME		300

//---------------------------------------------------------------------------

class CApplication
{
//data structs
private:
	//typedef struct {
	//	UINT32	Year;
	//	BYTE	Month;
	//	BYTE	Day;
	//	BYTE	Hour;
	//	BYTE	Minute;
	//	BYTE	Second;
	//} DATE_TIME;

	typedef struct
	{
		TComPtr<DSC_IInteractive>			interactive;
		TComPtr<DSC_IDiagnostics>			diagnostics;
		TComPtr<DSC_ISecurityBase>			instance;
		TComPtr<DSC_IAccessCredentials>		installer_credentials;
		TComPtr<DSC_IAccessCredentials>		user_credentials;
		TComPtr<DSC_ISystemManager>			system_manager;
		TComPtr<DSC_IVirtualZoneManager>    virtual_zone_manager;
		TComPtr<DSC_IVirtualKeypadManager>  virtual_keypad_manager;
		TComPtr<DSC_IVirtualKeypad>			virtual_keypad;
		TComPtr<DSC_IVirtualZone>           virtual_zone;
		TComPtr<DSC_IVirtualZoneStatus>     virtual_zone_status;
		TComPtr<DSC_IPartitionManager>		partition_manager;
		TComPtr<DSC_IPartition>				partition;
		TComPtr<DSC_IZoneManager>			zone_manager;
		TComPtr<DSC_IAccessCodeManager>		accesscode_manager;
		TComPtr<DSC_IZone>					zone;
		TComPtr<DSC_IZoneAttributes>        zone_attributes;
		TComPtr<DSC_IAccessCode>			access_code;
		TComPtr<DSC_IAccessCodeAttributes>	access_code_attributes;
		TComPtr<DSC_ISpecificFunctions>     specific_functions;
		BYTE								menulevel;
		BYTE								previous_menulevel;
	} UI_VARIBLES;

//constants
private:

	//UDP
	const TEventHandler<CUDPPoint, CSocketEventArgs, CApplication> OnUdpActivateHandler;
	const TEventHandler<CUDPPoint, CSocketEventArgs, CApplication> OnUdpShutdownHandler;
	const TEventHandler<CUDPPoint, CSocketEventArgs, CApplication> OnUdpMainLoopHandler;
	//const TEventHandler<CUDPPoint, CSocketEventArgs, CApplication> OnUdpReadIdleHandler;
	//const TEventHandler<CUDPPoint, CSocketEventArgs, CApplication> OnUdpSendIdleHandler;
	const TEventHandler<CUDPPoint, CSocketEventArgs, CApplication> OnUdpReceivedHandler;

	//TCP
	const TEventHandler<CTCPServer, CSocketEventArgs, CApplication> OnTcpActivateHandler;
	const TEventHandler<CTCPServer, CSocketEventArgs, CApplication> OnTcpShutdownHandler;
	const TEventHandler<CTCPServer, CSocketEventArgs, CApplication> OnTcpMainLoopHandler;

	const TEventHandler<CTCPProxy, CSocketEventArgs, CApplication> OnTcpConnectionOpenHandler;
	const TEventHandler<CTCPProxy, CSocketEventArgs, CApplication> OnTcpConnectionClosedHandler;
	const TEventHandler<CTCPProxy, CSocketEventArgs, CApplication> OnTcpConnectionThreadHandler;
	const TEventHandler<CTCPProxy, CSocketEventArgs, CApplication> OnTcpConnectionRxIdleHandler;
	const TEventHandler<CTCPProxy, CSocketEventArgs, CApplication> OnTcpConnectionTxIdleHandler;
	const TEventHandler<CTCPProxy, CSocketEventArgs, CApplication> OnTcpConnectionRxDataHandler;

	////ITV2 Channel

//private members
private:

	TComPtr<CDataStore>						m_ptrDataStore;
	TComPtr<DSC_IInteractive>				m_ptrInteractive;
	TComPtr<DSC_IDiagnostics>				m_ptrDiagnostics;
	TMemPtr<BYTE>							m_ptrDefaultLicense;
	TComPtr<DSC_ILicenseManager>			m_ptrLicenseManager;
	TComPtr<DSC_IBlockCipher>				m_ptrBlockCipher;
	TComPtr<DSC_IChannelEventSink>			m_ptrChannelEventSink;
	TComPtr<DSC_ISecurityEventSink>			m_ptrSecurityEventSink;

	CUDPPoint								m_clsUdpListener;
	CTCPServer								m_clsTcpServer;

	TDictionary<string, TComPtr<DSC_ISecurityBase> >	m_lstSecurityBases;
	CCriticalSection									m_objSecurityBasesLock;

	TDictionary<CSessionKey, CSessionData>	m_lstUDPSessions;
	//time_t								m_objUDPCleanupTime;
	CCriticalSection						m_objUDPSessionsLock;

	TDictionary<CSessionKey, CSessionData>	m_lstTCPSessions;
	CCriticalSection						m_objTCPSessionsLock;

	//diagnostics check time
	time_t			m_clsDiagnosticsTime;

	//user interface data
	UI_VARIBLES		ui_vars;
	time_t			m_clsStartTime;

//event handlers
private:
	//there are many ways of implementing the event sink...
	//class CChannelEventHandlers : public DSC_IChannelEventSink
	class CChannelEventHandlers : public CComponent, public DSC_IChannelEventSink
	{
	private:
		CApplication* m_ptrOwner;

	public:
		CChannelEventHandlers(CApplication* ptrOwner);
		virtual ~CChannelEventHandlers(VOID);
		VOID ClearOwner(VOID);
		VOID PrintfLogMessage(const char* pszSource, const char* pszFormat, ...) const;

		//DSC_IComponent
		virtual IRESULT ICALL Query(IN char const* pszInterface, OUT VOID** ptrInterface);
		virtual IRESULT ICALL Acquire(OUT ICOUNT* ptrCount);
		virtual IRESULT ICALL Release(OUT ICOUNT* ptrCount);

		//DSC_IChannelEventSink
		virtual IRESULT ICALL OnEventNotificationHandler(
			IN DSC_IChannel* ptrSender, IN char const* pszText,
			IN DSC_ChannelEvent flgEvent);
		virtual IRESULT ICALL OnErrorNotificationHandler(
			IN DSC_IChannel* ptrSender, IN char const* pszText,
			IN DSC_ChannelEvent flgEvent, IN DSC_ChannelError numError);
		virtual IRESULT ICALL OnStateNotificationHandler(
			IN DSC_IChannel* ptrSender, IN char const* pszText,
			IN DSC_ChannelEvent flgEvent, IN DSC_CHANNEL_STATE_FLAGS flgStateFlags);
		virtual IRESULT ICALL OnPacketReceivedHandler(IN DSC_IChannel* ptrSender, 
			IN char const* pszText, IN DSC_ChannelEvent flgEvent,
			IN BYTE const* bufData, IN DSC_SIZE_T numSize);
		virtual IRESULT ICALL OnSendDataPacketHandler(IN DSC_IChannel* ptrSender, 
			IN char const* pszText, IN DSC_ChannelEvent flgEvent,
			IN BYTE const* bufData, IN DSC_SIZE_T numSize);
		virtual IRESULT ICALL OnInspectPayloadHandler(IN DSC_IChannel* ptrSender, 
			IN char const* pszText, IN DSC_ChannelEvent flgEvent,
			IN BYTE const* bufData, IN DSC_SIZE_T numSize);
		virtual IRESULT ICALL OnDataProcessingHandler(IN DSC_IChannel* ptrSender, 
			IN char const* pszText, IN DSC_ChannelEvent flgEvent,
			IN DSC_IProtocolData* ptrPayload);
	//} m_clsChannelEventHandlers;	//event handlers
	};

	class CSecurityEventHandlers : public CComponent, public DSC_ISecurityEventSink2
	{
	private:
		CApplication* m_ptrOwner;

	public:
		CSecurityEventHandlers(CApplication* ptrOwner);
		virtual ~CSecurityEventHandlers(VOID);
		VOID ClearOwner(VOID);
		VOID PrintfLogMessage(const char* pszSource, const char* pszFormat, ...) const;

		//DSC_IComponent
		virtual IRESULT ICALL Query(IN char const* pszInterface, OUT VOID** ptrInterface);
		virtual IRESULT ICALL Acquire(OUT ICOUNT* ptrCount);
		virtual IRESULT ICALL Release(OUT ICOUNT* ptrCount);

		//DSC_ISecurityEventSink
		virtual IRESULT ICALL OnGeneralNotificationHandler(IN DSC_ISecurityBase* ptrSender, 
			IN DSC_SecurityEventCategory flgEventCategory, IN DSC_SecurityEventType flgEventType,
			IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer);

		virtual IRESULT ICALL OnDataUpdateNotificationHandler(IN DSC_ISecurityBase* ptrSender, 
			IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer, 
			IN DSC_SecurityDataSelector const* tblDataSelectors, IN DSC_SIZE_T numDataSelectors);

		virtual IRESULT ICALL OnDataUpdateNotificationExtHandler(IN DSC_ISecurityBase* ptrSender, 
			IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer, 
			IN DSC_SecurityDataSelector const* tblDataSelectors, IN DSC_SIZE_T numDataSelectors, 
			IN DSC_DataContainer flgAuxDataContainer, IN DSC_IComponent* ptrAuxDataContainer);
	};

//constructor and destructor
public:

	CApplication(VOID);
	virtual ~CApplication(VOID);

//properties
public:

//public methods
public:

	VOID Execute(VOID);

//private methods
private:

	VOID DisplayMainMenu(VOID);
	VOID DisplaySystemManagerMenu(VOID);
	VOID DisplayVirtualZoneManagerMenu(VOID);
	VOID DisplayVirtualKeypadManagerMenu(VOID);
	VOID DisplayVirtualKeypadMenu(VOID);
	VOID DisplayVirtualZoneMenu(VOID);
	VOID DisplayVirtualZoneStatusMenu(VOID);
	VOID DisplayPartitionManagerMenu(VOID);
	VOID DisplayPartitionMenu(VOID);
	VOID DisplayZoneManagerMenu(VOID);
	VOID DisplayAccessCodeManagerMenu(VOID);
	VOID DisplayZoneMenu(VOID);
	VOID DisplayZoneAttributesMenu(VOID);
	VOID DisplayAccessCodeMenu(VOID);
	VOID DisplayAccessCodeAttributesMenu(VOID);
	VOID DisplayMenu(VOID);
	VOID DisplaySpecificFunctionsMenu(VOID);
	VOID doUIMainMenu(VOID);
	VOID doUISystemManagerMenu(VOID);
	VOID doUIVirtualZoneManagerMenu(VOID);
	VOID doUIVirtualKeypadManagerMenu(VOID);
	VOID doUIVirtualKeypadMenu(VOID);
	VOID doUIVirtualZoneMenu(VOID);
	VOID doUIVirtualZoneStatusMenu(VOID);
	VOID doUIPartitionManagerMenu(VOID);
	VOID doUIPartitionMenu(VOID);
	VOID doUIZoneManagerMenu(VOID);
	VOID doUIAccessCodeManagerMenu(VOID);
	VOID doUIZoneMenu(VOID);
	VOID doUIZoneAttributesMenu(VOID);
	VOID doUIAccessCodeMenu(VOID);
	VOID doUIAccessCodeAttributesMenu(VOID);
	VOID doUISpecificFunctionsMenu(VOID);
	BOOL doUserInterface(VOID);

#ifndef NDEBUG
	VOID TestDatabaseQuery(VOID);
#endif

	string RequestResultToString(DSC_IRequestResult* result);
	string IResultToString(IRESULT result);
	string ResultCodeToString(DSC_RequestResultCode code);
	string DataToString(DSC_IDataBuffer* data);

	CSessionKey* GetSessionKey(DSC_IChannel* ptrChannel) const;
	BOOL SetSessionKey(DSC_IChannel* ptrChannel, CSessionKey const* ptrKey);
	CSessionData* FindSessionData(
		TDictionary<CSessionKey, CSessionData> const& lstSessionData, 
		CSessionKey const& clsSessionKey);
	BOOL ProcSessionTimeout(CSessionData& clsSession);
	BOOL SetChannelProperties(DSC_IChannel* ptrChannel, 
		char const* pszConnInfo, CSessionKey const& clsSessionKey);
	BOOL WriteDataToChannel(DSC_IChannel* ptrChannel,
		BYTE const* bufData, size_t numSize);
	VOID ProcessInternalStates(VOID);
	string CommandToString(UINT16 cmd);
	string CommonEnumResultToString(int commonValue);

	VOID ConnectUdpEvents(CUDPPoint& clsUdpPoint);
	VOID DisconnectUdpEvents(CUDPPoint& clsUdpPoint);

	VOID ConnectTcpEvents(CTCPServer& clsTcpServer);
	VOID DisconnectTcpEvents(CTCPServer& clsTcpServer);

	VOID ConnectChannelEvents(DSC_IChannel* ptrChannel);
	VOID DisconnectChannelEvents(DSC_IChannel* ptrChannel);

	VOID ConnectSecurityEvents(DSC_ISecurityBase* ptrSecurity);
	VOID DisconnectSecurityEvents(DSC_ISecurityBase* ptrSecurity);

	//VOID ConvertTimeStamp(time_t numUnixTime, DATE_TIME* ptrDateTime);
	VOID PrintfLogMessage(const char* pszSource, const char* pszFormat, ...) const;
	VOID CheckDiagnostics(DSC_IDiagnostics* ptrDiagnostics);

//event handlers
private:

	//UDP
	VOID OnUdpActivateEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnUdpShutdownEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnUdpMainLoopEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs);
	//VOID OnUdpReadIdleEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs);
	//VOID OnUdpSendIdleEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnUdpReceivedEvent(CUDPPoint* ptrSender, CSocketEventArgs const* ptrArgs);

	//TCP
	VOID OnTcpActivateEvent(CTCPServer* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnTcpShutdownEvent(CTCPServer* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnTcpMainLoopEvent(CTCPServer* ptrSender, CSocketEventArgs const* ptrArgs);

	VOID OnTcpConnectionOpenEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnTcpConnectionClosedEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnTcpConnectionThreadEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnTcpConnectionRxIdleEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnTcpConnectionTxIdleEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);
	VOID OnTcpConnectionRxDataEvent(CTCPProxy* ptrSender, CSocketEventArgs const* ptrArgs);

	//ITV2 Channel
	VOID OnEventNotificationEvent(DSC_IChannel* ptrSender, 
		char const* pszText, DSC_ChannelEvent flgEvent);
	VOID OnErrorNotificationEvent(DSC_IChannel* ptrSender, 
		char const* pszText, DSC_ChannelEvent flgEvent, DSC_ChannelError numError);
	VOID OnStateNotificationEvent(DSC_IChannel* ptrSender, 
		char const* pszText, DSC_ChannelEvent flgEvent, DSC_CHANNEL_STATE_FLAGS flgStateFlags);
	VOID OnSendDataPacketEvent(DSC_IChannel* ptrSender, 
		char const* pszText, DSC_ChannelEvent flgEvent, BYTE const* bufData, size_t numSize);

	//ITV2 Security
	VOID OnGeneralNotificationEvent(DSC_ISecurityBase* ptrSender, 
		DSC_SecurityEventCategory flgEventCategory, DSC_SecurityEventType flgEventType,
		DSC_DataContainer flgDataContainer, DSC_IComponent* ptrDataContainer);
	VOID OnDataUpdateNotificationEvent(DSC_ISecurityBase* ptrSender, 
		DSC_DataContainer flgDataContainer, DSC_IComponent* ptrDataContainer, 
		DSC_SecurityDataSelector const* tblDataSelectors, size_t numDataSelectors,
		DSC_DataContainer flgAuxDataContainer, DSC_IComponent* ptrAuxDataContainer);
};

//---------------------------------------------------------------------------
#endif	//_APPLICATION_H_
