//---------------------------------------------------------------------------
//
//	UInt16Map.hpp
//
//	Helper class for dealing with UINT16 bytes.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _UINT16MAP_HPP_
#define _UINT16MAP_HPP_

//---------------------------------------------------------------------------

class CUInt16Map
{
//private members
private:

//make sure the union is packed and aligned
#pragma pack(push, 1)
	typedef union {
		UINT16	Value;
		BYTE	Bytes[UINT16_SIZE];
	} DATA_UNION;
#pragma pack(pop)

//constructor and destructor
private:
	CUInt16Map(VOID);
	~CUInt16Map(VOID);

//public methods
public:

	//fetch UINT32 value from the data buffer
	static UINT16 FetchValue(const BYTE bufData[], 
		size_t numSize, BOOL flgSwap);

	//store UINT32 value in the data buffer
	static VOID StoreValue(BYTE bufData[], 
		size_t numSize, BOOL flgSwap, UINT16 numValue);

	//reverse the order of bytes in UINT16
	static UINT16 FlipBytes(UINT16 numValue);
};

//---------------------------------------------------------------------------

#endif	//_UINT16MAP_HPP_
