/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack Tick Manager module          *
 *============================================================================*
 *                                                                            *
 * See tick.c for details                                                     *
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
 * 06/28/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 ******************************************************************************/
#ifndef _TICK_H
#define _TICK_H

#include "include/config.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
typedef unsigned long TICK;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define TICK_PERIOD_MS  10
#define TICK_SECOND     ((TICK)TICKS_PER_SECOND)


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
#if !defined(_TICK_C)
extern TICK TickCount;
#endif


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#define TickGetDiff(a, b)  (a-b)


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void TickInit(void);
TICK TickGet(void);
void TickUpdate(void);

#endif // _TICK_H
