//---------------------------------------------------------------------------
//
//	DSC_PartitionBusyStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_BUSY_STATES_HPP_
#define _DSC_PARTITION_BUSY_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionBusyStates {
/*!
	The SDK provides access to Partition Busy States as described below.

	When a partition is in a busy state it is not accessible. 
	Partitions enter into a Busy state when they are placed into 
	any User function menu (Bypass, User function programming etc) 
	or Installers Programming mode. 
*/
	
enum DSC_PartitionBusyState_Tag {

	//Default for all enums
	Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    Partition_Is_Busy		= 1,	/**< The Partition is busy and is not accessible at this time. */
    Partition_Is_Not_Busy	= 2		/**< The Partition is not busy and in its normal operating state. */

}; }

#else

#define DSC_PartitionBusyStates(value)	(DSC_E39_##value)
enum DSC_PartitionBusyState_Tag {

	//Default for all enums
	DSC_E39_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E39_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    DSC_E39_Partition_Is_Busy		= 1,	/**< The Partition is busy and is not accessible at this time. */
    DSC_E39_Partition_Is_Not_Busy	= 2		/**< The Partition is not busy and in its normal operating state. */

};

#endif

/*!
	The DSC_PartitionBusyState data type corresponds with the enum DSC_PartitionBusyState_Tag.

	\sa enum DSC_PartitionBusyState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionBusyState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_BUSY_STATES_HPP_
