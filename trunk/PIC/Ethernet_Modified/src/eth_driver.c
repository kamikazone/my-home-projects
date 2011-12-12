
#include "eth_driver.h"


APP_CONFIG AppConfig = {
    DEFAULT_IP_ADDRESS, DEFAULT_MAC_ADDRESS, DEFAULT_NETMASK,
    DEFAULT_GATEWAY, DEFAULT_NS1,
    {0b00000001}, // Flags, enable DHCP
};

void MACInit1(void)
{
    BYTE i;
    ENC_SPI_IF = 0;
    // Wait for CLKRDY to become set.
    // Bit 3 in ESTAT is an unimplemented bit.  If it reads out as '1' that
    // means the part is in RESET or there is something wrong with the SPI
    // connection.  This loop makes sure that we can communicate with the
    // ENC28J60 before proceeding.
    do
    {
        i = ReadETHReg(ESTAT).Val;
    }
    while ((i & 0x08) || (~i & ESTAT_CLKRDY));
    // RESET the entire ENC28J60, clearing all registers
    SendSystemReset();
    DelayMs(1);
    // Enter Bank 2 and configure the MAC
    BankSel(MACON1);
    // Enable the receive portion of the MAC
    WriteReg((BYTE) MACON1, MACON1_TXPAUS | MACON1_RXPAUS | MACON1_MARXEN);
    // Pad packets to 60 bytes, add CRC, and check Type/Length field.
    WriteReg((BYTE) MACON3, MACON3_PADCFG0 | MACON3_TXCRCEN | MACON3_FRMLNEN);
    // Allow infinite deferals if the medium is continuously busy
    // (do not time out a transmission if the half duplex medium is
    // completely saturated with other people's data)
    WriteReg((BYTE) MACON4, MACON4_DEFER);
    // Late collisions occur beyond 63+8 bytes (8 bytes for preamble/start of frame delimiter)
    // 55 is all that is needed for IEEE 802.3, but ENC28J60 B5 errata for improper link pulse
    // collisions will occur less often with a larger number.
    WriteReg((BYTE) MACLCON2, 63);
    // Set non-back-to-back inter-packet gap to 9.6us.  The back-to-back
    // inter-packet gap (MABBIPG) is set by MACSetDuplex() which is called
    // later.
    WriteReg((BYTE) MAIPGL, 0x12);
    WriteReg((BYTE) MAIPGH, 0x0C);
    // Set the maximum packet size which the controller will accept
    WriteReg((BYTE) MAMXFLL, LOW(MAXFRAMEC));
    WriteReg((BYTE) MAMXFLH, HIGH(MAXFRAMEC));
    // Enter Bank 3 and initialize physical MAC address registers
    BankSel(MAADR1);
    WriteReg((BYTE) MAADR1, 0x00);
    WriteReg((BYTE) MAADR2, 0x04);
    WriteReg((BYTE) MAADR3, 0xa3);
    WriteReg((BYTE) MAADR4, 0x00);
    WriteReg((BYTE) MAADR5, 0x02);
    WriteReg((BYTE) MAADR6, 0x00);
    // Disable half duplex loopback in PHY.  Bank bits changed to Bank 2 as a
    // side effect.
    WritePHYReg(PHCON2, PHCON2_HDLDIS);
    // Configure LEDA to display LINK status, LEDB to display TX/RX activity
    SetLEDConfig(0x0472);
    // Set the MAC and PHY into the proper duplex state
    MACSetDuplex(HALF);
    // Enable packet reception
    BFSReg(ECON1, ECON1_RXEN);
}
void MACInit(void)
{
    BYTE i;
    ENC_SPI_IF = 0;
    // Wait for CLKRDY to become set.
    // Bit 3 in ESTAT is an unimplemented bit.  If it reads out as '1' that
    // means the part is in RESET or there is something wrong with the SPI
    // connection.  This loop makes sure that we can communicate with the
    // ENC28J60 before proceeding.
    do
    {
        i = ReadETHReg(ESTAT).Val;
    }
    while ((i & 0x08) || (~i & ESTAT_CLKRDY));
    // RESET the entire ENC28J60, clearing all registers
    SendSystemReset();
    DelayMs(1);
	
	WriteReg(ERXSTL, 0);
    WriteReg(ERXSTH, 0);
    WriteReg(ERXRDPTL, 0x07);     // Write low byte first
    WriteReg(ERXRDPTH, 0x10);    // Write high byte last
	// The RESET default ERXND is 0x1FFF
	WriteReg(ERXNDL, 0x07);
    WriteReg(ERXNDH, 0x10);
	// The RESET default ETXST is 0
	WriteReg(ETXSTL, 0x08);
    WriteReg(ETXSTH, 0x10);
	
    // Enter Bank 2 and configure the MAC
    BankSel(MACON1);
    // Enable the receive portion of the MAC
    WriteReg((BYTE) MACON1, MACON1_TXPAUS | MACON1_RXPAUS | MACON1_MARXEN);
    // Pad packets to 60 bytes, add CRC, and check Type/Length field.
    WriteReg((BYTE) MACON3, MACON3_PADCFG0 | MACON3_TXCRCEN | MACON3_FRMLNEN);
    // Allow infinite deferals if the medium is continuously busy
    // (do not time out a transmission if the half duplex medium is
    // completely saturated with other people's data)
    WriteReg((BYTE) MACON4, MACON4_DEFER);
    // Late collisions occur beyond 63+8 bytes (8 bytes for preamble/start of frame delimiter)
    // 55 is all that is needed for IEEE 802.3, but ENC28J60 B5 errata for improper link pulse
    // collisions will occur less often with a larger number.
    WriteReg((BYTE) MACLCON2, 63);
    // Set non-back-to-back inter-packet gap to 9.6us.  The back-to-back
    // inter-packet gap (MABBIPG) is set by MACSetDuplex() which is called
    // later.
    WriteReg((BYTE) MAIPGL, 0x12);
    WriteReg((BYTE) MAIPGH, 0x0C);
    // Set the maximum packet size which the controller will accept
    WriteReg((BYTE) MAMXFLL, LOW(MAXFRAMEC));
    WriteReg((BYTE) MAMXFLH, HIGH(MAXFRAMEC));
    // Enter Bank 3 and initialize physical MAC address registers
    BankSel(MAADR1);
    WriteReg((BYTE) MAADR1, 0x00);
    WriteReg((BYTE) MAADR2, 0x04);
    WriteReg((BYTE) MAADR3, 0xa3);
    WriteReg((BYTE) MAADR4, 0x00);
    WriteReg((BYTE) MAADR5, 0x02);
    WriteReg((BYTE) MAADR6, 0x00);
    // Disable half duplex loopback in PHY.  Bank bits changed to Bank 2 as a
    // side effect.
    WritePHYReg(PHCON2, PHCON2_HDLDIS);
    // Configure LEDA to display LINK status, LEDB to display TX/RX activity
    SetLEDConfig(0x0472);
    // Set the MAC and PHY into the proper duplex state
    MACSetDuplex(HALF);
    // Enable packet reception
    BFSReg(ECON1, ECON1_RXEN);
}

