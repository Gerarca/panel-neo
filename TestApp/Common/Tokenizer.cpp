//---------------------------------------------------------------------------
//
//	Tokenizer.cpp
//
//	Implementation of a helper class used for splitting strings into token.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "Tokenizer.hpp"

//---------------------------------------------------------------------------

	const string CTokenizer::EmptyString = TOKENIZER_EMPTY_STRING;
	const string CTokenizer::WhiteSpaces = TOKENIZER_WHITE_SPACES;
	const string CTokenizer::NestedQuote = TOKENIZER_NESTED_QUOTE;

//---------------------------------------------------------------------------

	CTokenizer::CTokenizer(VOID)
	{
	}

//---------------------------------------------------------------------------

	CTokenizer::~CTokenizer(VOID)
	{
	}

//---------------------------------------------------------------------------

	string CTokenizer::TrimLeft(string const& strText)
	{
		size_t index = strText.find_first_not_of(WhiteSpaces);
		if (string::npos != index)
		{
			return strText.substr(index, strText.length() - index);
		}
		return strText;
	}

//---------------------------------------------------------------------------

	string CTokenizer::TrimRight(string const& strText)
	{
		size_t index = strText.find_last_not_of(WhiteSpaces);
		if (string::npos != index)
		{
			return strText.substr(0, index + 1);
		}
		return strText;
	}

//---------------------------------------------------------------------------

	string CTokenizer::Trim(string const& strText)
	{
		return TrimRight(TrimLeft(strText));
	}

//---------------------------------------------------------------------------

	string CTokenizer::Replace(string const& strText, 
		string const& strOld, string const& strNew)
	{
		//local variables
		string text;		//new text string
		size_t curr = 0;	//current index
		size_t next = 0;	//next index

		//replace all occurences of old text with the new text
		while (string::npos != (next = strText.find(strOld, curr)))
		{
			//append all chars up to the old text and then the new text
			text += strText.substr(curr, next - curr);	//skip old text
			curr = next + strOld.length();	//move the current index
			text += strNew;	//append the new text in place of the old one
		}

		//check if there is any text left
		if (curr < strText.length())
		{
			//append the rest of the text
			text += strText.substr(curr, strText.length() - curr);
		}

		//return the new text string
		return text;
	}

//---------------------------------------------------------------------------

	BOOL CTokenizer::GetToken(
		string const& strText, string const& strSeparators, 
		size_t& numIndex, string& strToken, BOOL flgIgnoreQuotes)
	{
		//prepare the result
		strToken.clear();		//init the token to an empty string

		//check if the text and separators strings are not empty
		if (!strText.empty() && !strSeparators.empty())
		{
			size_t length = strText.length();	//text length
			BOOL quoted = FALSE;		//true when inside quoted string
			char curr_c = TOKENIZER_TERMINATOR_CHAR;	//current char
			char prev_c = TOKENIZER_TERMINATOR_CHAR;	//previous char

			//skip chars specified by token-separators string
			for (; numIndex < length; ++numIndex)
			{
				//get current char
				curr_c = strText[numIndex];

				//is it the beginning of a quote?
				if ((FALSE == flgIgnoreQuotes) && (TOKENIZER_QUOTE_CHAR == curr_c))
				{
					//the quote begins here
					quoted = TRUE;
					prev_c = TOKENIZER_SKIP_CHAR;	//ignore this quote char later
					break;
				}

				//check if non-separator encountered
				if (string::npos == strSeparators.find(curr_c))
				{
					//break loop on first non-separator
					break;
				}
				else
				{
					//count the separator
					++numIndex;

					//return empty string
					strToken.clear();
					return TRUE;
				}
			}

			//start processing non-separator chars
			size_t start = numIndex;	//store starting index of the token
			size_t count = 0;			//initialize token length counter

			//count token's characters (stop at first separator encountered)
			for (; numIndex < length; ++numIndex)
			{
				//get next char
				curr_c = strText[numIndex];
				if (FALSE != quoted)	//inside the quotes?
				{
					if ((TOKENIZER_QUOTE_CHAR == curr_c) &&
						(TOKENIZER_SKIP_CHAR != prev_c))	//the end of a quote?
					{
						//end of a quote
						quoted = FALSE;
					}
				}
				else	//outside the quote
				{
					//the start of a quote?
					if ((FALSE == flgIgnoreQuotes) &&
						(TOKENIZER_QUOTE_CHAR == curr_c) && 
						(TOKENIZER_SKIP_CHAR != prev_c))
					{
						//start of a quote
						quoted = TRUE;
					}
					else
					{
						//break loop on first separator
						if (string::npos != strSeparators.find(curr_c))
						{
							//count the separator
							++numIndex;
							break;
						}
					}
				}

				//update local state
				prev_c = curr_c;	//store character
				++count;			//count this char
			}

			//forbid broken quoted strings as tokens
			if (FALSE == quoted)
			{
				//check the count of chars
				if (0 < count)
				{
					//return the token
					strToken = strText.substr(start, count);
					return TRUE;
				}
				else
				{
					//return empty string
					strToken.clear();
					return TRUE;
				}
			}
		}

		//valid token not found
		return FALSE;
	}

