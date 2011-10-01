/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack SNTP Client Module           *
 *============================================================================*
 *                                                                            *
 * See sntp.c for details                                                      *
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
#ifndef _SNTP_H
#define _SNTP_H

#include "time/include/time.h"

/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define SNTP_PORT         123
#define SNTP_ARP_TIMEOUT  (2 * TICK_SECOND)
#define SNTP_REQ_TIMEOUT  (10 * TICK_SECOND)


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
BYTE IsClockValid(void);
void SNTPRequest(void);
void SNTPTask(void);

#endif // _SNTP_H
