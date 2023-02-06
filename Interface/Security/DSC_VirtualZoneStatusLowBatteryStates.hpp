//---------------------------------------------------------------------------
//
//	DSC_VirtualZoneStatusLowBatteryStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_VIRTUAL_ZONE_STATUS_LOW_BATTERY_STATES_HPP_
#define _DSC_VIRTUAL_ZONE_STATUS_LOW_BATTERY_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_VirtualZoneStatusLowBatteryStates {
/*!
	The SDK provides access to Virtual Zone Status Low Battery States as described below.
*/
enum DSC_VirtualZoneStatusLowBatteryState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    No_Low_Battery		= 1,	/**< The Low Battery condition is NOT present. */
	Low_Battery			= 2		/**< The Low Battery condition is present. */

}; }

#else

#define DSC_VirtualZoneStatusLowBatteryStates(value)	(DSC_E60_##value)
enum DSC_VirtualZoneStatusLowBatteryState_Tag {
	
	//Default for all enums
	DSC_E60_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E60_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E60_No_Low_Battery		= 1,	/**< The Low Battery condition is NOT present. */
	DSC_E60_Low_Battery			= 2		/**< The Low Battery condition is present. */

};

#endif

/*!
	The DSC_VirtualZoneStatusLowBatteryState data type corresponds with the enum DSC_VirtualZoneStatusLowBatteryState_Tag.

	\sa enum DSC_VirtualZoneStatusLowBatteryState_Tag
*/
typedef DSC_ENUM_T DSC_VirtualZoneStatusLowBatteryState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_VIRTUAL_ZONE_STATUS_LOW_BATTERY_STATES_HPP_
