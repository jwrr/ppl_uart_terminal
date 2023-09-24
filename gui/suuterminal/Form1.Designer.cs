namespace usb_gui
{
    partial class Form1
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
            this.comboBoxAvailablePorts = new System.Windows.Forms.ComboBox();
            this.commandLine = new System.Windows.Forms.TextBox();
            this.buttonSend = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.buttonConnect = new System.Windows.Forms.Button();
            this.groupBoxConnect = new System.Windows.Forms.GroupBox();
            this.buttonRunScript = new System.Windows.Forms.Button();
            this.buttonOpenScript = new System.Windows.Forms.Button();
            this.comboBoxScript = new System.Windows.Forms.ComboBox();
            this.buttonClear = new System.Windows.Forms.Button();
            this.comboBoxNewLine = new System.Windows.Forms.ComboBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.comboBoxBaudRate = new System.Windows.Forms.ComboBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.toolTipTrigger = new System.Windows.Forms.ToolTip(this.components);
            this.groupBoxConsole = new System.Windows.Forms.GroupBox();
            this.textBoxConsole = new System.Windows.Forms.TextBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.textBoxScratch = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonRunScratch = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.textBox7 = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.comboBox3 = new System.Windows.Forms.ComboBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.comboBox4 = new System.Windows.Forms.ComboBox();
            this.textBox8 = new System.Windows.Forms.TextBox();
            this.comboBox5 = new System.Windows.Forms.ComboBox();
            this.textBox9 = new System.Windows.Forms.TextBox();
            this.textBox10 = new System.Windows.Forms.TextBox();
            this.button4 = new System.Windows.Forms.Button();
            this.comboBox6 = new System.Windows.Forms.ComboBox();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.comboBox7 = new System.Windows.Forms.ComboBox();
            this.textBox11 = new System.Windows.Forms.TextBox();
            this.comboBox8 = new System.Windows.Forms.ComboBox();
            this.textBox12 = new System.Windows.Forms.TextBox();
            this.textBox13 = new System.Windows.Forms.TextBox();
            this.button7 = new System.Windows.Forms.Button();
            this.comboBox9 = new System.Windows.Forms.ComboBox();
            this.button8 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.groupBoxScriptsAndSnippets = new System.Windows.Forms.GroupBox();
            this.buttonLoadSnippet = new System.Windows.Forms.Button();
            this.groupBoxConnect.SuspendLayout();
            this.groupBoxConsole.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBoxScriptsAndSnippets.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBoxAvailablePorts
            // 
            this.comboBoxAvailablePorts.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBoxAvailablePorts.FormattingEnabled = true;
            this.comboBoxAvailablePorts.Location = new System.Drawing.Point(90, 85);
            this.comboBoxAvailablePorts.Margin = new System.Windows.Forms.Padding(2);
            this.comboBoxAvailablePorts.Name = "comboBoxAvailablePorts";
            this.comboBoxAvailablePorts.Size = new System.Drawing.Size(254, 25);
            this.comboBoxAvailablePorts.TabIndex = 0;
            this.comboBoxAvailablePorts.DropDown += new System.EventHandler(this.comboBoxAvailablePorts_DropDown);
            this.comboBoxAvailablePorts.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // commandLine
            // 
            this.commandLine.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.commandLine.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.commandLine.Location = new System.Drawing.Point(20, 844);
            this.commandLine.Margin = new System.Windows.Forms.Padding(2);
            this.commandLine.Name = "commandLine";
            this.commandLine.Size = new System.Drawing.Size(859, 26);
            this.commandLine.TabIndex = 2;
            this.commandLine.TextChanged += new System.EventHandler(this.commandLine_TextChanged);
            this.commandLine.Enter += new System.EventHandler(this.commandLine_Enter);
            this.commandLine.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.commandLine_KeyPress_1);
            // 
            // buttonSend
            // 
            this.buttonSend.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSend.BackColor = System.Drawing.Color.Gray;
            this.buttonSend.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonSend.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonSend.Location = new System.Drawing.Point(882, 844);
            this.buttonSend.Margin = new System.Windows.Forms.Padding(2);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Size = new System.Drawing.Size(76, 31);
            this.buttonSend.TabIndex = 3;
            this.buttonSend.Text = "Send";
            this.buttonSend.UseVisualStyleBackColor = false;
            this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // buttonConnect
            // 
            this.buttonConnect.BackColor = System.Drawing.Color.Gray;
            this.buttonConnect.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonConnect.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonConnect.Location = new System.Drawing.Point(124, 17);
            this.buttonConnect.Margin = new System.Windows.Forms.Padding(2);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(103, 58);
            this.buttonConnect.TabIndex = 14;
            this.buttonConnect.Text = "CONNECT TO PORT";
            this.buttonConnect.UseVisualStyleBackColor = false;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // groupBoxConnect
            // 
            this.groupBoxConnect.Controls.Add(this.groupBox4);
            this.groupBoxConnect.Controls.Add(this.groupBox2);
            this.groupBoxConnect.Controls.Add(this.groupBox1);
            this.groupBoxConnect.Controls.Add(this.comboBoxNewLine);
            this.groupBoxConnect.Controls.Add(this.textBox3);
            this.groupBoxConnect.Controls.Add(this.comboBoxBaudRate);
            this.groupBoxConnect.Controls.Add(this.textBox2);
            this.groupBoxConnect.Controls.Add(this.textBox1);
            this.groupBoxConnect.Controls.Add(this.buttonRefresh);
            this.groupBoxConnect.Controls.Add(this.comboBoxAvailablePorts);
            this.groupBoxConnect.Controls.Add(this.buttonClear);
            this.groupBoxConnect.Controls.Add(this.buttonConnect);
            this.groupBoxConnect.Location = new System.Drawing.Point(4, 2);
            this.groupBoxConnect.Margin = new System.Windows.Forms.Padding(2);
            this.groupBoxConnect.Name = "groupBoxConnect";
            this.groupBoxConnect.Padding = new System.Windows.Forms.Padding(2);
            this.groupBoxConnect.Size = new System.Drawing.Size(363, 212);
            this.groupBoxConnect.TabIndex = 15;
            this.groupBoxConnect.TabStop = false;
            this.groupBoxConnect.Text = "Connect";
            // 
            // buttonRunScript
            // 
            this.buttonRunScript.BackColor = System.Drawing.Color.Gray;
            this.buttonRunScript.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonRunScript.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonRunScript.Location = new System.Drawing.Point(231, 78);
            this.buttonRunScript.Margin = new System.Windows.Forms.Padding(2);
            this.buttonRunScript.Name = "buttonRunScript";
            this.buttonRunScript.Size = new System.Drawing.Size(115, 52);
            this.buttonRunScript.TabIndex = 27;
            this.buttonRunScript.Text = "  RUN   SCRIPT";
            this.buttonRunScript.UseVisualStyleBackColor = false;
            this.buttonRunScript.Click += new System.EventHandler(this.buttonRunScript_Click);
            // 
            // buttonOpenScript
            // 
            this.buttonOpenScript.BackColor = System.Drawing.Color.Gray;
            this.buttonOpenScript.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonOpenScript.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonOpenScript.Location = new System.Drawing.Point(17, 18);
            this.buttonOpenScript.Margin = new System.Windows.Forms.Padding(0);
            this.buttonOpenScript.Name = "buttonOpenScript";
            this.buttonOpenScript.Padding = new System.Windows.Forms.Padding(3);
            this.buttonOpenScript.Size = new System.Drawing.Size(69, 56);
            this.buttonOpenScript.TabIndex = 26;
            this.buttonOpenScript.Text = "OPEN FILE";
            this.buttonOpenScript.UseVisualStyleBackColor = false;
            this.buttonOpenScript.Click += new System.EventHandler(this.buttonOpenScript_Click);
            // 
            // comboBoxScript
            // 
            this.comboBoxScript.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBoxScript.FormattingEnabled = true;
            this.comboBoxScript.Items.AddRange(new object[] {
            "\\r",
            "\\n",
            "\\r\\n"});
            this.comboBoxScript.Location = new System.Drawing.Point(90, 33);
            this.comboBoxScript.Margin = new System.Windows.Forms.Padding(2);
            this.comboBoxScript.Name = "comboBoxScript";
            this.comboBoxScript.Size = new System.Drawing.Size(254, 26);
            this.comboBoxScript.TabIndex = 25;
            this.comboBoxScript.SelectedIndexChanged += new System.EventHandler(this.comboBoxScript_SelectedIndexChanged);
            // 
            // buttonClear
            // 
            this.buttonClear.BackColor = System.Drawing.Color.Gray;
            this.buttonClear.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonClear.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonClear.Location = new System.Drawing.Point(231, 17);
            this.buttonClear.Margin = new System.Windows.Forms.Padding(2);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(115, 58);
            this.buttonClear.TabIndex = 23;
            this.buttonClear.Text = "CLEAR CONSOLE";
            this.buttonClear.UseVisualStyleBackColor = false;
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // comboBoxNewLine
            // 
            this.comboBoxNewLine.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBoxNewLine.FormattingEnabled = true;
            this.comboBoxNewLine.Items.AddRange(new object[] {
            "\\r",
            "\\n",
            "\\r\\n"});
            this.comboBoxNewLine.Location = new System.Drawing.Point(90, 168);
            this.comboBoxNewLine.Margin = new System.Windows.Forms.Padding(2);
            this.comboBoxNewLine.Name = "comboBoxNewLine";
            this.comboBoxNewLine.Size = new System.Drawing.Size(254, 25);
            this.comboBoxNewLine.TabIndex = 22;
            this.comboBoxNewLine.Text = "\\r (CR = PuTTY\'s default)";
            this.comboBoxNewLine.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged_1);
            // 
            // textBox3
            // 
            this.textBox3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox3.Location = new System.Drawing.Point(17, 168);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(68, 24);
            this.textBox3.TabIndex = 21;
            this.textBox3.Text = "Newline";
            this.textBox3.TextChanged += new System.EventHandler(this.textBox3_TextChanged);
            // 
            // comboBoxBaudRate
            // 
            this.comboBoxBaudRate.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBoxBaudRate.FormattingEnabled = true;
            this.comboBoxBaudRate.Items.AddRange(new object[] {
            "115200",
            "9600"});
            this.comboBoxBaudRate.Location = new System.Drawing.Point(90, 129);
            this.comboBoxBaudRate.Margin = new System.Windows.Forms.Padding(2);
            this.comboBoxBaudRate.Name = "comboBoxBaudRate";
            this.comboBoxBaudRate.Size = new System.Drawing.Size(254, 25);
            this.comboBoxBaudRate.TabIndex = 20;
            this.comboBoxBaudRate.Text = "115200";
            // 
            // textBox2
            // 
            this.textBox2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox2.Location = new System.Drawing.Point(17, 129);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(68, 24);
            this.textBox2.TabIndex = 19;
            this.textBox2.Text = "Baud";
            this.textBox2.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // textBox1
            // 
            this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox1.Location = new System.Drawing.Point(17, 86);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(68, 24);
            this.textBox1.TabIndex = 18;
            this.textBox1.Text = "Port";
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.BackColor = System.Drawing.Color.Gray;
            this.buttonRefresh.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonRefresh.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonRefresh.Location = new System.Drawing.Point(17, 17);
            this.buttonRefresh.Margin = new System.Windows.Forms.Padding(2);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(103, 58);
            this.buttonRefresh.TabIndex = 15;
            this.buttonRefresh.Text = "REFRESH PORT LIST";
            this.buttonRefresh.UseVisualStyleBackColor = false;
            this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick_1);
            // 
            // groupBoxConsole
            // 
            this.groupBoxConsole.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxConsole.Controls.Add(this.commandLine);
            this.groupBoxConsole.Controls.Add(this.textBoxConsole);
            this.groupBoxConsole.Controls.Add(this.buttonSend);
            this.groupBoxConsole.Location = new System.Drawing.Point(382, 2);
            this.groupBoxConsole.Margin = new System.Windows.Forms.Padding(2);
            this.groupBoxConsole.Name = "groupBoxConsole";
            this.groupBoxConsole.Padding = new System.Windows.Forms.Padding(2);
            this.groupBoxConsole.Size = new System.Drawing.Size(972, 883);
            this.groupBoxConsole.TabIndex = 27;
            this.groupBoxConsole.TabStop = false;
            this.groupBoxConsole.Text = "Console";
            this.groupBoxConsole.Enter += new System.EventHandler(this.groupBoxConsole_Enter);
            // 
            // textBoxConsole
            // 
            this.textBoxConsole.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxConsole.Location = new System.Drawing.Point(20, 17);
            this.textBoxConsole.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxConsole.Multiline = true;
            this.textBoxConsole.Name = "textBoxConsole";
            this.textBoxConsole.ReadOnly = true;
            this.textBoxConsole.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxConsole.Size = new System.Drawing.Size(953, 823);
            this.textBoxConsole.TabIndex = 4;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.DefaultExt = "txt";
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Title = "Open Script To Send";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // textBoxScratch
            // 
            this.textBoxScratch.AccessibleName = "Scratch";
            this.textBoxScratch.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxScratch.Location = new System.Drawing.Point(8, 147);
            this.textBoxScratch.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxScratch.Multiline = true;
            this.textBoxScratch.Name = "textBoxScratch";
            this.textBoxScratch.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxScratch.Size = new System.Drawing.Size(346, 512);
            this.textBoxScratch.TabIndex = 5;
            this.textBoxScratch.Text = "Type (or Load) sequence of commands to run";
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Location = new System.Drawing.Point(718, 441);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(229, 0);
            this.groupBox1.TabIndex = 28;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Scratch";
            // 
            // buttonRunScratch
            // 
            this.buttonRunScratch.BackColor = System.Drawing.Color.Gray;
            this.buttonRunScratch.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonRunScratch.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonRunScratch.Location = new System.Drawing.Point(124, 78);
            this.buttonRunScratch.Margin = new System.Windows.Forms.Padding(2);
            this.buttonRunScratch.Name = "buttonRunScratch";
            this.buttonRunScratch.Size = new System.Drawing.Size(103, 53);
            this.buttonRunScratch.TabIndex = 29;
            this.buttonRunScratch.Text = "RUN SNIPPET";
            this.buttonRunScratch.UseVisualStyleBackColor = false;
            this.buttonRunScratch.Click += new System.EventHandler(this.buttonRunScratch_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Controls.Add(this.comboBox1);
            this.groupBox2.Controls.Add(this.textBox5);
            this.groupBox2.Controls.Add(this.comboBox2);
            this.groupBox2.Controls.Add(this.textBox6);
            this.groupBox2.Controls.Add(this.textBox7);
            this.groupBox2.Controls.Add(this.button1);
            this.groupBox2.Controls.Add(this.comboBox3);
            this.groupBox2.Controls.Add(this.button2);
            this.groupBox2.Controls.Add(this.button3);
            this.groupBox2.Location = new System.Drawing.Point(0, 216);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox2.Size = new System.Drawing.Size(363, 311);
            this.groupBox2.TabIndex = 29;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Connect";
            // 
            // groupBox3
            // 
            this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox3.Location = new System.Drawing.Point(718, 441);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(229, 99);
            this.groupBox3.TabIndex = 28;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Scratch";
            // 
            // comboBox1
            // 
            this.comboBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "\\r",
            "\\n",
            "\\r\\n"});
            this.comboBox1.Location = new System.Drawing.Point(90, 168);
            this.comboBox1.Margin = new System.Windows.Forms.Padding(2);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(254, 25);
            this.comboBox1.TabIndex = 22;
            this.comboBox1.Text = "\\r (CR = PuTTY\'s default)";
            // 
            // textBox5
            // 
            this.textBox5.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox5.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox5.Location = new System.Drawing.Point(17, 168);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(68, 24);
            this.textBox5.TabIndex = 21;
            this.textBox5.Text = "Newline";
            // 
            // comboBox2
            // 
            this.comboBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "115200",
            "9600"});
            this.comboBox2.Location = new System.Drawing.Point(90, 129);
            this.comboBox2.Margin = new System.Windows.Forms.Padding(2);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(254, 25);
            this.comboBox2.TabIndex = 20;
            this.comboBox2.Text = "115200";
            // 
            // textBox6
            // 
            this.textBox6.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox6.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox6.Location = new System.Drawing.Point(17, 129);
            this.textBox6.Name = "textBox6";
            this.textBox6.Size = new System.Drawing.Size(68, 24);
            this.textBox6.TabIndex = 19;
            this.textBox6.Text = "Baud";
            // 
            // textBox7
            // 
            this.textBox7.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox7.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox7.Location = new System.Drawing.Point(17, 86);
            this.textBox7.Name = "textBox7";
            this.textBox7.Size = new System.Drawing.Size(68, 24);
            this.textBox7.TabIndex = 18;
            this.textBox7.Text = "Port";
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.Gray;
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button1.Location = new System.Drawing.Point(17, 17);
            this.button1.Margin = new System.Windows.Forms.Padding(2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(103, 58);
            this.button1.TabIndex = 15;
            this.button1.Text = "REFRESH PORT LIST";
            this.button1.UseVisualStyleBackColor = false;
            // 
            // comboBox3
            // 
            this.comboBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBox3.FormattingEnabled = true;
            this.comboBox3.Location = new System.Drawing.Point(90, 85);
            this.comboBox3.Margin = new System.Windows.Forms.Padding(2);
            this.comboBox3.Name = "comboBox3";
            this.comboBox3.Size = new System.Drawing.Size(254, 25);
            this.comboBox3.TabIndex = 0;
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.Gray;
            this.button2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button2.Location = new System.Drawing.Point(231, 17);
            this.button2.Margin = new System.Windows.Forms.Padding(2);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(115, 58);
            this.button2.TabIndex = 23;
            this.button2.Text = "CLEAR CONSOLE";
            this.button2.UseVisualStyleBackColor = false;
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.Color.Gray;
            this.button3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button3.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button3.Location = new System.Drawing.Point(124, 17);
            this.button3.Margin = new System.Windows.Forms.Padding(2);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(103, 58);
            this.button3.TabIndex = 14;
            this.button3.Text = "CONNECT TO PORT";
            this.button3.UseVisualStyleBackColor = false;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.groupBox5);
            this.groupBox4.Controls.Add(this.groupBox7);
            this.groupBox4.Controls.Add(this.comboBox7);
            this.groupBox4.Controls.Add(this.textBox11);
            this.groupBox4.Controls.Add(this.comboBox8);
            this.groupBox4.Controls.Add(this.textBox12);
            this.groupBox4.Controls.Add(this.textBox13);
            this.groupBox4.Controls.Add(this.button7);
            this.groupBox4.Controls.Add(this.comboBox9);
            this.groupBox4.Controls.Add(this.button8);
            this.groupBox4.Controls.Add(this.button9);
            this.groupBox4.Location = new System.Drawing.Point(8, 216);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox4.Size = new System.Drawing.Size(363, 320);
            this.groupBox4.TabIndex = 30;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Connect";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.groupBox6);
            this.groupBox5.Controls.Add(this.comboBox4);
            this.groupBox5.Controls.Add(this.textBox8);
            this.groupBox5.Controls.Add(this.comboBox5);
            this.groupBox5.Controls.Add(this.textBox9);
            this.groupBox5.Controls.Add(this.textBox10);
            this.groupBox5.Controls.Add(this.button4);
            this.groupBox5.Controls.Add(this.comboBox6);
            this.groupBox5.Controls.Add(this.button5);
            this.groupBox5.Controls.Add(this.button6);
            this.groupBox5.Location = new System.Drawing.Point(0, 216);
            this.groupBox5.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox5.Size = new System.Drawing.Size(363, 311);
            this.groupBox5.TabIndex = 29;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Connect";
            // 
            // groupBox6
            // 
            this.groupBox6.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox6.Location = new System.Drawing.Point(718, 441);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(229, 99);
            this.groupBox6.TabIndex = 28;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Scratch";
            // 
            // comboBox4
            // 
            this.comboBox4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBox4.FormattingEnabled = true;
            this.comboBox4.Items.AddRange(new object[] {
            "\\r",
            "\\n",
            "\\r\\n"});
            this.comboBox4.Location = new System.Drawing.Point(90, 168);
            this.comboBox4.Margin = new System.Windows.Forms.Padding(2);
            this.comboBox4.Name = "comboBox4";
            this.comboBox4.Size = new System.Drawing.Size(254, 25);
            this.comboBox4.TabIndex = 22;
            this.comboBox4.Text = "\\r (CR = PuTTY\'s default)";
            // 
            // textBox8
            // 
            this.textBox8.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox8.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox8.Location = new System.Drawing.Point(17, 168);
            this.textBox8.Name = "textBox8";
            this.textBox8.Size = new System.Drawing.Size(68, 24);
            this.textBox8.TabIndex = 21;
            this.textBox8.Text = "Newline";
            // 
            // comboBox5
            // 
            this.comboBox5.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBox5.FormattingEnabled = true;
            this.comboBox5.Items.AddRange(new object[] {
            "115200",
            "9600"});
            this.comboBox5.Location = new System.Drawing.Point(90, 129);
            this.comboBox5.Margin = new System.Windows.Forms.Padding(2);
            this.comboBox5.Name = "comboBox5";
            this.comboBox5.Size = new System.Drawing.Size(254, 25);
            this.comboBox5.TabIndex = 20;
            this.comboBox5.Text = "115200";
            // 
            // textBox9
            // 
            this.textBox9.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox9.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox9.Location = new System.Drawing.Point(17, 129);
            this.textBox9.Name = "textBox9";
            this.textBox9.Size = new System.Drawing.Size(68, 24);
            this.textBox9.TabIndex = 19;
            this.textBox9.Text = "Baud";
            // 
            // textBox10
            // 
            this.textBox10.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox10.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox10.Location = new System.Drawing.Point(17, 86);
            this.textBox10.Name = "textBox10";
            this.textBox10.Size = new System.Drawing.Size(68, 24);
            this.textBox10.TabIndex = 18;
            this.textBox10.Text = "Port";
            // 
            // button4
            // 
            this.button4.BackColor = System.Drawing.Color.Gray;
            this.button4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button4.Location = new System.Drawing.Point(17, 17);
            this.button4.Margin = new System.Windows.Forms.Padding(2);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(103, 58);
            this.button4.TabIndex = 15;
            this.button4.Text = "REFRESH PORT LIST";
            this.button4.UseVisualStyleBackColor = false;
            // 
            // comboBox6
            // 
            this.comboBox6.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBox6.FormattingEnabled = true;
            this.comboBox6.Location = new System.Drawing.Point(90, 85);
            this.comboBox6.Margin = new System.Windows.Forms.Padding(2);
            this.comboBox6.Name = "comboBox6";
            this.comboBox6.Size = new System.Drawing.Size(254, 25);
            this.comboBox6.TabIndex = 0;
            // 
            // button5
            // 
            this.button5.BackColor = System.Drawing.Color.Gray;
            this.button5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button5.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button5.Location = new System.Drawing.Point(231, 17);
            this.button5.Margin = new System.Windows.Forms.Padding(2);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(115, 58);
            this.button5.TabIndex = 23;
            this.button5.Text = "CLEAR CONSOLE";
            this.button5.UseVisualStyleBackColor = false;
            // 
            // button6
            // 
            this.button6.BackColor = System.Drawing.Color.Gray;
            this.button6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button6.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button6.Location = new System.Drawing.Point(124, 17);
            this.button6.Margin = new System.Windows.Forms.Padding(2);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(103, 58);
            this.button6.TabIndex = 14;
            this.button6.Text = "CONNECT TO PORT";
            this.button6.UseVisualStyleBackColor = false;
            // 
            // groupBox7
            // 
            this.groupBox7.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox7.Location = new System.Drawing.Point(718, 441);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(229, 108);
            this.groupBox7.TabIndex = 28;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Scratch";
            // 
            // comboBox7
            // 
            this.comboBox7.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBox7.FormattingEnabled = true;
            this.comboBox7.Items.AddRange(new object[] {
            "\\r",
            "\\n",
            "\\r\\n"});
            this.comboBox7.Location = new System.Drawing.Point(90, 168);
            this.comboBox7.Margin = new System.Windows.Forms.Padding(2);
            this.comboBox7.Name = "comboBox7";
            this.comboBox7.Size = new System.Drawing.Size(254, 25);
            this.comboBox7.TabIndex = 22;
            this.comboBox7.Text = "\\r (CR = PuTTY\'s default)";
            // 
            // textBox11
            // 
            this.textBox11.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox11.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox11.Location = new System.Drawing.Point(17, 168);
            this.textBox11.Name = "textBox11";
            this.textBox11.Size = new System.Drawing.Size(68, 24);
            this.textBox11.TabIndex = 21;
            this.textBox11.Text = "Newline";
            // 
            // comboBox8
            // 
            this.comboBox8.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBox8.FormattingEnabled = true;
            this.comboBox8.Items.AddRange(new object[] {
            "115200",
            "9600"});
            this.comboBox8.Location = new System.Drawing.Point(90, 129);
            this.comboBox8.Margin = new System.Windows.Forms.Padding(2);
            this.comboBox8.Name = "comboBox8";
            this.comboBox8.Size = new System.Drawing.Size(254, 25);
            this.comboBox8.TabIndex = 20;
            this.comboBox8.Text = "115200";
            // 
            // textBox12
            // 
            this.textBox12.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox12.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox12.Location = new System.Drawing.Point(17, 129);
            this.textBox12.Name = "textBox12";
            this.textBox12.Size = new System.Drawing.Size(68, 24);
            this.textBox12.TabIndex = 19;
            this.textBox12.Text = "Baud";
            // 
            // textBox13
            // 
            this.textBox13.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox13.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox13.Location = new System.Drawing.Point(17, 86);
            this.textBox13.Name = "textBox13";
            this.textBox13.Size = new System.Drawing.Size(68, 24);
            this.textBox13.TabIndex = 18;
            this.textBox13.Text = "Port";
            // 
            // button7
            // 
            this.button7.BackColor = System.Drawing.Color.Gray;
            this.button7.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button7.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button7.Location = new System.Drawing.Point(17, 17);
            this.button7.Margin = new System.Windows.Forms.Padding(2);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(103, 58);
            this.button7.TabIndex = 15;
            this.button7.Text = "REFRESH PORT LIST";
            this.button7.UseVisualStyleBackColor = false;
            // 
            // comboBox9
            // 
            this.comboBox9.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBox9.FormattingEnabled = true;
            this.comboBox9.Location = new System.Drawing.Point(90, 85);
            this.comboBox9.Margin = new System.Windows.Forms.Padding(2);
            this.comboBox9.Name = "comboBox9";
            this.comboBox9.Size = new System.Drawing.Size(254, 25);
            this.comboBox9.TabIndex = 0;
            // 
            // button8
            // 
            this.button8.BackColor = System.Drawing.Color.Gray;
            this.button8.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button8.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button8.Location = new System.Drawing.Point(231, 17);
            this.button8.Margin = new System.Windows.Forms.Padding(2);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(115, 58);
            this.button8.TabIndex = 23;
            this.button8.Text = "CLEAR CONSOLE";
            this.button8.UseVisualStyleBackColor = false;
            // 
            // button9
            // 
            this.button9.BackColor = System.Drawing.Color.Gray;
            this.button9.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button9.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button9.Location = new System.Drawing.Point(124, 17);
            this.button9.Margin = new System.Windows.Forms.Padding(2);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(103, 58);
            this.button9.TabIndex = 14;
            this.button9.Text = "CONNECT TO PORT";
            this.button9.UseVisualStyleBackColor = false;
            // 
            // groupBoxScriptsAndSnippets
            // 
            this.groupBoxScriptsAndSnippets.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.groupBoxScriptsAndSnippets.Controls.Add(this.buttonLoadSnippet);
            this.groupBoxScriptsAndSnippets.Controls.Add(this.buttonRunScratch);
            this.groupBoxScriptsAndSnippets.Controls.Add(this.textBoxScratch);
            this.groupBoxScriptsAndSnippets.Controls.Add(this.buttonRunScript);
            this.groupBoxScriptsAndSnippets.Controls.Add(this.buttonOpenScript);
            this.groupBoxScriptsAndSnippets.Controls.Add(this.comboBoxScript);
            this.groupBoxScriptsAndSnippets.Location = new System.Drawing.Point(4, 219);
            this.groupBoxScriptsAndSnippets.Name = "groupBoxScriptsAndSnippets";
            this.groupBoxScriptsAndSnippets.Size = new System.Drawing.Size(363, 666);
            this.groupBoxScriptsAndSnippets.TabIndex = 30;
            this.groupBoxScriptsAndSnippets.TabStop = false;
            this.groupBoxScriptsAndSnippets.Text = "Scripts and Snippets";
            // 
            // buttonLoadSnippet
            // 
            this.buttonLoadSnippet.BackColor = System.Drawing.Color.Gray;
            this.buttonLoadSnippet.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonLoadSnippet.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonLoadSnippet.Location = new System.Drawing.Point(17, 79);
            this.buttonLoadSnippet.Margin = new System.Windows.Forms.Padding(2);
            this.buttonLoadSnippet.Name = "buttonLoadSnippet";
            this.buttonLoadSnippet.Size = new System.Drawing.Size(103, 52);
            this.buttonLoadSnippet.TabIndex = 28;
            this.buttonLoadSnippet.Text = "LOAD SNIPPET";
            this.buttonLoadSnippet.UseVisualStyleBackColor = false;
            this.buttonLoadSnippet.Click += new System.EventHandler(this.buttonLoadSnippet_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1357, 889);
            this.Controls.Add(this.groupBoxScriptsAndSnippets);
            this.Controls.Add(this.groupBoxConsole);
            this.Controls.Add(this.groupBoxConnect);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "Form1";
            this.Text = "SUUTerminal";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBoxConnect.ResumeLayout(false);
            this.groupBoxConnect.PerformLayout();
            this.groupBoxConsole.ResumeLayout(false);
            this.groupBoxConsole.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBoxScriptsAndSnippets.ResumeLayout(false);
            this.groupBoxScriptsAndSnippets.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBoxAvailablePorts;
        private System.Windows.Forms.TextBox commandLine;
        private System.Windows.Forms.Button buttonSend;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.GroupBox groupBoxConnect;
        private System.Windows.Forms.Button buttonRefresh;

        private const string G_prompt = "=>";
        private string G_defaultFilename = "";
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ToolTip toolTipTrigger;
        private System.Windows.Forms.GroupBox groupBoxConsole;
        private System.Windows.Forms.TextBox textBoxConsole;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.ComboBox comboBoxNewLine;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.ComboBox comboBoxBaudRate;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.ComboBox comboBoxScript;
        private System.Windows.Forms.Button buttonRunScript;
        private System.Windows.Forms.Button buttonOpenScript;
        private System.Windows.Forms.TextBox textBoxScratch;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button buttonRunScratch;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.TextBox textBox6;
        private System.Windows.Forms.TextBox textBox7;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ComboBox comboBox3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.ComboBox comboBox4;
        private System.Windows.Forms.TextBox textBox8;
        private System.Windows.Forms.ComboBox comboBox5;
        private System.Windows.Forms.TextBox textBox9;
        private System.Windows.Forms.TextBox textBox10;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.ComboBox comboBox6;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.ComboBox comboBox7;
        private System.Windows.Forms.TextBox textBox11;
        private System.Windows.Forms.ComboBox comboBox8;
        private System.Windows.Forms.TextBox textBox12;
        private System.Windows.Forms.TextBox textBox13;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.ComboBox comboBox9;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.GroupBox groupBoxScriptsAndSnippets;
        private System.Windows.Forms.Button buttonLoadSnippet;
    }
}

