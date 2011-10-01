/******************************************************************************
 * README.TXT file for the Microchip TCP/IP Stack Demo v3.75.6                *
 *============================================================================*
 *                                                                            *
 * Copyright (c) 2007, LJCV Electronics. All Rights Reserved                  *
 * San Antonio, Texas, USA. info@ljcv.net, www.ljcv.net                       *
 *                                                                            *
 *- Version Log --------------------------------------------------------------*
 *   Date       Author        Comments                                        *
 *----------------------------------------------------------------------------*
 * 06/01/07 Jorge Amodio      v3.75.5 beta release                            *
 * 07/15/07 Jorge Amodio      v3.75.6 Release                                 *
 ******************************************************************************/

/******************************************************************************
 * Introduction                                                               *
 ******************************************************************************/

 This version of the TCP/IP stack is based on the original distribution
 of the Microchip TCP/IP stack v3.75.

 While most of the code in this version follows the same logic as the 
 original version, some of the differences with previous versions are the
 directory structure, file names and the way the stack options and hardware
 configurations are defined.

 There are also some fixes and improvements, such as the LCD routines that
 have been replaced with new code that includes support for a character LCD
 module using the standard parallel interface or the SPI interface using a
 Microchip MCP23S08 port extender.

 Another addition is for example support for the new Microchip 25LC1024 1Mb
 serial EEPROM and better code selection to handle 24 and 32 bit addressing.

 All the source code is organized in the "src" directory with subdirectories
 for each of the major modules, such as the code for the TCP/IP stack in the
 "net" directory, the LCD driver functions in the "lcd" directory, etc. Each
 of these subdirectories also contain an include subdirectory where the
 associated header files for each module are located.

 All the files went through a clean up process to improve readability and
 better code organization, some definitions have been moved to other include
 files, all configuration options have been moved to the main config.h and
 hardware configuration files, all the header and source code files have been
 reorganized in sections and in an order such as the prototype definitions
 for every and each function could be removed eliminating a substantial
 amount of clutter from the source files.

 All the "code heritage" or version log history has been preserved but
 reorganized, all tabs replaced by white spaces to permit using any text
 viewer or editor without loosing the indentation for easy readability.
 Most of the files now follow a common editing style.

 There are several modifications based on suggestions, findings and comments
 from many members of the Microchip User's forum and some ideas taken out
 from the latest release (v4.02) of the original Microchip TCP/IP stack code.

 Thanks to all members that actively participate in the forum making great
 contributions and providing countless suggestions and ideas.


/******************************************************************************
 * Directory Structure                                                        *
 ******************************************************************************/

 MCHTCP         Main Directory
 |
 +- v3.75.X     Current version, MPLAB project files
    |
    +-- bin     Binary Images (Intel Hex)
    +-- doc     Documentation, Microchip License Agreement
    +-- html    Sample HTTP server documents
    +-- linker  Linker Scripts for MPLINK C18 & C30
    +-- tools   Utilities (mpfs.exe, etc)
    +-- src     Main source code directory
        |
        +-- include  General include headers and configuration files
        +-- net      TCP/IP Modules source code and includes
        +-- lcd      LCD Driver source code and includes
        +-- mpfs     Microchip File System source code and includes
        +-- eeprom   Serial EEPROM drivers source code and includes
        +-- time     RTCC and time support source code and includes
        +-- uart     Serial UART interface source code and includes


/******************************************************************************
 * Building the TCP/IP Stack                                                  *
 ******************************************************************************/

 To build the TCP/IP stack it's recommended that you install the latest
 versions of Microchip MPLAB IDE (version 7.61 or later), C18 (version 3.12
 or later) and/or C30 (version 3.01 or later) compilers.

 Given the new directory structure the include files search path for C18 and
 C30 must include the following directories: src, ../src and ../../src.
 If you use any of the existing MPLAB IDE project files the search path is
 already set.

 The current version DOES NOT support the HI-TECH or CCS compilers yet.


