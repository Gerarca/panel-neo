//---------------------------------------------------------------------------
//
//	DSC_ZoneAlarmStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_ALARM_STATES_HPP_
#define _DSC_ZONE_ALARM_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneAlarmStates {
/*!
	The SDK provides access to Zone Alarm states as described below.
*/
enum DSC_ZoneAlarmState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    Not_InAlarm			= 1,	/**< The Zone is NOT in an Alarm. */
	InAlarm				= 2		/**< The Zone is in an Alarm. */

}; }

#else

#define DSC_ZoneAlarmStates(value)	(DSC_E64_##value)
enum DSC_ZoneAlarmState_Tag {
	
	//Default for all enums
	DSC_E64_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E64_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E64_Not_InAlarm			= 1,	/**< The Zone is NOT in an Alarm. */
	DSC_E64_InAlarm				= 2		/**< The Zone is in an Alarm. */

};

#endif

/*!
	The DSC_ZoneAlarmState data type corresponds with the enum DSC_ZoneAlarmState_Tag.

	\sa enum DSC_ZoneAlarmState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneAlarmState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_ALARM_STATES_HPP_
