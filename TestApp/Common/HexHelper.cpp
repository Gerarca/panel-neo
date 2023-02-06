//---------------------------------------------------------------------------
//
//	HexHelper.hpp
//
//	String converter helper class.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "HexHelper.hpp"

//---------------------------------------------------------------------------

	const char CHexHelper::m_tblHexDigitsUpper[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};

	const char CHexHelper::m_tblHexDigitsLower[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
	};

	const string CHexHelper::m_strWhiteSpaces = " \t\r\n";

	const string CHexHelper::m_strHexDigitsUpper = "0123456789ABCDEF";
	const string CHexHelper::m_strHexDigitsLower = "0123456789abcdef";

//---------------------------------------------------------------------------

	CHexHelper::CHexHelper(VOID)
	{
	}

//---------------------------------------------------------------------------

	CHexHelper::~CHexHelper(VOID)
	{
	}

//---------------------------------------------------------------------------

	BYTE_MEMPTR CHexHelper::ToBytes(string const& strText, 
		string const& strPrefix, string const& strSuffix,
		string const& strSeparator, BOOL flgAlignLeft)
	{
		//init the result
		BYTE_MEMPTR result;

		//get strings info
		size_t text_len = strText.length();
		size_t prefix_len = strPrefix.length();
		size_t suffix_len = strSuffix.length();
		size_t sepa_len = strSeparator.length();
		size_t suffix = string::npos;

		//pre-allocate max result memory assuming 2 chars per byte
		if (FALSE == result.Create((text_len / 2) + 1))	//2 chars per byte
		{
			//cannot allocate the memory
			result.Delete();
			return result;
		}

		//convert the hex string to bytes
		size_t bytes = 0;
		for (size_t i = 0; i < text_len;)
		{
			//is separator present?
			if (0 < sepa_len)
			{
				//is it the separator?
				if (0 == strText.compare(i, sepa_len, strSeparator))
				{
					//skip the separator
					i += sepa_len;
					continue;
				}
			}

			//is it a white space?
			if (i == strText.find_first_of(m_strWhiteSpaces, i))
			{
				//skip the white space
				i += sizeof(char);
				continue;
			}

			//is prefix present?
			if (0 < prefix_len)
			{
				//look for prefix
				if (0 == strText.compare(i, prefix_len, strPrefix))
				{
					//skip the prefix
					i += prefix_len;
				}
				else
				{
					//required prefix is missing
					break;
				}
			}

			//is suffix present
			if (0 < suffix_len)
			{
				//look for suffix
				suffix = strText.find(strSuffix, i);
				if (string::npos == suffix)
				{
					//required suffix is missing
					break;
				}

				//get value bytes
				GetBytes(result, bytes, strText, i, suffix, flgAlignLeft);

				//skip the suffix (also skip any invalid chars
				//that might have been found before the suffix)
				i = suffix + suffix_len;
			}
			else //no suffix is used
			{
				//get value bytes
				GetBytes(result, bytes, strText, i, text_len, flgAlignLeft);
			}
		}

		//return the result
		result.Create(bytes);	//shrink the buffer
		return result;
	}

//---------------------------------------------------------------------------

	string CHexHelper::ToString(BYTE const* bufData, size_t numSize, 
		string const& strPrefix, string const& strSuffix,
		string const& strSeparator, BOOL flgToLower)
	{
		//init the result
		string result;
		if (NULL == bufData)
		{
			return result;
		}

		//conver all bytes to hex string
		if (FALSE == flgToLower)
		{
			//convert all the bytes to hex
			for (size_t i = 0; i < numSize; ++i)
			{
				if (0 == i)
				{
					result += strPrefix;
					result += m_tblHexDigitsUpper[(bufData[i] >> NIBBLE_BITS) & NIBBLE_MASK];
					result += m_tblHexDigitsUpper[bufData[i] & NIBBLE_MASK];
					result += strSuffix;
				}
				else
				{
					result += strSeparator;
					result += strPrefix;
					result += m_tblHexDigitsUpper[(bufData[i] >> NIBBLE_BITS) & NIBBLE_MASK];
					result += m_tblHexDigitsUpper[bufData[i] & NIBBLE_MASK];
					result += strSuffix;
				}
			}
		}
		else
		{
			//convert all the bytes to hex
			for (size_t i = 0; i < numSize; ++i)
			{
				if (0 == i)
				{
					result += strPrefix;
					result += m_tblHexDigitsLower[(bufData[i] >> NIBBLE_BITS) & NIBBLE_MASK];
					result += m_tblHexDigitsLower[bufData[i] & NIBBLE_MASK];
					result += strSuffix;
				}
				else
				{
					result += strSeparator;
					result += strPrefix;
					result += m_tblHexDigitsLower[(bufData[i] >> NIBBLE_BITS) & NIBBLE_MASK];
					result += m_tblHexDigitsLower[bufData[i] & NIBBLE_MASK];
					result += strSuffix;
				}
			}
		}

		//return the result
		return result;
	}

