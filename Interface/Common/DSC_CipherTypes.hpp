//---------------------------------------------------------------------------
//
//	DSC_CipherTypes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The list of various ciphers used by the SDK.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_CIPHER_TYPES_HPP_
#define _DSC_CIPHER_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_CipherTypes {
/*!
	The list of various ciphers used by the SDK.
*/
enum DSC_CipherType_Tag {

	Unknown			= 0,	/**< Unknown - must be 0! */

	ITV2_AES128		= 1		/**< AES algorithm used by the ITV2 on NEO platform */

}; }

#else

#define DSC_CipherTypes(value)	(DSC_E04_##value)
enum DSC_CipherType_Tag {

	DSC_E04_Unknown			= 0,	/**< Unknown - must be 0! */

	DSC_E04_ITV2_AES128		= 1		/**< AES algorithm used by the ITV2 on NEO platform */

};

#endif

/*!
	The DSC_CipherType data type corresponds with the enum DSC_CipherType_Tag.

	\sa enum DSC_CipherType_Tag
*/
typedef DSC_ENUM_T DSC_CipherType;

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_CIPHER_TYPES_HPP_
