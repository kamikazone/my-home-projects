/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack UDP module                   *
 *============================================================================*
 *                                                                            *
 * See udp.c for details                                                      *
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
 * 03/19/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 ******************************************************************************/
#ifndef _UDP_H
#define _UDP_H

#include "net/include/stacktsk.h"
#include "net/include/ip.h"
#include "net/include/mac.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
typedef WORD UDP_PORT;
typedef BYTE UDP_SOCKET;

typedef struct _UDP_SOCKET_INFO
{
    NODE_INFO remoteNode;
    UDP_PORT  remotePort;
    UDP_PORT  localPort;
    WORD      TxCount;
    WORD      RxCount;
    BUFFER    TxBuffer;
    WORD      TxOffset;

    struct
    {
        unsigned char bFirstRead: 1;
    } Flags;

} UDP_SOCKET_INFO;

typedef struct _UDP_HEADER
{
    UDP_PORT  SourcePort;
    UDP_PORT  DestinationPort;
    WORD      Length;
    WORD      Checksum;
} UDP_HEADER;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define BROADCAST_ADDRESS   (0xffffffffL)
#define INVALID_UDP_SOCKET  (0xff)
#define INVALID_UDP_PORT    (0L)


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
/*
 * All module utilizing UDP module will get extern definition of
 * activeUDPSocket.  While UDP module itself will define activeUDPSocket.
 */
#if !defined(_UDP_C)
extern UDP_SOCKET activeUDPSocket;
extern UDP_SOCKET_INFO  UDPSocketInfo[MAX_UDP_SOCKETS];
#endif


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#define UDPIsPutReady(s)  (activeUDPSocket = s, MACIsTxReady(TRUE))
#define UDPSetTxBuffer(a, b) (UDPSocketInfo[activeUDPSocket].TxOffset = b, IPSetTxBuffer(a, b+sizeof(UDP_HEADER)))
#define UDPSetRxBuffer(a) IPSetRxBuffer(a+sizeof(UDP_HEADER))


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void UDPInit(void);
UDP_SOCKET UDPOpen(UDP_PORT localPort,NODE_INFO *remoteNode,UDP_PORT remotePort);
void UDPClose(UDP_SOCKET s);
BOOL UDPPut(BYTE v);
void UDPFlush(void);
BOOL UDPIsGetReady(UDP_SOCKET s);
BOOL UDPGet(BYTE *v);
void UDPDiscard(void);
BOOL UDPProcess(NODE_INFO *remoteNode,IP_ADDR *localIP,WORD len);

#endif // _UDP_H
