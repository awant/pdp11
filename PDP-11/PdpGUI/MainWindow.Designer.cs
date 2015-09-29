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
            System.Windows.Forms.ListViewGroup listViewGroup1 = new System.Windows.Forms.ListViewGroup("ListViewGroup", System.Windows.Forms.HorizontalAlignment.Left);
            this.Display = new System.Windows.Forms.PictureBox();
            this.programText = new System.Windows.Forms.ListView();
            this.internalInfo = new System.Windows.Forms.TextBox();
            this.runButton = new System.Windows.Forms.Button();
            this.resetButton = new System.Windows.Forms.Button();
            this.stepButton = new System.Windows.Forms.Button();
            this.mainTimer = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.Display)).BeginInit();
            this.SuspendLayout();
            // 
            // Display
            // 
            this.Display.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.Display.Location = new System.Drawing.Point(13, 13);
            this.Display.Name = "Display";
            this.Display.Size = new System.Drawing.Size(512, 512);
            this.Display.TabIndex = 0;
            this.Display.TabStop = false;
            // 
            // programText
            // 
            listViewGroup1.Header = "ListViewGroup";
            listViewGroup1.Name = "listViewGroup1";
            this.programText.Groups.AddRange(new System.Windows.Forms.ListViewGroup[] {
            listViewGroup1});
            this.programText.Location = new System.Drawing.Point(531, 13);
            this.programText.Name = "programText";
            this.programText.Size = new System.Drawing.Size(574, 264);
            this.programText.TabIndex = 1;
            this.programText.UseCompatibleStateImageBehavior = false;
            // 
            // internalInfo
            // 
            this.internalInfo.Cursor = System.Windows.Forms.Cursors.Default;
            this.internalInfo.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.internalInfo.Location = new System.Drawing.Point(531, 321);
            this.internalInfo.Multiline = true;
            this.internalInfo.Name = "internalInfo";
            this.internalInfo.ReadOnly = true;
            this.internalInfo.Size = new System.Drawing.Size(574, 257);
            this.internalInfo.TabIndex = 2;
            this.internalInfo.Text = "Registers\r\nR0:\r\nR1:\r\nR2:\r\nR3:\r\nR4:\r\nR5:\r\nR6:\r\nR7:";
            // 
            // runButton
            // 
            this.runButton.Location = new System.Drawing.Point(201, 533);
            this.runButton.Name = "runButton";
            this.runButton.Size = new System.Drawing.Size(110, 45);
            this.runButton.TabIndex = 3;
            this.runButton.Text = "Run";
            this.runButton.UseVisualStyleBackColor = true;
            this.runButton.Click += new System.EventHandler(this.runButton_Click);
            // 
            // resetButton
            // 
            this.resetButton.Location = new System.Drawing.Point(13, 533);
            this.resetButton.Name = "resetButton";
            this.resetButton.Size = new System.Drawing.Size(110, 45);
            this.resetButton.TabIndex = 4;
            this.resetButton.Text = "Reset";
            this.resetButton.UseVisualStyleBackColor = true;
            this.resetButton.Click += new System.EventHandler(this.resetButton_Click);
            // 
            // stepButton
            // 
            this.stepButton.Location = new System.Drawing.Point(415, 533);
            this.stepButton.Name = "stepButton";
            this.stepButton.Size = new System.Drawing.Size(110, 45);
            this.stepButton.TabIndex = 5;
            this.stepButton.Text = "Step";
            this.stepButton.UseVisualStyleBackColor = true;
            this.stepButton.Click += new System.EventHandler(this.stepButton_Click);
            // 
            // mainTimer
            // 
            this.mainTimer.Interval = 750;
            this.mainTimer.Tick += new System.EventHandler(this.mainTimer_Tick);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1117, 590);
            this.Controls.Add(this.stepButton);
            this.Controls.Add(this.resetButton);
            this.Controls.Add(this.runButton);
            this.Controls.Add(this.internalInfo);
            this.Controls.Add(this.programText);
            this.Controls.Add(this.Display);
            this.Name = "MainWindow";
            this.Text = "PDP-11 Emulator";
            this.Load += new System.EventHandler(this.MainWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.Display)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox Display;
        private System.Windows.Forms.ListView programText;
        private System.Windows.Forms.TextBox internalInfo;
        private System.Windows.Forms.Button runButton;
        private System.Windows.Forms.Button resetButton;
        private System.Windows.Forms.Button stepButton;
        private System.Windows.Forms.Timer mainTimer;

    }
}

