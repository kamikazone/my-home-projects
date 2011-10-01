/******************************************************************************
 * Header definitions for UART Access routines for C18 and C30                *
 *============================================================================*
 *                                                                            *
 * See uart.c for details                                                     *
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
 * 06/16/06 Howard Schlunder  Original                                        *
 * 04/25/07 Jorge Amodio      Cleanup and moved to its own directory          *
 * 06/18/07 Jorge Amodio      Removed include <uart.h> it had no effect       *
 ******************************************************************************/
#ifndef _UART_H
#define _UART_H

/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
#if defined(__C30__)

void putsUART2(unsigned int *buffer);
unsigned int getsUART2(unsigned int length,unsigned int *buffer,
                       unsigned int uart_data_wait);
char DataRdyUART2(void);
char BusyUART2(void);
unsigned int ReadUART2(void);
void WriteUART2(unsigned int data);

#else

char BusyUSART(void);
void CloseUSART(void);
char DataRdyUSART(void);
char ReadUSART(void);
void WriteUSART(char data);
void getsUSART(char *buffer, unsigned char len);
void putsUSART(char *data);
void putrsUSART(const rom char *data);

#endif

#endif  // _UART_H
