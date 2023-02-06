//---------------------------------------------------------------------------
//
//	Platform.cpp
//
//	The file contains platform-dependent API.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "Platform.hpp"
#include "Exception.hpp"

//---------------------------------------------------------------------------

//******************************************************
#if defined(WINDOWS)
//******************************************************

#include <process.h>
#include <Mmsystem.h>
#include <Windows.h>

//******************************************************
#elif defined(LINUX)
//******************************************************

#include <time.h>
#include <errno.h>

//the number of nanoseconds per one millisecond
#define MSEC_PER_SEC    1000
#define	NSEC_PER_MSEC	1000000
#define NSEC_PER_SEC    1000000000

//******************************************************
#else
//******************************************************

#error "Undefined platform information!"

//******************************************************
#endif
//******************************************************

//---------------------------------------------------------------------------

	Platform::Platform(VOID)
	{
	}

//---------------------------------------------------------------------------

	Platform::~Platform(VOID)
	{
	}

//---------------------------------------------------------------------------

//******************************************************
#if defined(WINDOWS)
//******************************************************

//initialize critical section data structure
BOOL Platform::INIT_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection)
{
	InitializeCriticalSection(ptrCriticalSection);
	return TRUE;
}

//destroy critical section data structure
BOOL Platform::DESTROY_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection)	
{
	DeleteCriticalSection(ptrCriticalSection);
	return TRUE;
}

//lock critical section
BOOL Platform::LOCK_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection)	
{
	//try to enter critical section
	__try {
		//try entering the critical section (may throw exception if fails)
		EnterCriticalSection(ptrCriticalSection);
		return TRUE;
	} __except(EXCEPTION_EXECUTE_HANDLER) 
	{
		//just intercept exceptions
	}
	//failure
	return FALSE;
}

//unlock critical section
BOOL Platform::UNLOCK_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection)	
{
	//leave the critical section
	LeaveCriticalSection(ptrCriticalSection);
	return TRUE;
}

#ifndef EXCLUDE_THREAD_SUPPORT

//put thread to sleep
VOID Platform::THREAD_SLEEP(UINT32 numTime)
{
	Sleep(numTime);
}

//create a new thread
BOOL Platform::CREATE_THREAD(
	THREAD_TYPE* ptrThread, THREAD_FUNCTION ptrFunction, VOID* ptrArgs)
{
	//try creating a new thread
	//*ptrThread = (THREAD_TYPE)_beginthreadex(NULL, 0, ptrFunction, ptrArgs, 0, NULL);
	//return (NULL != *ptrThread) ? TRUE : FALSE;
	*ptrThread = (THREAD_TYPE)_beginthread(ptrFunction, 0, ptrArgs);
	return (THREAD_TYPE_INVALID_VALUE != *ptrThread)? TRUE : FALSE;
}

//BOOL Platform::DELETE_THREAD(THREAD_TYPE* ptrThread)
//{
//	//validate current thread
//	if (THREAD_TYPE_INVALID_VALUE != *ptrThread)
//	{
//		//close thread
//		if (0 != CloseHandle(*ptrThread))
//		{
//			//success
//			*ptrThread = THREAD_TYPE_INVALID_VALUE;
//			return TRUE;
//		}
//	}
//	//failure
//	return FALSE;
//}

//compare current thread
BOOL Platform::EQUAL_THREAD(THREAD_TYPE objThread)
{
	//get current thread id
	DWORD current = GetCurrentThreadId();
	DWORD another = GetThreadId(objThread);

	//compare thread IDs
	return (current == another)? TRUE : FALSE;
}

BOOL Platform::PREPARE_THREAD(THREAD_TYPE objThread)
{
	objThread = THREAD_TYPE_INVALID_VALUE;	//just to get rid of compiler warning
	return (TIMERR_NOERROR == timeBeginPeriod(1))? TRUE : FALSE;
}

BOOL Platform::CLEANUP_THREAD(THREAD_TYPE objThread)
{
	objThread = THREAD_TYPE_INVALID_VALUE;	//just to get rid of compiler warning
	return (TIMERR_NOERROR == timeEndPeriod(1))? TRUE : FALSE;
}

