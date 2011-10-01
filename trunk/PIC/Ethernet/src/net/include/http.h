/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack HTTP Server Module           *
 *============================================================================*
 *                                                                            *
 * See httpd.c for more details                                               *
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
 * 08/14/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 04/25/07 Jorge Amodio      Cleanup                                         *
 ******************************************************************************/
#ifndef _HTTP_H
#define _HTTP_H

/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#if !defined(HTTP_PORT)
#define HTTP_PORT            (80)
#endif

#define HTTP_START_OF_VAR    (0x0000)
#define HTTP_END_OF_VAR      (0xFFFF)


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void HTTPInit(void);
void HTTPServer(void);

#endif // _HTTP_H
