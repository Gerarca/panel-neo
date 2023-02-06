//---------------------------------------------------------------------------
//
//	DSC_AccessCodeAttributesOneTimeUseStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ACCESS_CODE_ATTRIBUTES_ONE_TIME_USE_STATES_HPP_
#define _DSC_ACCESS_CODE_ATTRIBUTES_ONE_TIME_USE_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_AccessCodeAttributesOneTimeUseStates {
/*!
	The SDK provides access to Access Code One Time Use options as described below.

	When Enabled the access code enables the user to arm the alarm system an unlimited number of times.
	However, an Access Code with this attribute Enabled can only disarm the system once per day. (Auto resets at midnight)
*/
enum DSC_AccessCodeAttributesOneTimeUseState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    OneTimeUse_Enabled	= 1,	/**< One Time Use option is Enabled. */	
	OneTimeUse_Disabled	= 2		/**< One Time Use option is Disabled. */	

}; }

#else

#define DSC_AccessCodeAttributesOneTimeUseStates(value)	(DSC_E23_##value)
enum DSC_AccessCodeAttributesOneTimeUseState_Tag {
	
	//Default for all enums
	DSC_E23_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E23_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E23_OneTimeUse_Enabled		= 1,	/**< One Time Use option is Enabled. */	
	DSC_E23_OneTimeUse_Disabled		= 2		/**< One Time Use option is Disabled. */	

};

#endif

/*!
	The DSC_AccessCodeAttributesOneTimeUseState data type corresponds with the enum DSC_AccessCodeAttributesOneTimeUseState_Tag.

	\sa enum DSC_AccessCodeAttributesOneTimeUseState_Tag
*/
typedef DSC_ENUM_T DSC_AccessCodeAttributesOneTimeUseState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ACCESS_CODE_ATTRIBUTES_ONE_TIME_USE_STATES_HPP_
