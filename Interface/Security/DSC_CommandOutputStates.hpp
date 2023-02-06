//---------------------------------------------------------------------------
//
//	DSC_CommandOutputStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_COMMAND_OUTPUT_STATES_HPP_
#define _DSC_COMMAND_OUTPUT_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_CommandOutputStates {	
/*!
	The SDK provides access to Output state options as described below.

	Used to interact with the present state of a Command Output 
*/
enum DSC_CommandOutputState_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    Output_Deactivate	= 1,	/**< The Output is in it's non active state. */	
	Output_Activate		= 2,	/**< The Output is in it's active state. */	
	Output_Toggle       = 3		/**< The Output is in it's toggle state. (Typically a 1 to 3 second active state then it returns to it's non active state.) */	

}; }

#else

#define DSC_CommandOutputStates(value)	(DSC_E27_##value)
enum DSC_CommandOutputState_Tag {
	
	//Default for all enums
	DSC_E27_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E27_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E27_Output_Deactivate	= 1,	/**< The Output is in it's non active state. */	
	DSC_E27_Output_Activate		= 2,	/**< The Output is in it's active state. */	
	DSC_E27_Output_Toggle       = 3		/**< The Output is in it's toggle state. (Typically a 1 to 3 second active state then it returns to it's non active state.) */	

};

#endif

/*!
	The DSC_CommandOutputState data type corresponds with the enum DSC_CommandOutputState_Tag.

	\sa enum DSC_CommandOutputState_Tag
*/
typedef DSC_ENUM_T DSC_CommandOutputState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_COMMAND_OUTPUT_STATES_HPP_
