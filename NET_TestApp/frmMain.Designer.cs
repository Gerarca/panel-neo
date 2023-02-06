namespace NET_TestApp
{
    partial class frmMain
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
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
			this.pnlMain = new System.Windows.Forms.Panel();
			this.scMain = new System.Windows.Forms.SplitContainer();
			this.lvSecurityBases = new NET_TestApp.Helpers.ListViewNF();
			this.ilStatus = new System.Windows.Forms.ImageList(this.components);
			this.rtbDebug = new System.Windows.Forms.RichTextBox();
			this.tsMain = new System.Windows.Forms.ToolStrip();
			this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
			this.tstbIP = new System.Windows.Forms.ToolStripTextBox();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.toolStripLabel2 = new System.Windows.Forms.ToolStripLabel();
			this.tstbUDP = new System.Windows.Forms.ToolStripTextBox();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.toolStripLabel3 = new System.Windows.Forms.ToolStripLabel();
			this.tstbTCP = new System.Windows.Forms.ToolStripTextBox();
			this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
			this.tsbAdd = new System.Windows.Forms.ToolStripButton();
			this.tsbRemove = new System.Windows.Forms.ToolStripButton();
			this.tsbEdit = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
			this.tsbStart = new System.Windows.Forms.ToolStripButton();
			this.tsbStop = new System.Windows.Forms.ToolStripButton();
			this.pnlMain.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.scMain)).BeginInit();
			this.scMain.Panel1.SuspendLayout();
			this.scMain.Panel2.SuspendLayout();
			this.scMain.SuspendLayout();
			this.tsMain.SuspendLayout();
			this.SuspendLayout();
			// 
			// pnlMain
			// 
			this.pnlMain.Controls.Add(this.scMain);
			this.pnlMain.Controls.Add(this.tsMain);
			this.pnlMain.Dock = System.Windows.Forms.DockStyle.Fill;
			this.pnlMain.Location = new System.Drawing.Point(0, 0);
			this.pnlMain.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.pnlMain.Name = "pnlMain";
			this.pnlMain.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.pnlMain.Size = new System.Drawing.Size(1324, 773);
			this.pnlMain.TabIndex = 0;
			// 
			// scMain
			// 
			this.scMain.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.scMain.Dock = System.Windows.Forms.DockStyle.Fill;
			this.scMain.Location = new System.Drawing.Point(4, 31);
			this.scMain.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.scMain.Name = "scMain";
			// 
			// scMain.Panel1
			// 
			this.scMain.Panel1.Controls.Add(this.lvSecurityBases);
			// 
			// scMain.Panel2
			// 
			this.scMain.Panel2.Controls.Add(this.rtbDebug);
			this.scMain.Size = new System.Drawing.Size(1316, 738);
			this.scMain.SplitterDistance = 612;
			this.scMain.SplitterWidth = 5;
			this.scMain.TabIndex = 3;
			// 
			// lvSecurityBases
			// 
			this.lvSecurityBases.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.lvSecurityBases.Dock = System.Windows.Forms.DockStyle.Fill;
			this.lvSecurityBases.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
			this.lvSecurityBases.HideSelection = false;
			this.lvSecurityBases.LargeImageList = this.ilStatus;
			this.lvSecurityBases.Location = new System.Drawing.Point(0, 0);
			this.lvSecurityBases.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.lvSecurityBases.MultiSelect = false;
			this.lvSecurityBases.Name = "lvSecurityBases";
			this.lvSecurityBases.ShowGroups = false;
			this.lvSecurityBases.Size = new System.Drawing.Size(610, 736);
			this.lvSecurityBases.TabIndex = 0;
			this.lvSecurityBases.TileSize = new System.Drawing.Size(210, 105);
			this.lvSecurityBases.UseCompatibleStateImageBehavior = false;
			this.lvSecurityBases.View = System.Windows.Forms.View.Tile;
			this.lvSecurityBases.SelectedIndexChanged += new System.EventHandler(this.lvSecurityBases_SelectedIndexChanged);
			this.lvSecurityBases.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.lvSecurityBases_MouseDoubleClick);
			// 
			// ilStatus
			// 
			this.ilStatus.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("ilStatus.ImageStream")));
			this.ilStatus.TransparentColor = System.Drawing.Color.Transparent;
			this.ilStatus.Images.SetKeyName(0, "96x96_Stopped.png");
			this.ilStatus.Images.SetKeyName(1, "96x96_Running.png");
			this.ilStatus.Images.SetKeyName(2, "96x96_Error.png");
			// 
			// rtbDebug
			// 
			this.rtbDebug.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.rtbDebug.Dock = System.Windows.Forms.DockStyle.Fill;
			this.rtbDebug.Location = new System.Drawing.Point(0, 0);
			this.rtbDebug.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.rtbDebug.Name = "rtbDebug";
			this.rtbDebug.Size = new System.Drawing.Size(697, 736);
			this.rtbDebug.TabIndex = 2;
			this.rtbDebug.Text = "";
			this.rtbDebug.TextChanged += new System.EventHandler(this.rtbDebug_TextChanged);
			// 
			// tsMain
			// 
			this.tsMain.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
			this.tsMain.ImageScalingSize = new System.Drawing.Size(20, 20);
			this.tsMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabel1,
            this.tstbIP,
            this.toolStripSeparator1,
            this.toolStripLabel2,
            this.tstbUDP,
            this.toolStripSeparator2,
            this.toolStripLabel3,
            this.tstbTCP,
            this.toolStripSeparator3,
            this.tsbAdd,
            this.tsbRemove,
            this.tsbEdit,
            this.toolStripSeparator4,
            this.tsbStart,
            this.tsbStop});
			this.tsMain.Location = new System.Drawing.Point(4, 4);
			this.tsMain.Name = "tsMain";
			this.tsMain.Size = new System.Drawing.Size(1316, 27);
			this.tsMain.TabIndex = 4;
			this.tsMain.Text = "tsMain";
			this.tsMain.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.tsMain_ItemClicked);
			// 
			// toolStripLabel1
			// 
			this.toolStripLabel1.Name = "toolStripLabel1";
			this.toolStripLabel1.Size = new System.Drawing.Size(94, 24);
			this.toolStripLabel1.Text = "Computer IP:";
			// 
			// tstbIP
			// 
			this.tstbIP.Font = new System.Drawing.Font("Segoe UI", 9F);
			this.tstbIP.Name = "tstbIP";
			this.tstbIP.Size = new System.Drawing.Size(132, 27);
			this.tstbIP.Text = "127.0.0.1";
			this.tstbIP.Click += new System.EventHandler(this.tstbIP_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(6, 27);
			// 
			// toolStripLabel2
			// 
			this.toolStripLabel2.Name = "toolStripLabel2";
			this.toolStripLabel2.Size = new System.Drawing.Size(71, 24);
			this.toolStripLabel2.Text = "UDP Port:";
			// 
			// tstbUDP
			// 
			this.tstbUDP.Font = new System.Drawing.Font("Segoe UI", 9F);
			this.tstbUDP.Name = "tstbUDP";
			this.tstbUDP.Size = new System.Drawing.Size(132, 27);
			this.tstbUDP.Text = "3073";
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(6, 27);
			// 
			// toolStripLabel3
			// 
			this.toolStripLabel3.Name = "toolStripLabel3";
			this.toolStripLabel3.Size = new System.Drawing.Size(66, 24);
			this.toolStripLabel3.Text = "TCP Port:";
			// 
			// tstbTCP
			// 
			this.tstbTCP.Font = new System.Drawing.Font("Segoe UI", 9F);
			this.tstbTCP.Name = "tstbTCP";
			this.tstbTCP.Size = new System.Drawing.Size(132, 27);
			this.tstbTCP.Text = "3072";
			// 
			// toolStripSeparator3
			// 
			this.toolStripSeparator3.Name = "toolStripSeparator3";
			this.toolStripSeparator3.Size = new System.Drawing.Size(6, 27);
			// 
			// tsbAdd
			// 
			this.tsbAdd.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbAdd.Image = ((System.Drawing.Image)(resources.GetObject("tsbAdd.Image")));
			this.tsbAdd.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbAdd.Name = "tsbAdd";
			this.tsbAdd.Size = new System.Drawing.Size(29, 24);
			this.tsbAdd.Text = "Add";
			this.tsbAdd.Click += new System.EventHandler(this.tsbAdd_Click);
			// 
			// tsbRemove
			// 
			this.tsbRemove.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbRemove.Image = ((System.Drawing.Image)(resources.GetObject("tsbRemove.Image")));
			this.tsbRemove.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbRemove.Name = "tsbRemove";
			this.tsbRemove.Size = new System.Drawing.Size(29, 24);
			this.tsbRemove.Text = "Remove";
			this.tsbRemove.Click += new System.EventHandler(this.tsbRemove_Click);
			// 
			// tsbEdit
			// 
			this.tsbEdit.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbEdit.Image = ((System.Drawing.Image)(resources.GetObject("tsbEdit.Image")));
			this.tsbEdit.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbEdit.Name = "tsbEdit";
			this.tsbEdit.Size = new System.Drawing.Size(29, 24);
			this.tsbEdit.Text = "Edit";
			this.tsbEdit.Click += new System.EventHandler(this.tsbEdit_Click);
			// 
			// toolStripSeparator4
			// 
			this.toolStripSeparator4.Name = "toolStripSeparator4";
			this.toolStripSeparator4.Size = new System.Drawing.Size(6, 27);
			// 
			// tsbStart
			// 
			this.tsbStart.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbStart.Image = ((System.Drawing.Image)(resources.GetObject("tsbStart.Image")));
			this.tsbStart.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbStart.Name = "tsbStart";
			this.tsbStart.Size = new System.Drawing.Size(29, 24);
			this.tsbStart.Text = "Start";
			this.tsbStart.Click += new System.EventHandler(this.tsbStart_Click);
			// 
			// tsbStop
			// 
			this.tsbStop.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbStop.Image = ((System.Drawing.Image)(resources.GetObject("tsbStop.Image")));
			this.tsbStop.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbStop.Name = "tsbStop";
			this.tsbStop.Size = new System.Drawing.Size(29, 24);
			this.tsbStop.Text = "Stop";
			this.tsbStop.Click += new System.EventHandler(this.tsbStop_Click);
			// 
			// frmMain
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1324, 773);
			this.Controls.Add(this.pnlMain);
			this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
			this.Name = "frmMain";
			this.Text = "dotNET TestApp";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmMain_FormClosing);
			this.Load += new System.EventHandler(this.frmMain_Load);
			this.pnlMain.ResumeLayout(false);
			this.pnlMain.PerformLayout();
			this.scMain.Panel1.ResumeLayout(false);
			this.scMain.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.scMain)).EndInit();
			this.scMain.ResumeLayout(false);
			this.tsMain.ResumeLayout(false);
			this.tsMain.PerformLayout();
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlMain;
        private System.Windows.Forms.SplitContainer scMain;
        private System.Windows.Forms.RichTextBox rtbDebug;
        private NET_TestApp.Helpers.ListViewNF lvSecurityBases;
        private System.Windows.Forms.ImageList ilStatus;
        private System.Windows.Forms.ToolStrip tsMain;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripTextBox tstbIP;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripLabel toolStripLabel2;
        private System.Windows.Forms.ToolStripTextBox tstbUDP;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripLabel toolStripLabel3;
        private System.Windows.Forms.ToolStripTextBox tstbTCP;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripButton tsbAdd;
        private System.Windows.Forms.ToolStripButton tsbRemove;
        private System.Windows.Forms.ToolStripButton tsbStart;
        private System.Windows.Forms.ToolStripButton tsbStop;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripButton tsbEdit;
    }
}