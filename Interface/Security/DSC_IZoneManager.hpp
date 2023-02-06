//---------------------------------------------------------------------------
//
//	DSC_IZoneManager.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IZone.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCredentials.hpp"

#ifndef _DSC_I_ZONE_MANAGER_HPP_
#define _DSC_I_ZONE_MANAGER_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IZoneManager	"DSC_IZoneManager"

//---------------------------------------------------------------------------

#ifndef DSC_IZoneManager_FWD_DEFINED
#define DSC_IZoneManager_FWD_DEFINED
typedef DSC_INTERFACE DSC_IZoneManager DSC_IZoneManager;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to request the list of enabled zones
	on the panel.
*/
DSC_INTERFACE DSC_IZoneManager : public DSC_IComponent
{
public:

	//! Refreshes the list of enabled zones on panel.
	/*! This function will issue the requisite commands to fetch the list of enabled zones on the panel.  */
	/*!
		\sa DSC_IAccessCredentials
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to request the list of enabled zones.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get the number of enabled zones.
	/*! Returns the number of enabled zones. */
	/*!
		\param ptrCount Pointer to storage for the number of enabled zones.
	*/
	virtual IRESULT ICALL get_NumberOfZones(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Get a Zone interface.
	/*! Retrieves a Zone interface. This is a 0 based list index, NOT a system index. */
	/*!
		\sa DSC_IZone
		\param numIndex Requested 0 based list index of the zone interface to get.
		\param ptrZone Pointer to storage for the requested zone interface.
	*/
	virtual IRESULT ICALL get_Zone(IN DSC_SIZE_T numIndex, OUT DSC_IZone** ptrZone) = 0;
};

#else

typedef struct DSC_IZoneManager_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IZoneManager *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IZoneManager *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IZoneManager *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IZoneManager *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_NumberOfZones)(IN DSC_IZoneManager *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_Zone)(IN DSC_IZoneManager *This, IN DSC_SIZE_T numIndex, OUT DSC_IZone** ptrZone);

	END_INTERFACE
} DSC_IZoneManager_Vtbl;

DSC_INTERFACE DSC_IZoneManager
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IZoneManager_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_ZONE_MANAGER_HPP_
