//---------------------------------------------------------------------------
//
//	DSC_TroubleStates.hpp
//  Copyright 2021 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_TROUBLE_STATES_HPP_
#define _DSC_TROUBLE_STATES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_TroubleStates {
/*!
	The SDK provides access to Trouble Types as described below.
*/
enum DSC_TroubleState_Tag {

	//Default for all enums
	Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	Trouble_Restore		= 0x01, /**< Trouble Restore. */
	Trouble				= 0x02, /**< Trouble. */
	Trouble_In_Memory	= 0x03	/**< Trouble In Memory. */		
}; }

#else

#define DSC_TroubleStates(value)	(DSC_E83_##value)
enum DSC_TroubleState_Tag {

	//Default for all enums
	DSC_E83_Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E83_Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E83_Trouble_Restore		= 0x01, /**< Trouble Restore. */
	DSC_E83_Trouble				= 0x02, /**< Trouble. */
	DSC_E83_Trouble_In_Memory	= 0x03	/**< Trouble In Memory. */		
};

#endif

/*!
	The DSC_TroubleState data type corresponds with the enum DSC_TroubleState_Tag.

	\sa enum DSC_TroubleState_Tag
*/
typedef DSC_ENUM_T DSC_TroubleState;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_TROUBLE_STATES_HPP_
