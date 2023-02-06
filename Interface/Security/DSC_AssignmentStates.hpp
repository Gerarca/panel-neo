//---------------------------------------------------------------------------
//
//	DSC_AssignmentStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ASSIGNMENT_STATES_HPP_
#define _DSC_ASSIGNMENT_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_AssignmentStates {
/*!
	These values are used to determine the state of assigment between 
	access codes and partitions, zones and partitions, or virtual zones and zones.
*/
enum DSC_AssignmentState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    Assigned			= 1,	/**< The assignment is present. */	
	Unassigned			= 2		/**< There is no assignment present. */	
}; }

#else

#define DSC_AssignmentStates(value)	(DSC_E81_##value)
enum DSC_AssignmentState_Tag {
	
	//Default for all enums
	DSC_E81_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E81_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E81_Assigned			= 1,	/**< The assignment is present. */	
	DSC_E81_Unassigned			= 2		/**< There is no assignment present. */	
};

#endif

/*!
	The DSC_AssignmentState data type corresponds with the enum DSC_AssignmentState_Tag.

	\sa enum DSC_AssignmntState_Tag
*/
typedef DSC_ENUM_T DSC_AssignmentState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ASSIGNMENT_STATES_HPP_
