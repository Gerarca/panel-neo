//---------------------------------------------------------------------------
//
//	DSC_IComponent.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The interface for implementing software components.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IBase.hpp"

#ifndef _DSC_I_COMPONENT_HPP_
#define _DSC_I_COMPONENT_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//The definition of the base interface that must be implemented by all
//software components that need to manage their lifespans internally.
#define NAME_DSC_IComponent		"DSC_IComponent"

//---------------------------------------------------------------------------

#ifndef DSC_IComponent_FWD_DEFINED
#define DSC_IComponent_FWD_DEFINED
typedef DSC_INTERFACE DSC_IComponent DSC_IComponent;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to control the lifetime of SDK objects.
	All other interfaces inherit it and all SDK objects must imeplement it.
*/
DSC_INTERFACE DSC_IComponent
{
public:

	//! The Query method returns a pointer to the interface specified by the name.
    /*! 
		The method may pass back NULL if the specified interface name is unknown.

     	\param pszInterface The name of the interface of interest.
     	\param ptrInterface Pointer to the requested interface or NULL if the interface is not available.
    */
	virtual IRESULT ICALL Query(IN char const* pszInterface, OUT VOID** ptrInterface) = 0;

	//! The Acquire method informs the object implementing the interface that a reference has been created.
    /*! 
		The lifetime of the object should be maintained as long as there are any references present.

     	\param ptrCount The number of currently remaining references.
    */
	virtual IRESULT ICALL Acquire(OUT ICOUNT* ptrCount) = 0;

	//! The Release method informs the object implementing the interface that a reference has been dropped.
    /*! 
		When all references are released the object is no longer needed and can be destroyed.

     	\param ptrCount The number of currently remaining references.
    */
	virtual IRESULT ICALL Release(OUT ICOUNT* ptrCount) = 0;
};

#else

typedef struct DSC_IComponent_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IComponent *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IComponent *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IComponent *This, OUT ICOUNT* ptrCount);

	END_INTERFACE
} DSC_IComponent_Vtbl;

DSC_INTERFACE DSC_IComponent
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IComponent_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_COMPONENT_HPP_
