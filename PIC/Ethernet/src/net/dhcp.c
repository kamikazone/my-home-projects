/******************************************************************************
 *  DHCP Client Module for Microchip TCP/IP Stack                             *
 *============================================================================*
 *                                                                            *
 * The current source files includes the functions to implement a DHCP        *
 * (Dynamic Host Configuration Protocol) client for dynamic configuration     *
 * of the local device.                                                       *
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
 * 03/21/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 07/12/02 Nilesh Rajbharti  Explicitly initialized tempIPAddress (Rev 2.11) *
 * 05/16/03 Nilesh Rajbharti  Increased DHCP_TIMEOUT to 2 seconds.            *
 *                            Fixed SM_DHCP_BROADCAST logic where UDPPut was  *
 *                            called before setting active socket.            *
 * 05/29/03 Robert Sloan      Improved DHCP State machine to handle NAK and   *
 *                            renew existing IP address.                      *
 * 08/15/03 Nilesh Rajbharti  Modified _DHCPRecieve() to check for chaddr     *
 *                            field before accpting the packet.               *
 *                            Fixed DHCPTask() where it would not reply       *
 *                            to first OFFER.                                 *
 * 03/01/04 Nilesh Rajbharti  Used tickDiff in DHCPTask() "bind" state to     *
 *                            adjust for irregular TICK_SECOND. Without this  *
 *                            logic, actual lease time count down may be      *
 *                            incorrect.                                      *
 * 05/11/06 Howard Schlunder  Fixed tickDiff usage, reducing accumulated      *
 *                            timing error.                                   *
 *                            Fixed DHCP state machine requesting IP 0.0.0.0  *
 *                            after lease expiration.                         *
 * 06/01/06 Howard Schlunder  Added DHCPState.bits.bOfferReceived flag to     *
 *                            allow operation on networks with multiple DHCP  *
 *                            servers offering multiple addresses.            *
 * 08/01/06 Howard Schlunder  Added DNS server option to DHCP request,        *
 *                            untested Host Name option to DHCP request.      *
 * 04/25/07 Jorge Amodio      Cleanup                                         *
 ******************************************************************************/
#define _DHCP_C
#include "include/config.h"

#if defined(STACK_USE_DHCP)
#include "net/include/stacktsk.h"
#include "net/include/dhcp.h"
#include "net/include/udp.h"
#include "net/include/tick.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
static union
{
    struct
    {
        char IPAddress:1;
        char Gateway:1;
        char Mask:1;
        char DNS:1;
        char HostName:1;
    } bits;
    BYTE Val;
} ValidValues;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define DHCP_TIMEOUT  (TICK)(2L * TICK_SECOND)

#define DHCP_CLIENT_PORT             (68u)
#define DHCP_SERVER_PORT             (67u)

#define BOOT_REQUEST                 (1u)
#define BOOT_REPLY                   (2u)
#define HW_TYPE                      (1u)
#define LEN_OF_HW_TYPE               (6u)

#define DHCP_MESSAGE_TYPE            (53u)
#define DHCP_MESSAGE_TYPE_LEN        (1u)

#define DHCP_UNKNOWN_MESSAGE         (0u)
#define DHCP_DISCOVER_MESSAGE        (1u)
#define DHCP_OFFER_MESSAGE           (2u)
#define DHCP_REQUEST_MESSAGE         (3u)
#define DHCP_DECLINE_MESSAGE         (4u)
#define DHCP_ACK_MESSAGE             (5u)
#define DHCP_NAK_MESSAGE             (6u)
#define DHCP_RELEASE_MESSAGE         (7u)

#define DHCP_SERVER_IDENTIFIER       (54u)
#define DHCP_SERVER_IDENTIFIER_LEN   (4u)

#define DHCP_PARAM_REQUEST_LIST            (55u)
#define DHCP_PARAM_REQUEST_LIST_LEN        (4u)
#define DHCP_PARAM_REQUEST_IP_ADDRESS      (50u)
#define DHCP_PARAM_REQUEST_IP_ADDRESS_LEN  (4u)
#define DHCP_SUBNET_MASK                   (1u)
#define DHCP_ROUTER                        (3u)
#define DHCP_DNS                           (6u)
#define DHCP_HOST_NAME                     (12u)
#define DHCP_IP_LEASE_TIME                 (51u)
#define DHCP_END_OPTION                    (255u)

