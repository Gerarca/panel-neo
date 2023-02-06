//---------------------------------------------------------------------------
//
//	DSC_AccessCodeAttributesCanBypassZoneStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ACCESS_CODE_ATTRIBUTES_CAN_BYPASS_ZONE_STATES_HPP_
#define _DSC_ACCESS_CODE_ATTRIBUTES_CAN_BYPASS_ZONE_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_AccessCodeAttributesCanBypassZoneStates {
/*!
	The SDK provides access to Zone Bypass capabilities per Access Code as described below.

	Bypassing Zones intentionally unprotects specified points of protection the next time your system is armed.
*/
enum DSC_AccessCodeAttributesCanBypassZoneState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    CanBypassZone_Enabled = 1,	/**< The Access Code is allowed to Bypass Zones. */	
	CanBypassZone_Disabled = 2	/**< The Access Code is NOT allowed to Bypass Zones. */	

}; }

#else

#define DSC_AccessCodeAttributesCanBypassZoneStates(value)	(DSC_E21_##value)
enum DSC_AccessCodeAttributesCanBypassZoneState_Tag {
	
	//Default for all enums
	DSC_E21_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E21_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E21_CanBypassZone_Enabled	= 1,	/**< The Access Code is allowed to Bypass Zones. */	
	DSC_E21_CanBypassZone_Disabled	= 2		/**< The Access Code is NOT allowed to Bypass Zones. */	

};

#endif

/*!
	The DSC_AccessCodeAttributesCanBypassZoneState data type corresponds with the enum DSC_AccessCodeAttributesCanBypassZoneState_Tag.

	\sa enum DSC_AccessCodeAttributesCanBypassZoneState_Tag
*/
typedef DSC_ENUM_T DSC_AccessCodeAttributesCanBypassZoneState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ACCESS_CODE_ATTRIBUTES_CAN_BYPASS_ZONE_STATES_HPP_
