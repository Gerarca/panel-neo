//---------------------------------------------------------------------------
//
//	DSC_ITextString.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The interface for implementing simple text string components.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"

#ifndef _DSC_I_TEXT_STRING_HPP_
#define _DSC_I_TEXT_STRING_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//The implementation must be thread safe.
#define NAME_DSC_ITextString	"DSC_ITextString"

//---------------------------------------------------------------------------

#ifndef DSC_ITextString_FWD_DEFINED
#define DSC_ITextString_FWD_DEFINED
typedef DSC_INTERFACE DSC_ITextString DSC_ITextString;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for implementing text string storage objects.
*/
DSC_INTERFACE DSC_ITextString : public DSC_IComponent
{
public:

	//! This function is used to get the length of the string excluding the null-terminator.
    /*! 
		Note that ALL strings used by this sdk are unicode encoded as UTF8.

     	\param ptrLength The length of a string not including null terminator
    */
	virtual IRESULT ICALL get_Length(OUT DSC_SIZE_T* ptrLength) const = 0;

	//! This function is used to get the pointer to the text string stored inside the component.
    /*! 
		Note that ALL strings used by this sdk are unicode encoded as UTF8.

		\param ptrString Pointer to the requested string
    */
	virtual IRESULT ICALL get_String(OUT char const** ptrString) const = 0;

	//! This function is used to store the copy of the text string inside the component.
    /*! 
		Note that ALL strings used by this sdk are unicode encoded as UTF8.

		\param pszString Pointer to the string data.
    */
	virtual IRESULT ICALL set_String(IN char const* pszString) = 0;
};

#else

typedef struct DSC_ITextString_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ITextString *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ITextString *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ITextString *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_Length)(IN DSC_ITextString *This, OUT DSC_SIZE_T* ptrLength);
	IRESULT (ICALL *get_String)(IN DSC_ITextString *This, OUT char const** ptrString);
	IRESULT (ICALL *set_String)(IN DSC_ITextString *This, IN char const* pszString);

	END_INTERFACE
} DSC_ITextString_Vtbl;

DSC_INTERFACE DSC_ITextString
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ITextString_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_TEXT_STRING_HPP_
