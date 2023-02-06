//---------------------------------------------------------------------------
//
//	DSC_VirtualKeypadTypes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_VIRTUAL_KEYPAD_TYPES_HPP_
#define _DSC_VIRTUAL_KEYPAD_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_VirtualKeypadTypes {
/*!
	The SDK supports various types of Virtual Keypads as described below.
*/
enum DSC_VirtualKeypadType_Tag {

	//Default for all enums
	Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	Character_Matrix_16x2	= 1		/**< Character matrix display: 2 rows of 16 characters per row. */

}; }

#else

#define DSC_VirtualKeypadTypes(value)	(DSC_E57_##value)
enum DSC_VirtualKeypadType_Tag {

	//Default for all enums
	DSC_E57_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E57_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E57_Character_Matrix_16x2	= 1		/**< Character matrix display: 2 rows of 16 characters per row. */

};

#endif

/*!
	The DSC_VirtualKeypadType data type corresponds with the enum DSC_VirtualKeypadType_Tag.

	\sa enum DSC_VirtualKeypadType_Tag
*/
typedef DSC_ENUM_T DSC_VirtualKeypadType;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_VIRTUAL_KEYPAD_TYPES_HPP_
