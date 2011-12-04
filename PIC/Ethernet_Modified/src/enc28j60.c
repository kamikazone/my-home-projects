
#define THIS_IS_MAC_LAYER
#include "minipic10t.h"
#include <string.h>

#include <delays.h>
#include "mac.h"
#include "enc28j60.h"

#define MAC_TX_BUFFER_SIZE   (576)
#define MAC_TX_BUFFER_COUNT  (MAX_SOCKETS+1)
#define MAX_SOCKETS          (6u)

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
// A generic structure representing the Ethernet header starting all
//  Ethernet frames

typedef struct _ETHER_HEADER
{
    MAC_ADDR DestMACAddr;
    MAC_ADDR SourceMACAddr;
    WORD_VAL Type;
} ETHER_HEADER;

// A header appended at the start of all RX frames by the hardware

typedef struct _ENC_PREAMBLE
{
    WORD NextPacketPointer;
    RXSTATUS StatusVector;
    MAC_ADDR DestMACAddr;
    MAC_ADDR SourceMACAddr;
    WORD_VAL Type;
} ENC_PREAMBLE;

typedef struct _DATA_BUFFER
{
    WORD_VAL StartAddress;
    WORD_VAL EndAddress;

    struct
    {
        unsigned char bFree : 1;
        unsigned char bTransmitted : 1;
    } Flags;
} DATA_BUFFER;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
// NIC RAM definitions
#define RAMSIZE  8192ul        
#define TXSTART  (RAMSIZE-(MAC_TX_BUFFER_COUNT * (MAC_TX_BUFFER_SIZE + 8ul)))
#define RXSTART  (0ul)                        // Should be an even memory address
#define RXSTOP   ((TXSTART-2ul) | 0x0001ul)   // Odd for errata workaround
#define RXSIZE   (RXSTOP-RXSTART+1ul)

// ENC28J60 Opcodes (to be ORed with a 5 bit address)
#define WCR (0b010<<5)             // Write Control Register command
#define BFS (0b100<<5)             // Bit Field Set command
#define BFC (0b101<<5)             // Bit Field Clear command
#define RCR (0b000<<5)             // Read Control Register command
#define RBM ((0b001<<5) | 0x1A)    // Read Buffer Memory command
#define WBM ((0b011<<5) | 0x1A)    // Write Buffer Memory command
#define SR  ((0b111<<5) | 0x1F)    // System Reset command

#define ETHER_IP  (0x00u)
#define ETHER_ARP (0x06u)

#define MAXFRAMEC (1500u+sizeof(ETHER_HEADER)+4u)


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
#if MAC_TX_BUFFER_COUNT > 1
static DATA_BUFFER TxBuffers[MAC_TX_BUFFER_COUNT];
#endif

BUFFER CurrentTxBuffer, LastTXedBuffer;
WORD_VAL NextPacketLocation, CurrentPacketLocation;
BOOL WasDiscarded;
BYTE ENCRevID;


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#define LOW(a)  (a & 0xFF)
#define HIGH(a) ((a>>8) & 0xFF)


/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/
#define Delay10us(us) Delay10TCYx(((TCY_CLOCK/1000000)*us))

void DelayMs(unsigned int ms)
{
    unsigned char i;

    while (ms--)
    {
        i = 4;

        while (i--)
        {
            Delay10us(25);
        }
    }
}

/******************************************************************************
 * Function:        REG ReadMACReg(BYTE Address)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 *                  Bank select bits must be set corresponding to the register
 *                  to read from.
 * Input:           5 bit address of the MAC or MII register to read from.
 *                  The top 3 bits must be 0.
 * Output:          Byte read from the Ethernet controller's MAC/MII register.
 * Side Effects:    None
 * Overview:        ReadMACReg sends the 8 bit RCR opcode/Address byte as well
 *                  as a dummy byte over the SPI and then retrives the
 *                  register contents in the last 8 SPI clocks.
 * Note:            This routine cannot be used to access ETH or PHY
 *                  registers.  Use ReadETHReg() or ReadPHYReg() for that
 *                  purpose.
 ******************************************************************************/
static REG ReadMACReg(BYTE Address)
{
    REG r;

#if defined(ENC_SAVE_SPI_CFG)    // If SPI is shared save config
#if defined(__18CXX)
    BYTE SPICONSave;
#else
    WORD SPICONSave;
#endif

    SPICONSave = ENC_SPICON1;
    ENC_SPIEN = 0;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPIEN = 1;
#endif

    ENC_CS_IO = 0;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = RCR | Address; // Send the Read Control Register opcode and
    // address.

    while (!ENC_SPI_IF);

    r.Val = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = 0; // Send a dummy byte

    while (!ENC_SPI_IF);

    r.Val = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = 0; // Send another dummy byte to receive the register
    // contents.
    while (!ENC_SPI_IF);

    r.Val = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_CS_IO = 1;

#if defined(ENC_SAVE_SPI_CFG)
    ENC_SPIEN = 0;
    ENC_SPICON1 = SPICONSave;
    ENC_SPIEN = 1;
#endif

    return r;
}

/******************************************************************************
 * Function:        REG ReadETHReg(BYTE Address)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 *                  Bank select bits must be set corresponding to the register
 *                  to read from.
 * Input:           5 bit address of the ETH control register to read from.
 *                  The top 3 bits must be 0.
 * Output:          Byte read from the Ethernet controller's ETH register.
 * Side Effects:    None
 * Overview:        ReadETHReg sends the 8 bit RCR opcode/Address byte over
 *                  the SPI and then retrives the register contents in the
 *                  next 8 SPI clocks.
 * Note:            This routine cannot be used to access MAC/MII or PHY
 *                  registers.  Use ReadMACReg() or ReadPHYReg() for that
 *                  purpose.
 *****************************************************************************/
