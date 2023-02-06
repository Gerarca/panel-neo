//---------------------------------------------------------------------------
//
//	DSC_VirtualZoneStatusOpenStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_VIRTUAL_ZONE_STATUS_OPEN_STATES_HPP_
#define _DSC_VIRTUAL_ZONE_STATUS_OPEN_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_VirtualZoneStatusOpenStates {
/*!
	The SDK provides access to Virtual Zone Status Open States as described below.
*/
enum DSC_VirtualZoneStatusOpenState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    Closed				= 1,	/**< The Zone is Closed / Restored. */
	Opened				= 2		/**< The Zone is Open. */

}; }

#else

#define DSC_VirtualZoneStatusOpenStates(value)	(DSC_E61_##value)
enum DSC_VirtualZoneStatusOpenState_Tag {
	
	//Default for all enums
	DSC_E61_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E61_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E61_Closed				= 1,	/**< The Zone is Closed / Restored. */
	DSC_E61_Opened				= 2		/**< The Zone is Open. */

};

#endif

/*!
	The DSC_VirtualZoneStatusOpenState data type corresponds with the enum DSC_VirtualZoneStatusOpenState_Tag.

	\sa enum DSC_VirtualZoneStatusOpenState_Tag
*/
typedef DSC_ENUM_T DSC_VirtualZoneStatusOpenState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_VIRTUAL_ZONE_STATUS_OPEN_STATES_HPP_
