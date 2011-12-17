
#define _MAIN_C
#include "generic_typedefs.h"
#include "minipic10t.h"
#include "mac.h"
#include "enc28j60.h"
#include "eth_driver.h"
#include "stdlib.h"
#include <string.h>

#pragma config OSC=EC, PWRT=ON, BOREN=OFF, WDT=OFF, MCLRE=OFF, PBADEN=OFF, LVP=OFF, XINST=OFF

#define ETH_HEADER_LEN	14
#define IP_HEADER_LEN	20
#define UDP_HEADER_LEN	8
#define DATA_LEN 20

BYTE FrameData[ETH_HEADER_LEN + IP_HEADER_LEN + UDP_HEADER_LEN + DATA_LEN];

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



void SendEthernetData(BYTE* data, WORD len)
{
    int i;
    BYTE* ethernetData;
	ETHER_HEADER header;
    BYTE destMAC[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    BYTE myMAC[] = { 0x00, 0x04, 0xa3, 0x00, 0x02, 0x00 };

    memcpy(header.DestMACAddress.v, destMAC, sizeof(destMAC));
    memcpy(header.SourceMACAddress.v, myMAC, sizeof(myMAC));

    header.Type.Val = swaps(0x0800);

    memcpy(ethernetData, &header, sizeof(ETHER_HEADER));
    memcpy(ethernetData + sizeof(ETHER_HEADER), data, len);
    
    SendUDPPacket( ethernetData, sizeof(ethernetData));   
}

void SendIP(BYTE* data, WORD len)
{
    int i;
    IP_HEADER header;
    BYTE source[] = { 192, 168, 1, 12 };
    BYTE dest[] = { 255, 255, 255, 255 };

    //header.VersionIHL = 4;
    header.HeaderLength = 0x45;
    header.TypeOfService = 0;
    header.TotalLength = swaps(34);
    header.Identification = swaps(0x17);
    header.FragmentInfo = swaps(0);
    header.TimeToLive = 100;
    header.Protocol = 17;
    header.HeaderChecksum = swaps(0x9500);
    memcpy( header.SourceAddress.v, source, sizeof(source));
    memcpy( header.DestAddress.v, dest, sizeof(dest));

    memcpy(FrameData + ETH_HEADER_LEN, &header, IP_HEADER_LEN);
    memcpy(FrameData + ETH_HEADER_LEN + IP_HEADER_LEN, data, len);
    
    SendEthernetData(FrameData, sizeof(IP_HEADER) + len );
}

void SendUDP(BYTE* data, WORD len)
{
	int i;
    UDP_HEADER header;
    header.SourcePort = swaps(0x0b2c);
    header.DestinationPort = swaps(30303);
    header.Length = swaps(14);
    header.Checksum = swaps(0);

    memcpy(FrameData + ETH_HEADER_LEN + IP_HEADER_LEN, &header, UDP_HEADER_LEN);
    memcpy(FrameData + ETH_HEADER_LEN + IP_HEADER_LEN + UDP_HEADER_LEN, data, len);

    SendIP(FrameData, len + UDP_HEADER_LEN);
}





void main(void)
{
	BYTE UDPData[] = {0x00, 0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0x00 ,0x04  ,0xa3 ,0x00 ,0x02 ,0x00 ,0x08 ,0x00 ,0x45 ,0x00, 0x00 ,0x22 ,0x05 ,0x55 ,0x00 ,0x00 ,0x64 ,0x11  ,0x8f ,0xc2 ,0xc0 ,0xa8 ,0x01 ,0x0c ,0xff ,0xff, 0xff ,0xff ,0x0b ,0x2c ,0x76 ,0x5f ,0x00 ,0x0e  ,0x00 ,0x00 ,0x43 ,0x6f ,0x62 ,0x72 ,0x61 ,0x78, 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00  ,0x00 ,0x00 ,0x00 ,0x00 };
	WORD len = 6;
    BYTE data[] = {'C', 'o', 'b', 'r', 'a', 'x'};
    InitializeBoard();
    MACInit();
    while (1)
    {
        SendUDPPacket(UDPData, sizeof(UDPData));
        //SendUDP(data, len);
    }
}


