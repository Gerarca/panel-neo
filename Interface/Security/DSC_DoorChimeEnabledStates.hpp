//---------------------------------------------------------------------------
//
//	DSC_DoorChimeEnabledStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_DOOR_CHIME_ENABLED_STATES_HPP_
#define _DSC_DOOR_CHIME_ENABLED_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_DoorChimeEnabledStates {	
/*!
	The SDK provides access to Door Chime state options as described below.

	Used to interact with the present state of a Door Chime option 
*/
enum DSC_DoorChimeEnabledState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    Chime_Disabled		= 1,	/**< Used to Disable the Door Chime Option. */
	Chime_Enabled		= 2,	/**< Used to Enable the Door Chime Option. */
	Chime_Toggle        = 3		/**< Used to Toggle the Door Chime Option. */

}; }

#else

#define DSC_DoorChimeEnabledStates(value)	(DSC_E29_##value)
enum DSC_DoorChimeEnabledState_Tag {
	
	//Default for all enums
	DSC_E29_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E29_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E29_Chime_Disabled		= 1,	/**< Used to Disable the Door Chime Option. */
	DSC_E29_Chime_Enabled		= 2,	/**< Used to Enable the Door Chime Option. */
	DSC_E29_Chime_Toggle		= 3		/**< Used to Toggle the Door Chime Option. */

};

#endif

/*!
	The DSC_DoorChimeEnabledState data type corresponds with the enum DSC_DoorChimeEnabledState_Tag.

	\sa enum DSC_DoorChimeEnabledState_Tag
*/
typedef DSC_ENUM_T DSC_DoorChimeEnabledState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_DOOR_CHIME_ENABLED_STATES_HPP_
