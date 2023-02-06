//---------------------------------------------------------------------------
//
//	DSC_AccessCodeAttributesBellSquawkStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ACCESS_CODE_ATTRIBUTES_BELL_SQUAWK_STATES_HPP_
#define _DSC_ACCESS_CODE_ATTRIBUTES_BELL_SQUAWK_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_AccessCodeAttributesBellSquawkStates {
/*!
	The SDK provides access to Bell Squawk states as described below.

	Bell Squawks are used to announce various System or Partition Events
*/
enum DSC_AccessCodeAttributesBellSquawkState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    BellSquawk_Enabled	= 1,	/**< Bell Squawk events are enabled. */	
	BellSquawk_Disabled	= 2		/**< Bell Squawk events are disabled. */	

}; }

#else

#define DSC_AccessCodeAttributesBellSquawkStates(value)	(DSC_E20_##value)
enum DSC_AccessCodeAttributesBellSquawkState_Tag {
	
	//Default for all enums
	DSC_E20_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E20_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E20_BellSquawk_Enabled	= 1,	/**< Bell Squawk events are enabled. */	
	DSC_E20_BellSquawk_Disabled	= 2		/**< Bell Squawk events are disabled. */	

};

#endif

/*!
	The DSC_AccessCodeAttributesBellSquawkState data type corresponds with the enum DSC_AccessCodeAttributesBellSquawkState_Tag.

	\sa enum DSC_AccessCodeAttributesBellSquawkState_Tag
*/
typedef DSC_ENUM_T DSC_AccessCodeAttributesBellSquawkState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ACCESS_CODE_ATTRIBUTES_BELL_SQUAWK_STATES_HPP_
