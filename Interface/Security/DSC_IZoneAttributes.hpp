//---------------------------------------------------------------------------
//
//	DSC_IZoneAttributes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCredentials.hpp"
#include "DSC_IZoneAttributes.hpp"
#include "DSC_ZoneAttributesChimeFunctionStates.hpp"
#include "DSC_ZoneAttributesBypassEnableStates.hpp"

#ifndef _DSC_I_ZONE_ATTRIBUTES_HPP_
#define _DSC_I_ZONE_ATTRIBUTES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IZoneAttributes	"DSC_IZoneAttributes"

//---------------------------------------------------------------------------

#ifndef DSC_IZoneAttributes_FWD_DEFINED
#define DSC_IZoneAttributes_FWD_DEFINED
typedef DSC_INTERFACE DSC_IZoneAttributes DSC_IZoneAttributes;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for accessing information on zone attributes.
*/
DSC_INTERFACE DSC_IZoneAttributes : public DSC_IComponent
{
public:

	//! Refreshes the zone attribute data.
	/*! This function will issue the requisite commands to get the Attributes of the Zone.    */
	/*!
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to read the Zone Attributes.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;
	
	//! Writes the Zone attribute data to the panel
	/*! This function will issue the requisite commands to change the Attributes of the Zone.  */
	/*!
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to change the Zone Attributes.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL WriteZoneAttributes(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get the ChimeFunction
	/*! Gets the last received attribute data for if a Zone will activate the Door Chime when violated. */
	/*!	(NOTE: calling the Refresh function is required in order to get the current state data) */
	/*!
		\sa enum DSC_ZoneAttributesChimeFunctionState_Tag
		\param ptrChimeFunction Pointer to store the requested Attribute data.
	*/
	virtual IRESULT ICALL get_ChimeFunction(OUT DSC_ZoneAttributesChimeFunctionState* ptrChimeFunction) const = 0;

	//! Get the BypassEnable
	/*! Gets the last received attribute data for if a Zone can be Bypassed. */
	/*!	(NOTE: calling the Refresh function is required in order to get the current state data) */
	/*!
		\sa enum DSC_ZoneAttributesBypassEnableState_Tag
		\param ptrBypassEnable Pointer to store the requested Attribute data.
	*/
	virtual IRESULT ICALL get_BypassEnable(OUT DSC_ZoneAttributesBypassEnableState* ptrBypassEnable) const = 0;

	//! Set the ChimeFunction
	/*! Call the Set functions to set the attributes desired, then call WriteAccessCodeAttributes() to update the attributes on the panel.  */
	/*!
		\sa enum DSC_ZoneAttributesChimeFunctionState_Tag
		\param flgChimeFunction The value to set the Attribute to.
	*/
	virtual IRESULT ICALL set_ChimeFunction(IN DSC_ZoneAttributesChimeFunctionState flgChimeFunction) = 0;

	//! Set the BypassEnable
	/*! Call the Set functions to set the attributes desired, then call WriteZoneAttributes() to update the attributes on the panel.  */
	/*!
		\sa DSC_ZoneAttributesBypassEnableState_Tag
		\param flgBypassEnable The value to set the Attribute to.
	*/
	virtual IRESULT ICALL set_BypassEnable(IN DSC_ZoneAttributesBypassEnableState flgBypassEnable) = 0;

	//! Get the Zone System Index 
	/*! Gets the System Index for the Zone as assigned by the panel.
		For example, Zone 5 would return system index 5. */
		/*!

			\param ptrSystemIndex Pointer to storage for the Zone System Index
		*/
	virtual IRESULT ICALL get_SystemIndex(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;
};

#else

typedef struct DSC_IZoneAttributes_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IZoneAttributes *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IZoneAttributes *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IZoneAttributes *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IZoneAttributes *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *WriteZoneAttributes)(IN DSC_IZoneAttributes *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_ChimeFunction)(IN DSC_IZoneAttributes *This, OUT DSC_ZoneAttributesChimeFunctionState* ptrChimeFunction);
	IRESULT (ICALL *get_BypassEnable)(IN DSC_IZoneAttributes *This, OUT DSC_ZoneAttributesBypassEnableState* ptrBypassEnable);
	IRESULT (ICALL *set_ChimeFunction)(IN DSC_IZoneAttributes *This, IN DSC_ZoneAttributesChimeFunctionState flgChimeFunction);
	IRESULT (ICALL *set_BypassEnable)(IN DSC_IZoneAttributes *This, IN DSC_ZoneAttributesBypassEnableState flgBypassEnable);
	IRESULT (ICALL *get_SystemIndex)(IN DSC_IZoneAttributes *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);

	END_INTERFACE
} DSC_IZoneAttributes_Vtbl;

DSC_INTERFACE DSC_IZoneAttributes
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IZoneAttributes_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_ZONE_ATTRIBUTES_HPP_
