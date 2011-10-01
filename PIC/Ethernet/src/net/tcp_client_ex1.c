/******************************************************************************
 * Generic TCP Client Example for Microchip TCP/IP Stack                      *
 *============================================================================*
 *                                                                            *
 * This module implements an example HTTP client and can be used as a         *
 * generic reference for a TCP Client implementation.                         *
 *                                                                            *
 * The HTTP client establishes a TCP connection to www.google.com submits a   *
 * search URL and shows the results via the serial interface.                 *
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
 * 08/01/06 Howard Schlunder  Original                                        *
 * 04/25/07 Jorge Amodio      Changed file name to tcp_client_ex1.c           *
 ******************************************************************************/
#include "include/config.h"
#if defined(STACK_USE_TCP_EXAMPLE1)

#include "include/generic_typedefs.h"
#include "net/include/dns.h"
#include "net/include/helpers.h"
#include "net/include/tcp.h"
#include "net/include/arp.h"
#include "uart/include/uart.h"

//TODO: Define proper server address here
BYTE ServerName[] = "www.google.com";
WORD ServerPort = 80;

// This is specific to this HTTP Client example
BYTE RemoteURL[] = "/search?as_q=Microchip&as_sitesearch=microchip.com";

/******************************************************************************
 * Function:        void GenericTCPClient(void)
 * PreCondition:    Stack is initialized()
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
void GenericTCPClient(void)
{
    BYTE i, *StringPtr;
    static TICK Timer;
    static TCP_SOCKET MySocket = INVALID_SOCKET;
    static NODE_INFO Server;
    static enum _GenericTCPExampleState
    {
        SM_HOME = 0,
        SM_NAME_RESOLVE,
        SM_ARP_START_RESOLVE,
        SM_ARP_RESOLVE,
        SM_SOCKET_OBTAIN,
        SM_SOCKET_OBTAINED,
        SM_PROCESS_RESPONSE,
        SM_DISCONNECT,
        SM_DONE
    } GenericTCPExampleState = SM_DONE;

    switch(GenericTCPExampleState)
    {
        case SM_HOME:
            // Obtain the IP address associated with the common ServerName
            DNSResolve(ServerName);
            GenericTCPExampleState++;
            break;

        case SM_NAME_RESOLVE:
            // Wait for the DNS server to return the requested IP address
            if(!DNSIsResolved(&Server.IPAddr))
                break;
            GenericTCPExampleState++;

        case SM_ARP_START_RESOLVE:
            // Obtain the MAC address associated with the server's IP address
            // (either direct MAC address on same subnet, or the MAC address
            // of the Gateway machine)
            ARPResolve(&Server.IPAddr);
            Timer = TickGet();
            GenericTCPExampleState++;
            break;

        case SM_ARP_RESOLVE:
            // Wait for the MAC address to finish being obtained
            if(!ARPIsResolved(&Server.IPAddr, &Server.MACAddr))
            {
                // Time out if too much time is spent in this state
                if(TickGet()-Timer > 1*TICK_SECOND)
                {
                    // Retransmit ARP request
                    GenericTCPExampleState--;
                }
                break;
            }
            GenericTCPExampleState++;

        case SM_SOCKET_OBTAIN:
            // Connect a socket to the remote TCP server
            MySocket = TCPConnect(&Server, ServerPort);
            
            // Abort operation if no TCP sockets are available
            // If this ever happens, incrementing MAX_TCP_SOCKETS in
            // config.h may help (at the expense of more global memory
            // resources).
            if(MySocket == INVALID_SOCKET)
                break;

            GenericTCPExampleState++;
            Timer = TickGet();
            break;

        case SM_SOCKET_OBTAINED:
            // Wait for the remote server to accept our connection request
            if(!TCPIsConnected(MySocket))
            {
                // Time out if too much time is spent in this state
                if(TickGet()-Timer > 5*TICK_SECOND)
                {
                    // Close the socket so it can be used by other modules
                    TCPDisconnect(MySocket);
                    MySocket = INVALID_SOCKET;
                    GenericTCPExampleState--;
                }
                break;
            }

            Timer = TickGet();

            // Make certain the socket can be written to
            if(!TCPIsPutReady(MySocket))
                break;
            
            // Place the application protocol data into the transmit buffer.
            // For this example, we are connected to an HTTP server, so we'll
            // send an HTTP GET request.
            TCPPut(MySocket, 'G');
            TCPPut(MySocket, 'E');
            TCPPut(MySocket, 'T');
            TCPPut(MySocket, ' ');
            {
                StringPtr = RemoteURL;
                for(i = 0; i < strlen(RemoteURL); i++)
                {
                    TCPPut(MySocket, *StringPtr++);
                } 
            }
            TCPPut(MySocket, ' ');
            TCPPut(MySocket, 'H');
            TCPPut(MySocket, 'T');
            TCPPut(MySocket, 'T');
            TCPPut(MySocket, 'P');
            TCPPut(MySocket, '/');
            TCPPut(MySocket, '1');
            TCPPut(MySocket, '.');
            TCPPut(MySocket, '1');
            TCPPut(MySocket, '\r');
            TCPPut(MySocket, '\n');
            TCPPut(MySocket, 'H');
            TCPPut(MySocket, 'o');
            TCPPut(MySocket, 's');
            TCPPut(MySocket, 't');
            TCPPut(MySocket, ':');
            TCPPut(MySocket, ' ');
            {
                StringPtr = ServerName;
                
                for(i = 0; i < strlen(ServerName); i++)
                {
                    TCPPut(MySocket, *StringPtr++);
                } 
            }
            TCPPut(MySocket, '\r');
            TCPPut(MySocket, '\n');
            TCPPut(MySocket, '\r');
            TCPPut(MySocket, '\n');

            // Send the packet
            TCPFlush(MySocket);
            GenericTCPExampleState++;

        case SM_PROCESS_RESPONSE:
            // Check to see if the remote node has disconnected from us or sent
            // us any application data
            // If application data is available, write it to the UART
            if(!TCPIsConnected(MySocket))
            {
                GenericTCPExampleState++;
            }

            if(!TCPIsGetReady(MySocket))
                break;

            // Obtain the server reply
            while(TCPGet(MySocket, &i))
            {
                while(BusyUART());
                WriteUART(i);
            }
            break;

        case SM_DISCONNECT:
            // Close the socket so it can be used by other modules
            // For this application, we wish to stay connected, but this state will
            // still get entered if the remote server decides to disconnect
            TCPDisconnect(MySocket);
            MySocket = INVALID_SOCKET;
            GenericTCPExampleState = SM_DONE;
            break;

        case SM_DONE:
            // Do nothing unless the user pushes BUTTON1 and wants to restart the whole
            // connection/download process
            if(BUTTON1_IO == 0)
                GenericTCPExampleState = SM_HOME;
            break;
    }
}

#endif  // STACK_USE_TCP_EXAMPLE1
