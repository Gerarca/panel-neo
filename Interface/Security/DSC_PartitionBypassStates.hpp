//---------------------------------------------------------------------------
//
//	DSC_PartitionBypassStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_BYPASS_STATES_HPP_
#define _DSC_PARTITION_BYPASS_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionBypassStates {
/*!
	The SDK provides access to Partition Bypass States as described below.
*/
enum DSC_PartitionBypassState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    ZonesAreBypassed	= 1,	/**< One or more zones on the selected partition are in the bypassed state. */
    No_ZonesBypassed	= 2		/**< No zones on the selected partition are in the bypassed state. */

}; }

#else

#define DSC_PartitionBypassStates(value)	(DSC_E41_##value)
enum DSC_PartitionBypassState_Tag {
	
	//Default for all enums
	DSC_E41_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E41_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    DSC_E41_ZonesAreBypassed	= 1,	/**< One or more zones on the selected partition are in the bypassed state. */
    DSC_E41_No_ZonesBypassed	= 2		/**< No zones on the selected partition are in the bypassed state. */

};

#endif

/*!
	The DSC_PartitionBypassState data type corresponds with the enum DSC_PartitionBypassState_Tag.

	\sa enum DSC_PartitionBypassState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionBypassState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_BYPASS_STATES_HPP_
