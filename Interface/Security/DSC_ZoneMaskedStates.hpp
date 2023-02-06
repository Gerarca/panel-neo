//---------------------------------------------------------------------------
//
//	DSC_ZoneMaskedStates.hpp
//  Copyright 2021 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_MASKED_STATES_HPP_
#define _DSC_ZONE_MASKED_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneMaskedStates {
/*!
	The SDK provides access to Masked states as described below.
*/
enum DSC_ZoneMaskedState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    Masked		= 1,	/**< The system masked zones. */
    Not_Masked	= 2		/**< The system does not have masked zones. */

}; }

#else

#define DSC_ZoneMaskedStates(value)	(DSC_E76_##value)
enum DSC_ZoneMaskedState_Tag {
	
	//Default for all enums
	DSC_E76_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E76_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    DSC_E76_Masked		= 1,	/**< The system has masked zones. */
    DSC_E76_Not_Masked	= 2		/**< The system does not have masked zonesy. */

};

#endif

/*!
	The DSC_ZoneMaskedState data type corresponds with the enum DSC_ZoneMaskedState_Tag.

	\sa enum DSC_ZoneMaskedState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneMaskedState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_MASKED_STATES_HPP_
