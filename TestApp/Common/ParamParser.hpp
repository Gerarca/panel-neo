//---------------------------------------------------------------------------
//
//	ParamParser.hpp
//
//	Implementation of parameters string parser class type.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "Tokenizer.hpp"
#include "TDictionary.hpp"
#include "StringComparer.hpp"

#ifndef _PARAMPARSER_HPP_
#define _PARAMPARSER_HPP_

//---------------------------------------------------------------------------

#define PARAM_PARSER_LIST_GRAIN		8

//---------------------------------------------------------------------------

//The purpose of this class is providing a tool for parsing
//strings containing parameters/arguments in special format.
//The format is: "Parameter_Name=Parameter_Value;".
//
//The <Parameter_Name> must be one word or multiple words and/or
//special chars enclosed by quotes ("..."). The text enclosed
//in quotes may include special characters but not quote chars.
//
//The <Parameter_Value> may be one word, multiple words enclosed 
//by quotes ("..."), or an <Array_Of_Values>. The text enclosed
//in quotes may include special characters but not quote chars.
//
//The <Array_Of_Values> consists of a list of <List_Value> enclosed
//by brackets ([...]) and separated by the coma char ",".
//
//The <List_Value> may be one word, multiple words enclosed 
//by quotes ("..."). The text enclosed in quotes may include 
//special characters but not quote chars. The <List_Value>
//must not be another <Array_Of_Values> - the array value nesting 
//is _NOT_ supported by the current implementation of the parser.
//
//The special characters mentioned above that may be used within
//quoted name or value strings are: ";", "=", "[", "]", ",".
//Nested quotes are not supported by the parser and are not allowed
//anywhere in the text string to be parsed.
class CParamParser
{
//constants
private:
	static const string ParameterSepa;	//separates name/value pairs
	static const string NameValueSepa;	//saparates name and value
	static const string ValueListSepa;	//separates values within the list
	static const string OpenBracket;	//value list start
	static const string CloseBracket;	//value list end
	static const string WhiteSpaces;
	static const string QuoteChar;

	static const TList<string>	EmptyValueList;	//empty list of values

	class CParamValue {
		public:
			BOOL			IsArray;	//TRUE if the param value is an array
			string			ValueText;	//single value text string
			TList<string>	ValueList;	//multiple values list

			CParamValue(VOID);			//constructor
			CParamValue(CParamValue const& refValue);	//copy constructor
			virtual ~CParamValue(VOID);	//destructor

			CParamValue& operator =(CParamValue const& refValue);
	};

//private members
private:

	//the dictionary uses string comparer to perform
	//case-insensitive comparison of the string keys
	TDictionary<string, CParamValue>	m_lstDictionary;

//constructor & destructor
public:
	CParamParser(VOID);
	CParamParser(string const& strParams);
	virtual ~CParamParser(VOID);

//public methods
public:

	VOID Clear(VOID);						//clear the dictionary
	BOOL Contains(string const& strName) const;	//check if the dictionary contains param
	TList<string> GetNames(VOID) const;		//get all param names

	BOOL IsArray(string const& strName) const;	//check if the value is an array

	string const& GetValue(string const& strName) const;
	TList<string> const& GetValues(string const& strName) const;
	BOOL SetValue(string const& strName, 
		string const& strValue, BOOL flgOverwrite = FALSE);
	BOOL SetValues(string const& strName, 
		TList<string> const& lstValues, BOOL flgOverwrite);

	VOID Remove(string const& strName);

	VOID Parse(string const& strParams);
	BOOL ParseArray(string const& strValue, TList<string>& lstValues);

	string Build(VOID) const;
	string BuildArray(TList<string> const& lstValues) const;

//operators
public:

	CParamValue const& operator [](string const& strName) const;

//private methods
private:

	string FormatValue(CParamValue const& objValue) const;
	string FortifyText(string const& strValue) const;
};

//---------------------------------------------------------------------------

#endif	//_PARAMPARSER_HPP_
