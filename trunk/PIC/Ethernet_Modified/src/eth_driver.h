
#ifndef _ETH_DRIVER
#define _ETH_DRIVER

#include "minipic10t.h"
#include "generic_typedefs.h"
#include "enc28j60.h"
#include "mac.h"

#define MAXFRAMEC (1500u+sizeof(ETHER_HEADER)+4u)
#define LOW(a)  (a & 0xFF)
#define HIGH(a) ((a>>8) & 0xFF)

typedef struct _ETHER_HEADER
{
    MAC_ADDR DestMACAddr;
    MAC_ADDR SourceMACAddr;
    WORD_VAL Type;
} ETHER_HEADER;

typedef struct _IP_HEADER
{
    BYTE    VersionIHL;
    BYTE    TypeOfService;
    WORD    TotalLength;
    WORD    Identification;
    WORD    FragmentInfo;
    BYTE    TimeToLive;
    BYTE    Protocol;
    WORD    HeaderChecksum;
    IP_ADDR SourceAddress;
    IP_ADDR DestAddress;

} IP_HEADER;

typedef struct _UDP_HEADER
{
    WORD  SourcePort;
    WORD  DestinationPort;
    WORD      Length;
    WORD      Checksum;
} UDP_HEADER;
///////////////////////////////////////////
    #define DEFAULT_MAC_ADDRESS { 0x00, 0x04, 0xa3, 0x00, 0x02, 0x00 }
    #define DEFAULT_IP_ADDRESS  { 192, 168, 1, 12 }
    #define DEFAULT_NETMASK     { 255, 255, 255, 0 }
    #define DEFAULT_GATEWAY     { 192, 168, 1, 1  }
    #define DEFAULT_NS1         { 192, 168, 1, 1  }
typedef struct _APP_CONFIG
{
    IP_ADDR     MyIPAddr;
    MAC_ADDR    MyMACAddr;
    IP_ADDR     MyMask;
    IP_ADDR     MyGateway;
    IP_ADDR     PrimaryDNSServer;
    struct
    {
        unsigned char bIsDHCPEnabled : 1;
        unsigned char bInConfigMode : 1;
    } Flags;
    WORD_VAL    SerialNumber;
    IP_ADDR     SMTPServerAddr;     // Not used.
    IP_ADDR     TFTPServerAddr;     // Not used.
    BYTE        NetBIOSName[16];
} APP_CONFIG;
#define IP_PROT_UDP     (17)
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

//////////////////////////////////////////////////
void MACInit(void);
void SendUDPPacket(void);
WORD swaps(WORD v);

#endif

