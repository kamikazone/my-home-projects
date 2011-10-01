/******************************************************************************
 * SPI Serial EEPROM Driver                                                   *
 *============================================================================*
 *                                                                            *
 * This module implements a basic driver for a serial EEPROM memory with a    *
 * standard SPI interface.                                                    *
 *                                                                            *
 * The current version of code expects the macros EEPROM_SPICON,              *
 * EEPROM_SPISTAT, EEPROM_SSPBUF, EEPROM_SPI_IF to be defined pointing to     *
 * the correct SPI control registers, and interrupt flag, and the macros      *
 * EEPROM_SPICON_CFG and EEPROM_SPISTAT_CFG defined with the proper           *
 * configuration values for the control registers.                            *
 *                                                                            *
 * For the hardware interface the code expects the macro EEPROM_CS_IO to be   *
 * defined pointing the corresponding I/O pin used to drive the the CS signal *
 * of the serial EEPROM device.                                               *
 *                                                                            *
 * The code asumes that I/O direction and initial state for associated I/O    *
 * pins and initial SPI mode configuration have been previously set in the    *
 * main application initialization routine.                                   *
 *                                                                            *
 * Compiling with the EEPROM_SAVE_SPI_CFG macro defined will include code to  *
 * preserve the previous value of the SPI configuration registers.            *
 *                                                                            *
 * IMPORTANT SPI NOTE: The code in this file expects that the SPI interrupt   *
 * flag (EEPROM_SPI_IF) be clear at all times.  If the SPI is shared with     *
 * other hardware, the other code should clear the EEPROM_SPI_IF when it is   *
 * done using the SPI.                                                        *
 *                                                                            *
 *                                                                            *
 * SOFTWARE LICENSE AGREEMENT                                                 *
 *                                                                            *
 * This software is owned by Microchip Technology Inc. ("Microchip") and is   *
 * supplied to you for use exclusively as described in the associated         *
 * software agreement.  This software is protected by software and other      *
 * intellectual property laws.  Any use in violation of the software license  *
 * may subject the user to criminal sanctions as well as civil liability.     *
 * Copyright 2006 Microchip Technology Inc.  All rights reserved.             *
 *                                                                            *
 * This software is provided "AS IS."  MICROCHIP DISCLAIMS ALL WARRANTIES,    *
 * EXPRESS, IMPLIED, STATUTORY OR OTHERWISE, NOT LIMITED TO MERCHANTABILITY,  *
 * FITNESS FOR A PARTICULAR PURPOSE, AND INFRINGEMENT. Microchip shall in no  *
 * event be liable for special, incidental, or consequential damages.         *
 *                                                                            *
 *- Version Log --------------------------------------------------------------*
 *   Date       Author        Comments                                        *
 *----------------------------------------------------------------------------*
 * 05/20/02 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 09/01/04 Howard Schlunder  Rewritten for SPI EEPROMs                       *
 * 08/10/06 Howard Schlunder  Modified to control SPI module frequency        *
 *                            whenever EEPROM accessed to allow bus sharing   *
 *                            with different frequencies.                     *
 * 03/30/07 Jorge Amodio      Added USE_SPIEEPROM, EEPROM_SAVE_SPI_CFG,       *
 *                            EEPROM_SPICON1_CFG, and EEPROM_SPISTAT_CFG      *
 *                            macros, removed I/O initialization code, it     *
 *                            asumes that it's done earlier in the main       *
 *                            initialization routine.                         *
 * 04/25/07 Jorge Amodio      Cleanup and moved to eeprom directory           *
 *                            added USE_SPIEEPROM macro                       *
 * 05/02/07 Jorge Amodio      Added support for 25LC1024 (24 bit addressing)  *
 * 06/19/07 Jorge Amodio      Added SPI Disable/Enable when SPI config switch *
 *                            (EEPROM_SAVE_SPI_CFG) is used, no need to save  *
 *                            SPISTAT, variables & code removed               *
 * 07/03/07 Jorge Amodio      Corrected EEPROM_SAVE_SPI_CFG due SSPEN mapping *
 ******************************************************************************/
#include "include/config.h"

#if defined(USE_SPIEEPROM)
#include "include/generic_typedefs.h"
#include "eeprom/include/xeeprom.h"


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
// EEPROM SPI opcodes
#define READ  0b00000011 // Read data from memory array beginning at selected address
#define WRITE 0b00000010 // Write data to memory array beginning at selected address
#define WRDI  0b00000100 // Reset the write enable latch (disable write operations)
#define WREN  0b00000110 // Set the write enable latch (enable write operations)
#define RDSR  0b00000101 // Read Status register
#define WRSR  0b00000001 // Write Status register


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
XEE_ADDR EEPROMAddress;
BYTE EEPROMBuffer[EEPROM_BUFFER_SIZE];
BYTE *EEPROMBufferPtr;