/******************************************************************************
 * Configuration                                                              *
 ******************************************************************************/

 There are at least three files that you will need to edit and modify to
 reflect your particular hardware configuration and code options, the
 config.h file, the particular hardware configuration file for your board
 and if necessary the main application source code.

 Once you have the files "tailored" for your project or application you must
 select the correct processor on MPLAB IDE and if necessary the language
 toolset that will be used to compile the code.

 Remember that some microcontrollers such as the PIC18F452 or PIC18F4520 have
 limited amount of program memory space to fit all stack modules and leave
 available space for your application. A recommended pin compatible device
 with more memory both program and RAM, and more advanced peripherals is the
 PIC18F4620 or its 28-pin version the PIC18F2620.

 In the "bin" directory you will find precompiled images for the PIC18F4620
 for boards/designs that accept a 40-pin device and for the PIC18F2620 for
 boards/designs that accept a 28-pin device.

 The main configuration file and other parts of the code use a special macro
 that define which is the hardware profile to be included for building the
 stack, you need to add this macro the project build options on MPLAB IDE.
 For example if you are planning to build the code for the Microchip
 PICDEM.net board, on the Projects->Build Options-> Project menu and MPLAB
 C18 tab you must add the macro PICDEMNET.


/******************************************************************************
 * Hardware configuration files                                               *
 ******************************************************************************/

 Each development board or reference design has a separate header file that
 defines the particular hardware configuration, options and initialization
 values for various registers.

 The configuration file must include all the required macro definitions for
 the particular drivers for each device such as the Ethernet controller, LCD
 display or serial EEPROM memory. If something is missing you most probably
 will get an error during compilation time.

 The current distribution includes several hardware configuration files for
 different development boards or designs and different hardware options.

 You can use these files as a reference to build the configuration file for
 your specific design.

 The main config.h file will select which hardware configuration file to
 include in the project based on the macro previously defined in MPLAB IDE.

 All hardware configuration files are located in the general "src/include"
 directory.

 The hardware configuration files included in this distribution are:

 - eip10.h          LJCV Electronics eIP-10 Board
 - eip10_lcd.h      LJCV Electronics eIP-10 Board + character LCD module
 - eip10_spilcd.h   LJCV Electronics eIP-10 Board + character LCD module
                    with SPI interface and MCP23S08 port extender
 - exp16_dspic33.h  Microchip Explorer 16 Board with dsPIC33FJ256GP710 PIM
                    and Microchip Ethernet PICTail+
 - exp16_pic24f.h   Microchip Explorer 16 Board with PIC24FJ128GA010 PIM
                    and Microchip Ethernet PICTail+
 - exp16_pic24h.h   Microchip Explorer 16 Board with PIC24HJ256GP610 PIM
                    and Microchip Ethernet PICTail+
 - hpc_explorer.h   Microchip HPC Explorer with PIC18F8722 + Ethernet PICtail
 - minipic10t.h     Jorge Amodio mini PIC10T reference project
 - pic10t.h         Jorge Amodio PIC10T reference project
 - pic24fj64.h      Jorge Amodio PIC24FJ64GA002 reference project
 - pic24fj64_lcd.h  Jorge Amodio PIC24FJ64GA002 reference project + character
                    LCD module with SPI interface and MCP23S08 port extender
 - picdem2.h        Microchip PICDEM 2+ (mod) + LJCV Electronics nic28 NIC
 - picdemnet.h      Microchip PICDEM.net Board with RTL8019AS controller
 - picdemnet2.h     Microchip PICDEM.net 2 Board with PIC18F87J60 
 - pic18_nic28.h    Connecting a 28 pin PIC18F to LJCV Electronics nic28 NIC
 - picnet1.h        LJCV Electronics PICNet 1 Development Board
 - picnet1_spilcd.h LJCV Electronics PICNet 1 Board + character LCD module
                    with SPI interface and MCP23S08 port extender
 - picweb1.h        Celeritous PICWEB1 Module with PIC18F67J60

 All the files above include references about where to obtain additional
 information about each board and detailed schematics.


/******************************************************************************
 * Main configuration file                                                    *
 ******************************************************************************/

 The main configuration file config.h includes all configuration options
 previously spread among different header and source code files in older
 versions of the TCP/IP stack.

 In most cases this will be probably the only file you need to modify if you
 wish to change the IP address configuration or basic TCP/IP stack options.

 All configuration options include self explanatory comments.

 Notice that for IP addresses the decimal numbers are separated by commas and
 not by the traditional dotted decimal notation, this is an array structure
 and each element of the array must be separated by commas for proper
 initialization.

 The last section of the config.h file includes a number of conditional macros
 used to select particular parameters based on the hardware configuration and
 previously selected options. For example if you enable the HTTP server module
 the conditional macros will automatically include the TCP module; if your
 hardware configuration file includes a 24LC512 serial EEPROM (USE_24LC512) the
 conditional macros will include the I2C EEPROM driver functions and set the
 correct clock speed, page size, etc.

 In many cases you should not need to modify the last section of the 
 configuration file.
 
 The config.h file is located "src/include" subdirectory".


