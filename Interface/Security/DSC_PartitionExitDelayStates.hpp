//---------------------------------------------------------------------------
//
//	DSC_PartitionExitDelayStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_EXIT_DELAY_STATES_HPP_
#define _DSC_PARTITION_EXIT_DELAY_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionExitDelayStates {
/*!
	The SDK provides access to Partition Exit Delay States as described below.
*/
enum DSC_PartitionExitDelayState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    Audible_Exit_Delay					= 1,	/**< Audible Exit Delay Is Active */
    Audible_Exit_Delay_With_Urgency		= 2,	/**< Audible Exit Delay Is Active and about to expire. */
	Infinite_Exit_Delay					= 3,    /**< Infinite Exit Delay Active */
	Silent_Exit_Delay 					= 4,	/**< Silent Exit Delay Is Active */
	Silent_Exit_Delay_With_Urgency     	= 5,    /**< Silent Exit Delay Is Active and about to expire. */

    Audible_Exit_Delay_Restarted				= 6,	/**< Audible Exit Delay Is Active and restarted */
    Audible_Exit_Delay_With_Urgency_Restarted	= 7,	/**< Audible Exit Delay Urgency Is Active and restarted */
	Silent_Exit_Delay_Restarted 				= 8,	/**< Silent Exit Delay Is Active and restarted */
	Silent_Exit_Delay_With_Urgency_Restarted    = 9,    /**< Silent Exit Delay With Urgency Is Active (while this doesn't make sense it indicates the last 10 seconds of exit delay) and restarted */

    No_Exit_Delay_Is_Active         	= 10  	/**< No Exit Delay is Active */

}; }

#else

#define DSC_PartitionExitDelayStates(value)	(DSC_E43_##value)
enum DSC_PartitionExitDelayState_Tag {
	
	//Default for all enums
	DSC_E43_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */
	DSC_E43_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    DSC_E43_Audible_Exit_Delay					= 1,	/**< Audible Exit Delay Is Active */
    DSC_E43_Audible_Exit_Delay_With_Urgency		= 2,	/**< Audible Exit Delay Is Active and about to expire. */
	DSC_E43_Infinite_Exit_Delay					= 3,    /**< Infinite Exit Delay Active */
	DSC_E43_Silent_Exit_Delay 					= 4,	/**< Silent Exit Delay Is Active */
	DSC_E43_Silent_Exit_Delay_With_Urgency     	= 5,    /**< Silent Exit Delay Is Active and about to expire. */

    DSC_E43_Audible_Exit_Delay_Restarted				= 6,	/**< Audible Exit Delay Is Active and restarted */
    DSC_E43_Audible_Exit_Delay_With_Urgency_Restarted	= 7,	/**< Audible Exit Delay Urgency Is Active and restarted */
	DSC_E43_Silent_Exit_Delay_Restarted 				= 8,	/**< Silent Exit Delay Is Active and restarted */
	DSC_E43_Silent_Exit_Delay_With_Urgency_Restarted    = 9,    /**< Silent Exit Delay With Urgency Is Active (while this doesn't make sense it indicates the last 10 seconds of exit delay) and restarted */

    DSC_E43_No_Exit_Delay_Is_Active         	= 10  	/**< No Exit Delay is Active */

};

#endif

/*!
	The DSC_PartitionExitDelayState data type corresponds with the enum DSC_PartitionExitDelayState_Tag.

	\sa enum DSC_PartitionExitDelayState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionExitDelayState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_ALARM_STATES_HPP_
