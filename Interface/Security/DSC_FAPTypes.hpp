//---------------------------------------------------------------------------
//
//	DSC_FAPTypes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_FAP_TYPES_HPP_
#define _DSC_FAP_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_FAPTypes {
/*!
	The SDK provides access to Keypad emergency keys [F], [A], [P], options as described below.

	Used to activate [F] [A] [P] emergency keys remotely.
*/
enum DSC_FAPType_Tag {
	
	//Default for all enums
	Not_Available	= -1,		/**< Reserved value. It indicates that this value is not available on the product. */
	Unknown			= 0,		/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */

	//Valid product values.
	Fire			= 1,		/**< Keypad Fire Alarm [F] Key. */
	Aux				= 2,		/**< Keypad Auxiliary Alarm [A] Key. */
	Panic			= 3			/**< Keypad Panic Alarm [P] Key. */

}; }

#else

#define DSC_FAPTypes(value)	(DSC_E30_##value)
enum DSC_FAPType_Tag {
	
	//Default for all enums
	DSC_E30_Not_Available	= -1,		/**< Reserved value. It indicates that this value is not available on the product. */
	DSC_E30_Unknown			= 0,			/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */

	//Valid product values.
	DSC_E30_Fire			= 1,				/**< Keypad Fire Alarm [F] Key. */
	DSC_E30_Aux				= 2,				/**< Keypad Auxiliary Alarm [A] Key. */
	DSC_E30_Panic			= 3				/**< Keypad Panic Alarm [P] Key. */

};

#endif

/*!
	The DSC_FAPType data type corresponds with the enum DSC_FAPType_Tag.

	\sa enum DSC_FAPType_Tag
*/
typedef DSC_ENUM_T DSC_FAPType;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_FAP_TYPES_HPP_
