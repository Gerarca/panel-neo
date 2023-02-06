//---------------------------------------------------------------------------
//
//	DSC_AccessCodeAttributesSupervisorStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ACCESS_CODE_ATTRIBUTES_SUPERVISOR_STATES_HPP_
#define _DSC_ACCESS_CODE_ATTRIBUTES_SUPERVISOR_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_AccessCodeAttributesSupervisorStates {
/*!
	The SDK provides access to Supervisor code capabilities per Access Code as described below.

	Users with this attribute Enabled can access the [*][5] and [6] user code programming section for the partition they are assigned to.
	However, these codes can only program codes which have equal or lesser attribute levels.
*/
enum DSC_AccessCodeAttributesSupervisorState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    Supervisor_Enabled	= 1,	/**< Supervisor level access is Enabled. */	
	Supervisor_Disabled = 2		/**< Supervisor level access is Disabled. */	

}; }

#else

#define DSC_AccessCodeAttributesSupervisorStates(value)	(DSC_E25_##value)
enum DSC_AccessCodeAttributesSupervisorState_Tag {
	
	//Default for all enums
	DSC_E25_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E25_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E25_Supervisor_Enabled	= 1,	/**< Supervisor level access is Enabled. */	
	DSC_E25_Supervisor_Disabled = 2		/**< Supervisor level access is Disabled. */	

};

#endif

/*!
	The DSC_AccessCodeAttributesSupervisorState data type corresponds with the enum DSC_AccessCodeAttributesSupervisorState_Tag.

	\sa enum DSC_AccessCodeAttributesSupervisorState_Tag
*/
typedef DSC_ENUM_T DSC_AccessCodeAttributesSupervisorState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ACCESS_CODE_ATTRIBUTES_SUPERVISOR_STATES_HPP_
