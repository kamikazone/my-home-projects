/******************************************************************************
 * Realtek 8019 Ethernet Controller MAC Driver for Microchip TCP/IP Stack     *
 *============================================================================*
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
 * 04/27/00 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 03/21/03 Nilesh Rajbharti  Fixed MACIsTxReady() bug where upon certain bus *
 *                            collision, this would always return FLASE       *
 *                            causing Stack to not handle any incoming        *
 *                            packets at all.                                 *
 * 08/09/06 Howard Schlunder  Slight modifications to work with 3.75          *
 * 04/25/07 Jorge Amodio      Cleanup. Added USE_RTL8019AS macro.             *
 ******************************************************************************/
//#define THIS_IS_MAC_LAYER
#include "include/config.h"

#if defined(USE_RTL8019AS)

#include <string.h>
#include "net/include/stacktsk.h"
#include "net/include/helpers.h"
#include "net/include/mac.h"
#include "include/delay.h"

// Hardware interface to NIC.
#define NIC_DATAPORT   (0x10)
#define NIC_RESET      (0x1f)

// Ethernet definitions
#define MINFRAME       60
#define MINFRAMEC      64
#define CRCLEN         4
#define MAXFRAME       1514
#define MAXFRAMEC      1518

// 8390 Network Interface Controller (NIC) page0 register offsets
#define CMDR           0x00    // command register for read & write
#define PSTART         0x01    // page start register for write
#define PSTOP          0x02    // page stop register for write
#define BNRY           0x03    // boundary reg for rd and wr
#define TPSR           0x04    // tx start page start reg for wr
#define TXSTAT         TPSR
#define TBCR0          0x05     // tx byte count 0 reg for wr
#define TBCR1          0x06     // tx byte count 1 reg for wr
#define ISR            0x07     // interrupt status reg for rd and wr
#define RSAR0          0x08     // low byte of remote start addr
#define RSAR1          0x09     // hi byte of remote start addr
#define RBCR0          0x0A     // remote byte count reg 0 for wr
#define RBCR1          0x0B     // remote byte count reg 1 for wr
#define RCR            0x0C     // rx configuration reg for wr
#define TCR            0x0D     // tx configuration reg for wr
#define DCR            0x0E     // data configuration reg for wr
#define IMR            0x0F     // interrupt mask reg for wr

// NIC page 1 register offsets
#define PAR0           0x01     // physical addr reg 0 for rd and wr
#define CURRP          0x07     // current page reg for rd and wr
#define MAR0           0x08     // multicast addr reg 0 for rd and WR

// NIC page 3 register offsets
#define RTL9346CR      0x01      // RTL 9346 command reg
#define RTL3           0x06      // RTL config reg 3

#define NIC_PAGE_SIZE  (256)

// NIC RAM definitions
#define RAMPAGES       0x20      // Total number of 256-byte RAM pages
#define TXSTART        0x40      // Tx buffer start page - NE2000 mode
#define TXPAGES        (MAC_TX_BUFFER_COUNT * (MAC_TX_BUFFER_SIZE/NIC_PAGE_SIZE))
#define RXSTART        (TXSTART+TXPAGES)      // Rx buffer start page
#define RXSTOP         (TXSTART+RAMPAGES-1)   // Last Rx buffer page
#define DCRVAL         0x48      // Value for data config reg
                                 // 8-bit DMA, big-endian, 1 DMA, Normal

#define RXPAGES (RXSTOP - RXSTART)

#define SET_NIC_READ()      (NIC_DATA_TRIS = 0xff)
#define SET_NIC_WRITE()     (NIC_DATA_TRIS = 0x00)
#define WRITE_NIC_ADDR(a)   {NIC_ADDR_IO = a;}

typedef struct _IEEE_HEADER
{
    MAC_ADDR        DestMACAddr;
    MAC_ADDR        SourceMACAddr;
    WORD_VAL        Len;
    BYTE            LSAPControl[3];
    BYTE            OUI[3];
    WORD_VAL        Protocol;
} IEEE_HEADER;

#define ETHER_IP        (0x00)
#define ETHER_ARP       (0x06)

typedef struct _DATA_BUFFER
{
    BYTE Index;
    BOOL bFree;
} DATA_BUFFER;

typedef struct _ETHER_HEADER
{
    MAC_ADDR        DestMACAddr;
    MAC_ADDR        SourceMACAddr;
    WORD_VAL        Type;
} ETHER_HEADER;

