/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack ICMP Daemon Module           *
 *============================================================================*
 *                                                                            *
 *  See icmpd.c for details                                                   *
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
 * 04/27/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 04/25/07 Jorge Amodio      Cleanup                                         *
 ******************************************************************************/
#ifndef _ICMP_H
#define _ICMP_H

#include "net/include/stacktsk.h"
#include "net/include/ip.h"
#include "net/include/mac.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
typedef enum _ICMP_CODE
{
    ICMP_ECHO_REPLY = 0,
    ICMP_ECHO_REQUEST = 8
} ICMP_CODE, ICMP_REQUESTS;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define MAX_ICMP_DATA       (32)
#define MAX_ICMP_DATA_LEN   (MAX_ICMP_DATA)


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#define ICMPIsTxReady()     MACIsTxReady(TRUE)


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void ICMPPut(NODE_INFO *remote,ICMP_CODE code,BYTE *data,BYTE len,WORD id,WORD seq);
BOOL ICMPGet(ICMP_CODE *code,BYTE *data,BYTE *len,WORD *id,WORD *seq);

#endif // _ICMP_H
