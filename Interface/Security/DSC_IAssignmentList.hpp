//---------------------------------------------------------------------------
//
//	DSC_IAssignmentList.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IAssignmentData.hpp"

#ifndef _DSC_I_ASSIGNMENT_LIST_HPP_
#define _DSC_I_ASSIGNMENT_LIST_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IAssignmentList	"DSC_IAssignmentList"

//---------------------------------------------------------------------------

#ifndef DSC_IAssignmentList_FWD_DEFINED
#define DSC_IAssignmentList_FWD_DEFINED
typedef DSC_INTERFACE DSC_IAssignmentList DSC_IAssignmentList;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for accessing assignment information.
	(eg. zones assigned to partitions, access codes assigned to partition etc)
*/
DSC_INTERFACE DSC_IAssignmentList : public DSC_IComponent
{
public:

    //! Get the number of assignments.
    /*! Returns the number of assignments. */
    /*!	
      	\param ptrCount Pointer to storage for the number of assignments.
    */
	virtual IRESULT ICALL get_NumberOfAssignments(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Get an AssignmentData interface.
	/*! Retrieves an AssignmentData interface. This is a 0 based list index, NOT a system index. */
	/*!
		\sa DSC_IAssignmentData
		\param numIndex Requested 0 based list index of the AssignmentData interface to get.
		\param ptrZone Pointer to storage for the requested AssignmentData interface.
	*/
	virtual IRESULT ICALL get_AssignmentData(IN DSC_SIZE_T numIndex, OUT DSC_IAssignmentData** ptrAssignmentData) = 0;
};

#else

typedef struct DSC_IAssignmentList_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IAssignmentList *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IAssignmentList *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IAssignmentList *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_NumberOfAssignments)(IN DSC_IAssignmentList *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_AssignmentData)(IN DSC_IAssignmentList *This, 
		IN DSC_SIZE_T numIndex, OUT DSC_IAssignmentData** ptrAssignmentData);

	END_INTERFACE
} DSC_IAssignmentList_Vtbl;

DSC_INTERFACE DSC_IAssignmentList
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IAssignmentList_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_ASSIGNMENT_LIST_HPP_
