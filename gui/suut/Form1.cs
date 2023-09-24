using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using System.Diagnostics;
using System.Windows.Forms.DataVisualization.Charting;

namespace usb_gui
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
            timer1.Interval = 500;
            getAvailablePorts();
        }

        bool getAvailablePorts()
        {

            timer1.Stop();
            bool fail = false;
            this.Text = this.Text.Split('-')[0];
            this.Text = this.Text.Trim();
            groupBoxConnect.Visible = true;
            buttonRefresh.Visible = true;
            buttonRefresh.Enabled = true;
            comboBoxAvailablePorts.Items.Clear();
            string[] ports = SerialPort.GetPortNames();

            string portName = serialPort1.PortName;

            // the ports list contains the current port, but the
            // current port close (for some reason). Check to see
            // if the port can be opened. If its not the mark it
            // as not connected.
            bool openSuccess = true;
            if (ports.Contains(portName))
            {
                serialPort1.Close();
                openSuccess = OpenSerialPort(portName);
                if (openSuccess)
                {
                    serialPort1.Close();
                }
                else
                {
                    int i = Array.IndexOf(ports, portName);
                    ports[i] += " Not Connected";
                    fail = true;
                }
            }

            int portsCount = ports.Count();
            if (portsCount == 0)
            {
                Array.Resize(ref ports, 1);    
                ports[0] = "No Ports Found";
                fail = true;
            }
            comboBoxAvailablePorts.Items.AddRange(ports);
            comboBoxAvailablePorts.SelectedIndex = 0;
            buttonConnect.Visible = (portsCount > 1) || (portsCount == 1 && openSuccess);
            bool success = !fail;


            return success;
        }

        void restartApp(String msg = "Connection failure")
        {
            if (msg != "")
            {
                MessageBox.Show("Error: " + msg);
            }
            Application.Restart();
            Environment.Exit(0);

            //Environment.Exit(1);
            // getAvailablePorts();
        }


        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        
        private bool OpenSerialPort(string portName)
        {
            bool success = false;
            try
            {
                serialPort1.PortName = portName;
                serialPort1.BaudRate = Int32.Parse(comboBoxBaudRate.Text);  // 115200; // 9600;
                serialPort1.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceived);
                serialPort1.Open();
                success = true;
            }
            catch (UnauthorizedAccessException)
            {
                success = false;
            }
            catch (IOException)
            {
                success = false;
                restartApp("Failed to open port");
            }
            return success;
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            string portName = comboBoxAvailablePorts.Text;
            bool success = OpenSerialPort(portName);
            if (success)
            {
                textBoxConsole.Enabled = true;
                textBoxConsole.AppendText("Connected to " + portName + ", waiting for rx input..." + Environment.NewLine);
                this.Text += " - " + portName;
            }
        }

        private bool sendCommandLine(string cmd = "")
        {
            if (cmd == "")
            {
                cmd = commandLine.Text;
            }

            if (cmd == "") { return true; }

            try
            {
                Console.WriteLine("CMD> " + cmd);
                string newline = "\n";
                if (comboBoxNewLine.Text.Contains("r") && comboBoxNewLine.Text.Contains("n"))
                {
                    newline = "\r\n";
                } else if (comboBoxNewLine.Text.Contains("r")) {
                    newline = "\r";
                }
                serialPort1.Write(cmd + newline);
            }
            catch
            {
                restartApp("");
                //restartApp("Failed writing to port");
            }

            commandLine.Text = "";
            return true;
        }

        private void handleSend()
        {
            sendCommandLine();
        }

        private void buttonSend_Click(object sender, EventArgs e)
        {
            handleSend();
        }


        private void commandLine_TextChanged(object sender, EventArgs e)
        {
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            String rxStr = serialPort1.ReadExisting();
            rxStr = rxStr.Replace("\r\n", "\n");
            rxStr = rxStr.Replace("\n\r", "\n");
            rxStr = rxStr.Replace("\r", "\n");
            rxStr = rxStr.Replace("\n", Environment.NewLine);

            Console.WriteLine(rxStr);
            textBoxConsole.Invoke((MethodInvoker)delegate
            {
                textBoxConsole.Text += rxStr;
                textBoxConsole.SelectionStart = textBoxConsole.Text.Length;
                textBoxConsole.ScrollToCaret();
            });
        }


        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            bool success = getAvailablePorts();
        }


        private void timer1_Tick_1(object sender, EventArgs e)
        {
            timer1.Start();
        }

 
        private void commandLine_Enter(object sender, EventArgs e)
        {
            timer1.Stop();
        }


        private void groupBoxConsole_Enter(object sender, EventArgs e)
        {

        }

  
        private void commandLine_KeyPress_1(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Return)
            {
                handleSend();
            }
        }


        private void comboBoxAvailablePorts_DropDown(object sender, EventArgs e)
        {
            bool success = getAvailablePorts();
        }


        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            textBoxConsole.Clear();
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void buttonOpenScript_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog
            {
                InitialDirectory = @".",
                Title = "Select Script",

                CheckFileExists = true,
                CheckPathExists = true,

                DefaultExt = "txt",
                Filter = "txt files (*.txt)|*.txt",
                FilterIndex = 2,
                RestoreDirectory = true,

                ReadOnlyChecked = true,
                ShowReadOnly = true
            };

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                comboBoxScript.Items.Add(openFileDialog1.FileName);
                comboBoxScript.Text = openFileDialog1.FileName;
                // show tail end of long path+filename
                comboBoxScript.SelectionStart = comboBoxScript.Text.Length;
                comboBoxScript.SelectionLength = 0;

            }

        }

        private void comboBoxScript_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private string[] slurpFile(string filename)
        {
            string[] lines = { };
            try
            {
                lines = File.ReadAllLines(filename);
            }
            catch (IOException)
            {
            }
            return lines;
        }

        private void buttonRunScript_Click(object sender, EventArgs e)
        {
            string filename = comboBoxScript.Text;
            string[] lines = slurpFile(filename);
            foreach (string line in lines)
            {
                sendCommandLine(line.Trim());
                System.Threading.Thread.Sleep(50);
            }
        }
    }
}
