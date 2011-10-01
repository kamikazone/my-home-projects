/******************************************************************************
 * Header definitions for the Real Time Clock and Calendar module             *
 *============================================================================*
 *                                                                            *
 * See "time.c" for details.                                                  *
 *                                                                            *
 * SOFTWARE LICENSE AGREEMENT                                                 *
 *                                                                            *
 * This software is provided to you free of charge with the sole condition    *
 * of preserving this Copyright Notice. This software is provided "AS IS".    *
 * LJCV Eelectronics disclaims all warranties, express, implied, statutory or *
 * otherwise, not limited to merchantability, fitness for a particular        *
 * purporse, and infringement. LJCV Electronics shall in no event be liable   *
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
#ifndef _TIME_H
#define _TIME_H

#include "include/generic_typedefs.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
typedef struct _tm
{
    BYTE    tm_sec;    // Seconds [0-60]
    BYTE    tm_min;    // Minutes [0-59]
    BYTE    tm_hour;   // Hours [0-23]
    BYTE    tm_mday;   // Day [1-31]
    BYTE    tm_mon;    // Month [0-11]
    int     tm_year;   // Year
    BYTE    tm_wday;   // Day of Week [0-6], 0 = Sunday
    int     tm_yday;   // Day of year [0-365]
} tm;

typedef unsigned long time_t;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define START_YEAR           2000
#define START_WDAY           6
#define SECS_MINUTE          60
#define SECS_HOUR            3600
#define SECS_DAY             86400
#define LOCAL_OFFSET_SECS    ((long) TZ_OFFSET*SECS_HOUR)


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void SetTimeTick(time_t t);
time_t GetTimeTick(void);
time_t mktime(tm *p);
void offtime(tm *ts, time_t t, long offset);
void asctime(tm *p, BYTE *q, BYTE f);

#if defined(TIME_SOURCE_32KTIMER)
void Init32KTimer(void);
#endif

#endif  // _TIME_H
