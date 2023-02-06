//
//	UtfConverter.cpp
//
//	UTF converter helper implementation.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "UtfConverter.hpp"

//---------------------------------------------------------------------------

//max number of bytes used by UTF to encode a chanracter
#define UTF_CHAR_BUFSIZE	4

//NULL char code
#define UTF_NULL_CHAR_CODE		0x00

//unknown/unrecognized/unrepresentable Unicode character code
#define UTF_UNKNOWN_CHAR_CODE	0xFFFD

//byte order mark used by UTF16 to determine endianess
#define UTF16_BYTE_ORDER_MARK_BE	0xFEFF
#define UTF16_BYTE_ORDER_MARK_LE	0xFFFE

//code ranges
#define UTF8_RANGE_ONE_B	0x00000000	//0...
#define UTF8_RANGE_ONE_E	0x0000007F	//...7F

#define UTF8_RANGE_TWO_B	0x00000080	//80...
#define UTF8_RANGE_TWO_E	0x000007FF	//...7FF

#define UTF8_RANGE_THREE_B	0x00000800	//800...
#define UTF8_RANGE_THREE_E	0x0000FFFF	//...FFFF

#define UTF8_RANGE_FOUR_B	0x00010000	//10000...
#define UTF8_RANGE_FOUR_E	0x0010FFFF	//...10FFFF

#define UTF16_RANGE_ONE_B	0x00000000	//>= 0...
#define UTF16_RANGE_ONE_E	0x0000D7FF	//<= ...D7FF

#define UTF16_RANGE_TWO_B	0x0000E000	//>= E000...
#define UTF16_RANGE_TWO_E	0x0000FFFF	//<= ...FFFF

#define UTF16_RANGE_THREE_B	0x00010000	//>= 10000
#define UTF16_RANGE_THREE_E	0x0010FFFF	//<= ...10FFFF

#define UTF16_HIGH_SURROGATE_B	0x0000D800
#define UTF16_HIGH_SURROGATE_E	0x0000D8FF
#define UTF16_LOW_SURROGATE_B	0x0000DC00
#define UTF16_LOW_SURROGATE_E	0x0000DFFF

//bit masks
#define UTF8_7BITS_MASK		0x7F
#define UTF8_6BITS_MASK		0x3F
#define UTF8_5BITS_MASK		0x1F
#define UTF8_4BITS_MASK		0x0F
#define UTF8_3BITS_MASK		0x07

#define UTF16_8BITS_MASK	0xFF
#define UTF16_10BITS_MASK	0x3FF

//shift counts
#define UTF8_6BITS_SHIFT	6
#define UTF16_8BITS_SHIFT	8
#define UTF16_10BITS_SHIFT	10

//markers
#define UTF8_7BITS_MARK		0x00
#define UTF8_6BITS_MARK		0x80
#define UTF8_5BITS_MARK		0xC0
#define UTF8_4BITS_MARK		0xE0
#define UTF8_3BITS_MARK		0xF0

//---------------------------------------------------------------------------

	CUtfConverter::CUtfConverter(VOID)
	{
	}

