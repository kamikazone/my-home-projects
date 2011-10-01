/******************************************************************************
 * Header definitions for Microchip TCP/IP Stack FTP Server module            *
 *============================================================================*
 *                                                                            *
 * See ftpd.c for details                                                     *
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
 * 04/23/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 ******************************************************************************/
#ifndef _FTP_H
#define _FTP_H

/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void FTPInit(void);
BOOL FTPServer(void);

#endif  // _FTP_H
