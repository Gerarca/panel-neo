//---------------------------------------------------------------------------
//
//	DSC_PacketStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The list of data packet states used by the SDK.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PACKET_STATES_HPP_
#define _DSC_PACKET_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PacketStates {
/*!
	The list of various states of the protocol data packets used by the SDK.
*/
enum DSC_PacketState_Tag {

	Unknown			= 0,		/**< unknown - must be 0! */

	Created			= 1,		/**< the data container has been created */
	Received		= 2,		/**< new protocol data has been received */

	Rejected		= 10,		/**< the data cannot be processed right now	*/
	Waiting			= 11,		/**< the data is waiting to be processed later  */
	Sending			= 12,		/**< the data is being sent (pending the acknowledge) */

	Success			= 20,		/**< the data was sent and the ACK has been received */
	Timeout			= 21,		/**< the data sending has timed out (no ACK received) */
	Aborted			= 22,		/**< the data sending was aborted */
	Failure			= 23		/**< failed to send or process the protocol data */

}; }

#else

#define DSC_PacketStates(value)	(DSC_E06_##value)
enum DSC_PacketState_Tag {

	DSC_E06_Unknown			= 0,		/**< unknown - must be 0! */

	DSC_E06_Created			= 1,		/**< the data container has been created */
	DSC_E06_Received		= 2,		/**< new protocol data has been received */

	DSC_E06_Rejected		= 10,		/**< the data cannot be processed right now	*/
	DSC_E06_Waiting			= 11,		/**< the data is waiting to be processed later  */
	DSC_E06_Sending			= 12,		/**< the data is being sent (pending the acknowledge) */

	DSC_E06_Success			= 20,		/**< the data was sent and the ACKed has been received */
	DSC_E06_Timeout			= 21,		/**< the data sending has timed out (no ACK received) */
	DSC_E06_Aborted			= 22,		/**< the data sending was aborted */
	DSC_E06_Failure			= 23		/**< failed to send or process the protocol data */

};

#endif

/*!
	The DSC_PacketState data type corresponds with the enum DSC_PacketState_Tag.

	\sa enum DSC_PacketState_Tag
*/
typedef DSC_ENUM_T DSC_PacketState;

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PACKET_STATES_HPP_
