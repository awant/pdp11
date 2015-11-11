using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;   // for using dll
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
        //[DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern bool pdpReset();
        //[DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern int getIndexOfCurrentInstruction();
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void test(StringBuilder str);
        //[DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern void GetVideoBuffer(StringBuilder str);
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetVideoBuffer(IntPtr str);
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ReleaseMemory(IntPtr ptr);


        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetRegisters(IntPtr ptr);
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern byte GetFlags();
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern byte GetCurrentInstruction(StringBuilder ptr);
        //[DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern IntPtr GetData();

        // Global State
        IntPtr valueOfRegisters = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(Int32)) * 8);
        byte valueOfFlag;
        StringBuilder currentInstruction = new StringBuilder(60);
        static int InstrNumber = 0;

        public MainWindow()
        {
            InitializeComponent();
            initInterface();
            //initProgramText();
            CreateBitmapAtRuntime();


            // Check getting data
            /*IntPtr ptr = GetData();
            IntPtr strPtr;
            for (int i = 0; i < 2; i++)
            {
                Console.WriteLine("i = " + i);
                strPtr = Marshal.ReadIntPtr(ptr);
                Console.WriteLine(Marshal.PtrToStringAnsi(strPtr));
                ptr += Marshal.SizeOf(typeof(IntPtr));
            }*/

            StringBuilder rntStr = new StringBuilder(4);
            test(rntStr);
            Debug.WriteLine(rntStr.ToString());
        }

        private void initInterface()
        {
            // ProgramText
            programText.View = View.Details;
            programText.Columns.Add("#", -2, HorizontalAlignment.Left);
            programText.Columns.Add("Command", -2, HorizontalAlignment.Left);
            // Proc
            procInfo.View = View.Details;
            procInfo.Columns.Add("Registers", 284, HorizontalAlignment.Left);
            procInfo.Columns.Add("Flags", 284, HorizontalAlignment.Left);
        }

        private void doStep()
        {
            GetCurrentInstruction(currentInstruction);
            GetRegisters(valueOfRegisters);
            valueOfFlag = GetFlags();
            fillProgramText();
            fillProcInfo();
        }

        private void fillProgramText()
        {
            // getNumberOfCommands();
            // getCommands();
            var item = new ListViewItem(new[] { InstrNumber.ToString(), currentInstruction.ToString() });
            programText.Items.Add(item);
            InstrNumber++;
        }

        private void fillProcInfo()
        {
            for (int i = procInfo.Items.Count - 1; i >= 0; i--)
            {
                procInfo.Items[i].Remove();
            }
            string[] flagNames = {"", "", "", "", "N", "Z", "V", "C"};
            string register, flag;
            Int32[] valueOfRegistersInInts = new Int32[8];
            Marshal.Copy(valueOfRegisters, valueOfRegistersInInts, 0, 8);
            for (int i = 0; i < 8; i++)
            {
                register = "R" + i.ToString() + " = " + ((UInt16)valueOfRegistersInInts[i]).ToString();
                flag = flagNames[i];
                if  (i >= 4)
                    flag += " = " + ((valueOfFlag >> (8 - i)) & 1);
                var item = new ListViewItem(new[] { register, flag });
                procInfo.Items.Add(item);
            }
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
        }

        private void runButton_Click(object sender, EventArgs e)
        {
            mainTimer.Start();
        }

        private void resetButton_Click(object sender, EventArgs e)
        {
            mainTimer.Stop();
            pdpReset();
        }

        private void stepButton_Click(object sender, EventArgs e)
        {
            step();
        }

        private void mainTimer_Tick(object sender, EventArgs e)
        {
            step();
        }

        // This is the main loop
        private void step()
        {
            //readNextInstruction();
            /*
            int i = getIndexOfCurrentInstruction();
            programText.Select();
            programText.Items[i].Selected = true;
            programText.EnsureVisible(i); */
            doStep();
        }

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

        // Funcions for realisation:
        int a = 0;
        int getIndexOfCurrentInstruction()
        {
            return a++;
        }

        void pdpReset()
        {
            a = 0;
        }

        //----------------------------------------------------------------------------
        public void CreateBitmapAtRuntime()
        {
            this.Controls.Add(Display);

            IntPtr videoMemory = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(byte)) * 512 * 256 / 8);
            GetVideoBuffer(videoMemory);
            int bytes = 512 * 256 / 8;

            byte[] managedArray = new byte[bytes];
            Marshal.Copy(videoMemory, managedArray, 0, bytes);
            Bitmap bmpImage = new Bitmap(512, 256, PixelFormat.Format1bppIndexed);
            Rectangle rect = new Rectangle(0, 0, 512, 256);
            System.Drawing.Imaging.BitmapData bmpData2 = bmpImage.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadWrite, bmpImage.PixelFormat);
            IntPtr ptr2 = bmpData2.Scan0;
            Marshal.Copy(managedArray, 0, ptr2, bytes);

            bmpImage.UnlockBits(bmpData2);

            Display.Image = bmpImage;
        }
        //----------------------------------------------------------------------------
    }
}
