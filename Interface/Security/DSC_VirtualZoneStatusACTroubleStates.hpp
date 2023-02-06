//---------------------------------------------------------------------------
//
//	DSC_VirtualZoneStatusACTroubleStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_VIRTUAL_ZONE_STATUS_AC_TROUBLE_STATES_HPP_
#define _DSC_VIRTUAL_ZONE_STATUS_AC_TROUBLE_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_VirtualZoneStatusACTroubleStates {
/*!
	The SDK provides access to Virtual Zone Status AC Trouble States as described below.
*/
enum DSC_VirtualZoneStatusACTroubleState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    No_AC_Trouble		= 1,	/**< The Trouble condition is NOT present. */
	AC_Trouble			= 2		/**< The Trouble condition is present. */

}; }

#else

#define DSC_VirtualZoneStatusACTroubleStates(value)	(DSC_E58_##value)
enum DSC_VirtualZoneStatusACTroubleState_Tag {
	
	//Default for all enums
	DSC_E58_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E58_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E58_No_AC_Trouble		= 1,	/**< The Trouble condition is NOT present. */
	DSC_E58_AC_Trouble			= 2		/**< The Trouble condition is present. */

};

#endif

/*!
	The DSC_VirtualZoneStatusACTroubleState data type corresponds with the enum DSC_VirtualZoneStatusACTroubleState_Tag.

	\sa enum DSC_VirtualZoneStatusACTroubleState_Tag
*/
typedef DSC_ENUM_T DSC_VirtualZoneStatusACTroubleState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_VIRTUAL_ZONE_STATUS_AC_TROUBLE_STATES_HPP_