#define HALF_HOUR  (WORD)((WORD)60 * (WORD)30)

// Uncomment following line if DHCP transactions are to be displayed on
// RS-232 - for debug purpose only.
//#define DHCP_DEBUG_MODE


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
SM_DHCP  smDHCPState = SM_DHCP_INIT_FIRST_TIME;
static UDP_SOCKET DHCPSocket = INVALID_UDP_SOCKET;
DHCP_STATE DHCPState = { 0x00 };
BYTE DHCPBindCount = 0;
static DWORD_VAL DHCPServerID, DHCPLeaseTime;
static IP_ADDR tempIPAddress, tempGateway, tempMask;

#if defined(STACK_USE_DNS)
static IP_ADDR tempDNS;
#endif

//static BYTE tempHostName[16];


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#if defined(DHCP_DEBUG_MODE)
void USARTPut(BYTE c)
{
    while( !TXSTAbits.TRMT);
    TXREG = c;
}
#else
#define USARTPut(a)
#endif


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void DHCPReset(void)
{
    // Do not reset DHCP if it was previously disabled.
    if ( smDHCPState == SM_DHCP_DISABLED )
        return;

    if ( DHCPSocket != INVALID_UDP_SOCKET )
        UDPClose(DHCPSocket);

    DHCPSocket = INVALID_UDP_SOCKET;
    smDHCPState = SM_DHCP_INIT_FIRST_TIME;
    DHCPBindCount = 0;
    DHCPState.bits.bIsBound = FALSE;
}

static void _DHCPSend(BYTE messageType)
{
    BYTE i;

    UDPPut(BOOT_REQUEST);                       // op
    UDPPut(HW_TYPE);                            // htype
    UDPPut(LEN_OF_HW_TYPE);                     // hlen
    UDPPut(0);                                  // hops
    UDPPut(0x12);                               // xid[0]
    UDPPut(0x23);                               // xid[1]
    UDPPut(0x34);                               // xid[2]
    UDPPut(0x56);                               // xid[3]
    UDPPut(0);                                  // secs[0]
    UDPPut(0);                                  // secs[1]
    UDPPut(0x80);                               // flags[0] with BF set
    UDPPut(0);                                  // flags[1]

    // If this is DHCP REQUEST message, use previously allocated IP address.
#if 0
    if ( messageType == DHCP_REQUEST_MESSAGE )
    {
        UDPPut(tempIPAddress.v[0]);
        UDPPut(tempIPAddress.v[1]);
        UDPPut(tempIPAddress.v[2]);
        UDPPut(tempIPAddress.v[3]);
    }
    else
#endif
    {
        UDPPut(0x00);
        UDPPut(0x00);
        UDPPut(0x00);
        UDPPut(0x00);
    }

    // Set yiaddr, siaddr, giaddr as zeros,
    for ( i = 0; i < 12u; i++ )
        UDPPut(0x00);

    // Load chaddr - Client hardware address.
    UDPPut(AppConfig.MyMACAddr.v[0]);
    UDPPut(AppConfig.MyMACAddr.v[1]);
    UDPPut(AppConfig.MyMACAddr.v[2]);
    UDPPut(AppConfig.MyMACAddr.v[3]);
    UDPPut(AppConfig.MyMACAddr.v[4]);
    UDPPut(AppConfig.MyMACAddr.v[5]);

    // Set chaddr[6..15], sname and file as zeros.
    for ( i = 0; i < 202u; i++ )
        UDPPut(0);

    // Load magic cookie as per RFC 1533.
    UDPPut(99);
    UDPPut(130);
    UDPPut(83);
    UDPPut(99);

    // Load message type.
    UDPPut(DHCP_MESSAGE_TYPE);
    UDPPut(DHCP_MESSAGE_TYPE_LEN);
    UDPPut(messageType);

    if(messageType == DHCP_DISCOVER_MESSAGE)
    {
        // Reset offered flag so we know to act upon the next valid offer
        DHCPState.bits.bOfferReceived = FALSE;
    }

    if ( messageType != DHCP_DISCOVER_MESSAGE && tempIPAddress.Val != 0x0000u )
    {
         // DHCP REQUEST message may include server identifier,
         // to identify the server we are talking to.
         // DHCP ACK may include it too.  To simplify logic,
         // we will include server identifier in DHCP ACK message too.
         // _DHCPReceive() would populate "serverID" when it
         // receives DHCP OFFER message. We will simply use that
         // when we are replying to server.
         // If this is a renwal request, do not include server id.
         UDPPut(DHCP_SERVER_IDENTIFIER);
         UDPPut(DHCP_SERVER_IDENTIFIER_LEN);
         UDPPut(DHCPServerID.v[3]);
         UDPPut(DHCPServerID.v[2]);
         UDPPut(DHCPServerID.v[1]);
         UDPPut(DHCPServerID.v[0]);
     }

    // Load our interested parameters
    // This is hardcoded list.  If any new parameters are desired,
    // new lines must be added here.
    UDPPut(DHCP_PARAM_REQUEST_LIST);
    UDPPut(DHCP_PARAM_REQUEST_LIST_LEN);
    UDPPut(DHCP_SUBNET_MASK);
    UDPPut(DHCP_ROUTER);
    UDPPut(DHCP_DNS);
    UDPPut(DHCP_HOST_NAME);

     // Add requested IP address to DHCP Request Message
    if ( messageType == DHCP_REQUEST_MESSAGE )
    {
        UDPPut(DHCP_PARAM_REQUEST_IP_ADDRESS);
        UDPPut(DHCP_PARAM_REQUEST_IP_ADDRESS_LEN);
        UDPPut(tempIPAddress.v[0]);
        UDPPut(tempIPAddress.v[1]);
        UDPPut(tempIPAddress.v[2]);
        UDPPut(tempIPAddress.v[3]);
    }

    // Add any new paramter request here.

    // End of Options.
    UDPPut(DHCP_END_OPTION);
    UDPFlush();
}

