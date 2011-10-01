/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack helper functions             *
 *============================================================================*
 *                                                                            *
 * See helpers.c for details                                                  *
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
 * 05/17/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 04/25/07 Jorge Amodio      More cleanup. Added ultoa function for C30      *
 ******************************************************************************/
#ifndef _HELPERS_H
#define _HELPERS_H

#include "include/config.h"
#include "include/generic_typedefs.h"

/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
BYTE ReadStringUART(BYTE *Dest, BYTE BufferLen);
BYTE hexatob(WORD_VAL AsciiChars);
BYTE btohexa_high(BYTE b);
BYTE btohexa_low(BYTE b);
WORD swaps(WORD v);
DWORD swapl(DWORD v);
WORD CalcIPChecksum(BYTE *buffer, WORD len);

#if defined(STACK_USE_SW_CKSUM)
WORD CalcIPBufferChecksum(WORD len);
#endif

#if defined(__C30__)
void itoa(unsigned int Value, char* Buffer);
void ultoa(unsigned long Value, char* Buffer);
char *strupr(char *s);
#endif

#endif  // _HELPERS_H
