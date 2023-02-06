//---------------------------------------------------------------------------
//
//	TComparer.hpp
//
//	The interface for implementing data comparers.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _TCOMPARER_HPP_
#define _TCOMPARER_HPP_

//---------------------------------------------------------------------------

template <class T> 
class TComparer
{
public:
	TComparer(VOID) {}
	virtual ~TComparer(VOID) {}

	//**************************************************************//
	//	This function is used to compare two arguments of type T.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refA	-	first argument's reference						//
	//																//
	//	refB	-	second argument's reference						//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns 0 if both arguments are equal, value	//
	//	greater than 0 if refA is greater than refB, and value less	//
	//	than 0 if refA is lesser than refB.							//
	//																//
	//**************************************************************//
	virtual int Compare(T const& refA, T const& refB) const = 0;

	//**************************************************************//
	//	This function is used to clone the comparer.				//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the pointer to the new instance of the	//
	//	comparer.													//
	//																//
	//**************************************************************//
	virtual TComparer<T>* Clone(VOID) = 0;
};

//---------------------------------------------------------------------------

#endif	//_TCOMPARER_HPP_
