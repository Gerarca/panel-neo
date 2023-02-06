//---------------------------------------------------------------------------
//
//	DSC_PartitionAudibleBellStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_AUDIBLE_BELL_STATES_HPP_
#define _DSC_PARTITION_AUDIBLE_BELL_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionAudibleBellStates {
/*!
	The SDK provides access to the bell output(s) audible states as described below.
*/
enum DSC_PartitionAudibleBellState_Tag {
	
	//Default for all enums
	Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
	Stopped					= 1,	/**< The bell is off / not audible. */
	Start_Or_In_Progress	= 2		/**< The bell is on / audible. */

}; }

#else

#define DSC_PartitionAudibleBellStates(value)	(DSC_E36_##value)
enum DSC_PartitionAudibleBellState_Tag {
	
	//Default for all enums
	DSC_E36_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E36_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
	DSC_E36_Stopped					= 1,	/**< The bell is off / not audible. */
	DSC_E36_Start_Or_In_Progress	= 2		/**< The bell is on / audible. */

};

#endif

/*!
	The DSC_PartitionAudibleBellState data type corresponds with the enum DSC_PartitionAudibleBellState_Tag.

	\sa enum DSC_PartitionAudibleBellState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionAudibleBellState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_AUDIBLE_BELL_STATES_HPP_
