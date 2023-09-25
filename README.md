# SUUTerminal

Sufficient USB UART TERMINAL GUI SOFTWARE
-----------------------------------------

SUUTerminal is written in C# using WinForms. It provides a USB UART serial
port interface. PuTTY is one of the leading terminal emulators.  I like PuTTY
and recommend it. But it doesn't support transmitting files, which is what
I need to script and automate test plans and command sequences. So I wrote
SUUTerminal, which is a pretty barebones terminal emulator that can send file
contents to the remote device. It doesn't do much more than that, but it's 
sufficient for my needs. Hence the name, Sufficient USB UART Terminal.

You can run SUUTerminal from Visual Studio with the following steps. I use
Microsoft Visual Studio Community 2022 (64-bit), but I didn't do anything
clever, so it should be portable to other versions. I would like to evenually 
try it on Linux with Mono.

* Use the Windows File Explorer (the folder icon) to navigate to the project's
  `gui` folder, and double-click on `suuterminal.sln`. This should open Visual
  Studio.
* Click "Start" green-triangle icon to build and run SUUTerminal.
* In SUUTerminal's configuration panel, select the appropriate Port, Baud Rate
  and Newline sequence.
* Press the `Connect to Port1` button. 
* In the Send Dialog Box at the bottom of the screen, enter lines to send to
  the remote device, and monitor the responses with the Console read-only box.
  You can also try the send file file and snippet scratchpad features... which
  is the reason SUUTerminal exists.

![SUUTerminal screenshot](screenshot.png)

Configuration
-------------
SUUTerminal isn't too configurable and has just a few settings.

* Port - The program scans for open ports and presents a drop-down selection
  menu. If there are multiple ports, a simple way to identify your port is to
  disconnect your device, hit refresh, re-plug in your device and hit refresh 
  again to see which port was added.
* Baud Rate - SUUTerminal allows you to select baud rates of 115200 and 9600. These 
  are the two most common rates. Typically USB devices can support 115200.
* Newline Sequence - Your UART device may want a `LF` (\n), `CR` (\r) or `CR+LF (\r\n)`
  at the end of each line. PuTTY defaults to `CR` (\r) and other terminals default
  to `LF` (\n). C# (.NET) defaults to `CR+LF` (\r\n) on Windows and `LF` (\n) on Linux.

End of Line Characters
----------------------
When receiving data, SUUTerminal converts several end-of-line/new-line variations,
including `LF`, `CR` and `CR+LF` to `Environment.NewLine`, which is `CR+LF` (\r\n)
on Windows and `LF` (\n) on Linux.

Running Scripts
---------------

To send the contents of a script file to the remote device, press `Open File`,
navigate to the file, and press `Run Script`. SUUTerminal waits 100 milliseconds
after each line is sent.

Running Snippets
----------------
Type a sequence of commands into the `Snippet` textbox and press `Run Snippet`.
You can press `Load Snippet`  to initialize the snippet textbox with the
file selected with `Open File`. 

Hacking
-------

* **Add a default port** - Open `Form1.cs [Design]`, right-click on the port
  selection textbox and pick properties. Change the `Text` property.
  
* **Add another Baud Rate** - Edit `Form1.Designer.cs`, search for 9600 and add
  the new baud rates to the `Items` list.
  
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

* **Change default Newline** - Open `Form1.cs [Design]`, right-click on the
  Newline textbox and pick `properties` and change the `text` property to your
  prefered newline character(s).
  
 * **Change delay after each line of script** - Edit `Form1.cs`, search for
   function `sendCommandLine` and replace sleep(100) with your delay in
   milliseconds. This also changes the delay between each line of a snippet.
