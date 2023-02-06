//---------------------------------------------------------------------------
//
//	DSC_PartitionArmedStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_ARMED_STATES_HPP_
#define _DSC_PARTITION_ARMED_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionArmedStates {
/*!
	The SDK provides multiple arming modes as described below.

	Note: Verify with your alarm company which modes are available on your system. 
	For SIA FAR listed panels, the Stay Arming Exit Delay will be twice as long as the Away Arming Exit Delay.
	Depending on your system configuration, there are multiple methods you can use to arm your system.
*/
enum DSC_PartitionArmedState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    Disarmed			= 1,		/**< All sensors/zones, except 24 Hour zone types, are not active. */
    StayArmed			= 2,		/**< Use this mode when you are staying home, but expect someone to use the entrance door later. Stay mode partially activates your alarm system by arming all perimeter sensors and bypassing all interior sensors. */
    AwayArmed			= 3,		/**< Use when no one in your household will be home. Away mode activates all perimeter and interior sensors. */
	StayArmedWithNoEntryDelay = 4,	/**< No-Entry Arming the system in Stay mode but eliminates Entry Delay. An entry through any delay zone will create an instant alarm . */
	AwayArmedWithNoEntryDelay = 5,	/**< No-Entry Arming the system in Away mode but eliminates Entry Delay. An entry through any delay zone will create an instant alarm . */
    NightModeArmed		= 6,		/**< Use when you want the perimeter and interior armed but would like to allow limited movement in your house without activating the alarm. (e.g., disable motion sensors in an area containing bedrooms and a washroom). Night mode is similar to Stay mode but only bypasses internal sensors configured as Night Zones. */
	InteriorArmed       = 7,		/**< Toggle from stay to away mode. Allows the interior zones to be armed without disarming the partition. */
	UserArmed           = 8			/**< This mode is processed by the panel in the same manner as entering an access code on a partition keypad.  When sent, the UserArm function will Arm the system with interior sensors bypassed unless a user exits via an entry / exit point. If there are no Stay/Away zones on the system, it will arm in Away Mode. */

}; }

#else

#define DSC_PartitionArmedStates(value)	(DSC_E35_##value)
enum DSC_PartitionArmedState_Tag {
	
	//Default for all enums
	DSC_E35_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E35_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    DSC_E35_Disarmed			= 1,		/**< All sensors/zones, except 24 Hour zone types, are not active. */
    DSC_E35_StayArmed			= 2,		/**< Use this mode when you are staying home, but expect someone to use the entrance door later. Stay mode partially activates your alarm system by arming all perimeter sensors and bypassing all interior sensors. */
    DSC_E35_AwayArmed			= 3,		/**< Use when no one in your household will be home. Away mode activates all perimeter and interior sensors. */
	DSC_E35_StayArmedWithNoEntryDelay = 4,	/**< No-Entry Arming the system in Stay mode but eliminates Entry Delay. An entry through any delay zone will create an instant alarm . */
	DSC_E35_AwayArmedWithNoEntryDelay = 5,	/**< No-Entry Arming the system in Away mode but eliminates Entry Delay. An entry through any delay zone will create an instant alarm . */
    DSC_E35_NightModeArmed		= 6,		/**< Use when you want the perimeter and interior armed but would like to allow limited movement in your house without activating the alarm. (e.g., disable motion sensors in an area containing bedrooms and a washroom). Night mode is similar to Stay mode but only bypasses internal sensors configured as Night Zones. */
	DSC_E35_InteriorArmed       = 7,		/**< Toggle from stay to away mode. Allows the interior zones to be armed without disarming the partition. */
	DSC_E35_UserArmed			= 8			/**< This mode is processed by the panel in the same manner as entering an access code on a partition keypad.  When sent, the UserArm function will Arm the system with interior sensors bypassed unless a user exits via an entry / exit point. If there are no Stay/Away zones on the system, it will arm in Away Mode. */

};

#endif

/*!
	The DSC_PartitionArmedState data type corresponds with the enum DSC_PartitionArmedState_Tag.

	\sa enum DSC_PartitionArmedState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionArmedState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_ARMED_STATES_HPP_
