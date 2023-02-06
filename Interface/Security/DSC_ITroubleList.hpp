//---------------------------------------------------------------------------
//
//	DSC_ITroubleList.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_ITroubleData.hpp"

#ifndef _DSC_I_TROUBLE_LIST_HPP_
#define _DSC_I_TROUBLE_LIST_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ITroubleList	"DSC_ITroubleList"

//---------------------------------------------------------------------------

#ifndef DSC_ITroubleList_FWD_DEFINED
#define DSC_ITroubleList_FWD_DEFINED
typedef DSC_INTERFACE DSC_ITroubleList DSC_ITroubleList;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to request the list of troubles
	on the panel.
*/
DSC_INTERFACE DSC_ITroubleList : public DSC_IComponent
{
public:

	//! Get the number of troubles.
	/*! Returns the number of troubles. */
	/*!
		\param ptrCount Pointer to storage for the number of troubles.
	*/
	virtual IRESULT ICALL get_NumberOfTroubles(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Get a TroubleData interface.
	/*! Retrieves a TroubleData interface. This is a 0 based list index, NOT a system index. */
	/*!
		\sa DSC_ITroubleData
		\param numIndex Requested 0 based list index of the trouble interface to get.
		\param ptrZone Pointer to storage for the requested trouble interface.
	*/
	virtual IRESULT ICALL get_TroubleData(IN DSC_SIZE_T numIndex, OUT DSC_ITroubleData** ptrTroubleData) = 0;
};

#else

typedef struct DSC_ITroubleList_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ITroubleList *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ITroubleList *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ITroubleList *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_NumberOfTroubles)(IN DSC_ITroubleList *This, 
		OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_TroubleData)(IN DSC_ITroubleList *This, 
		IN DSC_SIZE_T numIndex, OUT DSC_ITroubleData** ptrTroubleData);

	END_INTERFACE
} DSC_ITroubleList_Vtbl;

DSC_INTERFACE DSC_ITroubleList
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ITroubleList_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_TROUBLE_LIST_HPP_
