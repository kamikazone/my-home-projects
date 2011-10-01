/******************************************************************************
 * ARP Module for Microchip TCP/IP Stack                                      *
 *============================================================================*
 *                                                                            *
 * The ARP Module includes the functions to implement the Address Resolution  *
 * Protocol for Ethernet. The code includes a state machine that is part of   *
 * the main stack state machine (StackTsk), taking care of ARP requests for   *
 * the configured IP Address.                                                 *
 *                                                                            *
 * If the TCP/IP stack is compiled with the STACK_CLIENT_MODE the code        *
 * includes two additional functions to provide ARP resolution for local      *
 * clients. The current version has an ARP cache that is one entry deep.      *
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
 * 05/01/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0                                         *
 * 04/25/07 Jorge Amodio      Cleanup and code merge with ArpTsk.c            *                           *
 ******************************************************************************/
#include "net/include/stacktsk.h"
#include "net/include/helpers.h"
#include "net/include/arp.h"
#include "net/include/mac.h"


/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
// ARP packet
typedef struct _ARP_PACKET
{
    WORD     HardwareType;
    WORD     Protocol;
    BYTE     MACAddrLen;
    BYTE     ProtocolLen;
    WORD     Operation;
    MAC_ADDR SenderMACAddr;
    IP_ADDR  SenderIPAddr;
    MAC_ADDR TargetMACAddr;
    IP_ADDR  TargetIPAddr;
} ARP_PACKET;

// ARP Task FSM States
typedef enum _ARP_STATE
{
    SM_ARP_IDLE,
    SM_ARP_REPLY
} ARP_STATE;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
// ARP Operation codes.
#define ARP_OPERATION_REQ   0x01u
#define ARP_OPERATION_RESP  0x02u

// ETHERNET packet type as defined by IEEE 802.3
#define HW_ETHERNET         (0x0001u)
#define ARP_IP              (0x0800u)


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
static ARP_STATE smARP;

// This ARP task caches one ARP response.
#if defined(STACK_CLIENT_MODE)
static NODE_INFO Cache;
#endif

/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/