REG ReadETHReg(BYTE Address)
{
    REG r;

#if defined(ENC_SAVE_SPI_CFG)    // If SPI is shared save config
#if defined(__18CXX)
    BYTE SPICONSave;
#else
    WORD SPICONSave;
#endif

    SPICONSave = ENC_SPICON1;
    ENC_SPIEN = 0;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPIEN = 1;
#endif

    // Select the chip and send the Read Control Register opcode/address
    ENC_CS_IO = 0;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = RCR | Address;

    while (!ENC_SPI_IF);

    r.Val = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = 0; // Send a dummy byte to receive the register
    // contents
    while (!ENC_SPI_IF);

    r.Val = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_CS_IO = 1;

#if defined(ENC_SAVE_SPI_CFG)
    ENC_SPIEN = 0;
    ENC_SPICON1 = SPICONSave;
    ENC_SPIEN = 1;
#endif

    return r;
}

/******************************************************************************
 * Function:        void WriteReg(BYTE Address, BYTE Data)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 *                  Bank select bits must be set corresponding to the register
 *                  to modify.
 * Input:           5 bit address of the ETH, MAC, or MII register to modify.
 *                  The top 3 bits must be 0.
 *                  Byte to be written into the register.
 * Output:          None
 * Side Effects:    None
 * Overview:        WriteReg sends the 8 bit WCR opcode/Address byte over the
 *                  SPI and then sends the data to write in the next 8 SPI
 *                  clocks.
 * Note:            This routine is almost identical to the BFCReg() and
 *                  BFSReg() functions.  It is seperate to maximize speed.
 *                  Unlike the ReadETHReg/ReadMACReg functions, WriteReg()
 *                  can write to any ETH or MAC register.  Writing to PHY
 *                  registers must be accomplished with WritePHYReg().
 *****************************************************************************/
void WriteReg(BYTE Address, BYTE Data)
{
    BYTE Dummy;

#if defined(ENC_SAVE_SPI_CFG)    // If SPI is shared save config
#if defined(__18CXX)
    BYTE SPICONSave;
#else
    WORD SPICONSave;
#endif

    SPICONSave = ENC_SPICON1;
    ENC_SPIEN = 0;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPIEN = 1;
#endif

    ENC_CS_IO = 0;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = WCR | Address; // Send the opcode and address

    while (!ENC_SPI_IF);

    Dummy = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = Data; // Send the byte to be writen

    while (!ENC_SPI_IF);

    Dummy = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_CS_IO = 1;

#if defined(ENC_SAVE_SPI_CFG)
    ENC_SPIEN = 0;
    ENC_SPICON1 = SPICONSave;
    ENC_SPIEN = 1;
#endif
}

/******************************************************************************
 * Function:        void BFSReg(BYTE Address, BYTE Data)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 *                  Bank select bits must be set corresponding to the register
 *                  to modify.
 * Input:           5 bit address of the register to modify.  The top 3 bits
 *                  must be 0.  
 *                  Byte to be used with the Bit Field Set operation.
 * Output:          None
 * Side Effects:    None
 * Overview:        BFSReg sends the 8 bit BFC opcode/Address byte over the
 *                  SPI and then sends the data in the next 8 SPI clocks.
 * Note:            This routine is almost identical to the WriteReg() and
 *                  BFCReg() functions.  It is separate to maximize speed.
 *                  BFSReg() must only be used on ETH registers.
 *****************************************************************************/
void BFSReg(BYTE Address, BYTE Data)
{
    BYTE Dummy;

#if defined(ENC_SAVE_SPI_CFG)    // If SPI is shared save config
#if defined(__18CXX)
    BYTE SPICONSave;
#else
    WORD SPICONSave;
#endif

    SPICONSave = ENC_SPICON1;
    ENC_SPIEN = 0;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPIEN = 1;
#endif

    ENC_CS_IO = 0;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = BFS | Address; // Send the opcode and address

    while (!ENC_SPI_IF);

    Dummy = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = Data; // Send the byte to be writen

    while (!ENC_SPI_IF);

    Dummy = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_CS_IO = 1;

#if defined(ENC_SAVE_SPI_CFG)
    ENC_SPIEN = 0;
    ENC_SPICON1 = SPICONSave;
    ENC_SPIEN = 1;
#endif
}

/******************************************************************************
 * Function:        void BFCReg(BYTE Address, BYTE Data)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 *                  Bank select bits must be set corresponding to the register
 *                  to modify.
 * Input:           5 bit address of the register to modify.  The top 3 bits
 *                  must be 0.  
 *                  Byte to be used with the Bit Field Clear operation.
 * Output:          None
 * Side Effects:    None
 * Overview:        BFCReg sends the 8 bit BFC opcode/Address byte over the
 *                  SPI and then sends the data in the next 8 SPI clocks.
 * Note:            This routine is almost identical to the WriteReg() and
 *                  BFSReg() functions.  It is separate to maximize speed.
 *                  BFCReg() must only be used on ETH registers.
 *****************************************************************************/
static void BFCReg(BYTE Address, BYTE Data)
{
    BYTE Dummy;

#if defined(ENC_SAVE_SPI_CFG)    // If SPI is shared save config
#if defined(__18CXX)
    BYTE SPICONSave;
#else
    WORD SPICONSave;
#endif

    SPICONSave = ENC_SPICON1;
    ENC_SPIEN = 0;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPIEN = 1;
#endif

    ENC_CS_IO = 0;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = BFC | Address; // Send the opcode and address

    while (!ENC_SPI_IF);

    Dummy = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = Data; // Send the byte to be writen

    while (!ENC_SPI_IF);

    Dummy = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_CS_IO = 1;

#if defined(ENC_SAVE_SPI_CFG)
    ENC_SPIEN = 0;
    ENC_SPICON1 = SPICONSave;
    ENC_SPIEN = 1;
#endif
}

