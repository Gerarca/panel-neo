//---------------------------------------------------------------------------
//
//	DSC_IVirtualKeypadManager.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IVirtualKeypad.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCredentials.hpp"

#ifndef _DSC_I_VIRTUAL_KEYPAD_MANAGER_HPP_
#define _DSC_I_VIRTUAL_KEYPAD_MANAGER_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IVirtualKeypadManager	"DSC_IVirtualKeypadManager"

//---------------------------------------------------------------------------

#ifndef DSC_IVirtualKeypadManager_FWD_DEFINED
#define DSC_IVirtualKeypadManager_FWD_DEFINED
typedef DSC_INTERFACE DSC_IVirtualKeypadManager DSC_IVirtualKeypadManager;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to request the list of enabled virtual keypads
	on the panel.
*/
DSC_INTERFACE DSC_IVirtualKeypadManager : public DSC_IComponent
{
public:

	//! Refreshes the list of enabled virtual keypads on panel.
	/*! This function will issue the requisite commands to fetch the list of enabled virtual keypads on the panel.  */
	/*!
		\sa DSC_IAccessCredentials
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to request the list of virtual keypads.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get the number of enabled virtual keypads.
	/*! Returns the number of enabled virtual keypads. */
	/*!
		\param ptrCount Pointer to storage for the number of enabled virtual keypads.
	*/
	virtual IRESULT ICALL get_NumberOfVirtualKeypads(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Get a Virtual Keypad interface.
	/*! Retrieves a Virtual Keypad interface. This is a 0 based list index, NOT a system index. */
	/*!
		\sa DSC_IVirtualKeypad
		\param numIndex Requested 0 based list index of the virtual keypad interface to get.
		\param ptrZone Pointer to storage for the requested virtual keypad interface.
	*/
	virtual IRESULT ICALL get_VirtualKeypad(IN DSC_SIZE_T numIndex, OUT DSC_IVirtualKeypad** ptrVirtualKeypad) = 0;

	//! Get the number of virtual keypads of a given type supported by the panel. 
	/*! Returns the number of virtual keypads of a given type supported by the panel. */
	/*!
		\sa enum DSC_VirtualKeypadType_Tag
		\param flgType Provided virtual keypad type to check support for.
		\param ptrCount Pointer to storage for the number of supported keypads of the requested type.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL NumberOfSupportedVirtualKeypads(IN DSC_VirtualKeypadType flgType, 
		OUT DSC_SIZE_T* ptrCount, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Creates a Virtual Keypad. 
	/*! Attempts to create the Virtual Keypad. The number of virtual keypads
		available is determined by the panel.
	*/
	/*!
		\sa enum DSC_VirtualKeypadType_Tag
		\sa DSC_IVirtualKeypad
		\param flgType Provided virtual keypad type to create.
		\param ptrVirtualKeypad Pointer to storage for the Virtual Keypad interface.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL CreateVirtualKeypad(IN DSC_VirtualKeypadType flgType, 
		OUT DSC_IVirtualKeypad** ptrVirtualKeypad, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Deletes a Virtual Keypad. 
	/*! Deletes a Virtual Keypad that was previously created.	
	*/
	/*!
		\param numSystemIndex The system index of the Virtual Keypad to delete.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL DeleteVirtualKeypad(IN DSC_SYSTEM_INDEX numSystemIndex, 
		OUT DSC_IRequestResult** ptrRequestResult) = 0;
};

#else

typedef struct DSC_IVirtualKeypadManager_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IVirtualKeypadManager *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IVirtualKeypadManager *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IVirtualKeypadManager *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IVirtualKeypadManager *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_NumberOfVirtualKeypads)(IN DSC_IVirtualKeypadManager *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_VirtualKeypad)(IN DSC_IVirtualKeypadManager *This, 
		IN DSC_SIZE_T numIndex, OUT DSC_IVirtualKeypad** ptrVirtualKeypad);
	IRESULT (ICALL *NumberOfSupportedVirtualKeypads)(IN DSC_IVirtualKeypadManager *This, 
		IN DSC_VirtualKeypadType flgType, OUT DSC_SIZE_T* ptrCount, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *CreateVirtualKeypad)(IN DSC_IVirtualKeypadManager *This, IN DSC_VirtualKeypadType flgType, 
		OUT DSC_IVirtualKeypad** ptrVirtualKeypad, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *DeleteVirtualKeypad)(IN DSC_IVirtualKeypadManager *This, 
		IN DSC_SYSTEM_INDEX numSystemIndex, OUT DSC_IRequestResult** ptrRequestResult);

	END_INTERFACE
} DSC_IVirtualKeypadManager_Vtbl;

DSC_INTERFACE DSC_IVirtualKeypadManager
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IVirtualKeypadManager_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_VIRTUAL_KEYPAD_MANAGER_HPP_
