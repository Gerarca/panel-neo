//---------------------------------------------------------------------------
//
//	DSC_IPartition.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IPartitionStateData.hpp"
#include "DSC_IAlarmTypeContainer.hpp"
#include "DSC_IZoneManager.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCodeManager.hpp"
#include "DSC_IAccessCredentials.hpp"
#include "DSC_FAPTypes.hpp"
#include "DSC_DoorChimeEnabledStates.hpp"
#include "DSC_CommandOutputStates.hpp"

#ifndef _DSC_I_PARTITION_DATA_HPP_
#define _DSC_I_PARTITION_DATA_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IPartition		"DSC_IPartition"

//---------------------------------------------------------------------------

#ifndef DSC_IPartition_FWD_DEFINED
#define DSC_IPartition_FWD_DEFINED
typedef DSC_INTERFACE DSC_IPartition DSC_IPartition;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for accessing properties and functionality
	related to a partition.
*/
DSC_INTERFACE DSC_IPartition : public DSC_IComponent
{
public:

    //! Refreshes the partition data.
    /*! This function will issue the requisite commands to get the Partition information. */
    /*!	
		\sa DSC_IAccessCredentials
      	\param ptrAccessCredentials Provided Credentials with appropriate permissions to refresh the partition data.
      	\param ptrRequestResult Pointer to storage for the result of the operation.
    */
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Get the Partition Label.
	/*! Returns the last retrieved Label for this partition. By default this is "Partition x" where x is the System Index     */
	/*! UTF8 Null terminated Partition label. */
    /*!	
      	\param ppszLabel Pointer to storage for a text string containing the Partition label. 
    */
	virtual IRESULT ICALL get_Label(OUT DSC_ITextString** ppszLabel) const = 0;

    //! Get the enabled/disabled status of the Partition on the panel.
    /*! Returns the last retrieved enabled/disabled status for the Partition. */
    /*!	
      	\param ptrEnabled Pointer to storage for the enabled/disabled data.
    */
	virtual IRESULT ICALL get_Enabled(OUT BOOL* ptrEnabled) const = 0;

    //! Get the Partition System Index 
    /*! Gets the System Index for the Partition as assigned by the panel.
		For example, Partition 1 would return system index 1. */
	/*!	
      	\param ptrSystemIndex Pointer to storage for the Partition System Index.
    */
	virtual IRESULT ICALL get_SystemIndex(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;

    //! Get the PartitionStateData
    /*! Returns the last retrieved PartitionStateData for this Partition. 
		All of the relevant state information such as armed / trouble status is contained within this result.    
	*/
    /*!	
	    \sa DSC_IPartitionStateData
      	\param ptrStateData Pointer to storage for PartitionStateData information.
    */
	virtual IRESULT ICALL get_PartitionStateData(OUT DSC_IPartitionStateData** ptrStateData) = 0;

    //! Get the Zone Manager
    /*! Returns the Zone Manager interface of this partition. The Zone Manager contains the list of
		zones assigned to this partition.
	*/
    /*!	
	    \sa DSC_IZoneManager
      	\param ptrZoneManager Pointer to storage for the Zone Manager.
    */
	virtual IRESULT ICALL get_ZoneManager(OUT DSC_IZoneManager** ptrZoneManager) = 0;

    //! Get the Access Code Manager
    /*! Returns the Access Code Manager interface of this partition. The Access Code Manager contains the list of
		access code assigned to this partition.
	*/
    /*!	
	    \sa DSC_IAccessCodeManager
      	\param ptrAccessCodeManager Pointer to storage for the Access Code Manager.
    */
	virtual IRESULT ICALL get_AccessCodeManager(OUT DSC_IAccessCodeManager** ptrAccessCodeManager) = 0;

    //! Write the Partition label to the panel.
    /*! This function will issue the requisite commands to change an Partition label on the panel.
		This function may not be successful depending on the Partition state. 
	*/
    /*!	
      	\param pszPartitionLabel Provided UTF8 null terminated string containing Partition Label to write
      	\param ptrRequestResult Pointer to storage for the result of the operation.
    */
	virtual IRESULT ICALL WritePartitionLabel(IN char const* pszPartitionLabel, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Arms the partition in the provided mode using the provided AccessCredentials.
    /*! This function will issue the requisite commands to Arm (or change the arming level, if applicable) this Partition using the specified credentials.
		Note: Despite DSC_PartitionArmedState having an enumeration for a Disarmed state, you must explicitly use DisarmPartitionWithAccessCredentials to disarm a Partition.*/
    /*!	
		\sa enum DSC_PartitionArmedState_Tag
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to Arm the partition.
		\param flgPartitionArmingMode Provided Partition Arming mode.
      	\param ptrRequestResult Pointer to storage for the result of the operation. 
    */
	virtual IRESULT ICALL ArmPartitionWithAccessCredentials(IN DSC_IAccessCredentials* ptrAccessCredentials, IN DSC_PartitionArmedState flgPartitionArmingMode, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Disarms the partition using the provided AccessCredentials.
    /*! This function will issue the requsite commands to Disarm the Partititon using the specified credentials. */
    /*!	
      	\param ptrAccessCredentials Provided Credentials with appropriate permissions to Disarm the partition.
      	\param ptrRequestResult Pointer to storage for the result of the operation. 
    */
	virtual IRESULT ICALL DisarmPartitionWithAccessCredentials(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Silences the trouble beeps for the partition.
    /*! This function will issue the requsite commands to Silence Trouble Beeps, using the specified credentials if required. */
    /*!	
      	\param ptrAccessCredentials Provided Credentials with appropriate permissions to Disarm the partition.
      	\param ptrRequestResult Pointer to storage for the result of the operation. 
    */
	virtual IRESULT ICALL SilenceTroubleBeepsForThisPartition(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Activate keypad emergency function on the partition
	/*! This function will issue the requsite commands to initiate keypad emergency alarms. 
		This functionality must be enabled on the panel in order for this function to be accepted.
	*/
	/*!
		\sa enum DSC_FAPType_Tag
		\param flgFAPType Provided emergency alarm type to activate.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL ActivateFAP(IN DSC_FAPType flgFAPType, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get the DoorChimeEnabledState.
	/*! Returns the last retrieved DoorChime state of the partition.     */
	/*!
		\sa enum DSC_DoorChimeEnabledState_Tag
		\param ptrDoorChimeEnabledState Pointer to storage for the DoorChimeEnabled data.
	*/
	virtual IRESULT ICALL get_DoorChimeEnabledState(OUT DSC_DoorChimeEnabledState* ptrDoorChimeEnabledState) const = 0;

	//! Write the DoorChimeEnabledState to the panel
	/*! This function will issue the requisite commands to set the Door Chime Enabled of the partition, using the provided credentials. */
	/*!
		\sa enum DSC_DoorChimeEnabledState_Tag
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to change the DoorChimeEnable of the partition
		\param flgDoorChimeEnabledState Provided DoorChimeEnableState to write to the partition.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL WriteDoorChimeEnabledState(IN DSC_IAccessCredentials* ptrAccessCredentials, IN DSC_DoorChimeEnabledState flgDoorChimeEnabledState, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Activate the requested Command Output on this partition
	/*! This function will issue the requsite commands to Activate the requested Command Output. */
	/*!
		\sa enum DSC_CommandOutputState_Tag
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to activate the command output.
		\param numOutputNumber Provided Command Output number.
		\param flgCommandOutputState Provided state to set the Command Output to.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL ActivateCommandOutput(IN DSC_IAccessCredentials* ptrAccessCredentials, IN BYTE numOutputNumber, IN DSC_CommandOutputState flgCommandOutputState, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get the list of alarmtypes on the partition.
    /*! Returns the list of the last known Alarm Types for this partition. */
    /*!	
		\sa enum DSC_AlarmType_Tag
		\sa DSC_IAlarmTypeContainer
    	\param ptrAlarmTypes - Pointer to the storage for the result interface.
    */
	virtual IRESULT ICALL get_AlarmTypes(OUT DSC_IAlarmTypeContainer** ptrAlarmTypes) = 0;
};

#else

typedef struct DSC_IPartition_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IPartition *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IPartition *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IPartition *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IPartition *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_Label)(IN DSC_IPartition *This, OUT DSC_ITextString** ppszLabel);
	IRESULT (ICALL *get_Enabled)(IN DSC_IPartition *This, OUT BOOL* ptrEnabled);
	IRESULT (ICALL *get_SystemIndex)(IN DSC_IPartition *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_PartitionStateData)(IN DSC_IPartition *This, OUT DSC_IPartitionStateData** ptrStateData);
	IRESULT (ICALL *get_ZoneManager)(IN DSC_IPartition *This, OUT DSC_IZoneManager** ptrZoneManager);
	IRESULT (ICALL *get_AccessCodeManager)(IN DSC_IPartition *This, OUT DSC_IAccessCodeManager** ptrAccessCodeManager);
	IRESULT (ICALL *WritePartitionLabel)(IN DSC_IPartition *This, IN char const* pszPartitionLabel, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *ArmPartitionWithAccessCredentials)(IN DSC_IPartition *This, IN DSC_IAccessCredentials* ptrAccessCredentials, 
		IN DSC_PartitionArmedState flgPartitionArmingMode, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *DisarmPartitionWithAccessCredentials)(IN DSC_IPartition *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *SilenceTroubleBeepsForThisPartition)(IN DSC_IPartition *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *ActivateFAP)(IN DSC_IPartition *This, IN DSC_FAPType flgFAPType, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_DoorChimeEnabledState)(IN DSC_IPartition *This, OUT DSC_DoorChimeEnabledState* ptrDoorChimeEnabledState);
	IRESULT (ICALL *WriteDoorChimeEnabledState)(IN DSC_IPartition *This, IN DSC_IAccessCredentials* ptrAccessCredentials, 
		IN DSC_DoorChimeEnabledState flgDoorChimeEnabledState, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *ActivateCommandOutput)(IN DSC_IPartition *This, IN DSC_IAccessCredentials* ptrAccessCredentials, 
		IN BYTE numOutputNumber, IN DSC_CommandOutputState flgCommandOutputState, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_AlarmTypes)(IN DSC_IZone *This, OUT DSC_IAlarmTypeContainer** ptrAlarmTypes);

	END_INTERFACE
} DSC_IPartition_Vtbl;

DSC_INTERFACE DSC_IPartition
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IPartition_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_PARTITION_DATA_HPP_