/******************************************************************************
 * Function:        BankSel
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * Input:           Register address with the high byte containing the 2 bank
 *                  select 2 bits.
 * Output:          None
 * Side Effects:    None
 * Overview:        BankSel takes the high byte of a register address and
 *                  changes the bank select bits in ETHCON1 to match.
 * Note:            None
 *****************************************************************************/
void BankSel(WORD Register)
{
    BFCReg(ECON1, ECON1_BSEL1 | ECON1_BSEL0);
    BFSReg(ECON1, ((WORD_VAL*) & Register)->v[1]);
}

/******************************************************************************
 * Function:        ReadPHYReg
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * Input:           Address of the PHY register to read from.
 * Output:          16 bits of data read from the PHY register.
 * Side Effects:    Alters bank bits to point to Bank 2
 * Overview:        ReadPHYReg performs an MII read operation.  While in
 *                  progress, it simply polls the MII BUSY bit wasting time
 *                  (10.24us).
 * Note:            None
 *****************************************************************************/
PHYREG ReadPHYReg(BYTE Register)
{
    PHYREG Result;

    // Set the right address and start the register read operation
    BankSel(MIREGADR);
    WriteReg((BYTE) MIREGADR, Register);
    WriteReg((BYTE) MICMD, MICMD_MIIRD);

    // Loop to wait until the PHY register has been read through the MII
    // This requires 10.24us
    BankSel(MISTAT);

    while (ReadMACReg((BYTE) MISTAT).MISTATbits.BUSY);

    // Stop reading
    BankSel(MIREGADR);
    WriteReg((BYTE) MICMD, 0x00);

    // Obtain results and return
    Result.VAL.v[0] = ReadMACReg((BYTE) MIRDL).Val;
    Result.VAL.v[1] = ReadMACReg((BYTE) MIRDH).Val;

    return Result;
}

/******************************************************************************
 * Function:        WritePHYReg
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * Input:           Address of the PHY register to write to.
 *                  16 bits of data to write to PHY register.
 * Output:          None
 * Side Effects:    Alters bank bits to point to Bank 3
 * Overview:        WritePHYReg performs an MII write operation.  While in
 *                  progress, it simply polls the MII BUSY bit wasting time.
 * Note:            None
 *****************************************************************************/
void WritePHYReg(BYTE Register, WORD Data)
{
    // Write the register address
    BankSel(MIREGADR);
    WriteReg((BYTE) MIREGADR, Register);

    // Write the data
    // Order is important: write low byte first, high byte last
    WriteReg((BYTE) MIWRL, ((WORD_VAL*) & Data)->v[0]);
    WriteReg((BYTE) MIWRH, ((WORD_VAL*) & Data)->v[1]);

    // Wait until the PHY register has been written
    BankSel(MISTAT);

    while (ReadMACReg((BYTE) MISTAT).MISTATbits.BUSY);
}

/******************************************************************************
 * Function:        BYTE MACGet()
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 *                  ERDPT must point to the place to read from.
 * Input:           None
 * Output:          Byte read from the ENC28J60's RAM
 * Side Effects:    None
 * Overview:        MACGet returns the byte pointed to by ERDPT and
 *                  increments ERDPT so MACGet() can be called again. The
 *                  increment will follow the receive buffer wrapping boundary.
 * Note:            None
 *****************************************************************************/
BYTE MACGet()
{
    BYTE Result;

#if defined(ENC_SAVE_SPI_CFG)    // If SPI is shared save config
#if defined(__18CXX)
    BYTE SPICONSave;
#else
    WORD SPICONSave;
#endif

    SPICONSave = ENC_SPICON1;
    ENC_SPIEN = 0;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPIEN = 1;
#endif

    ENC_CS_IO = 0;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = RBM;

    while (!ENC_SPI_IF);

    Result = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = 0; // Send a dummy byte to receive the register
    // contents.
    while (!ENC_SPI_IF);

    Result = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_CS_IO = 1;

#if defined(ENC_SAVE_SPI_CFG)
    ENC_SPIEN = 0;
    ENC_SPICON1 = SPICONSave;
    ENC_SPIEN = 1;
#endif

    return Result;
}

/******************************************************************************
 * Function:        WORD MACGetArray(BYTE *val, WORD len)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 *                  ERDPT must point to the place to read from.
 * Input:           *val: Pointer to storage location
 *                   len:  Number of bytes to read from the data buffer.
 * Output:          Byte(s) of data read from the data buffer.
 * Side Effects:    None
 * Overview:        Burst reads several sequential bytes from the data buffer
 *                  and places them into local memory.  With SPI burst support,
 *                  it performs much faster than multiple MACGet() calls.
 *                  ERDPT is incremented after each byte, following the same
 *                  rules as MACGet().
 * Note:            None
 *****************************************************************************/
WORD MACGetArray(BYTE *val, WORD len)
{
    WORD i;
    BYTE Dummy;

#if defined(ENC_SAVE_SPI_CFG)    // If SPI is shared save config
#if defined(__18CXX)
    BYTE SPICONSave;
#else
    WORD SPICONSave;
#endif

    SPICONSave = ENC_SPICON1;
    ENC_SPIEN = 0;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPIEN = 1;
#endif

    // Start the burst operation
    ENC_CS_IO = 0;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = RBM; // Send the Read Buffer Memory opcode.
    i = 0;
    val--;

    while (!ENC_SPI_IF);

    Dummy = ENC_SSPBUF;
    ENC_SPI_IF = 0;

    // Read the data
    while (i < len)
    {
        ENC_SSPBUF = 0; // Send a dummy byte to receive a byte
        i++;
        val++;

        while (!ENC_SPI_IF);

        *val = ENC_SSPBUF;
        ENC_SPI_IF = 0;
    };

    // Terminate the burst operation
    ENC_CS_IO = 1;

#if defined(ENC_SAVE_SPI_CFG)
    ENC_SPIEN = 0;
    ENC_SPICON1 = SPICONSave;
    ENC_SPIEN = 1;
#endif

    return i;
}

