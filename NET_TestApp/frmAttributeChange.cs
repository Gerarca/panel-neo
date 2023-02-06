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
using NET_TestApp.Helpers;

namespace NET_TestApp
{
    public partial class frmAttributeChange : Form
    {
        #region Variables
        public string AttributeValue { get; set; }
        #endregion

        #region Constructor
        public frmAttributeChange(TreeNode node)
        {
            InitializeComponent();

            LoadCombobox(node);
        }
        #endregion

        #region Private Methods
        private void LoadCombobox(TreeNode node)
        {
            // doing some assembly magic to programatically resolve the Enum Type... avoids having to use a giant if statement
            // to process ALL the enums seperately
            string assembly = typeof(FAPType).AssemblyQualifiedName.Remove(0, typeof(FAPType).AssemblyQualifiedName.IndexOf(','));
            Type aType = ReflectionHelpers.GetPropertyType((node.Parent.Tag as clsNode).Object, (node.Tag as clsNode).ItemName);
            string[] tblValues = Enum.GetNames(aType);
            for (int i = 0; i < tblValues.Length; ++i)
            {
                if ((string.Compare(tblValues[i].ToString(), "Not_Available") == 0) ||
                    (string.Compare(tblValues[i].ToString(), "Unknown") == 0))
                {
                    continue;
                } // if
                cbAttributes.Items.Add(tblValues[i].ToString());
            } // for
            cbAttributes.SelectedItem = (node.Tag as clsNode).Value;
        }
        #endregion

        #region Form Events
        private void cbAttributes_SelectedIndexChanged(object sender, EventArgs e)
        {
            AttributeValue = cbAttributes.GetItemText(cbAttributes.SelectedItem);
        }
        #endregion
    }
}
