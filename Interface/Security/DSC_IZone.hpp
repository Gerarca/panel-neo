//---------------------------------------------------------------------------
//
//	DSC_IZone.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IZoneAttributes.hpp"
#include "DSC_IAlarmTypeContainer.hpp"
#include "DSC_ZoneAlarmInMemoryStates.hpp"
#include "DSC_ZoneAlarmStates.hpp"
#include "DSC_ZoneBypassStates.hpp"
#include "DSC_ZoneDelinquencyStates.hpp"
#include "DSC_ZoneFaultStates.hpp"
#include "DSC_ZoneOpenCloseStates.hpp"
#include "DSC_ZoneTamperStates.hpp"
#include "DSC_ZoneLowBatteryStates.hpp"
#include "DSC_ZoneLowSensitivityStates.hpp"
#include "DSC_ZoneMaskedStates.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCredentials.hpp"

#ifndef _DSC_I_ZONE_DATA_HPP_
#define _DSC_I_ZONE_DATA_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IZone	"DSC_IZone"

//---------------------------------------------------------------------------

#ifndef DSC_IZone_FWD_DEFINED
#define DSC_IZone_FWD_DEFINED
typedef DSC_INTERFACE DSC_IZone DSC_IZone;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for accessing properties and functionality
	related to a zone.
