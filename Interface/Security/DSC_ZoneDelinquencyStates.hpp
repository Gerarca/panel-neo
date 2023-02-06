//---------------------------------------------------------------------------
//
//	DSC_ZoneDelinquencyStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_DELINQUENCY_STATES_HPP_
#define _DSC_ZONE_DELINQUENCY_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneDelinquencyStates {
/*!
	The SDK provides access to Zone Delinquency states as described below.

	When the Delinquency option is on, this code is transmitted when 
	no zone activity has been detected on the system for the number of 
	hours programmed in Delinquency Transmission Delay.
*/
enum DSC_ZoneDelinquencyState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    No_Delinquency		= 1,	/**< The Zone is not in the Delinquency state. */
    Delinquency			= 2		/**< The Zone is in the Delinquency state. */

}; }

#else

#define DSC_ZoneDelinquencyStates(value)	(DSC_E68_##value)
enum DSC_ZoneDelinquencyState_Tag {
	
	//Default for all enums
	DSC_E68_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E68_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E68_No_Delinquency		= 1,	/**< The Zone is not in the Delinquency state. */
    DSC_E68_Delinquency			= 2		/**< The Zone is in the Delinquency state. */

};

#endif

/*!
	The DSC_ZoneDelinquencyState data type corresponds with the enum DSC_ZoneDelinquencyState_Tag.

	\sa enum DSC_ZoneDelinquencyState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneDelinquencyState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_DELINQUENCY_STATES_HPP_
