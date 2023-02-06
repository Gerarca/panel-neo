//---------------------------------------------------------------------------
//
//	Debug.hpp
//
//	Debugging macros and functions.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

//---------------------------------------------------------------------------

//application debug log file
#define DEBUG_LOGFILE	"AppDebug.log"

//---------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {
#endif

//debug functions prototypes
void DebugTrace(const char* pszFormat, ...);
void ReleaseTrace(const char* pszFormat, ...);
void DoDebugBreak(void);

#if defined(__cplusplus)
}
#endif

//---------------------------------------------------------------------------

#if defined(ENABLE_DEBUG_TRACE)

//show debug trace (The reson for 2 macros: _PRINT and _PRINTF is that the __VA_ARGS__
//may expand to nothing at all and confuse the compiler. The "##__VA_ARGS__" extension
//that solves the problem is unfortunately non-standard and therefore not portable.)
#define DEBUG_PRINT(text)			DebugTrace(text)
#define DEBUG_PRINTF(fmt, ...)		DebugTrace(fmt, __VA_ARGS__)

//enable the debug check
#define DEBUG_CHECK(expr)			do { if (!(expr)) DEBUG_PRINTF("Debug check \"%s\" failed in the file \"%s\" in line %d.\n", #expr, __FILE__, __LINE__); } while (0)

//***************************
#if defined(MS_VS_COMPILER)
//***************************
//enable the assert
#define DEBUG_ASSERT(expr)			do { if (!(expr)) { DEBUG_PRINTF("Debug assert \"%s\" failed in the file \"%s\" in line %d.\n", #expr, __FILE__, __LINE__); DoDebugBreak(); } } while (0)
//***************************
#elif defined(GCC_COMPILER)
//***************************
//enable the assert
#define DEBUG_ASSERT(expr)			do { if (!(expr)) DEBUG_PRINTF("Debug assert \"%s\" failed in the file \"%s\" in line %d.\n", #expr, __FILE__, __LINE__); } while (0)
//***************************
#else
#error "Undefined compiler information!"
#endif
//***************************

#else	//!ENABLE_DEBUG_TRACE

//hide debug trace (in Release mode, the compile should "optimize out" the "if (0)" code)
#define DEBUG_PRINT(text)			do { if (0) DebugTrace(text); } while (0)
#define DEBUG_PRINTF(fmt, ...)		do { if (0) DebugTrace(fmt, __VA_ARGS__); } while (0)

//disable the debug check and the assert
#define DEBUG_CHECK(expr)			((void)(0))
#define DEBUG_ASSERT(expr)			((void)(0))

#endif	//ENABLE_DEBUG_TRACE

//---------------------------------------------------------------------------

#if defined(ENABLE_RELEASE_TRACE)

//show the release trace
#define RELEASE_PRINT(text)			ReleaseTrace(text)
#define RELEASE_PRINTF(fmt, ...)	ReleaseTrace(fmt, __VA_ARGS__)

//enable the release check
#define RELEASE_CHECK(expr)			do { if (!(expr)) RELEASE_PRINTF("Release check \"%s\" failed in the file \"%s\" in line %d.\n", #expr, __FILE__, __LINE__); } while (0)

#else	//!ENABLE_RELEASE_TRACE

//hide the release trace
#define RELEASE_PRINT(text)			do { if (0) ReleaseTrace(text); } while (0)
#define RELEASE_PRINTF(fmt, ...)	do { if (0) ReleaseTrace(fmt, __VA_ARGS__); } while (0)

//disable the release check
#define RELEASE_CHECK(expr)			((void)(0))

#endif	//ENABLE_RELEASE_TRACE

//---------------------------------------------------------------------------

#endif	//_DEBUG_HPP_