//---------------------------------------------------------------------------

	BYTE CHexHelper::GetValue(char c)
	{
		//check upper hex digits
		size_t index = m_strHexDigitsUpper.find_first_of(c);
		if (string::npos != index)
		{
			//the index is the value
			return index & BYTE_MASK;
		}

		//check lower hex digits
		index = m_strHexDigitsLower.find_first_of(c);
		if (string::npos != index)
		{
			//the index is the value
			return index & BYTE_MASK;
		}

		//invalid char
		return BYTE_MAX;
	}

//---------------------------------------------------------------------------

	VOID CHexHelper::GetBytes(BYTE_MEMPTR& bufBytes, size_t& numBytes, 
		string const& strText, size_t& numIndex, size_t numCount, BOOL flgAlignLeft)
	{
		//get all byte digits
		BYTE value = 0x00;
		size_t bytes = numBytes;
		size_t digit = 0;
		while (numIndex < numCount)
		{
			//get digit
			value = GetValue(strText[numIndex++]);
			if (BYTE_MAX == value)
			{
				//not a valid hex digit
				break;
			}

			//stored even number of digits?
			if (!(1 & digit))
			{
				//store new value
				bufBytes[bytes] = value;
			}
			else
			{
				//store new value
				bufBytes[bytes] = BYTE((bufBytes[bytes] << NIBBLE_BITS) & BYTE_MASK);
				bufBytes[bytes] |= value;
				++bytes;
			}

			//inclrement the number of digits
			++digit;
		}

		//stored odd number of digits?
		if (1 & digit)
		{
			//increment the bytes count to include
			//the last byte with one valid nibble
			++bytes;

			//don't trim the leading 0?
			if (FALSE == flgAlignLeft)
			{
				//The hex number contained odd number of digits.
				//Because of the algorithm used above, the last
				//byte contains the last digit in the low nibble
				//while the high nibble is invalid. That needs
				//to be corrected by shifting all higher nibbles
				//right. 
				//For example, the result of parsing of the string 
				//"0x3C5A7" should be 3 bytes: { 0x03, 0xC5, 0xA7 }.
				//The algorithm above produces 3 bytes: { 0x3C, 0x5A, 
				//0x07 } - that is incorrect and requires shifting
				//the nibbles in the top 2 bytes right.

				//shift top nibbles
				for (size_t i = bytes - 1; numBytes < i; --i)
				{
					//get lower nibble from the previous byte
					//and shift the previous byte
					value = BYTE(bufBytes[i - 1] & NIBBLE_MASK);
					bufBytes[i - 1] = BYTE(
						(bufBytes[i - 1] >> NIBBLE_BITS) & BYTE_MASK);

					//store the nibble
					bufBytes[i] &= NIBBLE_MASK;
					bufBytes[i] = BYTE(bufBytes[i] | 
						BYTE((value << NIBBLE_BITS) & BYTE_MASK));
				}
			}
			else	//the leading 0 is trimmed but the last byte must be corrected
			{
				//any bytes present?
				if (0 < bytes)
				{
					//shift the low nibble in the last byte
					bufBytes[bytes - 1] = BYTE(
						(bufBytes[bytes - 1] << NIBBLE_BITS) & BYTE_MASK);
				}
			}
		}

		//update the number of bytes
		numBytes = bytes;
	}

//---------------------------------------------------------------------------
