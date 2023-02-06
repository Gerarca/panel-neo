//---------------------------------------------------------------------------
//
//	DSC_LEDCadences.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_LED_CADENCES_HPP_
#define _DSC_LED_CADENCES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_LEDCadences {
/*!
	The SDK uses various cadences for the LED indicator types as described below.
*/
enum DSC_LEDCadence_Tag {

	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	Off					= 1,	/**< The LED is OFF. */
	On					= 2,	/**< The LED is in steady ON state. */
	Flash				= 3,	/**< The LED is flashing (500ms ON, 500ms OFF). */
	Flash_Slow			= 4,	/**< The LED is flashing slowly. */
	Flash_Medium		= 5,	/**< The LED is flashing the medium speed. */
	Flash_Fast			= 6,	/**< The LED is flashing fast. */
	One_Wink			= 7,	/**< The LED is flashing quickly once (240ms ON, OFF). */
	Double_Wink			= 8,	/**< The LED is flashing quickly twice (250ms ON, 250ms OFF ; 250ms ON, 750ms OFF). */
	Triple_Wink			= 9,	/**< The LED is flashing quickly three times (250ms ON, 250ms OFF ; 250ms ON, 250ms OFF ; 250ms ON, 750ms OFF). */
	Long_Wink			= 10,	/**< The LED is flashing slowly once (400ms ON, 1700ms OFF). */
	Long_Double_Wink	= 11,	/**< The LED is flashing slowly twice (400ms ON, 400ms OFF ; 400ms ON, 1700ms OFF). */
	Long_Triple_Wink	= 12,	/**< The LED is flashing slowly three times. */
	Flash_Status_One	= 13,	/**< The LED is flashing Status 1 pattern. */
	Flash_Status_Two	= 14,	/**< The LED is flashing Status 2 pattern. */
	Flash_Status_Three	= 15,	/**< The LED is flashing Status 3 pattern. */
	Armed_Sleep_Mode	= 16,	/**< The LED is showing Armed status in sleep mode (100ms ON every 5 seconds). */
	Armed_Stop_Mode		= 17,	/**< The LED is showing Armed status in stop mode (100ms ON, 900ms OFF). */
	System_Test			= 18	/**< The LED is flashing System Test pattern (all LEDs are flashing). */

}; }

#else

#define DSC_LEDCadences(value)	(DSC_E31_##value)
enum DSC_LEDCadence_Tag {

	//Default for all enums
	DSC_E31_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E31_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E31_Off					= 1,	/**< The LED is OFF. */
	DSC_E31_On					= 2,	/**< The LED is in steady ON state. */
	DSC_E31_Flash				= 3,	/**< The LED is flashing (500ms ON, 500ms OFF). */
	DSC_E31_Flash_Slow			= 4,	/**< The LED is flashing slowly. */
	DSC_E31_Flash_Medium		= 5,	/**< The LED is flashing the medium speed. */
	DSC_E31_Flash_Fast			= 6,	/**< The LED is flashing fast. */
	DSC_E31_One_Wink			= 7,	/**< The LED is flashing quickly once (240ms ON, OFF). */
	DSC_E31_Double_Wink			= 8,	/**< The LED is flashing quickly twice (250ms ON, 250ms OFF ; 250ms ON, 750ms OFF). */
	DSC_E31_Triple_Wink			= 9,	/**< The LED is flashing quickly three times (250ms ON, 250ms OFF ; 250ms ON, 250ms OFF ; 250ms ON, 750ms OFF). */
	DSC_E31_Long_Wink			= 10,	/**< The LED is flashing slowly once (400ms ON, 1700ms OFF). */
	DSC_E31_Long_Double_Wink	= 11,	/**< The LED is flashing slowly twice (400ms ON, 400ms OFF ; 400ms ON, 1700ms OFF). */
	DSC_E31_Long_Triple_Wink	= 12,	/**< The LED is flashing slowly three times. */
	DSC_E31_Flash_Status_One	= 13,	/**< The LED is flashing Status 1 pattern. */
	DSC_E31_Flash_Status_Two	= 14,	/**< The LED is flashing Status 2 pattern. */
	DSC_E31_Flash_Status_Three	= 15,	/**< The LED is flashing Status 3 pattern. */
	DSC_E31_Armed_Sleep_Mode	= 16,	/**< The LED is showing Armed status in sleep mode (100ms ON every 5 seconds). */
	DSC_E31_Armed_Stop_Mode		= 17,	/**< The LED is showing Armed status in stop mode (100ms ON, 900ms OFF). */
	DSC_E31_System_Test			= 18	/**< The LED is flashing System Test pattern (all LEDs are flashing). */

};

#endif

/*!
	The DSC_LEDCadence data type corresponds with the enum DSC_LEDCadence_Tag.

	\sa enum DSC_LEDCadence_Tag
*/
typedef DSC_ENUM_T DSC_LEDCadence;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_LED_CADENCES_HPP_
