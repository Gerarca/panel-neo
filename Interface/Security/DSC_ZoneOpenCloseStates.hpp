//---------------------------------------------------------------------------
//
//	DSC_ZoneOpenCloseStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_OPEN_CLOSE_STATES_HPP_
#define _DSC_ZONE_OPEN_CLOSE_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneOpenCloseStates {
/*!
	The SDK provides access to Zone Open/Closed states as described below.

	Open and Closed states simplify all the detailed Zone States.
	For example a Zone protecting a door is in the open state when the door is open.
	The Zone protecting the door may or may not be in the alarm state based on the 
	present state of the Partition / System and / or the programming of the System.
*/
enum DSC_ZoneOpenCloseState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    ZoneClosed			= 1,	/**< The Zone is Closed / in its Restored state. */
	ZoneOpen			= 2		/**< The Zone is Open / in its Violated state. */

}; }

#else

#define DSC_ZoneOpenCloseStates(value)	(DSC_E72_##value)
enum DSC_ZoneOpenCloseState_Tag {
	
	//Default for all enums
	DSC_E72_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E72_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E72_ZoneClosed			= 1,	/**< The Zone is Closed / in its Restored state. */
	DSC_E72_ZoneOpen			= 2		/**< The Zone is Open / in its Violated state. */

};

#endif

/*!
	The DSC_ZoneOpenCloseState data type corresponds with the enum DSC_ZoneOpenCloseState_Tag.

	\sa enum DSC_ZoneOpenCloseState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneOpenCloseState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_OPEN_CLOSE_STATES_HPP_
