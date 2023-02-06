//---------------------------------------------------------------------------
//
//	TTypeHelp.hpp
//
//	Various template helper classes based on the article
//	"http://www.stroustrup.com/bs_faq2.html#constraints"
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"
#include "DSC_IComponent.hpp"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

#ifndef _TYPEHELP_HPP_
#define _TYPEHELP_HPP_

//---------------------------------------------------------------------------

//Force the compiler to complain if the class T 
//doesn't implement the DSC_IComponent interface.
template<class T>
struct IsComponent {
	static VOID Constraints(T* a) 
	{ 
		VOID* ptr;
		a->Query(NAME_DSC_IComponent, &ptr);
		a->Acquire(NULL);
		a->Release(NULL);
	}
	IsComponent(VOID) 
	{ 
		VOID(*FUNC)(T*) = Constraints; 
		if (FUNC) {};
	} //trigger
};

//---------------------------------------------------------------------------

//Force the compiler to complain if the class T is not derived from the class TBase.
template<class T, class TBase>
struct IsDerived {
	//can T* be casted back onto TBase*?
	static VOID Constraints(T* a) { TBase* b = a; }
	IsDerived(VOID) 
	{ 
		VOID(*FUNC)(T*) = Constraints; 
		if (FUNC) {};
	} //trigger
};

//---------------------------------------------------------------------------

//Force the compiler to complain if the class T2 cannot copy data from class T1.
template<class T1, class T2>
struct CanCopy {
	//is: 1) copy constructor present, and 2) copy operator present?
	static VOID Constraints(T1 a, T2 b) { T2 c = a; b = a; }
	CanCopy(VOID) 
	{ 
		VOID(*FUNC)(T1, T2) = Constraints; 
		if (FUNC) {};
	} //trigger
};

//---------------------------------------------------------------------------

#endif	//_TYPEHELP_HPP_
