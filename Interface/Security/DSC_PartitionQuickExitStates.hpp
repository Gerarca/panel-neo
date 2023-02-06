//---------------------------------------------------------------------------
//
//	DSC_PartitionQuickExitStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_QUICK_EXIT_STATES_HPP_
#define _DSC_PARTITION_QUICK_EXIT_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionQuickExitStates {
/*!
	The SDK provides access to Quick Exit states as described below.

	When the system is armed, users may enter the Quick Exit command to temporarily bypass a single 
	Delay 1 or Delay 2 zone to exit the premises. Only one delay zone may be activated. Activity on another 
	delay zone initiates the appropriate alarm sequence.
*/
enum DSC_PartitionQuickExitState_Tag {
	
	//Default for all enums
	Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    QuickExitStopped		= 1,	/**< Quick Exit functionality is not active. */
    QuickExitInProgress		= 2		/**< Quick Exit functionality is active. */

}; }

#else

#define DSC_PartitionQuickExitStates(value)	(DSC_E44_##value)
enum DSC_PartitionQuickExitState_Tag {
	
	//Default for all enums
	DSC_E44_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E44_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E44_QuickExitStopped		= 1,	/**< Quick Exit functionality is not active. */
    DSC_E44_QuickExitInProgress		= 2		/**< Quick Exit functionality is active. */

};

#endif

/*!
	The DSC_PartitionQuickExitState data type corresponds with the enum DSC_PartitionQuickExitState_Tag.

	\sa enum DSC_PartitionQuickExitState_Tag
*/
typedef DSC_ENUM_T DSC_PartitionQuickExitState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_QUICK_EXIT_STATES_HPP_