typedef struct _NE_RCR
{
    unsigned int PRX:1;
    unsigned int CRC:1;
    unsigned int FAE:1;
    unsigned int FO:1;
    unsigned int MPA:1;
    unsigned int PHY:1;
    unsigned int DIS:1;
    unsigned int DFR:1;
} NE_RCR;

typedef struct _NE_PREAMBLE
{
    NE_RCR Status;
    BYTE NextPacketPointer;
    WORD ReceivedBytes;

    MAC_ADDR        DestMACAddr;
    MAC_ADDR        SourceMACAddr;
    WORD_VAL        Type;
} NE_PREAMBLE;


static DATA_BUFFER TxBuffers[(TXPAGES*NIC_PAGE_SIZE)/MAC_TX_BUFFER_SIZE];
#define MAX_DATA_BUFFERS        (sizeof(TxBuffers)/sizeof(TxBuffers[0]))

BYTE NICReadPtr;                // Next page that will be used by NIC to load new packet.
BYTE NICCurrentRdPtr;           // Page that is being read...
BYTE NICCurrentTxBuffer;

static void NICReset(void)
{
    SET_NIC_READ();
    WRITE_NIC_ADDR(0);
    INTCON2bits.RBPU = 0;
    NIC_IOW_IO = 1;
    NIC_IOR_IO = 1;
    NIC_RESET_IO = 1;
    Delay10us(1);                  // Reset pulse must be at least 800 ns.
    NIC_RESET_IO = 0;
}

static void NICPut(BYTE reg, BYTE val)
{
    WRITE_NIC_ADDR(reg);
    NIC_DATA_IO = val;
    SET_NIC_WRITE();
    NIC_IOW_IO = 0;

#if TCY_CLOCK > 5000000
    Nop();
    Nop();
#endif

    NIC_IOW_IO = 1;
    SET_NIC_READ();
}

static BYTE NICGet(BYTE reg)
{
    BYTE val;

    SET_NIC_READ();
    WRITE_NIC_ADDR(reg);
    NIC_IOR_IO = 0;

#if TCY_CLOCK > 5000000
    Nop();
    Nop();
#endif

    val = NIC_DATA_IO;
    NIC_IOR_IO = 1;
    return val;
}

static void NICSetAddr(WORD addr)
{
    WORD_VAL t;

    t.Val = addr;
    NICPut(ISR, 0x40);
    NICPut(RSAR0, t.v[0]);
    NICPut(RSAR1, t.v[1]);
}

void MACSetRxBuffer(WORD offset)
{
    WORD_VAL t;

    t.v[1] = NICCurrentRdPtr;
    t.v[0] = sizeof(NE_PREAMBLE);
    t.Val += offset;
    NICSetAddr(t.Val);
}

void MACSetTxBuffer(BUFFER buffer, WORD offset)
{
    WORD_VAL t;

    NICCurrentTxBuffer = buffer;
    t.v[1] = TxBuffers[NICCurrentTxBuffer].Index;
    t.v[0] = sizeof(ETHER_HEADER);
    t.Val += offset;
    NICSetAddr(t.Val);
}

WORD MACGetOffset(void)
{
    WORD_VAL t;

    t.v[1] = NICGet(RSAR1);
    t.v[0] = NICGet(RSAR0);

    return t.Val;
}

