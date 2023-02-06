//---------------------------------------------------------------------------
//
//	DSC_IAccessCodeManager.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IAccessCode.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCredentials.hpp"

#ifndef _DSC_I_ACCESS_CODE_MANAGER_HPP_
#define _DSC_I_ACCESS_CODE_MANAGER_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IAccessCodeManager	"DSC_IAccessCodeManager"

//---------------------------------------------------------------------------

#ifndef DSC_IAccessCodeManager_FWD_DEFINED
#define DSC_IAccessCodeManager_FWD_DEFINED
typedef DSC_INTERFACE DSC_IAccessCodeManager DSC_IAccessCodeManager;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to request the list of enabled access codes
	on the panel.
*/
DSC_INTERFACE DSC_IAccessCodeManager : public DSC_IComponent
{
public:

	//! Refreshes the list of enabled access codes on panel.
	/*! This function will issue the requisite commands to fetch the list of enabled access codes on the panel.  */
	/*!
		\sa DSC_IAccessCredentials
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to request the list of enabled access codes.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get the number of enabled access codes.
	/*! Returns the number of enabled access codes. */
	/*!
		\param ptrCount Pointer to storage for the number of enabled access codes.
	*/
	virtual IRESULT ICALL get_NumberOfAccessCodes(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Get an Access Code interface.
	/*! Retrieves an Access Code interface. This is a 0 based list index, NOT a system index. */
	/*!
		\sa DSC_IAccessCode
		\param numIndex Requested 0 based list index of the access code interface to get.
		\param ptrAccessCode Pointer to storage for the requested access code interface.
	*/
	virtual IRESULT ICALL get_AccessCode(IN DSC_SIZE_T numIndex, OUT DSC_IAccessCode** ptrAccessCode) = 0;
};

#else

typedef struct DSC_IAccessCodeManager_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IAccessCodeManager *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IAccessCodeManager *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IAccessCodeManager *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IAccessCodeManager *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_NumberOfAccessCodes)(IN DSC_IAccessCodeManager *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_AccessCode)(IN DSC_IAccessCodeManager *This, 
		IN DSC_SIZE_T numIndex, OUT DSC_IAccessCode** ptrAccessCode);

	END_INTERFACE
} DSC_IAccessCodeManager_Vtbl;

DSC_INTERFACE DSC_IAccessCodeManager
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IAccessCodeManager_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_ACCESS_CODE_MANAGER_HPP_
