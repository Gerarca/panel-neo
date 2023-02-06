//---------------------------------------------------------------------------
//
//	DSC_ZoneLowBatteryStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_LOW_BATTERY_STATES_HPP_
#define _DSC_ZONE_LOW_BATTERY_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneLowBatteryStates {
/*!
	The SDK provides access to Zone Low Battery states as described below.
*/
enum DSC_ZoneLowBatteryState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    No_LowBattery		= 1,	/**< The Zone's Battery is functioning properly. */
	LowBattery			= 2		/**< The Zone's Battery is Low and should be replaced. */

}; }

#else

#define DSC_ZoneLowBatteryStates(value)	(DSC_E70_##value)
enum DSC_ZoneLowBatteryState_Tag {
	
	//Default for all enums
	DSC_E70_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E70_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E70_No_LowBattery		= 1,	/**< The Zone's Battery is functioning properly. */
	DSC_E70_LowBattery			= 2		/**< The Zone's Battery is Low and should be replaced. */

};

#endif

/*!
	The DSC_ZoneLowBatteryState data type corresponds with the enum DSC_ZoneLowBatteryState_Tag.

	\sa enum DSC_ZoneLowBatteryState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneLowBatteryState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_LOW_BATTERY_STATES_HPP_
