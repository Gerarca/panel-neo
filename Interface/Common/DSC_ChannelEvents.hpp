//---------------------------------------------------------------------------
//
//	DSC_ChannelEvents.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The list of various event notifications used by the channel.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_CHANNEL_EVENTS_HPP_
#define _DSC_CHANNEL_EVENTS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ChannelEvents {
/*!
	The list of various events codes used by the DSC_IChannel.
*/
enum DSC_ChannelEvent_Tag {

	Unknown					= 0,		/**< unknown - must be 0! */

	//event codes used by OnEventNotificationHandler

	ChannelClosing			= 0x0001,	/**< the channel is closing */
	ChannelDeleted			= 0x0002,	/**< the channel is being destroyed */
	ChannelRxIdle			= 0x0003,	/**< the RX channel is idle */
	ChannelTxIdle			= 0x0004,	/**< the TX channel is idle */
	DataLinkReset			= 0x0005,	/**< the channel has reset its data link state */

	PeerIdentified			= 0x1000,	/**< the peer has been identified */
	PeerSupported			= 0x1001,	/**< the peer (product) is supported by the SDK */
	PeerUnsupported			= 0x1002,	/**< the peer (product) is not supported by the SDK */

	EncryptionUpdate		= 0x1010,	/**< the encryption information has been updated */

	//event codes used by OnErrorNotificationHandler

	GeneralFailure			= 0x2000,	/**< general failure */
	DataLinkFailure			= 0x2001,	/**< data link layer failure */
	TransportFailure		= 0x2002,	/**< transport layer failure */
	ChannelFailure			= 0x2003,	/**< channel failure */
	ProtocolFailure			= 0x2004,	/**< protocol failure */

	//event codes used by OnStateNotificationHandler

	InternalState			= 0x3000,	/**< the internal state has been updated */

	//event codes used by OnPacketReceivedHandler

	PacketReceived			= 0x4000,	/**< data packet was received */

	//event codes used by OnSendDataPacketHandler

	SendDataPacket			= 0x5000,	/**< send data packet */

	//event codes used by OnInspectPayloadHandler

	IncomingData			= 0x6000,	/**< received raw payload data */
	OutgoingData			= 0x6001,	/**< raw payload data ready for sending */

	//event codes used by OnDataProcessingHandler

	ValidDataPresent		= 0x7000,	/**< valid payload data has been received */
	DataReadyToSend			= 0x7001,	/**< payload data is ready to send */
	DataStateUpdated		= 0x7002	/**< payload data's state has been updated */

}; }

#else

#define DSC_ChannelEvents(value)	(DSC_E02_##value)
enum DSC_ChannelEvent_Tag {

	DSC_E02_Unknown					= 0,		/**< unknown - must be 0! */

	//! event codes used by OnEventNotificationHandler

	DSC_E02_ChannelClosing			= 0x0001,	/**< the channel is closing */
	DSC_E02_ChannelDeleted			= 0x0002,	/**< the channel is being destroyed */
	DSC_E02_ChannelRxIdle			= 0x0003,	/**< the RX channel is idle */
	DSC_E02_ChannelTxIdle			= 0x0004,	/**< the TX channel is idle */
	DSC_E02_DataLinkReset			= 0x0005,	/**< the channel has reset its data link state */

	DSC_E02_PeerIdentified			= 0x1000,	/**< the peer has been identified */
	DSC_E02_PeerSupported			= 0x1001,	/**< the peer (product) is supported by the SDK */
	DSC_E02_PeerUnsupported			= 0x1002,	/**< the peer (product) is not supported by the SDK */

	DSC_E02_EncryptionUpdate		= 0x1010,	/**< the encryption information has been updated */

	//! event codes used by OnErrorNotificationHandler

	DSC_E02_GeneralFailure			= 0x2000,	/**< general failure */
	DSC_E02_DataLinkFailure			= 0x2001,	/**< data link layer failure */
	DSC_E02_TransportFailure		= 0x2002,	/**< transport layer failure */
	DSC_E02_ChannelFailure			= 0x2003,	/**< channel failure */
	DSC_E02_ProtocolFailure			= 0x2004,	/**< protocol failure */

	//! event codes used by OnStateNotificationHandler

	DSC_E02_InternalState			= 0x3000,	/**< the internal state has been updated */

	//! event codes used by OnPacketReceivedHandler

	DSC_E02_PacketReceived			= 0x4000,	/**< data packet was received */

	//! event codes used by OnSendDataPacketHandler

	DSC_E02_SendDataPacket			= 0x5000,	/**< send data packet */

	//! event codes used by OnInspectPayloadHandler

	DSC_E02_IncomingData			= 0x6000,	/**< received raw payload data */
	DSC_E02_OutgoingData			= 0x6001,	/**< raw payload data ready for sending */

	//! event codes used by OnDataProcessingHandler

	DSC_E02_ValidDataPresent		= 0x7000,	/**< valid payload data has been received */
	DSC_E02_DataReadyToSend			= 0x7001,	/**< payload data is ready to send */
	DSC_E02_DataStateUpdated		= 0x7002	/**< payload data's state has been updated */

};

#endif

/*!
	The DSC_ChannelEvent data type corresponds with the enum DSC_ChannelEvent_Tag.

	\sa enum DSC_ChannelEvent_Tag
*/
typedef DSC_ENUM_T DSC_ChannelEvent;

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_CHANNEL_EVENTS_HPP_