BOOL Platform::SET_THREAD_PRIORITY(THREAD_TYPE objThread, int numPriority)
{
	//update thread priority (it may not work for some values on Windows)
	if (0 != SetThreadPriority(objThread, numPriority))
	{
		//success
		return TRUE;
	}
	//failure
	return FALSE;
}

#endif//EXCLUDE_THREAD_SUPPORT

UINT32 Platform::GET_TIMESTAMP(VOID)
{
	return static_cast<UINT32>(GetTickCount() & UINT32_MASK);
}

//******************************************************
#elif defined(LINUX)
//******************************************************

//initialize critical section data structure
BOOL Platform::INIT_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection)
{
	//create mutex attribute
	pthread_mutexattr_t attr;
	if (0 == pthread_mutexattr_init(&attr))
	{
		//set the 'recursive mutex' attribute
		if (0 == pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE))
		{
			//initialize mutex
			if (0 == pthread_mutex_init(ptrCriticalSection, &attr))
			{
				//success
				return TRUE;
			}
		}
	}
	//failure
	return FALSE;
}

//destroy critical section data structure
BOOL Platform::DESTROY_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection)	
{
	if (0 == pthread_mutex_destroy(ptrCriticalSection))
	{
		//success
		return TRUE;
	}
	//failure
	return FALSE;
}

//lock critical section
BOOL Platform::LOCK_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection)	
{
	if (0 == pthread_mutex_lock(ptrCriticalSection))
	{
		//success
		return TRUE;
	}
	//failure
	return FALSE;
}

//unlock critical section
BOOL Platform::UNLOCK_CRITICAL_SECTION(CRITICAL_SECTION* ptrCriticalSection)	
{
	if (0 == pthread_mutex_unlock(ptrCriticalSection))
	{
		//success
		return TRUE;
	}
	//failure
	return FALSE;
}

#ifndef EXCLUDE_THREAD_SUPPORT

//put thread to sleep
VOID Platform::THREAD_SLEEP(UINT32 numTime)
{
	//original code (doesn't take into account error return due to non-EINTR ... therefore &delay will not be updated properly for remaining time
	//setup the timespec structure
	//timespec delay;
	//delay.tv_sec = 0;
	//delay.tv_nsec = NSEC_PER_MSEC;
	//delay.tv_nsec *= numTime;

	//put the thread to sleep (resume if interrupted)
	//while (0 != nanosleep(&delay, &delay)); 

	//first update (suffers from possible race condition if clock is changed via administrator or network time update)
	//while (1)
	//{
	//	// Sleep for the time specified in delay. If interrupted by a
	//	// signal, place the remaining time left to sleep back into delay.
	//	int rval = nanosleep(&delay, &delay);
	//	if (rval == 0)
	//	{
	//		// Completed the entire sleep time; all done.
	//		return;
	//	}
	//	else if (errno == EINTR)
	//	{
	//		// Interrupted by a signal. Try again.
	//		continue;
	//	}
	//	else
	//	{
	//		// Some other error; bail out.
	//		return;
	//	}
	//}

	struct timespec deadline;
	clock_gettime(CLOCK_MONOTONIC, &deadline);

	// Add the time you want to sleep
	deadline.tv_nsec += (numTime * NSEC_PER_MSEC);

	// Normalize the time to account for the second boundary (NOTE!!! if numTime > 1 second then this normalization needs to change)
	if (deadline.tv_nsec >= NSEC_PER_SEC)
	{
		deadline.tv_nsec -= NSEC_PER_SEC;
		deadline.tv_sec++;
	}
	
	while (1)
	{
		int rval = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
		if (rval == 0)
		{
			// sleep time complete; done
			break;
		}
		else if (rval == EINTR)
		{
			// interrupted by a signal; continue
			continue;
		}
		else
		{
			// some error; bail
			break;
		} 
	}

	return;
}

//create a new thread
BOOL Platform::CREATE_THREAD(
	THREAD_TYPE* ptrThread, THREAD_FUNCTION ptrFunction, VOID* ptrArgs)
{
	//create attributes
	pthread_attr_t attributes;
	if (0 != pthread_attr_init(&attributes))
	{
		//cannot init attributes
		goto CREATE_THREAD_Failure;
	}

	//set 'detached' attribute
	if (0 != pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED))
	{
		//cannot set 'detached' attribute
		goto CREATE_THREAD_Failure;
	}

	//create thread
	if (0 != pthread_create(ptrThread, &attributes, ptrFunction, ptrArgs))
	{
		//cannot create the thread
		goto CREATE_THREAD_Failure;
	}

	//cleanup and success
	pthread_attr_destroy(&attributes);
	return TRUE;

