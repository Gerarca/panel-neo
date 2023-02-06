//---------------------------------------------------------------------------
//
//	Component.hpp
//
//	Base class for all DSC_IComponent implmentations.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "Lock.hpp"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

//---------------------------------------------------------------------------

class CComponent : public DSC_IComponent
{
//private members
private:

	//component references counter
	CCriticalSection	m_clsSyncLock;	//protection
	ICOUNT				m_numRefCount;

//constructors and destructor
public:

	CComponent(VOID);
	virtual ~CComponent(VOID);

//public methods
public:

	//The Query method returns a pointer to the interface specified by
	//the name. The method may pass back NULL if the specified interface
	//name is unknown.
	virtual IRESULT ICALL Query(IN char const* pszInterface, OUT VOID** ptrInterface);

	//The Acquire method informs the object implementing the interface
	//that a reference has been created. The lifetime of the object should
	//be maintained as long as there are any references present.
	//The function returns the number of currently remaining references.
	virtual IRESULT ICALL Acquire(OUT ICOUNT* ptrCount);

	//The Release method informs the object implementing the interface
	//that a reference has been dropped. When all references are released
	//the object is no longer needed and can be destroyed.
	//The function returns the number of currently remaining references.
	virtual IRESULT ICALL Release(OUT ICOUNT* ptrCount);

//protected methods
protected:

	//use this to synchronize access in overwriten virtual methods
	CCriticalSection& GetSyncLock(VOID);
};

//---------------------------------------------------------------------------

#endif	//_COMPONENT_HPP_
