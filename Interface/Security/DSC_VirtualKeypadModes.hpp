//---------------------------------------------------------------------------
//
//	DSC_VirtualKeypadModes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_VIRTUAL_KEYPAD_MODES_HPP_
#define _DSC_VIRTUAL_KEYPAD_MODES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_VirtualKeypadModes {
/*!
	The SDK supports various Virtual Keypad modes as described below.
*/
enum DSC_VirtualKeypadMode_Tag {

	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	Disabled	= 1,	/**< This value indicates that the Virtual Keypad is disabled. */
	Monitor		= 2,	/**< This value indicates that the Virtual Keypad is used for monitoring only. The key presses are ignored. */
	Emulator	= 3		/**< This value indicates that the Virtual Keypad is fully enabled (including the key presses). */

}; }

#else

#define DSC_VirtualKeypadModes(value)	(DSC_E56_##value)
enum DSC_VirtualKeypadMode_Tag {

	//Default for all enums
	DSC_E56_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E56_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E56_Disabled			= 1,	/**< This value indicates that the Virtual Keypad is disabled. */
	DSC_E56_Monitor				= 2,	/**< This value indicates that the Virtual Keypad is used for monitoring only. The key presses are ignored. */
	DSC_E56_Emulator			= 3		/**< This value indicates that the Virtual Keypad is fully enabled (including the key presses). */

};

#endif

/*!
	The DSC_VirtualKeypadMode data type corresponds with the enum DSC_VirtualKeypadMode_Tag.

	\sa enum DSC_VirtualKeypadMode_Tag
*/
typedef DSC_ENUM_T DSC_VirtualKeypadMode;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_VIRTUAL_KEYPAD_MODES_HPP_
