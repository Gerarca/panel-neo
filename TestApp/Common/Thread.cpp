//---------------------------------------------------------------------------
//
//	Thread.cpp
//
//	Implementation of thread class type.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "Thread.hpp"
#include "Debug.hpp"

//---------------------------------------------------------------------------

	CThread::CThread(VOID) : 
		m_clsThread(THREAD_TYPE_INVALID_VALUE),
		m_flgStatus(ThreadStates::Unknown)
	{
	}

//---------------------------------------------------------------------------

	CThread::~CThread(VOID)
	{
		//try stopping the thread
		if (FALSE == Stop(THREAD_STOP_COUNT))
		{
			//the thread failed to stop
			DEBUG_ASSERT(FALSE);
			RELEASE_CHECK(FALSE);
		}
	}

//---------------------------------------------------------------------------

	ThreadState CThread::GetState(VOID) const
	{
		CLock lock = const_cast<CCriticalSection&>(m_objThreadLock);
		return m_flgStatus;
	}

//---------------------------------------------------------------------------

	BOOL CThread::TestThread(VOID) const
	{
		CLock lock = const_cast<CCriticalSection&>(m_objThreadLock);
		if ((ThreadStates::Unknown != m_flgStatus) &&
			(ThreadStates::Stopped != m_flgStatus))
		{
			//compare active threads
			return Platform::EQUAL_THREAD(m_clsThread);
		}
		//different threads
		return FALSE;
	}

//---------------------------------------------------------------------------

	BOOL CThread::Start(int numPriority)
	{
		//enter critical section
		BEGIN_CRITICAL_SECTION(m_objThreadLock);

			//check if the thread is present
			if ((ThreadStates::Unknown != m_flgStatus) &&
				(ThreadStates::Stopped != m_flgStatus))
			{
				//cannot re-initialize the thread right now
				return FALSE;
			}

			//create new thread
			THREAD_TYPE thread = THREAD_TYPE_INVALID_VALUE;
			if (FALSE != Platform::CREATE_THREAD(
				&thread, ThreadMain, static_cast<VOID*>(this)))
			{
				//set thread priority
				Platform::SET_THREAD_PRIORITY(thread, numPriority);

				//the thread is starting
				m_clsThread = thread;
				m_flgStatus = ThreadStates::Starting;
			}
			else
			{
				//cannot start the new thread
				m_clsThread = THREAD_TYPE_INVALID_VALUE;
				m_flgStatus = ThreadStates::Unknown;
				return FALSE;
			}

		END_CRITICAL_SECTION();


		//wait for the thread to start (or stop - in case of a problem)
		while (ThreadStates::Starting == GetState())
		{
			//take a nap
			Platform::THREAD_SLEEP(THREAD_IDLE_SLEEP);
		}
	
		//check whether the thread has started
		return (ThreadStates::Started == GetState())? TRUE : FALSE;
	}

//---------------------------------------------------------------------------

	//The timeout 0 is used to stop the thread without veryfying 
	//whether the thread has actualy stopped.
	//(if the timeout has not been specified, do not try to verify thread
	//state or access any other members of this class because the class
	//might have been deleted - that's what the timeout 0 is used for)
	BOOL CThread::Stop(int numTimeout)
	{
		//check if the created thread tries to stop itself
		//(this function must be called from a thread different
		//than the encapsulated thread or otherwise a deadlock
		//may happen)
		if (FALSE != TestThread())
		{
			//create temporary, 'shutdown' thread 
			//and quit immediately to avoid deadlock
			THREAD_TYPE thread = THREAD_TYPE_INVALID_VALUE;
			return Platform::CREATE_THREAD(
				&thread, ThreadShut, static_cast<VOID*>(this));
		}

		//enter critical section
		BEGIN_CRITICAL_SECTION(m_objThreadLock);

			//check if the thread is already stopped
			if ((ThreadStates::Unknown == m_flgStatus) ||
				(ThreadStates::Stopped == m_flgStatus))
			{
				//thread is already stopped
				return TRUE;
			}

			//check if the thread is currently running
			if ((ThreadStates::Starting == m_flgStatus) ||
				(ThreadStates::Started == m_flgStatus))
			{
				//signal the thread to shutdown
				m_flgStatus = ThreadStates::Shutdown;
			}
		
		END_CRITICAL_SECTION();

		//check if the stopping timeout is 0 (or less)
		if (0 >= numTimeout)	//no timeout specified?
		{
			//allow default waiting time if no timeout has been specified
			for (int i = THREAD_STOP_COUNT; 0 < i; --i)
			{
				//switch threads and wait
				Platform::THREAD_SLEEP(THREAD_STOP_SLEEP);
			}

			//thread stopping verification is not required
			return TRUE;
		}
		else
		{
			//wait for the thread to stop and verify its state
			for (int i = numTimeout; 0 < i; --i)
			{
				//switch threads and wait
				Platform::THREAD_SLEEP(THREAD_STOP_SLEEP);

				//check if the thread has stopped
				ThreadState state = GetState();
				if ((ThreadStates::Unknown == state) ||
					(ThreadStates::Stopped == state))
				{
					//thread has stopped
					return TRUE;
				}
			}
		}

		//failed to stop the thread
		return FALSE;
	}

