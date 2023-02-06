//---------------------------------------------------------------------------
//
//	DSC_TextAttributes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_TEXT_ATTRIBUTES_HPP_
#define _DSC_TEXT_ATTRIBUTES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_TextAttributes {
/*!
	When displaying text the SDK uses the text attributes as described below.
*/
enum DSC_TextAttribute_Tag {

	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	Normal				= 1,	/**< The text is displayed using default mode. */
	Blinking			= 2		/**< The text is displayed using blinking characters. */

}; }

#else

#define DSC_TextAttributes(value)	(DSC_E54_##value)
enum DSC_TextAttribute_Tag {	

	//Default for all enums
	DSC_E54_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E54_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E54_Normal				= 1,	/**< The text is displayed using default mode. */
	DSC_E54_Blinking			= 2		/**< The text is displayed using blinking characters. */

};

#endif

/*!
	The DSC_TextAttribute data type corresponds with the enum DSC_TextAttribute_Tag.

	\sa enum DSC_TextAttribute_Tag
*/
typedef DSC_ENUM_T DSC_TextAttribute;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_TEXT_ATTRIBUTES_HPP_
