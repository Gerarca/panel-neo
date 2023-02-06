//---------------------------------------------------------------------------
//
//	DSC_AssignmentTypes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ASSIGNMENT_TYPES_HPP_
#define _DSC_ASSIGNMENT_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_AssignmentTypes {
/*!
	These values are used to determine the type of assigment between 
	access codes and partitions, zones and partitions, or virtual zones and zones.
*/
enum DSC_AssignmentType_Tag {
	
	//Default for all enums
	Not_Available				= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown						= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
	Partition					= 1,	/**< This assignment type is used to determine whether or not a partition has been enabled. */
	AccessCode_Partition		= 2,	/**< This assignment type represents the assignment of an access code to a partition. */
	Zone_Partition				= 3,	/**< This assignment type represents the assignment of a zone to a partition. */
	VirtualZone_Zone			= 4		/**< This assignment type represents the assignment of a virtual zone to a zone.*/
}; }

#else

#define DSC_AssignmentTypes(value)	(DSC_E80_##value)
enum DSC_AssignmentType_Tag {
	
	//Default for all enums
	DSC_E80_Not_Available				= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E80_Unknown						= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
	DSC_E80_Partition					= 1,	/**< This assignment type is used to determine whether or not a partition has been enabled. */
	DSC_E80_AccessCode_Partition		= 2,	/**< This assignment type represents the assignment of an access code to a partition. */
	DSC_E80_Zone_Partition				= 3,	/**< This assignment type represents the assignment of a zone to a partition. */
	DSC_E80_VirtualZone_Zone			= 4		/**< This assignment type represents the assignment of a virtual zone to a zone.*/
};

#endif

/*!
	The DSC_AssignmentType data type corresponds with the enum DSC_AssignmentState_Tag.

	\sa enum DSC_AssignmentType_Tag
*/
typedef DSC_ENUM_T DSC_AssignmentType;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ASSIGNMENT_TYPES_HPP_
