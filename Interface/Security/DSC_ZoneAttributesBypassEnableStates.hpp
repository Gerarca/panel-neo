//---------------------------------------------------------------------------
//
//	DSC_ZoneAttributesBypassEnableStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_ATTRIBUTES_BYPASS_ENABLE_STATES_HPP_
#define _DSC_ZONE_ATTRIBUTES_BYPASS_ENABLE_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneAttributesBypassEnableStates {
/*!
	The SDK provides access to Zone Bypass Attribute states as described below.

	Bypassing Zones intentionally unprotects specified points of protection while your
	system is Armed, and may be automatically reset each time the system is disarmed.
	Note, some zone types will specifically inhibit bypassing.
*/
enum DSC_ZoneAttributesBypassEnableState_Tag {
	
	//Default for all enums
	Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    BypassEnable_Enabled	= 1,	/**< Bypassing is permitted on this zone */
	BypassEnable_Disabled	= 2		/**< Bypassing is NOT permitted on this zone */	

}; }

#else

#define DSC_ZoneAttributesBypassEnableStates(value)	(DSC_E65_##value)
enum DSC_ZoneAttributesBypassEnableState_Tag {
	
	//Default for all enums
	DSC_E65_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E65_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E65_BypassEnable_Enabled	= 1,	/**< Bypassing is permitted on this zone */
	DSC_E65_BypassEnable_Disabled	= 2		/**< Bypassing is NOT permitted on this zone */	

};

#endif

/*!
	The DSC_ZoneAttributesBypassEnableState data type corresponds with the enum DSC_ZoneAttributesBypassEnableState_Tag.

	\sa enum DSC_ZoneAttributesBypassEnableState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneAttributesBypassEnableState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_ATTRIBUTES_BYPASS_ENABLE_STATES_HPP_
