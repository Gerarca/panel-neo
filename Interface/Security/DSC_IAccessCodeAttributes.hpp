//---------------------------------------------------------------------------
//
//	DSC_IAccessCodeAttributes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCredentials.hpp"
#include "DSC_IAccessCodeAttributes.hpp"
#include "DSC_AccessCodeAttributesBellSquawkStates.hpp"
#include "DSC_AccessCodeAttributesCanBypassZoneStates.hpp"
#include "DSC_AccessCodeAttributesDuressCodeStates.hpp"
#include "DSC_AccessCodeAttributesOneTimeUseStates.hpp"
#include "DSC_AccessCodeAttributesRemoteAccessStates.hpp"
#include "DSC_AccessCodeAttributesSupervisorStates.hpp"

#ifndef _DSC_I_ACCESS_CODE_ATTRIBUTES_HPP_
#define _DSC_I_ACCESS_CODE_ATTRIBUTES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IAccessCodeAttributes	"DSC_IAccessCodeAttributes"

//---------------------------------------------------------------------------

#ifndef DSC_IAccessCodeAttributes_FWD_DEFINED
#define DSC_IAccessCodeAttributes_FWD_DEFINED
typedef DSC_INTERFACE DSC_IAccessCodeAttributes DSC_IAccessCodeAttributes;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for accessing information on access code attributes.
*/
DSC_INTERFACE DSC_IAccessCodeAttributes : public DSC_IComponent
{
public:

	//! Refreshes the access code attribute data.
	/*! This function will issue the requisite commands to get the Attributes of the Access Code.    */
	/*!
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to read the Access Code Attributes.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Writes the access code attributes to the panel
	/*! This function will issue the requisite commands to change the Attributes of the Access Code.      */
	/*!
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to change the Access Code Attributes.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL WriteAccessCodeAttributes(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get the CanBypassZone
	/*! Returns the last received CanBypassZone for this Access Code.     */
	/*!	(NOTE: calling the Refresh function is required in order to get the current state data) */
	/*!
		\sa enum DSC_AccessCodeAttributesCanBypassZoneState_Tag
		\param ptrCanBypassZone Pointer to storage for the CanBypassZone data.
	*/
	virtual IRESULT ICALL get_CanBypassZone(OUT DSC_AccessCodeAttributesCanBypassZoneState* ptrCanBypassZone) const = 0;
	
	//! Get the RemoteAccessEnabled
	/*! Returns the last received RemoteAccessEnabled for this Access Code.     */
	/*!	(NOTE: calling the Refresh function is required in order to get the current state data) */
	/*!
		\sa enum DSC_AccessCodeAttributesRemoteAccessState_Tag
		\param ptrRemoteAccessEnabled Pointer to storage for the RemoteAccessEnabled data.
	*/
	virtual IRESULT ICALL get_RemoteAccessEnabled(OUT DSC_AccessCodeAttributesRemoteAccessState* ptrRemoteAccessEnabled) const = 0;

	//! Get the OneTimeUse
	/*! Returns the last received OneTimeUse for this Access Code.     */
	/*!	(NOTE: calling the Refresh function is required in order to get the current state data) */
	/*!
		\sa enum DSC_AccessCodeAttributesOneTimeUseState_Tag
		\param ptrOneTimeUse Pointer to storage for the OneTimeUse data.
	*/
	virtual IRESULT ICALL get_OneTimeUse(OUT DSC_AccessCodeAttributesOneTimeUseState* ptrOneTimeUse) const = 0;
	
	//! Get the BellSquawk
	/*! Returns the last received BellSquawk for this Access Code.     */
	/*!	(NOTE: calling the Refresh function is required in order to get the current state data) */
	/*!
		\sa enum DSC_AccessCodeAttributesBellSquawkState_Tag
		\param ptrBellSquawk Pointer to storage for the BellSquawk data.
	*/
	virtual IRESULT ICALL get_BellSquawk(OUT DSC_AccessCodeAttributesBellSquawkState* ptrBellSquawk) const = 0;

	//! Get the Supervisor
	/*! Returns the last received Supervisor for this Access Code.     */
	/*!	(NOTE: calling the Refresh function is required in order to get the current state data) */
	/*!
		\sa enum DSC_AccessCodeAttributesSupervisorState_Tag
		\param ptrSupervisor Pointer to store the requested Attribute data.
	*/
	virtual IRESULT ICALL get_Supervisor(OUT DSC_AccessCodeAttributesSupervisorState* ptrSupervisor) const = 0;

	//! Get the DuressCode
	/*! Returns the last received DuressCode for this Access Code.     */
	/*!	(NOTE: calling the Refresh function is required in order to get the current state data) */
	/*!
		\sa enum DSC_AccessCodeAttributesDuressCodeState_Tag
		\param ptrDuressCode Pointer to store the requested Attribute data.
	*/
	virtual IRESULT ICALL get_DuressCode(OUT DSC_AccessCodeAttributesDuressCodeState* ptrDuressCode) const = 0;
	
	//! Set the CanBypassZone 
	/*! Call the Set functions to set the attributes desired, then call WriteAccessCodeAttributes() to update the attributes on the panel.     */
	/*!
		\sa enum DSC_AccessCodeAttributesCanBypassZoneState_Tag
		\param flgCanBypassZone The value to set the Attribute to.
	*/
	virtual IRESULT ICALL set_CanBypassZone(IN DSC_AccessCodeAttributesCanBypassZoneState flgCanBypassZone) = 0;

	//! Set the RemoteAccessEnabled
	/*! Call the Set functions to set the attributes desired, then call WriteAccessCodeAttributes() to update the attributes on the panel.     */
	/*!
		\sa enum DSC_AccessCodeAttributesRemoteAccessState_Tag
		\param flgRemoteAccessEnabled The value to set the Attribute to.
	*/
	virtual IRESULT ICALL set_RemoteAccessEnabled(IN DSC_AccessCodeAttributesRemoteAccessState flgRemoteAccessEnabled) = 0;

	//! Set the OneTimeUse
	/*! Call the Set functions to set the attributes desired, then call WriteAccessCodeAttributes() to update the attributes on the panel.   */
	/*!
		\sa enum DSC_AccessCodeAttributesOneTimeUseState_Tag
		\param flgOneTimeUse The value to set the Attribute to.
	*/
	virtual IRESULT ICALL set_OneTimeUse(IN DSC_AccessCodeAttributesOneTimeUseState flgOneTimeUse) = 0;

	//! Set the BellSquawk
	/*! Call the Set functions to set the attributes desired, then call WriteAccessCodeAttributes() to update the attributes on the panel.    */
	/*!
		\sa enum DSC_AccessCodeAttributesBellSquawkState_Tag
		\param flgBellSquawk The value to set the Attribute to.
	*/
	virtual IRESULT ICALL set_BellSquawk(IN DSC_AccessCodeAttributesBellSquawkState flgBellSquawk) = 0;

	//! Set the Supervisor
	/*! Call the Set functions to set the attributes desired, then call WriteAccessCodeAttributes() to update the attributes on the panel.    */
	/*!
		\sa enum DSC_AccessCodeAttributesSupervisorState_Tag
		\param flgSupervisor The value to set the Attribute to.
	*/
	virtual IRESULT ICALL set_Supervisor(IN DSC_AccessCodeAttributesSupervisorState flgSupervisor) = 0;

	//! Set the DuressCode
	/*! Call the Set functions to set the attributes desired, then call WriteAccessCodeAttributes() to update the attributes on the panel.     */
	/*!
		\sa enum DSC_AccessCodeAttributesDuressCodeState_Tag
		\param flgDuressCode The value to set the Attribute to.
	*/
	virtual IRESULT ICALL set_DuressCode(IN DSC_AccessCodeAttributesDuressCodeState flgDuressCode) = 0;

    //! Get the Access Code System Index 
	/*! Gets the System Index for the Access Code as assigned by the panel.
		For example, User Code 5 would return system index 5. */
	/*!

      	\param ptrSystemIndex Pointer to storage for the Access Code System Index
    */
	virtual IRESULT ICALL get_SystemIndex(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;
};

#else

typedef struct DSC_IAccessCodeAttributes_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IAccessCodeAttributes *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IAccessCodeAttributes *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IAccessCodeAttributes *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IAccessCodeAttributes *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *WriteAccessCodeAttributes)(IN DSC_IAccessCodeAttributes *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_CanBypassZone)(IN DSC_IAccessCodeAttributes *This, 
		OUT DSC_AccessCodeAttributesCanBypassZoneState* ptrCanBypassZone);
	IRESULT (ICALL *get_RemoteAccessEnabled)(IN DSC_IAccessCodeAttributes *This, 
		OUT DSC_AccessCodeAttributesRemoteAccessState* ptrRemoteAccessEnabled);
	IRESULT (ICALL *get_OneTimeUse)(IN DSC_IAccessCodeAttributes *This, 
		OUT DSC_AccessCodeAttributesOneTimeUseState* ptrOneTimeUse);
	IRESULT (ICALL *get_BellSquawk)(IN DSC_IAccessCodeAttributes *This, 
		OUT DSC_AccessCodeAttributesBellSquawkState* ptrBellSquawk);
	IRESULT (ICALL *get_Supervisor)(IN DSC_IAccessCodeAttributes *This, 
		OUT DSC_AccessCodeAttributesSupervisorState* ptrSupervisor);
	IRESULT (ICALL *get_DuressCode)(IN DSC_IAccessCodeAttributes *This, 
		OUT DSC_AccessCodeAttributesDuressCodeState* ptrDuressCode);
	IRESULT (ICALL *set_CanBypassZone)(IN DSC_IAccessCodeAttributes *This, 
		IN DSC_AccessCodeAttributesCanBypassZoneState flgCanBypassZone);
	IRESULT (ICALL *set_RemoteAccessEnabled)(IN DSC_IAccessCodeAttributes *This, 
		IN DSC_AccessCodeAttributesRemoteAccessState flgRemoteAccessEnabled);
	IRESULT (ICALL *set_OneTimeUse)(IN DSC_IAccessCodeAttributes *This, 
		IN DSC_AccessCodeAttributesOneTimeUseState flgOneTimeUse);
	IRESULT (ICALL *set_BellSquawk)(IN DSC_IAccessCodeAttributes *This, 
		IN DSC_AccessCodeAttributesBellSquawkState flgBellSquawk);
	IRESULT (ICALL *set_Supervisor)(IN DSC_IAccessCodeAttributes *This, 
		IN DSC_AccessCodeAttributesSupervisorState flgSupervisor);
	IRESULT (ICALL *set_DuressCode)(IN DSC_IAccessCodeAttributes *This, 
		IN DSC_AccessCodeAttributesDuressCodeState flgDuressCode);
	IRESULT (ICALL *get_SystemIndex)(IN DSC_IAccessCodeAttributes *This, 
		OUT DSC_SYSTEM_INDEX* ptrSystemIndex);

	END_INTERFACE
} DSC_IAccessCodeAttributes_Vtbl;

DSC_INTERFACE DSC_IAccessCodeAttributes
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IAccessCodeAttributes_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_ACCESS_CODE_ATTRIBUTES_HPP_
