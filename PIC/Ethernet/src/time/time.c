/******************************************************************************
 * Generic Real Time Clock and Calendar module                                *
 *============================================================================*
 *                                                                            *
 * This module includes a set of functions to implement a basic Real Time     *
 * Clock and Calendar.                                                        *
 *                                                                            *
 * While these functions are similar in concept to those found in the Unix    *
 * standard libc library, they have been recreated for an 8/16 bit MCU where  *
 * resources are limited, then to optimize and reduce code none of the        *
 * functions perform any checks to verify that the arguments are valid.       *
 *                                                                            *
 * The current version of the time module relies on a master seconds 32 bit   *
 * tick counter, a 0 value represents Jan 1, 2000 00:00:00 UTC, this counter  *
 * will obviously rollover after Feb 8, 2136 06:28:15 UTC.                    *
 *                                                                            *
 * To increment the seconds tick counter there are currently to options based *
 * on timer interrupts. The first option (TIME_SOURCE_TICK) uses the Timer0   *
 * 10ms interrupt counter implemented in the Microchip TCP/IP stack.          *
 *                                                                            *
 * A new version currently under development will add the option to use an    *
 * external 32.768KHz watch crystal as clock source for the timer, and        *
 * functions to provide access to an external RTCC or the internal RTCC of    *
 * some 16-bit microcontrollers. (Note: part of the code is already present   *
 * but not fully tested yet, particularly with 16-bit MCUs.                   *
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

#if defined(USE_TIME)
#include "time/include/time.h"

/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
// Three character representation of month names
ROM char *month_str[] = { 
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// Three character representation of the day of the week
ROM char *wday_str[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

// Days on each month for regular and leap years
ROM char days_month[2][12] = {
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

// The following table is used to construct the string with different
// formats produced by asctime(), each group represents a time format
// that is composed by a sequence of 1 to 4 smaller character strings.
ROM char tformat[9][4] = {
    { 1, 2, 3, 4 }, { 2, 3, 0, 0 }, { 3, 0, 0, 0 }, { 5, 0, 0, 0 },
    { 3, 5, 0, 0 }, { 5, 3, 0, 0 }, { 6, 0, 0, 0 }, { 5, 6, 0, 0 },
    { 6, 5, 0, 0 }
};

time_t _time_tick = 0;           // This is the master seconds tick counter

/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/

//*****************************************************************************
// SetTimeTick updates the master tick counter with the value of argument t
//
void SetTimeTick(time_t t)
{
    _time_tick = t;
}

//*****************************************************************************
// GetTimeTick() returns the current master second tick counter
//
time_t GetTimeTick(void)
{
    time_t t;

    t = _time_tick;
    return(t);
}

//*****************************************************************************
// isleap() takes the argument year and returns a non zero value if it is a
// leap year. 
//
int isleap(int year) {

    BYTE y;

    y = (( year % 4 == 0 ) && ( year % 100 != 0 || year % 400 == 0 ));
    return(y);
}

//*****************************************************************************
// mktime() take a tm time structure and generates the equivalent time_t
// value.
//
time_t mktime(tm *p)
{
    time_t j;
    int i;

    j = 0;

    for ( i = START_YEAR ; i < p->tm_year ; i++ )
    {
        j += isleap(i) ? 366 : 365;
    }
  
    for ( i = 0 ; i < p->tm_mon ; i++ )
    {
        j += days_month[isleap(p->tm_year)][i];
    }
   
    j = j + p->tm_mday - 1;
    j *= 86400;      // convert to seconds

    j = j + (time_t) (p->tm_hour * 3600L);
    j = j + (time_t) (p->tm_min * 60L);
    j = j + (time_t) (p->tm_sec);

    return(j);
}

//*****************************************************************************
// offtime() takes a time_t value and generates the corresponding tm time
// structure taking in account leap years. It also takes an offset value
// as argument to facilitate correction for Time Zone and Day Light Savings
// Time.
//
void offtime(tm *ts, time_t t, long offset)
{
    long days, j;
    int i, k;
    char *p;

    t += offset;                               // Correct for TZ/DST offset
    days = t / 86400;                          // Integer number of days
    j = t % 86400;                             // Fraction of a day
    ts->tm_hour = j / 3600;                    // Integer number of hours
    j %= 3600;                                 // Fraction of hour
    ts->tm_min = j / 60;                       // Integer number of minutes
    ts->tm_sec = j % 60;                       // Remainder seconds
    ts->tm_wday = ( days + START_WDAY ) % 7;   // Day of the week

    i = START_YEAR;

    // Count the number of days per year taking in account leap years
    // to determine the year number and remaining days
    while ( days >= (j = isleap(i) ? 366 : 365) )
    {
       i++;
       days -= j;
    }

    while ( days < 0 )
    {
        i--;
        days += isleap(i) ? 366 : 365;
    }

    ts->tm_year = i;                           // We have the year  
    ts->tm_yday = days;                        // And the number of days

    i = isleap(i);

    // Count the days for each month in this year to determine the month
    for ( k = 0 ; days >= days_month[i][k] ; ++k )
    {
        days -= days_month[i][k];
    }

    ts->tm_mon = k;                            // We have the month
    ts->tm_mday = days + 1;                    // And the day of the month
}

//*****************************************************************************
// asctime() takes a tm time structure and converts the values into different
// character string formats. The seecond argument is a pointer to a character
// array that must be defined by the calling function with enough memory
// allocated to hold the resulting string, the string is terminated with the
// null (\0) character and does not contain CRLF (\n\r).
//
// The last argument specifies the desired output format for the string,
// current supported formats are:
//
//    0  DDD MMM dd HH:MM:SS YYYY
//    1  MMM dd HH:MM:SS
//    2  HH:MM:SS
//    3  mm/dd/yy
//    4  HH:MM:SS mm/dd/yy
//    5  mm/dd/yy HH:MM:SS
//    6  HH:MM
//    7  mm/dd/yy HH:MM
//    8  HH:MM mm/dd/yy
//
void asctime(tm *p, BYTE *q, BYTE format)
{
    BYTE i, j;

    i = 0;

    for ( j = 0 ; j < 4 ; j++ )
    {
       if (tformat[format][j] == 0 )
       {
           i--;
           break;
       }

       switch (tformat[format][j])
       {
       case 1: // DDD
               memcpypgm2ram( &q[i], wday_str[p->tm_wday], 3);
               i += 3;
               break;

       case 2: // MMM dd
               memcpypgm2ram( &q[i], month_str[p->tm_mon], 3);
               i += 3;
               q[i++] = ' ';
               itoa(p->tm_mday,&q[i++]);

               if ( p->tm_mday > 9 ) i++;

               break;

       case 3: // HH:MM:SS
               if ( p->tm_hour < 10 )
               {
                   q[i++] = '0';
                   itoa(p->tm_hour, &q[i++]);
               } 
               else 
               {
                   itoa(p->tm_hour, &q[i]);
                   i += 2;
               }
               q[i++] = ':';    

               if ( p->tm_min < 10 )
               {
                   q[i++] = '0';
                   itoa(p->tm_min, &q[i++]);
               } 
               else 
               {
                   itoa(p->tm_min, &q[i]);
                   i += 2;
               }
               q[i++] = ':';    

               if ( p->tm_sec < 10 )
               {
                   q[i++] = '0';
                   itoa(p->tm_sec, &q[i++]);
               } 
               else 
               {
                   itoa(p->tm_sec, &q[i]);
                   i += 2;
               }
               break;

       case 4: // YYYY
               itoa(p->tm_year, &q[i]);
               i += 4;
               break;

       case 5: // mm/dd/yy
               if ( p->tm_mon < 9 )
               {
                   q[i++] = '0';
                   itoa(p->tm_mon + 1, &q[i++]);
               } 
               else 
               {
                   itoa(p->tm_mon + 1, &q[i]);
                   i += 2;
               }
               q[i++] = '/';    

               if ( p->tm_mday < 10 )
               {
                   q[i++] = '0';
                   itoa(p->tm_mday, &q[i++]);
               } 
               else 
               {
                   itoa(p->tm_mday, &q[i]);
                   i += 2;
               }
               q[i++] = '/';    
               itoa(p->tm_year, &q[i]);
               memcpy((void *)&q[i], (void *)&q[i+2], 2);
               i += 2;
               q[i] = ' ';
               q[i+1] = ' ';
               break;

       case 6: // HH:MM
               if ( p->tm_hour < 10 )
               {
                   q[i++] = '0';
                   itoa(p->tm_hour, &q[i++]);
               } 
               else 
               {
                   itoa(p->tm_hour, &q[i]);
                   i += 2;
               }
               q[i++] = ':';    

               if ( p->tm_min < 10 )
               {
                   q[i++] = '0';
                   itoa(p->tm_min, &q[i++]);
               } 
               else 
               {
                   itoa(p->tm_min, &q[i]);
                   i += 2;
               }
               break;
       };

       q[i++] = ' ';
    };

    q[i] = '\0';
}

//*****************************************************************************
#if defined(TIME_SOURCE_32KTIMER)
void Init32KTimer(void)
{
#if defined(__C30__)
    #error TIME_SOURCE_32KTIMER option not suppported yet for 16-bit MCUs 
#else
    TMR1H = 0x80;
    TMR1L = 0;
    T1CON = 0b00001111;
    T1CONbits.TMR1ON = 1;
    PIR1bits.TMR1IF = 1;
    PIE1bits.TMR1IE = 1;
#endif
}
#endif

#endif  // USE_TIME
