/******************************************************************************
 * UDP Test Module for Microchip TCP/IP Stack                                 *
 *============================================================================*
 *                                                                            *
 * This module implements a throughput test using UDP. Every time that the    *
 * UDPTest() function is called it will send over the network a UDP datagram  *
 * to a broadcast address or to a specific target address defined in the      *
 * udptest.h header file ( UDP_TST_TARGET_MAC and UDP_TST_TARGET_IP ),        *
 * datagrams are sent to the UDP port defined by UDP_TST_TARGET_PORT.         *
 *                                                                            *
 * Datagram size is determined by the MAX_UDP_DATA value defined below, and   *
 * all data bytes will be filled with the value 0x41 (A).                     *
 * If you will be using a specific host address as a target is recommended    *
 * that on the target host you run a process able to listen on the udp target *
 * port, if there is no process listening to the port depending on the TCP/IP *
 * implementation you may start getting back ICMP messages reporting that the *
 * service is not available. In Unix you can use nc or netcat for this        *
 * purpose.                                                                   *
 *                                                                            *
 * WARNING: While the number of packets per second and traffic volume this    *
 * function generates is not very high, if the target address is configured   *
 * as a broadcast address, depending on the configuration of your network or  *
 * other network devices this function can produce a broadcast storm or other *
 * undesirable network problems. Use for testing purposes only.              *
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
 * 05/10/07 Jorge Amodio      Original                                        *
 ******************************************************************************/
#include "include/config.h"

#if defined(STACK_USE_UDPTEST)
#include "net/include/stacktsk.h"
#include "net/include/udp.h"
#include "net/include/udptest.h"


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define SIZEOF_MAC_HEADER       (14)
#define MAX_UDP_DATA  (MAC_TX_BUFFER_SIZE - SIZEOF_MAC_HEADER - sizeof(IP_HEADER) - sizeof(UDP_HEADER))


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
NODE_INFO TestTarget =
{
    UDP_TST_TARGET_MAC,
    UDP_TST_TARGET_IP
};


/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/
void UDPTest(void)
{
    UDP_SOCKET s;
    WORD i;

    s = UDPOpen(0, &TestTarget, UDP_TST_TARGET_PORT);
        
    if( s == INVALID_UDP_SOCKET )
        return;

    if(!UDPIsPutReady(s))
    {
        UDPClose(s);
        return;
     }

    for ( i = 0 ; i < MAX_UDP_DATA-1 ; i++) {
        UDPPut('A');
    }

    UDPFlush();
    UDPClose(s);
}

#endif  // STACK_USE_UDPTEST
