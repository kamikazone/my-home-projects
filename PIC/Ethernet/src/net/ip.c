/******************************************************************************
 * IP Module for Microchip TCP/IP Stack                                       *
 *============================================================================*
 *                                                                            *
 * The current source code file implements the IP layer of the TCP/IP         *
 * protocol suite.                                                            *
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
 * 04/27/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 08/31/04 Howard Schlunder  Beta Rev 0.9 (See version.log for detail)       *
 * 01/05/06 Howard Schlunder  Improved DMA checksum efficiency                *
 * 11/23/06 Jorge Amodio      Added STACK_USE_SW_CKSUM to select software     *
 *                            checksum calculation due ENC28J60 DMA silicon   *
 *                            bug for Rev 1-5, and enable other ethernet      *
 *                            controllers.                                    *
 * 04/25/07 Jorge Amodio      Cleanup                                         *
 ******************************************************************************/
#include "net/include/stacktsk.h"
#include "net/include/helpers.h"
#include "net/include/mac.h"
#include "net/include/ip.h"

/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
// This is left shifted by 4.  Actual value is 0x04.
#define IPv4                (0x40u)
#define IP_VERSION          IPv4

// IHL (Internet Header Length) is # of DWORDs in a header.
// Since, we do not support options, our IP header length will be
// minimum i.e. 20 bytes : IHL = 20 / 4 = 5.
#define IP_IHL              (0x05)

#define IP_SERVICE_NW_CTRL  (0x07)
#define IP_SERVICE_IN_CTRL  (0x06)
#define IP_SERVICE_ECP      (0x05)
#define IP_SERVICE_OVR      (0x04)
#define IP_SERVICE_FLASH    (0x03)
#define IP_SERVICE_IMM      (0x02)
#define IP_SERVICE_PRIOR    (0x01)
#define IP_SERVICE_ROUTINE  (0x00)

#define IP_SERVICE_N_DELAY  (0x00)
#define IP_SERCICE_L_DELAY  (0x08)
#define IP_SERVICE_N_THRPT  (0x00)
#define IP_SERVICE_H_THRPT  (0x10)
#define IP_SERVICE_N_RELIB  (0x00)
#define IP_SERVICE_H_RELIB  (0x20)

#define IP_SERVICE          (IP_SERVICE_ROUTINE | IP_SERVICE_N_DELAY)
#define MY_IP_TTL           (100)  // Time-To-Live in Seconds


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
static WORD _Identifier = 0;
static BYTE IPHeaderLen;
unsigned long IP_RX_pktcnt = 0, IP_TX_pktcnt = 0;


/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/
static void SwapIPHeader(IP_HEADER* h)
{
    h->TotalLength = swaps(h->TotalLength);
    h->Identification = swaps(h->Identification);
    h->HeaderChecksum = swaps(h->HeaderChecksum);
}

/******************************************************************************
 * Function:        BOOL IPGetHeader(IP_ADDR *localIP,NODE_INFO *remote,BYTE *Protocol,WORD *len)
 * PreCondition:    MACGetHeader() == TRUE
 * Input:           localIP     - Local node IP Address as received
 *                                in current IP header.
 *                                If this information is not required
 *                                caller may pass NULL value.
 *                  remote      - Remote node info
 *                  Protocol    - Current packet protocol
 *                  len         - Current packet data length
 * Output:          TRUE, if valid packet was received
 *                  FALSE otherwise
 * Side Effects:    None
 * Note:            Only one IP message can be received.
 *                  Caller may not transmit and receive a message
 *                  at the same time.
 ******************************************************************************/
