//---------------------------------------------------------------------------
//
//	DSC_PartitionEntryDelayStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_ENTRY_DELAY_STATES_HPP_
#define _DSC_PARTITION_ENTRY_DELAY_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionEntryDelayStates {
/*!
	The SDK provides access to Partition Entry Delay States as described below.
*/
enum DSC_PartitionEntryDelayState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
	Entry_Delay_Active 								= 1,	/**< Entry Delay is active. */
	Entry_Delay_With_Urgency 						= 2,	/**< Entry Delay is active and about to expire.  */
	Entry_Delay_With_Urgency_With_Alarms_In_Memory 	= 3,	/**< Entry Delay is active and about to expire. There were alarm events while armed. */
	No_Entry_Delay_Active 							= 4		/**< Entry Delay is NOT active. */

}; }

#else

#define DSC_PartitionEntryDelayStates(value)	(DSC_E42_##value)
enum DSC_PartitionEntryDelayState_Tag {
	
	//Default for all enums
	DSC_E42_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E42_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
	DSC_E42_Entry_Delay_Active 									= 1,	/**< Entry Delay is active. */
	DSC_E42_Entry_Delay_With_Urgency 							= 2,	/**< Entry Delay is active and about to expire.  */
	DSC_E42_Entry_Delay_With_Urgency_With_Alarms_In_Memory 		= 3,	/**< Entry Delay is active and about to expire. There were alarm events while armed. */
	DSC_E42_No_Entry_Delay_Active 								= 4		/**< Entry Delay is NOT active. */

};

#endif

/*!
	The DSC_PartitionEntryDelayState data type corresponds with the enum DSC_PartitionEntryDelayState_Tag.

	\sa enum DSC_PartitionEntryDelayState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionEntryDelayState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_ALARM_STATES_HPP_
