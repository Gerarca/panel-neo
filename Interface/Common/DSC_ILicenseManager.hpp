//---------------------------------------------------------------------------
//
//	DSC_ILicenseManager.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The interface for implementing SDK's feature licensing.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"

#ifndef _DSC_I_LICENSE_MANAGER_HPP_
#define _DSC_I_LICENSE_MANAGER_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ILicenseManager	"DSC_ILicenseManager"

//---------------------------------------------------------------------------

#ifndef DSC_ILicenseManager_FWD_DEFINED
#define DSC_ILicenseManager_FWD_DEFINED
typedef DSC_INTERFACE DSC_ILicenseManager DSC_ILicenseManager;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to manage the SDK feature licenses.
	(The implementation must be thread safe.)
*/
DSC_INTERFACE DSC_ILicenseManager : public DSC_IComponent
{
public:

	//! This property is used to set the License Key.
    /*! 
		The SDK uses the License Key to enable various features. (eg. Virtual Keypad Support)
		The License Key is generated and provided by the Connected Partner Program.

		\param bufData Pointer to a byte array containing the license key.
		\param numSize The size of the byte array containing the license key.
    */
	virtual IRESULT ICALL set_LicenseKey(
		IN BYTE const* bufData, IN DSC_SIZE_T numSize) = 0;
};

#else

typedef struct DSC_ILicenseManager_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ILicenseManager *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ILicenseManager *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ILicenseManager *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *set_LicenseKey)(IN DSC_ILicenseManager *This, 
		IN BYTE const* bufData, IN DSC_SIZE_T numSize);

	END_INTERFACE
} DSC_ILicenseManager_Vtbl;

DSC_INTERFACE DSC_ILicenseManager
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ILicenseManager_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_LICENSE_MANAGER_HPP_
