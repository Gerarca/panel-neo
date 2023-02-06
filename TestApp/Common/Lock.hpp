//---------------------------------------------------------------------------
//
//	Lock.hpp
//
//	Implementation of critical section locks.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "Platform.hpp"
#include "TList.hpp"

#ifndef _LOCK_HPP_
#define _LOCK_HPP_

//---------------------------------------------------------------------------

//the following two macros are used to simply emphasize that 
//the code between them is protected by the 'critical_section'
#define BEGIN_CRITICAL_SECTION(critical_section)	{ CLock lock = critical_section;
#define END_CRITICAL_SECTION()						}

//---------------------------------------------------------------------------

// forward declaration
class CLock;

class CCriticalSection
{
//friends
private:
	//Only the CLock class is allowed to lock/unlock the critical
	//section object.
	friend class CLock;	//the CLock class can use private methods

//private members
private:
	//critical section data object
	CRITICAL_SECTION	m_objCriticalSection;
	TList<CLock*>		m_lstLockOwners;	//all the owners of recursive lock

	//The critical section can be locked by the same thread recursively.
	//When the critical section is being destroyed - as a result of the 
	//destruction of a containing object, it must unlock all the CLock
	//objects. Otherwise the heap may become corrupted.

//constructors and destructor
public:
	CCriticalSection(VOID);
	virtual ~CCriticalSection(VOID);

//operators
public:
	CCriticalSection& operator=(CCriticalSection const& refSection);

//private methods (only for access by friends)
private:
	VOID Lock(CLock* ptrLock);		//enter critical section
	VOID Unlock(CLock* ptrLock);	//leave critical section
};

//---------------------------------------------------------------------------

//The CLock class provides means to lock the critical section for the entire
//life of the Lock object.
class CLock
{
//friends
private:
	//The critical section should be able to release the lock if necessary.
	//For example the CCriticalSection being a member of a class would be
	//destroyed when the class is destroyed. It is necessary to ensure that
	//there is no left-over CLock object that might try to unlock the critical
	//section after it has already been destroyed - that would cause hard to
	//detect problems with heap corruption.
	friend class CCriticalSection;	//the CCriticalSection class can use private methods

//private members
private:
	CCriticalSection*	m_ptrCriticalSection;

//constructors and destructor
public:
	CLock(CCriticalSection& refCriticalSection);
	virtual ~CLock(VOID);

//operators
public:
	CLock& operator=(CLock const& refLock);

//private methods (only for access by friends)
private:
	VOID Relock(CCriticalSection* ptrCriticalSection);	//change the lock
	VOID Unlock(VOID);	//release the lock
};

//Lock encapsulates functionality for locking and unlocking critical 
//sections. Using CLock along with CCriticalSection guarantees that all 
//critical sections will be 'unlocked' when object containing CLock is
//destroyed.

//---------------------------------------------------------------------------

#endif	//_LOCK_HPP_