/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/

/******************************************************************************
 * Function:        void XEEInit(unsigned char speed)
 * PreCondition:    None
 * Input:           speed - not used (included for compatibility only)
 * Output:          None
 * Side Effects:    None
 * Overview:        
 * Note:            
 ******************************************************************************/
void XEEInit(unsigned char speed)
{
  // Current version of code asumes that the SPI interface has been
  // initialized to the proper configuration by the main application
  // initialization routine.
  // If SPI configuration has to be preserved and a particular mode has
  // to be set the macro EEPROM_SAVE_SPI_CFG will include the appropiate
  // code. This function is no longer called if the macro USE_SPI_EEPROM
  // is defined.
}

/******************************************************************************
 * Function:        XEE_RESULT XEEBeginRead(unsigned char control,XEE_ADDR address)
 * PreCondition:    XEEInit() is already called.
 * Input:           control - EEPROM control and address code.
 *                  address - Address at which read is to be performed.
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 * Side Effects:    None
 * Overview:        Sets internal address counter to given address.
 *                  Puts EEPROM in sequential read mode.
 * Note:            This function does not release I2C bus.
 *                  User must call XEEEndRead() when read is not longer
 *                  needed; I2C bus will released after XEEEndRead()
 *                  is called.
 ******************************************************************************/
XEE_RESULT XEEBeginRead(unsigned char control, XEE_ADDR address )
{
    // Save the address and emptry the contents of our local buffer
    EEPROMAddress = address;
    EEPROMBufferPtr = EEPROMBuffer + EEPROM_BUFFER_SIZE;

    return XEE_SUCCESS;
}

/******************************************************************************
 * Function:        XEE_RESULT XEERead(void)
 * PreCondition:    XEEInit() && XEEBeginRead() are already called.
 * Input:           None
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 * Side Effects:    None
 * Overview:        Reads next byte from EEPROM; internal address
 *                  is incremented by one.
 * Note:            This function does not release I2C bus.
 *                  User must call XEEEndRead() when read is not longer
 *                  needed; I2C bus will released after XEEEndRead()
 *                  is called.
 ******************************************************************************/
unsigned char XEERead(void)
{
    // Check if no more bytes are left in our local buffer
    if( EEPROMBufferPtr == EEPROMBuffer + EEPROM_BUFFER_SIZE )
    { 
        // Get a new set of bytes
        XEEReadArray(0, EEPROMAddress, EEPROMBuffer, EEPROM_BUFFER_SIZE);
        EEPROMAddress += EEPROM_BUFFER_SIZE;
        EEPROMBufferPtr = EEPROMBuffer;
    }

    // Return a byte from our local buffer
    return *EEPROMBufferPtr++;
}

/******************************************************************************
 * Function:        XEE_RESULT XEEEndRead(void)
 * PreCondition:    XEEInit() && XEEBeginRead() are already called.
 * Input:           None
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 * Side Effects:    None
 * Overview:        Ends sequential read cycle.
 * Note:            This function ends sequential cycle that was in
 *                  progress.  It releases I2C bus.
 ******************************************************************************/
XEE_RESULT XEEEndRead(void)
{
    return XEE_SUCCESS;
}

/******************************************************************************
 * Function:        XEE_RESULT XEEReadArray(unsigned char control,XEE_ADDR address,
 *                                          unsigned char *buffer,unsigned char length)
 * PreCondition:    XEEInit() is already called.
 * Input:           control     - Unused
 *                  address     - Address from where array is to be read
 *                  buffer      - Caller supplied buffer to hold the data
 *                  length      - Number of bytes to read.
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 * Side Effects:    None
 * Overview:        Reads desired number of bytes in sequential mode.
 *                  This function performs all necessary steps
 *                  and releases the bus when finished.
 * Note:            None
 ******************************************************************************/
