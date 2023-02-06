using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using TSP.DSC_InteractiveSDK;
using TSP.DSC_InteractiveSDK.Security;
using DSC.Automation.CustomProperties;
using DSC.Automation.DataHelpers;
using DSC.Automation.TextHelpers;

namespace NET_TestApp
{
    public partial class frmParameterValuesEntry : Form
    {
        #region Variables
        ParameterInfo[] _parametersInfo;
        List<object>    _values;
        InteractiveSDK  _sdk;
        PropertyHelper  _helper = new PropertyHelper();
        #endregion

        #region Constructor
        public frmParameterValuesEntry(string caption, InteractiveSDK sdk, ParameterInfo[] parametersInfo, List<object> values)
        {
            InitializeComponent();

            this.Text            = caption;
            this._parametersInfo = parametersInfo;
            this._values         = values;
            this._sdk            = sdk;

            pgParameters.SetParentForm(this);

            //clear property grid
            pgParameters.SelectedObject = null;

            // setup
            foreach (ParameterInfo pi in this._parametersInfo)
            {
                // only add if it isn't byRef... means we need to create an object based on what type.
                // byRef parameters need to be sent an object of NULL so the method can fill it in and
                // we take care to cast it to the proper type later.
                if (pi.ParameterType.IsByRef == false)
                {
                    PropertyData p = new PropertyData();
                    p.Name        = pi.Name;
                    p.Label       = pi.Name;
                    p.Value       = String.Empty;
                    p.DataType    = DataType.String;
                    p.IsBrowsable = true;
                    if (pi.ParameterType.IsEnum == true)
                    {
                        // doing some assembly magic to programatically resolve the ParameterType... avoids having to use a giant if statement
                        // to process ALL the enums seperately
                        string assembly = typeof(FAPType).AssemblyQualifiedName.Remove(0, typeof(FAPType).AssemblyQualifiedName.IndexOf(','));
                        Type aType = Type.GetType(pi.ParameterType.FullName + assembly);

                        string[] tblValues = Enum.GetNames(aType);
                        for (int i = 0; i < tblValues.Length; ++i)
                        {
                            if ((string.Compare(tblValues[i].ToString(), "Not_Available") == 0) ||
                                (string.Compare(tblValues[i].ToString(), "Unknown") == 0))
                            {
                                continue;
                            } // if
                            NamedValue clsValue = new NamedValue();
                            clsValue.Label = tblValues[i].ToString();
                            clsValue.Value = tblValues[i].ToString();
                            p.ValidValues.Add(clsValue);
                        } // for
                        p.Value = p.ValidValues[0].Label.ToString();
                    }
                    else if (pi.ParameterType == typeof(bool))
                    {
                        string[] tblValues = new string[] { "true", "false" };
                        for (int i = 0; i < tblValues.Length; ++i)
                        {
                            NamedValue clsValue = new NamedValue();
                            clsValue.Label = tblValues[i].ToString();
                            clsValue.Value = tblValues[i].ToString();
                            p.ValidValues.Add(clsValue);
                        } // for
                        p.Value = tblValues[0].ToString();
                    }
                    else
                    {
                    } // if
                    p.Synchronize();
                    _helper.AddProperty(p, false);
                } // if
            } // foreach

            pgParameters.SelectedObject = _helper.Properties;
        }
        #endregion

        #region Form Events
        private void frmParameterValuesEntry_Shown(object sender, EventArgs e)
        {
            pgParameters.Focus();
        }

        private void frmParameterValuesEntry_FormClosing(object sender, FormClosingEventArgs e)
        {
            // finalize
            if (this.DialogResult == DialogResult.OK)
            {
                foreach (ParameterInfo pi in this._parametersInfo)
                {
                    if (pi.ParameterType.IsByRef == true)
                    {
                        // reference parameter, add null object to catch the value on method execution
                        this._values.Add(null);
                        continue;
                    } // if

                    if (pi.ParameterType == typeof(IAccessCredentials))
                    {
                        IAccessCredentials credentials = this._sdk.CreateAccessCredentials(AccessCredentialsType.Numeric);
                        credentials.CredentialsString = (_helper.Properties[String.Format("{0}\\{1}", "", pi.Name)].Data.Value as string);
                        this._values.Add(credentials);
                    }
                    else if (pi.ParameterType == typeof(UInt32))
                    {
                        this._values.Add(Convert.ToUInt32(_helper.Properties[String.Format("{0}\\{1}", "", pi.Name)].Data.Value as string));
                    }
                    else if (pi.ParameterType == typeof(string))
                    {
                        this._values.Add(_helper.Properties[String.Format("{0}\\{1}", "", pi.Name)].Data.Value as string);
                    }
                    else if (pi.ParameterType.IsEnum == true)
                    {
                        // doing some assembly magic to programatically resolve the ParameterType... avoids having to use a giant if statement
                        // to process ALL the enums seperately
                        string assembly = typeof(FAPType).AssemblyQualifiedName.Remove(0, typeof(FAPType).AssemblyQualifiedName.IndexOf(','));
                        Type   aType    = Type.GetType(pi.ParameterType.FullName + assembly);

                        this._values.Add(Enum.Parse(aType, _helper.Properties[String.Format("{0}\\{1}", "", pi.Name)].Data.Value as string));
                    }
                    else if (pi.ParameterType == typeof(bool))
                    {
                        this._values.Add(Convert.ToBoolean(_helper.Properties[String.Format("{0}\\{1}", "", pi.Name)].Data.Value as string));
                    }
                    else if (pi.ParameterType == typeof(UInt32[]))
                    {
                        //split the string
                        string[] tblData = Tokenizer.Split(_helper.Properties[String.Format("{0}\\{1}", "", pi.Name)].Data.Value as string, ",");
                        int numCount = tblData.Length;
                        object objResult = new UInt32[numCount];

                        //use default converter
                        for (int i = 0; i < numCount; ++i)
                        {
                            ((UInt32[])objResult)[i] = (UInt32)Convert.ChangeType(tblData[i], typeof(UInt32));
                        }
                        this._values.Add((objResult as UInt32[]));
                    }
                    else if (pi.ParameterType == typeof(byte))
                    {
                        this._values.Add(Convert.ToByte(_helper.Properties[String.Format("{0}\\{1}", "", pi.Name)].Data.Value as string));
                    }
                    else
                    {
                        // unknown parametertype
                    } // if
                } // foreach
            } // if
        }
        #endregion
    }
}