/******************************************************************************
 * Function:        void MACPut(BYTE val)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 *                  EWRPT must point to the location to begin writing.
 * Input:           Byte to write into the ENC28J60 buffer memory
 * Output:          None
 * Side Effects:    None
 * Overview:        MACPut outputs the Write Buffer Memory opcode/constant
 *                  (8 bits) and data to write (8 bits) over the SPI.
 *                  EWRPT is incremented after the write.
 * Note:            None
 *****************************************************************************/
void MACPut(BYTE val)
{
    BYTE Dummy;

#if defined(ENC_SAVE_SPI_CFG)    // If SPI is shared save config
#if defined(__18CXX)
    BYTE SPICONSave;
#else
    WORD SPICONSave;
#endif

    SPICONSave = ENC_SPICON1;
    ENC_SPIEN = 0;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPIEN = 1;
#endif

    ENC_CS_IO = 0;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = WBM; // Send the opcode and constant

    while (!ENC_SPI_IF);

    Dummy = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = val;

    while (!ENC_SPI_IF);

    Dummy = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_CS_IO = 1;

#if defined(ENC_SAVE_SPI_CFG)
    ENC_SPIEN = 0;
    ENC_SPICON1 = SPICONSave;
    ENC_SPIEN = 1;
#endif
}

/******************************************************************************
 * Function:        void MACPutArray(BYTE *val, WORD len)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 *                  EWRPT must point to the location to begin writing.
 * Input:           *val: Pointer to source of bytes to copy.
 *                  len:  Number of bytes to write to the data buffer.
 * Output:          None
 * Side Effects:    None
 * Overview:        MACPutArray writes several sequential bytes to the
 *                  ENC28J60 RAM.  It performs faster than multiple MACPut()
 *                  calls.  EWRPT is incremented by len.
 * Note:            None
 *****************************************************************************/
void MACPutArray(BYTE *val, WORD len)
{
    BYTE Dummy;

#if defined(ENC_SAVE_SPI_CFG)    // If SPI is shared save config
#if defined(__18CXX)
    BYTE SPICONSave;
#else
    WORD SPICONSave;
#endif

    SPICONSave = ENC_SPICON1;
    ENC_SPIEN = 0;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPIEN = 1;
#endif

    // Select the chip and send the proper opcode
    ENC_CS_IO = 0;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = WBM; // Send the Write Buffer Memory opcode

    while (!ENC_SPI_IF);

    Dummy = ENC_SSPBUF;
    ENC_SPI_IF = 0;

    // Send the data
    while (len)
    {
        ENC_SSPBUF = *val; // Start sending the byte
        val++; // Increment after writing to ENC_SSPBUF to increase speed
        len--; // Decrement after writing to ENC_SSPBUF to increase speed

        while (!ENC_SPI_IF);

        Dummy = ENC_SSPBUF;
        ENC_SPI_IF = 0;
    };

    // Terminate the burst operation
    ENC_CS_IO = 1;

#if defined(ENC_SAVE_SPI_CFG)
    ENC_SPIEN = 0;
    ENC_SPICON1 = SPICONSave;
    ENC_SPIEN = 1;
#endif
}

/******************************************************************************
 * Function:        BOOL MACIsLinked(void)
 * PreCondition:    None
 * Input:           None
 * Output:          TRUE: If the PHY reports that a link partner is present 
 *                        and the link has been up continuously since the last 
 *                        call to MACIsLinked()
 *                  FALSE: If the PHY reports no link partner, or the link went
 *                         down momentarily since the last call to MACIsLinked()
 * Side Effects:    None
 * Overview:        Returns the PHSTAT1.LLSTAT bit.
 * Note:            None
 *****************************************************************************/
BOOL MACIsLinked(void)
{
    // LLSTAT is a latching low link status bit.  Therefore, if the link 
    // goes down and comes back up before a higher level stack program calls
    // MACIsLinked(), MACIsLinked() will still return FALSE.  The next 
    // call to MACIsLinked() will return TRUE (unless the link goes down
    // again).
    return ReadPHYReg(PHSTAT1).PHSTAT1bits.LLSTAT;
}

/******************************************************************************
 * Function:        BOOL MACIsTxReady(BOOL HighPriority)
 * PreCondition:    None
 * Input:           HighPriority: TRUE: Check the hardware ECON1.TXRTS bit
 *                                FALSE: Check if a TX buffer is free
 * Output:          TRUE: If no Ethernet transmission is in progress
 *                  FALSE: If a previous transmission was started, and it has
 *                         not completed yet.  While FALSE, the data in the
 *                         transmit buffer and the TXST/TXND pointers must not
 *                         be changed.
 * Side Effects:    None
 * Overview:        Returns the ECON1.TXRTS bit
 * Note:            None
 *****************************************************************************/
BOOL MACIsTxReady(BOOL HighPriority)
{
#if MAC_TX_BUFFER_COUNT > 1
    BUFFER i;

    if (HighPriority)
#endif
    {
        return !ReadETHReg(ECON1).ECON1bits.TXRTS;
    }

#if MAC_TX_BUFFER_COUNT > 1
    // Check if the current buffer can be modified.  It cannot be modified if
    // the TX hardware is currently transmitting it.
    if (CurrentTxBuffer == LastTXedBuffer)
    {
        return !ReadETHReg(ECON1).ECON1bits.TXRTS;
    }

    // Check if a buffer is available for a new packet
    for (i = 1; i < MAC_TX_BUFFER_COUNT; i++)
    {
        if (TxBuffers[i].Flags.bFree)
        {
            return TRUE;
        }
    }
    return FALSE;
#endif
}

