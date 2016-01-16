using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Data.Odbc;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Windows.Forms;

namespace PdpGUI
{
    public partial class MainWindow : Form
    {
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetVideoBuffer(IntPtr str);
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetRegisters(IntPtr ptr);
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern byte GetFlags();
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetCurrentInstruction(StringBuilder ptr);
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetInstructionNumber();
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetAllInstructions(IntPtr pInstructions);
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int PerformStep();
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PerformProgram();
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ResetProgram();
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetNextInstructions(StringBuilder ptr);

        // Global State
        const long interval = 10;
        const int numberOfNextInstructions = 5;
        const int lenInstructions = numberOfNextInstructions * 60;
        bool isExec = false;
        //
        IntPtr valueOfRegisters = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(Int32)) * 8);
        byte valueOfFlag;

        //StringBuilder nextInstructions = new StringBuilder(lenInstructions);

        StringBuilder currentInstruction = new StringBuilder(60);
        int currentInstructionNumber = 0;
        // Display
        static Rectangle displayBorders = new Rectangle(0, 0, 512, 256);
        Bitmap displayImage = new Bitmap(displayBorders.Width, displayBorders.Height, PixelFormat.Format1bppIndexed);
        IntPtr videoMemory = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(byte)) * displayBorders.Width * displayBorders.Height / 8);

        private readonly MicroLibrary.MicroTimer _microTimer;

        private void OnTimedEvent(object sender, MicroLibrary.MicroTimerEventArgs timerEventArgs)
        {
            doStep();
        }

        public MainWindow()
        {
            InitializeComponent();
            _microTimer = new MicroLibrary.MicroTimer();
            _microTimer.MicroTimerElapsed +=
                new MicroLibrary.MicroTimer.MicroTimerElapsedEventHandler(OnTimedEvent);

            screenUpdate.Start();
            initInterface();
            _microTimer.Interval = interval;
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            Display.Image = displayImage;
        }

        private void initInterface()
        {
            // Display
            this.Controls.Add(Display);
            // ProgramText
            programText.View = View.Details;
            programText.Columns.Add("#", 50, HorizontalAlignment.Left);
            programText.Columns.Add("Command", 400, HorizontalAlignment.Left);
            // Proc
            procInfo.View = View.Details;
            procInfo.Columns.Add("Registers", 237, HorizontalAlignment.Left);
            procInfo.Columns.Add("Flags", 237, HorizontalAlignment.Left);
        }

        private void addNextInstructionInProgramText()
        {
            var item = new ListViewItem(new[] { currentInstructionNumber.ToString(), currentInstruction.ToString() });
            programText.Items.Add(item);
            programText.Select();
            programText.Items[currentInstructionNumber].Selected = true;
            programText.EnsureVisible(currentInstructionNumber++);
        }

        private void fillProcInfo()
        {
            for (int i = procInfo.Items.Count - 1; i >= 0; i--)
            {
                procInfo.Items[i].Remove();
            }
            string[] flagNames = { "", "", "", "", "N", "Z", "V", "C" };
            string register, flag;
            Int32[] valueOfRegistersInInts = new Int32[8];
            Marshal.Copy(valueOfRegisters, valueOfRegistersInInts, 0, 8);
            for (int i = 0; i < 8; i++)
            {
                register = "R" + i.ToString() + " = " + ((UInt16)valueOfRegistersInInts[i]).ToString();
                flag = flagNames[i];
                if (i >= 4)
                    flag += " = " + ((valueOfFlag >> (8 - i)) & 1);
                var item = new ListViewItem(new[] { register, flag });
                procInfo.Items.Add(item);
            }
        }

        // Main Loop
        private void doStep()
        {
            if (PerformStep() == 1)
            {
                _microTimer.Stop();
                BeginInvoke((MethodInvoker)delegate
                {
                    state.Text = "Stop";
                    isExec = true;
                });
            }
            //Debug.WriteLine(currentInstruction);
            GetCurrentInstruction(currentInstruction);
            GetRegisters(valueOfRegisters);
            valueOfFlag = GetFlags();
        }

        private void fillInfo()
        {
            addNextInstructionInProgramText();
            fillProcInfo();
        }

        // Buttons
        private void runButton_Click(object sender, EventArgs e)
        {
            if (isExec) { return; }
            state.Text = "Running...";
            _microTimer.Start();
        }

        private void resetButton_Click(object sender, EventArgs e)
        {
            ResetProgram();
            isExec = false;
        }

        private void stepButton_Click(object sender, EventArgs e)
        {
            if (isExec) { return; }
            doStep();
            fillInfo();
        }

        private void stopButton_Click(object sender, EventArgs e)
        {
            if (isExec) { return; }
            _microTimer.Stop();
            state.Text = "Stop";
        }

        // Update Screen
        private void screenUpdate_Tick(object sender, EventArgs e)
        {
            GetVideoBuffer(videoMemory);
            int bytes = displayBorders.Width * displayBorders.Height / 8;
            byte[] managedArray = new byte[bytes];
            Marshal.Copy(videoMemory, managedArray, 0, bytes);
            System.Drawing.Imaging.BitmapData bmpData = displayImage.LockBits(displayBorders, 
                                                                              System.Drawing.Imaging.ImageLockMode.ReadWrite, 
                                                                              displayImage.PixelFormat);
            IntPtr ptr2 = bmpData.Scan0;
            Marshal.Copy(managedArray, 0, ptr2, bytes);
            displayImage.UnlockBits(bmpData);
            Display.Image = displayImage;
        }

        // Additional functions
        private void programText_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            e.Cancel = true;
            e.NewWidth = programText.Columns[e.ColumnIndex].Width;
        }

        private void procInfo_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            e.Cancel = true;
            e.NewWidth = procInfo.Columns[e.ColumnIndex].Width;
        }
    }
}
