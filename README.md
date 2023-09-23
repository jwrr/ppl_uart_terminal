# ppl_uart_terminal

USB UART TERMINAL GUI SOFTWARE
------------------------------

The terminal GUI is written in C# using WinForms. To run the GUI start Visual Studio 
(It has been tested using Microsoft Visual Studio Community 2022 (64-bit)).
* Click "Open a project or solution"
* open ppl_uart_terminal.sln
* Click "Start". This will compile and run the GUI.
* In the GUI's configuration pane, select the appropriate Port, Baud Rate and
  Newline sequence.
* Enter commands to send to the remote device using the Send Dialog box, and
  monitor the responses with the Console read-only box.

Configuration
-------------

* Port - The program scans for open ports and presents a drop-down selection menu
* Baud Rate - The baud rates 115200 and 9600 are supported.
* Newline Sequence - The selectible list of of new line sequences 
  are LF ("\n"), CR ("\r") and CR+LF ("\r\n"). This affects the transmit send path.
  On the receive path, the sequences LF ("\n"), CR ("\r") and CR+LF ("\r\n") are
  converted to Environment.NewLine. On Windows, Environment.NewLine is "\r\n" and
  on Linux it is "\n".

End of Line Characters
----------------------

When receiving, several variations of newline are converted to 
Environment.NewLine, which is "\r\n" on Windows and "\n" on Linux. 





