
#define _MAIN_C
#include "minipic10t.h"
#include "mac.h"
#include "enc28j60.h"
#include "eth_driver.h"
#include <string.h>

#pragma config OSC=EC, PWRT=ON, BOREN=OFF, WDT=OFF, MCLRE=OFF, PBADEN=OFF, LVP=OFF, XINST=OFF


static void InitializeBoard(void) 
{
    // Set direction and initial default valuefor GPIO Ports
    LATA = INIT_PORTA;
    TRISA = INIT_TRISA;
    LATB = INIT_PORTB;
    TRISB = INIT_TRISB;
    LATC = INIT_PORTC;
    TRISC = INIT_TRISC;

    INTCON2bits.RBPU = 0; // Enable internal PORTB pull-ups
    RCONbits.IPEN = 1; // Enable Interrupts
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPISTAT = ENC_SPISTAT_CFG;
}

void main(void)
{
    InitializeBoard();
    MACInit();
    while (1)
    {
        SendUDPPacket();
        //SendUDP("Kozhikode");
    }
}

