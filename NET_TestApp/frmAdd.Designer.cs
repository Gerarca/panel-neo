namespace NET_TestApp
{
    partial class frmAdd
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.btnOK = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.tbIAC = new System.Windows.Forms.TextBox();
			this.tbIID = new System.Windows.Forms.TextBox();
			this.cbxUDP = new System.Windows.Forms.ComboBox();
			this.cbxTCP = new System.Windows.Forms.ComboBox();
			this.tbInstallersCode = new System.Windows.Forms.TextBox();
			this.nudKeyTime = new System.Windows.Forms.NumericUpDown();
			((System.ComponentModel.ISupportInitialize)(this.nudKeyTime)).BeginInit();
			this.SuspendLayout();
			// 
			// btnOK
			// 
			this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.btnOK.Location = new System.Drawing.Point(192, 263);
			this.btnOK.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(100, 28);
			this.btnOK.TabIndex = 0;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(16, 11);
			this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(86, 16);
			this.label1.TabIndex = 1;
			this.label1.Text = "Integration Id:";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(16, 53);
			this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(156, 16);
			this.label2.TabIndex = 2;
			this.label2.Text = "Integration Access Code:";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(16, 91);
			this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(144, 16);
			this.label3.TabIndex = 3;
			this.label3.Text = "UDP Channel Function:";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(16, 135);
			this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(142, 16);
			this.label4.TabIndex = 4;
			this.label4.Text = "TCP Channel Function:";
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(16, 174);
			this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(102, 16);
			this.label5.TabIndex = 5;
			this.label5.Text = "Installer\'s Code:";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(16, 214);
			this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(117, 16);
			this.label6.TabIndex = 6;
			this.label6.Text = "Key Change Time:";
			// 
			// tbIAC
			// 
			this.tbIAC.Location = new System.Drawing.Point(192, 49);
			this.tbIAC.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.tbIAC.MaxLength = 32;
			this.tbIAC.Name = "tbIAC";
			this.tbIAC.Size = new System.Drawing.Size(273, 22);
			this.tbIAC.TabIndex = 7;
			this.tbIAC.Text = "12345678123456781234567812345678";
			this.tbIAC.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbIAC_KeyPress);
			// 
			// tbIID
			// 
			this.tbIID.Location = new System.Drawing.Point(192, 7);
			this.tbIID.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.tbIID.MaxLength = 12;
			this.tbIID.Name = "tbIID";
			this.tbIID.Size = new System.Drawing.Size(273, 22);
			this.tbIID.TabIndex = 8;
			this.tbIID.Text = "123456781234";
			this.tbIID.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbIID_KeyPress);
			// 
			// cbxUDP
			// 
			this.cbxUDP.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cbxUDP.FormattingEnabled = true;
			this.cbxUDP.Location = new System.Drawing.Point(192, 87);
			this.cbxUDP.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.cbxUDP.Name = "cbxUDP";
			this.cbxUDP.Size = new System.Drawing.Size(273, 24);
			this.cbxUDP.TabIndex = 9;
			// 
			// cbxTCP
			// 
			this.cbxTCP.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cbxTCP.FormattingEnabled = true;
			this.cbxTCP.Location = new System.Drawing.Point(192, 132);
			this.cbxTCP.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.cbxTCP.Name = "cbxTCP";
			this.cbxTCP.Size = new System.Drawing.Size(273, 24);
			this.cbxTCP.TabIndex = 10;
			// 
			// tbInstallersCode
			// 
			this.tbInstallersCode.Location = new System.Drawing.Point(192, 170);
			this.tbInstallersCode.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.tbInstallersCode.MaxLength = 6;
			this.tbInstallersCode.Name = "tbInstallersCode";
			this.tbInstallersCode.Size = new System.Drawing.Size(273, 22);
			this.tbInstallersCode.TabIndex = 11;
			this.tbInstallersCode.Text = "5555";
			this.tbInstallersCode.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbInstallersCode_KeyPress);
			// 
			// nudKeyTime
			// 
			this.nudKeyTime.Location = new System.Drawing.Point(192, 212);
			this.nudKeyTime.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.nudKeyTime.Name = "nudKeyTime";
			this.nudKeyTime.Size = new System.Drawing.Size(275, 22);
			this.nudKeyTime.TabIndex = 12;
			// 
			// frmAdd
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(487, 303);
			this.Controls.Add(this.nudKeyTime);
			this.Controls.Add(this.tbInstallersCode);
			this.Controls.Add(this.cbxTCP);
			this.Controls.Add(this.cbxUDP);
			this.Controls.Add(this.tbIID);
			this.Controls.Add(this.tbIAC);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.btnOK);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "frmAdd";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Add Account";
			this.Load += new System.EventHandler(this.frmAdd_Load);
			((System.ComponentModel.ISupportInitialize)(this.nudKeyTime)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox tbIAC;
        private System.Windows.Forms.TextBox tbIID;
        private System.Windows.Forms.ComboBox cbxUDP;
        private System.Windows.Forms.ComboBox cbxTCP;
        private System.Windows.Forms.TextBox tbInstallersCode;
        private System.Windows.Forms.NumericUpDown nudKeyTime;
    }
}