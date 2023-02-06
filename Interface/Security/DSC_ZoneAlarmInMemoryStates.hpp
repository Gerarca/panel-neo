//---------------------------------------------------------------------------
//
//	DSC_ZoneAlarmInMemoryStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_ALARM_IN_MEMORY_STATES_HPP_
#define _DSC_ZONE_ALARM_IN_MEMORY_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneAlarmInMemoryStates {
/*!
	The SDK provides access to Alarm Memory states as described below.

	If an alarm, tamper or fault event occurred during the last armed period or while the panel was disarmed 
	(for 24 hour zones). Press [*][3] to view zones in alarm memory. To clear the memory, arm and disarm the system.
*/
enum DSC_ZoneAlarmInMemoryState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    Alarm_In_Memory		= 1,	/**< The system has alarm(s) in memory. */
    No_Alarm_In_Memory	= 2		/**< The system does not have any alarms in memory. */

}; }

#else

#define DSC_ZoneAlarmInMemoryStates(value)	(DSC_E63_##value)
enum DSC_ZoneAlarmInMemoryState_Tag {
	
	//Default for all enums
	DSC_E63_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E63_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    DSC_E63_Alarm_In_Memory		= 1,	/**< The system has alarm(s) in memory. */
    DSC_E63_No_Alarm_In_Memory	= 2		/**< The system does not have any alarms in memory. */

};

#endif

/*!
	The DSC_ZoneAlarmInMemoryState data type corresponds with the enum DSC_ZoneAlarmInMemoryState_Tag.

	\sa enum DSC_ZoneAlarmInMemoryState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneAlarmInMemoryState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_ALARM_IN_MEMORY_STATES_HPP_
