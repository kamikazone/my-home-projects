/******************************************************************************
 * Generic HD44780/KS0066 Character Mode LCD Display Driver Routines          *
 *============================================================================*
 *                                                                            *
 * This driver module includes the routines needed to interface a             *
 * Microcontroller to a character module LCD. They support the 4/8 bit        *
 * parallel interface and a serial SPI interface using Microchip's MC23S08    *
 * port extender chip.                                                        *
 *                                                                            *
 * All the functions are non blocking and don't read back the BUSY status     *
 * from the LCD module, R/W should be held low (Write) or hardwired to low.   *
 * To satisfy LCD timing requirements the functions use various delays.       *
 *                                                                            *
 * Required and optional Macro definitions from application:                  *
 * - If a direct parallel interface is used:                                  *
 *   - LCD_4BIT_IFACE  If defined 4 bit interface is used,                    *
 *   - LCD_E_IO        Mapped to I/O pin used for E signal                    *
 *   - LCD_RS_IO       Mapped to I/O pin used for RS signal                   *
 *   - LCD_RW_IO       Mapped to I/O pin if used for R/W signal               *
 *   - LCD_DATA_IO     Mapped to struct representing the I/O pins for DB7-0   *
 *                                                                            *
 * - If the SPI/Port extender interface is used:                              *
 *   - LCD_USE_SPI     Define to select this interface mode                   *
 *                     (see requirements on mcp23s08.c)                       *
 * Other macros:                                                              *
 * - LCD_USE_BUFFER    Define to enable local memory buffer                   *
 * - LCD_USE_CGCHAR    Define to enable Custom Characters support             *
 * - LCD_ROWS,LCD_COLS Display geometry                                       *
 *                                                                            *
 * These routines assume that I/O ports and SPI interface registers have      *
 * been previously configured and initialized.                                *
 *                                                                            *
 * Application code must include the header file "cmlcddriver.h".             *
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
 * 02/11/07 Jorge Amodio      Initial Version (1.0)                           *
 ******************************************************************************/
#include "include/config.h"

#if defined(USE_CM_LCD)
#include "include/delay.h"
#include "lcd/include/hd44780.h"

#if defined(LCD_USE_SPI)
#include "lcd/include/portx.h"
#endif

//*****************************************************************************
// Local variables used by the lcd driver routines 
// LCD_ROWS, LCD_COLS defined in application code or default 2x16 in hd44780.h
// LCD_MAP defined in hd44780.h
//
#if defined(LCD_USE_BUFFER)
unsigned char LCDBuffer[LCD_ROWS][LCD_COLS];
#endif
ROM char const LCDMemMap[] = LCD_MMAP;

//*****************************************************************************
// LCDSend sends a command or data byte to the LCD module
// cmd argument has the same logic as the LCD RS pin
// cmd = 0 -> data byte is a LCD command
// cmd = 1 -> data byte is a character value
//
void LCDSend(unsigned char cmd, unsigned char data)
{
    cmd &= 1;
   
#if defined(LCD_USE_SPI)
    // When using the port extender (MCP23S08), the interface to the LCD
    // is 4 bits and no data setup or E cycle delays are needed due the
    // inherent delays introduced by using the SPI interface
    WritePortX( ((data>>4) & 0x0f) | cmd<<4 );   // Send high nibble
    BitSetPortX(0x20);
    BitClearPortX(0x20);
    WritePortX(  (data & 0x0f) | cmd<<4);        // Send lower nibble
    BitSetPortX(0x20);
    WritePortX(0);
#else
  #if defined(LCD_RW_TRIS)                       // If required initialize
    LCD_RW_TRIS = 0;                             // I/O port directions
  #endif

  #if defined(LCD_RW_IO)
    LCD_RW_IO = 0;
  #endif

  #if defined(LCD_DATA_TRIS)
    LCD_DATA_TRIS = 0;
  #endif

  #if defined(LCD_RS_TRIS)
    LCD_RS_TRIS = 0;
  #endif

    LCD_RS_IO = cmd;                             // Set RS to command or data

  #if defined(LCD_4BIT_IFACE)
    LCD_DATA_IO = data>>4;                       // Send high nibble
    Nop();                                       // Add some data setup delay
    Nop();
    Nop();
    Nop();
    LCD_E_IO = 1;
    Delay10us(1);                                // E signal normally requires
    LCD_E_IO = 0;                                // some minimum cycle time
    Delay10us(1);                                // and pulse width
  #endif

    LCD_DATA_IO = data;                          // Send lower nibble or byte
    Nop();                                       // if mode is 8-bit
    Nop();                                       // Again delay for E cycle
    Nop();                                       // time and pulse width
    Nop();
    LCD_E_IO = 1;
    Delay10us(1);
    LCD_E_IO = 0;
    Delay10us(1);
#endif  // LCD_USE_SPI

    Delay10us(LCD_DATA_DELAY/10);                // Data process delay
}

