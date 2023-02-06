//---------------------------------------------------------------------------
//
//	WinLIB_Library.hpp
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//	The file contains info used when implementing Windows libraries.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IBase.hpp"

#ifndef _WINLIB_LIBRARY_HPP_
#define _WINLIB_LIBRARY_HPP_

namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#ifdef __cplusplus

#ifdef WINLIB_LIBRARY_IMPL
#define WINLIB_LIBRARY_API	extern "C"
#else
#define WINLIB_LIBRARY_API	extern "C"
#endif

#else	//__cplusplus

#ifdef WINLIB_LIBRARY_IMPL
#define WINLIB_LIBRARY_API	extern
#else
#define WINLIB_LIBRARY_API	extern
#endif

#endif	//__cplusplus

//-------------------------------------------------------------------------

//Use this predefined name to obtain the name of the library function.
#define WINLIB_LIBRARY_FUNCNAME	"CreateObject"

//Use this type to prototype the library function.
typedef IRESULT (ICALL *WINLIB_LIBRARY_FUNCTION)(char const* pszName, VOID** ptrObject);

//-------------------------------------------------------------------------

//This is the main function of the library. It must be implemented in the LIB.
WINLIB_LIBRARY_API IRESULT ICALL CreateObject(char const* pszName, VOID** ptrObject);

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE

#endif	//_WINLIB_LIBRARY_HPP_
