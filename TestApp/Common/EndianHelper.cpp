//---------------------------------------------------------------------------
//
//	EndianHelper.cpp
//
//	Helper class for dealing with machine 'endianness'.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "EndianHelper.hpp"

//---------------------------------------------------------------------------

#define DATA_MSB	0x12
#define DATA_LSB	0x34
#define DATA_NUM	0x1234

//---------------------------------------------------------------------------

	CEndianHelper::CEndianHelper(VOID)
	{
	}

//---------------------------------------------------------------------------

	CEndianHelper::~CEndianHelper(VOID)
	{
	}


//---------------------------------------------------------------------------

	BOOL CEndianHelper::IsBigEndian(VOID)
	{
		DATA_UNION data;
		data.Short = DATA_NUM;
		return (DATA_MSB == data.Bytes[0])? TRUE :FALSE;
	}

//---------------------------------------------------------------------------

	BOOL CEndianHelper::IsLittleEndian(VOID)
	{
		DATA_UNION data;
		data.Short = DATA_NUM;
		return (DATA_LSB == data.Bytes[0])? TRUE :FALSE;
	}

//---------------------------------------------------------------------------
