//---------------------------------------------------------------------------
//
//	DSC_PartitionReadyStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_READY_STATES_HPP_
#define _DSC_PARTITION_READY_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionReadyStates {
/*!
	The SDK provides access to system / partition Ready states as described below.

	Used to determine if the selected Partition is ready to be armed.
	There are many reasons a System / Partition may not be ready to arm including, 
	but not limited to, Zones are open, Troubles present, or the Partition is in alarm.
*/
enum DSC_PartitionReadyState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    Ready				= 1,	/**< The selected Partition is ready to be armed / is in the ready state. */	
    Not_Ready			= 2		/**< The selected Partition is not ready to be armed / is not in the ready state. */	

}; }

#else

#define DSC_PartitionReadyStates(value)	(DSC_E45_##value)
enum DSC_PartitionReadyState_Tag {
	
	//Default for all enums
	DSC_E45_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E45_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E45_Ready				= 1,	/**< The selected Partition is ready to be armed / is in the ready state. */	
    DSC_E45_Not_Ready			= 2		/**< The selected Partition is not ready to be armed / is not in the ready state. */	

};

#endif

/*!
	The DSC_PartitionReadyState data type corresponds with the enum DSC_PartitionReadyState_Tag.

	\sa enum DSC_PartitionReadyState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionReadyState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_READY_STATES_HPP_
