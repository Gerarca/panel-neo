//---------------------------------------------------------------------------
//
//	HexHelper.hpp
//
//	String converter helper class.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "TMemPtr.hpp"
#include <string>

using namespace std;

#ifndef _HEX_HELPER_HPP_
#define _HEX_HELPER_HPP_

//---------------------------------------------------------------------------

class CHexHelper
{
//constants
private:
	static const char m_tblHexDigitsUpper[16];
	static const char m_tblHexDigitsLower[16];
	static const string m_strWhiteSpaces;
	static const string m_strHexDigitsUpper;
	static const string m_strHexDigitsLower;

//constructors and destructor
private:
	CHexHelper(VOID);
public:
	virtual ~CHexHelper(VOID);

//public methods
public:
	//convert ASCII string containing hex digits to bytes
	static BYTE_MEMPTR ToBytes(string const& strText, 
		string const& strPrefix, string const& strSuffix,
		string const& strSeparator, BOOL flgAlignLeft = FALSE);

	//convert bytes to ASCII string containing hex digits
	static string ToString(BYTE const* bufData, size_t numSize, 
		string const& strPrefix, string const& strSuffix,
		string const& strSeparator, BOOL flgToLower = FALSE);

//private methods
private:
	static BYTE GetValue(char c);
	static VOID GetBytes(BYTE_MEMPTR& bufBytes, size_t& numBytes,
		string const& strText, size_t& numIndex, size_t numCount, 
		BOOL flgAlignLeft);
};

//---------------------------------------------------------------------------

#endif	//_HEX_HELPER_HPP_
