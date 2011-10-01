/******************************************************************************
 * HD44780/KS0066 Character Mode LCD Display Driver Header file               *
 *============================================================================*
 *                                                                            *
 * See "cmlcddriver.c" for details.                                           *
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
#ifndef _CMLCDDRIVER_H
#define _CMLCDDRIVER_H

#include "include/config.h"

/******************************************************************************
 * Local & external variables & constants for this module                     *
 ******************************************************************************/
#if defined(LCD_USE_BUFFER)
extern unsigned char LCDBuffer[LCD_ROWS][LCD_COLS];
#endif

#if defined(LCD_USE_CGCHARS)
// Some predefined character bitmaps
ROM char const CGCHAR00[] = { 0b00000,\
                              0b00000,\
                              0b00000,\
                              0b00000,\
                              0b00000,\
                              0b00000,\
                              0b00000,\
                              0b00000 };

ROM char const CGCHAR01[] = { 0b00001,\
                              0b00011,\
                              0b00111,\
                              0b01110,\
                              0b11110,\
                              0b11110,\
                              0b11110,\
                              0b11100 };

ROM char const CGCHAR02[] = { 0b11111,\
                              0b11111,\
                              0b11111,\
                              0b11111,\
                              0b11110,\
                              0b01110,\
                              0b01110,\
                              0b00111 };

ROM char const CGCHAR03[] = { 0b10000,\
                              0b11000,\
                              0b11000,\
                              0b11100,\
                              0b01100,\
                              0b00110,\
                              0b00111,\
                              0b00011 };

ROM char const CGCHAR04[] = { 0b11001,\
                              0b11001,\
                              0b10001,\
                              0b00001,\
                              0b00011,\
                              0b00111,\
                              0b00011,\
                              0b00001 };

ROM char const CGCHAR05[] = { 0b00111,\
                              0b00011,\
                              0b00001,\
                              0b10001,\
                              0b10001,\
                              0b11011,\
                              0b11111,\
                              0b11111 };

ROM char const CGCHAR06[] = { 0b10001,\
                              0b11000,\
                              0b11100,\
                              0b11110,\
                              0b11110,\
                              0b11100,\
                              0b11000,\
                              0b10000 };
#endif // LCD_USE_CGCHARS


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void LCDInit(void);
void LCDClear(void);
void LCDClearRow(unsigned char row);
void LCDSend(unsigned char cmd, unsigned char data);
void LCDGoto(unsigned char row, unsigned char col);
void LCDWriteStr(char *s);
void LCDWritePGMStr(ROM char const *s);

#if defined(LCD_USE_BUFFER)
void LCDRefresh(void);
void LCDClearBuffer(void);
void LCDClearBufferRow(unsigned char row);
#endif

#if defined(LCD_USE_CGCHARS)
void LCDLoadCGRAM(unsigned char c, ROM char *p);
#endif

#endif // _CMLCDDRIVER_H

