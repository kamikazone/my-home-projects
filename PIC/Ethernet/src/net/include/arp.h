/******************************************************************************
 * Header definitions for Microchip TCP/Stack ARP Module                      *
 *============================================================================*
 *                                                                            *
 * See arp.c for details                                                      *
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
 * 05/01/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 02/08/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 04/25/07 Jorge Amodio      Cleanup and merged with ArpTsk.h                *
 ******************************************************************************/
#ifndef _ARP_H
#define _ARP_H

#include "net/include/stacktsk.h"
#include "net/include/mac.h"

/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define ARP_REPLY       (0x00)
#define ARP_REQUEST     (0x01)
#define ARP_UNKNOWN     (0x02)


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#define ARPIsTxReady()      MACIsTxReady(TRUE)


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
BOOL ARPGet(NODE_INFO *remote, BYTE *opCode);
BOOL ARPPut(NODE_INFO *remote, BYTE opCode);
void ARPInit(void);
BOOL ARPProcess(void);
void ARPResolve(IP_ADDR *IPAddr);
BOOL ARPIsResolved(IP_ADDR *IPAddr, MAC_ADDR *MACAddr);

#endif // _ARP_H
