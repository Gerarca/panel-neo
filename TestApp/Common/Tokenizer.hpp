//---------------------------------------------------------------------------
//
//	Tokenizer.hpp
//
//	Implementation of a helper class used for splitting strings into token.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "TList.hpp"
#include <string>

using namespace std;

#ifndef _TOKENIZER_HPP_
#define _TOKENIZER_HPP_

//---------------------------------------------------------------------------

#define TOKENIZER_QUOTE_CHAR		'\"'	//this is always a non-separator
#define TOKENIZER_SKIP_CHAR			'\\'
#define TOKENIZER_TERMINATOR_CHAR	'\0'
#define TOKENIZER_SPACE_CHAR		' '
#define TOKENIZER_TAB_CHAR			'\t'
#define TOKENIZER_CR_CHAR			'\r'
#define TOKENIZER_LF_CHAR			'\n'

#define TOKENIZER_EMPTY_STRING		""
#define TOKENIZER_WHITE_SPACES		" \t\r\n"
#define TOKENIZER_NESTED_QUOTE		"\\\""

//---------------------------------------------------------------------------

//The purpose of this class is to provide methods for splitting strings into
//tokens using specified separators. However in some situations we want the 
//substrings of the string enclosed in quotes to be treated as one single 
//token regardless of whether these substrings contain separator characters 
//or not. The Tokenizer class allows performing a split action on input string 
//but substrings enclosed in quotes are treated as whole tokens. 
//
//For example a call:
//
//Tokenizer.Split("First token, second token, \"hi, this is third token\", ",")
//
//will produce three tokens:
//
//1) "First token"
//2) " second token"
//3) " \"hi, this is third token\""
//
//Notice that since the separator is coma (',') the space chars before 
//'second token' and '"hi, this is third token"' are treated as a parts 
//of the tokens. If necessary/required they should be later removed by
//using Strip().
//Notice that the third token contains quotes chars as well. Notice
//also the way quotes are entered in the input string by preceeding
//them with an escape char '\' - this is consistent with the way
//strings are defined in C/C++/C#.
//
//The behaviours noted above are not a "side-effects" but were introduced
//purposefully for the sake of flexibility and consistency.
//
//The Tokenizer supports nested strings. A token can contain nested
//strings surrounded by quote char ('\"') preceded by the escape char ('\\').
//For example: 
// 
//Tokenizer.Split("First token, second token, \"hi, this is third token\", ", \" this is a token with \\\"nested string\\\"!\"", ", ")
//
//will produce the tokens (notice that the space (' ') is now one of the 'spliters'):
//
//1) "First token"
//2) "second token"
//3) "\"hi, this is third token\""
//4) "\" this is a token with \\\"nested string\\\"!\""  
//
// The functions "Strip" and "Decorate" are used to manipulate quoted strings.
// 
// Tokenizer.Strip("\" this is a token with \\\"nested string\\\"!\"")
// 
// Will produce the result:
// 
// " this is a token with \"nested string\"!"
// 
// And Tokenizer.Decorate(" this is a token with \"nested string\"!")
// 
// Will producte the result:
// 
// "\" this is a token with \\\"nested string\\\"!\""
// 
class CTokenizer
{
//constants
private:
	static const string EmptyString;
	static const string WhiteSpaces;
	static const string NestedQuote;

//constructors and destructor
private:

	CTokenizer(VOID);
	~CTokenizer(VOID);

//public methods
public:

	static string TrimLeft(string const& strText);
	static string TrimRight(string const& strText);
	static string Trim(string const& strText);
	static string Replace(string const& strText,
		string const& strOld, string const& strNew);

	static BOOL GetToken(string const& strText, string const& strSeparators, 
		size_t& numIndex, string& strToken, BOOL flgIgnoreQuotes = FALSE);
	static TList<string> Split(string const& strText, 
		string const& strSeparators, BOOL flgIgnoreQuotes = FALSE);
	static string Strip(string const& strText);
	static string Decorate(string const& strText);
	static TList<string> BreakLine(string const& strLine, size_t numLength);
};

//---------------------------------------------------------------------------

#endif	//_TOKENIZER_HPP_