//*****************************************************************************
// LCDGoto sets the current LCD memory address pointer to the corresponding
// address for row,col using the predefined Memory Map
// If row,col are not under the correct range no action is performed
//
void LCDGoto(unsigned char row, unsigned char col)
{
    if ((row < LCD_ROWS) && (col < LCD_COLS ))
    {
        LCDSend(0,(LCDMemMap[row]+col) | SET_DDRAM_ADDR);
    }
}

//*****************************************************************************
// LCDWriteStr sends directly to the LCD a string in RAM pointed by s.
// The string must be ended with null
//
void LCDWriteStr(char *s)
{
    char c;

    while(c = *s)
    {
        LCDSend(1,c);
        s++;
    }
}

//*****************************************************************************
// LCDWritePGMStr sends directly to the LCD a string in Program Memory
// pointed by s. The string must be ended with null
//
void LCDWritePGMStr(ROM char const *s)
{
    char c;

    while(c = *s)
    {
        LCDSend(1,c);
        s++;
    }
}

//*****************************************************************************
// LCDClear sends the clear display command to the LCD
//
void LCDClear(void)
{
    LCDSend(0, CLEAR_DISPLAY);
    DelayMs(LCD_CLEAR_DELAY);
}

//*****************************************************************************
// LCDClearRow clears a display line sending whitespaces directly to the LCD
// The function leaves the LCD RAM address at the start of the cleared row
//
void LCDClearRow(unsigned char row)
{
    unsigned char i;

    if ( row < LCD_ROWS ) {
      LCDGoto(row,0);
      for ( i = 0 ; i < LCD_COLS ; i++)
        LCDSend(1,' ');
    }
    LCDGoto(row,0);
} 

#if defined(LCD_USE_BUFFER)
//*****************************************************************************
// LCDRefresh transfers the local LCD memory buffer to the LCD memory
// null character is replaced by a white space
//
void LCDRefresh(void)
{
    unsigned char x, y, c;
    
    for ( y = 0; y < LCD_ROWS ; y++ ) {
        LCDGoto(y,0);
        for ( x = 0 ; x < LCD_COLS ; x ++)
            LCDSend(1, (c = LCDBuffer[y][x]) ? c : ' ');
    }
}

//*****************************************************************************
// LCDClearBuffer "clears" the local LCD memory buffer filling it with
// white spaces
//
void LCDClearBuffer(void)
{
    unsigned char x, y;

    for ( y = 0 ; y < LCD_ROWS ; y++)
        for ( x = 0 ; x < LCD_COLS ; x++)
            LCDBuffer[y][x] = ' ';
}

//*****************************************************************************
// LCDClearBufferRow fills the corresponding LCD buffer row with
// whitespaces
//
void LCDClearBufferRow(unsigned char row)
{
    unsigned char i;

    if ( row < LCD_ROWS )
        for ( i = 0 ; i < LCD_COLS ; i++)
          LCDBuffer[row][i] = ' ';
} 
#endif

#if defined(LCD_USE_CGCHARS)
//*****************************************************************************
// LCDLoadCGRAM transfers a 5x8 bit pattern character from Program Memory
// to the LCD Character Generator RAM for the character number 'c' (0-7)
//
void LCDLoadCGRAM(unsigned char c, ROM char *p)
{
   unsigned char i;

   if ( c < 8 ) {
     LCDSend(0, SET_CGRAM_ADDR | c<<3 );
     for ( i = 0 ; i < 8 ; i++ )
       LCDSend(1, p[i]);
   }
   LCDSend(0, SET_DDRAM_ADDR);
}
#endif

//*****************************************************************************
// LCDInit sends the initialization command sequence and sets the default
// operation mode, clears the LCD memory and turns it on
//
void LCDInit(void)
{
#if defined(LCD_USE_BUFFER)
    LCDClearBuffer();              // Clear memory buffer
#endif

#if defined(LCD_USE_SPI)           // LCD interface via MCP23S08 port extender
    InitPortX(0);
#endif

    DelayMs(LCD_INIT_DELAY);                     // Delay for LCD to be ready
    LCDSend(0, FUNCTION_SET | EIGHT_BIT_IF);     // Initialization sequence
    DelayMs(5);
    LCDSend(0, FUNCTION_SET | EIGHT_BIT_IF);
    Delay10us(15);

#if defined(LCD_4BIT_IFACE)                      // Set 4-bit interface mode
    LCDSend(0, FUNCTION_SET | FOUR_BIT_IF );
    LCDSend(0, FUNCTION_SET | MULTI_LINE); 
#else                                            // Set 8-bit interface mode
    LCDSend(0, FUNCTION_SET | EIGHT_BIT_IF | MULTI_LINE); 
#endif

    LCDSend(0, ENTRY_MODE | SHIFT_RIGHT);        // Cursor right, increment
    LCDClear();                                  // Clear LCD 
    LCDSend(0, DISPLAY_ON_CTRL | DISPLAY_ON);    // Turn on LCD
}

#endif  // USE_CM_LCD

