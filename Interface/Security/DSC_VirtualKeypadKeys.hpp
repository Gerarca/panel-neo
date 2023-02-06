//---------------------------------------------------------------------------
//
//	DSC_VirtualKeypadKeys.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_VIRTUAL_KEYPAD_KEYS_HPP_
#define _DSC_VIRTUAL_KEYPAD_KEYS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_VirtualKeypadKeys {
/*!
	The SDK defines a number of Virtual Keypad key codes as described below.
*/
enum DSC_VirtualKeypadKey_Tag {

	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	Key_0_Short			= 1,	/**< Short press of the key '0'. */	
	Key_1_Short			= 2,	/**< Short press of the key '1'. */
	Key_2_Short			= 3,	/**< Short press of the key '2'. */
	Key_3_Short			= 4,	/**< Short press of the key '3'. */
	Key_4_Short			= 5,	/**< Short press of the key '4'. */
	Key_5_Short			= 6,	/**< Short press of the key '5'. */
	Key_6_Short			= 7,	/**< Short press of the key '6'. */
	Key_7_Short			= 8,	/**< Short press of the key '7'. */
	Key_8_Short			= 9,	/**< Short press of the key '8'. */
	Key_9_Short			= 10,	/**< Short press of the key '9'. */
	Key_Star_Short		= 11,	/**< Short press of the key '*'. */
	Key_Pound_Short		= 12,	/**< Short press of the key '#'. */
	Key_Fire_Short		= 13,	/**< Short press of the Fire key. */
	Key_Aux_Short		= 14,	/**< Short press of the Auxiliary key. */
	Key_Panic_Short		= 15,	/**< Short press of the Panic key. */
	Key_Func1_Short		= 16,	/**< Short press of the Func_1 key. */
	Key_Func2_Short		= 17,	/**< Short press of the Func_2 key. */
	Key_Func3_Short		= 18,	/**< Short press of the Func_3 key. */
	Key_Func4_Short		= 19,	/**< Short press of the Func_4 key. */
	Key_Func5_Short		= 20,	/**< Short press of the Func_5 key. */
	Key_ArrowR_Short	= 21,	/**< Short press of the right arrow key. */
	Key_ArrowL_Short	= 22,	/**< Short press of the left arrow key. */
	Key_ArrowLR_Short	= 23,	/**< Short press of the both arrow keys. */
	Key_FireD_Short		= 24,	/**< Short press of the Fire dual key. */
	Key_AuxD_Short		= 25,	/**< Short press of the Auxiliary dual key. */
	Key_PanicD_Short	= 26,	/**< Short press of the Panic dual key. */
	Key_Func15_Short	= 27,	/**< Short press of the Func_15 key. */
	Key_Func25_Short	= 28,	/**< Short press of the Func_25 key. */
	Key_Func35_Short	= 29,	/**< Short press of the Func_35 key. */
	Key_Func45_Short	= 30,	/**< Short press of the Func_45 key. */
	Key_FireSide_Short	= 31,	/**< Short press of the Fire side key. */
	Key_AuxSide_Short	= 32,	/**< Short press of the Auxiliary side key. */
	Key_PanicSide_Short = 33,	/**< Short press of the Panic side key. */

