/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack UDP Test module              *
 *============================================================================*
 *                                                                            *
 * See udptest.c for details                                                  *
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
 * 05/10/07 Jorge Amodio      Original                                        *
 ******************************************************************************/
#ifndef _UDPTEST_H
#define _UDPTEST_H


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
//#define UDP_TST_TARGET_MAC     {0xff,0xff,0xff,0xff,0xff,0xff}
//#define UDP_TST_TARGET_IP      {255,255,255,255}
#define UDP_TST_TARGET_MAC     {0x00,0x01,0x02,0xc5,0x33,0x47}
#define UDP_TST_TARGET_IP      {192,168,1,1}
#define UDP_TST_TARGET_PORT    12345


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void UDPTest(void);

#endif // _UDPTEST_H
