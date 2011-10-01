/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack IP module                    *
 *============================================================================*
 *                                                                            *
 *  See ip.c for details                                                      *
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
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 04/25/07 Jorge Amodio      Cleanup                                         *
 ******************************************************************************/
#ifndef _IP_H
#define _IP_H

#include "net/include/stacktsk.h"
#include "net/include/mac.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/

// IP packet header definition
typedef struct _IP_HEADER
{
    BYTE    VersionIHL;
    BYTE    TypeOfService;
    WORD    TotalLength;
    WORD    Identification;
    WORD    FragmentInfo;
    BYTE    TimeToLive;
    BYTE    Protocol;
    WORD    HeaderChecksum;
    IP_ADDR SourceAddress;
    IP_ADDR DestAddress;

} IP_HEADER;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define IP_PROT_ICMP    (1)
#define IP_PROT_TCP     (6)
#define IP_PROT_UDP     (17)


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#define IPIsTxReady(HighPriority)  MACIsTxReady(HighPriority)
#define IPSetTxBuffer(a, b)        MACSetTxBuffer(a, b+sizeof(IP_HEADER))
#define IPDiscard()                MACDiscard()
#define IPGetArray(a, b)           MACGetArray(a, b)
#define IPPutArray(a, b)           MACPutArray(a, b)


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
WORD IPPutHeader(NODE_INFO *remote,BYTE protocol,WORD len);
BOOL IPGetHeader(IP_ADDR *localIP,NODE_INFO *remote,BYTE *protocol,WORD *len);
void IPSetRxBuffer(WORD Offset);

#endif // _IP_H
