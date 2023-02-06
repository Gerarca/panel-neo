//---------------------------------------------------------------------------
//
//	DSC_ChannelStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The list of various flags used by the channel.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_CHANNEL_STATES_HPP_
#define _DSC_CHANNEL_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//channel internal state flags
#ifndef DSC_CHANNEL_STATE_FLAGS_DEFINED
#define DSC_CHANNEL_STATE_FLAGS_DEFINED
#define DSC_CHANNEL_STATE_FLAGS		UINT32
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ChannelStates {
/*!
	The list of various DSC_IChannel state flags.
*/
enum DSC_ChannelState_Tag {

	None							= 0x00000000,	/**< No flags set - must be 0! */

	Session_Handshake_Exchanged		= 0x00010000,	/**< The SDK and device are talking to each other */
	Incoming_Traffic_Encrypted		= 0x00020000,	/**< The incomming traffic from the device is encrypted */
	Outgoing_Traffic_Encrypted		= 0x00040000,	/**< The ougoing traffic to the device is encrypted */
	Product_Is_Supported			= 0x00080000,	/**< The peer device is supported by the SDK */

	Channel_Is_Closing				= 0x80000000	/**< The channel is closing */

}; }

#else

#define DSC_ChannelStates(value)	(DSC_E03_##value)
enum DSC_ChannelState_Tag {

	DSC_E03_None							= 0x00000000,	/**< No flags set - must be 0! */

	DSC_E03_Session_Handshake_Exchanged		= 0x00010000,	/**< The SDK and device are talking to each other */
	DSC_E03_Incoming_Traffic_Encrypted		= 0x00020000,	/**< The incomming traffic from the device is encrypted */
	DSC_E03_Outgoing_Traffic_Encrypted		= 0x00040000,	/**< The ougoing traffic to the device is encrypted */
	DSC_E03_Product_Is_Supported			= 0x00080000,	/**< The peer device is supported by the SDK */

	DSC_E03_Channel_Is_Closing				= 0x80000000	/**< The channel is closing */

};

#endif

/*!
	The DSC_ChannelState data type corresponds with the enum DSC_ChannelState_Tag.

	\sa enum DSC_ChannelState_Tag
*/
typedef DSC_ENUM_T DSC_ChannelState;

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_CHANNEL_STATES_HPP_
