//---------------------------------------------------------------------------
//
//	DSC_IPartitionStateData.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_PartitionBuzzerStates.hpp"
#include "DSC_PartitionQuickExitStates.hpp"
#include "DSC_PartitionReadyStates.hpp"
#include "DSC_PartitionArmedStates.hpp"
#include "DSC_PartitionBlankStates.hpp"
#include "DSC_PartitionTroubleStates.hpp"
#include "DSC_PartitionBypassStates.hpp"
#include "DSC_PartitionAlarmStates.hpp"
#include "DSC_PartitionAlarmMemoryStates.hpp"
#include "DSC_PartitionBusyStates.hpp"
#include "DSC_PartitionAudibleBellStates.hpp"
#include "DSC_PartitionAudibleBellTypes.hpp"
#include "DSC_PartitionExitDelayStates.hpp"
#include "DSC_PartitionEntryDelayStates.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCredentials.hpp"

#ifndef _DSC_I_PARTITION_STATE_DATA_HPP_
#define _DSC_I_PARTITION_STATE_DATA_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IPartitionStateData	"DSC_IPartitionStateData"

//---------------------------------------------------------------------------

#ifndef DSC_IPartitionStateData_FWD_DEFINED
#define DSC_IPartitionStateData_FWD_DEFINED
typedef DSC_INTERFACE DSC_IPartitionStateData DSC_IPartitionStateData;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for accessing partition state information.
*/
DSC_INTERFACE DSC_IPartitionStateData : public DSC_IComponent
{
public:

    //! Get the PartitionBuzzerState
    /*! Returns the last received PartitionBuzzerState for this Partition.
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionBuzzerState_Tag
      	\param ptrBuzzerState Pointer to storage for the PartitionBuzzerState data.
    */
	virtual IRESULT ICALL get_PartitionBuzzerState(OUT DSC_PartitionBuzzerState* ptrBuzzerState) const = 0;

    //! Get the PartitionQuickExitState
    /*! Returns the last received PartitionQuickExitState for this Partition.  
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionQuickExitState_Tag
      	\param ptrQuickExitState Pointer to storage for the PartitionQuickExitState data.
    */
	virtual IRESULT ICALL get_PartitionQuickExitState(OUT DSC_PartitionQuickExitState* ptrQuickExitState) const = 0;

    //! Get the PartitionReadyState
    /*! Returns the last received PartitionReadyState for this Partition. 
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionReadyState_Tag
      	\param ptrReadyState Pointer to storage for the PartitionReadyState data.
    */
	virtual IRESULT ICALL get_PartitionReadyState(OUT DSC_PartitionReadyState* ptrReadyState) const = 0;

    //! Get the PartitionArmedState
    /*! Returns the last received PartitionArmedState for this Partition.
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionArmedState_Tag
      	\param ptrArmedState Pointer to storage for the PartitionArmedState data.
    */
	virtual IRESULT ICALL get_PartitionArmedState(OUT DSC_PartitionArmedState* ptrArmedState) const = 0;

    //! Get the PartitionBlankState
    /*! Returns the last received PartitionKeypadBlankState for this Partition.
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionBlankState_Tag
      	\param ptrBlankState Pointer to storage for the PartitionBlankState data.
    */
	virtual IRESULT ICALL get_PartitionBlankState(OUT DSC_PartitionBlankState* ptrBlankState) const = 0;

    //! Get the PartitionTroubleState
    /*! Returns the last received PartitionTroubleState for this Partition.
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionTroubleState_Tag
      	\param ptrTroubleState Pointer to storage for the PartitionTroubleState data.
    */
	virtual IRESULT ICALL get_PartitionTroubleState(OUT DSC_PartitionTroubleState* ptrTroubleState) const = 0;

    //! Get the PartitionExitDelayState
    /*! Returns the last received PartitionExitDelayState for this Partition.
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionExitDelayState_Tag
      	\param ptrExitDelayState Pointer to storage for the PartitionExitDelayState data.
    */
	virtual IRESULT ICALL get_PartitionExitDelayState(OUT DSC_PartitionExitDelayState* ptrExitDelayState) const = 0;

    //! Get the PartitionEntryDelayState
    /*! Returns the last received PartitionEntryDelayState for this Partition.
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionEntryDelayState_Tag
      	\param ptrEntryDelayState Pointer to storage for the PartitionEntryDelayState data.
    */
	virtual IRESULT ICALL get_PartitionEntryDelayState(OUT DSC_PartitionEntryDelayState* ptrEntryDelayState) const = 0;

    //! Get the PartitionBypassState
    /*! Returns the last received PartitionBypassState for this Partition. (if any zones are currently Bypassed on this Partition).
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionBypassState_Tag
      	\param ptrBypassState Pointer to storage for the PartitionBypassState data.
    */
	virtual IRESULT ICALL get_PartitionBypassState(OUT DSC_PartitionBypassState* ptrBypassState) const = 0;

    //! Get the PartitionAlarmState
    /*! Returns the last received PartitionAlarmSate for this Partition. (if there is an Alarm condition currently active on this Partition).
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionAlarmState_Tag
      	\param ptrAlarmState Pointer to storage for the PartitionAlarmState data.
    */
	virtual IRESULT ICALL get_PartitionAlarmState(OUT DSC_PartitionAlarmState* ptrAlarmState) const = 0;

    //! Get the PartitionAlarmMemoryState
    /*! Returns the last received AlarmMemoryState for this Partition. (if there are any Alarms In Memory on this Partition, cleared next time Panel is armed).  */
    /*!	
		\sa enum DSC_PartitionAlarmMemoryState_Tag
      	\param ptrAlarmMemoryState Pointer to storage for the PartitionAlarmMemoryState data.
    */
	virtual IRESULT ICALL get_PartitionAlarmMemoryState(OUT DSC_PartitionAlarmMemoryState* ptrAlarmMemoryState) const = 0;

    //! Get the PartitionBusyState
    /*! Returns the last received PartitionBusyState for this Partition. Partitions can be "Busied Out" if the system is unable to process user requests, such as when 
		programming is active.
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionBusyState_Tag
      	\param ptrBusyState Pointer to storage for the PartitionBusyState data.
    */
	virtual IRESULT ICALL get_PartitionBusyState(OUT DSC_PartitionBusyState* ptrBusyState) const = 0;

    //! Get the PartitionAudibleBellState
    /*! Returns the last received PartitionAudibleBellState for this Partition. Note, this is only if the bells are active or not. You may need to get the AudibleBellType
	    for more information regarding the alarm type.
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionAudibleBellState_Tag
      	\param ptrAudibleBellState Pointer to storage for the PartitionAudibleBellState data.
    */
	virtual IRESULT ICALL get_PartitionAudibleBellState(OUT DSC_PartitionAudibleBellState* ptrAudibleBellState) const = 0;

    //! Get the PartitionAudibleBellType
    /*! Returns the last received PartitionAudibleBellType for this Partition. You may need to check the PartitionAudibleBellState to determine if this audible 
		bell type is currently active.
		(NOTE: calling the Refresh function is required in order to get the initial state data)
	*/
    /*!	
		\sa enum DSC_PartitionAudibleBellType_Tag
      	\param ptrAudibleBellType Pointer to storage for the PartitionAudibleBellType data.
    */
	virtual IRESULT ICALL get_PartitionAudibleBellType(OUT DSC_PartitionAudibleBellType* ptrAudibleBellType) const = 0;

	//! Refreshes the Partition State Data.
	/*! This function will issue the requisite commands to get the Partition State Data of the Partition.    */
	/*!
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to read the Partition State Data.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Get the Partition System Index
	/*! Gets the System Index for the Partition as assigned by the panel.
		For example, Partition 1 would return system index 1. */
	/*!
      	\param ptrSystemIndex Pointer to storage for the Partition System Index.
    */
	virtual IRESULT ICALL get_SystemIndex(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;
};

#else

typedef struct DSC_IPartitionStateData_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IPartitionStateData *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IPartitionStateData *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IPartitionStateData *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_PartitionBuzzerState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionBuzzerState* ptrBuzzerState);
	IRESULT (ICALL *get_PartitionQuickExitState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionQuickExitState* ptrQuickExitState);
	IRESULT (ICALL *get_PartitionReadyState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionReadyState* ptrReadyState);
	IRESULT (ICALL *get_PartitionArmedState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionArmedState* ptrArmedState);
	IRESULT (ICALL *get_PartitionBlankState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionBlankState* ptrBlankState);
	IRESULT (ICALL *get_PartitionTroubleState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionTroubleState* ptrTroubleState);
	IRESULT (ICALL *get_PartitionExitDelayState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionExitDelayState* ptrExitDelayState);
	IRESULT (ICALL *get_PartitionEntryDelayState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionEntryDelayState* ptrEntryDelayState);
	IRESULT (ICALL *get_PartitionBypassState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionBypassState* ptrBypassState);
	IRESULT (ICALL *get_PartitionAlarmState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionAlarmState* ptrAlarmState);
	IRESULT (ICALL *get_PartitionAlarmMemoryState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionAlarmMemoryState* ptrAlarmMemoryState);
	IRESULT (ICALL *get_PartitionBusyState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionBusyState* ptrBusyState);
	IRESULT (ICALL *get_PartitionAudibleBellState)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionAudibleBellState* ptrAudibleBellState);
	IRESULT (ICALL *get_PartitionAudibleBellType)(IN DSC_IPartitionStateData *This, OUT DSC_PartitionAudibleBellType* ptrAudibleBellType);

	IRESULT (ICALL *Refresh)(IN DSC_IPartitionStateData *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_SystemIndex)(IN DSC_IPartitionStateData *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);

	END_INTERFACE
} DSC_IPartitionStateData_Vtbl;

DSC_INTERFACE DSC_IPartitionStateData
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IPartitionStateData_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_PARTITION_STATE_DATA_HPP_
