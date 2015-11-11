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

        Dictionary<string, int> dictionary =
	    new Dictionary<string, int>();

        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetData();

        public MainWindow()
        {
            InitializeComponent();
            initInterface();
            initProgramText();
            initProcInfo();
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

        private void initProgramText()
        {
            // getNumberOfCommands();
            // getCommands();
           /* for (int i = 0; i < 300; i++)
            {
                var item = new ListViewItem(new[] { "line number", "command" });
                programText.Items.Add(item);
            }*/
        }

        private void initProcInfo()
        {

            // getRegisters: (R0: 2) - for example
            // getFlags: (OF: True) - for example
            // IIITNZVC
            string[] flagNames = {"", "", "", "", "N", "Z", "V", "C"};
            string register, flag;
            StringBuilder valueOfRegister;
            for (int i = 0; i < 8; i++)
            {
                register = "R" + i.ToString() + " = " + "";
                flag = flagNames[i];
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
            int i = getIndexOfCurrentInstruction();
            programText.Select();
            programText.Items[i].Selected = true;
            programText.EnsureVisible(i);
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
