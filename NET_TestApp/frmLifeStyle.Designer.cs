namespace NET_TestApp
{
    partial class frmLifeStyle
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
            this.pnlLifeStyle = new System.Windows.Forms.Panel();
            this.btnMoveToOn = new System.Windows.Forms.Button();
            this.btnMoveToOff = new System.Windows.Forms.Button();
            this.lblOff = new System.Windows.Forms.Label();
            this.lblOn = new System.Windows.Forms.Label();
            this.lbOn = new System.Windows.Forms.ListBox();
            this.lbOff = new System.Windows.Forms.ListBox();
            this.btnWriteZones = new System.Windows.Forms.Button();
            this.btnReadZones = new System.Windows.Forms.Button();
            this.btnWriteLifeStyle = new System.Windows.Forms.Button();
            this.btnReadLifeStyle = new System.Windows.Forms.Button();
            this.btnDefaultLifeStyle = new System.Windows.Forms.Button();
            this.btnDefaultZones = new System.Windows.Forms.Button();
            this.pnlLifeStyle.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlLifeStyle
            // 
            this.pnlLifeStyle.Controls.Add(this.btnDefaultZones);
            this.pnlLifeStyle.Controls.Add(this.btnDefaultLifeStyle);
            this.pnlLifeStyle.Controls.Add(this.btnMoveToOn);
            this.pnlLifeStyle.Controls.Add(this.btnMoveToOff);
            this.pnlLifeStyle.Controls.Add(this.lblOff);
            this.pnlLifeStyle.Controls.Add(this.lblOn);
            this.pnlLifeStyle.Controls.Add(this.lbOn);
            this.pnlLifeStyle.Controls.Add(this.lbOff);
            this.pnlLifeStyle.Controls.Add(this.btnWriteZones);
            this.pnlLifeStyle.Controls.Add(this.btnReadZones);
            this.pnlLifeStyle.Controls.Add(this.btnWriteLifeStyle);
            this.pnlLifeStyle.Controls.Add(this.btnReadLifeStyle);
            this.pnlLifeStyle.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlLifeStyle.Location = new System.Drawing.Point(0, 0);
            this.pnlLifeStyle.Name = "pnlLifeStyle";
            this.pnlLifeStyle.Size = new System.Drawing.Size(836, 475);
            this.pnlLifeStyle.TabIndex = 0;
            // 
            // btnMoveToOn
            // 
            this.btnMoveToOn.Location = new System.Drawing.Point(251, 230);
            this.btnMoveToOn.Name = "btnMoveToOn";
            this.btnMoveToOn.Size = new System.Drawing.Size(107, 23);
            this.btnMoveToOn.TabIndex = 7;
            this.btnMoveToOn.TabStop = false;
            this.btnMoveToOn.Text = "<<";
            this.btnMoveToOn.UseVisualStyleBackColor = true;
            this.btnMoveToOn.Click += new System.EventHandler(this.Move_To_Click);
            // 
            // btnMoveToOff
            // 
            this.btnMoveToOff.Location = new System.Drawing.Point(251, 201);
            this.btnMoveToOff.Name = "btnMoveToOff";
            this.btnMoveToOff.Size = new System.Drawing.Size(107, 23);
            this.btnMoveToOff.TabIndex = 6;
            this.btnMoveToOff.TabStop = false;
            this.btnMoveToOff.Text = ">>";
            this.btnMoveToOff.UseVisualStyleBackColor = true;
            this.btnMoveToOff.Click += new System.EventHandler(this.Move_To_Click);
            // 
            // lblOff
            // 
            this.lblOff.AutoSize = true;
            this.lblOff.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblOff.Location = new System.Drawing.Point(361, 9);
            this.lblOff.Name = "lblOff";
            this.lblOff.Size = new System.Drawing.Size(99, 13);
            this.lblOff.TabIndex = 5;
            this.lblOff.Text = "Notifications Off";
            // 
            // lblOn
            // 
            this.lblOn.AutoSize = true;
            this.lblOn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblOn.Location = new System.Drawing.Point(3, 9);
            this.lblOn.Name = "lblOn";
            this.lblOn.Size = new System.Drawing.Size(98, 13);
            this.lblOn.TabIndex = 4;
            this.lblOn.Text = "Notifications On";
            // 
            // lbOn
            // 
            this.lbOn.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.lbOn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lbOn.FormattingEnabled = true;
            this.lbOn.Location = new System.Drawing.Point(3, 29);
            this.lbOn.Name = "lbOn";
            this.lbOn.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.lbOn.Size = new System.Drawing.Size(242, 444);
            this.lbOn.Sorted = true;
            this.lbOn.TabIndex = 0;
            this.lbOn.TabStop = false;
            // 
            // lbOff
            // 
            this.lbOff.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.lbOff.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lbOff.FormattingEnabled = true;
            this.lbOff.Location = new System.Drawing.Point(364, 29);
            this.lbOff.Name = "lbOff";
            this.lbOff.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.lbOff.Size = new System.Drawing.Size(242, 444);
            this.lbOff.Sorted = true;
            this.lbOff.TabIndex = 0;
            this.lbOff.TabStop = false;
            // 
            // btnWriteZones
            // 
            this.btnWriteZones.Location = new System.Drawing.Point(608, 144);
            this.btnWriteZones.Name = "btnWriteZones";
            this.btnWriteZones.Size = new System.Drawing.Size(225, 23);
            this.btnWriteZones.TabIndex = 3;
            this.btnWriteZones.TabStop = false;
            this.btnWriteZones.Text = "ITV2_WriteZoneNotificationSettings";
            this.btnWriteZones.UseVisualStyleBackColor = true;
            this.btnWriteZones.Click += new System.EventHandler(this.Read_Write_Click);
            // 
            // btnReadZones
            // 
            this.btnReadZones.Location = new System.Drawing.Point(608, 115);
            this.btnReadZones.Name = "btnReadZones";
            this.btnReadZones.Size = new System.Drawing.Size(225, 23);
            this.btnReadZones.TabIndex = 2;
            this.btnReadZones.TabStop = false;
            this.btnReadZones.Text = "ITV2_ReadZoneNotificationSettings";
            this.btnReadZones.UseVisualStyleBackColor = true;
            this.btnReadZones.Click += new System.EventHandler(this.Read_Write_Click);
            // 
            // btnWriteLifeStyle
            // 
            this.btnWriteLifeStyle.Location = new System.Drawing.Point(608, 57);
            this.btnWriteLifeStyle.Name = "btnWriteLifeStyle";
            this.btnWriteLifeStyle.Size = new System.Drawing.Size(225, 23);
            this.btnWriteLifeStyle.TabIndex = 1;
            this.btnWriteLifeStyle.TabStop = false;
            this.btnWriteLifeStyle.Text = "ITV2_WriteLifeStyleNotificationSettings";
            this.btnWriteLifeStyle.UseVisualStyleBackColor = true;
            this.btnWriteLifeStyle.Click += new System.EventHandler(this.Read_Write_Click);
            // 
            // btnReadLifeStyle
            // 
            this.btnReadLifeStyle.Location = new System.Drawing.Point(608, 28);
            this.btnReadLifeStyle.Name = "btnReadLifeStyle";
            this.btnReadLifeStyle.Size = new System.Drawing.Size(225, 23);
            this.btnReadLifeStyle.TabIndex = 0;
            this.btnReadLifeStyle.TabStop = false;
            this.btnReadLifeStyle.Text = "ITV2_ReadLifeStyleNotificationSettings";
            this.btnReadLifeStyle.UseVisualStyleBackColor = true;
            this.btnReadLifeStyle.Click += new System.EventHandler(this.Read_Write_Click);
            // 
            // btnDefaultLifeStyle
            // 
            this.btnDefaultLifeStyle.Location = new System.Drawing.Point(608, 86);
            this.btnDefaultLifeStyle.Name = "btnDefaultLifeStyle";
            this.btnDefaultLifeStyle.Size = new System.Drawing.Size(225, 23);
            this.btnDefaultLifeStyle.TabIndex = 8;
            this.btnDefaultLifeStyle.TabStop = false;
            this.btnDefaultLifeStyle.Text = "ITV2_DefaultLifeStyleNotificationSettings";
            this.btnDefaultLifeStyle.UseVisualStyleBackColor = true;
            this.btnDefaultLifeStyle.Click += new System.EventHandler(this.Read_Write_Click);
            // 
            // btnDefaultZones
            // 
            this.btnDefaultZones.Location = new System.Drawing.Point(608, 173);
            this.btnDefaultZones.Name = "btnDefaultZones";
            this.btnDefaultZones.Size = new System.Drawing.Size(225, 23);
            this.btnDefaultZones.TabIndex = 9;
            this.btnDefaultZones.TabStop = false;
            this.btnDefaultZones.Text = "ITV2_DefaultZoneNotificationSettings";
            this.btnDefaultZones.UseVisualStyleBackColor = true;
            this.btnDefaultZones.Click += new System.EventHandler(this.Read_Write_Click);
            // 
            // frmLifeStyle
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(836, 475);
            this.Controls.Add(this.pnlLifeStyle);
            this.Name = "frmLifeStyle";
            this.Text = "LifeStyle";
            this.pnlLifeStyle.ResumeLayout(false);
            this.pnlLifeStyle.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlLifeStyle;
        private System.Windows.Forms.ListBox lbOn;
        private System.Windows.Forms.ListBox lbOff;
        private System.Windows.Forms.Button btnWriteZones;
        private System.Windows.Forms.Button btnReadZones;
        private System.Windows.Forms.Button btnWriteLifeStyle;
        private System.Windows.Forms.Button btnReadLifeStyle;
        private System.Windows.Forms.Label lblOff;
        private System.Windows.Forms.Label lblOn;
        private System.Windows.Forms.Button btnMoveToOn;
        private System.Windows.Forms.Button btnMoveToOff;
        private System.Windows.Forms.Button btnDefaultZones;
        private System.Windows.Forms.Button btnDefaultLifeStyle;
    }
}