//---------------------------------------------------------------------------
//
//	ParamParser.cpp
//
//	Implementation of parameters string parser class type.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "ParamParser.hpp"
#include "Debug.hpp"

//---------------------------------------------------------------------------

	const string CParamParser::ParameterSepa = ";";
	const string CParamParser::NameValueSepa = "=";
	const string CParamParser::ValueListSepa = ",";
	const string CParamParser::OpenBracket = "[";
	const string CParamParser::CloseBracket = "]";
	const string CParamParser::WhiteSpaces = TOKENIZER_WHITE_SPACES;
	const string CParamParser::QuoteChar = string(1, TOKENIZER_QUOTE_CHAR);

	//keep this list empty forever
	const TList<string>	CParamParser::EmptyValueList;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

CParamParser::CParamValue::CParamValue(VOID) : IsArray(FALSE)
{
}

//---------------------------------------------------------------------------

CParamParser::CParamValue::CParamValue(CParamValue const& refValue) : IsArray(FALSE)
{
	operator =(refValue);
}

//---------------------------------------------------------------------------

CParamParser::CParamValue::~CParamValue(VOID)
{
}

//---------------------------------------------------------------------------

CParamParser::CParamValue& CParamParser::CParamValue::operator =(CParamValue const& refValue)
{
	//copy the data
	IsArray = refValue.IsArray;
	ValueText = refValue.ValueText;
	ValueList.Copy(refValue.ValueList);
	return *this;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

	CParamParser::CParamParser(VOID) : 
		m_lstDictionary(new CStringComparer(TRUE))
	{
	}

//---------------------------------------------------------------------------

	CParamParser::CParamParser(string const& strParams) :
		m_lstDictionary(new CStringComparer(TRUE))
	{
		//parse the params string
		Parse(strParams);
	}

//---------------------------------------------------------------------------

	CParamParser::~CParamParser(VOID)
	{
	}

//---------------------------------------------------------------------------

	VOID CParamParser::Clear(VOID)
	{
		m_lstDictionary.Clear();
	}

//---------------------------------------------------------------------------

	BOOL CParamParser::Contains(string const& strName) const
	{
		return (FALSE != m_lstDictionary.Contains(strName))? TRUE : FALSE;
	}

//---------------------------------------------------------------------------

	TList<string> CParamParser::GetNames(VOID) const
	{
		return m_lstDictionary.GetKeys();
	}

//---------------------------------------------------------------------------

	BOOL CParamParser::IsArray(string const& strName) const
	{
		return m_lstDictionary[strName].IsArray;
	}

//---------------------------------------------------------------------------

	string const& CParamParser::GetValue(string const& strName) const
	{
		return m_lstDictionary[strName].ValueText;
	}

//---------------------------------------------------------------------------

	TList<string> const& CParamParser::GetValues(string const& strName) const
	{
		return m_lstDictionary[strName].ValueList;
	}

//---------------------------------------------------------------------------

	BOOL CParamParser::SetValue(string const& strName, 
		string const& strValue, BOOL flgOverwrite)
	{
		//create value structure
		CParamValue value;
		value.IsArray = FALSE;
		value.ValueText = strValue;

		//add value to the list
		return (NULL != m_lstDictionary.Add(
			strName, value, flgOverwrite))? TRUE : FALSE;
	}

//---------------------------------------------------------------------------

	BOOL CParamParser::SetValues(string const& strName, 
		TList<string> const& lstValues, BOOL flgOverwrite)
	{
		//create value structure
		CParamValue value;
		value.IsArray = TRUE;
		value.ValueList = lstValues;

		//add value to the list
		return (NULL != m_lstDictionary.Add(
			strName, value, flgOverwrite))? TRUE : FALSE;
	}

//---------------------------------------------------------------------------

	VOID CParamParser::Remove(string const& strName)
	{
		m_lstDictionary.Remove(strName);
	}

//---------------------------------------------------------------------------

	VOID CParamParser::Parse(string const& strParams)
	{
		//clear the current result
		Clear();
		
		//get the parameter data
		TList<string> params = CTokenizer::Split(strParams, ParameterSepa);
		size_t count = params.Count();

		//prepare the result
		string name;
		CParamValue data;

		//parse the results
		for (size_t i = 0; i < count; ++i)
		{
			//get rid of token's leading and trailing spaces
			string param = CTokenizer::Trim(params[i]);
			
			//clear param data
			name.clear();
			data.IsArray = FALSE;
			data.ValueText.clear();
			data.ValueList.Clear();
			
			//get name and value
			TList<string> pair = CTokenizer::Split(param, NameValueSepa);
			if (2 == pair.Count())	//name-value pair?
			{
				//trim and strip quotes
				name = CTokenizer::Strip(CTokenizer::Trim(pair[0]));
				
				//get the value string and try parsing as an array
				string text = CTokenizer::Trim(pair[1]);
				if (FALSE == ParseArray(text, data.ValueList))
				{
					//the text does not represent an array of values
					data.ValueText = CTokenizer::Strip(text);	//single value
				}
				else
				{
					//the param value is an array
					data.IsArray = TRUE;
				}
			}
			else if (1 == pair.Count())	//only name?
			{
				//trim and strip quotes
				name = CTokenizer::Strip(CTokenizer::Trim(pair[0]));
			}
			
			//add valid result to the table
			if (!name.empty())
			{
				//add result to the dictionary
				if (NULL == m_lstDictionary.Add(name, data, TRUE))
				{
					DEBUG_CHECK(FALSE);
					RELEASE_CHECK(FALSE);
				}
			}
		}
	}

//---------------------------------------------------------------------------

	BOOL CParamParser::ParseArray(string const& strValue, TList<string>& lstValues)
	{
		//trim the arg
		string text = CTokenizer::Trim(strValue);
		size_t size = text.length();

		//check if the value could be an array (value could contain both '[' and ']')
		if (2 <= size)
		{
			//check if the value is an array
			if (0 == text.find_first_of(OpenBracket) &&
				(size - 1 == text.find_last_of(CloseBracket)))
			{
				//the value is an array
				string list = text.substr(1, size - 2);
				lstValues = CTokenizer::Split(list, ValueListSepa);

				//trim the value strings and strip quotes
				size = lstValues.Count();
				for (size_t i = 0; i < size; ++i)
				{
					//trim and strip quotes
					lstValues[i] = 
						CTokenizer::Strip(CTokenizer::Trim(lstValues[i]));
				}

				//a list of values found
				return TRUE;
			}
		}
		//the value is not an array
		return FALSE;
	}

//---------------------------------------------------------------------------

	string CParamParser::Build(VOID) const
	{
		//preset the result
		string text;

		//iterate through the list of all params
		size_t count = m_lstDictionary.Count();
		for (size_t i = 0; i < count; ++i)
		{
			//fetch param info
			TKeyValue<string, CParamValue> const& entry = m_lstDictionary[i];

			//format the text string
			if (0 < i)	//add param separator?
			{
				text += ParameterSepa;
			}

			//append key and value
			text += FortifyText(entry.get_Key());
			text += NameValueSepa;
			text += FormatValue(entry.get_Value());
		}

		//return the result
		return text;
	}

//---------------------------------------------------------------------------

	string CParamParser::BuildArray(TList<string> const& lstValues) const
	{
		//iterate through the array
		string text;
		size_t size = lstValues.Count();
		for (size_t i = 0; i < size; ++i)
		{
			//is this the next value?
			if (0 < i)
			{
				//add separator
				text += ValueListSepa;
			}

			//add value string
			text += FortifyText(lstValues[i]);
		}

		//return the result
		return OpenBracket + text + CloseBracket;
	}

//---------------------------------------------------------------------------

	string CParamParser::FormatValue(CParamValue const& objValue) const
	{
		//is the value an array of strings?
		if (FALSE != objValue.IsArray)
		{
			//return the result
			return BuildArray(objValue.ValueList);
		}

		//the value is a string - return the result
		return FortifyText(objValue.ValueText);
	}

//---------------------------------------------------------------------------

	string CParamParser::FortifyText(string const& strValue) const
	{
		//does the string contain special chars?
		if ((string::npos != strValue.find(ParameterSepa)) ||
			(string::npos != strValue.find(NameValueSepa)) ||
			(string::npos != strValue.find(ValueListSepa)) ||
			(string::npos != strValue.find(OpenBracket)) ||
			(string::npos != strValue.find(CloseBracket)) ||
			(string::npos != strValue.find_first_of(WhiteSpaces)))
		{
			//decorate the string
			return CTokenizer::Decorate(strValue);
		}

		//return the string "as is"
		return strValue;
	}

//---------------------------------------------------------------------------

	CParamParser::CParamValue const& 
		CParamParser::operator [](string const& strName) const
	{
		return m_lstDictionary[strName];
	}

//---------------------------------------------------------------------------
