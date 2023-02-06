//---------------------------------------------------------------------------
//
//	WinDLL_Library.hpp
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//	The file contains info used when implementing Windows DLL libraries.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IBase.hpp"

#ifndef _WINDLL_LIBRARY_HPP_
#define _WINDLL_LIBRARY_HPP_

namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#ifdef __cplusplus

#ifdef WINDLL_LIBRARY_IMPL
#define WINDLL_LIBRARY_API	extern "C" __declspec(dllexport)
#else
#define WINDLL_LIBRARY_API	extern "C" __declspec(dllimport)
#endif

#else	//__cplusplus

#ifdef WINDLL_LIBRARY_IMPL
#define WINDLL_LIBRARY_API	extern __declspec(dllexport)
#else
#define WINDLL_LIBRARY_API	extern __declspec(dllimport)
#endif

#endif	//__cplusplus

//-------------------------------------------------------------------------

//Use this predefined name to obtain the name of the library function.
#define WINDLL_LIBRARY_FUNCNAME	"CreateObject"

//Use this type to prototype the library function.
typedef IRESULT (ICALL *WINDLL_LIBRARY_FUNCTION)(char const* pszName, VOID** ptrObject);

//-------------------------------------------------------------------------

//This is the main function of the library. It must be implemented in the DLL.
WINDLL_LIBRARY_API IRESULT ICALL CreateObject(char const* pszName, VOID** ptrObject);

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE

#endif	//_WINDLL_LIBRARY_HPP_
