//---------------------------------------------------------------------------
//
//	DSC_SecurityEventTypes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_SECURITY_EVENT_TYPES_HPP_
#define _DSC_SECURITY_EVENT_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_SecurityEventTypes {
/*!
	The SDK provides access to real time events by the “OnGeneralNotificationHandler” in DSC_ISecurityBase:

	Specifies the type of the event (the ‘minor’ selector in a ‘switch’ case for OnGeneralNotificationHandler).
*/
enum DSC_SecurityEventType_Tag {

	Unknown				= 0,	/**< Reserved value. */

	//category: Programming
	Programming						= 1,	/**< The notification event relates to programming. */

	//category: SystemState
	RemoteBufferOverload			= 1000,	/**< A remote Interactive Buffer Overload has occured. */
	TimeDate						= 1001,	/**< The system Time and Date has been changed or updated. */
	StateInfo						= 1002,	/**< The partition state information has changed. */
	AccessCodePartitionAssignments	= 1003,	/**< Access Code Partition Assignments have changed. */
	BuzzerType						= 1004,	/**< The buzzer type notification. */
	Assignment						= 1005,	/**< The assignment information has changed. */
	Trouble							= 1006,	/**< The trouble information has changed. */

	//category: VirtualKeypad
	KeyPressed						= 2000,	/**< The Virtual Keypad's key was pressed. */
	LCDUpdate						= 2001,	/**< The text on the Virtual Keypad's LCD has been updated. */
	LCDCursor						= 2002,	/**< The cursor position on the Virtual Keypad's LCD has been updated. */
	LEDStatus						= 2003,	/**< The status of the Virtual Keypad's LEDs has changed. */

	//category: CommandOutput
	CommandOutputUpdate             = 3000,	/**< The Command Output state has updated. */

	//category: EventBuffer
	EventBufferUpdate               = 4000  /**< Something was logged in the event buffer. */

}; }

#else

#define DSC_SecurityEventTypes(value)	(DSC_E53_##value)
enum DSC_SecurityEventType_Tag {

	DSC_E53_Unknown							= 0,	/**< Reserved value. */

	//category: Programming
	DSC_E53_Programming						= 1,	/**< The notification event relates to programming. */

	//category: SystemState
	DSC_E53_RemoteBufferOverload			= 1000,	/**< A remote Interactive Buffer Overload has occured. */
	DSC_E53_TimeDate						= 1001,	/**< The system Time and Date has been changed or updated. */
	DSC_E53_StateInfo						= 1002,	/**< The partition state information has changed. */
	DSC_E53_AccessCodePartitionAssignments	= 1003,	/**< Access Code Partition Assignments have changed. */
	DSC_E53_BuzzerType						= 1004,	/**< The buzzer type notification. */
	DSC_E53_Assignment						= 1005,	/**< An assignment information has changed. */

	//category: VirtualKeypad
	DSC_E53_KeyPressed						= 2000,	/**< The Virtual Keypad's key was pressed. */
	DSC_E53_LCDUpdate						= 2001,	/**< The text on the Virtual Keypad's LCD has been updated. */
	DSC_E53_LCDCursor						= 2002,	/**< The cursor position on the Virtual Keypad's LCD has been updated. */
	DSC_E53_LEDStatus						= 2003,	/**< The status of the Virtual Keypad's LEDs has changed. */

	//category: CommandOutput
	DSC_E53_CommandOutputUpdate             = 3000,	/**< The Command Output state has updated. */

	//category: EventBuffer
	DSC_E53_EventBufferUpdate               = 4000  /**< Something was logged in the event buffer. */

};

#endif

/*!
	The DSC_SecurityEventType data type corresponds with the enum DSC_SecurityEventType_Tag.

	\sa enum DSC_SecurityEventType_Tag
*/
typedef DSC_ENUM_T DSC_SecurityEventType;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_SECURITY_EVENT_TYPES_HPP_