BUFFER MACGetTxBuffer(BOOL HighPriority)
{
#if MAC_TX_BUFFER_COUNT > 1
    BUFFER i;

    if (HighPriority)
#endif
    {
        return !ReadETHReg(ECON1).ECON1bits.TXRTS ? 0 : INVALID_BUFFER;
    }

#if MAC_TX_BUFFER_COUNT > 1
    // Find a free buffer.  Do not use buffer 0, it is reserved for
    // high priority messages that don't need to be acknowledged
    // before being discarded (TCP control packets, all ICMP 
    // packets, all UDP packets, etc.)
    for (i = 1; i < MAC_TX_BUFFER_COUNT; i++)
    {
        // If this buffer is free, then mark it as used and return with it
        if (TxBuffers[i].Flags.bFree)
        {
            TxBuffers[i].Flags.bFree = FALSE;
            TxBuffers[i].Flags.bTransmitted = FALSE;
            return i;
        }
    }
    return INVALID_BUFFER;
#endif
}

/******************************************************************************
 * Function:        void MACSetTxBuffer(BUFFER buffer, WORD offset)
 * PreCondition:    None
 * Input:           buffer: BYTE specifying which transmit buffer to seek
 *                          within.  If MAC_TX_BUFFER_COUNT <= 1, this
 *                          parameter is not used.
 *                  offset: WORD specifying how many bytes beyond the Ethernet
 *                          header's type field to relocate the SPI read and
 *                          write pointers.
 * Output:          None
 * Side Effects:    None
 * Overview:        SPI read and write pointers are updated.  All calls to
 *                  MACGet(), MACPut(), MACGetArray(), and MACPutArray(),
 *                  and various other functions will use these new values.
 * Note:            None
 *****************************************************************************/
void MACSetTxBuffer(BUFFER buffer, WORD offset)
{
    CurrentTxBuffer = buffer;

    // Calculate the proper address.  Since the TX memory area is not circular,
    // no wrapparound checks are necessary. +1 adjustment is needed because of
    // the per packet control byte which preceeds the packet in the TX memory
    // area.
#if MAC_TX_BUFFER_COUNT > 1
    offset += TxBuffers[buffer].StartAddress.Val + 1 + sizeof (ETHER_HEADER);
#else
    offset += TXSTART + 1 + sizeof (ETHER_HEADER);
#endif

    // Set the SPI read and write pointers to the new calculated value
    BankSel(EWRPTL);
    WriteReg(ERDPTL, ((WORD_VAL*) & offset)->v[0]);
    WriteReg(ERDPTH, ((WORD_VAL*) & offset)->v[1]);
    WriteReg(EWRPTL, ((WORD_VAL*) & offset)->v[0]);
    WriteReg(EWRPTH, ((WORD_VAL*) & offset)->v[1]);
}
void MACSetTxBuffer1()
{
	WORD offset;
    //CurrentTxBuffer = buffer;
    offset = 23889;	// 1 + sizeof (ETHER_HEADER) + sizeof (IP_HEADER);
    // Set the SPI read and write pointers to the new calculated value
    BankSel(EWRPTL);
    WriteReg(ERDPTL, ((WORD_VAL*) & offset)->v[0]);
    WriteReg(ERDPTH, ((WORD_VAL*) & offset)->v[1]);
    WriteReg(EWRPTL, ((WORD_VAL*) & offset)->v[0]);
    WriteReg(EWRPTH, ((WORD_VAL*) & offset)->v[1]);
}
void MACDiscardTx(BUFFER buffer)
{
#if MAC_TX_BUFFER_COUNT > 1
    if (buffer < sizeof (TxBuffers) / sizeof (TxBuffers[0]))
    {
        TxBuffers[buffer].Flags.bFree = TRUE;
        CurrentTxBuffer = buffer;
    }
#endif
}

/******************************************************************************
 * Function:        void MACSetRxBuffer(WORD offset)
 * PreCondition:    A packet has been obtained by calling MACGetHeader() and
 *                  getting a TRUE result.
 * Input:           offset: WORD specifying how many bytes beyond the Ethernet
 *                          header's type field to relocate the SPI read and
 *                          write pointers.
 * Output:          None
 * Side Effects:    None
 * Overview:        SPI read and write pointers are updated.  All calls to
 *                  MACGet(), MACPut(), MACGetArray(), and MACPutArray(),
 *                  and various other functions will use these new values.
 * Note:            RXSTOP must be statically defined as being > RXSTART for
 *                  this function to work correctly.  In other words, do not
 *                  define an RX buffer which spans the 0x1FFF->0x0000 memory
 *                  boundary.
 *****************************************************************************/
void MACSetRxBuffer(WORD offset)
{
    WORD_VAL ReadPT;

    // Determine the address of the beginning of the entire packet
    // and adjust the address to the desired location
    ReadPT.Val = CurrentPacketLocation.Val + sizeof (ENC_PREAMBLE) + offset;

    // Since the receive buffer is circular, adjust if a wraparound is needed
    if (ReadPT.Val > RXSTOP) ReadPT.Val -= RXSIZE;

    // Set the SPI read and write pointers to the new calculated value
    BankSel(ERDPTL);
    WriteReg(ERDPTL, ReadPT.v[0]);
    WriteReg(ERDPTH, ReadPT.v[1]);
    WriteReg(EWRPTL, ReadPT.v[0]);
    WriteReg(EWRPTH, ReadPT.v[1]);
}

