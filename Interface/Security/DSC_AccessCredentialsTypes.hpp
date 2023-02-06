//---------------------------------------------------------------------------
//
//	DSC_AccessCredentialsType.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ACCESS_CREDENTIALS_TYPE_HPP_
#define _DSC_ACCESS_CREDENTIALS_TYPE_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_AccessCredentialsTypes {
/*!
	The SDK provides functionality for different Access Credential types as described below.

	Used to future proof the SDK and allow it to support future data types if needed. (i.e. fingerprint scan data.)
*/
enum DSC_AccessCredentialsType_Tag {

	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
	Numeric             = 1		/**< Valid Credential data are numeric from 0 to 9. */

}; }

#else

#define DSC_AccessCredentialsTypes(value)	(DSC_E26_##value)
enum DSC_AccessCredentialsType_Tag {

	//Default for all enums
	DSC_E26_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E26_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
	DSC_E26_Numeric             = 1		/**< Valid Credential data are numeric from 0 to 9. */

};

#endif

/*!
	The DSC_AccessCredentialsType data type corresponds with the enum DSC_AccessCredentialsType_Tag.

	\sa enum DSC_AccessCredentialsType_Tag
*/
typedef DSC_ENUM_T DSC_AccessCredentialsType;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ACCESS_CREDENTIALS_TYPE_HPP_
