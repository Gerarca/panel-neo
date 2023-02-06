//---------------------------------------------------------------------------
//
//	DSC_CommandOutputReportingStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_COMMAND_OUTPUT_REPORTING_STATES_HPP_
#define _DSC_COMMAND_OUTPUT_REPORTING_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_CommandOutputReportingStates {	
/*!
	The SDK provides access to Output state options as described below.

	Used to interact with the present state of a Command Output 
*/
enum DSC_CommandOutputReportingStates_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    Output_Off			= 1,	/**< The Output is in it's off status. */	
	Output_On			= 2,	/**< The Output is in it's on status. */	
	Output_Unknown      = 3		/**< The Output is in an unknown status. */	

}; }

#else

#define DSC_CommandOutputReportingStates(value)	(DSC_E75_##value)
enum DSC_CommandOutputReportingStates_Tag {
	
	//Default for all enums
	DSC_E75_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E75_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values.
    DSC_E75_Output_Off			= 1,	/**< The Output is in it's off status. */	
	DSC_E75_Output_On			= 2,	/**< The Output is in it's on status. */	
	DSC_E75_Output_Unknown      = 3		/**< The Output is in an unknown status. */	

};

#endif

/*!
	The DSC_CommandOutputReportingState data type corresponds with the enum DSC_CommandOutputReportingStates_Tag.

	\sa enum DSC_CommandOutputStatus_Tag
*/
typedef DSC_ENUM_T DSC_CommandOutputReportingState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_COMMAND_OUTPUT_REPORTING_STATES_HPP_
