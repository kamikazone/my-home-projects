/******************************************************************************
 * Announce Module for Microchip TCP/IP Stack                                 *
 *============================================================================*
 *                                                                            *
 * The Announce Module implements two functions that help to detect a device  *
 * in the network running the Microchip TCP/IP stack.                         *
 *                                                                            *
 * The function AnnounceIP() is called after startup and any time that the    *
 * IP address change, this function sends a UDP broadcast packet to the       *
 * announce port (30303 by default) with information about the local device   *
 * such as it's defined NetBIOS name and MAC address.                         *
 * This information can be captured on a PC by running the MCHPDetect.exe     *
 * tool. This program is located in the tools directory.                      *
 *                                                                            *
 * The funcion DiscoveryTask() is called on every pass of the application     *
 * main loop. It implements a simple UDP server that listens on the announce  *
 * port for broadcasts that include a discovery request message. If a request *
 * message  is received the funcion will send a unicast response to the IP    *
 * address of the latest request with similar information as Announce().      *
 * A discovery request message and it's response can be initiatied using the  *
 * MCHPDiscover.exe utility located in the tools directory.                   *
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
 * 10/07/04 Howard Schlunder  Original                                        *
 * 02/09/05 Howard Schlunder  Simplified MAC address to text conversion logic *
 * 02/14/05 Howard Schlunder  Fixed subnet broadcast calculation              *
 ******************************************************************************/
#include "include/config.h"

#if defined(STACK_USE_ANNOUNCE)
#include "net/include/stacktsk.h"
#include "net/include/udp.h"
#include "net/include/helpers.h"

/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define ANNOUNCE_PORT  30303


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
extern NODE_INFO remoteNode;


/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/

/******************************************************************************
 * Function:        void AnnounceIP(void)
 * PreCondition:    Stack is initialized()
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        AnnounceIP opens a UDP socket and transmits a 
 *                  broadcast packet to port 30303.  If a computer is
 *                  on the same subnet and a utility is looking for 
 *                  packets on the UDP port, it will receive the 
 *                  broadcast.  For this application, it is used to 
 *                  announce the change of this board's IP address.
 *                  The messages can be viewed with the MCHPDetect.exe
 *                  program.
 * Note:            A UDP socket must be available before this 
 *                  function is called.  It is freed at the end of 
 *                  the function.  MAX_UDP_SOCKETS may need to be 
 *                  increased if other modules use UDP sockets.
 ******************************************************************************/
void AnnounceIP(void)
{
    UDP_SOCKET MySocket;
    NODE_INFO Remote;
    BYTE i;

    // Set the socket's destination to be a broadcast over our IP subnet
    // Set the MAC destination to be a broadcast
    memset(&Remote, 0xFF, sizeof(Remote));

    // Open a UDP socket for outbound transmission
    MySocket = UDPOpen(2860, &Remote, ANNOUNCE_PORT);

    // Abort operation if no UDP sockets are available
    // If this ever happens, incrementing MAX_UDP_SOCKETS in config.h may help
    // (at the expense of more global memory resources).
    if( MySocket == INVALID_UDP_SOCKET )
        return;

    // Make certain the socket can be written to
    while( !UDPIsPutReady(MySocket) );

    // Begin sending our MAC address in human readable form.
    // The MAC address theoretically could be obtained from the packet header
    // when the computer receives our UDP packet, however, in practice, the OS
    // will abstract away the useful information and it would be difficult 
    // to obtain. It also would be lost if this broadcast packet were forwarded
    // by a router to a different portion of the network (note that broadcasts
    // are normally not forwarded by routers).
    for(i=0; i < sizeof(AppConfig.NetBIOSName)-1; i++)
    {
        UDPPut(AppConfig.NetBIOSName[i]);
    }

    UDPPut('\r');
    UDPPut('\n');

    // Convert the MAC address bytes to hex (text) and then send it
    i = 0;

    while(1)
    {
        UDPPut(btohexa_high(AppConfig.MyMACAddr.v[i]));
        UDPPut(btohexa_low(AppConfig.MyMACAddr.v[i]));

        if(++i == 6)
            break;
        UDPPut('-');
    }

    UDPPut('\r');
    UDPPut('\n');

    // Send some other human readable information.
    UDPPut('D');
    UDPPut('H');
    UDPPut('C');
    UDPPut('P');
    UDPPut('/');
    UDPPut('P');
    UDPPut('o');
    UDPPut('w');
    UDPPut('e');
    UDPPut('r');
    UDPPut(' ');
    UDPPut('e');
    UDPPut('v');
    UDPPut('e');
    UDPPut('n');
    UDPPut('t');
    UDPPut(' ');
    UDPPut('o');
    UDPPut('c');
    UDPPut('c');
    UDPPut('u');
    UDPPut('r');
    UDPPut('r');
    UDPPut('e');
    UDPPut('d');

    // Send the packet
    UDPFlush();

    // Close the socket so it can be used by other modules
    UDPClose(MySocket);
}

