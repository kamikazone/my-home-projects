/******************************************************************************
 * Header definitions for general delay routines                              *
 *============================================================================*
 *                                                                            *
 * See delay.c for details                                                    *
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
 * 05/09/02 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 06/10/02 Nilesh Rajbharti  Fixed C18 ms and us routines                    *
 * 04/04/06 Howard Schlunder  Changed for C30                                 *
 * 04/25/07 Jorge Amodio      Cleanup & DelayMs fix                           *
 ******************************************************************************/
#ifndef _DELAY_H
#define _DELAY_H

#include "include/config.h"

#if defined(__18CXX)
#include <delays.h>
#endif

/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#if defined(__C30__)
#define Delay10us(x)             \
    {                            \
        unsigned long _dcnt;     \
        _dcnt=x*((unsigned long)(0.00001/(1.0/TCY_CLOCK)/6)); \
        while(_dcnt--);          \
    }

#else
#define Delay10us(us) Delay10TCYx(((TCY_CLOCK/1000000)*us))
#endif


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void DelayMs(unsigned int ms);

#endif // _DELAY_H

