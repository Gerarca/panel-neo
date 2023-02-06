//---------------------------------------------------------------------------
//
//	DSC_IAssignmentData.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_AssignmentTypes.hpp"
#include "DSC_AssignmentStates.hpp"

#ifndef _DSC_I_ASSIGNMENT_DATA_HPP_
#define _DSC_I_ASSIGNMENT_DATA_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IAssignmentData	"DSC_IAssignmentData"

//---------------------------------------------------------------------------

#ifndef DSC_IAssignmentData_FWD_DEFINED
#define DSC_IAssignmentData_FWD_DEFINED
typedef DSC_INTERFACE DSC_IAssignmentData DSC_IAssignmentData;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used with the general event notification for 
	providing assignment information for partitions, zones, virtual zones, etc.
*/
DSC_INTERFACE DSC_IAssignmentData : public DSC_IComponent
{
public:

    //! Get the value indicating the type of assignment. 
    /*! This property returns one of the DSC_AssignmentType enum values to indicate the type of the assignment.     */
    /*!	
		\sa enum DSC_AssignmentType_Tag
      	\param ptrType Pointer to storage for the DSC_AssignmentType value.
    */
	virtual IRESULT ICALL get_Type(OUT DSC_AssignmentType* ptrType) const = 0;

    //! Get the value indicating the state of assignment. 
    /*! This property returns one of the DSC_AssignmentState enum values to indicate the state of the assignment.     */
    /*!	
		\sa enum DSC_AssignmentState_Tag
      	\param ptrState Pointer to storage for the DSC_AssignmentState value.
    */
	virtual IRESULT ICALL get_State(OUT DSC_AssignmentState* ptrState) const = 0;

	//! Get the Access Code System Index 
	/*! Gets the System Index for the Access Code as assigned by the panel.
		For example, User Code 5 would return system index 5.
		NOTE: If get_Type() returns DSC_AssignmentTypes::AccessCode_Partition, this value will be set. 
		For any other values of get_Type(), this value will be DSC_INVALID_SYSTEM_INDEX.
	*/
	/*!	
      	\param ptrSystemIndex Pointer to storage for the Access Code system index.
    */
	virtual IRESULT ICALL get_AccessCodeNumber(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;

	//! Get the Partition System Index 
	/*! Gets the System Index for the Partition as assigned by the panel.
		For example, Partition 1 would return system index 1.
		NOTE: If get_Type() returns DSC_AssignmentTypes::VirtualZone_Zone, this value will be DSC_INVALID_SYSTEM_INDEX.
		For any other values of get_Type(), this value will be set.
	*/
	/*!
		\param ptrSystemIndex Pointer to storage for the Partition system index.
	*/
	virtual IRESULT ICALL get_PartitionNumber(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;

	//! Get the Virtual Zone System Index 
	/*! Gets the System Index for the Virtual Zone as assigned by the panel.
		For example, Virtual Zone 1 would return system index 1.
		NOTE: If get_Type() returns DSC_AssignmentTypes::VirtualZone_Zone, this value will be set.
		For any other values of get_Type(), this value will be DSC_INVALID_SYSTEM_INDEX.
	*/
	/*!
		\param ptrSystemIndex Pointer to storage for the Virtual Zone system index.
	*/
	virtual IRESULT ICALL get_VirtualZoneNumber(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;

	//! Get the Zone System Index 
	/*! Gets the System Index for the Zone as assigned by the panel.
		For example, Zone 1 would return system index 1.
		NOTE: If get_Type() returns DSC_AssignmentTypes::Zone_Partition 
		or DSC_AssignmentTypes::VirtualZone_Zone, this value will be set.
		For any other values of get_Type(), this value will be DSC_INVALID_SYSTEM_INDEX.
	*/
	/*!
		\param ptrSystemIndex Pointer to storage for the Zone system index.
	*/
	virtual IRESULT ICALL get_ZoneNumber(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;
};

#else

typedef struct DSC_IAssignmentData_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IAssignmentData *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IAssignmentData *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IAssignmentData *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_Type)(IN DSC_IAssignmentData *This, OUT DSC_AssignmentType* ptrType);
	IRESULT (ICALL *get_State)(IN DSC_IAssignmentData *This, OUT DSC_AssignmentState* ptrState);
	IRESULT (ICALL *get_AccessCodeNumber)(IN DSC_IAssignmentData *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_PartitionNumber)(IN DSC_IAssignmentData *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_VirtualZoneNumber)(IN DSC_IAssignmentData *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *ICALL get_ZoneNumber)(IN DSC_IAssignmentData *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);

	END_INTERFACE
} DSC_IAssignmentData_Vtbl;

DSC_INTERFACE DSC_IAssignmentData
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IAssignmentData_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_ASSIGNMENT_DATA_HPP_
