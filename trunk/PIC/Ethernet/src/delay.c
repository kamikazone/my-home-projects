/******************************************************************************
 * General Delay Routines                                                     *
 *============================================================================*
 *                                                                            *
 * The current source file implements a delay support function for the        *
 * Microchip C18/C30 Compilers.                                               *
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
 * 05/09/02 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 04/25/07 Jorge Amodio      Cleanup & included DelayMs for C18 too          *
 ******************************************************************************/
#include "include/delay.h"

/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/
void DelayMs(unsigned int ms)
{
    unsigned char i;

    while(ms--)
    {
        i=4;

        while(i--)
        {
            Delay10us(25);
        }
    }
}
