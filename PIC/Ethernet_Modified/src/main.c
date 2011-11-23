
#define _MAIN_C
#include "config.h"
#include "mac.h"
#include "helpers.h"
#include "udp.h"
#include "ip.h"

#pragma config OSC=EC, PWRT=ON, BOREN=OFF, WDT=OFF, MCLRE=OFF, PBADEN=OFF, LVP=OFF, XINST=OFF


APP_CONFIG AppConfig = {
    DEFAULT_IP_ADDRESS, DEFAULT_MAC_ADDRESS, DEFAULT_NETMASK,
    DEFAULT_GATEWAY, DEFAULT_NS1,
    {0b00000001}, // Flags, enable DHCP
};

BYTE myDHCPBindCount = 0;
static char AN0String[8];
extern unsigned long IP_RX_pktcnt;
extern unsigned long IP_TX_pktcnt;
ROM char CRLF[] = "\r\n";
extern BYTE DHCPBindCount;

static void InitializeBoard(void) {
    // Set direction and initial default valuefor GPIO Ports
    LATA = INIT_PORTA;
    TRISA = INIT_TRISA;
    LATB = INIT_PORTB;
    TRISB = INIT_TRISB;
    LATC = INIT_PORTC;
    TRISC = INIT_TRISC;
    // Initialize serial RS232 Interface
    UART_TXSTA = 0b00100000; // Set baud rate and enable UART serial
    UART_RCSTA = 0b10010000; // RS232 interface

#if defined(USART_USE_BRGH_HIGH)
    UART_TXSTAbits.BRGH = 1;
#endif

    UART_SPBRG = SPBRG_VAL;
    ADCON0 = INIT_ADCON0; // Set up analog features of PORTA
    ADCON1 = INIT_ADCON1;
    INTCON2bits.RBPU = 0; // Enable internal PORTB pull-ups
    RCONbits.IPEN = 1; // Enable Interrupts
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPISTAT = ENC_SPISTAT_CFG;
}

static BYTE IPHeaderLen;
static WORD _Identifier = 0;
#define IPv4                (0x40u)
#define IP_VERSION          IPv4
#define IP_IHL              (0x05)
#define IP_SERVICE_NW_CTRL  (0x07)
#define IP_SERVICE_IN_CTRL  (0x06)
#define IP_SERVICE_ECP      (0x05)
#define IP_SERVICE_OVR      (0x04)
#define IP_SERVICE_FLASH    (0x03)
#define IP_SERVICE_IMM      (0x02)
#define IP_SERVICE_PRIOR    (0x01)
#define IP_SERVICE_ROUTINE  (0x00)

#define IP_SERVICE_N_DELAY  (0x00)
#define IP_SERCICE_L_DELAY  (0x08)
#define IP_SERVICE_N_THRPT  (0x00)
#define IP_SERVICE_H_THRPT  (0x10)
#define IP_SERVICE_N_RELIB  (0x00)
#define IP_SERVICE_H_RELIB  (0x20)

#define IP_SERVICE          (IP_SERVICE_ROUTINE | IP_SERVICE_N_DELAY)
#define MY_IP_TTL           (100)  // Time-To-Live in Seconds


void SendUDPPacket(void)
{
    UDP_HEADER UDPHeader;
    IP_HEADER IPHeader;
    BYTE data[] = {'C', 'o', 'b', 'r', 'a', 'x'};
    MAC_ADDR RemMac;
    BUFFER buf = 0;
    RemMac.v[0] = 0xff;
    RemMac.v[1] = 0xff;
    RemMac.v[2] = 0xff;
    RemMac.v[3] = 0xff;
    RemMac.v[4] = 0xff;
    RemMac.v[5] = 0xff;

    UDPHeader.SourcePort = swaps(2860);
    UDPHeader.DestinationPort = swaps(30303);
    UDPHeader.Length = (WORD) ((WORD) sizeof (data) + (WORD)sizeof (UDP_HEADER));
    UDPHeader.Checksum = 0x0000;
    //IPPutHeader
    IPHeader.VersionIHL = IPv4 | IP_IHL;
    IPHeader.TypeOfService = IP_SERVICE;
    IPHeader.TotalLength = sizeof (IPHeader) + UDPHeader.Length;
    IPHeader.Identification = ++_Identifier;
    IPHeader.FragmentInfo = 0;
    IPHeader.TimeToLive = MY_IP_TTL;
    IPHeader.Protocol = IP_PROT_UDP;
    IPHeader.HeaderChecksum = 0;
    IPHeader.SourceAddress = AppConfig.MyIPAddr;
    IPHeader.DestAddress.v[0] = 255;
    IPHeader.DestAddress.v[1] = 255;
    IPHeader.DestAddress.v[2] = 255;
    IPHeader.DestAddress.v[3] = 255;

    IPHeader.TotalLength = swaps(IPHeader.TotalLength);
    IPHeader.Identification = swaps(IPHeader.Identification);
    IPHeader.HeaderChecksum = swaps(IPHeader.HeaderChecksum);
    IPHeader.HeaderChecksum = CalcIPChecksum((BYTE*) & IPHeader, sizeof (IPHeader));

    while (!IPIsTxReady(TRUE));
    //UDPFlush
    MACSetTxBuffer(buf, 0 + sizeof (IP_HEADER));
    MACPutHeader(&RemMac, MAC_IP, (sizeof (IPHeader) + UDPHeader.Length));
    MACPutArray((BYTE*) & IPHeader, sizeof (IPHeader)); // IP Heaer
    UDPHeader.Length = swaps(UDPHeader.Length);
    MACPutArray((BYTE*) & UDPHeader, sizeof (UDPHeader)); // UDP Header
    MACPutArray(data, sizeof (data));
    MACFlush();
    //end UDPFlush
}

void main(void)
{
    InitializeBoard();
    MACInit();
    while (1)
    {
        SendUDPPacket();
    }
}