//---------------------------------------------------------------------------

	CUtfConverter::~CUtfConverter(VOID)
	{
	}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

	size_t CUtfConverter::SizeOfUTF8(UCHAR_CODE numCode)
	{
		//determine the number of bytes to use
		if ((UTF8_RANGE_ONE_B <= numCode) && (UTF8_RANGE_ONE_E >= numCode))
		{
			//use modified UTF8 to represent 0 to avoid NULL-terminator
			//chars within strings encoded using the UTF8
			if (UTF_NULL_CHAR_CODE == numCode)
			{
				//use 2 bytes to encode the NULL char code
				return 2;
			}
			else
			{
				//use 1 byte to encode 7 bits (0bbbbbbb)
				return 1;
			}
		}
		else if ((UTF8_RANGE_TWO_B <= numCode) && (UTF8_RANGE_TWO_E >= numCode))
		{
			//use 2 bytes to encode 11 bits (110bbbbb 10bbbbbb)
			return 2;
		}
		else  if ((UTF8_RANGE_THREE_B <= numCode) && (UTF8_RANGE_THREE_E >= numCode))
		{
			//use 3 bytes to encode 16 bits (1110bbbb 10bbbbbb 10bbbbbb)
			return 3;
		}
		else if ((UTF8_RANGE_FOUR_B <= numCode) && (UTF8_RANGE_FOUR_E >= numCode))
		{
			//use 4 bytes to encode 21 bits (11110bbb 10bbbbbb 10bbbbbb 10bbbbbb)
			return 4;
		}

		//all other char codes should be treated as an unknown code

		//use 3 bytes to encode 16 bits (1110bbbb 10bbbbbb 10bbbbbb)
		return 3;
	}

//---------------------------------------------------------------------------

	BYTE_MEMPTR CUtfConverter::CharToUTF8(UCHAR_CODE numCode)
	{
		//allocate temp space
		BYTE buffer[UTF_CHAR_BUFSIZE] = {0};	//zero the content
		size_t count = 0;

		//determine the number of bytes to use
		if ((UTF8_RANGE_ONE_B <= numCode) && (UTF8_RANGE_ONE_E >= numCode))
		{
			//use modified UTF8 to represent 0 to avoid NULL-terminator
			//chars within strings encoded using the UTF8
			if (UTF_NULL_CHAR_CODE == numCode)
			{
				//use 2 bytes to encode the NULL char code
				count = 2;

				//convert the code
				buffer[1] = BYTE(UTF8_6BITS_MARK | (numCode & UTF8_6BITS_MASK));
				numCode = UCHAR_CODE(numCode >> UTF8_6BITS_SHIFT);
				buffer[0] = BYTE(UTF8_5BITS_MARK | (numCode & UTF8_5BITS_MASK));
			}
			else
			{
				//use 1 byte to encode 7 bits (0bbbbbbb)
				count = 1;

				//convert the code
				buffer[0] = BYTE(UTF8_7BITS_MARK | (numCode & UTF8_7BITS_MASK));
			}
		}
		else if ((UTF8_RANGE_TWO_B <= numCode) && (UTF8_RANGE_TWO_E >= numCode))
		{
			//use 2 bytes to encode 11 bits (110bbbbb 10bbbbbb)
			count = 2;

			//convert the code
			buffer[1] = BYTE(UTF8_6BITS_MARK | (numCode & UTF8_6BITS_MASK));
			numCode = UCHAR_CODE(numCode >> UTF8_6BITS_SHIFT);
			buffer[0] = BYTE(UTF8_5BITS_MARK | (numCode & UTF8_5BITS_MASK));
		}
		else  if ((UTF8_RANGE_THREE_B <= numCode) && (UTF8_RANGE_THREE_E >= numCode))
		{
			//use 3 bytes to encode 16 bits (1110bbbb 10bbbbbb 10bbbbbb)
			count = 3;

			//convert the code
			buffer[2] = BYTE(UTF8_6BITS_MARK | (numCode & UTF8_6BITS_MASK));
			numCode = UCHAR_CODE(numCode >> UTF8_6BITS_SHIFT);
			buffer[1] = BYTE(UTF8_6BITS_MARK | (numCode & UTF8_6BITS_MASK));
			numCode = UCHAR_CODE(numCode >> UTF8_6BITS_SHIFT);
			buffer[0] = BYTE(UTF8_4BITS_MARK | (numCode & UTF8_4BITS_MASK));
		}
		else if ((UTF8_RANGE_FOUR_B <= numCode) && (UTF8_RANGE_FOUR_E >= numCode))
		{
			//use 4 bytes to encode 21 bits (11110bbb 10bbbbbb 10bbbbbb 10bbbbbb)
			count = 4;

			//convert the code
			buffer[3] = BYTE(UTF8_6BITS_MARK | (numCode & UTF8_6BITS_MASK));
			numCode = UCHAR_CODE(numCode >> UTF8_6BITS_SHIFT);
			buffer[2] = BYTE(UTF8_6BITS_MARK | (numCode & UTF8_6BITS_MASK));
			numCode = UCHAR_CODE(numCode >> UTF8_6BITS_SHIFT);
			buffer[1] = BYTE(UTF8_6BITS_MARK | (numCode & UTF8_6BITS_MASK));
			numCode = UCHAR_CODE(numCode >> UTF8_6BITS_SHIFT);
			buffer[0] = BYTE(UTF8_3BITS_MARK | (numCode & UTF8_3BITS_MASK));
		}
		else
		{
			//all other char codes should be treated as an unknown code
			numCode = UTF_UNKNOWN_CHAR_CODE;

			//use 3 bytes to encode 16 bits (1110bbbb 10bbbbbb 10bbbbbb)
			count = 3;

			//convert the code
			buffer[2] = BYTE(UTF8_6BITS_MARK | (numCode & UTF8_6BITS_MASK));
			numCode = UCHAR_CODE(numCode >> UTF8_6BITS_SHIFT);
			buffer[1] = BYTE(UTF8_6BITS_MARK | (numCode & UTF8_6BITS_MASK));
			numCode = UCHAR_CODE(numCode >> UTF8_6BITS_SHIFT);
			buffer[0] = BYTE(UTF8_4BITS_MARK | (numCode & UTF8_4BITS_MASK));
		}

		//create and return the result
		return BYTE_MEMPTR(const_cast<BYTE const*>(buffer), count);
	}

