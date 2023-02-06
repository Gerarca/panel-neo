//---------------------------------------------------------------------------
//
//	DSC_IPartitionManager.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IPartition.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_IAccessCredentials.hpp"
#include "DSC_PartitionArmedStates.hpp"
#include "DSC_IAccessCode.hpp"
#include "DSC_IZone.hpp"

#ifndef _DSC_I_PARTITION_MANAGER_HPP_
#define _DSC_I_PARTITION_MANAGER_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IPartitionManager	"DSC_IPartitionManager"

//---------------------------------------------------------------------------

#ifndef DSC_IPartitionManager_FWD_DEFINED
#define DSC_IPartitionManager_FWD_DEFINED
typedef DSC_INTERFACE DSC_IPartitionManager DSC_IPartitionManager;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to request the list of enabled partitions
	on the panel.
*/
DSC_INTERFACE DSC_IPartitionManager : public DSC_IComponent
{
public:

    //! Refreshes the list of enabled partition on panel.
    /*! This function will issue the requisite commands to fetch the list of enabled partitions on the panel.  */
    /*!	
		\sa DSC_IAccessCredentials
		\param ptrAccessCredentials Provided Credentials with appropriate permissions to request the list of enabled partitions.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Get the number of enabled partitions.
    /*! Returns the number of enabled partitions. */
    /*!	
      	\param ptrCount Pointer to storage for the number of enabled partitions.
    */
	virtual IRESULT ICALL get_NumberOfPartitions(OUT DSC_SIZE_T* ptrCount) const = 0;

    //! Get a Partition interface.
    /*! Retrieves a Partition interface. This is a 0 based list index, NOT a system index. */
    /*!	
		\sa DSC_IPartition
      	\param numIndex Requested 0 based list index of the partition interface to get.
		\param ptrPartition Pointer to storage for the requested partition interface.
    */
	virtual IRESULT ICALL get_Partition(IN DSC_SIZE_T numIndex, OUT DSC_IPartition** ptrPartition) = 0;
};

#else

typedef struct DSC_IPartitionManager_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IPartitionManager *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IPartitionManager *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IPartitionManager *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IPartitionManager *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_NumberOfPartitions)(IN DSC_IPartitionManager *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_Partition)(IN DSC_IPartitionManager *This, 
		IN DSC_SIZE_T numIndex, OUT DSC_IPartition** ptrPartition);

	END_INTERFACE
} DSC_IPartitionManager_Vtbl;

DSC_INTERFACE DSC_IPartitionManager
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IPartitionManager_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_PARTITION_MANAGER_HPP_
