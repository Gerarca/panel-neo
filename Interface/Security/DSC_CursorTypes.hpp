//---------------------------------------------------------------------------
//
//	DSC_CursorTypes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_CURSOR_TYPES_HPP_
#define _DSC_CURSOR_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_CursorTypes {
/*!
	The SDK uses the cursor types on keypad LCDs as described below.
*/
enum DSC_CursorType_Tag {

	//Default for all enums
	Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	Off				= 1,	/**< The cursor is disabled (not visible). */
	Normal			= 2,	/**< The default LCD cursor. It is usualy the underscore. */
	Block			= 3		/**< The block LCD cursor uses the entire character space. */

}; }

#else

#define DSC_CursorTypes(value)	(DSC_E28_##value)
enum DSC_CursorType_Tag {

	//Default for all enums
	DSC_E28_Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E28_Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E28_Off				= 1,		/**< The cursor is disabled (not visible). */
	DSC_E28_Normal			= 2,		/**< The default LCD cursor. It is usualy the underscore. */
	DSC_E28_Block			= 3			/**< The block LCD cursor uses the entire character space. */

};

#endif

/*!
	The DSC_CursorType data type corresponds with the enum DSC_CursorType_Tag.

	\sa enum DSC_CursorType_Tag
*/
typedef DSC_ENUM_T DSC_CursorType;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_CURSOR_TYPES_HPP_
