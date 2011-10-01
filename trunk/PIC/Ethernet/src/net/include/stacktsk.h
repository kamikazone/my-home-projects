/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack FSM module                   *
 *============================================================================*
 *                                                                            *
 * See stacktsk.c for details                                                 *
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
 * 08/10/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 08/07/03 Nilesh Rajbharti  Rev 2.21 - TFTP Client addition                 *
 * 09/30/04 Howard Schlunder  Added MCHP_MAC, MAC_POWER_ON_TEST,              *
 *                            EEPROM_BUFFER_SIZE, USE_LCD                     *
 * 08/09/06 Howard Schlunder  Removed MCHP_MAC, added STACK_USE_NBNS,         *
 *                            STACK_USE_DNS, and STACK_USE_GENERIC_TCP_EXAMPLE*
 * 03/30/07 Jorge Amodio      Moved hardware definitions to specific separate *
 *                            configuration files, moved all stack user       *
 *                            options and configurations to config.h          *
 * 04/25/07  Jorge Amodio     Cleanup                                         *
 * 06/26/07  Jorge Amodio     Added MAC_ADDR_ZERO & MAC_ADDR_BCAST defs       *
 ******************************************************************************/
#ifndef _STACKTSK_H
#define _STACKTSK_H

#include "include/config.h"
#include "include/generic_typedefs.h"


/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
typedef BYTE BUFFER;

typedef struct _MAC_ADDR
{
    BYTE v[6];
} MAC_ADDR;

typedef union _IP_ADDR
{
    BYTE        v[4];
    DWORD       Val;
} IP_ADDR;

typedef struct _NODE_INFO
{
    MAC_ADDR    MACAddr;
    IP_ADDR     IPAddr;
} NODE_INFO;

typedef struct _APP_CONFIG
{
    IP_ADDR     MyIPAddr;
    MAC_ADDR    MyMACAddr;
    IP_ADDR     MyMask;
    IP_ADDR     MyGateway;
    IP_ADDR     PrimaryDNSServer;
    struct
    {
        unsigned char bIsDHCPEnabled : 1;
        unsigned char bInConfigMode : 1;
    } Flags;
    WORD_VAL    SerialNumber;
    IP_ADDR     SMTPServerAddr;     // Not used.
    IP_ADDR     TFTPServerAddr;     // Not used.
    BYTE        NetBIOSName[16];
} APP_CONFIG;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define MAC_ADDR_ZERO     {0x00,0x00,0x00,0x00,0x00,0x00}
#define MAC_ADDR_BCAST    {0xff,0xff,0xff,0xff,0xff,0xff}


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
#if !defined(_MAIN_C)
  extern APP_CONFIG AppConfig;
#endif


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#if defined(STACK_USE_IP_GLEANING) || defined(STACK_USE_DHCP)
  #define StackIsInConfigMode()  (AppConfig.Flags.bInConfigMode)
#else
  #define StackIsInConfigMode()  (FALSE)
#endif


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void StackInit(void);
void StackTask(void);

#endif // _STACKTSK_H
