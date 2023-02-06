#include "Application.h"
#include "HexHelper.hpp"
#include "UInt16Map.hpp"
#include "EndianHelper.hpp"
#include "Debug.hpp"

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

CApplication::CChannelEventHandlers::CChannelEventHandlers(CApplication* ptrOwner) : 
	m_ptrOwner(ptrOwner)
{
	PrintfLogMessage("CChannelEventHandlers::CChannelEventHandlers", "%p\n", this);
}

//---------------------------------------------------------------------------

CApplication::CChannelEventHandlers::~CChannelEventHandlers(VOID)
{
	PrintfLogMessage("CChannelEventHandlers::~CChannelEventHandlers", "%p\n", this);
}

//---------------------------------------------------------------------------

VOID CApplication::CChannelEventHandlers::ClearOwner(VOID)
{
	m_ptrOwner = NULL;
}

//---------------------------------------------------------------------------

VOID CApplication::CChannelEventHandlers::PrintfLogMessage(
	const char* pszSource, const char* pszFormat, ...) const
{
	if (NULL != m_ptrOwner)
	{
		try {
			//get time duration since the start of the app
			time_t duration = static_cast<time_t>(
				difftime(time(NULL), m_ptrOwner->m_clsStartTime));

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
		} catch (...) {}
	}
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CChannelEventHandlers::Query(IN char const* pszInterface, OUT VOID** ptrInterface)
{
	//validate arguments
	if ((NULL == pszInterface) || (NULL == ptrInterface))
	{
		//validate arguments
		return IRESULT_E_BAD_ARGUMENTS;
	}

	//check for DSC_IChannelEventSink ID
	CLock lock = CComponent::GetSyncLock();
	if (0 == strcmp(pszInterface, NAME_DSC_IChannelEventSink))
	{
		//increase ref count and return the pointer to this component
		DSC_IChannelEventSink* ptr = static_cast<DSC_IChannelEventSink*>(this);
		ptr->Acquire(NULL);

		//return the result
		*ptrInterface = ptr;
		return IRESULT_S_OK;
	}

	////check for DSC_IComponent ID
	//if (0 == strcmp(pszInterface, NAME_DSC_IComponent))
	//{
	//	//increase ref count and return the pointer to this component
	//	DSC_IComponent* ptr = static_cast<DSC_IComponent*>(this);
	//	ptr->Acquire(NULL);

	//	//return the result
	//	*ptrInterface = ptr;
	//	return IRESULT_S_OK;
	//}
	////unknown interface
	//return IRESULT_E_NOT_IMPLEMENTED;

	return CComponent::Query(pszInterface, ptrInterface);
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CChannelEventHandlers::Acquire(OUT ICOUNT* ptrCount)
{
	////do not control the life span
	//return IRESULT_S_OK;

	return CComponent::Acquire(ptrCount);
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CChannelEventHandlers::Release(OUT ICOUNT* ptrCount)
{
	////do not control the life span
	//return IRESULT_S_OK;

	return CComponent::Release(ptrCount);
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CChannelEventHandlers::OnEventNotificationHandler(
	IN DSC_IChannel* ptrSender, IN char const* pszText,
	IN DSC_ChannelEvent flgEvent)
{
	try
	{
		if (NULL != m_ptrOwner)
		{
			m_ptrOwner->OnEventNotificationEvent(ptrSender, pszText, flgEvent);
		}
	}
	catch (...)
	{
		DEBUG_ASSERT(FALSE);
		RELEASE_CHECK(FALSE);
		return IRESULT_E_FAILURE;
	}
	//return default result
	return IRESULT_S_OK;
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CChannelEventHandlers::OnErrorNotificationHandler(
	IN DSC_IChannel* ptrSender, IN char const* pszText,
	IN DSC_ChannelEvent flgEvent, IN DSC_ChannelError numError)
{
	try
	{
		if (NULL != m_ptrOwner)
		{
			m_ptrOwner->OnErrorNotificationEvent(ptrSender, pszText, flgEvent, numError);
		}
	}
	catch (...)
	{
		DEBUG_ASSERT(FALSE);
		RELEASE_CHECK(FALSE);
		return IRESULT_E_FAILURE;
	}
	//return default result
	return IRESULT_S_OK;
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CChannelEventHandlers::OnStateNotificationHandler(
	IN DSC_IChannel* ptrSender, IN char const* pszText,
	IN DSC_ChannelEvent flgEvent, IN DSC_CHANNEL_STATE_FLAGS flgStateFlags)
{
	try
	{
		if (NULL != m_ptrOwner)
		{
			m_ptrOwner->OnStateNotificationEvent(ptrSender, pszText, flgEvent, flgStateFlags);
		}
	}
	catch (...)
	{
		DEBUG_ASSERT(FALSE);
		RELEASE_CHECK(FALSE);
		return IRESULT_E_FAILURE;
	}
	//return default result
	return IRESULT_S_OK;
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CChannelEventHandlers::OnPacketReceivedHandler(
	IN DSC_IChannel* ptrSender, IN char const* pszText, IN DSC_ChannelEvent flgEvent,
	IN BYTE const* bufData, IN DSC_SIZE_T numSize)
{
	try
	{
		//do nothing here
	}
	catch (...)
	{
		DEBUG_ASSERT(FALSE);
		RELEASE_CHECK(FALSE);
		return IRESULT_E_FAILURE;
	}
	//return default result
	return IRESULT_S_OK;
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CChannelEventHandlers::OnSendDataPacketHandler(
	IN DSC_IChannel* ptrSender, IN char const* pszText, IN DSC_ChannelEvent flgEvent,
	IN BYTE const* bufData, IN DSC_SIZE_T numSize)
{
	try
	{
		if (NULL != m_ptrOwner)
		{
			m_ptrOwner->OnSendDataPacketEvent(
				ptrSender, pszText, flgEvent, bufData, numSize);
		}
	}
	catch (...)
	{
		DEBUG_ASSERT(FALSE);
		RELEASE_CHECK(FALSE);
		return IRESULT_E_FAILURE;
	}
	//return default result
	return IRESULT_S_OK;
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CChannelEventHandlers::OnInspectPayloadHandler(
	IN DSC_IChannel* ptrSender, IN char const* pszText, IN DSC_ChannelEvent flgEvent,
	IN BYTE const* bufData, IN DSC_SIZE_T numSize)
{
	try
	{
		if (NULL != bufData)
		{
			//get session info
			string channel = "UNKNOWN";
			CSessionKey* key = m_ptrOwner->GetSessionKey(ptrSender);
			if (NULL != key)
			{
				//check session type
				SessionType type = key->GetSessionType();
				if (SessionTypes::UDP == type)
				{
					channel = "UDP";
				}
				else if (SessionTypes::TCP == type)
				{
					channel = "TCP";
				}
			}
			else
			{
				PrintfLogMessage("CChannelEventHandlers::OnInspectPayloadHandler", 
					"%p: The session key is missing!\n", ptrSender);
			}

			UINT16 cmd;
			string cmd_msg;
			if (bufData[0] == 0x04)
			{
				cmd     = CUInt16Map::FetchValue(&bufData[1], sizeof(UINT16), CEndianHelper::IsLittleEndian());
				cmd_msg = "Low_Level_ACK";
			}
			else
			{
				// command (check data size - first byte MSB set means 2 length bytes)
				if (bufData[0] & 0x80)
				{
					cmd = CUInt16Map::FetchValue(&bufData[4], sizeof(UINT16), CEndianHelper::IsLittleEndian());
				}
				else
				{
					cmd = CUInt16Map::FetchValue(&bufData[3], sizeof(UINT16), CEndianHelper::IsLittleEndian());
				}
				cmd_msg  = m_ptrOwner->CommandToString(cmd);
			} // if
			string byte_string = CHexHelper::ToString(bufData, static_cast<size_t>(numSize), "", "", " ", FALSE);
			if (DSC_ChannelEvents::IncomingData == flgEvent)
			{
				PrintfLogMessage("CChannelEventHandlers::OnInspectPayloadHandler",
					"%p: {%s} RAW RX %04X [%s]\n", ptrSender, channel.c_str(), cmd, cmd_msg.c_str());
				PrintfLogMessage("CChannelEventHandlers::OnInspectPayloadHandler",
					"%p: %s\n", ptrSender, byte_string.c_str());
			}
			else if (DSC_ChannelEvents::OutgoingData == flgEvent)
			{
				PrintfLogMessage("CChannelEventHandlers::OnInspectPayloadHandler",
					"%p: {%s} RAW TX %04X [%s]\n", ptrSender, channel.c_str(), cmd, cmd_msg.c_str());
				PrintfLogMessage("CChannelEventHandlers::OnInspectPayloadHandler",
					"%p: %s\n", ptrSender, byte_string.c_str());
			}
		}
	}
	catch (...)
	{
		DEBUG_ASSERT(FALSE);
		RELEASE_CHECK(FALSE);
		return IRESULT_E_FAILURE;
	}
	//return default result
	return IRESULT_S_OK;
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CChannelEventHandlers::OnDataProcessingHandler(
		IN DSC_IChannel* ptrSender, IN char const* pszText, IN DSC_ChannelEvent flgEvent,
		IN DSC_IProtocolData* ptrPayload)
{
	try
	{
		//do nothing here
	}
	catch (...)
	{
		DEBUG_ASSERT(FALSE);
		RELEASE_CHECK(FALSE);
		return IRESULT_E_FAILURE;
	}
	//return default result
	return IRESULT_S_OK;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

CApplication::CSecurityEventHandlers::CSecurityEventHandlers(CApplication* ptrOwner) : 
	m_ptrOwner(ptrOwner)
{
	PrintfLogMessage("CSecurityEventHandlers::CSecurityEventHandlers", "%p\n", this);
}

//---------------------------------------------------------------------------

CApplication::CSecurityEventHandlers::~CSecurityEventHandlers(VOID)
{
	PrintfLogMessage("CSecurityEventHandlers::~CSecurityEventHandlers", "%p\n", this);
}

//---------------------------------------------------------------------------

VOID CApplication::CSecurityEventHandlers::ClearOwner(VOID)
{
	m_ptrOwner = NULL;
}

//---------------------------------------------------------------------------

VOID CApplication::CSecurityEventHandlers::PrintfLogMessage(
	const char* pszSource, const char* pszFormat, ...) const
{
	if (NULL != m_ptrOwner)
	{
		try {
			//get time duration since the start of the app
			time_t duration = static_cast<time_t>(
				difftime(time(NULL), m_ptrOwner->m_clsStartTime));

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
		} catch (...) {}
	}
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CSecurityEventHandlers::Query(IN char const* pszInterface, OUT VOID** ptrInterface)
{
	//validate arguments
	if ((NULL == pszInterface) || (NULL == ptrInterface))
	{
		//validate arguments
		return IRESULT_E_BAD_ARGUMENTS;
	}

	//check for DSC_ISecurityEventSink ID
	CLock lock = CComponent::GetSyncLock();
	if (0 == strcmp(pszInterface, NAME_DSC_ISecurityEventSink))
	{
		//increase ref count and return the pointer to this component
		DSC_ISecurityEventSink* ptr = static_cast<DSC_ISecurityEventSink*>(this);
		ptr->Acquire(NULL);

		//return the result
		*ptrInterface = ptr;
		return IRESULT_S_OK;
	}
	else if (0 == strcmp(pszInterface, NAME_DSC_ISecurityEventSink2))
	{
		//increase ref count and return the pointer to this component
		DSC_ISecurityEventSink2* ptr = static_cast<DSC_ISecurityEventSink2*>(this);
		ptr->Acquire(NULL);

		//return the result
		*ptrInterface = ptr;
		return IRESULT_S_OK;
	}

	//check for DSC_IComponent ID
	return CComponent::Query(pszInterface, ptrInterface);
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CSecurityEventHandlers::Acquire(OUT ICOUNT* ptrCount)
{
	////do not control the life span
	//return IRESULT_S_OK;

	return CComponent::Acquire(ptrCount);
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CSecurityEventHandlers::Release(OUT ICOUNT* ptrCount)
{
	////do not control the life span
	//return IRESULT_S_OK;

	return CComponent::Release(ptrCount);
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CSecurityEventHandlers::OnGeneralNotificationHandler(
	IN DSC_ISecurityBase* ptrSender, 
	IN DSC_SecurityEventCategory flgEventCategory, IN DSC_SecurityEventType flgEventType,
	IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer)
{
	try
	{
		if (NULL != m_ptrOwner)
		{
			m_ptrOwner->OnGeneralNotificationEvent(ptrSender, 
				flgEventCategory, flgEventType,
				flgDataContainer, ptrDataContainer);
		}
	}
	catch (...)
	{
		DEBUG_ASSERT(FALSE);
		RELEASE_CHECK(FALSE);
		return IRESULT_E_FAILURE;
	}
	//return default result
	return IRESULT_S_OK;
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CSecurityEventHandlers::OnDataUpdateNotificationHandler(
	IN DSC_ISecurityBase* ptrSender, 
	IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer, 
	IN DSC_SecurityDataSelector const* tblDataSelectors, IN DSC_SIZE_T numDataSelectors)
{
	//this handler is obsolete in DSC_ISecurityEventSink2 - 
	//use the extended handler: OnDataUpdateNotificationExtHandler
	DEBUG_ASSERT(FALSE);

	//return default result
	return IRESULT_S_OK;
}

//---------------------------------------------------------------------------

IRESULT ICALL CApplication::CSecurityEventHandlers::OnDataUpdateNotificationExtHandler(
	IN DSC_ISecurityBase* ptrSender, 
	IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer, 
	IN DSC_SecurityDataSelector const* tblDataSelectors, IN DSC_SIZE_T numDataSelectors,
	IN DSC_DataContainer flgAuxDataContainer, IN DSC_IComponent* ptrAuxDataContainer)
{
	try
	{
		if (NULL != m_ptrOwner)
		{
			m_ptrOwner->OnDataUpdateNotificationEvent(ptrSender, 
				flgDataContainer, ptrDataContainer, 
				tblDataSelectors, static_cast<size_t>(numDataSelectors),
				flgAuxDataContainer, ptrAuxDataContainer);
		}
	}
	catch (...)
	{
		DEBUG_ASSERT(FALSE);
		RELEASE_CHECK(FALSE);
		return IRESULT_E_FAILURE;
	}
	//return default result
	return IRESULT_S_OK;
}

//---------------------------------------------------------------------------
