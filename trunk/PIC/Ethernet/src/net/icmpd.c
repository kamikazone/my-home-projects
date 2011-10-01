/******************************************************************************
 * ICMP Daemon Module for Microchip TCP/IP Stack                              *
 *============================================================================*
 *                                                                            *
 * The current source code implements a basic ICMP deamon to accept and reply *
 * to ICMP REPLY messages (ping), no other ICMP messages are supported.       *
 *                                                                            *
 * Note: The current version only support ICMP REPLY requests with data       *
 * payloads with a maximum of 32 bytes, some systems may send by default      *
 * bigger payloads (such as Linux) in that case you have to specify a payload *
 * size no larger than 32 bytes, ex: ping -s32 your_ip_address                *
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
 * 04/30/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 09/08/04 Howard Schlunder  Added ENC28J60 DMA checksum support             *
 * 01/05/06 Howard Schlunder  Increased DMA checksum efficiency               *
 * 11/23/06 Jorge Amodio      Added STACK_USE_SW_CKSUM to select software     *
 *                            checksum calculation due ENC28J60 DMA silicon   *
 *                            bug for Rev 1-5, and enable other ethernet      *
 *                            controllers.                                    *
 * 04/25/07 Jorge Amodio      Cleanup, file name changed to icmpd.c           *
 ******************************************************************************/
#include "include/config.h"

#if defined(STACK_USE_ICMP)
#include "net/include/stacktsk.h"
#include "net/include/helpers.h"
#include "net/include/icmp.h"
#include "net/include/ip.h"
#include "net/include/mac.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
// ICMP packet definition
typedef struct _ICMP_PACKET
{
    BYTE  Type;
    BYTE  Code;
    WORD  Checksum;
    WORD  Identifier;
    WORD  SequenceNumber;
    BYTE  Data[MAX_ICMP_DATA];
} ICMP_PACKET;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define ICMP_HEADER_SIZE  (sizeof(ICMP_PACKET) - MAX_ICMP_DATA)


/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/

/******************************************************************************
 * Function:        void SwapICMPPacket(ICMP_PACKET* p)
 * PreCondition:    None
 * Input:           p - ICMP packet header
 * Output:          ICMP packet is swapped
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
static void SwapICMPPacket(ICMP_PACKET* p)
{
    p->Identifier = swaps(p->Identifier);
    p->SequenceNumber = swaps(p->SequenceNumber);
    p->Checksum = swaps(p->Checksum);
}

/******************************************************************************
 * Function:        BOOL ICMPGet(ICMP_CODE *code,BYTE *data,BYTE *len,WORD *id,WORD *seq)
 * PreCondition:    MAC buffer contains ICMP type packet.
 * Input:           code    - Buffer to hold ICMP code value
 *                  data    - Buffer to hold ICMP data
 *                  len     - Buffer to hold ICMP data length
 *                  id      - Buffer to hold ICMP id
 *                  seq     - Buffer to hold ICMP seq
 * Output:          TRUE if valid ICMP packet was received
 *                  FALSE otherwise.
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
BOOL ICMPGet(ICMP_CODE *code, BYTE *data, BYTE *len, WORD *id, WORD *seq)
{
    ICMP_PACKET packet;
    WORD CalcChecksum, ReceivedChecksum;

#if defined(STACK_USE_SW_CKSUM)
    WORD checksums[2];
#endif

    // Obtain the ICMP Header
    MACGetArray((BYTE*)&packet, ICMP_HEADER_SIZE);

#if defined(STACK_USE_HW_CKSUM)
    // Calculate the checksum using the Microchip MAC's DMA module
    // The checksum data includes the precomputed checksum in the 
    // header, so a valid packet will always have a checksum of 
    // 0x0000 if the packet is not disturbed.
    ReceivedChecksum = 0x0000;
    CalcChecksum = MACCalcRxChecksum(0+sizeof(IP_HEADER), *len);
#endif

    // Obtain the ICMP data payload
    *len -= ICMP_HEADER_SIZE;
    MACGetArray(data, *len);

#if defined(STACK_USE_SW_CKSUM)
    // Calculte the checksum in local memory without hardware help
    ReceivedChecksum = packet.Checksum;
    packet.Checksum = 0;
    checksums[0] = ~CalcIPChecksum((BYTE*)&packet, ICMP_HEADER_SIZE);
    checksums[1] = ~CalcIPChecksum(data, *len);
    CalcChecksum = CalcIPChecksum((BYTE*)checksums, 2 * sizeof(WORD));
#endif

    SwapICMPPacket(&packet);
    *code = packet.Type;
    *id = packet.Identifier;
    *seq = packet.SequenceNumber;

    return ( CalcChecksum == ReceivedChecksum );
}

/******************************************************************************
 * Function:        void ICMPPut(NODE_INFO *remote, ICMP_CODE code,BYTE *data,BYTE len,WORD id,WORD seq)
 * PreCondition:    ICMPIsTxReady() == TRUE
 * Input:           remote      - Remote node info
 *                  code        - ICMP_ECHO_REPLY or ICMP_ECHO_REQUEST
 *                  data        - Data bytes
 *                  len         - Number of bytes to send
 *                  id          - ICMP identifier
 *                  seq         - ICMP sequence number
 * Output:          None
 * Side Effects:    None
 * Note:            A ICMP packet is created and put on MAC.
 ******************************************************************************/
void ICMPPut(NODE_INFO *remote, ICMP_CODE code, BYTE *data, BYTE len, WORD id, WORD seq)
{
    ICMP_PACKET packet;
    WORD ICMPLen;
    BUFFER MyTxBuffer = MACGetTxBuffer(TRUE);

    // Abort if there is no where in the Ethernet controller to 
    // store this packet.
    if(MyTxBuffer == INVALID_BUFFER)
        return;

    IPSetTxBuffer(MyTxBuffer, 0);
    ICMPLen = ICMP_HEADER_SIZE + (WORD)len;
    packet.Code = 0;
    packet.Type = code;
    packet.Checksum = 0;
    packet.Identifier = id;
    packet.SequenceNumber = seq;
    memcpy((void*)packet.Data, (void*)data, len);
    SwapICMPPacket(&packet);

#if defined(STACK_USE_SW_CKSUM)
    packet.Checksum = CalcIPChecksum((BYTE*)&packet, ICMPLen);
#endif

    IPPutHeader(remote, IP_PROT_ICMP, (WORD)(ICMP_HEADER_SIZE + len));
    IPPutArray((BYTE*)&packet, ICMPLen);

#if defined(STACK_USE_HW_CKSUM)
    // Calculate and write the ICMP checksum using the Microchip MAC's DMA
    packet.Checksum = MACCalcTxChecksum(sizeof(IP_HEADER), ICMPLen);
    IPSetTxBuffer(MyTxBuffer, 2);
    MACPutArray((BYTE*)&packet.Checksum, 2);
#endif

    MACFlush();
}

#endif  // STACK_USE_ICMP
