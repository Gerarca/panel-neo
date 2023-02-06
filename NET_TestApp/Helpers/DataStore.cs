using System;
using System.Collections.Generic;
using TSP.DSC_InteractiveSDK;
using DSC.Automation.TextHelpers;

namespace NET_TestApp
{
    public static class ExtendedParameters
    {
        public static string ITV2_Param_InstallersCode      = "ITV2_InstallersCode";
        public static string Query_Selector_Installers_Code = "InstallersCode";
    }

    public static class ExtendedParameterValues
    {
        public static string ITV2_Param_Value_UDP = "UDP";
        public static string ITV2_Param_Value_TCP = "TCP";
    }

    class DataStore : IDataStore
    {
        #region Variables
        private bool                        _flgDisposed = false;
        private Dictionary<string, Account> _accounts    = new Dictionary<string, Account>();
        #endregion

        #region Constructor
        public DataStore()
        {
        }

        ~DataStore()
        {
            Dispose(false);
        }
        #endregion

        #region Properties
        public Dictionary<string, Account> Accounts
        {
            get { return (_accounts); }
        }
        #endregion

        #region Public Methods
        public string SelectData(string strParams)
        {
            if (strParams != null)
            {
                ParamParser parser = new ParamParser();
                parser.Parse(strParams);
                if ((parser.Contains(Parameters.Query_Category) == true) &&
                    (parser.Contains(Parameters.Query_Selector) == true) &&
                    (parser.Contains(Parameters.ITV2_Param_Connection) == true) &&
                    (parser.Contains(Parameters.ITV2_Param_Identifier) == true))
                {
                    string category = parser.GetValue(Parameters.Query_Category);
                    string selector = parser.GetValue(Parameters.Query_Selector);
                    if ((string.Compare(category, Parameters.Query_Category_ITV2) == 0) &&
                        (string.Compare(selector, Parameters.Query_Selector_Account_Info) == 0))
                    {
                        string key = parser.GetValue(Parameters.ITV2_Param_Identifier);
                        if (_accounts.ContainsKey(key) == true)
                        {
                            Account account = _accounts[key];
                            parser.SetValue(Parameters.ITV2_Param_Integration_ID, account.IntegrationId);
                            parser.SetValue(Parameters.ITV2_Param_AccessCode, account.IntegrationAccessCode);
                            string connection = parser.GetValue(Parameters.ITV2_Param_Connection);
                            if (string.Compare(connection, ExtendedParameterValues.ITV2_Param_Value_UDP) == 0)
                            {
                                parser.SetValue(Parameters.ITV2_Param_Channel_Function, account.UdpChannelFunction);
                            }
                            else if (string.Compare(connection, ExtendedParameterValues.ITV2_Param_Value_TCP) == 0)
                            {
                                parser.SetValue(Parameters.ITV2_Param_Channel_Function, account.TcpChannelFunction);
                            }
                            else
                            {
                                parser.SetValue(Parameters.ITV2_Param_Channel_Function, Parameters.ITV2_Param_Function_No_Function);
                            } // if
                            parser.SetValue(ExtendedParameters.ITV2_Param_InstallersCode, account.InstallerCode);
                            parser.SetValue(Parameters.ITV2_Param_KeyChangeTime, account.KeyChangeTime.ToString());
                            return (parser.ToString());
                        } // if
                    } // if
                } // if
            } // if
            return (string.Empty);
        }

        public UInt32 InsertData(string strParams)
        {
            return 0;
        }

        public UInt32 UpdateData(string strParams)
        {
            UInt32 result = 0;
            if (strParams != null)
            {
                ParamParser parser = new ParamParser();
                parser.Parse(strParams);
                if ((parser.Contains(Parameters.Query_Category) == true) &&
                    (parser.Contains(Parameters.ITV2_Param_Connection) == true) &&
                    (parser.Contains(Parameters.ITV2_Param_Identifier) == true))
                {
                    string category = parser.GetValue(Parameters.Query_Category);
                    if (string.Compare(category, Parameters.Query_Category_ITV2) == 0)
                    {
                        string key = parser.GetValue(Parameters.ITV2_Param_Identifier);
                        if (_accounts.ContainsKey(key) == true)
                        {
                            Account account = _accounts[key];

                            //access code?
                            if (parser.Contains(Parameters.ITV2_Param_AccessCode) == true)
                            {
                                //update access code
                                account.IntegrationAccessCode = parser.GetValue(Parameters.ITV2_Param_AccessCode);
                                ++result;
                            }
                        } // if
                    } // if
                } // if
            } // if
            return result;
        }

        public UInt32 DeleteData(string strParams)
        {
            return 0;
        }

        public bool AddAccount(string identifier, string integrationid, string integrationcode, string udpchannelfunction, string tcpchannelfunction, string installercode, UInt32 keychangetime)
        {
            try
            {
                Account account = new Account(identifier, integrationid, integrationcode, udpchannelfunction, tcpchannelfunction, installercode, keychangetime);

                if (_accounts.ContainsKey(identifier) == false)
                {
                    _accounts.Add(identifier, account);
                }
                else
                {
                    _accounts[identifier] = account;
                } // if
                return (true);
            }
            catch (Exception)
            {
            } // try
            return (false);
        }

        public bool RemoveAccount(string identifier)
        {
            try
            {
                return (_accounts.Remove(identifier));
            }
            catch (Exception)
            {
            } // try
            return (false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion

        #region Private Methods
        private void Dispose(bool flgDisposing)
        {
            //check if the object has already been disposed of
            if (_flgDisposed) return;

            //explicit disposing?
            if (flgDisposing)
            {
                //dispose of the managed resources
            }

            //dispose of the unmanaged resources

            //the object has been disposed of
            _flgDisposed = true;
        }        
        #endregion
    }
}