//---------------------------------------------------------------------------

	UCHAR_CODE CUtfConverter::CharFromUTF8(
		BYTE const* bufData, size_t numSize, size_t* ptrIndex)
	{
		//sanity check
		if ((NULL != bufData) || (0 < numSize))
		{
			//fetch the first byte
			UCHAR_CODE code = 0;
			if (*ptrIndex < numSize)
			{
				//get the first byte
				BYTE byte = UCHAR_CODE(bufData[*ptrIndex]);
				if (UTF8_3BITS_MARK == (byte & ~UTF8_3BITS_MASK))	//4 bytes?
				{
					code = UCHAR_CODE(byte & UTF8_3BITS_MASK);
					if (FALSE != Add6Bits(bufData, numSize, *ptrIndex + 1, code))
					{
						if (FALSE != Add6Bits(bufData, numSize, *ptrIndex + 2, code))
						{
							if (FALSE != Add6Bits(bufData, numSize, *ptrIndex + 3, code))
							{
								//accept 4 bytes and return the code
								*ptrIndex = *ptrIndex + 4;
								return code;
							}
						}
					}
				}
				else if (UTF8_4BITS_MARK == (byte & ~UTF8_4BITS_MASK))	//3 bytes?
				{
					code = UCHAR_CODE(byte & UTF8_4BITS_MASK);
					if (FALSE != Add6Bits(bufData, numSize, *ptrIndex + 1, code))
					{
						if (FALSE != Add6Bits(bufData, numSize, *ptrIndex + 2, code))
						{
							//accept 3 bytes and return the code
							*ptrIndex = *ptrIndex + 3;
							return code;
						}
					}
				}
				else if (UTF8_5BITS_MARK == (byte & ~UTF8_5BITS_MASK))	//2 bytes?
				{
					code = UCHAR_CODE(byte & UTF8_5BITS_MASK);
					if (FALSE != Add6Bits(bufData, numSize, *ptrIndex + 1, code))
					{
						//accept 2 bytes and return the code
						*ptrIndex = *ptrIndex + 2;
						return code;
					}
				}
				else if (UTF8_6BITS_MARK != (byte & ~UTF8_7BITS_MASK))	//1 byte?
				{
					//valid UTF8 encoding should have MSb 0!
					code = UCHAR_CODE(byte & UTF8_7BITS_MASK);

					//accept 1 byte and return the code
					*ptrIndex = *ptrIndex + 1;
					return code;
				}

				//invalid UTF8 encoding encountered
				//skip one byte (to allow to re-syncing)
				*ptrIndex = *ptrIndex + 1;
			}
		}

		//the char code is unknown
		return UTF_UNKNOWN_CHAR_CODE;
	}

