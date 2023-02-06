//---------------------------------------------------------------------------
//
//	Debug.cpp
//
//	Debugging macros and functions.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "Debug.hpp"
#include "Platform.hpp"

#include <stdarg.h>
#include <stdio.h>

#ifdef MS_VS_COMPILER
#include <intrin.h>		//contains the prototype for __debugbreak()
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif

//---------------------------------------------------------------------------

void DoDebugBreak(void)
{	
#ifdef MS_VS_COMPILER
	//break into debugger
	__debugbreak();
#else
	//all other compilers should get stuck here
	while (1)
	{
		Platform::THREAD_SLEEP(0);
	}
#endif
}

//---------------------------------------------------------------------------

#if (defined(ENABLE_DEBUG_TRACE) || defined(ENABLE_RELEASE_TRACE))
void Trace(const char* pszFormat, va_list args)
{
	//print trace text to stderr stream
	fprintf(stderr, "[%08X] ", Platform::GET_TIMESTAMP());
	vfprintf(stderr, pszFormat, args);
}
#endif

//---------------------------------------------------------------------------

//disable some well-understood warnings
#if defined(MS_VS_COMPILER)
#pragma warning(push)
#pragma warning(disable: 4996)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

#if (defined(ENABLE_DEBUG_TRACE) || defined(ENABLE_RELEASE_TRACE))
void TraceLog(const char* pszFormat, va_list args)
{
	//append trace text to the log file
	FILE* flog = fopen(DEBUG_LOGFILE, "a+");
	if (NULL != flog)
	{
		fprintf(flog, "[%08X] ", Platform::GET_TIMESTAMP());
		vfprintf(flog, pszFormat, args);
		fclose(flog);
	}
}
#endif

#if defined(MS_VS_COMPILER)
#pragma warning(pop)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------

void DebugTrace(const char* pszFormat, ...)
{
#if defined(ENABLE_DEBUG_TRACE) && defined(USE_FILE_TRACE_LOG)
	va_list args1;
	va_start(args1, pszFormat);
	TraceLog(pszFormat, args1);
	va_end(args1);
#endif

#if defined(ENABLE_DEBUG_TRACE)
	va_list args2;
	va_start(args2, pszFormat);
	Trace(pszFormat, args2);
	va_end(args2);
#endif
}

//---------------------------------------------------------------------------

void ReleaseTrace(const char* pszFormat, ...)
{
#if defined(ENABLE_RELEASE_TRACE) && defined(USE_FILE_TRACE_LOG)
	va_list args1;
	va_start(args1, pszFormat);
	TraceLog(pszFormat, args1);
	va_end(args1);
#endif

#if defined(ENABLE_RELEASE_TRACE)
	va_list args2;
	va_start(args2, pszFormat);
	Trace(pszFormat, args2);
	va_end(args2);
#endif
}

//---------------------------------------------------------------------------
