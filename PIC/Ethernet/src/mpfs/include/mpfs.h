/******************************************************************************
 * Header definitions for Microchip simple File System                        *
 *============================================================================*
 *                                                                            *
 * See mpfs.c for details                                                     *
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
 * 05/31/06 Howard Schlunder  Changed EEPROM addressing to 32 bits            *
 * 04/25/07 Jorge Amodio      Moved to it's own directory as a module         *
 * 05/02/07 Jorge Amodio      Added macros MPFS_USE_24BITADDR, and            *
 *                            MPFS_USE_32BIT_ADDR for 24 and 32 bits memory   *
 *                            addressing.                                     *
 ******************************************************************************/
#ifndef _MPFS_H
#define _MPFS_H

#include "include/generic_typedefs.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
#if defined(MPFS_USE_PGRM)
    typedef ROM BYTE* MPFS;
    typedef WORD MPFS_OFFSET;
#else
  #if defined(MPFS_USE_32BIT_ADDR)
    typedef DWORD MPFS;
    typedef DWORD MPFS_OFFSET;
  #elif defined(MPFS_USE_24BIT_ADDR)
    typedef LWORD MPFS;
    typedef LWORD MPFS_OFFSET;
  #else  // 16 bit
    typedef WORD MPFS;
    typedef WORD MPFS_OFFSET;
  #endif
#endif


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define MPFS_NOT_AVAILABLE   (0x0)

#if defined(MPFS_USE_PGRM)
    #define MPFS_INVALID     (MPFS)(0xffffff)
#else
  #if defined(MPFS_USE_32BIT_ADDR)
    #define MPFS_INVALID     (0xffffffff)
  #elif defined(MPFS_USE_24BIT_ADDR)
    #define MPFS_INVALID     (0xffffff)
  #else  // 16 bit
    #define MPFS_INVALID     (0xffff)
  #endif
#endif


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
#if !defined(_MPFS_C)
extern BYTE mpfsOpenCount;
extern MPFS _currentHandle;
extern BYTE _currentCount;
#endif


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#define MPFSIsEOF()     (_currentHandle == MPFS_INVALID)
#define MPFSIsInUse()   (mpfsOpenCount)
#define MPFSTell()      (_currentHandle)

#if !defined(MPFS_USE_EEPROM)
#define MPFSPutBegin(handle)  (_currentHandle = handle)
#define MPFSGetEnd()          (_currentHandle)
#define MPFSGetBegin(handle)  (_currentHandle = handle)
#endif


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
BOOL MPFSInit(void);
MPFS MPFSOpen(BYTE* name);
void MPFSClose(void);
BYTE MPFSGet(void);
MPFS MPFSFormat(void);
BOOL MPFSPut(BYTE b);
MPFS MPFSPutEnd(void);
MPFS MPFSSeek(MPFS_OFFSET offset);

#if defined(MPFS_USE_EEPROM)
BOOL MPFSPutBegin(MPFS handle);
MPFS MPFSGetEnd(void);
BOOL MPFSGetBegin(MPFS handle);
#endif

#endif // _MPFS_H

