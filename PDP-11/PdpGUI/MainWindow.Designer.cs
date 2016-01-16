namespace PdpGUI
{
    partial class MainWindow
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
            this.Display = new System.Windows.Forms.PictureBox();
            this.programText = new System.Windows.Forms.ListView();
            this.runButton = new System.Windows.Forms.Button();
            this.resetButton = new System.Windows.Forms.Button();
            this.stepButton = new System.Windows.Forms.Button();
            this.mainTimer = new System.Windows.Forms.Timer(this.components);
            this.procInfo = new System.Windows.Forms.ListView();
            this.screenUpdate = new System.Windows.Forms.Timer(this.components);
            this.stopButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.Display)).BeginInit();
            this.SuspendLayout();
            // 
            // Display
            // 
            this.Display.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.Display.Location = new System.Drawing.Point(13, 13);
            this.Display.Name = "Display";
            this.Display.Size = new System.Drawing.Size(512, 256);
            this.Display.TabIndex = 0;
            this.Display.TabStop = false;
            // 
            // programText
            // 
            this.programText.BackColor = System.Drawing.SystemColors.Window;
            this.programText.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.programText.HideSelection = false;
            this.programText.Location = new System.Drawing.Point(531, 13);
            this.programText.MultiSelect = false;
            this.programText.Name = "programText";
            this.programText.Size = new System.Drawing.Size(479, 256);
            this.programText.TabIndex = 1;
            this.programText.UseCompatibleStateImageBehavior = false;
            this.programText.ColumnWidthChanging += new System.Windows.Forms.ColumnWidthChangingEventHandler(this.programText_ColumnWidthChanging);
            // 
            // runButton
            // 
            this.runButton.Location = new System.Drawing.Point(13, 275);
            this.runButton.Name = "runButton";
            this.runButton.Size = new System.Drawing.Size(110, 45);
            this.runButton.TabIndex = 3;
            this.runButton.Text = "Run";
            this.runButton.UseVisualStyleBackColor = true;
            this.runButton.Click += new System.EventHandler(this.runButton_Click);
            // 
            // resetButton
            // 
            this.resetButton.Location = new System.Drawing.Point(415, 416);
            this.resetButton.Name = "resetButton";
            this.resetButton.Size = new System.Drawing.Size(110, 45);
            this.resetButton.TabIndex = 4;
            this.resetButton.Text = "Reset";
            this.resetButton.UseVisualStyleBackColor = true;
            this.resetButton.Click += new System.EventHandler(this.resetButton_Click);
            // 
            // stepButton
            // 
            this.stepButton.Location = new System.Drawing.Point(245, 275);
            this.stepButton.Name = "stepButton";
            this.stepButton.Size = new System.Drawing.Size(110, 45);
            this.stepButton.TabIndex = 5;
            this.stepButton.Text = "Step";
            this.stepButton.UseVisualStyleBackColor = true;
            this.stepButton.Click += new System.EventHandler(this.stepButton_Click);
            // 
            // mainTimer
            // 
            this.mainTimer.Interval = 1;
            this.mainTimer.Tick += new System.EventHandler(this.mainTimer_Tick);
            // 
            // procInfo
            // 
            this.procInfo.BackColor = System.Drawing.SystemColors.ControlLight;
            this.procInfo.Enabled = false;
            this.procInfo.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.procInfo.Location = new System.Drawing.Point(531, 275);
            this.procInfo.MultiSelect = false;
            this.procInfo.Name = "procInfo";
            this.procInfo.Size = new System.Drawing.Size(479, 186);
            this.procInfo.TabIndex = 6;
            this.procInfo.UseCompatibleStateImageBehavior = false;
            this.procInfo.ColumnWidthChanging += new System.Windows.Forms.ColumnWidthChangingEventHandler(this.procInfo_ColumnWidthChanging);
            // 
            // screenUpdate
            // 
            this.screenUpdate.Interval = 750;
            this.screenUpdate.Tick += new System.EventHandler(this.screenUpdate_Tick);
            // 
            // stopButton
            // 
            this.stopButton.Location = new System.Drawing.Point(129, 275);
            this.stopButton.Name = "stopButton";
            this.stopButton.Size = new System.Drawing.Size(110, 45);
            this.stopButton.TabIndex = 7;
            this.stopButton.Text = "Stop";
            this.stopButton.UseVisualStyleBackColor = true;
            this.stopButton.Click += new System.EventHandler(this.stopButton_Click);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1022, 474);
            this.Controls.Add(this.stopButton);
            this.Controls.Add(this.procInfo);
            this.Controls.Add(this.stepButton);
            this.Controls.Add(this.resetButton);
            this.Controls.Add(this.runButton);
            this.Controls.Add(this.programText);
            this.Controls.Add(this.Display);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Name = "MainWindow";
            this.Text = "PDP-11 Emulator";
            this.Load += new System.EventHandler(this.MainWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.Display)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox Display;
        private System.Windows.Forms.ListView programText;
        private System.Windows.Forms.Button runButton;
        private System.Windows.Forms.Button resetButton;
        private System.Windows.Forms.Button stepButton;
        private System.Windows.Forms.Timer mainTimer;
        private System.Windows.Forms.ListView procInfo;
        private System.Windows.Forms.Timer screenUpdate;
        private System.Windows.Forms.Button stopButton;

    }
}

