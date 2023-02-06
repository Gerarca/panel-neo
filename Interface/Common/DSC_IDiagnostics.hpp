//---------------------------------------------------------------------------
//
//	DSC_IDiagnostics.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The interface for providing SDK dagnostics functionality.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_ObjectTypes.hpp"

#ifndef _DSC_I_DIAGNOSTICS_HPP_
#define _DSC_I_DIAGNOSTICS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//The implementation must be thread safe.
#define NAME_DSC_IDiagnostics	"DSC_IDiagnostics"

//---------------------------------------------------------------------------

#ifndef DSC_IDiagnostics_FWD_DEFINED
#define DSC_IDiagnostics_FWD_DEFINED
typedef DSC_INTERFACE DSC_IDiagnostics DSC_IDiagnostics;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for accessing SDK diagnostics information.
*/
DSC_INTERFACE DSC_IDiagnostics : public DSC_IComponent
{
public:

    //! Get the basic stats for objects created by the SDK.
    /*! Returns the total count for objects created by the SDK that 
		are currently in memory as well as the total reference count.
		The SDK tracks lifetimes of the created objects using reference 
		count mechanism. Each time an interface is created, the reference 
		counter for the underlying object implmenting it is incremented. 
		And when the interface is no longer needed and it is released (by 
		calling the Release function), the object's reference counter is 
		decremented. Once the reference counter for given object reaches 0, 
		the object is deleted from the memory. This function return the 
		information on how many objecs of given type are still in memory 
		and their total reference count. */
    /*!	
		\sa DSC_ObjectType
      	\param flgObjectType The type of object to check.
		\param ptrMemCount Pointer to storage for the count of objects in memory.
		\param ptrRefCount Pointer to storage for the count of interfaces.
    */
	virtual IRESULT ICALL GetObjectTypeCounts(IN DSC_ObjectType flgObjectType, 
			OUT ICOUNT* ptrMemCount, OUT ICOUNT* ptrRefCount) = 0;
};

#else

typedef struct DSC_IDiagnostics_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IDiagnostics *This, 
		IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IDiagnostics *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IDiagnostics *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *GetObjectTypeCounts)(IN DSC_IDiagnostics *This, 
		IN DSC_ObjectType flgObjectType, OUT ICOUNT* ptrMemCount, OUT ICOUNT* ptrRefCount);

	END_INTERFACE
} DSC_IDiagnostics_Vtbl;

DSC_INTERFACE DSC_IDiagnostics
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IDiagnostics_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_DIAGNOSTICS_HPP_
