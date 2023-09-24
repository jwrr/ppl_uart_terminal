# suut

SUITABLE USB UART TERMINAL GUI SOFTWARE
---------------------------------------

The terminal GUI is written in C# using WinForms. To run the GUI start Visual Studio 
(It has been tested using Microsoft Visual Studio Community 2022 (64-bit)).
* Click "Open a project or solution"
* open  suut.sln
* Click "Start". This will compile and run the GUI.
* In the GUI's configuration pane, select the appropriate Port, Baud Rate and
  Newline sequence.
* Enter lines to send to the remote device using the Send Dialog box, and
  monitor the responses with the Console read-only box.

![suut screenshot](./img/suut.png)

Configuration
-------------
SUUT isn't too configurable with just a few settings.

* Port - The program scans for open ports and presents a drop-down selection
  menu. If there are multiple ports, a simple way to identify your port is to
  disconnect your device, hit refresh, re-plug in your device and hit refresh 
  again to see which port was added.
* Baud Rate - SUUT allows you to select baud rates of 115200 and 9600. These 
  are the two most common rates. Typically USB devices can support 115200.
* Newline Sequence - Your UART device may want a LF (\n), CR (\r) or CR+LF (\r\n)
  at the end of each line. PuTTY defaults to CR (\r) and other terminals default
  to LF (\n). C# (.NET) defaults to CR+LF (\r\n) on Windows and LF (\n) on Linux.

End of Line Characters
----------------------
When receiving data, SUUT converts several variations, including LF, CR and
CR+LF to Environment.NewLine, which is CR+LF (\r\n) on Windows and LF (\n) on
Linux.

Hacking
-------

* **Add a default port** - Open 'Form1.cs [Design]', right-click on the port
  selection textbox and pick properties. Change the 'Text' property.
  
* **Add another Baud Rate** - Edit 'Form1.Designer.cs', search for 9600 and add
  the new baud rates.
  
```cpp
    this.comboBoxBaudRate.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
    this.comboBoxBaudRate.FormattingEnabled = true;
    this.comboBoxBaudRate.Items.AddRange(new object[] {
    "115200",
    "9600"});
    this.comboBoxBaudRate.Location = new System.Drawing.Point(91, 66);
    this.comboBoxBaudRate.Margin = new System.Windows.Forms.Padding(2);
    this.comboBoxBaudRate.Name = "comboBoxBaudRate";
    this.comboBoxBaudRate.Size = new System.Drawing.Size(254, 25);
```

* **Change default Newline** - Open 'Form1.cs [Design]', right-click on the
  Newline textbox and pick properties. Change the 'Text' property.
