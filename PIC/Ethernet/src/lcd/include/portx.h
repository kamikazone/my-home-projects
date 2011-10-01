/******************************************************************************
 * Microchip MCP23S08 I/O Port Extender Driver Headers                        *
 *============================================================================*
 *                                                                            *
 * See "mcp23s08.c" for details.                                              *
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
#ifndef _PORTX_H
#define _PORTX_H

#include "lcd/include/mcp23s08.h"

/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#define ReadPortX()    ReadPortXReg(PXGPIO)
#define ReadPortXLAT() ReadPortXReg(PXOLAT)
#define WritePortX(a) WritePortXReg(PXOLAT,a)


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
unsigned char ReadPortXReg(unsigned char RegAddr);
void WritePortXReg(unsigned char RegAddr, unsigned char Value);
void BitSetPortX(unsigned char p);
void BitClearPortX(unsigned char p);
void InitPortX(unsigned char iodir);

#endif // _PORTX_H

