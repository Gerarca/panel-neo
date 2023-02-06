//---------------------------------------------------------------------------
//
//	DSC_LEDTypes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_LED_TYPES_HPP_
#define _DSC_LED_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_LEDTypes {
/*!
	The SDK utilize the LED indicator types as described below.
*/
enum DSC_LEDType_Tag {

	//Default for all enums
	Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	Ready			= 1,	/**< This LED type is used to signal that the system is ready for arming. */
	Armed			= 2,	/**< This LED type is used to signal that the system is armed. */
	Memory			= 3,	/**< This LED type is used to signal that there are events present in memory. */
	Bypass			= 4,	/**< This LED type is used to signal that some zones have been bypassed. */
	Trouble			= 5,	/**< This LED type is used to signal that there are troubles present on the system. */
	Program			= 6,	/**< This LED type is used to signal that the system is programming mode. */
	Fire			= 7,	/**< This LED type is used to signal that the fire alarm has been activated. */
	Backlight		= 8,	/**< This LED type is used to activate LCD display backlight on the keypad. */
	AC				= 9,	/**< This LED type is used to signal that the AC power is present. */
	LightBar		= 10,	/**< This LED type is used to activate the light bar on the keypad. */
	HomeButton		= 11	/**< This LED type is used to highlight the Home button. */

}; }

#else

#define DSC_LEDTypes(value)	(DSC_E32_##value)
enum DSC_LEDType_Tag {

	//Default for all enums
	DSC_E32_Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E32_Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E32_Ready			= 1,	/**< This LED type is used to signal that the system is ready for arming. */
	DSC_E32_Armed			= 2,	/**< This LED type is used to signal that the system is armed. */
	DSC_E32_Memory			= 3,	/**< This LED type is used to signal that there are events present in memory. */
	DSC_E32_Bypass			= 4,	/**< This LED type is used to signal that some zones have been bypassed. */
	DSC_E32_Trouble			= 5,	/**< This LED type is used to signal that there are troubles present on the system. */
	DSC_E32_Program			= 6,	/**< This LED type is used to signal that the system is programming mode. */
	DSC_E32_Fire			= 7,	/**< This LED type is used to signal that the fire alarm has been activated. */
	DSC_E32_Backlight		= 8,	/**< This LED type is used to activate LCD display backlight on the keypad. */
	DSC_E32_AC				= 9,	/**< This LED type is used to signal that the AC power is present. */
	DSC_E32_LightBar		= 10,	/**< This LED type is used to activate the light bar on the keypad. */
	DSC_E32_HomeButton		= 11	/**< This LED type is used to highlight the Home button. */

};

#endif

/*!
	The DSC_LEDType data type corresponds with the enum DSC_LEDType_Tag.

	\sa enum DSC_LEDType_Tag
*/
typedef DSC_ENUM_T DSC_LEDType;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_LED_TYPES_HPP_
