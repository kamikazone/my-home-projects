/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack MAC module                   *
 *============================================================================*
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
 * 11/27/01 Nilesh Rajbharti  Added SLIP                                      *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 06/28/04 Howard Schlunder  Added ENC28J60 specific features                *
 * 11/29/04 Howard Schlunder  Added Get/SetLEDConfig macros                   *
 * 11/23/06 Jorge Amodio      Added STACK_USE_HW_CKSUM macro for conditional  *
 *                            compiliation of checksum functions due DMA      *
 *                            silicon bug for Rev 1-5                         *
 * 04/25/07 Jorge Amodio      Cleanup                                         *
 * 07/03/07 Jorge Amodio      Added __PIC18FXX60                              *
 ******************************************************************************/
#ifndef _MAC_H
#define _MAC_H

#include "stacktsk.h"
#if defined(__18F97J60) || defined(__18F96J65) || defined(__18F96J60) || defined(__18F87J60) || defined(__18F86J65) || defined(__18F86J60) || defined(__18F67J60) || defined(__18F66J65) || defined(__18F66J60) 
    #include "net/include/eth97j60.h"
#elif defined(USE_ENC28J60)
    #include "enc28j60.h"
#endif

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
#if defined(USE_ENC28J60) || defined(__PIC18FXXJ60)
typedef enum _DUPLEX {
    HALF = 0, 
    FULL = 1, 
    USE_PHY = 2
} DUPLEX;

typedef enum _CLK_CONFIG {
    Divide1,
    Divide2,
    Divide3,
    Divide4,
    Divide8
} CLK_CONFIG;
#endif


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define MAC_IP      (0u)
#define MAC_ARP     (0x6u)
#define MAC_UNKNOWN (0x0ffu)
#define INVALID_BUFFER  (0xffu)


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
//extern BUFFER CurrentTxBuffer;


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#if defined(USE_ENC28J60)|| defined(__PIC18FXXJ60)
#define SetLEDConfig(NewConfig)  WritePHYReg(PHLCON, NewConfig)
#define GetLEDConfig()  ReadPHYReg(PHLCON).Val
#endif

/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void MACInit(void);
BOOL MACIsLinked(void);
BOOL MACGetHeader(MAC_ADDR *remote, BYTE* type);
void MACSetRxBuffer(WORD offset);
BYTE MACGet(void);
WORD MACGetArray(BYTE *val, WORD len);
void MACDiscardRx(void);
WORD MACGetFreeRxSize(void);
void MACPutHeader(MAC_ADDR *remote, BYTE type, WORD dataLen);
BOOL MACIsTxReady(BOOL HighPriority);
void MACSetTxBuffer(BUFFER buffer, WORD offset);
void MACPut(BYTE val);
void MACPutArray(BYTE *val, WORD len);
void MACDiscardTx(BUFFER buffer);
void MACFlush(void);
BUFFER MACGetTxBuffer(BOOL HighPriority);

#if defined(USE_ENC28J60)|| defined(__PIC18FXXJ60)
void MACSetDuplex(DUPLEX DuplexState);
void MACPowerDown(void);
void MACPowerUp(void);
void MACCopyRxToTx(WORD RxOffset, WORD TxOffset, WORD len);
void WritePHYReg(BYTE Register, WORD Data);
PHYREG ReadPHYReg(BYTE Register);
void SetRXHashTableEntry(MAC_ADDR DestMACAddr);

#if defined(STACK_USE_HW_CKSUM)
WORD MACCalcRxChecksum(WORD offset, WORD len);
WORD MACCalcTxChecksum(WORD offset, WORD len);
WORD CalcIPBufferChecksum(WORD len);
#endif

#endif // USE_ENC28J60

#endif // _MAC_H