//---------------------------------------------------------------------------

	size_t CUtfConverter::SizeOfUTF16(UCHAR_CODE numCode)
	{
		//determine the number of bytes to use
		if (((UTF16_RANGE_ONE_B <= numCode) && (UTF16_RANGE_ONE_E >= numCode)) ||
			((UTF16_RANGE_TWO_B <= numCode) && (UTF16_RANGE_TWO_E >= numCode)))	//2 bytes?
		{
			//unlike UTF-8, the UTF-16 does not handle 
			//the UTF_NULL_CHAR_CODE in any special way!

			//use 2 bytes to encode 16 bits
			return 2;
		}
		else if ((UTF16_RANGE_THREE_B <= numCode) && (UTF16_RANGE_THREE_E >= numCode))
		{
			//use 4 bytes to encode two 16-bits surrogates
			return 4;
		}

		//all other char codes should be treated as an unknown code

		//use 2 bytes to encode 16 bits
		return 2;
	}

//---------------------------------------------------------------------------

	BYTE_MEMPTR CUtfConverter::CharToUTF16(UCHAR_CODE numCode, BOOL flgLittleEndian)
	{
		//allocate temp space
		BYTE buffer[UTF_CHAR_BUFSIZE];
		size_t count = 0;

		//determine the number of bytes to use
		if (((UTF16_RANGE_ONE_B <= numCode) && (UTF16_RANGE_ONE_E >= numCode)) ||
			((UTF16_RANGE_TWO_B <= numCode) && (UTF16_RANGE_TWO_E >= numCode)))	//2 bytes?
		{
			//unlike UTF-8, the UTF-16 does not handle 
			//the UTF_NULL_CHAR_CODE in any special way!

			//use 2 bytes to encode 16 bits
			count = 2;

			//store the value
			Store2Bytes(buffer, numCode, flgLittleEndian);
		}
		else if ((UTF16_RANGE_THREE_B <= numCode) && (UTF16_RANGE_THREE_E >= numCode))
		{
			//use 4 bytes to encode two 16-bits surrogates
			count = 4;

			//adjust the code value (result 0...FFFFF)
			numCode = UCHAR_CODE(numCode - UTF16_RANGE_THREE_B);

			//calculate the high and low surrogates
			UCHAR_CODE high = UCHAR_CODE(UTF16_HIGH_SURROGATE_B + 
				((numCode >> UTF16_10BITS_SHIFT) & UTF16_10BITS_MASK));
			UCHAR_CODE low = UCHAR_CODE(UTF16_LOW_SURROGATE_B + 
				(numCode & UTF16_10BITS_MASK));

			//store the value
			Store2Bytes(&buffer[0], high, flgLittleEndian);

			//store the value
			Store2Bytes(&buffer[2], low, flgLittleEndian);
		}
		else
		{
			//all other char codes should be treated as an unknown code
			numCode = UTF_UNKNOWN_CHAR_CODE;

			//use 2 bytes to encode 16 bits
			count = 2;

			//store the value
			Store2Bytes(buffer, numCode, flgLittleEndian);
		}

		//create and return the result
		return BYTE_MEMPTR(const_cast<BYTE const*>(buffer), count);
	}

