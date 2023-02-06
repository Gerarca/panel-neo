using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using TSP.DSC_InteractiveSDK;

namespace NET_TestApp
{
    public partial class frmAdd : Form
    {
        private Dictionary<string, Account> _accounts = null;
        private Account                     _account  = null;

        public frmAdd(Dictionary<string, Account> accounts, Account account)
        {
            InitializeComponent();

            _accounts = accounts;
            _account = account;

            cbxUDP.Items.Add(Parameters.ITV2_Param_Function_No_Function);
            cbxUDP.Items.Add(Parameters.ITV2_Param_Function_Polling_Only);
            cbxUDP.Items.Add(Parameters.ITV2_Param_Function_Notifications);
            cbxUDP.Items.Add(Parameters.ITV2_Param_Function_Poll_And_Notify);
            cbxTCP.Items.Add(Parameters.ITV2_Param_Function_No_Function);
            cbxTCP.Items.Add(Parameters.ITV2_Param_Function_Polling_Only);
            cbxTCP.Items.Add(Parameters.ITV2_Param_Function_Notifications);
            cbxTCP.Items.Add(Parameters.ITV2_Param_Function_Poll_And_Notify);
            if (_account == null)
            {
                this.Text = "Add Account";
                cbxUDP.SelectedIndex = 1;
                cbxTCP.SelectedIndex = 2;
            }
            else
            {
                this.Text = "Edit Account";
                tbIID.Text = _account.IntegrationId;
                tbIAC.Text = _account.IntegrationAccessCode;
                tbInstallersCode.Text = _account.InstallerCode;
                nudKeyTime.Value = _account.KeyChangeTime;
                cbxUDP.SelectedIndex = cbxUDP.Items.IndexOf(_account.UdpChannelFunction);
                cbxTCP.SelectedIndex = cbxUDP.Items.IndexOf(_account.TcpChannelFunction);
            }
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (_account == null)
            {
                _account = new Account();
            }
            if (_accounts.ContainsKey(_account.Identifier) == true)
            {
                // in list, update it
                _accounts.Remove(_account.Identifier);
            }
            _account.Identifier = tbIID.Text;
            _account.IntegrationId = tbIID.Text;
            _account.IntegrationAccessCode = tbIAC.Text;
            _account.InstallerCode = tbInstallersCode.Text;
            _account.UdpChannelFunction = cbxUDP.SelectedItem.ToString();
            _account.TcpChannelFunction = cbxTCP.SelectedItem.ToString();
            _account.KeyChangeTime = Convert.ToUInt32(nudKeyTime.Value);
            _accounts.Add(_account.Identifier, _account);
        }

        private void tbIID_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Uri.IsHexDigit(e.KeyChar) && !Char.IsControl(e.KeyChar))
            {
               e.Handled = true; 
            }            
            e.KeyChar = Char.ToUpper(e.KeyChar);
        }

        private void tbIAC_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsNumber(e.KeyChar) && !Char.IsControl(e.KeyChar))
            {
                e.Handled = true;
            }            
        }

        private void tbInstallersCode_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsNumber(e.KeyChar) && !Char.IsControl(e.KeyChar))
            {
                e.Handled = true;
            }            
        }

		private void frmAdd_Load(object sender, EventArgs e)
		{

		}
	}
}
