/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 * Author: Guido Socher
 * Copyright: GPL V2
 *
 * Based on the enc28j60.c file from the AVRlib library by Pascal Stang.
 * For AVRlib See http://www.procyonengineering.com/
 * Used with explicit permission of Pascal Stang.
 *
 * Title: Microchip ENC28J60 Ethernet Interface Driver
 * Chip type           : ATMEGA88 with ENC28J60
 *********************************************/
#include <avr/io.h>
#include "avr_compat.h"
#include "enc28j60.h"
#include "timeout.h"
//
#define F_CPU 8000000UL  // 8 MHz
#ifndef ALIBC_OLD
#include <util/delay.h>
#else
#include <avr/delay.h>
#endif

static uint8_t ENC28J60Bank;
static uint16_t NextPacketPtr;
#define ENC28J60_CONTROL_PORT   PORTB
#define ENC28J60_CONTROL_DDR    DDRB
#define ENC28J60_CONTROL_CS     2
// set CS to 0 = active
#define CSACTIVE ENC28J60_CONTROL_PORT&=~(1<<ENC28J60_CONTROL_CS)
// set CS to 1 = passive
#define CSPASSIVE ENC28J60_CONTROL_PORT|=(1<<ENC28J60_CONTROL_CS)
//
#define WaitSPI() while(!(SPSR&(1<<SPIF)))

uint8_t ENC28J60ReadOp(uint8_t op, uint8_t address)
{
	CSACTIVE;
	// issue read command
	SPDR = op | (address & ADDR_MASK);
	WaitSPI();
	// read data
	SPDR = 0x00;
	WaitSPI();
	// do dummy read if needed (for mac and mii, see datasheet page 29)
	if(address & 0x80)
	{
		SPDR = 0x00;
		WaitSPI();
	}
	// release CS
	CSPASSIVE;
	return(SPDR);
}

void ENC28J60WriteOp(uint8_t op, uint8_t address, uint8_t data)
{
	CSACTIVE;
	// issue write command
	SPDR = op | (address & ADDR_MASK);
	WaitSPI();
	// write data
	SPDR = data;
	WaitSPI();
	CSPASSIVE;
}

void ENC28J60ReadBuffer(uint16_t len, uint8_t* data)
{
	CSACTIVE;
	// issue read command
	SPDR = ENC28J60_READ_BUF_MEM;
	WaitSPI();
	while(len)
	{
		len--;
		// read data
		SPDR = 0x00;
		WaitSPI();
		*data = SPDR;
		data++;
	}
	*data='\0';
	CSPASSIVE;
}

void ENC28J60WriteBuffer(uint16_t len, uint8_t* data)
{
	CSACTIVE;
	// issue write command
	SPDR = ENC28J60_WRITE_BUF_MEM;
	WaitSPI();
	while(len)
	{
		len--;
		// write data
		SPDR = *data;
		data++;
		WaitSPI();
	}
	CSPASSIVE;
}

void ENC28J60SetBank(uint8_t address)
{
	// set the bank (if needed)
	if ((address & BANK_MASK) != ENC28J60Bank)
	{
		// set the bank
		ENC28J60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1,
				(ECON1_BSEL1|ECON1_BSEL0));
		ENC28J60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, (address & BANK_MASK)
				>> 5);
		ENC28J60Bank = (address & BANK_MASK);
	}
}

uint8_t ENC28J60Read(uint8_t address)
{
	// set the bank
	ENC28J60SetBank(address);
	// do the read
	return ENC28J60ReadOp(ENC28J60_READ_CTRL_REG, address);
}

void ENC28J60Write(uint8_t address, uint8_t data)
{
	// set the bank
	ENC28J60SetBank(address);
	// do the write
	ENC28J60WriteOp(ENC28J60_WRITE_CTRL_REG, address, data);
}

void ENC28J60PhyWrite(uint8_t address, uint16_t data)
{
	// set the PHY register address
	ENC28J60Write(MIREGADR, address);
	// write the PHY data
	ENC28J60Write(MIWRL, data);
	ENC28J60Write(MIWRH, data >> 8);
	// wait until the PHY write completes
	while (ENC28J60Read(MISTAT) & MISTAT_BUSY)
	{
		_delay_us(15);
	}
}

