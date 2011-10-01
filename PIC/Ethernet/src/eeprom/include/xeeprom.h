/******************************************************************************
 * Header definitions for external serial EEPROM memory drivers               *
 *============================================================================*
 *                                                                            *
 * See spieeprom.c and i2ceeprom.c for details                                *
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
 * 05/02/07 Jorge Amodio      XEE_ADDR is now defined depending on the memory *
 *                            to select proper addressing word lenght         *
 ******************************************************************************/
#ifndef _XEEPROM_H
#define _XEEPROM_H
#include "include/config.h"
#include "include/generic_typedefs.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
typedef enum _XEE_RESULT
{
    XEE_SUCCESS = 0,
    XEE_READY = 0,
    XEE_BUS_COLLISION,
    XEE_NAK,
    XEE_VERIFY_ERR,
    XEE_BUSY
} XEE_RESULT;

#if defined(USE_25LC1024)
  typedef unsigned short long XEE_ADDR;
  typedef union _XEE_ADDR_VAL
  {
    LWORD Val;
    BYTE v[3];
  } XEE_ADDR_VAL;
#else
  typedef unsigned short int XEE_ADDR;
  typedef union _XEE_ADDR_VAL
  {
    WORD Val;
    BYTE v[2];
  } XEE_ADDR_VAL;
#endif  

/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#define EE_BAUD(CLOCK, BAUD)  ( ((CLOCK / BAUD) / 4) - 1 )
#define XEEBeginWrite(control, address)  XEESetAddr(control, address)


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void XEEInit(BYTE baud);
XEE_RESULT XEESetAddr(BYTE control, XEE_ADDR address);
XEE_RESULT XEEWrite(BYTE val);
XEE_RESULT XEEEndWrite(void);
XEE_RESULT XEEBeginRead(BYTE control, XEE_ADDR address);
BYTE XEERead(void);
XEE_RESULT XEEEndRead(void);
XEE_RESULT XEEReadArray(BYTE control,XEE_ADDR address,BYTE *buffer,BYTE length);
XEE_RESULT XEEIsBusy(BYTE control);

#endif // _XEEPROM_H