static BYTE _DHCPReceive(void)
{
    BYTE v, i, j, type;
    DWORD_VAL tempServerID;
    BOOL lbDone;

    // Assume unknown message until proven otherwise.
    type = DHCP_UNKNOWN_MESSAGE;

    UDPGet(&v);                             // op

    // Make sure this is BOOT_REPLY.
    if ( v == BOOT_REPLY )
    {
        // Discard htype, hlen, hops, xid, secs, flags, ciaddr.
        for ( i = 0; i < 15u; i++ )
            UDPGet(&v);

        // Check to see if this is the first offer
        if(DHCPState.bits.bOfferReceived)
        {
            // Discard offered IP address, we already have an offer
            for ( i = 0; i < 4u; i++ )
                UDPGet(&v);
        }
        else
        {
            // Save offered IP address until we know for sure that we have it.
            UDPGet(&tempIPAddress.v[0]);
            UDPGet(&tempIPAddress.v[1]);
            UDPGet(&tempIPAddress.v[2]);
            UDPGet(&tempIPAddress.v[3]);
            ValidValues.bits.IPAddress = 1;
        }

        // Ignore siaddr, giaddr
        for ( i = 0; i < 8u; i++ )
            UDPGet(&v);

        // Check to see if chaddr (Client Hardware Address) belongs to us.
        for ( i = 0; i < 6u; i++ )
        {
            UDPGet(&v);
            if ( v != AppConfig.MyMACAddr.v[i])
                goto UDPInvalid;
        }


        // Ignore part of chaddr, sname, file, magic cookie.
        for ( i = 0; i < 206u; i++ )
            UDPGet(&v);

        lbDone = FALSE;
        do
        {
            // Get the Option number
            // Break out eventually in case if this is a malformed 
            // DHCP message, ie: missing DHCP_END_OPTION marker
            if(!UDPGet(&v))
            {
                lbDone = TRUE;
                break;
            }

            switch(v)
            {
            case DHCP_MESSAGE_TYPE:
                UDPGet(&v);                         // Skip len
                // Len must be 1.
                if ( v == 1u )
                {
                    UDPGet(&type);                  // Get type

                    // Throw away the packet if we know we don't need it (ie: another offer when we already have one)
                    if(DHCPState.bits.bOfferReceived && (type == DHCP_OFFER_MESSAGE))
                    {
                        goto UDPInvalid;
                    }
                }
                else
                    goto UDPInvalid;
                break;

            case DHCP_SUBNET_MASK:
                UDPGet(&v);                     // Skip len
                // Len must be 4.
                if ( v == 4u )
                {
                    // Check to see if this is the first offer
                    if(DHCPState.bits.bOfferReceived)
                    {
                        // Discard offered IP mask, we already have an offer
                        for ( i = 0; i < 4u; i++ )
                            UDPGet(&v);
                    }
                    else
                    {
                        UDPGet(&tempMask.v[0]);
                        UDPGet(&tempMask.v[1]);
                        UDPGet(&tempMask.v[2]);
                        UDPGet(&tempMask.v[3]);
                        ValidValues.bits.Mask = 1;
                    }
                }
                else
                    goto UDPInvalid;
                break;

            case DHCP_ROUTER:
                UDPGet(&j);
                // Len must be >= 4.
                if ( j >= 4u )
                {
                    // Check to see if this is the first offer
                    if(DHCPState.bits.bOfferReceived)
                    {
                        // Discard offered Gateway address, we already have an offer
                        for ( i = 0; i < 4u; i++ )
                            UDPGet(&v);
                    }
                    else
                    {
                        UDPGet(&tempGateway.v[0]);
                        UDPGet(&tempGateway.v[1]);
                        UDPGet(&tempGateway.v[2]);
                        UDPGet(&tempGateway.v[3]);
                        ValidValues.bits.Gateway = 1;
                    }
                }
                else
                    goto UDPInvalid;

                // Discard any other router addresses.
                j -= 4;
                while(j--)
                    UDPGet(&v);
                break;

#if defined(STACK_USE_DNS)
            case DHCP_DNS:
                UDPGet(&j);
                // Len must be >= 4.
                if ( j >= 4u )
                {
                    // Check to see if this is the first offer
                    if(DHCPState.bits.bOfferReceived)
                    {
                        // Discard offered DNS server address, we already have an offer
                        for ( i = 0; i < 4u; i++ )
                            UDPGet(&v);
                    }
                    else
                    {
                        UDPGet(&tempDNS.v[0]);
                        UDPGet(&tempDNS.v[1]);
                        UDPGet(&tempDNS.v[2]);
                        UDPGet(&tempDNS.v[3]);
                        ValidValues.bits.DNS = 1;
                    }
                }
                else
                    goto UDPInvalid;

                // Discard any other DNS server addresses
                j -= 4;
                while(j--)
                    UDPGet(&v);
                break;
#endif

//            case DHCP_HOST_NAME:
//                UDPGet(&j);
//                // Len must be >= 4.
//                if(j < 1u)
//                    goto UDPInvalid;
//
//                // Check to see if this is the first offer
//                if(DHCPState.bits.bOfferReceived)
//                {
//                    // Discard offered host name, we already have an offer
//                    while(j--)
//                        UDPGet(&v);
//                }
//                else
//                {
//                    for(i = 0; j, i < sizeof(tempHostName); i++, j--)
//                    {
//                        UDPGet(&tempHostName[i]);
//                    }
//                    while(j--)
//                    {
//                        UDPGet(&v);
//                    }
//                    ValidValues.bits.HostName = 1;
//                }
//
//                break;

            case DHCP_SERVER_IDENTIFIER:
                UDPGet(&v);                         // Get len
                // Len must be 4.
                if ( v == 4u )
                {
                    UDPGet(&tempServerID.v[3]);   // Get the id
                    UDPGet(&tempServerID.v[2]);
                    UDPGet(&tempServerID.v[1]);
                    UDPGet(&tempServerID.v[0]);
                }
                else
                    goto UDPInvalid;
                break;

            case DHCP_END_OPTION:
                lbDone = TRUE;
                break;

            case DHCP_IP_LEASE_TIME:
                UDPGet(&v);                         // Get len
                // Len must be 4.
                if ( v == 4u )
                {
                    // Check to see if this is the first offer
                    if(DHCPState.bits.bOfferReceived)
                    {
                        // Discard offered lease time, we already have an offer
                        for ( i = 0; i < 4u; i++ )
                            UDPGet(&v);
                    }
                    else
                    {
                        UDPGet(&DHCPLeaseTime.v[3]);
                        UDPGet(&DHCPLeaseTime.v[2]);
                        UDPGet(&DHCPLeaseTime.v[1]);
                        UDPGet(&DHCPLeaseTime.v[0]);

                        // Due to possible timing delays, consider actual lease
                        // time less by half hour.
                        if ( DHCPLeaseTime.Val > HALF_HOUR )
                            DHCPLeaseTime.Val = DHCPLeaseTime.Val - HALF_HOUR;
                    }
                }
                else
                    goto UDPInvalid;
                break;

            default:
                // Ignore all unsupport tags.
                UDPGet(&j);                     // Get option len
                while( j-- )                    // Ignore option values
                    UDPGet(&v);
            }
        } while( !lbDone );
    }

    // If this is an OFFER message, remember current server id.
    if ( type == DHCP_OFFER_MESSAGE )
    {
        DHCPServerID.Val = tempServerID.Val;
        DHCPState.bits.bOfferReceived = TRUE;
    }
    else
    {
        // For other types of messages, make sure that received
        // server id matches with our previous one.
        if ( DHCPServerID.Val != tempServerID.Val )
            type = DHCP_UNKNOWN_MESSAGE;
    }

    UDPDiscard();                             // We are done with this packet
    return type;

UDPInvalid:
    UDPDiscard();
    return DHCP_UNKNOWN_MESSAGE;

}