BOOL IPGetHeader(IP_ADDR *localIP, NODE_INFO *remote, BYTE *protocol, WORD *len)
{
    WORD_VAL CalcChecksum;
    IP_HEADER header;

#if defined(STACK_USE_SW_CKSUM)
    WORD_VAL ReceivedChecksum;
    WORD checksums[2];
    BYTE optionsLen;

#define MAX_OPTIONS_LEN  (40)          // As per RFC 791.
    BYTE options[MAX_OPTIONS_LEN];
#endif

    // Read IP header.
    MACGetArray((BYTE*)&header, sizeof(header));

    // Make sure that this is an IPv4 packet.
    if ( (header.VersionIHL & 0xf0) != IP_VERSION )
        return FALSE;

#if defined(STACK_USE_HW_CKSUM)
    IPHeaderLen = (header.VersionIHL & 0x0f) << 2;
    
    // Validate the IP header.  If it is correct, the checksum
    // will come out to 0x0000 (because the header contains a
    // precomputed checksum).  A corrupt header will have a
    // nonzero checksum.
    CalcChecksum.Val = MACCalcRxChecksum(0, IPHeaderLen);

    // Seek to the end of the IP header
    MACSetRxBuffer(IPHeaderLen);

    if(CalcChecksum.Val)
#else
    // Calculate options length in this header, if there is any.
    // IHL is in terms of numbers of 32-bit DWORDs; i.e. actual
    // length is 4 times IHL.
    optionsLen = ((header.VersionIHL & 0x0f) << 2) - sizeof(header);

    // If there is any option(s), read it so that we can include them
    // in checksum calculation.
    if ( optionsLen > MAX_OPTIONS_LEN )
        return FALSE;

    if ( optionsLen > 0 ) MACGetArray(options, optionsLen);

    // Save header checksum; clear it and recalculate it ourselves.
    ReceivedChecksum.Val = header.HeaderChecksum;
    header.HeaderChecksum = 0;

    // Calculate checksum of header including options bytes.
    checksums[0] = ~CalcIPChecksum((BYTE*)&header, sizeof(header));

    // Calculate Options checksum too, if they are present.
    if ( optionsLen > 0 )
        checksums[1] = ~CalcIPChecksum((BYTE*)options, optionsLen);
    else
        checksums[1] = 0;

    CalcChecksum.Val = CalcIPChecksum((BYTE*)checksums, 2 * sizeof(WORD));

    // Make sure that checksum is correct
    if ( ReceivedChecksum.Val != CalcChecksum.Val )
#endif

    {
        // Bad packet. The function caller will be notified by means of the FALSE
        // return value and it should discard the packet.
        return FALSE;
    }

    // Network to host conversion.
    SwapIPHeader(&header);

    // If caller is intrested, return destination IP address
    // as seen in this IP header.
    if ( localIP ) localIP->Val = header.DestAddress.Val;

    remote->IPAddr.Val = header.SourceAddress.Val;
    *protocol = header.Protocol;

#if defined(STACK_USE_HW_CKSUM)
    *len = header.TotalLength - IPHeaderLen;
#else
    *len = header.TotalLength - optionsLen - sizeof(header);
#endif

    IP_RX_pktcnt++;

    return TRUE;
}

/******************************************************************************
 * Function: WORD IPPutHeader(NODE_INFO *remote,BYTE protocol,WORD len)
 * PreCondition:    IPIsTxReady() == TRUE
 * Input:           *remote     - Destination node address
 *                  protocol    - Current packet protocol
 *                  len         - Current packet data length
 * Output:          (WORD)0
 * Side Effects:    None
 * Note:            Only one IP message can be transmitted at any
 *                  time.
 ******************************************************************************/
WORD IPPutHeader(NODE_INFO *remote, BYTE protocol, WORD len)
{
    IP_HEADER header;

    IPHeaderLen = sizeof(IP_HEADER);
    header.VersionIHL = IP_VERSION | IP_IHL;
    header.TypeOfService  = IP_SERVICE;
    header.TotalLength = sizeof(header) + len;
    header.Identification = ++_Identifier;
    header.FragmentInfo = 0;
    header.TimeToLive = MY_IP_TTL;
    header.Protocol = protocol;
    header.HeaderChecksum = 0;
    header.SourceAddress = AppConfig.MyIPAddr;
    header.DestAddress.Val = remote->IPAddr.Val;
    SwapIPHeader(&header);

#if defined(STACK_USE_SW_CKSUM)
    header.HeaderChecksum = CalcIPChecksum((BYTE*)&header, sizeof(header));
#endif

    MACPutHeader(&remote->MACAddr, MAC_IP, (sizeof(header)+len));
    MACPutArray((BYTE*)&header, sizeof(header));

#if defined(STACK_USE_HW_CKSUM)
    header.HeaderChecksum = MACCalcTxChecksum(0, sizeof(header));
    MACSetTxBuffer(CurrentTxBuffer, 10);                 // 10 is the offset in header to the HeaderChecksum member
    MACPutArray((BYTE*)&header.HeaderChecksum, 2);
    MACSetTxBuffer(CurrentTxBuffer, sizeof(header));     // Seek back to the end of the packet
#endif   
 
    IP_TX_pktcnt++;

    return 0x0;
}

/******************************************************************************
 * Function:        IPSetRxBuffer(WORD Offset)
 * PreCondition:    IPHeaderLen must have been intialized by 
 *                  IPGetHeader() or IPPutHeader()
 * Input:           Offset from beginning of IP data field
 * Output:          Next Read/Write access to receive buffer is
 *                  set to Offset 
 * Side Effects:    None
 * Note:            None
 ******************************************************************************/
void IPSetRxBuffer(WORD Offset) 
{
    MACSetRxBuffer(Offset+IPHeaderLen);
}