	Key_0_Long			= 101,	/**< Long press of the key '0'. */
	Key_1_Long			= 102,	/**< Long press of the key '1'. */
	Key_2_Long			= 103,	/**< Long press of the key '2'. */
	Key_3_Long			= 104,	/**< Long press of the key '3'. */
	Key_4_Long			= 105,	/**< Long press of the key '4'. */
	Key_5_Long			= 106,	/**< Long press of the key '5'. */
	Key_6_Long			= 107,	/**< Long press of the key '6'. */
	Key_7_Long			= 108,	/**< Long press of the key '7'. */
	Key_8_Long			= 109,	/**< Long press of the key '8'. */
	Key_9_Long			= 110,	/**< Long press of the key '9'. */
	Key_Star_Long		= 111,	/**< Long press of the key '*'. */
	Key_Pound_Long		= 112,	/**< Long press of the key '#'. */
	Key_Fire_Long		= 113,	/**< Long press of the Fire key. */
	Key_Aux_Long		= 114,	/**< Long press of the Auxiliary key. */
	Key_Panic_Long		= 115,	/**< Long press of the Panic key. */
	Key_Func1_Long		= 116,	/**< Long press of the Func_1 key. */
	Key_Func2_Long		= 117,	/**< Long press of the Func_2 key. */
	Key_Func3_Long		= 118,	/**< Long press of the Func_3 key. */
	Key_Func4_Long		= 119,	/**< Long press of the Func_4 key. */
	Key_Func5_Long		= 120,	/**< Long press of the Func_5 key. */
	Key_ArrowR_Long		= 121,	/**< Long press of the right arrow key. */
	Key_ArrowL_Long		= 122,	/**< Long press of the left arrow key. */
	Key_ArrowLR_Long	= 123,	/**< Long press of the both arrow keys. */
	Key_FireD_Long		= 124,	/**< Long press of the Fire dual key. */
	Key_AuxD_Long		= 125,	/**< Long press of the Auxiliary dual key. */
	Key_PanicD_Long		= 126,	/**< Long press of the Panic dual key. */
	Key_Func15_Long		= 127,	/**< Long press of the Func_15 key. */
	Key_Func25_Long		= 128,	/**< Long press of the Func_25 key. */
	Key_Func35_Long		= 129,	/**< Long press of the Func_35 key. */
	Key_Func45_Long		= 130,	/**< Long press of the Func_45 key. */
	Key_FireSide_Long	= 131,	/**< Long press of the Fire side key. */
	Key_AuxSide_Long	= 132,	/**< Long press of the Auxiliary side key. */
	Key_PanicSide_Long	= 133	/**< Long press of the Panic side key. */

}; }

#else

#define DSC_VirtualKeypadKeys(value)	(DSC_E55_##value)
enum DSC_VirtualKeypadKey_Tag {

	//Default for all enums
	DSC_E55_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E55_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	DSC_E55_Key_0_Short				= 1,	/**< Short press of the key '0'. */	
	DSC_E55_Key_1_Short				= 2,	/**< Short press of the key '1'. */
	DSC_E55_Key_2_Short				= 3,	/**< Short press of the key '2'. */
	DSC_E55_Key_3_Short				= 4,	/**< Short press of the key '3'. */
	DSC_E55_Key_4_Short				= 5,	/**< Short press of the key '4'. */
	DSC_E55_Key_5_Short				= 6,	/**< Short press of the key '5'. */
	DSC_E55_Key_6_Short				= 7,	/**< Short press of the key '6'. */
	DSC_E55_Key_7_Short				= 8,	/**< Short press of the key '7'. */
	DSC_E55_Key_8_Short				= 9,	/**< Short press of the key '8'. */
	DSC_E55_Key_9_Short				= 10,	/**< Short press of the key '9'. */
	DSC_E55_Key_Star_Short			= 11,	/**< Short press of the key '*'. */
	DSC_E55_Key_Pound_Short			= 12,	/**< Short press of the key '#'. */
	DSC_E55_Key_Fire_Short			= 13,	/**< Short press of the Fire key. */
	DSC_E55_Key_Aux_Short			= 14,	/**< Short press of the Auxiliary key. */
	DSC_E55_Key_Panic_Short			= 15,	/**< Short press of the Panic key. */
	DSC_E55_Key_Func1_Short			= 16,	/**< Short press of the Func_1 key. */
	DSC_E55_Key_Func2_Short			= 17,	/**< Short press of the Func_2 key. */
	DSC_E55_Key_Func3_Short			= 18,	/**< Short press of the Func_3 key. */
	DSC_E55_Key_Func4_Short			= 19,	/**< Short press of the Func_4 key. */
	DSC_E55_Key_Func5_Short			= 20,	/**< Short press of the Func_5 key. */
	DSC_E55_Key_ArrowR_Short		= 21,	/**< Short press of the right arrow key. */
	DSC_E55_Key_ArrowL_Short		= 22,	/**< Short press of the left arrow key. */
	DSC_E55_Key_ArrowLR_Short		= 23,	/**< Short press of the both arrow keys. */
	DSC_E55_Key_FireD_Short			= 24,	/**< Short press of the Fire dual key. */
	DSC_E55_Key_AuxD_Short			= 25,	/**< Short press of the Auxiliary dual key. */
	DSC_E55_Key_PanicD_Short		= 26,	/**< Short press of the Panic dual key. */
	DSC_E55_Key_Func15_Short		= 27,	/**< Short press of the Func_15 key. */
	DSC_E55_Key_Func25_Short		= 28,	/**< Short press of the Func_25 key. */
	DSC_E55_Key_Func35_Short		= 29,	/**< Short press of the Func_35 key. */
	DSC_E55_Key_Func45_Short		= 30,	/**< Short press of the Func_45 key. */
	DSC_E55_Key_FireSide_Short		= 31,	/**< Short press of the Fire side key. */
	DSC_E55_Key_AuxSide_Short		= 32,	/**< Short press of the Auxiliary side key. */
	DSC_E55_Key_PanicSide_Short		= 33,	/**< Short press of the Panic side key. */

