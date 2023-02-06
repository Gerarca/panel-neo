//---------------------------------------------------------------------------
//
//	StringComparer.cpp
//
//	String comparer helper class type provides functionality for comparing
//	strings.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "StringComparer.hpp"
#include <cctype>
#include <algorithm>

using namespace std;

//---------------------------------------------------------------------------

	CStringComparer::CStringComparer(BOOL flgCaseInsensitive) :
		m_flgCaseInsensitive(flgCaseInsensitive)
	{
	}

//---------------------------------------------------------------------------

	//copy constructor
	CStringComparer::CStringComparer(CStringComparer const& refCStringComparer) :
		m_flgCaseInsensitive(FALSE)
	{
		operator =(refCStringComparer);
	}

//---------------------------------------------------------------------------

	CStringComparer::~CStringComparer(VOID)
	{
	}


//---------------------------------------------------------------------------

	int CStringComparer::Compare(string const& refA, string const& refB) const
	{
		if (FALSE != m_flgCaseInsensitive)
		{
			//copy strings
			string tempA = refA;
			string tempB = refB;

			//convert the strings to upper case
			transform(tempA.begin(), tempA.end(), tempA.begin(), ::toupper);
			transform(tempB.begin(), tempB.end(), tempB.begin(), ::toupper);

			//compare strings
			return tempA.compare(tempB);
		}

		//use the string compare method of the string class
		return refA.compare(refB);
	}

//---------------------------------------------------------------------------

	TComparer<string>* CStringComparer::Clone(VOID)
	{
		return new CStringComparer(*this);
	}

//---------------------------------------------------------------------------

	//copy operator
	CStringComparer& CStringComparer::operator =(
		CStringComparer const& refCStringComparer)
	{
		m_flgCaseInsensitive = refCStringComparer.m_flgCaseInsensitive;
		return *this;
	}

//---------------------------------------------------------------------------

	int CStringComparer::Compare(string const& refA, 
		string const& refB, BOOL flgIgnoreCase)
	{
		//ignore case?
		if (FALSE != flgIgnoreCase)
		{
			//copy strings
			string tempA = refA;
			string tempB = refB;

			//convert the strings to upper case
			transform(tempA.begin(), tempA.end(), tempA.begin(), ::toupper);
			transform(tempB.begin(), tempB.end(), tempB.begin(), ::toupper);

			//compare strings
			return tempA.compare(tempB);
		}

		//use the string compare method of the string class
		return refA.compare(refB);
	}

//---------------------------------------------------------------------------
