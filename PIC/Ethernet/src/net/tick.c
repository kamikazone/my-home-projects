
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
    TMR0H = (TICK_LOAD & 0xFF00)>>8;
    TMR0L = TICK_LOAD & 0xFF;
    // Set up the timer interrupt
    INTCON2bits.TMR0IP = 0;		// Low priority
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;		// Enable interrupt

    // Timer0 on, 16-bit, internal timer, 4:1 prescale
    T0CON = 0x81;
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

        INTCONbits.TMR0IF = 0;
    }

}