void MACInit(void)
{
    BYTE i;

    // On Init, all transmit buffers are free.
    for ( i = 0; i < MAX_DATA_BUFFERS; i++ )
    {
        TxBuffers[i].Index = TXSTART + (i * (MAC_TX_BUFFER_SIZE/NIC_PAGE_SIZE));
        TxBuffers[i].bFree = TRUE;
    }

    NICCurrentTxBuffer = 0;
    NICReset();
    DelayMs(2);
    NICPut(NIC_RESET, NICGet(NIC_RESET));
    DelayMs(2);                    // mimimum Delay of 1.6 ms

    // Continue only if reset state is entered.
    if ( (NICGet(ISR) & 0x80) != 0 )
    {
        NICPut(CMDR, 0x21);        // Select Page 0
        DelayMs(2);
        NICPut(DCR, DCRVAL);       // Initialize Data Configuration Register
        NICPut(RBCR0, 0);          // Clear Remote Byte Count Registers
        NICPut(RBCR1, 0);
        NICPut(RCR, 0x04);         // Initialize Receive Configuration Register
        NICPut(TCR, 0x02);         // Place NIC in LOOPBACK mode 1

        // Initialize Transmit buffer queue
        NICPut(TPSR, TxBuffers[NICCurrentTxBuffer].Index);

        NICPut(PSTART, RXSTART);   // Initialize Receive Buffer Ring
        NICPut(PSTOP, RXSTOP);
        NICPut(BNRY, (BYTE)(RXSTOP-1));

        // Initialize Interrupt Mask Register
        NICPut(ISR, 0xff);         // Clear all status bits
        NICPut(IMR, 0x00);         // No interrupt enabled.
        NICPut(CMDR, 0x61);        // Select Page 1

        // Initialize Physical Address Registers
        NICPut(PAR0+0, AppConfig.MyMACAddr.v[0]);
        NICPut(PAR0+1, AppConfig.MyMACAddr.v[1]);
        NICPut(PAR0+2, AppConfig.MyMACAddr.v[2]);
        NICPut(PAR0+3, AppConfig.MyMACAddr.v[3]);
        NICPut(PAR0+4, AppConfig.MyMACAddr.v[4]);
        NICPut(PAR0+5, AppConfig.MyMACAddr.v[5]);

        // Initialize Multicast registers
        for ( i = 0; i < 8; i++ )
            NICPut(MAR0+i, 0xff);

        NICPut(CURRP, RXSTART);    // Initialize CURRent pointer
        NICReadPtr = RXSTART;      // Remember current receive page
        NICPut(CMDR, 0x22);        // Page 0, Abort Remote DMA and
                                   // Activate the transmitter.
        NICPut(TCR, 0x00);         // Set Normal Mode
    }
}

BOOL MACIsTxReady(BOOL HighPriority)
{
    // NICCurrentTxBuffer always points to free buffer, if there is any.
    // If there is none, NICCurrentTxBuffer will be a in 'Use' state.
    // return TxBuffers[NICCurrentTxBuffer].bFree;
    // Check to see if previous transmission was successful or not.

    return !(NICGet(CMDR) & 0x04);
}

BUFFER MACGetTxBuffer(BOOL HighPriority)
{
    return 0;
}

void MACPut(BYTE val)
{
    NICPut(RBCR0, 1);
    NICPut(RBCR1, 0);
    NICPut(CMDR, 0x12);
    NICPut(NIC_DATAPORT, val);
}

void MACPutArray(BYTE *val, WORD len)
{
    WORD_VAL t;

    t.Val = len + (len & 1);

    NICPut(ISR, 0x40);
    NICPut(RBCR0, t.v[0]);
    NICPut(RBCR1, t.v[1]);
    NICPut(CMDR, 0x12);

    //while ( len-- > 0 )
    while( t.Val-- > 0 )
        NICPut(NIC_DATAPORT, *val++);

    // Make sure that DMA is complete.
#if 0
    len = 255;
    while( len && (NICGet(ISR) & 0x40) == 0 )
        len--;
#endif

}

BYTE MACGet(void)
{
    NICPut(RBCR0, 1);
    NICPut(RBCR1, 0);
    NICPut(CMDR, 0x0a);
    return NICGet(NIC_DATAPORT);
}

WORD MACGetArray(BYTE *val, WORD len)
{
    WORD_VAL t;

    t.Val = len;

    NICPut(ISR, 0x40);
    NICPut(RBCR0, t.v[0]);
    NICPut(RBCR1, t.v[1]);
    NICPut(CMDR, 0x0a);

    while( len-- > 0 )
    {
        *val++ = NICGet(NIC_DATAPORT);
    }

    return t.Val;
}

void MACReserveTxBuffer(BUFFER buffer)
{
    TxBuffers[buffer].bFree = FALSE;
}

void MACDiscardTx(BUFFER buffer)
{
    TxBuffers[buffer].bFree = TRUE;
    NICCurrentTxBuffer = buffer;
}

void MACDiscardRx(void)
{
    BYTE newBoundary;

    newBoundary = NICReadPtr - 1;

    if ( newBoundary < RXSTART ) newBoundary = RXSTOP - 1;

    NICPut(CMDR, 0x20);            // Select PAGE 0
    NICPut(BNRY, newBoundary);

    return;
}

WORD MACGetFreeRxSize(void)
{
    BYTE NICWritePtr, temp;
    WORD_VAL tempVal;

    NICPut(CMDR, 0x60);
    NICWritePtr = NICGet(CURRP);
    NICPut(CMDR, 0x20);

    if ( NICWritePtr < NICCurrentRdPtr )
        temp = (RXSTOP - NICCurrentRdPtr) + NICWritePtr;
    else
        temp = NICWritePtr - NICCurrentRdPtr;

    temp = RXPAGES - temp;
    tempVal.v[1] = temp;
    tempVal.v[0] = 0;

    return tempVal.Val;
}