//---------------------------------------------------------------------------

	TList<string> CTokenizer::Split(string const& strText, 
		string const& strSeparators, BOOL flgIgnoreQuotes)
	{
		//split the text into tokens
		TList<string> tokens;
		if (!strText.empty() && !strSeparators.empty())
		{
			//keep fetching tokens
			size_t index = 0;
			size_t count = strText.length();
			string token = EmptyString;
			while (index < count)
			{
				//get next token
				if (FALSE == GetToken(strText, 
					strSeparators, index, token, flgIgnoreQuotes))
				{
					//no more tokens found
					break;	
				}

				//add token to the list
				if (NULL == tokens.Add(token))
				{
					DEBUG_CHECK(FALSE);
					RELEASE_CHECK(FALSE);
				}
			}

			//check if the string was not empty
			if (0 < index)
			{
				//check if the last char was a separator
				if (string::npos != strSeparators.find(strText[index - 1]))
				{
					//add empty token to the list because each separator
					//separates exactly two tokens - if the last token is
					//missing it must be assumed to be an empty string
					token.clear();
					if (NULL == tokens.Add(token))
					{
						DEBUG_CHECK(FALSE);
						RELEASE_CHECK(FALSE);
					}
				}
			}
		}

		//return the list of tokens
		return tokens;
	}

//---------------------------------------------------------------------------

	string CTokenizer::Strip(string const& strText)
	{
		//trim the white spaces and remove quotes
		string text = CTokenizer::Trim(strText);
		size_t size = text.length();
		if (2 <= size)
		{
			//check if the string has outer quotes
			if (0 == text.find_first_of(TOKENIZER_QUOTE_CHAR) &&
				(size - 1 == text.find_last_of(TOKENIZER_QUOTE_CHAR)))
			{
				//remove outer quotes
				text = text.substr(1, size - 2);

				//process nested quotes
				string quote = string(1, TOKENIZER_QUOTE_CHAR);
				text = Replace(text, NestedQuote, quote);
			}
		}

		//return the new text
		return text;
	}

//---------------------------------------------------------------------------

	string CTokenizer::Decorate(string const& strText)
	{
		//(do not trim the string to preserve it as-is)
		//string text = CTokenizer::Trim(strText);
		string text = strText;
		size_t size = text.length();
		if (2 <= size)
		{
			//check if the string has outer quotes
			if (0 == text.find_first_of(TOKENIZER_QUOTE_CHAR) &&
				(size - 1 == text.find_last_of(TOKENIZER_QUOTE_CHAR)))
			{
				//return the string as is
				return text;
			}
		}

		//process nested quotes
		string quote = string(1, TOKENIZER_QUOTE_CHAR);
		text = Replace(text, quote, NestedQuote);

        //add outer quotes
        text = quote + text + quote;

		//return the new text
		return text;
	}

//---------------------------------------------------------------------------

	TList<string> CTokenizer::BreakLine(string const& strLine, size_t numLength)
	{
		//break one long line into shorter ones
		TList<string> lines;

		//split the text line into pieces
        TList<string> tokens = Split(strLine, WhiteSpaces, TRUE);

		//combine lines
		string temp = EmptyString;
		size_t count = tokens.Count();
		for (size_t i = 0; i < count; ++i)
		{
			//add token to the temp string
			temp += tokens[i];
			temp += TOKENIZER_SPACE_CHAR;	//add space

			//is it time to break the line?
			if (numLength <= temp.length())
			{
				//add line and clear the temp string
				if (NULL == lines.Add(Trim(temp)))
				{
					DEBUG_CHECK(FALSE);
					RELEASE_CHECK(FALSE);
				}
				temp = EmptyString;
			}
		}

		//add the reminder (if there is a reminder)
		temp = Trim(temp);
        if (0 < temp.length())
        {
			//add the rest of the text
            if (NULL == lines.Add(temp))
			{
				DEBUG_CHECK(FALSE);
				RELEASE_CHECK(FALSE);
			}
        }

		//return teh collection of lines
		return lines;
	}

//---------------------------------------------------------------------------
