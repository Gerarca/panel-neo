//---------------------------------------------------------------------------
//
//	Platform.hpp
//
//	The file contains platform-dependent API.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _PLATFORM_HPP_
#define _PLATFORM_HPP_

//---------------------------------------------------------------------------

//******************************************************
#if defined(WINDOWS)
//******************************************************

//thread info (do NOT use the '_beginthreadex' but use _beginthread instead
//because the _beginthread will automatically free the resources after the
//thread is finished)
#define THREAD_TYPE					HANDLE
#define THREAD_TYPE_INVALID_VALUE	INVALID_HANDLE_VALUE
//#define THREAD_FUNC_CALL			__stdcall	//used by _beginthreadex
//#define THREAD_RESULT				UINT32		//used by _beginthreadex
//#define THREAD_RESULT_VALUE		0			//used by _beginthreadex
#define THREAD_FUNC_CALL			__cdecl		//used by _beginthread
#define THREAD_RESULT				VOID		//used by _beginthread
#define THREAD_RESULT_VALUE						//used by _beginthread

//the 'ptr' must be a pointer to (U)INT32
#define ATOMIC_INCREMENT(ptr)	InterlockedIncrement(ptr)
#define ATOMIC_DECREMENT(ptr)	InterlockedDecrement(ptr)

//The CRITICAL_SECTION on Windows is process-bound while
//mutexes can be used across process boundaries.
#define CRITICAL_SECTION	CRITICAL_SECTION

//******************************************************
#elif defined(LINUX)
//******************************************************

//thread info
#define THREAD_TYPE					pthread_t
#define THREAD_TYPE_INVALID_VALUE	0
#define THREAD_FUNC_CALL
#define THREAD_RESULT				VOID*
#define THREAD_RESULT_VALUE			NULL

//the 'ptr' must be a pointer to (U)INT32
#define ATOMIC_INCREMENT(ptr)	__sync_add_and_fetch(ptr, 1)
#define ATOMIC_DECREMENT(ptr)	__sync_sub_and_fetch(ptr, 1)

//The pthread_mutex_t on Posix systems is process-bound.
//In that sense the mutex is equivalent to CRITICAL_SECTION
//on Windows (and not Windows' mutex object).
#define CRITICAL_SECTION	pthread_mutex_t

//******************************************************
#else
//******************************************************

#error "Undefined platform information!"

//******************************************************
#endif
//******************************************************

//---------------------------------------------------------------------------

typedef THREAD_RESULT (THREAD_FUNC_CALL *THREAD_FUNCTION)(VOID* ptrArgs);

//---------------------------------------------------------------------------

class Platform
{
//constructors/destructor
private:

	Platform(VOID);
	~Platform(VOID);

//public methods related to ritical sections
public:

	//initialize critical section data structure
	static BOOL INIT_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection);

	//destroy critical section data structure
	static BOOL DESTROY_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection);

	//lock critical section
	static BOOL LOCK_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection);

	//unlock critical section
	static BOOL UNLOCK_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection);

	//validate pointer
	static BOOL VALIDATE_HEAP_POINTER(VOID* ptrData);

#ifndef EXCLUDE_THREAD_SUPPORT

	//put thread to sleep [ms]
	static VOID THREAD_SLEEP(UINT32 numTime);

	//create a new thread
	static BOOL CREATE_THREAD(THREAD_TYPE* ptrThread, 
		THREAD_FUNCTION ptrFunction, VOID* ptrArgs);

	////cleanup kernel thread resources (needed by _beginthreadex)
	//static BOOL DELETE_THREAD(THREAD_TYPE* ptrThread);

	//compare current thread
	static BOOL EQUAL_THREAD(THREAD_TYPE objThread);

	//prepare thread after it is launched
	static BOOL PREPARE_THREAD(THREAD_TYPE objThread);

	//cleanup after the thread is finished
	static BOOL CLEANUP_THREAD(THREAD_TYPE objThread);

	//set thread's priority
	static BOOL SET_THREAD_PRIORITY(THREAD_TYPE objThread, int numPriority);

#endif	//EXCLUDE_THREAD_SUPPORT

	//get a timestamp in milliseconds
	static UINT32 GET_TIMESTAMP(VOID);
};

//---------------------------------------------------------------------------

#endif	//_PLATFORM_HPP_
