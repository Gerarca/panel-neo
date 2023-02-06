//---------------------------------------------------------------------------
//
//	UtfConverter.hpp
//
//	UTF converter helper implementation.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"
#include "TMemPtr.hpp"

#ifndef _UTF_CONVERTER_HPP_
#define _UTF_CONVERTER_HPP_

//---------------------------------------------------------------------------

//the Unicode character code (do not confuse with the UTF encoding!)
typedef UINT32	UCHAR_CODE;

//---------------------------------------------------------------------------

class CUtfConverter
{
//private members
private:
	static const UINT32 Utf8Ranges[4];

//constructor
private:	//prevent instantiation
	CUtfConverter(VOID);

//destructor
public:
	virtual ~CUtfConverter(VOID);

//public methods
public:

	static size_t SizeOfUTF8(UCHAR_CODE numCode);
	static BYTE_MEMPTR CharToUTF8(UCHAR_CODE numCode);
	static UCHAR_CODE CharFromUTF8(BYTE const* bufData, 
		size_t numSize, size_t* ptrIndex);

	static size_t SizeOfUTF16(UCHAR_CODE numCode);
	static BYTE_MEMPTR CharToUTF16(
		UCHAR_CODE numCode, BOOL flgLittleEndian);
	static UCHAR_CODE CharFromUTF16(BYTE const* bufData, 
		size_t numSize, size_t* ptrIndex, BOOL flgLittleEndian);

	//convert the string to UTF16
	static BOOL StringToUTF8(
		string const& strText, BYTE_MEMPTR& refData);

	//convert the UTF8 to string
	static BOOL StringFromUTF8(
		BYTE const* bufData, size_t numSize, string& strText);

	//convert the UTF8 string to UTF16 (optionally 
	//add the byte order mark at the begining)
	static BOOL StringToUTF16(string const& strText, 
		BOOL flgLittleEndian, BOOL flgAddByteOrderMark, 
		BYTE_MEMPTR& refData);

	//convert the UTF16 to UTF8 string using the byte order mark
	//to determine the 'endianess' (the BOM must be present!)
	static BOOL StringFromUTF16(BYTE const* bufData, 
		size_t numSize, string& strText);

	//convert the UTF16 to UTF8 string using pre-determined
	//byte order information
	static BOOL StringFromUTF16(BYTE const* bufData, 
		size_t numSize, BOOL flgLittleEndian, string& strText);

//private methods
private:

	static BOOL Add6Bits(BYTE const* bufData, 
		size_t numSize, size_t numIndex, UCHAR_CODE& numCode);

	static VOID Store2Bytes(BYTE* bufData,
		UCHAR_CODE numValue, BOOL flgLittleEndian);

	static BOOL Load2Bytes(BYTE const* bufData, size_t numSize, 
		size_t numIndex, BOOL flgLittleEndian, UCHAR_CODE& numCode);
};

//---------------------------------------------------------------------------

#endif	//_UTF_CONVERTER_HPP_
