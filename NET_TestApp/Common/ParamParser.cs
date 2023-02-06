using System;
using System.Collections.Generic;

namespace DSC.Automation.TextHelpers
{
    /// <summary>
    /// The purpose of this class is providing a tool for parsing
    /// strings containing parameters/arguments in special format.
    /// The format is: "Parameter_Name=Parameter_Value;".
    /// 
    /// The <Parameter_Name> must be one word or multiple words and/or
    /// special chars enclosed by quotes ("..."). The text enclosed
    /// in quotes may include special characters but not quote chars.
    /// 
    /// The <Parameter_Value> may be one word, multiple words enclosed 
    /// by quotes ("..."), or an <Array_Of_Values>. The text enclosed
    /// in quotes may include special characters but not quote chars.
    /// 
    /// The <Array_Of_Values> consists of a list of <List_Value> enclosed
    /// by brackets ([...]) and separated by the coma char ",".
    /// 
    /// The <List_Value> may be one word, multiple words enclosed 
    /// by quotes ("..."). The text enclosed in quotes may include 
    /// special characters but not quote chars. The <List_Value>
    /// must not be another <Array_Of_Values> - the array value nesting 
    /// is _NOT_ supported by the current implementation of the parser.
    /// 
    /// The special characters mentioned above that may be used within
    /// quoted name or value strings are: ";", "=", "[", "]", ",".
    /// Nested quotes are not supported by the parser and are not allowed
    /// anywhere in the text string to be parsed.
    /// </summary>
    public class ParamParser : MarshalByRefObject
    {
        #region Constants
        private const string _cstrParamSepa = ";";   //separates name/value pairs
        private const string _cstrNameValueSepa = "=";
        private const string _cstrValueListSepa = ",";
        private const string _cstrOpenBracket = "[";
        private const string _cstrCloseBracket = "]";
        private const string _cstrWordSepa = " \t\n";
        private const string _cstrQuoteChar = "\"";
        #endregion Constants

        #region Private Members
        private Dictionary<string, object> _lstParams =
            new Dictionary<string, object>(StringComparer.OrdinalIgnoreCase);
        #endregion Private Members

        #region Properties
        public object this[string strName]
        {
            get
            {
                if (_lstParams.ContainsKey(strName))
                {
                    return _lstParams[strName];
                }
                return String.Empty;
            }
            set
            {
                if (_lstParams.ContainsKey(strName))
                {
                    //try casting value
                    string[] tblValues = value as string[];
                    string strValue = value as string;

                    //setup new value
                    if (tblValues != null)
                    {
                        _lstParams[strName] = tblValues;
                    }
                    else if (strValue != null)
                    {
                        _lstParams[strName] = strValue;
                    }
                    else
                    {
                        //set the default value
                        _lstParams[strName] = String.Empty;
                    }
                }
            }
        }
        #endregion Properties

        #region Public Methods
        public ParamParser()
        {
        }

        public override object InitializeLifetimeService()
        {
            return null;
        }

        public void Clear()
        {
            _lstParams.Clear();
        }

        public bool Contains(string strName)
        {
            return _lstParams.ContainsKey(strName);
        }

        public string[] GetNames()
        {
            List<string> lstNames = new List<string>();
            foreach (string strName in _lstParams.Keys)
            {
                lstNames.Add(strName);
            }
            return lstNames.ToArray();
        }

        public string GetValue(string strName)
        {
            if (_lstParams.ContainsKey(strName))
            {
                //return the result
                string strValue = _lstParams[strName] as string;
                if (strValue != null)
                {
                    //return the string value
                    return strValue;
                }
            }
            //return default result
            return String.Empty;
        }

        public string[] GetValues(string strName)
        {
            if (_lstParams.ContainsKey(strName))
            {
                string[] tblValues = _lstParams[strName] as string[];
                if (tblValues != null)
                {
                    //return the array of values
                    return tblValues;
                }
            }
            //return default result
            return new string[0];
        }

        //add or update if exists
        public void SetValue(string strName, string strValue)
        {
            if (_lstParams.ContainsKey(strName))
            {
                //update existing value
                _lstParams[strName] = (strValue != null) ? strValue : String.Empty;
            }
            else
            {
                //add new value
                _lstParams.Add(strName, (strValue != null) ? strValue : String.Empty);
            }
        }

        //add or update if exists
        public void SetValues(string strName, string[] tblValues)
        {
            if (_lstParams.ContainsKey(strName))
            {
                //update existing value
                _lstParams[strName] = (tblValues != null) ? tblValues : new string[0];
            }
            else
            {
                //add new value
                _lstParams.Add(strName, (tblValues != null) ? tblValues : new string[0]);
            }
        }

        //add or error if exists
        public bool AddValue(string strName, string strValue)
        {
            if (!_lstParams.ContainsKey(strName))
            {
                _lstParams.Add(strName, strValue);
                return true;
            }
            return false;
        }

        //add or error if exists
        public bool AddValues(string strName, string[] tblValues)
        {
            if (!_lstParams.ContainsKey(strName))
            {
                _lstParams.Add(strName, tblValues);
                return true;
            }
            return false;
        }

        public void Remove(string strName)
        {
            if (_lstParams.ContainsKey(strName))
            {
                _lstParams.Remove(strName);
            }
        }