	DSC_E55_Key_0_Long				= 101,	/**< Long press of the key '0'. */
	DSC_E55_Key_1_Long				= 102,	/**< Long press of the key '1'. */
	DSC_E55_Key_2_Long				= 103,	/**< Long press of the key '2'. */
	DSC_E55_Key_3_Long				= 104,	/**< Long press of the key '3'. */
	DSC_E55_Key_4_Long				= 105,	/**< Long press of the key '4'. */
	DSC_E55_Key_5_Long				= 106,	/**< Long press of the key '5'. */
	DSC_E55_Key_6_Long				= 107,	/**< Long press of the key '6'. */
	DSC_E55_Key_7_Long				= 108,	/**< Long press of the key '7'. */
	DSC_E55_Key_8_Long				= 109,	/**< Long press of the key '8'. */
	DSC_E55_Key_9_Long				= 110,	/**< Long press of the key '9'. */
	DSC_E55_Key_Star_Long			= 111,	/**< Long press of the key '*'. */
	DSC_E55_Key_Pound_Long			= 112,	/**< Long press of the key '#'. */
	DSC_E55_Key_Fire_Long			= 113,	/**< Long press of the Fire key. */
	DSC_E55_Key_Aux_Long			= 114,	/**< Long press of the Auxiliary key. */
	DSC_E55_Key_Panic_Long			= 115,	/**< Long press of the Panic key. */
	DSC_E55_Key_Func1_Long			= 116,	/**< Long press of the Func_1 key. */
	DSC_E55_Key_Func2_Long			= 117,	/**< Long press of the Func_2 key. */
	DSC_E55_Key_Func3_Long			= 118,	/**< Long press of the Func_3 key. */
	DSC_E55_Key_Func4_Long			= 119,	/**< Long press of the Func_4 key. */
	DSC_E55_Key_Func5_Long			= 120,	/**< Long press of the Func_5 key. */
	DSC_E55_Key_ArrowR_Long			= 121,	/**< Long press of the right arrow key. */
	DSC_E55_Key_ArrowL_Long			= 122,	/**< Long press of the left arrow key. */
	DSC_E55_Key_ArrowLR_Long		= 123,	/**< Long press of the both arrow keys. */
	DSC_E55_Key_FireD_Long			= 124,	/**< Long press of the Fire dual key. */
	DSC_E55_Key_AuxD_Long			= 125,	/**< Long press of the Auxiliary dual key. */
	DSC_E55_Key_PanicD_Long			= 126,	/**< Long press of the Panic dual key. */
	DSC_E55_Key_Func15_Long			= 127,	/**< Long press of the Func_15 key. */
	DSC_E55_Key_Func25_Long			= 128,	/**< Long press of the Func_25 key. */
	DSC_E55_Key_Func35_Long			= 129,	/**< Long press of the Func_35 key. */
	DSC_E55_Key_Func45_Long			= 130,	/**< Long press of the Func_45 key. */
	DSC_E55_Key_FireSide_Long		= 131,	/**< Long press of the Fire side key. */
	DSC_E55_Key_AuxSide_Long		= 132,	/**< Long press of the Auxiliary side key. */
	DSC_E55_Key_PanicSide_Long		= 133	/**< Long press of the Panic side key. */

};

#endif

/*!
	The DSC_VirtualKeypadKey data type corresponds with the enum DSC_VirtualKeypadKey_Tag.

	\sa enum DSC_VirtualKeypadKey_Tag
*/
typedef DSC_ENUM_T DSC_VirtualKeypadKey;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_VIRTUAL_KEYPAD_KEYS_HPP_
