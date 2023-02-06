//---------------------------------------------------------------------------
//
//	DSC_AccessCodeAttributesDuressCodeStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ACCESS_CODE_ATTRIBUTES_DURESS_CODE_STATES_HPP_
#define _DSC_ACCESS_CODE_ATTRIBUTES_DURESS_CODE_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_AccessCodeAttributesDuressCodeStates {
/*!
	The SDK provides access to Duress code capabilities per Access Code as described below.

	Duress codes function the same as user access codes, except they transmit 
	a duress reporting code when used to perform any function on the system.
*/
enum DSC_AccessCodeAttributesDuressCodeState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DuressCode_Enabled	= 1,	/**< The Access Code will function as a Duress Code. */	
	DuressCode_Disabled	= 2		/**< The Access Code will function normally. */	

}; }

#else

#define DSC_AccessCodeAttributesDuressCodeStates(value)	(DSC_E22_##value)
enum DSC_AccessCodeAttributesDuressCodeState_Tag {
	
	//Default for all enums
	DSC_E22_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E22_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E22_DuressCode_Enabled		= 1,	/**< The Access Code will function as a Duress Code. */	
	DSC_E22_DuressCode_Disabled		= 2		/**< The Access Code will function normally. */	

};

#endif

/*!
	The DSC_AccessCodeAttributesDuressCodeState data type corresponds with the enum DSC_AccessCodeAttributesDuressCodeState_Tag.

	\sa enum DSC_AccessCodeAttributesDuressCodeState_Tag
*/
typedef DSC_ENUM_T DSC_AccessCodeAttributesDuressCodeState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ACCESS_CODE_ATTRIBUTES_DURESS_CODE_STATES_HPP_