BOOL MACIsLinked(void)
{
    BYTE_VAL temp;

    NICPut(CMDR, 0xe0);            // Select Page 3
    temp.Val = NICGet(0x03);       // Read CONFIG0.
    NICPut(CMDR, 0x20);            // Reset to page 0.

    // Bit 2 "BNC" will be '0' if LINK is established.
    return (temp.bits.b2 == 0);
}

BOOL MACGetHeader(MAC_ADDR *remote, BYTE* type)
{
    NE_PREAMBLE header;
    BYTE NICWritePtr;
    WORD_VAL temp;

    *type = MAC_UNKNOWN;

    // Reset NIC if overrun has occured.
    if ( NICGet(ISR) & 0x10 )
    {
#if 1
        NICPut(CMDR, 0x21);
        {
            BYTE i;

            for(i = 0; i < 10; i++)
            {
                DelayMs(20);
            }
        }
        NICPut(RBCR0, 0);
        NICPut(RBCR1, 0);
        NICPut(TCR, 0x02);
        NICPut(CMDR, 0x20);
        MACDiscardRx();
        NICPut(ISR, 0xff);
        NICPut(TCR, 0x00);

        return FALSE;
#else
        MACInit();

        return FALSE;
#endif
    }

    NICPut(CMDR, 0x60);
    NICWritePtr = NICGet(CURRP);
    NICPut(CMDR, 0x20);

    if ( NICWritePtr != NICReadPtr )
    {
        temp.v[1] = NICReadPtr;
        temp.v[0] = 0;
        NICSetAddr(temp.Val);

        MACGetArray((BYTE*)&header, sizeof(header));

        // Validate packet length and status.
        if ( header.Status.PRX && (header.ReceivedBytes >= MINFRAMEC) && (header.ReceivedBytes <= MAXFRAMEC) )
        {
            header.Type.Val = swaps(header.Type.Val);
            memcpy((void*)remote->v, (void*)header.SourceMACAddr.v, sizeof(*remote));

            if ( (header.Type.v[1] == 0x08) && ((header.Type.v[0] == ETHER_IP) || (header.Type.v[0] == ETHER_ARP)) )
                *type = header.Type.v[0];
        }

        NICCurrentRdPtr = NICReadPtr;
        NICReadPtr = header.NextPacketPointer;

        return TRUE;
    }
    return FALSE;
}

void MACPutHeader(MAC_ADDR *remote, BYTE type, WORD dataLen)
{
    WORD_VAL mytemp;
    BYTE etherType;

    NICPut(ISR, 0x0a);
    mytemp.v[1] = TxBuffers[NICCurrentTxBuffer].Index;
    mytemp.v[0] = 0;
    NICSetAddr(mytemp.Val);
    MACPutArray((BYTE*)remote, sizeof(*remote));
    MACPut(AppConfig.MyMACAddr.v[0]);
    MACPut(AppConfig.MyMACAddr.v[1]);
    MACPut(AppConfig.MyMACAddr.v[2]);
    MACPut(AppConfig.MyMACAddr.v[3]);
    MACPut(AppConfig.MyMACAddr.v[4]);
    MACPut(AppConfig.MyMACAddr.v[5]);

    if ( type == MAC_IP )
        etherType = ETHER_IP;
    else
        etherType = ETHER_ARP;

    MACPut(0x08);
    MACPut(etherType);
    dataLen += (WORD)sizeof(ETHER_HEADER);

    if ( dataLen < MINFRAME ) dataLen = 64;

    mytemp.Val = dataLen;
    NICPut(TBCR0, mytemp.v[0]);
    NICPut(TBCR1, mytemp.v[1]);
}

void MACFlush(void)
{
    BYTE i;

    NICPut(TPSR, TxBuffers[NICCurrentTxBuffer].Index);
    NICPut(CMDR, 0x24);

    // After every transmission, adjust transmit pointer to
    // next free transmit buffer.
    for ( i = 0; i < MAX_DATA_BUFFERS; i++ )
    {
        if ( TxBuffers[i].bFree )
        {
            NICCurrentTxBuffer = i;

            return;
        }
    }
}

#endif  // USE_RTL8019AS
