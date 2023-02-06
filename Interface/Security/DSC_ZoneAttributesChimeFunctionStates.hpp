//---------------------------------------------------------------------------
//
//	DSC_ZoneAttributesChimeFunctionStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ZONE_ATTRIBUTES_CHIME_FUNCTION_STATES_HPP_
#define _DSC_ZONE_ATTRIBUTES_CHIME_FUNCTION_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ZoneAttributesChimeFunctionStates {
/*!
	The SDK provides access to Zone Chime states as described below.
*/
enum DSC_ZoneAttributesChimeFunctionState_Tag {
	
	//Default for all enums
	Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    ChimeFunction_Enabled	= 1,	/**< Door chime is enabled on this zone. */
	ChimeFunction_Disabled	= 2		/**< Door chime is NOT enabled on this zone. */

}; }

#else

#define DSC_ZoneAttributesChimeFunctionStates(value)	(DSC_E66_##value)
enum DSC_ZoneAttributesChimeFunctionState_Tag {
	
	//Default for all enums
	DSC_E66_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E66_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E66_ChimeFunction_Enabled	= 1,	/**< Door chime is enabled on this zone. */
	DSC_E66_ChimeFunction_Disabled	= 2		/**< Door chime is NOT enabled on this zone. */

};

#endif

/*!
	The DSC_ZoneAttributesChimeFunctionState data type corresponds with the enum DSC_ZoneAttributesChimeFunctionState_Tag.

	\sa enum DSC_ZoneAttributesChimeFunctionState_Tag
*/
typedef DSC_ENUM_T DSC_ZoneAttributesChimeFunctionState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ZONE_ATTRIBUTES_CHIME_FUNCTION_STATES_HPP_
