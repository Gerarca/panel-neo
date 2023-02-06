//---------------------------------------------------------------------------
//
//	DSC_ZoneFaultStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_FAULT_STATES_HPP_
#define _DSC_ZONE_FAULT_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneFaultStates {
/*!
	The SDK provides access to Zone Fault states as described below.

	For hard wired Zones using Double-End-of-Line (DEOL) resistors 
	allow detection of zone faults (shorted zone).
	Typical usage is to detect short circuits in a Zones wiring. For example, 
	a nail for a picture frame has shorted out wires behind the drywall.
	For some wireless devices, a zone Fault may be indicated where the zone has 
	failed to report a Supervisory signal within the programmed Supervisory Window.
*/
enum DSC_ZoneFaultState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    No_Fault			= 1,	/**< The Zone is functioning properly. */
	Fault				= 2		/**< The Zone is in the Fault State. */

}; }

#else

#define DSC_ZoneFaultStates(value)	(DSC_E69_##value)
enum DSC_ZoneFaultState_Tag {
	
	//Default for all enums
	DSC_E69_Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E69_Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E69_No_Fault		= 1,	/**< The Zone is functioning properly. */
	DSC_E69_Fault			= 2		/**< The Zone is in the Fault State. */

};

#endif

/*!
	The DSC_ZoneFaultState data type corresponds with the enum DSC_ZoneFaultState_Tag.

	\sa enum DSC_ZoneFaultState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneFaultState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_FAULT_STATES_HPP_
