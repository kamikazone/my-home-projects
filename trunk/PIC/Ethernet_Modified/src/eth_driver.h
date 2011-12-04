
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

void MACInit(void);
void SendUDPPacket(void);
WORD swaps(WORD v);

#endif

