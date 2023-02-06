//---------------------------------------------------------------------------
//
//	DSC_IChannel.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The interface for implementing communication channels.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IProtocolData.hpp"
#include "DSC_ChannelStates.hpp"
#include "DSC_ChannelErrors.hpp"
#include "DSC_ChannelEvents.hpp"

#ifndef _DSC_I_CHANNEL_EVENT_SINK_HPP_
#define _DSC_I_CHANNEL_EVENT_SINK_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//The event sink interface is used for receiving channel event notifications.
#define NAME_DSC_IChannelEventSink	"DSC_IChannelEventSink"

//---------------------------------------------------------------------------

#ifndef DSC_IChannelEventSink_FWD_DEFINED
#define DSC_IChannelEventSink_FWD_DEFINED
typedef DSC_INTERFACE DSC_IChannelEventSink DSC_IChannelEventSink;
#endif

#ifndef DSC_IChannel_FWD_DEFINED
#define DSC_IChannel_FWD_DEFINED
typedef DSC_INTERFACE DSC_IChannel DSC_IChannel;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This is interface is used to receive event notifications from the DSC_IChannel.
	It must be implemented by the 3rd party software.
*/
DSC_INTERFACE DSC_IChannelEventSink : public DSC_IComponent
{
public:

	//! This event fires when a normal event is reported by the DSC_IChannel.
    /*!	
		\sa DSC_IChannel
		\sa enum DSC_ChannelEvent_Tag
     	\param ptrSender Pointer to the calling channel
     	\param pszText Used for addition connection information, if needed.
     	\param flgEvent General category of the event. See DSC_ChannelEvents.hpp
    */
	virtual IRESULT ICALL OnEventNotificationHandler(IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent) = 0;

	//! This event fires when an error event is reported by the DSC_IChannel.
    /*!	
		\sa DSC_IChannel
		\sa enum DSC_ChannelEvent_Tag
		\sa enum DSC_ChannelError_Tag
     	\param ptrSender Pointer to the calling channel
     	\param pszText Used for addition connection information, if needed.
     	\param flgEvent General category of the event. See DSC_ChannelEvents.hpp
		\param flgError The reported error code. See DSC_ChannelErrors.hpp
    */
	virtual IRESULT ICALL OnErrorNotificationHandler(IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent, 
		IN DSC_ChannelError flgError) = 0;

	//! This event fires when a state update event is reported by the DSC_IChannel.
    /*!	
		\sa DSC_IChannel
		\sa enum DSC_ChannelEvent_Tag
		\sa enum DSC_ChannelState_Tag
     	\param ptrSender Pointer to the calling channel
     	\param pszText Used for addition connection information, if needed.
     	\param flgEvent General category of the event. See DSC_ChannelEvents.hpp
		\param flgStateFlags The current state flags. See DSC_ChannelStates.hpp
    */
	virtual IRESULT ICALL OnStateNotificationHandler(IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent, 
		IN DSC_CHANNEL_STATE_FLAGS flgStateFlags) = 0;

	//! This event fires when a packet frame is received but before it is validated.
    /*! 
		This event is intended mainly for debugging.

		\sa DSC_IChannel
		\sa enum DSC_ChannelEvent_Tag
     	\param ptrSender Pointer to the calling channel
     	\param pszText Used for addition connection information, if needed.
		\param flgEvent General category of the event. See DSC_ChannelEvents.hpp
     	\param bufData Raw buffer frame, for debugging only.
     	\param numSize Size, in bytes, of the data.
    */
	virtual IRESULT ICALL OnPacketReceivedHandler(IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent,
		IN BYTE const* bufData, IN DSC_SIZE_T numSize) = 0;

	//! This event fires when a channel requests sending a packet.
    /*! 
		The data provided must be forwarded/sent to the connected product.

		\sa DSC_IChannel
		\sa enum DSC_ChannelEvent_Tag
     	\param ptrSender Pointer to the calling channel
     	\param pszText Used for addition connection information, if needed.
		\param flgEvent General category of the event. See DSC_ChannelEvents.hpp
     	\param bufData Pointer to the data to send
     	\param numSize Number of bytes to send
    */
	virtual IRESULT ICALL OnSendDataPacketHandler(IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent,
		IN BYTE const* bufData, IN DSC_SIZE_T numSize) = 0;

	//! This event fires when the valid payload is retrieved or when a payload is ready for sending
    /*! 
		This event is intended mainly for debugging.

		\sa DSC_IChannel
		\sa enum DSC_ChannelEvent_Tag
     	\param ptrSender Pointer to the calling channel
     	\param pszText Used for addition connection information, if needed.
		\param flgEvent General category of the event. See DSC_ChannelEvents.hpp
     	\param bufData Protocol specific data, do not modify!
     	\param numSize Number of bytes in the buffer
    */
	virtual IRESULT ICALL OnInspectPayloadHandler(IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent,
		IN BYTE const* bufData, IN DSC_SIZE_T numSize) = 0;

	//! This event fires when payload's status is updated during protocol's data processing.
    /*! 
		This event is intended mainly for debugging.

		\sa DSC_IChannel
		\sa enum DSC_ChannelEvent_Tag
		\sa DSC_IProtocolData
     	\param ptrSender Pointer to the calling channel
     	\param pszText Used for addition connection information, if needed.
		\param flgEvent General category of the event. See DSC_ChannelEvents.hpp
     	\param ptrPayload Protocol specific data, do not modify!
    */
	virtual IRESULT ICALL OnDataProcessingHandler(IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent,
		IN DSC_IProtocolData* ptrPayload) = 0;
};

#else

typedef struct DSC_IChannelEventSink_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IChannelEventSink *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IChannelEventSink *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IChannelEventSink *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *OnEventNotificationHandler)(IN DSC_IChannelEventSink *This,
		IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent);
	IRESULT (ICALL *OnErrorNotificationHandler)(IN DSC_IChannelEventSink *This,
		IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent, 
		IN DSC_ChannelError flgError);
	IRESULT (ICALL *OnStateNotificationHandler)(IN DSC_IChannelEventSink *This,
		IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent, 
		IN DSC_CHANNEL_STATE_FLAGS flgStateFlags);
	IRESULT (ICALL *OnPacketReceivedHandler)(IN DSC_IChannelEventSink *This,
		IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent,
		IN BYTE const* bufData, IN DSC_SIZE_T numSize);
	IRESULT (ICALL *OnSendDataPacketHandler)(IN DSC_IChannelEventSink *This,
		IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent,
		IN BYTE const* bufData, IN DSC_SIZE_T numSize);
	IRESULT (ICALL *OnInspectPayloadHandler)(IN DSC_IChannelEventSink *This,
		IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent,
		IN BYTE const* bufData, IN DSC_SIZE_T numSize);
	IRESULT (ICALL *OnDataProcessingHandler)(IN DSC_IChannelEventSink *This,
		IN DSC_IChannel* ptrSender, 
		IN char const* pszText, IN DSC_ChannelEvent flgEvent,
		IN DSC_IProtocolData* ptrPayload);

	END_INTERFACE
} DSC_IChannelEventSink_Vtbl;

DSC_INTERFACE DSC_IChannelEventSink
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IChannelEventSink_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_CHANNEL_EVENT_SINK_HPP_
