//---------------------------------------------------------------------------
//
//	DSC_VirtualZoneStatusFaultStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_VIRTUAL_ZONE_STATUS_FAULT_STATES_HPP_
#define _DSC_VIRTUAL_ZONE_STATUS_FAULT_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_VirtualZoneStatusFaultStates {
/*!
	The SDK provides access to Virtual Zone Status Fault States as described below.
*/
enum DSC_VirtualZoneStatusFaultState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    No_Fault			= 1,	/**< The Fault condition is NOT present. */
	Fault				= 2		/**< The Fault condition is present. */

}; }

#else

#define DSC_VirtualZoneStatusFaultStates(value)	(DSC_E59_##value)
enum DSC_VirtualZoneStatusFaultState_Tag {
	
	//Default for all enums
	DSC_E59_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E59_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E59_No_Fault			= 1,	/**< The Fault condition is NOT present. */
	DSC_E59_Fault				= 2		/**< The Fault condition is present. */

};

#endif

/*!
	The DSC_VirtualZoneStatusFaultState data type corresponds with the enum DSC_VirtualZoneStatusFaultState_Tag.

	\sa enum DSC_VirtualZoneStatusFaultState_Tag
*/
typedef DSC_ENUM_T DSC_VirtualZoneStatusFaultState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_VIRTUAL_ZONE_STATUS_FAULT_STATES_HPP_