//---------------------------------------------------------------------------

	UCHAR_CODE CUtfConverter::CharFromUTF16(
		BYTE const* bufData, size_t numSize, size_t* ptrIndex, BOOL flgLittleEndian)
	{
		//sanity check
		if ((NULL != bufData) || (0 < numSize))
		{
			//fetch the first 2 bytes
			UCHAR_CODE code = 0;
			if (FALSE != Load2Bytes(bufData, numSize, *ptrIndex, flgLittleEndian, code))
			{
				//check the ranges
				if (((UTF16_RANGE_ONE_B <= code) && (UTF16_RANGE_ONE_E >= code)) ||
					((UTF16_RANGE_TWO_B <= code) && (UTF16_RANGE_TWO_E >= code)))
				{
					//accept 2 bytes and return the code
					*ptrIndex = *ptrIndex + 2;	//2 bytes per char
					return code;
				}
				else if ((UTF16_HIGH_SURROGATE_B <= code) && (UTF16_HIGH_SURROGATE_E >= code))
				{
					//the high surrogate found
					UCHAR_CODE high = UCHAR_CODE(code - UTF16_HIGH_SURROGATE_B);
					high = UCHAR_CODE(high << UTF16_10BITS_SHIFT);

					//look for the low surrogate
					if (FALSE != Load2Bytes(bufData, numSize, *ptrIndex + 2, flgLittleEndian, code))
					{
						if ((UTF16_LOW_SURROGATE_B <= code) && (UTF16_LOW_SURROGATE_E >= code))
						{
							//the low surrogate found
							UCHAR_CODE low = UCHAR_CODE(code - UTF16_LOW_SURROGATE_B);
							low = UCHAR_CODE(low & UTF16_10BITS_MASK);

							//combine the result
							code = UCHAR_CODE(UTF16_RANGE_THREE_B + (high | low));

							//accept 4 bytes and return the result
							*ptrIndex = *ptrIndex + 4;	//4 bytes per char
							return code;
						}
					}
				}
			}

			//invalid UTF16 encoding encountered
			//skip two bytes (to allow to re-syncing)
			*ptrIndex = *ptrIndex + 2;
		}

		//the char code is unknown
		return UTF_UNKNOWN_CHAR_CODE;
	}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

	//the purpose of this function is re-encoding the UTF8 string into 
	//another UTF8 string to preserve (re-encode) any potential '\0' 
	//terminator chars that may be present in the original string
	BOOL CUtfConverter::StringToUTF8(
		string const& strText, BYTE_MEMPTR& refData)
	{
		//no data present
		refData.Delete();

		//get text info
		BYTE const* pdata = reinterpret_cast<BYTE const*>(strText.c_str());
		size_t count = strText.size();

		//calculate the size of the required buffer
		size_t size = 0;

		//check the sizes of all other codes
		size_t index = 0;
		while (index < count)
		{
			//get the char code
			UCHAR_CODE code = 
				CUtfConverter::CharFromUTF8(pdata, count, &index);

			//update the size
			size +=	CUtfConverter::SizeOfUTF8(code);
		}

		//allocate the output buffer
		size_t used = 0;	//no space used yet
		if (FALSE == refData.Create(size))
		{
			//failed to allocate required buffer
			return FALSE;
		}

		//fetch all the char codes from the multi-byte string
		index = 0;
		while (index < count)
		{
			//error check
			if (used >= size)
			{
				//ther is not enough space left
				//(possible space calculation issue)
				return FALSE;
			}

			//get the char code
			UCHAR_CODE code = 
				CUtfConverter::CharFromUTF8(pdata, count, &index);

			//encode the code with UTF8
			BYTE_MEMPTR data = CUtfConverter::CharToUTF8(code);
			if (FALSE != data.IsNull())
			{
				//couldn't allocate the memory
				return FALSE;
			}

			//copy the data
			memcpy(&refData[used], data, data.Count());
			used += data.Count();
		}

		//success
		return TRUE;
	}