XEE_RESULT XEEReadArray(unsigned char control,XEE_ADDR address,unsigned char *buffer,unsigned char length)
{
    BYTE Dummy;

#if defined(EEPROM_SAVE_SPI_CFG)
    #if defined(__18CXX)
    BYTE SPICONSave;
    #else
    WORD SPICONSave;
    #endif

    SPICONSave = EEPROM_SPICON1;
    EEPROM_SPIEN = 0;
    EEPROM_SPICON1 = EEPROM_SPICON1_CFG;
    EEPROM_SPIEN = 1;
#endif

    EEPROM_CS_IO = 0;

    // Send READ opcode
    EEPROM_SSPBUF = READ;

    while(!EEPROM_SPI_IF);

    Dummy = EEPROM_SSPBUF;
    EEPROM_SPI_IF = 0;
    
#if defined(USE_25LC1024)
    EEPROM_SSPBUF = ((XEE_ADDR_VAL*)&address)->v[2];

    while(!EEPROM_SPI_IF);

    Dummy = EEPROM_SSPBUF;
    EEPROM_SPI_IF = 0;
#endif

    EEPROM_SSPBUF = ((XEE_ADDR_VAL*)&address)->v[1];

    while(!EEPROM_SPI_IF);

    Dummy = EEPROM_SSPBUF;
    EEPROM_SPI_IF = 0;
    EEPROM_SSPBUF = ((XEE_ADDR_VAL*)&address)->v[0];

    while(!EEPROM_SPI_IF);

    Dummy = EEPROM_SSPBUF;
    EEPROM_SPI_IF = 0;

    while(length--)
    {
        EEPROM_SSPBUF = 0;

        while(!EEPROM_SPI_IF);

        *buffer++ = EEPROM_SSPBUF;
        EEPROM_SPI_IF = 0;
    };
    
    EEPROM_CS_IO = 1;

#if defined(EEPROM_SAVE_SPI_CFG)
    EEPROM_SPIEN = 0;
    EEPROM_SPICON1 = SPICONSave;
    EEPROM_SPIEN = 1;
#endif

    return XEE_SUCCESS;
}

/******************************************************************************
 * Function:        XEE_RESULT XEESetAddr(unsigned char control,XEE_ADDR address)
 * PreCondition:    XEEInit() is already called.
 * Input:           control     - data EEPROM control code
 *                  address     - address to be set for writing
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 * Side Effects:    None
 * Overview:        Modifies internal address counter of EEPROM.
 * Note:            Unlike XEESetAddr() in xeeprom.c for I2C EEPROM 
 *                  memories, this function is used only for writing
 *                  to the EEPROM.  Reads must use XEEBeginRead(), 
 *                  XEERead(), and XEEEndRead().
 *                  This function does not release the SPI bus.
 *                  User must close XEEClose() after this function
 *                  is called.
 ******************************************************************************/
XEE_RESULT XEESetAddr(unsigned char control, XEE_ADDR address)
{
    EEPROMAddress = address;
    EEPROMBufferPtr = EEPROMBuffer;
    return XEE_SUCCESS;
}

void DoWrite(void)
{
    BYTE Dummy;
    BYTE BytesToWrite;

#if defined(EEPROM_SAVE_SPI_CFG)
    #if defined(__18CXX)
    BYTE SPICONSave;
    #else
    WORD SPICONSave;
    #endif

    SPICONSave = EEPROM_SPICON1;
    EEPROM_SPIEN = 0;
    EEPROM_SPICON1 = EEPROM_SPICON1_CFG;
    EEPROM_SPIEN = 1;
#endif

    // Set the Write Enable latch
    EEPROM_CS_IO = 0;
    EEPROM_SSPBUF = WREN;

    while(!EEPROM_SPI_IF);

    Dummy = EEPROM_SSPBUF;
    EEPROM_SPI_IF = 0;
    EEPROM_CS_IO = 1;

    // Send WRITE opcode
    EEPROM_CS_IO = 0;
    EEPROM_SSPBUF = WRITE;

    while(!EEPROM_SPI_IF);

    Dummy = EEPROM_SSPBUF;
    EEPROM_SPI_IF = 0;
    
#if defined(USE_25LC1024)
    EEPROM_SSPBUF = ((XEE_ADDR_VAL*)&EEPROMAddress)->v[2];

    while(!EEPROM_SPI_IF);

    Dummy = EEPROM_SSPBUF;
    EEPROM_SPI_IF = 0;
#endif

    EEPROM_SSPBUF = ((XEE_ADDR_VAL*)&EEPROMAddress)->v[1];

    while(!EEPROM_SPI_IF);

    Dummy = EEPROM_SSPBUF;
    EEPROM_SPI_IF = 0;
    EEPROM_SSPBUF = ((XEE_ADDR_VAL*)&EEPROMAddress)->v[0];

    while(!EEPROM_SPI_IF);

    Dummy = EEPROM_SSPBUF;
    EEPROM_SPI_IF = 0;
    
    BytesToWrite = (BYTE)(EEPROMBufferPtr - EEPROMBuffer);
    EEPROMAddress += BytesToWrite;
    EEPROMBufferPtr = EEPROMBuffer;

    while(BytesToWrite--)
    {
        // Send the byte to write
        EEPROM_SSPBUF = *EEPROMBufferPtr++;

        while(!EEPROM_SPI_IF);

        Dummy = EEPROM_SSPBUF;
        EEPROM_SPI_IF = 0;
    }

    // Begin the write
    EEPROM_CS_IO = 1;

    EEPROMBufferPtr = EEPROMBuffer;

#if defined(EEPROM_SAVE_SPI_CFG)
    EEPROM_SPIEN = 0;
    EEPROM_SPICON1 = SPICONSave;
    EEPROM_SPIEN = 1;
#endif

    // Wait for write to complete
    while( XEEIsBusy(0) );
}