/******************************************************************************
 * Function:        WORD MACGetFreeRxSize(void)
 * PreCondition:    None
 * Input:           None
 * Output:          A WORD estimate of how much RX buffer space is free at
 *                  the present time.
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 *****************************************************************************/
WORD MACGetFreeRxSize(void)
{
    WORD_VAL ReadPT, WritePT;

    // Read the Ethernet hardware buffer write pointer.  Because packets can be
    // received at any time, it can change between reading the low and high
    // bytes.  A loop is necessary to make certain a proper low/high byte pair
    // is read.
    BankSel(EPKTCNT);
    do
    {
        // Save EPKTCNT in a temporary location
        ReadPT.v[0] = ReadETHReg((BYTE) EPKTCNT).Val;
        BankSel(ERXWRPTL);
        WritePT.v[0] = ReadETHReg(ERXWRPTL).Val;
        WritePT.v[1] = ReadETHReg(ERXWRPTH).Val;
        BankSel(EPKTCNT);
    }
    while (ReadETHReg((BYTE) EPKTCNT).Val != ReadPT.v[0]);

    // Determine where the write protection pointer is
    BankSel(ERXRDPTL);
    ReadPT.v[0] = ReadETHReg(ERXRDPTL).Val;
    ReadPT.v[1] = ReadETHReg(ERXRDPTH).Val;

    // Calculate the difference between the pointers, taking care to account
    // for buffer wrapping conditions
    if (WritePT.Val > ReadPT.Val)
    {
        return (RXSTOP - RXSTART) - (WritePT.Val - ReadPT.Val);
    }
    else if (WritePT.Val == ReadPT.Val)
    {
        return RXSIZE - 1;
    }
    else
    {
        return ReadPT.Val - WritePT.Val - 1;
    }
}

/******************************************************************************
 * Function:        void MACDiscardRx(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        Marks the last received packet (obtained using
 *                  MACGetHeader())as being processed and frees the buffer
 *                  memory associated with it
 * Note:            None
 *****************************************************************************/
void MACDiscardRx(void)
{
    WORD_VAL NewRXRDLocation;

    // Make sure the current packet was not already discarded
    if (WasDiscarded)
        return;

    WasDiscarded = TRUE;

    // Decrement the next packet pointer before writing it into
    // the ERXRDPT registers.  This is a silicon errata workaround.
    // RX buffer wrapping must be taken into account if the
    // NextPacketLocation is precisely RXSTART.
    NewRXRDLocation.Val = NextPacketLocation.Val - 1;

#if RXSTART == 0
    if (NewRXRDLocation.Val > RXSTOP)
#else
    if (NewRXRDLocation.Val < RXSTART || NewRXRDLocation.Val > RXSTOP)
#endif
    {
        NewRXRDLocation.Val = RXSTOP;
    }

    // Decrement the RX packet counter register, EPKTCNT
    BFSReg(ECON2, ECON2_PKTDEC);

    // Move the receive read pointer to unwrite-protect the memory used by the
    // last packet.  The writing order is important: set the low byte first,
    // high byte last.
    BankSel(ERXRDPTL);
    WriteReg(ERXRDPTL, NewRXRDLocation.v[0]);
    WriteReg(ERXRDPTH, NewRXRDLocation.v[1]);
}

/******************************************************************************
 * Function:        BOOL MACGetHeader(MAC_ADDR *remote, BYTE* type)
 * PreCondition:    None
 * Input:           *remote: Location to store the Source MAC address of the
 *                           received frame.
 *                  *type: Location of a BYTE to store the constant
 *                         MAC_UNKNOWN, ETHER_IP, or ETHER_ARP, representing
 *                         the contents of the Ethernet type field.
 * Output:          TRUE: If a packet was waiting in the RX buffer.  The
 *                        remote, and type values are updated.
 *                  FALSE: If a packet was not pending.  remote and type are
 *                         not changed.
 * Side Effects:    Last packet is discarded if MACDiscardRx() hasn't already
 *                  been called.
 * Overview:        None
 * Note:            None
 *****************************************************************************/
BOOL MACGetHeader(MAC_ADDR *remote, BYTE* type)
{
    ENC_PREAMBLE header;

    // Test if at least one packet has been received and is waiting
    BankSel(EPKTCNT);

    if (ReadETHReg((BYTE) EPKTCNT).Val == 0)
        return FALSE;

    // Make absolutely certain that any previous packet was discarded
    if (WasDiscarded == FALSE)
    {
        MACDiscardRx();
        return FALSE;
    }

    // Save the location of this packet
    CurrentPacketLocation.Val = NextPacketLocation.Val;

    // Set the SPI read pointer to the beginning of the next unprocessed packet
    BankSel(ERDPTL);
    WriteReg(ERDPTL, NextPacketLocation.v[0]);
    WriteReg(ERDPTH, NextPacketLocation.v[1]);

    // Obtain the MAC header from the Ethernet buffer
    MACGetArray((BYTE*) & header, sizeof (header));

    // The EtherType field, like most items transmitted on the Ethernet medium
    // are in big endian.
    header.Type.Val = swaps(header.Type.Val);

    // Validate the data returned from the ENC28J60.  Random data corruption, 
    // such as if a single SPI bit error occurs while communicating or a 
    // momentary power glitch could cause this to occur in rare circumstances.
    if (header.NextPacketPointer > RXSTOP || ((BYTE_VAL*) (&header.NextPacketPointer))->bits.b0 ||
            header.StatusVector.bits.Zero ||
            header.StatusVector.bits.CRCError ||
            header.StatusVector.bits.ByteCount > 1518 ||
            !header.StatusVector.bits.ReceiveOk)
    {
        Reset();
    }

    // Save the location where the hardware will write the next packet to
    NextPacketLocation.Val = header.NextPacketPointer;

    // Return the Ethernet frame's Source MAC address field to the caller
    // This parameter is useful for replying to requests without requiring an
    // ARP cycle.
    memcpy((void*) remote->v, (void*) header.SourceMACAddr.v, sizeof (*remote));

    // Return a simplified version of the EtherType field to the caller
    *type = MAC_UNKNOWN;

    if ((header.Type.v[1] == 0x08u) &&
            ((header.Type.v[0] == ETHER_IP) || (header.Type.v[0] == ETHER_ARP)))
    {
        *type = header.Type.v[0];
    }

    // Mark this packet as discardable
    WasDiscarded = FALSE;

    return TRUE;
}