void ENC28J60Init(uint8_t* macaddr)
{
	// initialize I/O
	ENC28J60_CONTROL_DDR |= 1 << ENC28J60_CONTROL_CS;
	CSPASSIVE;
	//
	DDRB |= 1 << PB2 | 1 << PB3 | 1 << PB5; // mosi, sck, ss output
	cbi(DDRB,PINB4); // MISO is input
	//
	CSPASSIVE;
	cbi(PORTB,PB3); // MOSI low
	cbi(PORTB,PB5); // SCK low
	//
	// initialize SPI interface
	// master mode and Fosc/2 clock:
	SPCR = (1 << SPE) | (1 << MSTR);
	SPSR |= (1 << SPI2X);
	// perform system reset
	ENC28J60WriteOp(ENC28J60_SOFT_RESET, 0, ENC28J60_SOFT_RESET);
	delay_ms(50);
	// check CLKRDY bit to see if reset is complete
	// The CLKRDY does not work. See Rev. B4 Silicon Errata point. Just wait.
	//while(!(enc28j60Read(ESTAT) & ESTAT_CLKRDY));
	// do bank 0 stuff
	// initialize receive buffer
	// 16-bit transfers, must write low byte first
	// set receive buffer start address
	NextPacketPtr = RXSTART_INIT;
	// Rx start
	ENC28J60Write(ERXSTL, RXSTART_INIT & 0xFF);
	ENC28J60Write(ERXSTH, RXSTART_INIT >> 8);
	// set receive pointer address
	ENC28J60Write(ERXRDPTL, RXSTART_INIT & 0xFF);
	ENC28J60Write(ERXRDPTH, RXSTART_INIT >> 8);
	// RX end
	ENC28J60Write(ERXNDL, RXSTOP_INIT&0xFF);
	ENC28J60Write(ERXNDH, RXSTOP_INIT>>8);
	// TX start
	ENC28J60Write(ETXSTL, TXSTART_INIT&0xFF);
	ENC28J60Write(ETXSTH, TXSTART_INIT>>8);
	// TX end
	ENC28J60Write(ETXNDL, TXSTOP_INIT&0xFF);
	ENC28J60Write(ETXNDH, TXSTOP_INIT>>8);
	// do bank 1 stuff, packet filter:
	// For broadcast packets we allow only ARP packtets
	// All other packets should be unicast only for our mac (MAADR)
	//
	// The pattern to match on is therefore
	// Type     ETH.DST
	// ARP      BROADCAST
	// 06 08 -- ff ff ff ff ff ff -> ip checksum for theses bytes=f7f9
	// in binary these poitions are:11 0000 0011 1111
	// This is hex 303F->EPMM0=0x3f,EPMM1=0x30
	ENC28J60Write(ERXFCON, ERXFCON_UCEN|ERXFCON_CRCEN|ERXFCON_PMEN);
	ENC28J60Write(EPMM0, 0x3f);
	ENC28J60Write(EPMM1, 0x30);
	ENC28J60Write(EPMCSL, 0xf9);
	ENC28J60Write(EPMCSH, 0xf7);
	//
	//
	// do bank 2 stuff
	// enable MAC receive
	ENC28J60Write(MACON1, MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);
	// bring MAC out of reset
	ENC28J60Write(MACON2, 0x00);
	// enable automatic padding to 60bytes and CRC operations
	ENC28J60WriteOp(ENC28J60_BIT_FIELD_SET, MACON3, MACON3_PADCFG0|MACON3_TXCRCEN|MACON3_FRMLNEN);
	// set inter-frame gap (non-back-to-back)
	ENC28J60Write(MAIPGL, 0x12);
	ENC28J60Write(MAIPGH, 0x0C);
	// set inter-frame gap (back-to-back)
	ENC28J60Write(MABBIPG, 0x12);
	// Set the maximum packet size which the controller will accept
	// Do not send packets longer than MAX_FRAMELEN:
	ENC28J60Write(MAMXFLL, MAX_FRAMELEN&0xFF);
	ENC28J60Write(MAMXFLH, MAX_FRAMELEN>>8);
	// do bank 3 stuff
	// write MAC address
	// NOTE: MAC address in ENC28J60 is byte-backward
	ENC28J60Write(MAADR5, macaddr[0]);
	ENC28J60Write(MAADR4, macaddr[1]);
	ENC28J60Write(MAADR3, macaddr[2]);
	ENC28J60Write(MAADR2, macaddr[3]);
	ENC28J60Write(MAADR1, macaddr[4]);
	ENC28J60Write(MAADR0, macaddr[5]);
	// no loopback of transmitted frames
	ENC28J60PhyWrite(PHCON2, PHCON2_HDLDIS);
	// switch to bank 0
	ENC28J60SetBank(ECON1);
	// enable interrutps
	ENC28J60WriteOp(ENC28J60_BIT_FIELD_SET, EIE, EIE_INTIE|EIE_PKTIE);
	// enable packet reception
	ENC28J60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN);
}

	// read the revision of the chip:
