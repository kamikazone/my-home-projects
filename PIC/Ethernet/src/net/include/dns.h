/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack DNS Client Module            *
 *============================================================================*
 *                                                                            *
 * See dns.c for details                                                      *
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
 * 07/31/06 Howard Schlunder  Original                                        *
 ******************************************************************************/
#ifndef _DNS_H
#define _DNS_H

#include "net/include/stacktsk.h"

/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void DNSResolve(BYTE *HostName);
BOOL DNSIsResolved(IP_ADDR *HostIP);

#endif // _DNS_H