//---------------------------------------------------------------------------

	//virtual function - should be overriden
	//(do NOT delete the CThread object within 
	//this function or bad things will haoppen!)
	BOOL CThread::ThreadStart(VOID* ptrParam)
	{
		ptrParam = NULL;	//just to suppress a warning
		return TRUE;	//return "FALSE" if error during initialization
	}

//---------------------------------------------------------------------------

	//virtual function - should be overriden
	//(do NOT delete the CThread object within 
	//this function or bad things will haoppen!)
	BOOL CThread::ThreadStop(VOID* ptrParam)
	{
		ptrParam = NULL;	//just to suppress a warning
		return TRUE;	//return "FALSE" to autodelete the thread (it makes
						//sense only for dynamically created threads)
	}					

//---------------------------------------------------------------------------

	//virtual function - should be overriden
	//(do NOT delete the CThread object within 
	//this function or bad things will happen!)
	BOOL CThread::ThreadProc(VOID* ptrParam)
	{
		ptrParam = NULL;	//just to suppress a warning
		return TRUE;	//return "FALSE" to stop the thread
	}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

	THREAD_RESULT THREAD_FUNC_CALL CThread::ThreadMain(VOID* ptrParam)
	{
		// get the pointer to the thread object
		CThread* pthread = static_cast<CThread*>(ptrParam);
		DEBUG_ASSERT(NULL != pthread);

		//local data
		BOOL started = FALSE;
		BOOL destroy = FALSE;

		//enter critical section
		BEGIN_CRITICAL_SECTION(pthread->m_objThreadLock);
			//is the thread still marked as starting?
			if (ThreadStates::Starting == pthread->m_flgStatus)
			{
				//mark the thread as started
				pthread->m_flgStatus = ThreadStates::Started;
				started = TRUE;	// the thread has started

				//prepare thread
				Platform::PREPARE_THREAD(pthread->m_clsThread);
			}
		END_CRITICAL_SECTION();

		//**************************************************
		//thread initialization and processing
		try
		{
			//thread started successfully?
			if (FALSE != started)
			{
				//execute the initialization code
				if (FALSE != pthread->ThreadStart(ptrParam))
				{
					//execute the main thread processing loop
					while (ThreadStates::Started == pthread->GetState())
					{
						//execute the processing code
						if (FALSE == pthread->ThreadProc(ptrParam))
						{
							//thread processing finished normally
							break;
						}

						//switch threads
						Platform::THREAD_SLEEP(THREAD_IDLE_SLEEP);
					}
				}
			}
		}
		catch (...)
		{
			//unexpected exception happened
			DEBUG_ASSERT(FALSE);
			RELEASE_CHECK(FALSE);
		}

		//**************************************************
		//the thread is stopping
		BEGIN_CRITICAL_SECTION(pthread->m_objThreadLock);
			//the thread has stopped
			pthread->m_flgStatus = ThreadStates::Stopping;
		END_CRITICAL_SECTION();

		//thread cleanup
		try
		{
			//execute the cleanup code
			if (FALSE == pthread->ThreadStop(ptrParam))
			{
				//auto-delete this object
				destroy = TRUE;
			}
		}
		catch (...)
		{
			//unexpected exception happened
			DEBUG_ASSERT(FALSE); 
			RELEASE_CHECK(FALSE); 
		}

		//**************************************************
		//the thread has stopped

		BEGIN_CRITICAL_SECTION(pthread->m_objThreadLock);
			//cleanup after the thread is done
			Platform::CLEANUP_THREAD(pthread->m_clsThread);

			//the thread has stopped
			pthread->m_clsThread = THREAD_TYPE_INVALID_VALUE;
			pthread->m_flgStatus = ThreadStates::Stopped;
		END_CRITICAL_SECTION();

		//auto delete this object?
		if (FALSE != destroy)
		{
			//auto-delete the thread object
			delete pthread;
		}

		//exit this thread
		return THREAD_RESULT_VALUE;
	}

//---------------------------------------------------------------------------

	THREAD_RESULT THREAD_FUNC_CALL CThread::ThreadShut(VOID* ptrParam)
	{
		// get the pointer to the thread context and shutdown the thread
		CThread* pthread = static_cast<CThread*>(ptrParam);
		DEBUG_ASSERT(NULL != pthread);

		//stop the thread
		try 
		{
			//try stopping the thread asynchronously
			if (FALSE == pthread->Stop())
			{
				//the thread failed to stop
				DEBUG_CHECK(FALSE);
				RELEASE_CHECK(FALSE);
			}
		} 
		catch (...) {}

		//exit this thread
		return THREAD_RESULT_VALUE;
	}

//---------------------------------------------------------------------------