uint8_t ENC28J60GetRev(void)
{
	return (ENC28J60Read(EREVID));
}

void ENC28J60PacketSend(uint16_t len, uint8_t* packet)
{
	// Set the write pointer to start of transmit buffer area
	ENC28J60Write(EWRPTL, TXSTART_INIT&0xFF);
	ENC28J60Write(EWRPTH, TXSTART_INIT>>8);
	// Set the TXND pointer to correspond to the packet size given
			ENC28J60Write(ETXNDL, (TXSTART_INIT+len)&0xFF);
			ENC28J60Write(ETXNDH, (TXSTART_INIT+len)>>8);
			// write per-packet control byte (0x00 means use macon3 settings)
			ENC28J60WriteOp(ENC28J60_WRITE_BUF_MEM, 0, 0x00);
			// copy the packet into the transmit buffer
			ENC28J60WriteBuffer(len, packet);
			// send the contents of the transmit buffer onto the network
			ENC28J60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);
			// Reset the transmit logic problem. See Rev. B4 Silicon Errata point 12.
			if( (ENC28J60Read(EIR) & EIR_TXERIF) )
			{
				ENC28J60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRTS);
			}
		}

	// Gets a packet from the network receive buffer, if one is available.
	// The packet will by headed by an ethernet header.
	//      maxlen  The maximum acceptable length of a retrieved packet.
	//      packet  Pointer where packet data should be stored.
	// Returns: Packet length in bytes if a packet was retrieved, zero otherwise.
uint16_t ENC28J60PacketReceive(uint16_t maxlen, uint8_t* packet)
{
	uint16_t rxstat;
	uint16_t len;
	// check if a packet has been received and buffered
	//if( !(enc28j60Read(EIR) & EIR_PKTIF) ){
	// The above does not work. See Rev. B4 Silicon Errata point 6.
	if (ENC28J60Read(EPKTCNT) == 0)
	{
		return (0);
	}

	// Set the read pointer to the start of the received packet
	ENC28J60Write(ERDPTL, (NextPacketPtr));
	ENC28J60Write(ERDPTH, (NextPacketPtr) >> 8);
	// read the next packet pointer
	NextPacketPtr = ENC28J60ReadOp(ENC28J60_READ_BUF_MEM, 0);
	NextPacketPtr |= ENC28J60ReadOp(ENC28J60_READ_BUF_MEM, 0) << 8;
	// read the packet length (see datasheet page 43)
	len = ENC28J60ReadOp(ENC28J60_READ_BUF_MEM, 0);
	len |= ENC28J60ReadOp(ENC28J60_READ_BUF_MEM, 0) << 8;
	len -= 4; //remove the CRC count
	// read the receive status (see datasheet page 43)
	rxstat = ENC28J60ReadOp(ENC28J60_READ_BUF_MEM, 0);
	rxstat |= ENC28J60ReadOp(ENC28J60_READ_BUF_MEM, 0) << 8;
	// limit retrieve length
	if (len > maxlen - 1)
	{
		len = maxlen - 1;
	}
	// check CRC and symbol errors (see datasheet page 44, table 7-3):
	// The ERXFCON.CRCEN is set by default. Normally we should not
	// need to check this.
	if ((rxstat & 0x80) == 0)
	{
		// invalid
		len = 0;
	}
	else
	{
		// copy the packet from the receive buffer
		ENC28J60ReadBuffer(len, packet);
	}
	// Move the RX read pointer to the start of the next received packet
	// This frees the memory we just read out
	ENC28J60Write(ERXRDPTL, (NextPacketPtr));
	ENC28J60Write(ERXRDPTH, (NextPacketPtr) >> 8);
	// decrement the packet counter indicate we are done with this packet
	ENC28J60WriteOp(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_PKTDEC);
	return (len);
}

