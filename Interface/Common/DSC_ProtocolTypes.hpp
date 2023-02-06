//---------------------------------------------------------------------------
//
//	DSC_ProtocolTypes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The list of protocols supported by the SDK.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PROTOCOL_TYPES_HPP_
#define _DSC_PROTOCOL_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ProtocolTypes {
/*!
	The list of various data protocol types supported by the SDK.
*/
enum DSC_ProtocolType_Tag {

	Unknown			= 0,		/**< unknown - must be 0! */

	ITV2			= 1			/**< ITv2 protocol */

}; }

#else

#define DSC_ProtocolTypes(value)	(DSC_E07_##value)
enum DSC_ProtocolType_Tag {

	DSC_E07_Unknown		= 0,		/**< unknown - must be 0! */

	DSC_E07_ITV2		= 1			/**< ITv2 protocol */

};

#endif

/*!
	The DSC_ProtocolType data type corresponds with the enum DSC_ProtocolType_Tag.

	\sa enum DSC_ProtocolType_Tag
*/
typedef DSC_ENUM_T DSC_ProtocolType;

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PROTOCOL_TYPES_HPP_
