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

namespace PdpGUI
{
    public partial class MainWindow : Form
    {
        //[DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern bool pdpReset();
        //[DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern int getIndexOfCurrentInstruction();

        Dictionary<string, int> dictionary =
	    new Dictionary<string, int>();

        public MainWindow()
        {
            InitializeComponent();
            initProgramText();
            initProcInfo();
        }

        private void initProgramText()
        {
            programText.View = View.Details;
            programText.Columns.Add("#", -2, HorizontalAlignment.Left);
            programText.Columns.Add("Command", -2, HorizontalAlignment.Left);
            // getNumberOfCommands();
            // getCommands();
            for (int i = 0; i < 300; i++)
            {
                var item = new ListViewItem(new[] { "line number", "command" });
                programText.Items.Add(item);
            }
        }

        private void initProcInfo()
        {
            procInfo.View = View.Details;
            procInfo.Columns.Add("Registers", 284, HorizontalAlignment.Left);
            procInfo.Columns.Add("Flags", 284, HorizontalAlignment.Left);
            // getRegisters: (R0: 2) - for example
            // getFlags: (OF: True) - for example
            for (int i = 0; i < 8; i++)
            {
                var item = new ListViewItem(new[] { "some register", "some flag" });
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

    }
}