/******************************************************************************
 * Function:        void MACFlush(void)
 * PreCondition:    A packet has been created by calling MACPut() and
 *                  MACPutHeader().
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        MACFlush causes the current TX packet to be sent out on
 *                  the Ethernet medium.  The hardware MAC will take control
 *                  and handle CRC generation, collision retransmission and
 *                  other details.
 * Note:            After transmission completes (MACIsTxReady() returns TRUE),
 *                  the packet can be modified and transmitted again by calling
 *                  MACFlush() again.  Until MACPutHeader() or MACPut() is
 *                  called (in the TX data area), the data in the TX buffer
 *                  will not be corrupted.
 *****************************************************************************/
void MACFlush(void)
{
#if MAC_TX_BUFFER_COUNT > 1
    // Set the packet start and end address pointers
    BankSel(ETXSTL);
    WriteReg(ETXSTL, TxBuffers[CurrentTxBuffer].StartAddress.v[0]);
    WriteReg(ETXSTH, TxBuffers[CurrentTxBuffer].StartAddress.v[1]);
    WriteReg(ETXNDL, TxBuffers[CurrentTxBuffer].EndAddress.v[0]);
    WriteReg(ETXNDH, TxBuffers[CurrentTxBuffer].EndAddress.v[1]);
    LastTXedBuffer = CurrentTxBuffer;
    TxBuffers[CurrentTxBuffer].Flags.bTransmitted = TRUE;
#endif

    // Reset transmit logic if a TX Error has previously occured
    // This is a silicon errata workaround
    if (ReadETHReg(EIR).EIRbits.TXERIF)
    {
        BFSReg(ECON1, ECON1_TXRST);
        BFCReg(ECON1, ECON1_TXRST);
    }
    BFCReg(EIR, EIR_TXERIF | EIR_TXIF);

    // Start the transmission
    // After transmission completes (MACIsTxReady() returns TRUE), the packet
    // can be modified and transmitted again by calling MACFlush() again.
    // Until MACPutHeader() is called, the data in the TX buffer will not be
    // corrupted.
    BFSReg(ECON1, ECON1_TXRTS);

    // Revision B5 silicon errata workaround
    if (ENCRevID == 0x05)
    {
        while (!(ReadETHReg(EIR).Val & (EIR_TXERIF | EIR_TXIF)));

        if (ReadETHReg(EIR).EIRbits.TXERIF)
        {
            WORD_VAL ReadPtrSave, TXEnd;
            TXSTATUS TXStatus;
            BYTE i;

            // Cancel the previous transmission if it has become stuck set
            BFCReg(ECON1, ECON1_TXRTS);

            // Save the current read pointer (controlled by application)
            BankSel(ERDPTL);
            ReadPtrSave.v[0] = ReadETHReg(ERDPTL).Val;
            ReadPtrSave.v[1] = ReadETHReg(ERDPTH).Val;

            // Get the location of the transmit status vector
            TXEnd.v[0] = ReadETHReg(ETXNDL).Val;
            TXEnd.v[1] = ReadETHReg(ETXNDH).Val;
            TXEnd.Val++;

            // Read the transmit status vector
            WriteReg(ERDPTL, TXEnd.v[0]);
            WriteReg(ERDPTH, TXEnd.v[1]);
            MACGetArray((BYTE*) & TXStatus, sizeof (TXStatus));

            // Implement retransmission if a late collision occured (this can
            // happen on B5 when certain link pulses arrive at the same time
            // as the transmission)
            for (i = 0; i < 16; i++)
            {
                if (ReadETHReg(EIR).EIRbits.TXERIF && TXStatus.bits.LateCollision)
                {
                    // Reset the TX logic
                    BFSReg(ECON1, ECON1_TXRST);
                    BFCReg(ECON1, ECON1_TXRST);
                    BFCReg(EIR, EIR_TXERIF | EIR_TXIF);

                    // Transmit the packet again
                    BFSReg(ECON1, ECON1_TXRTS);

                    while (!(ReadETHReg(EIR).Val & (EIR_TXERIF | EIR_TXIF)));

                    // Cancel the previous transmission if it has become stuck set
                    BFCReg(ECON1, ECON1_TXRTS);

                    // Read transmit status vector
                    WriteReg(ERDPTL, TXEnd.v[0]);
                    WriteReg(ERDPTH, TXEnd.v[1]);
                    MACGetArray((BYTE*) & TXStatus, sizeof (TXStatus));
                }
                else
                {
                    break;
                }
            }

            // Restore the current read pointer
            WriteReg(ERDPTL, ReadPtrSave.v[0]);
            WriteReg(ERDPTH, ReadPtrSave.v[1]);
        }
    }
}


/******************************************************************************
 * Function:        void MACPowerUp(void)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        MACPowerUp returns the ENC28J60 back to normal operation
 *                  after a previous call to MACPowerDown().  Calling this
 *                  function when already powered up will have no effect.
 * Note:            If a link partner is present, it will take 10s of
 *                  milliseconds before a new link will be established after
 *                  waking up.  While not linked, packets which are 
 *                  transmitted will most likely be lost.  MACIsLinked() can
 *                  be called to determine if a link is established.
 *****************************************************************************/
void MACPowerUp(void)
{
    // Leave power down mode
    BFCReg(ECON2, ECON2_PWRSV);

    // Wait for the 300us Oscillator Startup Timer (OST) to time out.  This
    // delay is required for the PHY module to return to an operational state.
    while (!ReadETHReg(ESTAT).ESTATbits.CLKRDY);

    // Enable packet reception
    BFSReg(ECON1, ECON1_RXEN);
}

/******************************************************************************
 * Function:        void MACPowerDown(void)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        MACPowerDown puts the ENC28J60 in low power sleep mode. In
 *                  sleep mode, no packets can be transmitted or received.
 *                  All MAC and PHY registers should not be accessed.
 * Note:            If a packet is being transmitted while this function is
 *                  called, this function will block until it is it complete.
 *                  If anything is being received, it will be completed.
 *****************************************************************************/
