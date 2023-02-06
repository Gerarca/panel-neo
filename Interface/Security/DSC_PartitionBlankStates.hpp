//---------------------------------------------------------------------------
//
//	DSC_PartitionBlankStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_BLANK_STATES_HPP_
#define _DSC_PARTITION_BLANK_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionBlankStates {
/*!
	The SDK provides access to Blank States as described below.

	Some products have a blanking option usually associated with the keypad. 
	Typical usage is for power saving mode(s), when required by some regulations, 
	or locking out users on a delinquent account.
*/
enum DSC_PartitionBlankState_Tag {

	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
		
	//Valid product values. 
	Blank				= 1,	/**< The product, usually a keypad, is Blanked out. */
    Not_Blank			= 2		/**< The product, usually a keypad, is functional / operating normally. */

}; }

#else

#define DSC_PartitionBlankStates(value)	(DSC_E38_##value)
enum DSC_PartitionBlankState_Tag {

	//Default for all enums
	DSC_E38_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E38_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
		
	//Valid product values. 
	DSC_E38_Blank				= 1,	/**< The product, usually a keypad, is Blanked out. */
    DSC_E38_Not_Blank			= 2		/**< The product, usually a keypad, is functional / operating normally. */

};

#endif

/*!
	The DSC_PartitionBlankState data type corresponds with the enum DSC_PartitionBlankState_Tag.

	\sa enum DSC_PartitionBlankState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionBlankState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_BLANK_STATES_HPP_
