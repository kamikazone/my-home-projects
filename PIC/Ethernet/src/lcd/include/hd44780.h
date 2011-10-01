/******************************************************************************
 * HD44780/KS0066 Compatible LCD Controller Definitions                       *
 *============================================================================*
 *                                                                            *
 * SOFTWARE LICENSE AGREEMENT                                                 *
 *                                                                            *
 * This software is provided to you free of charge with the sole condition    *
 * of preserving this Copyright Notice. This software is provided "AS IS".    *
 * LJCV Electronics disclaims all warranties, express, implied, statutory or  *
 * otherwise, not limited to merchantability, fitness for a particular        *
 * purpose, and infringement. LJCV Electronics shall in no event be liable    *
 * for special, incidental, or consequential damages. By using this software  *
 * or incorporating parts of it in your particular design or application you  *
 * are accepting the terms of this agreement.                                 *
 *                                                                            *
 * LJCV ELECTRONICS ASSUMES NO OBLIGATION TO PROVIDE ANY WARRANTY OR SUPPORT. *
 *                                                                            *
 * Copyright (c) 2007, LJCV Electronics. All Rights Reserved                  *
 * San Antonio, Texas, USA. info@ljcv.net, www.ljcv.net                       *
 *                                                                            *
 *- Version Log --------------------------------------------------------------*
 *   Date       Author        Comments                                        *
 *----------------------------------------------------------------------------*
 * 02/11/07  Jorge Amodio     Initial Version                                 *
 ******************************************************************************/
#ifndef _HD44780_H
#define _HD44780_H

//*****************************************************************************
// Standard command set for LCD character modules based using the HD44780,
// KS0066 or equivalent LCD controller
#define CLEAR_DISPLAY    0b00000001
#define RETURN_HOME      0b00000010

#define ENTRY_MODE       0b00000100    // Entry Mode Set
//                               |+--- SH:  Shift entire display
//                               |          0 = Shift disabled
//                               |          1 = Shift enabled
//                               +---- I/D: Increment/decrement DDRAM Address
//                                          0 = cursor moves left, address -1
//                                              display shifts right if SH=1
//                                          1 = cursor moves right, address +1
//                                              display shifts left if SH=1
#define SHIFT_RIGHT      0b00000010
#define SHIFT_ENABLE     0b00000001

#define DISPLAY_ON_CTRL  0b00001000    // Display ON/OFF Control
//                              ||+--- B: 0 = Cursor Blink Off, 1 = Blink On
//                              |+---- C: 0 = Cursor Off, 1 = Cursor On
//                              +----- D: 0 = Display Off, 1 = Display On
#define CURSOR_BLINK     0b00000001
#define CURSOR_ON        0b00000010
#define DISPLAY_ON       0b00000100

#define CURSOR_SHIFT     0b00010000    // Cursor or Display Shift
//                             ++----- S/C R/L
//                                      0   0  Shift Cursor left, AC -1
//                                      0   1  Shift Cursor right, AC +1
//                                      1   0  Shift Display left
//                                      1   1  Shift Display Right
#define CURSOR_RIGHT     0b00000100
#define DISPLAY_RIGHT    0b00001100

#define FUNCTION_SET     0b00100000    // Display Function Set
//                            ||+----- F:  Display Font Type
//                            ||           0 = 5x8 dots format
//                            ||           1 = 5x11 dots format
//                            |+------ N:  Display Line Number
//                            |            0 = 1-line display mode
//                            |            1 = 2-line display mode 
//                            +------ DL:  Interface Data Lenght
//                                         0 = 4-bit Interface
//                                         1 = 8-bit Interface
#define FONT_5X11        0b00100100
#define MULTI_LINE       0b00101000
#define EIGHT_BIT_IF     0b00110000
#define FOUR_BIT_IF      0b00100000

#define SET_CGRAM_ADDR   0b01000000    // Set Character Generator RAM Address
                                       // last six bits are the address
#define SET_DDRAM_ADDR   0b10000000    // Set Display Data RAM Address
                                       // last seven bits are the address 

//*****************************************************************************
// LCD Geometry and Display Data RAM memory map
//
// We expect LCD_ROWS and LCD_COLS defined by the application configuration,
// if not set to 2x16 by default
#ifndef LCD_ROWS
  #define LCD_ROWS  2                  // Number of lines/rows
#endif
#ifndef LCD_COLS
  #define LCD_COLS  16                 // Number of characters per line
#endif

//*****************************************************************************
// LCD_MMAP defines the starting DDRAM address for each line, this may vary
// between different LCD implementations, double check the specific 
// data sheet and modify accordingly
#if (LCD_ROWS > 2)
  #if (LCD_COLS > 16)
    #define LCD_MMAP    { 0x00, 0x40, 0x14, 0x54 } // ie 4x20 LCD
  #else
    #define LCD_MMAP    { 0x00, 0x40, 0x10, 0x50 } // ie 4x16 LCD
  #endif
#else
  #define LCD_MMAP      { 0x00, 0x40 }             // ie 2x16 or 2x20 LCD
#endif

//*****************************************************************************
// LCD Delays
// The LCD controller requires some delays to process particular commands and
// transfer to the LCD RAM memory, the values defined below are derived from
// various LCD modules data sheets and empirical testing, double check the
// specific delays and modify accordingly here or define the macro in the
// application configuration
#ifndef LCD_INIT_DELAY
#define LCD_INIT_DELAY   200           // Initialization delay in ms
#endif

#ifndef LCD_CLEAR_DELAY
#define LCD_CLEAR_DELAY  2             // Delay after clear or home cmd in ms
#endif

#ifndef LCD_DATA_DELAY
#define LCD_DATA_DELAY   50            // Data entry delay
#endif

#endif // _HD44780_H

