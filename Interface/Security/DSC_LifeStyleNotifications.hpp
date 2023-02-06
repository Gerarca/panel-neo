//---------------------------------------------------------------------------
//
//	DSC_LifeStyleNotifications.hpp
//  Copyright 2021 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_LIFESTYLE_NOTIFICATIONS_HPP_
#define _DSC_LIFESTYLE_NOTIFICATIONS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_LifeStyleNotifications {
/*!
	The SDK utilizes the LifeStyle Notifications as described below.
*/
enum DSC_LifeStyleNotifications_Tag {

	//Default for all enums
	Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	Panel_Event_Buffer								= 1,    /**< (0110) */
	Reserved1               						= 2,    /**< Reserved */
	Reserved2										= 3,    /**< Reserved */
	Time_Date										= 4,    /**< (0220) */
	Temperature										= 5,    /**< (0221) */
	Chime											= 6,    /**< (0223) */
	Exit_Delay										= 7,    /**< (0230) */
	Entry_Delay										= 8,    /**< (0231) */

	Arming_Disarming								= 9,    /**< (0232) */
	Arming_Prealert									= 10,   /**< (0233) */
	Access_Code_Length								= 11,   /**< (0236) */
	Partition_Quick_Exit							= 12,   /**< (0238) */
	Partition_Ready_Status							= 13,   /**< (0239) */
	System_Test										= 14,   /**< (023A) */
	Partition_Audible_Bell							= 15,   /**< (023B) */
	Partition_Alarm_Memory							= 16,   /**< (023C) */

	Miscellaneous_Prealert							= 17,   /**< (023D) */
	Partition_Blank_Status							= 18,   /**< (023E) */
	Partition_Trouble_Status						= 19,   /**< (023F) */
	Partition_Bypass_Status							= 20,   /**< (0240) */
	Partition_Busy_Status							= 21,   /**< (0241) */
	General_Activity								= 22,   /**< (0242) */
	Signal_Strength									= 23,   /**< (0243) */
	Command_Output_Activation						= 24,   /**< (0244) */

	Partition_Banner								= 25,   /**< (0245) */
	Partition_Buzzer								= 26,   /**< (0246) */
	Panel_Programming_Lead_In_Out					= 27,   /**< (0702) */
	Zone_Partition_Assignment_Configuration			= 28,   /**< (0770) */
	Configuration_Broadcast							= 29,   /**< (0771/ 0774) */
	Partition_Assignment_Configuration				= 30,   /**< (0772) */
	Virtual_Zone_Zone_Assignment_Configuration		= 31,   /**< (0773) */
	Zone_Multiple_Status							= 32,   /**< (0811) */

	Zone_Bypass_Status								= 33,   /**< (0813, 0820) */
	Door_Chime_Status								= 34,   /**< (0819) */
	Trouble_Detail_Notification						= 35,   /**< (0823) */
	Zone_Alarm										= 36,   /**< (0840) */
	Miscellaneous_Alarm								= 37,   /**< (0841) non-zone alarm */
	Key_Pressed_Notification						= 38,   /**< (0F01) */
	Reserved3										= 39,   /**< Reserved */
	Reserved4										= 40,   /**< Reserved */

	Firmware_Update_Status_Notification				= 41,   /**< (0306) */
	User_Configuration_Change						= 42,   /**< (0250) */
	User_Partition_Assignment_Configuration			= 43    /**< (0775) */

}; }

#else

#define DSC_LifeStyleNotifications(value)	(DSC_E78_##value)
enum DSC_LifeStyleNotifications_Tag {

	//Default for all enums
	DSC_E78_Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E78_Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E78_Panel_Event_Buffer								= 1,    /**< (0110) */
	DSC_E78_Reserved1               						= 2,    /**< Reserved */
	DSC_E78_Reserved2										= 3,    /**< Reserved */
	DSC_E78_Time_Date										= 4,    /**< (0220) */
	DSC_E78_Temperature										= 5,    /**< (0221) */
	DSC_E78_Chime											= 6,    /**< (0223) */
	DSC_E78_Exit_Delay										= 7,    /**< (0230) */
	DSC_E78_Entry_Delay										= 8,    /**< (0231) */

	DSC_E78_Arming_Disarming								= 9,    /**< (0232) */
	DSC_E78_Arming_Prealert									= 10,   /**< (0233) */
	DSC_E78_Access_Code_Length								= 11,   /**< (0236) */
	DSC_E78_Partition_Quick_Exit							= 12,   /**< (0238) */
	DSC_E78_Partition_Ready_Status							= 13,   /**< (0239) */
	DSC_E78_System_Test										= 14,   /**< (023A) */
	DSC_E78_Partition_Audible_Bell							= 15,   /**< (023B) */
	DSC_E78_Partition_Alarm_Memory							= 16,   /**< (023C) */

	DSC_E78_Miscellaneous_Prealert							= 17,   /**< (023D) */
	DSC_E78_Partition_Blank_Status							= 18,   /**< (023E) */
	DSC_E78_Partition_Trouble_Status						= 19,   /**< (023F) */
	DSC_E78_Partition_Bypass_Status							= 20,   /**< (0240) */
	DSC_E78_Partition_Busy_Status							= 21,   /**< (0241) */
	DSC_E78_General_Activity								= 22,   /**< (0242) */
	DSC_E78_Signal_Strength									= 23,   /**< (0243) */
	DSC_E78_Command_Output_Activation						= 24,   /**< (0244) */

	DSC_E78_Partition_Banner								= 25,   /**< (0245) */
	DSC_E78_Partition_Buzzer								= 26,   /**< (0246) */
	DSC_E78_Panel_Programming_Lead_In_Out					= 27,   /**< (0702) */
	DSC_E78_Zone_Partition_Assignment_Configuration			= 28,   /**< (0770) */
	DSC_E78_Configuration_Broadcast							= 29,   /**< (0771/ 0774) */
	DSC_E78_Partition_Assignment_Configuration				= 30,   /**< (0772) */
	DSC_E78_Virtual_Zone_Zone_Assignment_Configuration		= 31,   /**< (0773) */
	DSC_E78_Zone_Multiple_Status							= 32,   /**< (0811) */

	DSC_E78_Zone_Bypass_Status								= 33,   /**< (0813, 0820) */
	DSC_E78_Door_Chime_Status								= 34,   /**< (0819) */
	DSC_E78_Trouble_Detail_Notification						= 35,   /**< (0823) */
	DSC_E78_Zone_Alarm										= 36,   /**< (0840) */
	DSC_E78_Miscelanous_Alarm								= 37,   /**< (0841) non-zone alarm */
	DSC_E78_Key_Pressed_Notification						= 38,   /**< (0F01) */
	DSC_E78_Reserved3										= 39,   /**< Reserved */
	DSC_E78_Reserved4										= 40,   /**< Reserved */

	DSC_E78_Firmware_Update_Status_Notification				= 41,   /**< (0306) */
	DSC_E78_User_Configuration_Change						= 42,   /**< (0250) */
	DSC_E78_User_Partition_Assignment_Configuration			= 43    /**< (0775) */

};

#endif

/*!
	The DSC_LifeStyleNotification data type corresponds with the enum DSC_LifeStyleNotifications_Tag.

	\sa enum DSC_LifeStyleNotifications_Tag
*/
typedef DSC_ENUM_T DSC_LifeStyleNotification;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_LIFESTYLE_NOTIFICATIONS_HPP_
