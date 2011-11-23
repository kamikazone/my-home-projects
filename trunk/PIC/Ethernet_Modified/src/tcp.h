/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack TCP module                   *
 *============================================================================*
 *                                                                            *
 * See tcp.c for details                                                      *
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
 * 05/08/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 12/05/03 Nilesh Rajbharti  Modified TCPProcess() prototype. See TCP.c for  *
 *                            more information.                               *
 * 02/25/07 Jorge Amodio      Added TCPSetRxBuffer(), see tcp.c               *
 ******************************************************************************/
#ifndef _TCP_H
#define _TCP_H

#include "net/include/stacktsk.h"
#include "net/include/tick.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
typedef BYTE TCP_SOCKET;
typedef WORD TCP_PORT;

// TCP States as defined by rfc793
typedef enum _TCP_STATE
{
    TCP_LISTEN = 0,
    TCP_SYN_SENT,
    TCP_SYN_RECEIVED,
    TCP_ESTABLISHED,
    TCP_FIN_WAIT_1,
    TCP_FIN_WAIT_2,
    TCP_CLOSING,
    TCP_TIME_WAIT,
    TCP_CLOSE_WAIT,
    TCP_LAST_ACK,
    TCP_CLOSED,
} TCP_STATE;

// Socket info. Union is used to create anonymous structure members.
typedef struct _SOCKET_INFO
{
    TCP_STATE smState;
    NODE_INFO remote;
    TCP_PORT localPort;
    TCP_PORT remotePort;
    BUFFER TxBuffer;
    WORD TxCount;
    WORD RxCount;
    WORD RemoteWindow;
    DWORD SND_SEQ;
    DWORD SND_ACK;
    BYTE RetryCount;
    TICK startTick;
    TICK TimeOut;
    struct
    {
        unsigned char bServer: 1;
        unsigned char bIsPutReady: 1;
        unsigned char bFirstRead: 1;
        unsigned char bIsGetReady: 1;
        unsigned char bIsTxInProgress: 1;
        unsigned char bACKValid: 1;
    } Flags;
} SOCKET_INFO;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define MAX_RETRY_COUNTS  (3)
#define INVALID_SOCKET    (0xfe)
#define UNKNOWN_SOCKET    (0xff)


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
#if !defined(_TCP_C)
// These are all sockets supported by this TCP.
extern SOCKET_INFO TCB[MAX_SOCKETS];
#endif


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#define REMOTE_HOST(s)    (TCB[s].remote)


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void TCPInit(void);
TCP_SOCKET TCPListen(TCP_PORT port);
TCP_SOCKET TCPConnect(NODE_INFO *remote, TCP_PORT port);
BOOL TCPIsConnected(TCP_SOCKET s);
void TCPDisconnect(TCP_SOCKET s);
BOOL TCPIsPutReady(TCP_SOCKET s);
BOOL TCPPut(TCP_SOCKET socket, BYTE byte);
BOOL TCPFlush(TCP_SOCKET socket);
BOOL TCPIsGetReady(TCP_SOCKET s);
BOOL TCPGet(TCP_SOCKET socket, BYTE *byte);
WORD TCPGetArray(TCP_SOCKET s, BYTE *buffer, WORD count);
BOOL TCPDiscard(TCP_SOCKET socket);
BOOL TCPProcess(NODE_INFO *remote,IP_ADDR *localIP,WORD len);
void TCPTick(void);
void TCPSetRxBuffer(TCP_SOCKET s, WORD Offset);

#endif // _TCP_H
