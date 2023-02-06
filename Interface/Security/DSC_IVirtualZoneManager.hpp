//---------------------------------------------------------------------------
//
//	DSC_IVirtualZoneManager.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IVirtualZone.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCredentials.hpp"

#ifndef _DSC_I_VIRTUAL_ZONE_MANAGER_HPP_
#define _DSC_I_VIRTUAL_ZONE_MANAGER_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IVirtualZoneManager	"DSC_IVirtualZoneManager"

//---------------------------------------------------------------------------

#ifndef DSC_IVirtualZoneManager_FWD_DEFINED
#define DSC_IVirtualZoneManager_FWD_DEFINED
typedef DSC_INTERFACE DSC_IVirtualZoneManager DSC_IVirtualZoneManager;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to request the list of enabled virtual zones
	on the panel.
*/
DSC_INTERFACE DSC_IVirtualZoneManager : public DSC_IComponent
{
public:

	//! Refreshes the list of enabled virtual zones on panel.
	/*! This function will issue the requisite commands to fetch the list of enabled virtual zones on the panel.  */
	/*!
		\sa DSC_IAccessCredentials
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to request the list of enabled virtual zones.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get the number of enabled virtual zones.
	/*! Returns the number of enabled virtual zones. */
	/*!
		\param ptrCount Pointer to storage for the number of enabled virtual zones.
	*/
	virtual IRESULT ICALL get_NumberOfVirtualZones(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Get a Virtual Zone interface.
	/*! Retrieves a Virtual Zone interface. This is a 0 based list index, NOT a system index. */
	/*!
		\sa DSC_IVirtualZone
		\param numIndex Requested 0 based list index of the virtual zone interface to get.
		\param ptrVirtualZone Pointer to storage for the requested virtual zone interface.
	*/
	virtual IRESULT ICALL get_VirtualZone(IN DSC_SIZE_T numIndex, OUT DSC_IVirtualZone** ptrVirtualZone) = 0;
};

#else

typedef struct DSC_IVirtualZoneManager_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IVirtualZoneManager *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IVirtualZoneManager *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IVirtualZoneManager *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IVirtualZoneManager *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_NumberOfVirtualZones)(IN DSC_IVirtualZoneManager *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_VirtualZone)(IN DSC_IVirtualZoneManager *This, 
		IN DSC_SIZE_T numIndex, OUT DSC_IVirtualZone** ptrVirtualZone);

	END_INTERFACE
} DSC_IVirtualZoneManager_Vtbl;

DSC_INTERFACE DSC_IVirtualZoneManager
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IVirtualZoneManager_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_VIRTUAL_ZONE_MANAGER_HPP_
