//---------------------------------------------------------------------------
//
//	DSC_ZoneTamperStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_TAMPER_STATES_HPP_
#define _DSC_ZONE_TAMPER_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneTamperStates {
/*!
	The SDK provides access to Zone Tamper states as described below.

	For hard wired Zones using Double-End-of-Line (DEOL) resistors allows detection of zone tampers (open zone).
	Typical usage is to detect open/broken circuits in a Zones wiring. Example, a nail for a picture frame has broken/opened the wires behind the drywall.
	For Wireless devices, this indicates that the device housing / cover has been opened.
*/
enum DSC_ZoneTamperState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    No_TamperPresent	= 1,	/**< The Zone is functioning properly. */
	TamperPresent		= 2		/**< The Zone is in the Tamper State. */

}; }

#else

#define DSC_ZoneTamperStates(value)	(DSC_E73_##value)
enum DSC_ZoneTamperState_Tag {
	
	//Default for all enums
	DSC_E73_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E73_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E73_No_TamperPresent	= 1,	/**< The Zone is functioning properly. */
	DSC_E73_TamperPresent		= 2		/**< The Zone is in the Tamper State. */

};

#endif

/*!
	The DSC_ZoneTamperState data type corresponds with the enum DSC_ZoneTamperState_Tag.

	\sa enum DSC_ZoneTamperState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneTamperState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_TAMPER_STATES_HPP_
