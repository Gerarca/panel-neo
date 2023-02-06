//---------------------------------------------------------------------------
//
//	DSC_ISystemIndices.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The interface for implementing an array of system indices.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"

#ifndef _DSC_I_SYSTEM_INDICES_HPP_
#define _DSC_I_SYSTEM_INDICES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//The implementation must be thread safe.
#define NAME_DSC_ISystemIndices	"DSC_ISystemIndices"

//---------------------------------------------------------------------------

#ifndef DSC_ISystemIndices_FWD_DEFINED
#define DSC_ISystemIndices_FWD_DEFINED
typedef DSC_INTERFACE DSC_ISystemIndices DSC_ISystemIndices;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to access and manipulate an array of system indexes.
*/
DSC_INTERFACE DSC_ISystemIndices : public DSC_IComponent
{
public:

	//! Gets the number of indices stored in the list.
    /*!	
     	\param ptrCount Pointer to DSC_SIZE_T that contains the number of indices stored.
    */
	virtual IRESULT ICALL get_Size(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Gets the pointer to the selected system index.
    /*!	
		\param numIndex The array index of the system index information.
     	\param ptrSystemIndex Pointer to DSC_SYSTEM_INDEX that receives the system index information.
    */
	virtual IRESULT ICALL get_Index(IN DSC_SIZE_T numIndex, 
		OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;

	//! Clears all the system indices stored in the list.
    /*!	
    */
	virtual IRESULT ICALL Clear(VOID) = 0;

	//! Adds new system index to the list.
    /*!	
     	\param numSystemIndex New system index to be added to the list.
    */
	virtual IRESULT ICALL Add(
		IN DSC_SYSTEM_INDEX numSystemIndex) = 0;

	//! Inserts new system index to the list at given position.
    /*!	
		\param numIndex The list index where to insert the new system index.
     	\param numSystemIndex New system index to be inserted to the list.
    */
	virtual IRESULT ICALL InsertAt(IN DSC_SIZE_T numIndex, 
		IN DSC_SYSTEM_INDEX numSystemIndex) = 0;

	//! Removes the system index from the list at given position.
    /*!	
		\param numIndex The list index where of the system index to remove.
    */
	virtual IRESULT ICALL RemoveAt(IN DSC_SIZE_T numIndex) = 0;

	//! Checks if the list contains given system index.
    /*!	
		\param numSystemIndex The system index to look for in the list.
		\param result Pointer to the BOOL member that receives the result of the check.
    */
	virtual IRESULT ICALL Contains(IN DSC_SYSTEM_INDEX numSystemIndex, OUT BOOL* result) = 0;
};

#else

typedef struct DSC_ISystemIndices_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ISystemIndices *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ISystemIndices *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ISystemIndices *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_Size)(IN DSC_ISystemIndices *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_Index)(IN DSC_ISystemIndices *This, 
		IN DSC_SIZE_T numIndex, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *Clear)(IN DSC_ISystemIndices *This);
	IRESULT (ICALL *Add)(IN DSC_ISystemIndices *This, 
		IN DSC_SYSTEM_INDEX numSystemIndex);
	IRESULT (ICALL *InsertAt)(IN DSC_ISystemIndices *This, 
		IN DSC_SIZE_T numIndex, IN DSC_SYSTEM_INDEX numSystemIndex);
	IRESULT (ICALL *RemoveAt)(IN DSC_ISystemIndices *This, IN DSC_SIZE_T numIndex);
	IRESULT (ICALL *Contains)(IN DSC_ISystemIndices *This, 
		IN DSC_SYSTEM_INDEX numSystemIndex, OUT BOOL* result);

	END_INTERFACE
} DSC_ISystemIndices_Vtbl;

DSC_INTERFACE DSC_ISystemIndices
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ISystemIndices_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_SYSTEM_INDICES_HPP_
