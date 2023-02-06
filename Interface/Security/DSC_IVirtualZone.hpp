//---------------------------------------------------------------------------
//
//	DSC_IVirtualZone.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCredentials.hpp"
#include "DSC_IVirtualZoneStatus.hpp"

#ifndef _DSC_I_VIRTUAL_ZONE_HPP_
#define _DSC_I_VIRTUAL_ZONE_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IVirtualZone	"DSC_IVirtualZone"

//---------------------------------------------------------------------------

#ifndef DSC_IVirtualZone_FWD_DEFINED
#define DSC_IVirtualZone_FWD_DEFINED
typedef DSC_INTERFACE DSC_IVirtualZone DSC_IVirtualZone;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for accessing virtual zone information.
*/
DSC_INTERFACE DSC_IVirtualZone : public DSC_IComponent
{
public:

	//! Refreshes the Virtual Zone data
	/*! This function will issue the requisite commands to get the Virtual Zone information.  */
	/*!
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to read the Virtual Zone data.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Get the Virtual Zone System Index
	/*! Gets the System Index for the Virtual Zone as assigned by the panel.
		For example, Virtual Zone 3 would return system index 3.     */
	/*!
		\param ptrSystemIndex Pointer to storage for the Virtual Zone System Index
	*/
	virtual IRESULT ICALL get_SystemIndex(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;

    //! Get the Zone Number
    /*! Returns the Zone System Index that the Virtual Zone is assigned to on the panel.  */
    /*!	
      	\param ptrZoneNumber Pointer to storage for the Zone Number the Virtual Zone is assigned to.
    */
	virtual IRESULT ICALL get_ZoneNumber(OUT DSC_SYSTEM_INDEX* ptrZoneNumber) const = 0;

    //! Get the VirtualZoneStatus
    /*! Returns the last retrieved VirtualZoneStatus for this Virtual Zone.  */
    /*!	
		\sa DSC_IVirtualZoneStatus
      	\param ptrStatus Pointer to storage for the VirtualZoneStatus information.
    */
	virtual IRESULT ICALL get_VirtualZoneStatus(OUT DSC_IVirtualZoneStatus** ptrStatus) = 0;
};

#else

typedef struct DSC_IVirtualZone_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IVirtualZone *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IVirtualZone *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IVirtualZone *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IVirtualZone *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_SystemIndex)(IN DSC_IVirtualZone *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_ZoneNumber)(IN DSC_IVirtualZone *This, OUT DSC_SYSTEM_INDEX* ptrZoneNumber);
	IRESULT (ICALL *get_VirtualZoneStatus)(IN DSC_IVirtualZone *This, OUT DSC_IVirtualZoneStatus** ptrStatus);

	END_INTERFACE
} DSC_IVirtualZone_Vtbl;

DSC_INTERFACE DSC_IVirtualZone
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IVirtualZone_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_VIRTUAL_ZONE_HPP_