        public void Parse(string strParams)
        {
            //clear the current result
            Clear();

            if (strParams != null)
            {
                //get the parameter data
                string[] tblParams = Tokenizer.Split(strParams, _cstrParamSepa);

                //parse the results
                for (int i = 0; i < tblParams.Length; ++i)
                {
                    //get rid of token's leading and trailing spaces
                    string strParam = tblParams[i].Trim();

                    //prepare the result
                    string strName = String.Empty;
                    string strValue = String.Empty; //string representation of the value
                    object objValue = null;

                    //get name and value
                    string[] tblNameValue =
                        Tokenizer.Split(strParam, _cstrNameValueSepa);
                    if (tblNameValue.Length == 2)   //pair name-value
                    {
                        //trim and strip quotes
                        strName = Tokenizer.Strip(tblNameValue[0].Trim());

                        //set the value - by default, it is the same as its string representation
                        strValue = tblNameValue[1].Trim();
                        objValue = Tokenizer.Strip(strValue);

                        //check if the value could be an array
                        string[] tblValues = ParseArray(strValue);
                        if (tblValues != null)
                        {
                            //store array as the value
                            objValue = tblValues;
                        }
                    }
                    else if (tblNameValue.Length == 1)	//only name
                    {
                        //trim and strip quotes
                        strName = Tokenizer.Strip(tblNameValue[0].Trim());
                        objValue = String.Empty;    //the value is a blank string
                    }

                    //add valid result to the table
                    if (strName != String.Empty)
                    {
                        //add result to the dictionary
                        if (!_lstParams.ContainsKey(strName))
                        {
                            //add new value
                            _lstParams.Add(strName, objValue);
                        }
                        else
                        {
                            //update existing value
                            _lstParams[strName] = objValue;
                        }
                    }
                }
            }
        }

        public string[] ParseArray(string strValue)
        {
            //trim the arg
            strValue = strValue.Trim();

            //check if the value could be an array
            if (strValue.Length >= 2)
            {
                //check if the value is an array
                if ((strValue.IndexOf(_cstrOpenBracket) == 0) &&
                    (strValue.LastIndexOf(_cstrCloseBracket) == strValue.Length - 1))
                {
                    //the value is an array
                    string strList = strValue.Substring(1, strValue.Length - 2);
                    string[] tblValues = Tokenizer.Split(strList, _cstrValueListSepa);
                    for (int v = 0; v < tblValues.Length; ++v)
                    {
                        //trim and strip quotes
                        tblValues[v] = Tokenizer.Strip(tblValues[v].Trim());
                    }

                    //return the array
                    return tblValues;
                }
            }

            //the value is not an array
            return null;
        }

        public string BuildArray(string[] tblValues)
        {
            //iterate through the array
            string strValues = String.Empty;
            for (int i = 0; i < tblValues.Length; ++i)
            {
                if (i == 0)
                {
                    strValues = FortifyText(tblValues[i]);
                }
                else
                {
                    strValues = strValues + _cstrValueListSepa +
                        FortifyText(tblValues[i]);
                }
            }

            //return the result
            return _cstrOpenBracket + strValues + _cstrCloseBracket;
        }

        public override string ToString()
        {
            //preset the result
            string strResult = String.Empty;

            //iterate through the list of all params
            bool flgFirst = true;
            foreach (KeyValuePair<string, object> clsParam in _lstParams)
            {
                if (flgFirst)
                {
                    //first param
                    flgFirst = false;
                    strResult = strResult +
                        FormatText(clsParam.Key) + _cstrNameValueSepa + FormatText(clsParam.Value);
                }
                else
                {
                    //next param (add param separator)
                    strResult = strResult + _cstrParamSepa +
                        FormatText(clsParam.Key) + _cstrNameValueSepa + FormatText(clsParam.Value);
                }
            }
            return strResult;
        }
        #endregion Public Methods

        #region Private Methods
        private string FormatText(object objValue)
        {
            //is the value an array of strings?
            if (objValue is string[])
            {
                //return the result
                return BuildArray(objValue as string[]);
            }
            else if (objValue is string)    //is the value a string?
            {
                //return the result
                return FortifyText(objValue as string);
            }

            //no valid value given
            return String.Empty;
        }

        private string FortifyText(string strValue)
        {
            //does the string contain special chars?
            if ((strValue.IndexOf(_cstrParamSepa) >= 0) ||
                (strValue.IndexOf(_cstrNameValueSepa) >= 0) ||
                (strValue.IndexOf(_cstrValueListSepa) >= 0) ||
                (strValue.IndexOf(_cstrOpenBracket) >= 0) ||
                (strValue.IndexOf(_cstrCloseBracket) >= 0) ||
                (strValue.IndexOfAny(_cstrWordSepa.ToCharArray()) >= 0))
            {
                //is the string longer than 2 chars?
                if (strValue.Length > 2)
                {
                    //is the string in quotes already?
                    if ((strValue.IndexOf(_cstrQuoteChar) == 0) &&
                        (strValue.LastIndexOf(_cstrQuoteChar) == strValue.Length - 1))
                    {
                        //the string is in quotes so there is no need to do anything
                    }
                    else
                    {
                        //add quotes to the string
                        strValue = _cstrQuoteChar + strValue + _cstrQuoteChar;
                    }
                }
                else
                {
                    //add quotes to the string
                    strValue = _cstrQuoteChar + strValue + _cstrQuoteChar;
                }
            }

            //return the string "as is"
            return strValue;
        }
        #endregion Private Methods
    }
}
