
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

typedef struct _ETHER_FRAME
{
    ETHER_HEADER ethHeader;
    IP_HEADER ipHeader;
    UDP_HEADER udpHeader;
} ETHER_FRAME;

void SendData(void)
{
    ETHER_FRAME frame;
    BYTE destMAC[] = {0xff,0xff,0xff,0xff,0xff,0xff};
    BYTE myMAC[] = {0x00,0x04,0xa3,0x00,0x02,0x00};

    memcpy(frame.ethHeader.DestMACAddr.v, (void *)destMAC, sizeof(destMAC) );
    memcpy(frame.ethHeader.SourceMACAddr.v, (void *)myMAC, sizeof(destMAC) );
}

IP_HEADER SendIP(BYTE* data)
{

}

void SendUDP(BYTE* data)
{
    BYTE* udpData;
    UDP_HEADER header;
    header.SourcePort = 2680;
    header.DestinationPort = 30303;
    header.Length = 14;
    header.Checksum = 0;
    memcpy(udpData, (void*)&header, sizeof(header));
    memcpy(udpData, data, sizeof(data));
    SendIP(udpData);
}

void main(void)
{
    InitializeBoard();
    MACInit();
    while (1)
    {
        //SendUDPPacket();
        SendUDP("Kozhikode");
    }
}