/******************************************************************************
 * Function:        XEE_RESULT XEEWrite(unsigned char val)
 * PreCondition:    XEEInit() && XEEBeginWrite() are already called.
 * Input:           val - Byte to be written
 * Output:          XEE_SUCCESS
 * Side Effects:    None
 * Overview:        Adds a byte to the current page to be writen when
 *                  XEEEndWrite() is called.
 * Note:            Page boundary cannot be exceeded or the byte 
 *                  to be written will be looped back to the 
 *                  beginning of the page.
 ******************************************************************************/
XEE_RESULT XEEWrite(unsigned char val)
{
    *EEPROMBufferPtr++ = val;

    if( EEPROMBufferPtr == EEPROMBuffer + EEPROM_BUFFER_SIZE )
    {
        DoWrite();
    }

    return XEE_SUCCESS;
}

/******************************************************************************
 * Function:        XEE_RESULT XEEEndWrite(void)
 * PreCondition:    XEEInit() && XEEBeginWrite() are already called.
 * Input:           None
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 * Side Effects:    None
 * Overview:        Instructs EEPROM to begin write cycle.
 * Note:            Call this function after either page full of bytes
 *                  written or no more bytes are left to load.
 *                  This function initiates the write cycle.
 *                  User must call for XEEIsBusy() to ensure that write
 *                  cycle is finished before calling any other
 *                  routine.
 ******************************************************************************/
XEE_RESULT XEEEndWrite(void)
{
    if( EEPROMBufferPtr != EEPROMBuffer )
    {
        DoWrite();
    }

    return XEE_SUCCESS;
}

/******************************************************************************
 * Function:        XEE_RESULT XEEIsBusy(unsigned char control)
 * PreCondition:    XEEInit() is already called.
 * Input:           control     - EEPROM control and address code.
 * Output:          XEE_READY if EEPROM is not busy
 *                  XEE_BUSY if EEPROM is busy
 *                  other value if failed.
 * Side Effects:    None
 * Overview:        Requests ack from EEPROM.
 * Note:            None
 ******************************************************************************/
XEE_RESULT XEEIsBusy(unsigned char control)
{
    BYTE_VAL result;

#if defined(EEPROM_SAVE_SPI_CFG)
    #if defined(__18CXX)
    BYTE SPICONSave;
    #else
    WORD SPICONSave;
    #endif

    SPICONSave = EEPROM_SPICON1;
    EEPROM_SPIEN = 0;
    EEPROM_SPICON1 = EEPROM_SPICON1_CFG;
    EEPROM_SPIEN = 1;
#endif

    EEPROM_CS_IO = 0;
    // Send RDSR - Read Status Register opcode
    EEPROM_SSPBUF = RDSR;

    while(!EEPROM_SPI_IF);

    result.Val = EEPROM_SSPBUF;
    EEPROM_SPI_IF = 0;
    
    // Get register contents
    EEPROM_SSPBUF = 0;

    while(!EEPROM_SPI_IF);

    result.Val = EEPROM_SSPBUF;
    EEPROM_SPI_IF = 0;
    EEPROM_CS_IO = 1;

#if defined(EEPROM_SAVE_SPI_CFG)
    EEPROM_SPIEN = 0;
    EEPROM_SPICON1 = SPICONSave;
    EEPROM_SPIEN = 1;
#endif

    return result.bits.b0 ? XEE_BUSY : XEE_SUCCESS;
}

#endif // USE_SPIEEPROM

