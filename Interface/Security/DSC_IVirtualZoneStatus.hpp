//---------------------------------------------------------------------------
//
//	DSC_IVirtualZoneStatus.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCredentials.hpp"
#include "DSC_VirtualZoneStatusOpenStates.hpp"
#include "DSC_VirtualZoneStatusTamperStates.hpp"
#include "DSC_VirtualZoneStatusFaultStates.hpp"
#include "DSC_VirtualZoneStatusLowBatteryStates.hpp"
#include "DSC_VirtualZoneStatusACTroubleStates.hpp"
#include "DSC_VirtualZoneStatusMaskedStates.hpp"

#ifndef _DSC_I_VIRTUAL_ZONE_STATUS_HPP_
#define _DSC_I_VIRTUAL_ZONE_STATUS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IVirtualZoneStatus	"DSC_IVirtualZoneStatus"

//---------------------------------------------------------------------------

#ifndef DSC_IVirtualZoneStatus_FWD_DEFINED
#define DSC_IVirtualZoneStatus_FWD_DEFINED
typedef DSC_INTERFACE DSC_IVirtualZoneStatus DSC_IVirtualZoneStatus;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for accessing the Virtual Zone Status information.
*/
DSC_INTERFACE DSC_IVirtualZoneStatus : public DSC_IComponent
{
public:

	//! Refreshes the Virtual Zone Status data
	/*! This function will issue the requisite commands to get the Virtual Zone Status information.  */
	/*!
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to read the Virtual Zone Status data.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;
	
	//! Writes the virtual zone status data to the panel
	/*! This function will issue the requisite commands to change the Virtual Zone Status data on the panel.  */
	/*!
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL WriteVirtualZoneStatus(OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get the Open
	/*! Returns the last received Open state for this Virtual Zone.     
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
	/*!
		\sa enum DSC_VirtualZoneStatusOpenState_Tag
		\param ptrOpen Pointer to store the requested data.
	*/
	virtual IRESULT ICALL get_Open(OUT DSC_VirtualZoneStatusOpenState* ptrOpen) const = 0;

	//! Get the Tamper
	/*! Returns the last received Tamper state for this Virtual Zone.     
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
	/*!
		\sa enum DSC_VirtualZoneStatusTamperState_Tag
		\param ptrTamper Pointer to store the requested data.
	*/
	virtual IRESULT ICALL get_Tamper(OUT DSC_VirtualZoneStatusTamperState* ptrTamper) const = 0;

	//! Get the Fault
	/*! Returns the last received Fault state for this Virtual Zone.     
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
	/*!
		\sa enum DSC_VirtualZoneStatusFaultState_Tag
		\param ptrFault Pointer to store the requested data.
	*/
	virtual IRESULT ICALL get_Fault(OUT DSC_VirtualZoneStatusFaultState* ptrFault) const = 0;

	//! Get the LowBattery
	/*! Returns the last received LowBattery state for this Virtual Zone.     
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
	/*!
		\sa enum DSC_VirtualZoneStatusLowBatteryState_Tag
		\param ptrLowBattery Pointer to store the requested data.
	*/
	virtual IRESULT ICALL get_LowBattery(OUT DSC_VirtualZoneStatusLowBatteryState* ptrLowBattery) const = 0;

	//! Get the ACTrouble
	/*! Returns the last received ACTrouble state for this Virtual Zone.     
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
	/*!
		\sa enum DSC_VirtualZoneStatusACTroubleState_Tag
		\param ptrACTrouble Pointer to store the requested data.
	*/
	virtual IRESULT ICALL get_ACTrouble(OUT DSC_VirtualZoneStatusACTroubleState* ptrACTrouble) const = 0;

	//! Set the Open
	/*! Call the Set functions to set the desired statuses, then call WriteAccessCodeAttributes() to update the statuses on the panel.     */
	/*!
		\sa enum DSC_VirtualZoneStatusOpenState_Tag
		\param flgOpen The Open state data.
	*/
	virtual IRESULT ICALL set_Open(IN DSC_VirtualZoneStatusOpenState flgOpen) = 0;

	//! Set the Tamper
	/*! Call the Set functions to set the desired statuses, then call WriteAccessCodeAttributes() to update the statuses on the panel.     */
	/*!
		\sa enum DSC_VirtualZoneStatusTamperState_Tag
		\param flgTamper The Tamper state data.
	*/
	virtual IRESULT ICALL set_Tamper(IN DSC_VirtualZoneStatusTamperState flgTamper) = 0;

	//! Set the Fault
	/*! Call the Set functions to set the desired statuses, then call WriteAccessCodeAttributes() to update the statuses on the panel.     */
	/*!
		\sa enum DSC_VirtualZoneStatusFaultState_Tag
		\param flgFault The Fault state data.
	*/
	virtual IRESULT ICALL set_Fault(IN DSC_VirtualZoneStatusFaultState flgFault) = 0;

	//! Set the LowBattery
	/*! Call the Set functions to set the desired statuses, then call WriteAccessCodeAttributes() to update the statuses on the panel.     */
	/*!
		\sa enum DSC_VirtualZoneStatusLowBatteryState_Tag
		\param flgLowBattery The LowBattery state data.
	*/
	virtual IRESULT ICALL set_LowBattery(IN DSC_VirtualZoneStatusLowBatteryState flgLowBattery) = 0;

	//! Set the ACTrouble
	/*! Call the Set functions to set the desired statuses, then call WriteAccessCodeAttributes() to update the statuses on the panel.     */
	/*!
		\sa enum DSC_VirtualZoneStatusACTroubleState_Tag
		\param flgACTrouble The ACTrouble state data.
	*/
	virtual IRESULT ICALL set_ACTrouble(IN DSC_VirtualZoneStatusACTroubleState flgACTrouble) = 0;

    //! Get the Virtual Zone System Index
	/*! Gets the System Index for the Virtual Zone as assigned by the panel.
		For example, Virtual Zone 3 would return system index 3.     */
	/*!
		\param ptrSystemIndex Pointer to storage for the Virtual Zone System Index
	*/
	virtual IRESULT ICALL get_SystemIndex(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;

	//! Get the Masked 
	/*! Returns the last received Masked state for this Virtual Zone.
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
	/*!
		\sa enum DSC_VirtualZoneStatusMaskedState_Tag
		\param ptrMasked Pointer to store the requested data.
	*/
	virtual IRESULT ICALL get_Masked(OUT DSC_VirtualZoneStatusMaskedState* ptrMasked) const = 0;

	//! Set the Masked
	/*! Call the Set functions to set the desired statuses, then call WriteAccessCodeAttributes() to update the statuses on the panel.     */
	/*!
		\sa enum DSC_VirtualZoneStatusMaskedState_Tag
		\param flgMasked The Masked state data.
	*/
	virtual IRESULT ICALL set_Masked(IN DSC_VirtualZoneStatusMaskedState flgMasked) = 0;

};

#else

typedef struct DSC_IVirtualZoneStatus_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IVirtualZoneStatus *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IVirtualZoneStatus *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IVirtualZoneStatus *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IVirtualZoneStatus *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *WriteVirtualZoneStatus)(IN DSC_IVirtualZoneStatus *This, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_Open)(IN DSC_IVirtualZoneStatus *This, OUT DSC_VirtualZoneStatusOpenState* ptrOpen);
	IRESULT (ICALL *get_Tamper)(IN DSC_IVirtualZoneStatus *This, OUT DSC_VirtualZoneStatusTamperState* ptrTamper);
	IRESULT (ICALL *get_Fault)(IN DSC_IVirtualZoneStatus *This, OUT DSC_VirtualZoneStatusFaultState* ptrFault);
	IRESULT (ICALL *get_LowBattery)(IN DSC_IVirtualZoneStatus *This, OUT DSC_VirtualZoneStatusLowBatteryState* ptrLowBattery);
	IRESULT (ICALL *get_ACTrouble)(IN DSC_IVirtualZoneStatus *This, OUT DSC_VirtualZoneStatusACTroubleState* ptrACTrouble);
	IRESULT (ICALL *set_Open)(IN DSC_IVirtualZoneStatus *This, IN DSC_VirtualZoneStatusOpenState flgOpen);
	IRESULT (ICALL *set_Tamper)(IN DSC_IVirtualZoneStatus *This, IN DSC_VirtualZoneStatusTamperState flgTamper);
	IRESULT (ICALL *set_Fault)(IN DSC_IVirtualZoneStatus *This, IN DSC_VirtualZoneStatusFaultState flgFault);
	IRESULT (ICALL *set_LowBattery)(IN DSC_IVirtualZoneStatus *This, IN DSC_VirtualZoneStatusLowBatteryState flgLowBattery);
	IRESULT (ICALL *set_ACTrouble)(IN DSC_IVirtualZoneStatus *This, IN DSC_VirtualZoneStatusACTroubleState flgACTrouble);
	IRESULT (ICALL *get_SystemIndex)(IN DSC_IVirtualZoneStatus *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_Masked)(IN DSC_IVirtualZoneStatus *This, OUT DSC_VirtualZoneStatusMaskedState* ptrMasked);
	IRESULT (ICALL *set_Masked)(IN DSC_IVirtualZoneStatus *This, IN DSC_VirtualZoneStatusMaskedState flgMasked);

	END_INTERFACE
} DSC_IVirtualZoneStatus_Vtbl;

DSC_INTERFACE DSC_IVirtualZoneStatus
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IVirtualZoneStatus_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_VIRTUAL_ZONE_STATUS_HPP_