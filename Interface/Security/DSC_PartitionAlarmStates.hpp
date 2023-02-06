//---------------------------------------------------------------------------
//
//	DSC_PartitionAlarmStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_ALARM_STATES_HPP_
#define _DSC_PARTITION_ALARM_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionAlarmStates {
/*!
	The SDK provides access to Partition Alarm States as described below.
*/
enum DSC_PartitionAlarmState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    In_Alarm			= 1,	/**< The Partition is in alarm. */
    No_Alarm			= 2		/**< The Partition is not in alarm. */

}; }

#else

#define DSC_PartitionAlarmStates(value)	(DSC_E34_##value)
enum DSC_PartitionAlarmState_Tag {
	
	//Default for all enums
	DSC_E34_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E34_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    DSC_E34_In_Alarm			= 1,	/**< The Partition is in alarm. */
    DSC_E34_No_Alarm			= 2		/**< The Partition is not in alarm. */

};

#endif

/*!
	The DSC_PartitionAlarmState data type corresponds with the enum DSC_PartitionAlarmState_Tag.

	\sa enum DSC_PartitionAlarmState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionAlarmState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_ALARM_STATES_HPP_
