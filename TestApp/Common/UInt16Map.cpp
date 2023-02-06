//---------------------------------------------------------------------------
//
//	UInt16Map.cpp
//
//	Helper class for dealing with UINT16 bytes.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "UInt16Map.hpp"
#include "Debug.hpp"

//---------------------------------------------------------------------------

	CUInt16Map::CUInt16Map(VOID)
	{
	}

//---------------------------------------------------------------------------

	CUInt16Map::~CUInt16Map(VOID)
	{
	}

//---------------------------------------------------------------------------

	UINT16 CUInt16Map::FetchValue(const BYTE bufData[], 
		size_t numSize, BOOL flgSwap)
	{
		//prepare layout map
		DATA_UNION layout;
		layout.Value = 0;

		//copy bytes
		size_t count = MIN_VALUE(sizeof(layout), numSize);
		if (FALSE != flgSwap)
		{
			//swap bytes
			for (size_t i = 0; i < count; ++i)
			{
				layout.Bytes[count - i - 1] = bufData[i];
			}
		}
		else
		{
			//copy bytes (shift if necessary)
			size_t shift = sizeof(layout) - count;
			for (size_t i = 0; i < count; ++i)
			{
				layout.Bytes[i + shift] = bufData[i];
			}
		}

		//return value
		return layout.Value;
	}

//---------------------------------------------------------------------------

	VOID CUInt16Map::StoreValue(BYTE bufData[], 
		size_t numSize, BOOL flgSwap, UINT16 numValue)
	{
		//prepare layout map
		DATA_UNION layout;
		layout.Value = numValue;

		//copy bytes
		size_t count = MIN_VALUE(sizeof(layout), numSize);
		if (FALSE != flgSwap)
		{
			//swap bytes
			for (size_t i = 0; i < count; ++i)
			{
				bufData[i] = layout.Bytes[count - i - 1];
			}
		}
		else
		{
			//copy bytes (shift if necessary)
			size_t shift = sizeof(layout) - count;
			for (size_t i = 0; i < count; ++i)
			{
				bufData[i] = layout.Bytes[i + shift];
			}
		}
	}

//---------------------------------------------------------------------------

	UINT16 CUInt16Map::FlipBytes(UINT16 numValue)
	{
		//prepare layout maps
		DATA_UNION current = {0};
		DATA_UNION swapped = {0};

		//store current value
		current.Value = numValue;

		//swap bytes during copy
		size_t count = sizeof(DATA_UNION);
		for (size_t i = 0; i < count; ++i)
		{
			swapped.Bytes[count - i - 1] = current.Bytes[i];
		}

		//return the swapped value
		return swapped.Value;
	}

//---------------------------------------------------------------------------
