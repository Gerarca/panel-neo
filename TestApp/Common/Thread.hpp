//---------------------------------------------------------------------------
//
//	Thread.hpp
//
//	Implementation of thread class type.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "Platform.hpp"
#include "Lock.hpp"

#ifndef _THREAD_HPP_
#define _THREAD_HPP_

//---------------------------------------------------------------------------

#define THREAD_IDLE_SLEEP		0		//processing sleep time [ms] (0 - just switch threads)
#define THREAD_STOP_SLEEP		1		//stopping sleep time in [ms]
#define THREAD_STOP_COUNT		1000	//stoping delay in units of THREAD_STOP_SLEEP[ms]

//---------------------------------------------------------------------------

//thread states
namespace ThreadStates {
enum value {
	Unknown = 0,	//the thread is unknown
	Stopped,		//the thread has stopped
	Started,		//the thread has started
	Stopping,		//the thread is stopping
	Starting,		//the thread is starting
	Shutdown		//the thread shutdown requested
}; }
typedef DSC_ENUM_T ThreadState;

//Therad's state transitions:
//'Unknown'->'Starting'->'Started'->('Exiting')->'Stopping'->'Stopped'
//The 'Exiting' state is set/used to request the thread processing loop
//to exit - for example by calling the 'Stop' method.

//---------------------------------------------------------------------------

class CThread
{
//private members
private:
	CCriticalSection	m_objThreadLock;	//critical section
	volatile THREAD_TYPE	m_clsThread;	//thread type
	volatile ThreadState	m_flgStatus;	//thread state

//constructor and destructor
public:
	CThread(VOID);
	virtual ~CThread(VOID);

//public methods
public:

	ThreadState GetState(VOID) const;	//return the thread state
	BOOL TestThread(VOID) const;		//compare created thread to current thread

	virtual BOOL Start(int numPriority = 0);	//start the thread
	virtual	BOOL Stop(int numTimeout = 0);		//stop the thread

//protected methods
protected:
	//Warning: Do NOT delete the CThread object from within one of
	//these functions or bad things will most certainly happen!
	virtual BOOL ThreadStart(VOID* ptrParam);	//called from ThreadMain before main loop
	virtual BOOL ThreadStop(VOID* ptrParam);	//called from ThreadMain after main loop
	virtual BOOL ThreadProc(VOID* ptrParam);	//called from ThreadMain main loop

//private methods
private:
	//the main function of the thread class type
	static THREAD_RESULT THREAD_FUNC_CALL ThreadMain(VOID* ptrParam);
	static THREAD_RESULT THREAD_FUNC_CALL ThreadShut(VOID* ptrParam);
};

//---------------------------------------------------------------------------

#endif //_THREAD_HPP_
