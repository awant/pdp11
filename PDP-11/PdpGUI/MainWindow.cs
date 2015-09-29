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
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)] 
        public static extern int Sum(int a, int b);
        [DllImport("PdpEmulator.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Sub(int a, int b);

        public MainWindow()
        {
            InitializeComponent();
            programText.Columns.Add("12");
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {

        }

        private void runButton_Click(object sender, EventArgs e)
        {

        }

        private void resetButton_Click(object sender, EventArgs e)
        {

        }

        private void stepButton_Click(object sender, EventArgs e)
        {

        }

        private void mainTimer_Tick(object sender, EventArgs e)
        {
            // This is the main loop
        }

    }
}
