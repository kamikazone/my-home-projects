/******************************************************************************
 * SNTP Client Module for Microchip TCP/IP Stack                              *
 *============================================================================*
 *                                                                            *
 * The current module implements a basic Simple Network Time Protocol client  *
 * based on NTP version 4.                                                    *
 *                                                                            *
 * For the current version the IP address of the remote NTP server is         *
 * statically defined in the config.h (SNTP_SERVER_IP), as well the update    *
 * interval in seconds (SNTP_UPDATE_SECS).                                    *
 *                                                                            *
 * Future versions of this module will include a variable list of time        *
 * and parameters configurable via a user interface (serial menu or web page).*
 *                                                                            *
 *                                                                            *
 * SOFTWARE LICENSE AGREEMENT                                                 *
 *                                                                            *
 * This software is provided to you free of charge with the sole condition    *
 * of preserving this Copyright Notice. This software is provided "AS IS".    *
 * LJCV Electronics disclaims all warranties, express, implied, statutory or  *
 * otherwise, not limited to merchantability, fitness for a particular        *
 * purpose, and infringement. LJCV Electronics shall in no event be liable    *
 * for special, incidental, or consequential damages. By using this software  *
 * or incorporating parts of it in your particular design or application you  *
 * are accepting the terms of this agreement.                                 *
 *                                                                            *
 * LJCV ELECTRONICS ASSUMES NO OBLIGATION TO PROVIDE ANY WARRANTY OR SUPPORT. *
 *                                                                            *
 * Copyright (c) 2007, LJCV Electronics. All Rights Reserved                  *
 * San Antonio, Texas, USA. info@ljcv.net, www.ljcv.net                       *
 *                                                                            *
 *- Version Log --------------------------------------------------------------*
 *   Date       Author        Comments                                        *
 *----------------------------------------------------------------------------*
 * 06/26/07 Jorge Amodio      Beta 0.9 test version                           *
 ******************************************************************************/
#include "include/config.h"

#if defined(STACK_USE_SNTP)
#include "net/include/stacktsk.h"
#include "net/include/udp.h"
#include "net/include/tick.h"
#include "net/include/arp.h"
#include "net/include/sntp.h"
#include "time/include/time.h"
#include "net/include/helpers.h"


/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
static enum
{
    SNTP_IDLE = 0,
    SNTP_START,
    SNTP_RESOLVE_ARP,
    SNTP_OPEN_SOCKET,
    SNTP_REQUEST,
    SNTP_TIMEOUT,
    SNTP_REPLY,
    SNTP_DONE
} smSNTP = SNTP_IDLE;


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
static BYTE Valid_Clock = 0;
static time_t SNTP_LastUpdate = 0;


/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/

//*****************************************************************************
// IsValidClock() returns the Valid_Clock flag value 
BYTE IsClockValid(void)
{
    return Valid_Clock;
}

//*****************************************************************************
// SNTPRequest() switches the SNTP client state machine to the SNTP_START
// state if it's in idle state
//
void SNTPRequest(void)
{
    if ( smSNTP == SNTP_IDLE ) smSNTP = SNTP_START;
}

//*****************************************************************************
// SNTPTask() executes the SNTP client state machine, it must be periodically
// call from the main application loop to switch through the different states
// and check for automatic updates
//
void SNTPTask(void)
{
    static UDP_SOCKET s;
    static NODE_INFO SNTPServer = {MAC_ADDR_ZERO , SNTP_SERVER_IP};
    static TICK StartTime;
    DWORD_VAL TX_Timestamp;
    BYTE i;

    switch(smSNTP)
    {
        case SNTP_IDLE:
            // If there is no specific request just check if we have to
            // start an automatic update
            if ( Valid_Clock && (GetTimeTick() - SNTP_LastUpdate) < SNTP_UPDATE_SECS )
                break;
            smSNTP++;

        case SNTP_START:
            // Obtain SNTP server MAC address
            ARPResolve(&SNTPServer.IPAddr);
            StartTime = TickGet();
            smSNTP++;
            break;

        case SNTP_RESOLVE_ARP:
            // Wait for ARP resolution to complete or retry
            if(!ARPIsResolved(&SNTPServer.IPAddr, &SNTPServer.MACAddr))
            {
                if(TickGet() - StartTime > SNTP_ARP_TIMEOUT )
                {
                    smSNTP--;
                }
                break;
            }
            smSNTP++;
            
        case SNTP_OPEN_SOCKET:
            // Open a UDP socket
            s = UDPOpen(1200, &SNTPServer, SNTP_PORT);
            if (s == INVALID_UDP_SOCKET) break;
            smSNTP++;

        case SNTP_REQUEST:
             // Send SNTP request, NTP Version 4, Mode Client
             if (!UDPIsPutReady(s)) break;
             UDPPut(0x23);
             for ( i = 1; i < 48 ; i++ ) UDPPut(0x00);
             UDPFlush();
             StartTime = TickGet();
             smSNTP++;
             break;

        case SNTP_TIMEOUT:
             // Check if we have any data in the socket
             if(!UDPIsGetReady(s))
             {
                if(TickGet() - StartTime > SNTP_REQ_TIMEOUT)
                {
                    smSNTP--;
                }
                break;
             }

        case SNTP_REPLY:
             // We are only interested in the Transmit timestamp seconds
             // which is a 32 bit value (big indian) starting at offset 40
             for ( i = 0 ; i < 40 ; i ++ ) UDPGet(&TX_Timestamp.v[0]);
             for ( i = 0 ; i < 4 ; i++ ) UDPGet(&TX_Timestamp.v[i]);
             UDPDiscard();
             UDPClose(s);
             smSNTP++;

        case SNTP_DONE:
             TX_Timestamp.Val = swapl(TX_Timestamp.Val);

             // Adjust for SNTP counter rollover and local tick counter
             // start time
             if  ( TX_Timestamp.v[3] & 0x80 )
                 TX_Timestamp.Val -= 3155673600ul;
             else
                 TX_Timestamp.Val += 1139207298ul;
            
             // Update local tick counter
             SetTimeTick(TX_Timestamp.Val);
             Valid_Clock = 1;
             SNTP_LastUpdate = TX_Timestamp.Val;
             smSNTP = SNTP_IDLE;
    }
}

#endif  // STACK_USE_SNTP
