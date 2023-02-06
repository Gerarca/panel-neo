//---------------------------------------------------------------------------
//
//	DSC_ZoneLowSensitivityStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_LOW_SENSITIVITY_STATES_HPP_
#define _DSC_ZONE_LOW_SENSITIVITY_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneLowSensitivityStates {
/*!
	The SDK provides access to Zone Low Sensitivity states as described below.

	This is provided to indicate a wireless Smoke/Fire sensor may not be functioning properly. 
*/
enum DSC_ZoneLowSensitivityState_Tag {
	
	//Default for all enums
	Not_Available				= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown						= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    No_LowSensitivityTrouble	= 1,	/**< The Zone is functioning properly. */
	LowSensitivityTrouble		= 2		/**< The Zone is in a Low Sensitivity state. */

}; }

#else

#define DSC_ZoneLowSensitivityStates(value)	(DSC_E71_##value)
enum DSC_ZoneLowSensitivityState_Tag {
	
	//Default for all enums
	DSC_E71_Not_Available				= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E71_Unknown						= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E71_No_LowSensitivityTrouble	= 1,	/**< The Zone is functioning properly. */
	DSC_E71_LowSensitivityTrouble		= 2		/**< The Zone is in a Low Sensitivity state. */

};

#endif

/*!
	The DSC_ZoneLowSensitivityState data type corresponds with the enum DSC_ZoneLowSensitivityState_Tag.

	\sa enum DSC_ZoneLowSensitivityState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneLowSensitivityState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_LOW_SENSITIVITY_STATES_HPP_
