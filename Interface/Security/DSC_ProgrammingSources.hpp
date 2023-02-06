//---------------------------------------------------------------------------
//
//	DSC_ProgrammingSources.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PROGRAMMING_SOURCES_HPP_
#define _DSC_PROGRAMMING_SOURCES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------
	
#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ProgrammingSources {
/*!
	The SDK provides access to the source of programming state changes as described below.

	These notification events describe when programming has changed. 
	The system configuration has changed and you will likely need to 
	refresh the data in the SDK by calling the Refresh() function to 
	update any state data.
*/
enum DSC_ProgrammingSource_Tag {

	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	Local_Site			= 1,	/**< Programming State Change Occured at local site likely via keypad. */	
	Remote_DLS			= 2,	/**< Programming State Change Occured via DLS */	
	Remote_Connect24	= 3,	/**< Programming State Change Occured via Connect24 */	
	Remote_Interactive	= 4		/**< Programming State Change Occured via Remote Interactive. Note! Some functions of the SDK may trigger this source as they require the SDK to enter configuration mode to effect their changes!*/	

}; }

#else

#define DSC_ProgrammingSources(value)	(DSC_E48_##value)
enum DSC_ProgrammingSource_Tag {

	DSC_E48_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E48_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E48_Local_Site			= 1,	/**< Programming State Change Occured at local site likely via keypad. */	
	DSC_E48_Remote_DLS			= 2,	/**< Programming State Change Occured via DLS */	
	DSC_E48_Remote_Connect24	= 3,	/**< Programming State Change Occured via Connect24 */	
	DSC_E48_Remote_Interactive	= 4		/**< Programming State Change Occured via Remote Interactive. Note! Some functions of the SDK may trigger this source as they require the SDK to enter configuration mode to effect their changes!*/	

};

#endif

/*!
	The DSC_ProgrammingSource data type corresponds with the enum DSC_ProgrammingSource_Tag.

	\sa enum DSC_ProgrammingSource_Tag
*/
typedef DSC_ENUM_T DSC_ProgrammingSource;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PROGRAMMING_SOURCES_HPP_