//---------------------------------------------------------------------------

	//the purpose of this function is re-encoding the UTF8 string into 
	//another UTF8 string to preserve (re-encode) any potential '\0' 
	//terminator chars that may be present in the original string
	BOOL CUtfConverter::StringFromUTF8(
		BYTE const* bufData, size_t numSize, string& strText)
	{
		//data present?
		strText.clear();	//no text present
		if ((NULL != bufData) && (0 < numSize))
		{
			size_t index = 0;
			while (index < numSize)
			{
				//get next char code
				UCHAR_CODE code = 
					CUtfConverter::CharFromUTF8(bufData, numSize, &index);

				//convert the char code to UTF8
				BYTE_MEMPTR temp = CUtfConverter::CharToUTF8(code);
				if (FALSE == temp.IsNull())	//data present?
				{
					//add bytes to the result
					strText.append(reinterpret_cast<char const*>(
						static_cast<BYTE const*>(temp)), temp.Count());
				}
			}

			//check if there was any data present
			if (0 < strText.size())
			{
				//at least some chars were present
				return TRUE;
			}
		}
		//failure
		return FALSE;
	}

//---------------------------------------------------------------------------

	BOOL CUtfConverter::StringToUTF16(string const& strText, 
		BOOL flgLittleEndian, BOOL flgAddByteOrderMark, BYTE_MEMPTR& refData)
	{
		//no data present
		refData.Delete();

		//get text info
		BYTE const* pdata = reinterpret_cast<BYTE const*>(strText.c_str());
		size_t count = strText.size();

		//calculate the size of the required buffer
		size_t size = (FALSE != flgAddByteOrderMark)? 
			CUtfConverter::SizeOfUTF16(UTF16_BYTE_ORDER_MARK_BE) : 0;

		//check the sizes of all other codes
		size_t index = 0;
		while (index < count)
		{
			//get the char code
			UCHAR_CODE code = 
				CUtfConverter::CharFromUTF8(pdata, count, &index);

			//update the size
			size +=	CUtfConverter::SizeOfUTF16(code);
		}

		//allocate the output buffer
		size_t used = 0;	//no space used yet
		if (FALSE == refData.Create(size))
		{
			//failed to allocate required buffer
			return FALSE;
		}

		//add the byte order mark?
		if (FALSE != flgAddByteOrderMark)
		{
			//get the bytes of the byte order mark
			BYTE_MEMPTR data = CUtfConverter::CharToUTF16(
				UTF16_BYTE_ORDER_MARK_BE, flgLittleEndian);
			if (FALSE != data.IsNull())
			{
				//couldn't allocate the memory
				return FALSE;
			}

			//copy the data
			memcpy(&refData[used], data, data.Count());
			used += data.Count();
		}

		//fetch all the char codes from the multi-byte string
		index = 0;
		while (index < count)
		{
			//error check
			if (used >= size)
			{
				//ther is not enough space left
				//(possible space calculation issue)
				return FALSE;
			}

			//get the char code
			UCHAR_CODE code = 
				CUtfConverter::CharFromUTF8(pdata, count, &index);

			//encode the code with UTF16
			BYTE_MEMPTR data = 
				CUtfConverter::CharToUTF16(code, flgLittleEndian);
			if (FALSE != data.IsNull())
			{
				//couldn't allocate the memory
				return FALSE;
			}

			//copy the data
			memcpy(&refData[used], data, data.Count());
			used += data.Count();
		}

		//success
		return TRUE;
	}

//---------------------------------------------------------------------------

	BOOL CUtfConverter::StringFromUTF16(BYTE const* bufData, 
		size_t numSize, string& strText)
	{
		//data present?
		strText.clear();	//no text present
		if ((NULL != bufData) && (0 < numSize))
		{
			//get the first char code to determine the byte order
			size_t index = 0;
			UCHAR_CODE code = CUtfConverter::CharFromUTF16(
				bufData, numSize, &index, FALSE);
			if (UTF16_BYTE_ORDER_MARK_BE == code)
			{
				//skip the byte order mark and use big endian
				return StringFromUTF16(
					&bufData[index], numSize - index, FALSE, strText);
			}
			else if (UTF16_BYTE_ORDER_MARK_LE == code)
			{
				//skip the byte order mark and use little endian
				return StringFromUTF16(
					&bufData[index], numSize - index, TRUE, strText);
			}
		}
		//failure - unknown byte order
		return FALSE;
	}