void MACPowerDown(void)
{
    // Disable packet reception
    BFCReg(ECON1, ECON1_RXEN);

    // Make sure any last packet which was in-progress when RXEN was cleared
    // is completed
    while (ReadETHReg(ESTAT).ESTATbits.RXBUSY);

    // If a packet is being transmitted, wait for it to finish
    while (ReadETHReg(ECON1).ECON1bits.TXRTS);

    // Enter sleep mode
    BFSReg(ECON2, ECON2_PWRSV);
}

/******************************************************************************
 * Function:        void MACSetDuplex(DUPLEX DuplexState) 
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * Input:           Member of DUPLEX enum:
 *                        FULL: Set full duplex mode
 *                        HALF: Set half duplex mode
 *                        USE_PHY: Set the MAC to match the PHYDPLXMODE bit in
 *                                 PHYCON.  This is controlled by LEDB on RESET.
 * Output:          None
 * Side Effects:    Changes bank bits to Bank 2.
 * Overview:        Disables RX, TX logic, sets MAC up for full duplex
 *                  operation, sets PHY up for full duplex operation, and
 *                  reenables RX logic.  The back-to-back inter-packet gap
 *                  register (MACBBIPG) is updated to maintain a 9.6us gap.
 * Note:            If a packet is being transmitted or received while this
 *                  function is called, it will be aborted.
 *****************************************************************************/
void MACSetDuplex(DUPLEX DuplexState)
{
    REG Register;
    PHYREG PhyReg;

    // Disable receive logic and abort any packets currently being transmitted
    BFCReg(ECON1, ECON1_TXRTS | ECON1_RXEN);

    // Set the PHY to the proper duplex mode
    PhyReg = ReadPHYReg(PHCON1);

    if (DuplexState == USE_PHY)
    {
        DuplexState = PhyReg.PHCON1bits.PDPXMD;
    }
    else
    {
        PhyReg.PHCON1bits.PDPXMD = DuplexState;
        WritePHYReg(PHCON1, PhyReg.Val);
    }

    // Set the MAC to the proper duplex mode
    BankSel(MACON3);
    Register = ReadMACReg((BYTE) MACON3);
    Register.MACON3bits.FULDPX = DuplexState;
    WriteReg((BYTE) MACON3, Register.Val);

    // Set the back-to-back inter-packet gap time to IEEE specified 
    // requirements.  The meaning of the MABBIPG value changes with the duplex
    // state, so it must be updated in this function.
    // In full duplex, 0x15 represents 9.6us; 0x12 is 9.6us in half duplex
    WriteReg((BYTE) MABBIPG, DuplexState ? 0x15 : 0x12);

    // Reenable receive logic
    BFSReg(ECON1, ECON1_RXEN);
} //end MACSetDuplex

/******************************************************************************
 * Function:        void SetCLKOUT(BYTE NewConfig)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * Input:           NewConfig - 0x00: CLKOUT disabled (pin driven low)
 *                              0x01: Divide by 1 (25 MHz)
 *                              0x02: Divide by 2 (12.5 MHz)
 *                              0x03: Divide by 3 (8.333333 MHz)
 *                              0x04: Divide by 4 (6.25 MHz, POR default)
 *                              0x05: Divide by 8 (3.125 MHz)
 * Output:          None
 * Side Effects:    None
 * Overview:        Writes the value of NewConfig into the ECOCON register.
 *                  The CLKOUT pin will beginning outputting the new frequency
 *                  immediately.
 * Note:            
 *****************************************************************************/
void SetCLKOUT(BYTE NewConfig)
{
    BankSel(ECOCON);
    WriteReg((BYTE) ECOCON, NewConfig);
    BankSel(ERDPTL);
}

/******************************************************************************
 * Function:        BYTE GetCLKOUT(void)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * Input:           None
 * Output:          BYTE - 0x00: CLKOUT disabled (pin driven low)
 *                         0x01: Divide by 1 (25 MHz)
 *                         0x02: Divide by 2 (12.5 MHz)
 *                         0x03: Divide by 3 (8.333333 MHz)
 *                         0x04: Divide by 4 (6.25 MHz, POR default)
 *                         0x05: Divide by 8 (3.125 MHz)
 *                         0x06: Reserved
 *                         0x07: Reserved
 * Side Effects:    None
 * Overview:        Returns the current value of the ECOCON register.
 * Note:            None
 *****************************************************************************/
BYTE GetCLKOUT(void)
{
    BYTE i;

    BankSel(ECOCON);
    i = ReadETHReg((BYTE) ECOCON).Val;
    BankSel(ERDPTL);
    return i;
}

/******************************************************************************
 * Function:        static void SendSystemReset(void)
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        SendSystemReset sends the System Reset SPI command to
 *                  the Ethernet controller.  It resets all register contents
 *                  (except for ECOCON) and returns the device to the power
 *                  on default state.
 * Note:            None
 *****************************************************************************/
void SendSystemReset(void)
{
    BYTE Dummy;

#if defined(ENC_SAVE_SPI_CFG)    // If SPI is shared save config
#if defined(__18CXX)
    BYTE SPICONSave;
#else
    WORD SPICONSave;
#endif

    SPICONSave = ENC_SPICON1;
    ENC_SPIEN = 0;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPIEN = 1;
#endif

    ENC_CS_IO = 0;
    ENC_SPI_IF = 0;
    ENC_SSPBUF = SR;

    while (!ENC_SPI_IF);

    Dummy = ENC_SSPBUF;
    ENC_SPI_IF = 0;
    ENC_CS_IO = 1;

#if defined(ENC_SAVE_SPI_CFG)
    ENC_SPIEN = 0;
    ENC_SPICON1 = SPICONSave;
    ENC_SPIEN = 1;
#endif

} //end SendSystemReset


