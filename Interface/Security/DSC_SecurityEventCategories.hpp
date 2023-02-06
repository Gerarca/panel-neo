//---------------------------------------------------------------------------
//
//	DSC_SecurityEventCategories.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_SECURITY_EVENT_CATEGORIES_HPP_
#define _DSC_SECURITY_EVENT_CATEGORIES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_SecurityEventCategories {
/*!
	The SDK provides access to real time events by the “OnGeneralNotificationHandler” in DSC_ISecurityBase:

	Specifies the type of the event (the ‘major’ selector in a ‘switch’ case for OnGeneralNotificationHandler).
*/
enum DSC_SecurityEventCategory_Tag {

	Unknown				    = 0,	/**< Reserved value. */

	Programming			    = 1,	/**< The notification event relates to programming of the security system. */
	SystemState			    = 2,	/**< The notification event relates to the current state of the security system. */
	VirtualKeypad		    = 3,	/**< The notification event relates to the functionality of the virtual keypad. */
	CommandOutput           = 4,    /**< The notification event relates to the functionality of the command output. */
	DeviceModule			= 5,	/**< The notification event relates to the physical device or hardware module. */
	EventBuffer             = 6     /**< The notification event relates to the event buffer. */

}; }

#else

#define DSC_SecurityEventCategories(value)	(DSC_E52_##value)
enum DSC_SecurityEventCategory_Tag {

	DSC_E52_Unknown		        	= 0,	/**< Reserved value. */

	DSC_E52_Programming	        	= 1,	/**< The notification event relates to programming of the security system. */
	DSC_E52_SystemState	        	= 2,	/**< The notification event relates to the current state of the security system. */
	DSC_E52_VirtualKeypad       	= 3,	/**< The notification event relates to the functionality of the virtual keypad. */
	DSC_E52_CommandOutput       	= 4,	/**< The notification event relates to the functionality of the command output. */
	DSC_E52_EventBuffer             = 5     /**< The notification event relates to the event buffer. */

};

#endif

/*!
	The DSC_SecurityEventCategory data type corresponds with the enum DSC_SecurityEventCategory_Tag.

	\sa enum DSC_SecurityEventCategory_Tag
*/
typedef DSC_ENUM_T DSC_SecurityEventCategory;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_SECURITY_EVENT_CATEGORIES_HPP_