WORD swaps(WORD v)
{
    WORD_VAL t;
    BYTE b;

    t.Val = v;
    b = t.v[1];
    t.v[1] = t.v[0];
    t.v[0] = b;

    return t.Val;
}

void SendUDPPacket(void)
{
    BYTE UDPData[] = {0x00, 0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0x00 ,0x04  ,0xa3 ,0x00 ,0x02 ,0x00 ,0x08 ,0x00 ,0x45 ,0x00, 0x00 ,0x22 ,0x05 ,0x55 ,0x00 ,0x00 ,0x64 ,0x11  ,0x8f ,0xc2 ,0xc0 ,0xa8 ,0x01 ,0x0c ,0xff ,0xff, 0xff ,0xff ,0x0b ,0x2c ,0x76 ,0x5f ,0x00 ,0x0e  ,0x00 ,0x00 ,0x43 ,0x6f ,0x62 ,0x72 ,0x61 ,0x78, 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00  ,0x00 ,0x00 ,0x00 ,0x00 };

    while (!MACIsTxReady(TRUE));
    BankSel(EWRPTL);
    // Set the SPI write pointer to the beginning of the transmit buffer
    WriteReg(ERDPTL, 0x39);
    WriteReg(ERDPTH, 0x10);
    //WriteReg(EWRPTL, 0x39);
    //WriteReg(EWRPTH, 0x10);
	
	WriteReg(EWRPTL, 0x08);
	WriteReg(EWRPTH, 0x10);
	
    MACPutArray(UDPData, sizeof (UDPData));
    //MACFlush();
    BankSel(ETXSTL);
    WriteReg(ETXSTL, 0x08);
    WriteReg(ETXSTH, 0x10);
    WriteReg(ETXNDL, 0x38);
    WriteReg(ETXNDH, 0x10);
    //LastTXedBuffer = CurrentTxBuffer;
    //TxBuffers[CurrentTxBuffer].Flags.bTransmitted = TRUE;
    
    // Reset transmit logic if a TX Error has previously occured
    // This is a silicon errata workaround
    if(ReadETHReg(EIR).EIRbits.TXERIF)
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

}
/*
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
*/

