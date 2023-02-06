//---------------------------------------------------------------------------
//
//	DSC_ZoneBypassStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_BYPASS_STATES_HPP_
#define _DSC_ZONE_BYPASS_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneBypassStates {
/*!
	The SDK provides access to Zone Bypass states as described below.

	Bypassing Zones intentionally unprotects specified points of protection the next time your system is armed.
*/
enum DSC_ZoneBypassState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    Not_Bypassed		= 1,	/**< The Zone is not in a Bypassed State. */	
	Bypassed			= 2		/**< The Zone is in the Bypassed State. */	

}; }

#else

#define DSC_ZoneBypassStates(value)	(DSC_E67_##value)
enum DSC_ZoneBypassState_Tag {
	
	//Default for all enums
	DSC_E67_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E67_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E67_Not_Bypassed		= 1,	/**< The Zone is not in a Bypassed State. */	
	DSC_E67_Bypassed			= 2		/**< The Zone is in the Bypassed State. */	

};

#endif

/*!
	The DSC_ZoneBypassState data type corresponds with the enum DSC_ZoneBypassState_Tag.

	\sa enum DSC_ZoneBypassState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneBypassState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_BYPASS_STATES_HPP_
