<html>
<meta http-equiv=refresh content=10>
<head><title>Microchip TCP/IP Stack Demo</title></head>
<body bgcolor=#FFFFFF  leftmargin=0 topmargin=0 marginwidth=0 marginheight=0>
<font face=Arial>
<table width=100%% bgcolor=#FFFFFF border=0 cellpadding=0 cellspacing=0>
<tr valign=center>
<td colspan=2 align=right><a href="http://www.microchip.com/"><img src="mchp.gif" width=230 height=60 alt="" border=0 align=left></a></td>
<td colspan=2 align=right><font color=#156F4F size=6><b>Microchip TCP/IP Stack&nbsp;</b></font></td>
</tr>
<tr bgcolor=#E5EFEC>
<td width=25%% align=center><b>Home</b></td>
<td width=25%% align=center><a href="arch.htm">Architecture</a></td>
<td width=25%% align=center><a href="feat.htm">Features</a></td>
<td width=25%% align=center><a href="links.htm">Links</a></td>
</tr>
<tr>
<td colspan=4>
<table width=100%% border=0 cellpadding=0 cellspacing=0>
<tr valign=top>
<td width=8 bgcolor=#E5EFEC rowspan=5></td>
<td width=70%% rowspan=5>
<table>
<tr>
<td>&nbsp;</td>
<td>
<font color=#6C6C6C size=2><br>
This is a demo website that is being served by a simple HTTP server part of the Microchip TCP/IP Stack running on an 8 or 16-bit
Microchip microcontroller.<br><br>
The Microchip TCP/IP Stack supports different configurations and ethernet controllers such as the Microchip ENC28J60, the Realtek
RTL8019 and the new PIC18F97J60 family of 8-bit microcontrollers with integrated ethernet interface.<br><br>
The <a href="links.htm">Links</a> page includes several links to additional information and reference designs using the Microchip TCP/IP Stack.<br><br>
The right section of this page demonstrates the ability to handle real-time control functions and how to generate pages with dynamic contents. The <b>Status</b> section shows the current status of several variables which are refreshed every time you reload the page and automatically about every 10 seconds. The <b>Actions</b> section sends commands like changing the status of particular I/O ports.<br><br>
If available you can push the on-board switch(es) or change the voltage on the analog inputs and see the new data updated on this page. You can	also click on one of the two LED command buttons to toggle the on-board LEDs.<br><br>
For more information about how to put together a simple hardware design to run the Microchip TCP/IP Stack and for products and tools available for developing applications like this one, visit the <a href="http://www.ljcv.net/projects/">LJCV Electronics Projects Page</a>.<br><br><br>
</font>
</td>
<td>&nbsp;</td>
</tr>
</table>
</td>
<td width=8 bgcolor=#E5EFEC rowspan=5></td>
<td><br><font color=#6C6C6C size=2>Version: %16<br>Build date: %17<br><br></font></td>
<td width=8 bgcolor=#E5EFEC rowspan=5></td>
</tr>
<tr bgcolor=#E5EFEC>
<td height=8></td>
</tr>
<tr valign=top>
<td>
<form method="get" action="0">
<font color=#156F4F size=3><b>Actions</b><br><br></font>
<font color=#6C6C6C size=2>Toggle LEDs &nbsp;&nbsp;
<input type="submit" name="0" value="LED1"></input>
<input type="submit" name="1" value="LED2"></input>
<br><br></font>
</td>
</tr>
<tr bgcolor=#E5EFEC>
<td height=8></td>
</tr>
<tr valign=top>
<td height=100%%>
<font color=#156F4F size=3><b>Status</b><br><br></font>
<table cellpadding="3">
<tr><td>Date:</td><td>%22</td></tr>
<tr><td>Time:</td><td>%23</td></tr>
<tr><td>AN0:</td><td>%02</td></tr>
<tr><td>Buttons:</td><td>%0F %0E %0D %04</td></tr>
<tr><td>LEDs:</td><td>%15 %14 %13 %12 %11 %10 %01 %00</td></tr>
<tr><td colspan=2><br><b>IP Packet Counters</b><br></td></tr>
<tr><td>Tx:</td><td>%20</td></tr>
<tr><td>Rx:</td><td>%21</td></tr>
</table>
<br><br>
</td>
</tr>
</table>
</td>
</tr>
<tr bgcolor=#E5EFEC>
<td height=8 colspan=4></td>
</tr>
</table>
</font>
</body>
</html>
