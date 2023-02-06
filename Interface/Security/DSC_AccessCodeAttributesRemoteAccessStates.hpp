//---------------------------------------------------------------------------
//
//	DSC_AccessCodeAttributesRemoteAccessStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ACCESS_CODE_ATTRIBUTES_REMOTE_ACCESS_STATES_HPP_
#define _DSC_ACCESS_CODE_ATTRIBUTES_REMOTE_ACCESS_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_AccessCodeAttributesRemoteAccessStates {
/*!
	The SDK provides access to modify an Access Codes ability to access the alarm system remotely as described below.

	Users with this attribute Enabled can access the alarm system remotely via SMS.
*/
enum DSC_AccessCodeAttributesRemoteAccessState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    RemoteAccess_Enabled = 1,	/**< Remote access is Enabled. */	
	RemoteAccess_Disabled = 2	/**< Remote access is Disabled. */	

}; }

#else

#define DSC_AccessCodeAttributesRemoteAccessStates(value)	(DSC_E24_##value)
enum DSC_AccessCodeAttributesRemoteAccessState_Tag {
	
	//Default for all enums
	DSC_E24_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E24_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E24_RemoteAccess_Enabled	= 1,	/**< Remote access is Enabled. */	
	DSC_E24_RemoteAccess_Disabled	= 2	/**< Remote access is Disabled. */	

};

#endif

/*!
	The DSC_AccessCodeAttributesRemoteAccessState data type corresponds with the enum DSC_AccessCodeAttributesRemoteAccessState_Tag.

	\sa enum DSC_AccessCodeAttributesRemoteAccessState_Tag
*/
typedef DSC_ENUM_T DSC_AccessCodeAttributesRemoteAccessState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ACCESS_CODE_ATTRIBUTES_REMOTE_ACCESS_STATES_HPP_
