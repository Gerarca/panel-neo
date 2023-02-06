//---------------------------------------------------------------------------
//
//	DSC_ProgrammingModes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PROGRAMMING_MODES_HPP_
#define _DSC_PROGRAMMING_MODES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------
	
#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ProgrammingModes {
/*!
	The SDK provides access to programming mode changes as described below.

	These notification events describe when programming has changed. 
	The system configuration has changed and you will likely need to 
	refresh the data in the SDK by calling the Refresh() function to 
	update any state data.
*/
enum DSC_ProgrammingMode_Tag {

	Not_Available				= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown						= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	InstallerProgramming		= 1,	/**< Programming Mode is Installer Programming - System Configuration may have changed */
	AccessCodeProgramming		= 2,	/**< Programming Mode is Access Code - Access Codes may have changed */
	UserFunctionProgramming		= 3,	/**< Programming Mode is User Programming - Auto-Arm / Some user functions may have been initiated (system test, time of day change etc).*/
	BypassProgramming			= 4,	/**< Programming Mode is Bypass - Zone Bypass information may have changed.*/			
	Device_Or_ModuleEnrollment	= 5,	/**< Programming Mode is Device/Module enrollment, System Configuration may have changed.*/
	Zone_Enrollment				= 6,	/**< Programming Mode is Zone Enrollment, System Configuration, specifically Zone assignments may have changed.*/
	All_Temperature_Zones_For_Zone_Status_Page = 7,
	All_Temperature_Zones_For_Temperature_Status_Page = 8

}; }

#else

#define DSC_ProgrammingModes(value)	(DSC_E47_##value)
enum DSC_ProgrammingMode_Tag {

	DSC_E47_Not_Available				= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E47_Unknown						= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E47_InstallerProgramming		= 1,	/**< Programming Mode is Installer Programming - System Configuration may have changed */
	DSC_E47_AccessCodeProgramming		= 2,	/**< Programming Mode is Access Code - Access Codes may have changed */
	DSC_E47_UserFunctionProgramming		= 3,	/**< Programming Mode is User Programming - Auto-Arm / Some user functions may have been initiated (system test, time of day change etc).*/
	DSC_E47_BypassProgramming			= 4,	/**< Programming Mode is Bypass - Zone Bypass information may have changed.*/			
	DSC_E47_Device_Or_ModuleEnrollment	= 5,	/**< Programming Mode is Device/Module enrollment, System Configuration may have changed.*/
	DSC_E47_Zone_Enrollment				= 6,	/**< Programming Mode is Zone Enrollment, System Configuration, specifically Zone assignments may have changed.*/
	DSC_E47_All_Temperature_Zones_For_Zone_Status_Page = 7,
	DSC_E47_All_Temperature_Zones_For_Temperature_Status_Page = 8
};

#endif

/*!
	The DSC_ProgrammingMode data type corresponds with the enum DSC_ProgrammingMode_Tag.

	\sa enum DSC_ProgrammingMode_Tag
*/
typedef DSC_ENUM_T DSC_ProgrammingMode;


//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PROGRAMMING_MODES_HPP_