/******************************************************************************
 * Function:        static void SwapARPPacket(ARP_PACKET* p)
 * PreCondition:    None
 * Input:           p   - ARP packet to be swapped.
 * Output:          None
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
static void SwapARPPacket(ARP_PACKET *p)
{
    p->HardwareType = swaps(p->HardwareType);
    p->Protocol = swaps(p->Protocol);
    p->Operation = swaps(p->Operation);
}

/******************************************************************************
 * Function:        BOOL ARPGet(NODE_INFO* remote, BYTE* opCode)
 * PreCondition:    ARP packet is ready in MAC buffer.
 * Input:           remote  - Remote node info
 *                  opCode  - Buffer to hold ARP op code.
 * Output:          TRUE if a valid ARP packet was received.
 *                  FALSE otherwise.
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
BOOL ARPGet(NODE_INFO *remote, BYTE *opCode)
{
    ARP_PACKET packet;

    MACGetArray((BYTE*)&packet, sizeof(packet));
    MACDiscardRx();
    SwapARPPacket(&packet);

    if ( packet.HardwareType != HW_ETHERNET  || packet.MACAddrLen != sizeof(MAC_ADDR) ||
         packet.ProtocolLen != sizeof(IP_ADDR) )
    {
         return FALSE;
    }

    if ( packet.Operation == ARP_OPERATION_RESP )
    {   
        *opCode = ARP_REPLY;
    }
    else if ( packet.Operation == ARP_OPERATION_REQ )
        *opCode = ARP_REQUEST;
    else
    {
        *opCode = ARP_UNKNOWN;
        return FALSE;
    }

    if(packet.TargetIPAddr.Val == AppConfig.MyIPAddr.Val)
    {
        remote->MACAddr = packet.SenderMACAddr;
        remote->IPAddr = packet.SenderIPAddr;
        return TRUE;
    }
    else
        return FALSE;
}

/******************************************************************************
 * Function:        BOOL ARPPut(NODE_INFO* more, BYTE opCode)
 * PreCondition:    None
 * Input:           remote  - Remote node info
 *                  opCode  - ARP op code to send
 * Output:          TRUE - The ARP packet was generated properly
 *                  FALSE - Unable to allocate a TX buffer
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
BOOL ARPPut(NODE_INFO *remote, BYTE opCode)
{
    ARP_PACKET packet;

    BUFFER MyTxBuffer = MACGetTxBuffer(TRUE);
    
    // Do not respond if there is no room to generate the ARP reply
    if(MyTxBuffer == INVALID_BUFFER)
        return FALSE;

    MACSetTxBuffer(MyTxBuffer, 0);
    packet.HardwareType = HW_ETHERNET;
    packet.Protocol = ARP_IP;
    packet.MACAddrLen = sizeof(MAC_ADDR);
    packet.ProtocolLen = sizeof(IP_ADDR);

    if ( opCode == ARP_REQUEST )
    {
        packet.Operation = ARP_OPERATION_REQ;
        packet.TargetMACAddr.v[0] = 0xff;
        packet.TargetMACAddr.v[1] = 0xff;
        packet.TargetMACAddr.v[2] = 0xff;
        packet.TargetMACAddr.v[3] = 0xff;
        packet.TargetMACAddr.v[4] = 0xff;
        packet.TargetMACAddr.v[5] = 0xff;
    }
    else
    {
        packet.Operation = ARP_OPERATION_RESP;
        packet.TargetMACAddr = remote->MACAddr;
    }

    packet.SenderMACAddr = AppConfig.MyMACAddr;
    packet.SenderIPAddr = AppConfig.MyIPAddr;

    // Check to see if target is on same subnet, if not, find Gateway MAC.
    // Once we get Gateway MAC, all access to remote host will go through Gateway.
    if((packet.SenderIPAddr.Val ^ remote->IPAddr.Val) & AppConfig.MyMask.Val)
    {
         packet.TargetIPAddr = AppConfig.MyGateway;
    }
    else
    {
        packet.TargetIPAddr = remote->IPAddr;
    }

    SwapARPPacket(&packet);
    MACPutHeader(&packet.TargetMACAddr, MAC_ARP, sizeof(packet));
    MACPutArray((BYTE*)&packet, sizeof(packet));
    MACFlush();
    
    return TRUE;
}

/******************************************************************************
 * Function:        BOOL ARPProcess(void)
 * PreCondition:    ARP packet is ready in MAC buffer.
 * Input:           None
 * Output:          ARP FSM is executed.
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
BOOL ARPProcess(void)
{
    NODE_INFO remoteNode;
    BYTE opCode;

    switch(smARP)
    {
    case SM_ARP_IDLE:
        if ( !ARPGet(&remoteNode, &opCode) )
            break;

        if ( opCode == ARP_REPLY )
        {
#if defined(STACK_CLIENT_MODE)
            Cache.MACAddr = remoteNode.MACAddr;
            Cache.IPAddr.Val = remoteNode.IPAddr.Val;
#endif
            break;
        }
        else
            smARP = SM_ARP_REPLY;

    default:
        if(ARPPut(&remoteNode, ARP_REPLY))
        {
            smARP = SM_ARP_IDLE;
        }
        else
            return FALSE;
        break;
    }
    return TRUE;
}

#if defined(STACK_CLIENT_MODE)
/******************************************************************************
 * Function:        void ARPResolve(IP_ADDR* IPAddr)
 * PreCondition:    MACIsTxReady(TRUE) returns TRUE
 * Input:           IPAddr  - IP Address to be resolved.
 * Output:          None
 * Side Effects:    None
 * Overview:        An ARP request is sent.
 * Note:            This function is available only when
 *                  STACK_CLIENT_MODE is defined.
 ******************************************************************************/
void ARPResolve(IP_ADDR *IPAddr)
{
    NODE_INFO remoteNode;

    remoteNode.IPAddr = *IPAddr;
    ARPPut(&remoteNode, ARP_REQUEST);
}

/******************************************************************************
 * Function:        BOOL ARPIsResolved(IP_ADDR* IPAddr,MAC_ADDR *MACAddr)
 * PreCondition:    None
 * Input:           IPAddr      - IPAddress to be resolved.
 *                  MACAddr     - Buffer to hold corresponding
 *                                MAC Address.
 * Output:          TRUE if given IP Address has been resolved.
 *                  FALSE otherwise.
 * Side Effects:    None
 * Overview:        None
 * Note:            This function is available only when
 *                  STACK_CLIENT_MODE is defined.
 ******************************************************************************/
BOOL ARPIsResolved(IP_ADDR *IPAddr, MAC_ADDR *MACAddr)
{
    if(Cache.IPAddr.Val == IPAddr->Val || Cache.IPAddr.Val == AppConfig.MyGateway.Val)
    {
        *MACAddr = Cache.MACAddr;
        return TRUE;
    }
    return FALSE;
}
#endif // STACK_CLIENT_MODE

/******************************************************************************
 * Function:        void ARPInit(void)
 * PreCondition:    None
 * Input:           None
 * Output:          ARP Cache is initialized.
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
void ARPInit(void)
{
    smARP = SM_ARP_IDLE;

#if defined(STACK_CLIENT_MODE)
    Cache.MACAddr.v[0] = 0xff;
    Cache.MACAddr.v[1] = 0xff;
    Cache.MACAddr.v[2] = 0xff;
    Cache.MACAddr.v[3] = 0xff;
    Cache.MACAddr.v[4] = 0xff;
    Cache.MACAddr.v[5] = 0xff;
    Cache.IPAddr.Val = 0x0;
#endif
}

