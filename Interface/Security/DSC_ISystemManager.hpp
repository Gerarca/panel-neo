//---------------------------------------------------------------------------
//
//	DSC_ISystemManager.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IAccessCode.hpp"
#include "DSC_IZone.hpp"
#include "DSC_IVirtualZoneManager.hpp"
#include "DSC_IPartition.hpp"
#include "DSC_ITextString.hpp"
#include "DSC_IAccessCredentials.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_ISystemIndices.hpp"
#include "DSC_IVirtualKeypadManager.hpp"
#include "DSC_IAlarmTypeContainer.hpp"

#ifndef _DSC_I_SYSTEM_MANAGER_HPP_
#define _DSC_I_SYSTEM_MANAGER_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ISystemManager	"DSC_ISystemManager"

//---------------------------------------------------------------------------

#ifndef DSC_ISystemManager_FWD_DEFINED
#define DSC_ISystemManager_FWD_DEFINED
typedef DSC_INTERFACE DSC_ISystemManager DSC_ISystemManager;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for accessing sytem-related functionality
	of the security system.
*/
DSC_INTERFACE DSC_ISystemManager : public DSC_IComponent
{
public:

    //! Refreshes all data for this System
    /*! This function sends all of the requisite commands to the target to get all state and configuration information for this system. */
    /*!	
      	\param ptrAccessCredentials Pointer to storage for the Credentials with the required access level
      	\param ptrRequestResult Pointer to storage for the request result.
    */
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Used to get the present system time and date information.
    /*! Sends the requisite commands to read the current System Time and Date on the target.     */
    /*!	
		\param ptrAccessCredentials Pointer to a DSC_IAccessCredentials class with sufficient permission level.
		\param ptrTimeDate Pointer to storage for result.
		\param ptrRequestResult Pointer to store the request result.
	*/
    virtual IRESULT ICALL ReadSystemTimeDate(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_ITextString** ptrTimeDate, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Used to program the systems time and date information/value.
    /*! Sends the requisite commands to change the system Time and Date. Note, this may require a user code with enough privledges to perform this operation,
		and may be inhibited if a Partition is currently not Disarmed.     */
    /*!	
		\param ptrAccessCredentials Pointer to a DSC_IAccessCredentials class with sufficient permission level.
		\param pszTimeDate Pointer to new Time and Date information.
		\param ptrRequestResult Pointer to store the request result.
	*/
    virtual IRESULT ICALL WriteSystemTimeDate(IN DSC_IAccessCredentials* ptrAccessCredentials, IN char const* pszTimeDate, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Checks if a trouble is present on the system 
    /*! Returns a boolean value indicating that a trouble condition is present on the System.     */
    /*!	
      	\param ptrTroublePresent Pointer to storage for the result.
    */
	virtual IRESULT ICALL get_TroublePresent(OUT BOOL* ptrTroublePresent) const = 0;

	//! Used to manage Virtual Zones on the system.
	/*! Returns the Virtual Zone Manager that contains all of the functions	required to interact with Virtual Zones.*/
	/*!
		\param ptrVirtualZoneManager Pointer to storage for the Virtual Zone Manager.
	*/
	virtual IRESULT ICALL get_VirtualZoneManager(OUT DSC_IVirtualZoneManager** ptrVirtualZoneManager) = 0;

    //! Used to read what Partition(s) Access Codes are assigned to. 
    /*! Reads the Partition Assignments for an access code. Note this requires access credentials of sufficient privledges to read/write Access Code Attributes. */
    /*!	
      	\param ptrAccessCredentials Credentials with sufficient privledges to read / write Access Code Partition assignments
		\param numAccessCodeSystemIndex Access Code System Index of the Access code you wish to find the Partition assignments for.
		\param ptrPartitionSystemIndexes Pointer to storage of a DSC_ISystemIndices container of indexes
		\param ptrRequestResult Pointer to storage for the request result
    */
	virtual IRESULT ICALL ReadAccessCodePartitionAssignments(IN DSC_IAccessCredentials* ptrAccessCredentials, IN DSC_SYSTEM_INDEX numAccessCodeSystemIndex, OUT DSC_ISystemIndices** ptrPartitionSystemIndexes, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Adds Partition Assignments to an existing Access Code
    /*! This function is used when you wish to update what Partitions an existing Access Code can be used on. Specifically, this function call is used to ADD access to a Partition / Partitions to an Access Code.
        Note, this requires Credentials with sufficient privledges to be able to modify Access Code Attributes. */
    /*!	
      	\sa RemoveAccessCodeFromPartitions, ReadAccessCodePartitionAssignments
		\param ptrAccessCredentials Credentials with sufficient privledges to be able to modify Access Code Attributes
		\param numAccessCodeSystemIndex System Index of Access Code you wish to add Partition Access to
		\param ptrPartitionSystemIndexes Pointer to storage of Partition System Indexes that you wish to allow access to this Access Code.
		\param numNumberOfPartitionSystemIndexes Number of elements to expect in ptrPartitionSystemIndexes
		\param ptrRequestResult Pointer to storage for the result.
    */
	virtual IRESULT ICALL AddAccessCodeToPartitions(IN DSC_IAccessCredentials* ptrAccessCredentials, IN DSC_SYSTEM_INDEX numAccessCodeSystemIndex, IN DSC_SYSTEM_INDEX const* ptrPartitionSystemIndexes, IN DSC_SIZE_T numNumberOfPartitionSystemIndexes, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Removes Partition Assignments to an existing Access Code
    /*! This function is used when you wish to update what Partitions an existing Access Code can be used on. Specifically, this function call is used to REMOVE access to a Partition / Partitions from an Access Code.
        Note, this requires Credentials with sufficient privledges to be able to modify Access Code Attributes. */
    /*!	
      	\sa AddAccessCodeToPartitions, ReadAccessCodePartitionAssignments
		\param ptrAccessCredentials Credentials with sufficient privledges to be able to modify Access Code Attributes
		\param numAccessCodeSystemIndex System Index of Access Code you wish to add Partition Access to
		\param ptrPartitionSystemIndexes Pointer to storage of Partition System Indexes that you wish to remove access from this Access Code.
		\param numNumberOfPartitionSystemIndexes Number of elements to expect in ptrPartitionSystemIndexes
		\param ptrRequestResult Pointer to storage for the result.
    */
	virtual IRESULT ICALL RemoveAccessCodeFromPartitions(IN DSC_IAccessCredentials* ptrAccessCredentials, IN DSC_SYSTEM_INDEX numAccessCodeSystemIndex, IN DSC_SYSTEM_INDEX const* ptrPartitionSystemIndexes, IN DSC_SIZE_T numNumberOfPartitionSystemIndexes, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Used to manage Virtual Keypads on the system.
	/*! Returns the Virtual Keypad Manager that contains all of the functions required to interact with Virtual Keypads.*/
	/*!
		\param ptrVirtualKeypadManager Pointer to storage for the Virtual Keypad Manager.
	*/
	virtual IRESULT ICALL get_VirtualKeypadManager(OUT DSC_IVirtualKeypadManager** ptrVirtualKeypadManager) = 0;

	//! Fatches the current array of Alarm Types.
    /*! Returns the array of the last known Alarm Types for the system.     */
    /*!	
    	\param ptrAlarmTypes - Pointer to the storage for the result interface
    */
	virtual IRESULT ICALL get_AlarmTypes(OUT DSC_IAlarmTypeContainer** ptrAlarmTypes) = 0;
};

#else

typedef struct DSC_ISystemManager_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ISystemManager *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ISystemManager *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ISystemManager *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_ISystemManager *This, IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
    IRESULT (ICALL *ReadSystemTimeDate)(IN DSC_ISystemManager *This, IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_ITextString** ptrTimeDate, OUT DSC_IRequestResult** ptrRequestResult);
    IRESULT (ICALL *WriteSystemTimeDate)(IN DSC_ISystemManager *This, IN DSC_IAccessCredentials* ptrAccessCredentials, IN char const* pszTimeDate, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_TroublePresent)(IN DSC_ISystemManager *This, OUT BOOL* ptrTroublePresent);
	IRESULT (ICALL *get_VirtualZoneManager)(IN DSC_ISystemManager *This, OUT DSC_IVirtualZoneManager** ptrVirtualZoneManager);
	IRESULT (ICALL *ReadAccessCodePartitionAssignments)(IN DSC_ISystemManager *This, IN DSC_IAccessCredentials* ptrAccessCredentials, IN DSC_SYSTEM_INDEX numAccessCodeSystemIndex, OUT DSC_ISystemIndices** ptrPartitionSystemIndexes, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *AddAccessCodeToPartitions)(IN DSC_ISystemManager *This, IN DSC_IAccessCredentials* ptrAccessCredentials, IN DSC_SYSTEM_INDEX numAccessCodeSystemIndex, IN DSC_SYSTEM_INDEX const* ptrPartitionSystemIndexes, IN DSC_SIZE_T numNumberOfPartitionSystemIndexes, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *RemoveAccessCodeFromPartitions)(IN DSC_ISystemManager *This, IN DSC_IAccessCredentials* ptrAccessCredentials, IN DSC_SYSTEM_INDEX numAccessCodeSystemIndex, IN DSC_SYSTEM_INDEX const* ptrPartitionSystemIndexes, IN DSC_SIZE_T numNumberOfPartitionSystemIndexes, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_VirtualKeypadManager)(IN DSC_ISystemManager *This, OUT DSC_IVirtualKeypadManager** ptrVirtualKeypadManager);
	IRESULT (ICALL *get_AlarmTypes)(IN DSC_ISystemManager *This, OUT DSC_IAlarmTypeContainer** ptrAlarmTypes);

	END_INTERFACE
} DSC_ISystemManager_Vtbl;

DSC_INTERFACE DSC_ISystemManager
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ISystemManager_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_SYSTEM_MANAGER_HPP_
