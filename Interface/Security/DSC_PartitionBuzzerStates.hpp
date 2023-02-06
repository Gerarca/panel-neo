//---------------------------------------------------------------------------
//
//	DSC_PartitionBuzzerStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_BUZZER_TYPES_HPP_
#define _DSC_PARTITION_BUZZER_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionBuzzerStates {

/*!
	The SDK provides access to Partition Buzzer(s) audible states as described below.

	Note: in the descriptions below the term "beep" refers to a short on/off cadence approximately 100ms ON / 100ms OFF.
*/
enum DSC_PartitionBuzzerState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    Stop_Buzzer								= 1,	/**< Buzzer is silent */
    Trouble									= 2,	/**< 2 beeps every 10 seconds */
    Steady_Tone								= 3,	/**< Buzzer is a constant tone */
    Keypad_Ring_Back						= 4,	/**< 8 beeps */
    Walk_Test								= 5,	/**< 5 beeps every 10 seconds */
    Error_Short								= 6,	/**< 1 sec tone */
    Error									= 7,	/**< 2 sec tone */
    Error_Long								= 8,	/**< 3 sec tone */
    Error_Double							= 9,	/**< 4 sec tone */
    Single_ACK								= 10,	/**< 1 beep */
    Short_ACK								= 11,	/**< 2 beeps */
    ACK										= 12,	/**< 3 beeps */
    Long_ACK								= 13,	/**< 4 beeps */
    Double_ACK								= 14,	/**< 6 beeps */
    Entry_Delay_Normal						= 15,	/**< Steady tone */
    Entry_Delay_Alarm						= 16,	/**< Steady tone with 1 beep every second */
    Entry_Delay_Warning						= 17,	/**< Steady tone with 3 beeps every second */
    Entry_Delay_Alarm_Memory				= 18,	/**< Steady tone with 3 beeps every second */
    Exit_Delay_Normal						= 19,	/**< 1 beep every second */
    Exit_Delay_Warning						= 20,	/**< 3 beeps every second */
    Pendant_Test							= 21,	/**< 1 sec tone */
    Burglary_Alarm							= 22,	/**< Steady tone */
    Scheduled_Auto_Arming_PreAlert			= 23,	/**< Steady tone */
    No_Activity_Auto_Arming_PreAlert		= 24,	/**< Steady tone */
    Beep_Keypad_Via_DLS						= 25,	/**< 6 beeps */
    Chime_Pattern_0							= 26,	/**< 6 beeps chime pattern / Standard chime pattern(*) */
    Chime_Pattern_1							= 27,	/**< Bing-bing chime pattern */
    Chime_Pattern_2							= 28,	/**< Ding-ding chime pattern */
    Chime_Pattern_3							= 29,	/**< Alarming chime pattern */
    Urgent_Notification						= 30,	/**< Steady tone with 3 beeps every second */
    Urgent_Notification_With_Trouble		= 31,	/**< Steady tone with 2 beeps every 10 seconds */
    Exit_Delay_Normal_With_Alarm			= 32,	/**< Steady tone with 1 beep every second */
    Exit_Delay_Warning_With_Alarm			= 33,	/**< Steady tone with 3 beeps every second */
    Exit_Delay_Stay_Arm						= 34,	/**< 1 beep every 3 seconds */
    Exit_Delay_Stay_Alarm					= 35,	/**< Steady tone with 1 beep every 3 seconds */
    Exit_Delay_Stay_PreAlert				= 36,	/**< Steady tone with 1 beep every 3 seconds */
    Bus_Fault								= 37	/**< 1 sec tone every 2 seconds */

}; }

#else

#define DSC_PartitionBuzzerStates(value)	(DSC_E40_##value)
enum DSC_PartitionBuzzerState_Tag {
	
	//Default for all enums
	DSC_E40_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E40_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    DSC_E40_Stop_Buzzer							= 1,	/**< Buzzer is silent */
    DSC_E40_Trouble								= 2,	/**< 2 beeps every 10 seconds */
    DSC_E40_Steady_Tone							= 3,	/**< Buzzer is a constant tone */
    DSC_E40_Keypad_Ring_Back					= 4,	/**< 8 beeps */
    DSC_E40_Walk_Test							= 5,	/**< 5 beeps every 10 seconds */
    DSC_E40_Error_Short							= 6,	/**< 1 sec tone */
    DSC_E40_Error								= 7,	/**< 2 sec tone */
    DSC_E40_Error_Long							= 8,	/**< 3 sec tone */
    DSC_E40_Error_Double						= 9,	/**< 4 sec tone */
    DSC_E40_Single_ACK							= 10,	/**< 1 beep */
    DSC_E40_Short_ACK							= 11,	/**< 2 beeps */
    DSC_E40_ACK									= 12,	/**< 3 beeps */
    DSC_E40_Long_ACK							= 13,	/**< 4 beeps */
    DSC_E40_Double_ACK							= 14,	/**< 6 beeps */
    DSC_E40_Entry_Delay_Normal					= 15,	/**< Steady tone */
    DSC_E40_Entry_Delay_Alarm					= 16,	/**< Steady tone with 1 beep every second */
    DSC_E40_Entry_Delay_Warning					= 17,	/**< Steady tone with 3 beeps every second */
    DSC_E40_Entry_Delay_Alarm_Memory			= 18,	/**< Steady tone with 3 beeps every second */
    DSC_E40_Exit_Delay_Normal					= 19,	/**< 1 beep every second */
    DSC_E40_Exit_Delay_Warning					= 20,	/**< 3 beeps every second */
    DSC_E40_Pendant_Test						= 21,	/**< 1 sec tone */
    DSC_E40_Burglary_Alarm						= 22,	/**< Steady tone */
    DSC_E40_Scheduled_Auto_Arming_PreAlert		= 23,	/**< Steady tone */
    DSC_E40_No_Activity_Auto_Arming_PreAlert	= 24,	/**< Steady tone */
    DSC_E40_Beep_Keypad_Via_DLS					= 25,	/**< 6 beeps */
    DSC_E40_Chime_Pattern_0						= 26,	/**< 6 beeps chime pattern / Standard chime pattern(*) */
    DSC_E40_Chime_Pattern_1						= 27,	/**< Bing-bing chime pattern */
    DSC_E40_Chime_Pattern_2						= 28,	/**< Ding-ding chime pattern */
    DSC_E40_Chime_Pattern_3						= 29,	/**< Alarming chime pattern */
    DSC_E40_Urgent_Notification					= 30,	/**< Steady tone with 3 beeps every second */
    DSC_E40_Urgent_Notification_With_Trouble	= 31,	/**< Steady tone with 2 beeps every 10 seconds */
    DSC_E40_Exit_Delay_Normal_With_Alarm		= 32,	/**< Steady tone with 1 beep every second */
    DSC_E40_Exit_Delay_Warning_With_Alarm		= 33,	/**< Steady tone with 3 beeps every second */
    DSC_E40_Exit_Delay_Stay_Arm					= 34,	/**< 1 beep every 3 seconds */
    DSC_E40_Exit_Delay_Stay_Alarm				= 35,	/**< Steady tone with 1 beep every 3 seconds */
    DSC_E40_Exit_Delay_Stay_PreAlert			= 36,	/**< Steady tone with 1 beep every 3 seconds */
    DSC_E40_Bus_Fault							= 37	/**< 1 sec tone every 2 seconds */

};

#endif

/*!
	The DSC_PartitionBuzzerState data type corresponds with the enum DSC_PartitionBuzzerState_Tag.

	\sa enum DSC_PartitionBuzzerState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionBuzzerState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_BUZZER_TYPES_HPP_
