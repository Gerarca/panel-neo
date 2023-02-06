//---------------------------------------------------------------------------
//
//	Lock.hpp
//
//	Implementation of critical section locks.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "Lock.hpp"
#include "Debug.hpp"

//---------------------------------------------------------------------------

	CCriticalSection::CCriticalSection(VOID)
	{
		//initialize critical section
		if (FALSE == Platform::INIT_CRITICAL_SECTION(&m_objCriticalSection))
		{
			DEBUG_ASSERT(FALSE);	//break into debugger
			RELEASE_CHECK(FALSE);	//log during runtime
			throw CException(ExceptionCodes::Create_Critical_Section,
				"[CCriticalSection::CCriticalSection] Cannot init the critical section object!");
		}
	}

//---------------------------------------------------------------------------

	CCriticalSection::~CCriticalSection(VOID)
	{
		//release all pending locks
		while (0 < m_lstLockOwners.Count())
		{
			m_lstLockOwners[0]->Unlock();
		}

		//destroy the critical section
		if (FALSE == Platform::DESTROY_CRITICAL_SECTION(&m_objCriticalSection))
		{
			DEBUG_ASSERT(FALSE);	//break into debugger
			RELEASE_CHECK(FALSE);	//log during runtime
		}
	}

//---------------------------------------------------------------------------

	CCriticalSection& CCriticalSection::operator=(CCriticalSection const& refSection)
	{
		//the CRITICAL_SECTION objects must not be copied ever!

		//de-const the source critical section reference
		CCriticalSection& section = const_cast<CCriticalSection&>(refSection);

		//relock all the original locks using this critical section
		while (0 < section.m_lstLockOwners.Count())
		{
			//relock
			CLock* lock = section.m_lstLockOwners[0];
			DEBUG_ASSERT(NULL != lock);
			lock->Relock(this);
		}
		return *this;
	}

//---------------------------------------------------------------------------

	VOID CCriticalSection::Lock(CLock* ptrLock)
	{
		//sanity check
		if (NULL == ptrLock)
		{
			DEBUG_ASSERT(FALSE);	//break into debugger
			RELEASE_CHECK(FALSE);	//log during runtime
			throw CException(ExceptionCodes::Lock_Critical_Section,
				"[CCriticalSection::Lock] Missing the lock owner!");
		}

		//try locking the critical section
		if (FALSE == Platform::LOCK_CRITICAL_SECTION(&m_objCriticalSection))
		{
			//the object containing the critical section may have been
			//deleted and the critical section object is invalid but
			//let the code throw exception here and do not break into
			//debugger
			DEBUG_CHECK(FALSE);		//do not break into debugger
			RELEASE_CHECK(FALSE);	//log during runtime
			throw CException(ExceptionCodes::Lock_Critical_Section,
				"[CCriticalSection::Lock] Cannot lock the critical section!");
		}

		//find the lock owner
		int index = m_lstLockOwners.IndexOf(ptrLock);
		if (0 > index)
		{
			//add new lock owner
			m_lstLockOwners.Add(ptrLock);
		}
		else
		{
			//this should never happen
			DEBUG_ASSERT(FALSE);	//break into debugger
			RELEASE_CHECK(FALSE);	//log during runtime
			throw CException(ExceptionCodes::Lock_Critical_Section,
				"[CCriticalSection::Lock] Re-locking the critical section by the same lock object!");
		}
	}

//---------------------------------------------------------------------------

	VOID CCriticalSection::Unlock(CLock* ptrLock)
	{
		//sanity check
		if (NULL == ptrLock)
		{
			DEBUG_ASSERT(FALSE);	//break into debugger
			RELEASE_CHECK(FALSE);	//log during runtime
			throw CException(ExceptionCodes::Unlock_Critical_Section,
				"[CCriticalSection::Unlock] Missing the lock owner!");
		}

		//find the lock owner
		int index = m_lstLockOwners.IndexOf(ptrLock);
		if (0 <= index)
		{
			//remove the lock owner
			m_lstLockOwners.RemoveAt(size_t(index));
		}
		else
		{
			//this should never happen
			DEBUG_ASSERT(FALSE);	//break into debugger
			RELEASE_CHECK(FALSE);	//log during runtime
			throw CException(ExceptionCodes::Lock_Critical_Section,
				"[CCriticalSection::Unlock] Un-locking the critical section by unknown lock object!");
		}

		//try unlocking the critical section
		if (FALSE == Platform::UNLOCK_CRITICAL_SECTION(&m_objCriticalSection))
		{
			DEBUG_ASSERT(FALSE);	//break into debugger
			RELEASE_CHECK(FALSE);	//log during runtime
			throw CException(ExceptionCodes::Unlock_Critical_Section,
				"[CCriticalSection::Unlock] Cannot unlock the critical section!");
		}
	}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

	CLock::CLock(CCriticalSection& refCriticalSection) : 
		m_ptrCriticalSection(NULL)
	{
		Relock(&refCriticalSection);
	}

//---------------------------------------------------------------------------

	CLock::~CLock(VOID)
	{
		Unlock();
	}

//---------------------------------------------------------------------------

	CLock& CLock::operator=(CLock const& refLock)
	{
		//release the current lock
		Unlock();

		//copy the pointer to the critical section
		m_ptrCriticalSection = refLock.m_ptrCriticalSection;

		//was the original lock engaged?
		if (NULL != m_ptrCriticalSection)
		{
			//lock the cruitical section here, too
			m_ptrCriticalSection->Lock(this);
		}
		return *this;
	}

//---------------------------------------------------------------------------

	VOID CLock::Relock(CCriticalSection* ptrCriticalSection)
	{
		//save the original critical section
		CCriticalSection* original = m_ptrCriticalSection;

		//lock the new critical section
		if (NULL != ptrCriticalSection)
		{
			ptrCriticalSection->Lock(this);
			m_ptrCriticalSection = ptrCriticalSection;
		}

		//unlock the original critical section
		if (NULL != original)
		{
			//unlock the critical section
			original->Unlock(this);
		}
	}

//---------------------------------------------------------------------------

	VOID CLock::Unlock(VOID)
	{
		//check if the critical section is locked
		if (NULL != m_ptrCriticalSection)
		{
			//unlock the critical section
			m_ptrCriticalSection->Unlock(this);
			m_ptrCriticalSection = NULL;
		}
	}

//---------------------------------------------------------------------------
