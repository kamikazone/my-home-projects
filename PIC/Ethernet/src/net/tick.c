/******************************************************************************
 * Tick Manager module for Microchip TCP/IP Stack                             *
 *============================================================================*
 *                                                                            *
 *                                                                            *
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
 * 06/28/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 06/27/07 Jorge Amodio      Updated timer setup code from 4.02 version      *
 *                            Added second tick counter for time routines     *
 ******************************************************************************/
#define _TICK_C

#include "net/include/stacktsk.h"
#include "net/include/tick.h"

#if defined(USE_TIME)
#include "time/include/time.h"
#endif

/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define PERIOD 	  ((WORD)((TCY_CLOCK+32+TICKS_PER_SECOND/2)/64/TICKS_PER_SECOND))
#define TICK_LOAD ((WORD)((-(TCY_CLOCK+2+TICKS_PER_SECOND/2)/4/TICKS_PER_SECOND)+4))


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
TICK TickCount = 0;    // 10ms/unit

#if defined(USE_TIME)
extern time_t _time_tick;
#endif

#if defined(TIME_SOURCE_TICK)
static unsigned int _tcon;
#endif


/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/

/******************************************************************************
 * Function:        void TickInit(void)
 * PreCondition:    None
 * Input:           None
 * Output:          Tick manager is initialized.
 * Side Effects:    None
 * Overview:        Initializes Timer0 as a tick counter.
 * Note:            None
 ******************************************************************************/
void TickInit(void)
{
#if defined(__C30__)
	// Set up timer1 to wake up by timeout
	// 1:64 prescale
	T1CONbits.TCKPS = 2;
	// Base
	PR1 = (WORD)PERIOD;
	// Clear counter
	TMR1 = 0;
	// Enable timer interrupt
	IFS0bits.T1IF = 0;
	IEC0bits.T1IE = 1;
	// Start timer
	T1CONbits.TON = 1;
#else
    // Initialize the time
    TMR0H = (TICK_LOAD & 0xFF00)>>8;
    TMR0L = TICK_LOAD & 0xFF;

	// Set up the timer interrupt
	INTCON2bits.TMR0IP = 0;		// Low priority
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;		// Enable interrupt

    // Timer0 on, 16-bit, internal timer, 4:1 prescale
    T0CON = 0x81;

#endif

#if defined(USE_TIME) && defined(TIME_SOURCE_TICK)
    _tcon = TICKS_PER_SECOND - 1;
#endif
}

/******************************************************************************
 * Function:        TICK TickGet(void)
 * PreCondition:    None
 * Input:           None
 * Output:          Current tick value is given
 *                  1 tick represents approximately 10ms
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
TICK TickGet(void)
{
    return TickCount;
}

#if defined(__18CXX)
/******************************************************************************
 * Function:        void TickUpdate(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        Internal Tick and Seconds count are updated.
 * Note:            None
 ******************************************************************************/
void TickUpdate(void)
{
	WORD_VAL TMR0Val;

    if(INTCONbits.TMR0IF)
    {
		TMR0Val.v[0] = TMR0L;
		TMR0Val.v[1] = TMR0H;
		TMR0Val.Val += (WORD)TICK_LOAD;
		TMR0H = TMR0Val.v[1];
		TMR0L = TMR0Val.v[0];

        TickCount++;

#if defined(USE_TIME) && defined(TIME_SOURCE_TICK)
        if ( _tcon-- == 0 )
        {
            _time_tick++;
            _tcon = TICKS_PER_SECOND - 1;
        }
#endif

        INTCONbits.TMR0IF = 0;
    }

#if defined(USE_TIME) && defined(TIME_SOURCE_32KTIMER)
    if(PIR1bits.TMR1IF)
    {
        TMR1H = 0x80;
        PIR1bits.TMR1IF = 0;
        _time_tick++;
    }
#endif

}

#else // (C30)
/******************************************************************************
 * Function:        void _ISR _T1Interrupt(void)
 * PreCondition:    None
 * Input:           None
 * Output:          TickCount variable is updated
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
void _ISR __attribute__((__no_auto_psv__)) _T1Interrupt(void)
{
    TickCount++;

#if defined(USE_TIME) && defined(TIME_SOURCE_TICK)
        if ( _tcon-- == 0 )
        {
            _time_tick++;
            _tcon = TICKS_PER_SECOND - 1;
        }
#endif

    IFS0bits.T1IF = 0;             // Reset interrupt flag

    return;
}
#endif