/******************************************************************************
 * Function:        void DHCPTask(void)
 * PreCondition:    DHCPInit() is already called AND
 *                  IPGetHeader() is called with
 *                  IPFrameType == IP_PROT_UDP
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        Fetches pending UDP packet from MAC receive buffer
 *                  and dispatches it appropriate UDP socket.
 *                  If not UDP socket is matched, UDP packet is
 *                  silently discarded.
 * Note:            Caller must make sure that MAC receive buffer
 *                  access pointer is set to begining of UDP packet.
 *                  Required steps before calling this function is:
 *                  If ( MACIsRxReady() )
 *                  {
 *                      MACGetHeader()
 *                      If MACFrameType == IP
 *                          IPGetHeader()
 *                          if ( IPFrameType == IP_PROT_UDP )
 *                              Call DHCPTask()
 *                  ...
 ******************************************************************************/
void DHCPTask(void)
{
    NODE_INFO DHCPServerNode;
    static TICK lastTryTick;
    BYTE DHCPRecvReturnValue;
    TICK tickDiff;

    switch(smDHCPState)
    {
    case SM_DHCP_INIT_FIRST_TIME:
        tempIPAddress.Val = 0x0;
//        smDHCPState = SM_DHCP_INIT;            // State automatically changes
        /* No break */

    case SM_DHCP_INIT:
        DHCPServerNode.MACAddr.v[0] = 0xff;
        DHCPServerNode.MACAddr.v[1] = 0xff;
        DHCPServerNode.MACAddr.v[2] = 0xff;
        DHCPServerNode.MACAddr.v[3] = 0xff;
        DHCPServerNode.MACAddr.v[4] = 0xff;
        DHCPServerNode.MACAddr.v[5] = 0xff;
        DHCPServerNode.IPAddr.Val = 0xffffffff;
        DHCPSocket = UDPOpen(DHCP_CLIENT_PORT,&DHCPServerNode,DHCP_SERVER_PORT);
        lastTryTick = TickGet();
        smDHCPState = SM_DHCP_RESET_WAIT;
        /* No break */

    case SM_DHCP_RESET_WAIT:
        if ( TickGetDiff(TickGet(), lastTryTick) >= (TICK_SECOND/(TICK)5) )
            smDHCPState = SM_DHCP_BROADCAST;
        break;

    case SM_DHCP_BROADCAST:
        // Assume default IP Lease time of 60 seconds.
        // This should be minimum possible to make sure that if
        // server did not specify lease time, we try again after this minimum time.
        DHCPLeaseTime.Val = 60;

        // If we have already obtained some IP address, renew it.
        if(DHCPState.bits.bIsBound)
        {
            smDHCPState = SM_DHCP_REQUEST;
        }
        else if ( UDPIsPutReady(DHCPSocket) )
        {
            // To minimize code requirement, user must make sure that
            // above call will be successful by making at least one
            // UDP socket available.
            // Usually this will be the case, given that DHCP will be
            // the first one to use UDP socket.
            // Also, we will not check for transmitter readiness,
            // we assume it to be ready.
            _DHCPSend(DHCP_DISCOVER_MESSAGE);
            ValidValues.Val = 0x00;

            // DEBUG
            USARTPut('\n');
            USARTPut('\r');
            USARTPut('D');

            lastTryTick = TickGet();
            smDHCPState = SM_DHCP_DISCOVER;
        }

        break;

    case SM_DHCP_DISCOVER:
        if ( TickGetDiff(TickGet(), lastTryTick) >= DHCP_TIMEOUT )
        {
            smDHCPState = SM_DHCP_BROADCAST;
            //return;
        }

        if ( UDPIsGetReady(DHCPSocket) )
        {
            // DEBUG
            USARTPut('R');

            if ( _DHCPReceive() == DHCP_OFFER_MESSAGE )
            {
                // DEBUG
                USARTPut('O');

                smDHCPState = SM_DHCP_REQUEST;
            }
            else
                break;
        }
        else
            break;

    case SM_DHCP_REQUEST:
        if ( UDPIsPutReady(DHCPSocket) )
        {
            _DHCPSend(DHCP_REQUEST_MESSAGE);

            lastTryTick = TickGet();
            smDHCPState = SM_DHCP_BIND;
        }
        break;

    case SM_DHCP_BIND:
        if ( UDPIsGetReady(DHCPSocket) )
        {
            DHCPRecvReturnValue = _DHCPReceive();
            if ( DHCPRecvReturnValue == DHCP_NAK_MESSAGE )
            {
                // (RSS) NAK recieved.  DHCP server didn't like our DHCP 
                //Request (format wrong/IP address allocated to someone else/outside IP pool)
                USARTPut('n');
                DHCPReset();                   // Start all over again
                return;
            }
            else if ( DHCPRecvReturnValue == DHCP_ACK_MESSAGE )
            {
                // DEBUG
                USARTPut('B');

                // Once DCHP is successful, release the UDP socket
                // This will ensure that UDP layer discards any further DHCP related packets.
                UDPClose(DHCPSocket);
                DHCPSocket = INVALID_UDP_SOCKET;

                lastTryTick = TickGet();
                smDHCPState = SM_DHCP_BOUND;

                if(ValidValues.bits.IPAddress)
                    AppConfig.MyIPAddr = tempIPAddress;
                if(ValidValues.bits.Mask)
                    AppConfig.MyMask = tempMask;
                if(ValidValues.bits.Gateway)
                    AppConfig.MyGateway = tempGateway;

#if defined(STACK_USE_DNS)
                if(ValidValues.bits.DNS)
                    AppConfig.PrimaryDNSServer = tempDNS;
#endif

//                if(ValidValues.bits.HostName)
//                    memcpy(AppConfig.NetBIOSName, (void*)tempHostName, sizeof(AppConfig.NetBIOSName));

                DHCPState.bits.bIsBound = TRUE;
                DHCPBindCount++;

                return;
            }
        }
        else if ( TickGetDiff(TickGet(), lastTryTick) >= DHCP_TIMEOUT )
        {
            USARTPut('t');
            smDHCPState = SM_DHCP_BROADCAST;
        }
        break;

    case SM_DHCP_BOUND:
        // Keep track of how long we use this IP configuration.
        // When lease period expires, renew the configuration.
        tickDiff = TickGetDiff(TickGet(), lastTryTick);

        if(tickDiff >= TICK_SECOND)
        {
            do 
            {
                DHCPLeaseTime.Val--;
                tickDiff -= TICK_SECOND;
                if(DHCPLeaseTime.Val == 0u)
                    smDHCPState = SM_DHCP_INIT;
            } while(tickDiff >= TICK_SECOND);
            lastTryTick = TickGet() - tickDiff;
        }
    }
}

#endif // STACK_USE_DHCP

