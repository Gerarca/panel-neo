//---------------------------------------------------------------------------
//
//	DSC_LinuxLIB.hpp
//
//	The file contains info used when implementing Linux libraries.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"

#ifndef _LINUXLIB_LIBRARY_HPP_
#define _LINUXLIB_LIBRARY_HPP_

namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#ifdef __cplusplus

#ifdef LINUXLIB_LIBRARY_IMPL
#define LINUXLIB_LIBRARY_API	extern "C"
#else
#define LINUXLIB_LIBRARY_API	extern "C"
#endif

#else	//__cplusplus

#ifdef LINUXLIB_LIBRARY_IMPL
#define LINUXLIB_LIBRARY_API	extern
#else
#define LINUXLIB_LIBRARY_API	extern
#endif

#endif	//__cplusplus

//-------------------------------------------------------------------------

//Use this predefined name to obtain the name of the library function.
#define LINUXLIB_LIBRARY_FUNCNAME	"CreateObject"

//Use this type to prototype the library function.
typedef IRESULT (ICALL *LINUXLIB_LIBRARY_FUNCTION)(char const* pszName, VOID** ptrObject);

//-------------------------------------------------------------------------

//This is the main function of the library. It must be implemented in the LIB.
LINUXLIB_LIBRARY_API IRESULT ICALL CreateObject(char const* pszName, VOID** ptrObject);

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE

#endif	//_LINUXLIB_LIBRARY_HPP_
