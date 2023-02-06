using System;
using System.Collections;

namespace DSC.Automation.TextHelpers
{
    /// <summary>
    ///The purpose of this class is to provide alternative to the Split() method
    ///of the String class. That method simply splits string into tokens using
    ///specified separators. However in some situations we want the substrings of
    ///the string enclosed in quotas to be treated as one single token regardless
    ///of whether these substrings contain separator characters or not.
    ///The Tokenizer class allows performing a split action on input string but
    ///substrings enclosed in quotas are treated as whole tokens. For example a call:
    ///
    ///Tokenizer.Split("First token, second token, \"hi, this is third token\", ",")
    ///
    ///will produce three tokens:
    ///
    ///1) First token
    ///2)  second token
    ///3)  "hi, this is third token"
    ///
    ///Notice that since the separator is coma (',') the space chars before 
    ///'second token' and '"hi, this is third token"' are treated as a parts 
    ///of the tokens. If necessary/required they should be later removed by
    ///using Strip().
    ///Notice that the third token contains quotas chars as well. Notice
    ///also the way quotas are entered in the input string by preceeding
    ///them with an escape char '\' - this is consistent with the way
    ///strings are defined in C/C++/C#.
    ///
    ///The behaviours noted above are not a "side-effects" but were introduced
    ///purposefully for the sake of flexibility and consistency.
    /// </summary>
    public class Tokenizer
    {
        private Tokenizer() { }	//do not allow instantinating

        public static string GetToken(string strText, string strSeparators, ref int nIndex)
        {
            const char charQuote = '\"';	//this is always a non-separator
            const char charSkip = '\\';

            if ((strText != null) && (strSeparators != null) && (nIndex >= 0))
            {
                int nLength = strText.Length;
                bool boolQuoted = false;		//true when inside quoted string
                char charCurr = '\0';			//current char
                char charPrev = '\0';			//previous char

                //skip chars specified by token-separators string
                for (; nIndex < nLength; ++nIndex)
                {
                    charCurr = strText[nIndex];	//retrieve current char
                    if (charCurr == charQuote)	//the beginning of a quote
                    {
                        boolQuoted = true;
                        charPrev = charSkip;	//ignore this quote char later
                        break;
                    }
                    if (strSeparators.IndexOf(charCurr) < 0) break;	//break loop on first non-separator
                }

                int nStart = nIndex;	//store starting index of the token
                int nCount = 0;			//initialize token length counter

                //count token's characters (stop at first separator encountered)
                for (; nIndex < nLength; ++nIndex)
                {
                    charCurr = strText[nIndex];	//retrieve current char

                    if (boolQuoted)		//inside the quotes?
                    {
                        if ((charCurr == charQuote) &&
                            (charPrev != charSkip))	//the end of a quote?
                        {
                            boolQuoted = false;
                        }
                    }
                    else	//outside the quote
                    {
                        if ((charCurr == charQuote) &&
                            (charPrev != charSkip))	//the start of a quote?
                        {
                            boolQuoted = true;
                        }
                        else
                        {
                            //break loop on first separator
                            if (strSeparators.IndexOf(charCurr) >= 0) break;
                        }
                    }

                    charPrev = charCurr;	//store character
                    ++nCount;				//count this char
                }

                //retrieve the token and store it in memory
                if ((nCount > 0) && !boolQuoted)	//forbid broken quoted strings as tokens
                {
                    return strText.Substring(nStart, nCount);	//return substring
                }
            }
            return null;
        }

        public static string[] Split(string strText, string strSeparators)
        {
            //create temporary storage
            ArrayList clsTokens = new ArrayList();

            //tokenize the text
            if ((strText != null) && (strSeparators != null))
            {
                int nIndex = 0;
                string strToken = null;
                while (nIndex < strText.Length)
                {
                    strToken = GetToken(strText, strSeparators, ref nIndex);
                    if (strToken == null) break;	//no more tokens found
                    clsTokens.Add(strToken);	//add token to the table
                }
            }

            //create the result
            string[] tblTokens = new string[clsTokens.Count];
            for (int i = 0; i < clsTokens.Count; ++i)
            {
                tblTokens[i] = clsTokens[i].ToString();
            }
            return tblTokens;
        }

        public static string Strip(string strText)
        {
            if (strText != null)
            {
                //trim the white spaces and remove quotas
                strText = strText.Trim();
                if (strText.Length >= 2)
                {
                    if ((strText.IndexOf("\"") == 0) &&
                        (strText.LastIndexOf("\"") == strText.Length - 1))
                    {
                        strText = strText.Substring(1, strText.Length - 2);
                    }
                }
            }
            return strText;
        }

        public static string[] BreakLine(string strLine, int nLength)
        {
            //break one long line into several shorter lines
            ArrayList clsLines = new ArrayList();

            //analyse the text line
            if (strLine != null)
            {
                //split the text line into pieces
                string[] tblTokens = strLine.Split(new char[] { ' ', '\t' });

                //combine lines
                string strTemp = "";
                for (int i = 0; i < tblTokens.Length; ++i)
                {
                    strTemp += tblTokens[i];
                    strTemp += " ";		//add space
                    if (strTemp.Length >= nLength)	//time to break the line
                    {
                        clsLines.Add(strTemp.Trim());
                        strTemp = "";
                    }
                }

                //add the reminder (if there is a reminder)
                if (strTemp.Trim().Length > 0) clsLines.Add(strTemp.Trim());
            }

            //convert the result to the array of strings
            string[] tblLines = new string[clsLines.Count];
            for (int i = 0; i < clsLines.Count; ++i)
            {
                tblLines[i] = clsLines[i].ToString();
            }
            return tblLines;
        }
    }
}