CREATE_THREAD_Failure:
	//cleanup and failure
	pthread_attr_destroy(&attributes);
	*ptrThread = THREAD_TYPE_INVALID_VALUE;
	return FALSE;
}

//BOOL Platform::DELETE_THREAD(THREAD_TYPE* ptrThread)
//{
//	//done
//	*ptrThread = THREAD_TYPE_INVALID_VALUE;
//	return TRUE;
//}

//compare current thread
BOOL Platform::EQUAL_THREAD(THREAD_TYPE objThread)
{
	//get current thread id
	pthread_t current = pthread_self();

	//compare thread IDs
	return pthread_equal(current, objThread)? TRUE : FALSE;
}

BOOL Platform::PREPARE_THREAD(THREAD_TYPE objThread)
{
	//allow killing the thread if necessary (resources may leak!)
#if defined(ANDROID)
	return (0 == pthread_kill (objThread,0))? TRUE: FALSE;
#else
	return (0 == pthread_setcanceltype(
		PTHREAD_CANCEL_ASYNCHRONOUS, NULL))? TRUE : FALSE;

#endif
}

BOOL Platform::CLEANUP_THREAD(THREAD_TYPE objThread)
{
	//done
	return TRUE;
}

BOOL Platform::SET_THREAD_PRIORITY(THREAD_TYPE objThread, int numPriority)
{
	//get supported priority range
	int policy = 0;
	sched_param sparam = {0};
	if (0 == pthread_getschedparam(objThread, &policy, &sparam))
	{
		//get min and max priority numbers
		int min_prio = sched_get_priority_min(policy);
		int max_prio = sched_get_priority_max(policy);

		//set thread's priority if required
		if ((numPriority >= min_prio) && (numPriority <= max_prio))
		{
			//update thread priority (it may not work for some policy types on Linux)
			sparam.sched_priority = numPriority;
			if (0 == pthread_setschedparam(objThread, policy, &sparam))
			{
				//success
				return TRUE;
			}
		}
	}

	//failure
	return FALSE;
}

#endif	//EXCLUDE_THREAD_SUPPORT

UINT32 Platform::GET_TIMESTAMP(VOID)
{
	struct timespec ts;
	if (-1 == clock_gettime(CLOCK_MONOTONIC, &ts))
	{
		ts.tv_sec = 0;
		ts.tv_nsec = 0;
	}
	return static_cast<UINT32>((ts.tv_sec * MSEC_PER_SEC) & UINT32_MASK) + 
		static_cast<UINT32>((ts.tv_nsec / NSEC_PER_MSEC) & UINT32_MASK);
}

//******************************************************
#else
//******************************************************

#error "Undefined platform information!"

//******************************************************
#endif
//******************************************************

//---------------------------------------------------------------------------

//******************************************************
#if defined(MS_VS_COMPILER)
//******************************************************

BOOL Platform::VALIDATE_HEAP_POINTER(VOID* ptrData)
{
	if (!_CrtCheckMemory())
	{
		//heap problem
		return FALSE;
	}
	
	if (!_CrtIsValidHeapPointer(ptrData))
	{
		//pointer problem
		return FALSE;
	}

	//all looks good
	return TRUE;
}

//******************************************************
#elif defined(GCC_COMPILER)
//******************************************************

BOOL Platform::VALIDATE_HEAP_POINTER(VOID* ptrData)
{
	//if (!_CrtCheckMemory())	//update with linux function
	//{
	//	//heap problem
	//	return FALSE;
	//}
	//
	//if (!_CrtIsValidHeapPointer(ptrData))	//update with linux function
	//{
	//	//pointer problem
	//	return FALSE;
	//}

	//all looks good
	return TRUE;
}

//******************************************************
#else
//******************************************************

#error "Undefined compiler information!"

//******************************************************
#endif	//MS_VS_COMPILER
//******************************************************

//---------------------------------------------------------------------------
