//---------------------------------------------------------------------------
//
//	DSC_VirtualZoneStatusMaskedStates.hpp
//  Copyright 2021 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_VIRTUAL_ZONE_STATUS_MASKED_STATES_HPP_
#define _DSC_VIRTUAL_ZONE_STATUS_MASKED_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_VirtualZoneStatusMaskedStates {
/*!
	The SDK provides access to Virtual Zone Status Masked States as described below.
*/
enum DSC_VirtualZoneStatusMaskedState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    Not_Masked			= 1,	/**< The Masked condition is NOT present. */
	Masked				= 2		/**< The Masked condition is present. */

}; }

#else

#define DSC_VirtualZoneStatusMaskedStates(value)	(DSC_E77_##value)
enum DSC_VirtualZoneStatusMaskedState_Tag {
	
	//Default for all enums
	DSC_E77_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E77_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E77_Not_Masked			= 1,	/**< The Masked condition is NOT present. */
	DSC_E77_Masked				= 2		/**< The Masked condition is present. */

};

#endif

/*!
	The DSC_VirtualZoneStatusMaskedState data type corresponds with the enum DSC_VirtualZoneStatusMaskedState_Tag.

	\sa enum DSC_VirtualZoneStatusMaskedState_Tag
*/
typedef DSC_ENUM_T DSC_VirtualZoneStatusMaskedState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_VIRTUAL_ZONE_STATUS_MASKED_STATES_HPP_