void DiscoveryTask(void)
{
    static enum {
        DISCOVERY_HOME = 0,
        DISCOVERY_LISTEN,
        DISCOVERY_REQUEST_RECEIVED,
        DISCOVERY_DISABLED
    } DiscoverySM = DISCOVERY_HOME;

    static UDP_SOCKET MySocket;
    BYTE i;

    switch(DiscoverySM)
    {
        case DISCOVERY_HOME:
            // Open a UDP socket for inbound and outbound transmission
            // Since we expect to only receive broadcast packets and only send
            // unicast packets directly to the node we last received from, the
            // remote NodeInfo parameter can be anything
            MySocket = UDPOpen(ANNOUNCE_PORT, NULL, ANNOUNCE_PORT);

            if(MySocket == INVALID_UDP_SOCKET)
                return;
            else
                DiscoverySM++;
            break;

        case DISCOVERY_LISTEN:
            // Do nothing if no data is waiting
            if(!UDPIsGetReady(MySocket))
                return;

            // See if this is a discovery query or reply
            UDPGet(&i);
            UDPDiscard();

            if(i != 'D')
                return;

            // We received a discovery request, reply
            DiscoverySM++;
            break;

        case DISCOVERY_REQUEST_RECEIVED:
            if(!UDPIsPutReady(MySocket))
                return;

            // Begin sending our MAC address in human readable form.
            // The MAC address theoretically could be obtained from the packet
            // header when the computer receives our UDP packet, however, in
            // practice, the OS will abstract away the useful information and
            // it would be difficult to obtain. It also would be lost if this
            // broadcast packet were forwarded by a router to a different
            // portion of the network (note that broadcasts are normally not
            // forwarded by routers).
            for(i=0; i < sizeof(AppConfig.NetBIOSName)-1; i++)
            {
                UDPPut(AppConfig.NetBIOSName[i]);
            }

            UDPPut('\r');
            UDPPut('\n');

            // Convert the MAC address bytes to hex (text) and then send it
            i = 0;

            while(1)
            {
                UDPPut(btohexa_high(AppConfig.MyMACAddr.v[i]));
                UDPPut(btohexa_low(AppConfig.MyMACAddr.v[i]));
                if(++i == 6)
                    break;
                UDPPut('-');
            }

            UDPPut('\r');
            UDPPut('\n');

            // Change the destination to the unicast address of the last received packet
            memcpy((void*)&UDPSocketInfo[MySocket].remoteNode, (const void*)&remoteNode, sizeof(remoteNode));

            // Send the packet
            UDPFlush();

            // Listen for other discovery requests
            DiscoverySM = DISCOVERY_LISTEN;
            break;

        case DISCOVERY_DISABLED:
            break;
    }
}

#endif  // STACK_USE_ANNOUNCE