*/
DSC_INTERFACE DSC_IZone : public DSC_IComponent
{
public:

    //! Refreshes the zone information
	/*! This function will issue the requisite commands to get the Zone information. */
	/*!
		\sa DSC_IAccessCredentials
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to refresh the zone data.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get the Zone Label.
	/*! Returns the last retrieved Label for this zone. By default this is "Zone x" where x is the System Index     */
	/*! UTF8 Null terminated Zone label. */
	/*!
		\param ppszLabel Pointer to storage for a text string containing the Zone label.
	*/
	virtual IRESULT ICALL get_Label(OUT DSC_ITextString** ppszLabel) const = 0;

	//! Get the Zone System Index 
	/*! Gets the System Index for the Zone as assigned by the panel.
		For example, Zone 3 would return system index 3. */
		/*!
			\param ptrSystemIndex Pointer to storage for the Zone System Index.
		*/
	virtual IRESULT ICALL get_SystemIndex(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;

    //! Get the AlarmInMemoryState
    /*! Returns the last received Alarm In Memory state of this zone. 
		This indicates that within the last arming period there has been at least one Alarm on this Zone.     */
    /*!	
		\sa enum DSC_ZoneAlarmInMemoryState_Tag
      	\param ptrAlarmInMemoryState Pointer to storage for the AlarmInMemoryState data.
    */
	virtual IRESULT ICALL get_AlarmInMemoryState(OUT DSC_ZoneAlarmInMemoryState* ptrAlarmInMemoryState) const = 0;

    //! Get the AlarmState
    /*! Returns the last received Alarm state of this zone.   
		Indicates if this zone is currently in Alarm. */
    /*!	
		\sa enum DSC_ZoneAlarmState_Tag
    	\param ptrAlarmState Pointer to storage for the AlarmState data.
    */
	virtual IRESULT ICALL get_AlarmState(OUT DSC_ZoneAlarmState* ptrAlarmState) const = 0;

    //! Get the BypassState
    /*! Returns the last received Bypass state of this zone. 
		Indicates if this zone is currently Bypassed. */
    /*!	
		\sa enum DSC_ZoneBypassState_Tag
    	\param ptrBypassState Pointer to storage for the BypassState data.
    */
	virtual IRESULT ICALL get_BypassState(OUT DSC_ZoneBypassState* ptrBypassState) const = 0;

    //! Get the OpenCloseState
    /*! Returns the last received Opened / Closed state of this zone.     
		Indicates if this zone is currently opened / closed. */
    /*!	
		\sa enum DSC_ZoneOpenCloseState_Tag
    	\param ptrOpenCloseState - Pointer to storage for the OpenCloseState data.
    */
	virtual IRESULT ICALL get_OpenCloseState(OUT DSC_ZoneOpenCloseState* ptrOpenCloseState) const = 0;

    //! Get the TamperState
    /*! Returns the last received Tamper state of this zone.
		Indicates if this zone is currently Tampered. */
    /*!	
		\sa enum DSC_ZoneTamperState_Tag
    	\param ptrTamperState- Pointer to storage for the TamperState data.
    */
	virtual IRESULT ICALL get_TamperState(OUT DSC_ZoneTamperState* ptrTamperState) const = 0;

    //! Get the LowSensitivityState
    /*! Returns the last received Low Sensitivity state of this zone. 
		This is usually used for smoke detectors.    */
    /*!	
		\sa enum DSC_ZoneLowSensitivityState_Tag
    	\param ptrLowSensitivityState - Pointer to storage for the LowSensitivityState data.
    */
	virtual IRESULT ICALL get_LowSensitivityState(OUT DSC_ZoneLowSensitivityState* ptrLowSensitivityState) const = 0;

    //! Get the DelinquencyState
    /*! Returns the last received Zone Delinquency state of this zone. */
    /*!	
		\sa enum DSC_ZoneDelinquencyState_Tag
    	\param ptrDelinquencyState - Pointer to storage for the DelinquencyState data.
    */
	virtual IRESULT ICALL get_DelinquencyState(OUT DSC_ZoneDelinquencyState* ptrDelinquencyState) const = 0;

    //! Get the LowBatteryState
    /*! Returns the last received Low Battery state of this zone.     */
    /*!	
		\sa enum DSC_ZoneLowBatteryState_Tag
    	\param ptrLowBatteryState - Pointer to storage for the LowBatteryState data.
    */
	virtual IRESULT ICALL get_LowBatteryState(OUT DSC_ZoneLowBatteryState* ptrLowBatteryState) const = 0;

	//! Get the FaultState
    /*! Returns the last received Fault state of this zone.     */
    /*!	
		\sa enum DSC_ZoneFaultState_Tag
    	\param ptrFaultState - Pointer to storage for the FaultState data.
    */
	virtual IRESULT ICALL get_FaultState(OUT DSC_ZoneFaultState* ptrFaultState) const = 0;

	//! Get the Zone Attributes
	/*! Gets the attributes for the Zone.
		Zone Attributes are used to determine functionality of the zone. eg. bypass enable, swinger shutdown etc.     */
	/*!
		\param ptrAttributes Pointer to storage for the attributes assigned to this Zone
	*/
	virtual IRESULT ICALL get_Attributes(OUT DSC_IZoneAttributes** ptrAttributes) = 0;

	//! Write the Zone Label to the panel
	/*! This function will issue the requisite commands to change an Zone Label on the panel.
	*/
	/*!
		\param pszZoneLabel Provided UTF8 null terminated string containing the Zone Label to write.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL WriteZoneLabel(IN char const* pszZoneLabel, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Bypass or Unbypass a zone.
    /*! Allows bypassing or unbypassing of the zone. 
		This requires that the Zone has Bypassing enabled, and in addition bypassing a zone may require credentials sufficient to permit Zone Bypassing.  */
    /*!	
      	\param ptrAccessCredentials Provided Credentials with appropriate permissions to permit zone bypassing.
		\param flgBypass Provided bypass state to set for this Zone (FALSE to unbypass, TRUE to bypass)
		\param ptrRequestResult Pointer to storage for the result of the operation.
    */
	virtual IRESULT ICALL WriteZoneBypass(IN DSC_IAccessCredentials* ptrAccessCredentials, IN BOOL flgBypass, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get the list of alarmtypes on the zone.
	/*! Returns the list of the last known Alarm Types for this zone. */
	/*!
		\sa enum DSC_AlarmType_Tag
		\sa DSC_IAlarmTypeContainer
		\param ptrAlarmTypes - Pointer to the storage for the result interface.
	*/
	virtual IRESULT ICALL get_AlarmTypes(OUT DSC_IAlarmTypeContainer** ptrAlarmTypes) = 0;

	//! Get the MaskedState
    /*! Returns the last received Masked state of this zone.     */
    /*!	
		\sa enum DSC_ZoneMaskedState_Tag
    	\param ptrMaskedState - Pointer to storage for the MaskedState data.
    */
	virtual IRESULT ICALL get_MaskedState(OUT DSC_ZoneMaskedState* ptrMaskedState) const = 0;
};

#else

typedef struct DSC_IZone_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IZone *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IZone *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IZone *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IZone *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_Label)(IN DSC_IZone *This, OUT DSC_ITextString** ppszLabel);
	IRESULT (ICALL *get_SystemIndex)(IN DSC_IZone *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_AlarmInMemoryState)(IN DSC_IZone *This, OUT DSC_ZoneAlarmInMemoryState* ptrAlarmInMemoryState);
	IRESULT (ICALL *get_AlarmState)(IN DSC_IZone *This, OUT DSC_ZoneAlarmState* ptrAlarmState);
	IRESULT (ICALL *get_BypassState)(IN DSC_IZone *This, OUT DSC_ZoneBypassState* ptrBypassState);
	IRESULT (ICALL *get_OpenCloseState)(IN DSC_IZone *This, OUT DSC_ZoneOpenCloseState* ptrOpenCloseState);
	IRESULT (ICALL *get_TamperState)(IN DSC_IZone *This, OUT DSC_ZoneTamperState* ptrTamperState);
	IRESULT (ICALL *get_LowSensitivityState)(IN DSC_IZone *This, OUT DSC_ZoneLowSensitivityState* ptrLowSensitivityState);
	IRESULT (ICALL *get_DelinquencyState)(IN DSC_IZone *This, OUT DSC_ZoneDelinquencyState* ptrDelinquencyState);
	IRESULT (ICALL *get_LowBatteryState)(IN DSC_IZone *This, OUT DSC_ZoneLowBatteryState* ptrLowBatteryState);
	IRESULT (ICALL *get_FaultState)(IN DSC_IZone *This, OUT DSC_ZoneFaultState* ptrFaultState);
	IRESULT (ICALL *get_Attributes)(IN DSC_IZone *This, OUT DSC_IZoneAttributes** ptrAttributes);
	IRESULT (ICALL *WriteZoneLabel)(IN DSC_IZone *This, IN char const* pszZoneLabel, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *WriteZoneBypass)(IN DSC_IZone *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, IN BOOL flgBypass, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_AlarmTypes)(IN DSC_IZone *This, OUT DSC_IAlarmTypeContainer** ptrAlarmTypes);
	IRESULT (ICALL *get_MaskedState)(IN DSC_IZone *This, OUT DSC_ZoneMaskedState* ptrMaskedState);

	END_INTERFACE
} DSC_IZone_Vtbl;

DSC_INTERFACE DSC_IZone
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IZone_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_ZONE_DATA_HPP_
