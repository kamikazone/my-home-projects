/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack DHCP Client Module           *
 *============================================================================*
 *                                                                            *
 * See dhcp.c for details                                                     *
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
 * 03/21/01 Nilesh Rajbharti  Original (Rev 1.0                               *
 * 04/25/07 Jorge Amodio      Cleanup                                         *
 ******************************************************************************/
#ifndef _DHCP_H
#define _DHCP_H

#include "net/include/stacktsk.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
typedef enum _SM_DHCP
{
    SM_DHCP_INIT_FIRST_TIME,
    SM_DHCP_INIT,
    SM_DHCP_RESET_WAIT,
    SM_DHCP_BROADCAST,
    SM_DHCP_DISCOVER,
    SM_DHCP_REQUEST,
    SM_DHCP_BIND,
    SM_DHCP_BOUND,
    SM_DHCP_DISABLED,
} SM_DHCP;

typedef union _DHCP_STATE
{
    struct
    {
        unsigned char bIsBound : 1;
        unsigned char bOfferReceived : 1;
    } bits;
    BYTE Val;
} DHCP_STATE;


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
#if !defined(_DHCP_C)
    extern SM_DHCP smDHCPState;
    extern DHCP_STATE DHCPState;
#endif


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#define DHCPDisable() (smDHCPState = SM_DHCP_DISABLED)
#define DHCPIsBound() (DHCPState.bits.bIsBound)


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void DHCPTask(void);
void DHCPReset(void);

#endif // _DHCP_H
