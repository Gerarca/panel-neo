//---------------------------------------------------------------------------
//
//	DSC_ProgrammingStates.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PROGRAMMING_STATES_HPP_
#define _DSC_PROGRAMMING_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------
	
#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ProgrammingStates {
/*!
	The SDK provides access to programming state changes as described below.

	These notification events describe when programming has started or ended. 
	The system configuration has changed and you will likely need to refresh 
	the data in the SDK by calling the Refresh() function to update any state 
	data when the "End" notification is received.
*/
enum DSC_ProgrammingState_Tag {

	Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	Begin			= 1,	/**< Programming State Change Begin - The specified Programming Mode has started, changes may take effect while this is active*/	
	End				= 2		/**< Programming State Change End - The specified Programming Mode has finished. Change may or may not be present on your system and may require refreshing. */	

}; }

#else

#define DSC_ProgrammingStates(value)	(DSC_E49_##value)
enum DSC_ProgrammingState_Tag {

	DSC_E49_Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E49_Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E49_Begin			= 1,	/**< Programming State Change Begin - The specified Programming Mode has started, changes may take effect while this is active*/	
	DSC_E49_End				= 2		/**< Programming State Change End - The specified Programming Mode has finished. Change may or may not be present on your system and may require refreshing. */	

};

#endif

/*!
	The DSC_ProgrammingState data type corresponds with the enum DSC_ProgrammingState_Tag.

	\sa enum DSC_ProgrammingState_Tag
*/
typedef DSC_ENUM_T DSC_ProgrammingState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PROGRAMMING_STATES_HPP_