//---------------------------------------------------------------------------

	BOOL CUtfConverter::StringFromUTF16(BYTE const* bufData, 
		size_t numSize, BOOL flgLittleEndian, string& strText)
	{
		//data present?
		strText.clear();	//no text present
		if ((NULL != bufData) && (0 < numSize))
		{
			size_t index = 0;
			while (index < numSize)
			{
				//get next char code
				UCHAR_CODE code = CUtfConverter::CharFromUTF16(
					bufData, numSize, &index, flgLittleEndian);

				//convert the char code to UTF8
				BYTE_MEMPTR temp = CUtfConverter::CharToUTF8(code);
				if (FALSE == temp.IsNull())	//data present?
				{
					//add bytes to the result
					strText.append(reinterpret_cast<char const*>(
						static_cast<BYTE const*>(temp)), temp.Count());
				}
			}

			//check if there was any data present
			if (0 < strText.size())
			{
				//at least some chars were present
				return TRUE;
			}
		}
		//failure
		return FALSE;
	}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

	BOOL CUtfConverter::Add6Bits(BYTE const* bufData, 
		size_t numSize, size_t numIndex, UCHAR_CODE& numCode)
	{
		//validate index
		if (numIndex < numSize)
		{
			//check if 6bits marker is present
			BYTE byte = bufData[numIndex];
			if (UTF8_6BITS_MARK == (byte & ~UTF8_6BITS_MASK))
			{
				//add 6 bits
				numCode = UCHAR_CODE(numCode << UTF8_6BITS_SHIFT);
				numCode = UCHAR_CODE(numCode | (byte & UTF8_6BITS_MASK));
				return TRUE;
			}
		}
		//failure
		return FALSE;
	}

//---------------------------------------------------------------------------

	VOID CUtfConverter::Store2Bytes(
		BYTE* bufData, UCHAR_CODE numValue, BOOL flgLittleEndian)
	{
		//store bytes using 'big endian' convention?
		if (FALSE == flgLittleEndian)
		{
			//store MSB first
			bufData[0] = BYTE((numValue >> UTF16_8BITS_SHIFT) & UTF16_8BITS_MASK);
			bufData[1] = BYTE(numValue & UTF16_8BITS_MASK);
		}
		else
		{
			//store LSB first
			bufData[0] = BYTE(numValue & UTF16_8BITS_MASK);
			bufData[1] = BYTE((numValue >> UTF16_8BITS_SHIFT) & UTF16_8BITS_MASK);
		}
	}

//---------------------------------------------------------------------------

	BOOL CUtfConverter::Load2Bytes(BYTE const* bufData, size_t numSize, 
		size_t numIndex, BOOL flgLittleEndian, UCHAR_CODE& numCode)
	{
		//are at least 2 bytes available?
		if ((numIndex + 1) < numSize)
		{
			//load bytes using 'big endian' convention?
			if (FALSE == flgLittleEndian)
			{
				//load MSB first
				numCode = UCHAR_CODE(bufData[numIndex + 0]);
				numCode = UCHAR_CODE(numCode << UTF16_8BITS_SHIFT);
				numCode = UCHAR_CODE(numCode | bufData[numIndex + 1]);
			}
			else
			{
				//load LSB first
				numCode = UCHAR_CODE(bufData[numIndex + 1]);
				numCode = UCHAR_CODE(numCode << UTF16_8BITS_SHIFT);
				numCode = UCHAR_CODE(numCode | bufData[numIndex + 0]);
			}

			//success
			return TRUE;
		}

		//failure
		return FALSE;
	}

//---------------------------------------------------------------------------
