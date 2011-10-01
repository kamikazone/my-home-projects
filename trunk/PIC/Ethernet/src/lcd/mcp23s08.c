/******************************************************************************
 * Microchip MCP23S08 I/O Port Extender Driver                                *
 *============================================================================*
 *                                                                            *
 * This driver module includes the routines needed to communicate using the   *
 * SPI interface with Microchip's MCP23S08 port extender IC.                  *
 *                                                                            *
 * Required Macro definitions from application                                *
 * - USE_MCP23S08  Defined to enable compilation of this module               *
 * - PORTX_CS      Mapped to the correct I/O pin used for CS of the MCP23S08  *
 * - PORTX_ADDRESS Two bit value representing A1,A0 address of the MCP23S08   *
 * - PORTX_SSPBUF  Mapped to the correct SPI Buffer Register to use           *
 * - PORTX_SPI_IF  Mapped to the correct SPI Interrupt Flag to use            *
 *                                                                            *
 * These routines assume that I/O ports direction and initial state have been *
 * previously initialized.                                                    *
 * The current driver version has been compiled and tested only for PIC18     *
 * devices with Microchip MPLAB C18 v3.10                                     *
 *                                                                            *
 * Application code must include the header file "portx.h"                    *
 *                                                                            *
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
 * 02/11/07 Jorge Amodio      Initial Version                                 *
 * 06/20/07 Jorge Amodio      Added dummy reads to prevent fault interrupts   *
 *                            Added SPI Disable/Enable when SPI config switch *
 *                            (PORTX_SAVE_SPI_CFG) is used, no need to save   *
 *                            SPISTAT, variables & code removed               *
 * 07/03/07 Jorge Amodio      Corrected PORTX_SAVE_SPI_CFG due SSPEN mapping  *
 * 07/17/07 Jorge Amodio      Corrected SPICONSave type for C30               *
 ******************************************************************************/
#include "include/config.h"

#if defined(USE_MCP23S08)

#include "lcd/include/mcp23s08.h"
#include "include/delay.h"

/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/

//*****************************************************************************
// ReadPortXReg returns a byte read from the data input register
//
unsigned char ReadPortXReg(unsigned char RegAddr)
{
    unsigned char p;

#if defined(PORTX_SAVE_SPI_CFG)
    #if defined(__18CXX)
    unsigned char SPICONSave;
    #else
    unsigned short int SPICONSave;
    #endif

    SPICONSave = PORTX_SPICON1;
    PORTX_SPIEN = 0;
    PORTX_SPICON1 = PORTX_SPICON1_CFG;
    PORTX_SPIEN = 1;
#endif

    PORTX_CS_IO = 0;
    PORTX_SPI_IF = 0;
    PORTX_SSPBUF = (PXREAD | PORTX_ADDRESS); // Send Read Command + Address

    while(!PORTX_SPI_IF);                    // Wait for SPI transmit completed

    p = PORTX_SSPBUF;
    PORTX_SPI_IF = 0;
    PORTX_SSPBUF = RegAddr;                  // Send GPIO Register Address

    while(!PORTX_SPI_IF);

    p = PORTX_SSPBUF;
    PORTX_SPI_IF = 0;
    PORTX_SSPBUF = 0;                        // Send dummy byte for clocking

    while(!PORTX_SPI_IF);                    // Wait for SPI transfer complete

    p = PORTX_SSPBUF;                        // Get register value
    PORTX_SPI_IF = 0;
    PORTX_CS_IO = 1;

#if defined(PORTX_SAVE_SPI_CFG)
    PORTX_SPIEN = 0;
    PORTX_SPICON1 = SPICONSave;
    PORTX_SPIEN = 1;
#endif

    return(p);
}

//*****************************************************************************
// ReadPortX returns a byte read from the Input Register
//
#define ReadPortX()    ReadPortXReg(PXGPIO)

//*****************************************************************************
// ReadPortXLAT returns a byte read from the Ouput Latch Register
//
#define ReadPortXLAT() ReadPortXReg(PXOLAT)

//*****************************************************************************
// WritePortXReg writes a byte to the register addressed by RegAddr
//
void WritePortXReg(unsigned char RegAddr, unsigned char Value)
{
    unsigned char p;

#if defined(PORTX_SAVE_SPI_CFG)
    #if defined(__18CXX)
    unsigned char SPICONSave;
    #else
    unsigned short int SPICONSave;
    #endif

    SPICONSave = PORTX_SPICON1;
    PORTX_SPIEN = 0;
    PORTX_SPICON1 = PORTX_SPICON1_CFG;
    PORTX_SPIEN = 1;
#endif

    PORTX_CS_IO = 0;
    PORTX_SPI_IF = 0;
    PORTX_SSPBUF = (PXWRITE|PORTX_ADDRESS);  // Send Write Command + Address

    while(!PORTX_SPI_IF);                    // Wait for SPI transmit completed

    p = PORTX_SSPBUF;
    PORTX_SPI_IF = 0;
    PORTX_SSPBUF = RegAddr;                  // Send Register Address

    while(!PORTX_SPI_IF);

    p = PORTX_SSPBUF;
    PORTX_SPI_IF = 0;
    PORTX_SSPBUF = Value;                    // Send value to write
  
    while(!PORTX_SPI_IF);                    // Wait for SPI transmit completed

    p = PORTX_SSPBUF;
    PORTX_SPI_IF = 0;
    PORTX_CS_IO = 1;

#if defined(PORTX_SAVE_SPI_CFG)
    PORTX_SPIEN = 0;
    PORTX_SPICON1 = SPICONSave;
    PORTX_SPIEN = 1;
#endif
}

//*****************************************************************************
// WritePortX writes a byte to the Output Latch Register
//
#define WritePortX(a) WritePortXReg(PXOLAT,a)

//*****************************************************************************
// BitSetPortX changes to 1 only the bits that are on 1 in the argument byte
// To perform this operation the previous content of the Output Latch
// is read and then or'ed with the argument
//
void BitSetPortX(unsigned char p)
{
      WritePortX(ReadPortXLAT() + p);
}

//*****************************************************************************
// BitClearPortX changes to 0 only the bits that are on 1 in the argument byte
// To perform this operation the previous content of the Output Latch
// is read and then and'ed with the complement of the argument
//
void BitClearPortX(unsigned char p)
{
      WritePortX(ReadPortXLAT() & ~p);
}

//*****************************************************************************
// InitPortX initializes the SPI interface and sets the I/O direction on
// each pin according to iodir bits ( 0 = Output, 1 = Input )
// This function assumes that the SPI interface has been previously 
// initialized by the main application. Proper initialization values for
// configuration registers must be declared as macros (PORTX_SPICON_CFG and
// PORTX_SPISTAT_CFG) in the hardware profile.
//
void InitPortX(unsigned char iodir)
{
    PORTX_SPI_IF = 0;
    WritePortXReg(PXIODIR,iodir);  // Configure MCP23S08 pin directions
    WritePortX(0);
}

#endif // USE_MCP23S08

