//---------------------------------------------------------------------------
//
//	DSC_PartitionTroubleStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_TROUBLE_STATES_HPP_
#define _DSC_PARTITION_TROUBLE_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionTroubleStates {
/*!
	The SDK provides access to Partition level Trouble states as described below.

	Used to determin if the selected Partition has Trouble(s) present.
	There are many trouble(s) that can be present on a partition, see 
	the DSC_SystemTroubleTypes for a list of potential troubles.
*/
enum DSC_PartitionTroubleState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    TroublesPresent		= 1,	/**< The selected partition has one or more trouble condition(s) present. */
    No_TroublesPresent	= 2		/**< The selected partition has no trouble conditions present. */

}; }

#else

#define DSC_PartitionTroubleStates(value)	(DSC_E46_##value)
enum DSC_PartitionTroubleState_Tag {
	
	//Default for all enums
	DSC_E46_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E46_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E46_TroublesPresent			= 1,	/**< The selected partition has one or more trouble condition(s) present. */
    DSC_E46_No_TroublesPresent		= 2		/**< The selected partition has no trouble conditions present. */

};

#endif

/*!
	The DSC_PartitionTroubleState data type corresponds with the enum DSC_PartitionTroubleState_Tag.

	\sa enum DSC_PartitionTroubleState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionTroubleState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_TROUBLE_STATES_HPP_
