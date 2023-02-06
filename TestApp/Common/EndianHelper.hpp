//---------------------------------------------------------------------------
//
//	EndianHelper.hpp
//
//	Helper class for dealing with machine 'endianness'.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _ENDIAN_HELPER_HPP_
#define _ENDIAN_HELPER_HPP_

//---------------------------------------------------------------------------

class CEndianHelper
{
//private members
private:

//make sure the union is packed and aligned
#pragma pack(push, 1)
	typedef union {
		UINT16	Short;
		BYTE	Bytes[2];
	} DATA_UNION;
#pragma pack(pop)

//constructor
private:
	CEndianHelper(VOID);

//destructor
public:
	~CEndianHelper(VOID);

//public methods
public:

	static BOOL IsBigEndian(VOID);
	static BOOL IsLittleEndian(VOID);
};

//---------------------------------------------------------------------------

#endif	//_ENDIAN_HELPER_HPP_