/******************************************************************************
 * Main application source code                                               *
 ******************************************************************************/

 Based on your project or application you most surely will need to modify the
 main.c source code file. Remember that any code you modify/add/remove must
 be written within the overall context of the TCP/IP stack architecture which
 is based on cooperative multitasking and a continuous execution loop that
 must always include at least a call to the StackTsk() function.

 There is a particular section of main.c where the configuration bits for the
 processor are set. Review this section and make sure that the appropriate
 configuration bits for your project are set and that are consistent with the
 hardware configuration file.

 It's recommended that with the Microchip TCP/IP stack you disable the Watch
 Dog Timer (WDT), Low Voltage Programming (LVP) and JTAG.


/******************************************************************************
 * Compiling the source code                                                  *
 ******************************************************************************/

 After you are done with the configuration of the stack you must include in
 your MPLAB IDE project the correct linker script file (if a different
 processor than the existing one in the project will be used).

 The "linker" directory includes several script files for various processors
 compatible with the boards/designs included in this version.

 If in the config.h file you enabled the HTTP server module and storage on
 program memory (MPFS_USE_PGRM), previously to build the image, you must first
 generate a "C language image" source file using the MPFS.EXE utility using
 the /c option, move the output C file to the main source directory, include
 it in the project Source file list and edit it to replace the line that has
 the #include "..\Include\Compiler.h" by #include "include/config.h".

 The current distribution includes a C source code image of the sample website
 in the file mpfsimg.c in the main source directory.

 To build your project just use the make or build functions on MPLAB IDE.

 If there are some missing configuration options or errors the compiler will
 stop and show the error on the output screen.

 If you use any of the existing MPLAB IDE project files to build the code
 image, the project options are set in a way that all objects will be stored
 under a "obj" subdirectory for each module and the binary files, cof and map
 files will be stored in the "bin" directory.

 The project files also assume that the C18 compiler is installed in the
 "C:\MCC18" directory and the C30 compiler in the "C:\MPLAB C30", if your
 install path is different you will need to change the language tool suite
 directories accordingly.

 Use your preferred PIC programmer to download the image to the microcontroller
 program memory.


/******************************************************************************
 * Uploading the HTTP server documents image                                  *
 ******************************************************************************/

 If you selected the MPFS_USE_EEPROM option to store the HTTP documents in an
 external serial EEPROM, you must upload the file system image by using FTP
 or via the serial command interface with XMODEM.

 First you must create a MPFS binary image of the HTTP server documents, to
 do so you must use the MPFS.EXE utility passing as arguments the directory
 where the source documents are located (the example website documents are in
 the "html" directory) and the name of the output file that will be later
 uploaded.

 If your design includes the new Microchip 25LC1024 serial EEPROM, you must
 create the image using the MPFS.EXE /l option (24 bit addressing). Remember
 also to include the USE_25LC1024 macro in your hardware configuration file
 to include the appropriate code and settings for this memory device.

 Double check that your image file does not exceed the available capacity of
 the EEPROM memory, the stack reserves the first 64 bytes to save the
 application configuration information and the rest of the memory is available
 for the HTTP documents image (which includes a simple File Allocation Table).

 Nor FTP or the XMODEM uploading options check for available memory space, if
 you exceed the actual available memory, the code will wraparound and start
 writing over the previously written FAT and documents.

 To upload your image to memory via FTP just use the FTP command available in
 any Windows or Unix machine, enter the username (the default is "ftp") and
 the password (the default is "microchip") and then execute the "put" command
 providing the file name of your image file.


/******************************************************************************
 * Note about configuration information stored in EEPROM                      *
 ******************************************************************************/

 If you use an external serial EEPROM, the current stack code will reserve
 the first 64 bytes to write the configuration information, such as IP 
 address, netmask, etc.

 When you run the stack code for the very first time the default configuration
 hard coded in program memory will be written to the serial EEPROM. The next
 time the stack code starts will load the previously stored configuration from
 the serial EEPROM.

 If you change the default hard coded configuration in the config.h file, you
 must invalidate the previously stored configuration in the serial EEPROM.
 To do so hold low the I/O port mapped to BUTTON0 for at least 4 seconds 
 after reset or while in the serial configuration menu, the new configuration
 will be written into the serial EEPROM, the serial interface will show a
 message and LED0 to LED2 will turn on for few seconds and the microcontroller
 will reset automatically.

 Note that the BUTTON0 option to rewrite the configuration in the serial
 EEPROM and the configuration menu via the serial interface will be included
 in the code only if you define the ENABLE_BUTTON0_CONFIG macro in the
 config.h file.

