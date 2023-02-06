//---------------------------------------------------------------------------
//
//	StringComparer.hpp
//
//	String comparer helper class type provides functionality for comparing
//	strings.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "TComparer.hpp"
#include <string>

using namespace std;

#ifndef _STRINGCOMPARER_HPP_
#define _STRINGCOMPARER_HPP_

//---------------------------------------------------------------------------

class CStringComparer : public TComparer<string>
{
//private members
private:
	BOOL m_flgCaseInsensitive;

//constructor & destructor
public:
	CStringComparer(BOOL flgCaseInsensitive = FALSE);
	CStringComparer(CStringComparer const& refCStringComparer);
	virtual ~CStringComparer(VOID);

//public methods
public:
	virtual int Compare(string const& refA, string const& refB) const;
	virtual TComparer<string>* Clone(VOID);

//operators
public:
	CStringComparer& operator =(CStringComparer const& refCStringComparer);

//static methods
public:
	static int Compare(string const& refA, 
		string const& refB, BOOL flgIgnoreCase = FALSE);
};

//---------------------------------------------------------------------------

#endif	//_STRINGCOMPARER_HPP_
