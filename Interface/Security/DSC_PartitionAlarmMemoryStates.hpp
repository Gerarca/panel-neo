//---------------------------------------------------------------------------
//
//	DSC_PartitionAlarmMemoryStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_ALARM_MEMORY_STATES_HPP_
#define _DSC_PARTITION_ALARM_MEMORY_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionAlarmMemoryStates {
/*!
	The SDK provides access to Alarm Memory states as described below.

	If an alarm, tamper or fault event occurred during the last armed period or while the panel was disarmed 
	(for 24 hour zones). Alarm memory is usually cleared by reading the Alarm Memory Status or by arming and disarming the System.
*/
enum DSC_PartitionAlarmMemoryState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    Alarm_In_Memory		= 1,	/**< Partition alarm(s) are in memory. */
    No_Alarm_In_Memory	= 2		/**< No Alarm(s) are in memory for this Partition. */

}; }

#else

#define DSC_PartitionAlarmMemoryStates(value)	(DSC_E33_##value)
enum DSC_PartitionAlarmMemoryState_Tag {
	
	//Default for all enums
	DSC_E33_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E33_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    DSC_E33_Alarm_In_Memory		= 1,	/**< Partition alarm(s) are in memory. */
    DSC_E33_No_Alarm_In_Memory	= 2		/**< No Alarm(s) are in memory for this Partition. */

};

#endif

/*!
	The DSC_PartitionAlarmMemoryState data type corresponds with the enum DSC_PartitionAlarmMemoryState_Tag.

	\sa enum DSC_PartitionAlarmMemoryState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionAlarmMemoryState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_ALARM_MEMORY_STATES_HPP_
