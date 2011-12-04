
#ifndef _MAC_H
#define _MAC_H

#include "enc28j60.h"

typedef BYTE BUFFER;

typedef struct _MAC_ADDR
{
    BYTE v[6];
} MAC_ADDR;

typedef union _IP_ADDR
{
    BYTE        v[4];
    DWORD       Val;
} IP_ADDR;

typedef struct _NODE_INFO
{
    MAC_ADDR    MACAddr;
    IP_ADDR     IPAddr;
} NODE_INFO;

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

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
#if defined(USE_ENC28J60) || defined(__PIC18FXXJ60)
typedef enum _DUPLEX {
    HALF = 0, 
    FULL = 1, 
    USE_PHY = 2
} DUPLEX;

typedef enum _CLK_CONFIG {
    Divide1,
    Divide2,
    Divide3,
    Divide4,
    Divide8
} CLK_CONFIG;
#endif


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define MAC_IP      (0u)
#define MAC_ARP     (0x6u)
#define MAC_UNKNOWN (0x0ffu)
#define INVALID_BUFFER  (0xffu)


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
//extern BUFFER CurrentTxBuffer;


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#if defined(USE_ENC28J60)|| defined(__PIC18FXXJ60)
#define SetLEDConfig(NewConfig)  WritePHYReg(PHLCON, NewConfig)
#define GetLEDConfig()  ReadPHYReg(PHLCON).Val
#endif

/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void MACInit(void);
BOOL MACIsLinked(void);
BOOL MACGetHeader(MAC_ADDR *remote, BYTE* type);
void MACSetRxBuffer(WORD offset);
BYTE MACGet(void);
WORD MACGetArray(BYTE *val, WORD len);
void MACDiscardRx(void);
WORD MACGetFreeRxSize(void);
void MACPutHeader(MAC_ADDR *remote, BYTE type, WORD dataLen);
BOOL MACIsTxReady(BOOL HighPriority);
void MACSetTxBuffer(BUFFER buffer, WORD offset);
void MACPut(BYTE val);
void MACPutArray(BYTE *val, WORD len);
void MACDiscardTx(BUFFER buffer);
void MACFlush(void);
BUFFER MACGetTxBuffer(BOOL HighPriority);

//RAHUL

void BankSel(WORD Register);
void WriteReg(BYTE Address, BYTE Data);
REG ReadETHReg(BYTE Address);
void SendSystemReset(void);
void DelayMs(unsigned int ms);
void BFSReg(BYTE Address, BYTE Data);

//RAHUL


#if defined(USE_ENC28J60)|| defined(__PIC18FXXJ60)
void MACSetDuplex(DUPLEX DuplexState);
void MACPowerDown(void);
void MACPowerUp(void);
void MACCopyRxToTx(WORD RxOffset, WORD TxOffset, WORD len);
void WritePHYReg(BYTE Register, WORD Data);
PHYREG ReadPHYReg(BYTE Register);
void SetRXHashTableEntry(MAC_ADDR DestMACAddr);

#if defined(STACK_USE_HW_CKSUM)
WORD MACCalcRxChecksum(WORD offset, WORD len);
WORD MACCalcTxChecksum(WORD offset, WORD len);
WORD CalcIPBufferChecksum(WORD len);
#endif

#endif // USE_ENC28J60

#endif // _MAC_H
