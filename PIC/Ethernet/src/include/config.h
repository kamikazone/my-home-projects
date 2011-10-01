/******************************************************************************
 * Global configuration file for the Microchip TCP/IP Stack                   *
 *============================================================================*
 *                                                                            *
 * See README.TXT in the doc directory.                                       *
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
 *                                                                            *
 *- Version Log --------------------------------------------------------------*
 *   Date       Author        Comments                                        *
 *----------------------------------------------------------------------------*
 * 02/11/07 Jorge Amodio      Initial Version                                 *
 * 04/25/07 Jorge Amodio      Moved definitions from compiler.h and stacktsk.h*
 * 05/01/07 Jorge Amodio      Added macros for different serial EEPROMS part  *
 *                            numbers. Added MPFS_USE_24BIT_ADDR macro        *
 * 05/10/07 Jorge Amodio      Added STACK_USE_UDPTEST                         *
 * 05/12/07 Jorge Amodio      Added ENABLE_USER_PROCESS                       *
 * 06/01/01 Jorge Amodio      Rev 3.75.5 Beta Release                         *
 * 06/17/07 Jorge Amodio      Added support for PIC24FJ64GA002 based projects *
 * 06/21/07 Jorge Amodio      Added UART register mappings to enable UART     *
 *                            module selection in hardware config file if     *
 *                            needed.                                         *
 * 06/26/07 Jorge Amodio      Removed casts from mem manipulation functions   *
 *                            and compatibility with latest (3.12) C18 fix    *
 *                            Correct casts are introduced in config.h        *
 * 06/27/07 Jorge Amodio      Removed TICK_PRESCALE, added time and SNTP      *
 *                            definitions                                     *
 * 07/03/07 Jorge Amodio      Added support and configuration for PICDEM.net2 *
 * 07/04/07 Jorge Amodio      Added correct castings for printf C18 & C30     *
 * 07/09/07 Jorge Amodio      Added support for HPC Explorer (PIC18F8722)     *  
 * 07/10/07 Jorge Amodio      Added support for Cerelitous PICWEB1 module     *
 ******************************************************************************/
#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__C30__)
#include <libpic30.h>
#endif

#define VERSION   "3.75.6"        // Firmware version


//*****************************************************************************
// Define or include your hardware configuration
//
// In this section you have to include the header file that defines the 
// particular hardware configuration for your board or design.
//
// A macro is defined in the project options to name each board or design and
// select the appropiate header file for inclusion. You must define this
// macro in the MPLAB IDE Project->Build Options->Project compiler options.
// All header files are located in the main include directory, refer to the
// existing files as an example about how to create a new one.
//
#if defined(PIC10T)
    #include "include/pic10t.h"
#elif defined(MINIPIC10T)
    #include "include/minipic10t.h"
#elif defined(PICNET1)
//    #include "include/picnet1.h"
    #include "include/picnet1_spilcd.h"
#elif defined(EIP10)
      #include "include/eip10.h"
//    #include "include/eip10_lcd.h"
//    #include "include/eip10_spilcd.h"
#elif defined(PICDEM2)
    #include "include/picdem2.h"
#elif defined(PIC18_NIC28)
    #include "include/pic18_nic28.h"
#elif defined(PICDEMNET)
    #include "include/picdemnet.h"
#elif defined(PICDEMNET2)
    #include "include/picdemnet2.h"
#elif defined(HPC_EXPLORER)
    #include "include/hpc_explorer.h"
#elif defined(PICWEB1)
    #include "include/picweb1.h"
#elif defined(EXP16_DSPIC33)
    #include "include/exp16_dspic33.h"
#elif defined(EXP16_PIC24H)
    #include "include/exp16_pic24h.h"
#elif defined(EXP16_PIC24F)
    #include "include/exp16_pic24F.h"
#elif defined(PIC24FJ64_NIC28)
//    #include "include/pic24fj64.h"
    #include "include/pic24fj64_lcd.h"
#else
    #error: CFG001: No hardware configuration defined
#endif


//*****************************************************************************
// TCP/IP Config
//
// Define the default values for your MAC and IP configuration.
// Notice that the IP addresses are separated by commas and not by the
// traditional dot in the decimal dotted notation.
//
#define HOME

#if defined(HOME)
    #define DEFAULT_MAC_ADDRESS { 0x00, 0x04, 0xa3, 0x00, 0x02, 0x00 }
    #define DEFAULT_IP_ADDRESS  { 192, 168, 1, 12 }
    #define DEFAULT_NETMASK     { 255, 255, 255, 0 }
    #define DEFAULT_GATEWAY     { 192, 168, 1, 1  }
    #define DEFAULT_NS1         { 192, 168, 1, 1  }
    #define SNTP_SERVER_IP      { 192, 43, 244, 18 }   // time.nist.gov
#else
    #define DEFAULT_MAC_ADDRESS { 0x00, 0x04, 0xa3, 0x00, 0x02, 0x00 }
    #define DEFAULT_IP_ADDRESS  { 10, 10, 4, 2 }
    #define DEFAULT_NETMASK     { 255, 255, 0, 0 }
    #define DEFAULT_GATEWAY     { 10, 10, 11, 1  }
    #define DEFAULT_NS1         { 10, 10, 10, 6  }
    #define SNTP_SERVER_IP      { 192, 43, 244, 18 }   // time.nist.gov
#endif
#if defined(PICDEM2)
    #define DEFAULT_NETBIOS_NAME  "COBRA"
#elif defined(PIC10T) || defined(MINIPIC10T)
    #define DEFAULT_NETBIOS_NAME  "COBRA"
#elif defined(EIP10)
    #define DEFAULT_NETBIOS_NAME  "COBRA"
#elif defined(PICNET1)
    #define DEFAULT_NETBIOS_NAME  "COBRA"
#else
    #define DEFAULT_NETBIOS_NAME  "COBRA"
#endif


//*****************************************************************************
// Stack Modules
//
// Enable/Disable supported protocol and application modules for the TCP/IP
// stack. The TCP and UDP protocol modules will be enabled according to the
// modules you select here.
//
#define STACK_USE_ICMP               // ICMP reply (ping) module
#define STACK_USE_HTTP_SERVER        // HTTP server
//#define STACK_USE_IP_GLEANING      // Obtain IP address via IP Gleaning 
#define STACK_USE_DHCP             // DHCP client
//#define STACK_USE_FTP_SERVER         // FTP server
//#define STACK_USE_TCP_EXAMPLE1     // HTTP client example in tcp_client_ex1.c
//#define STACK_USE_ANNOUNCE           // Ethernet Device Discoverer server/client
//#define STACK_USE_SNTP               // SNTP client
//#define STACK_USE_DNS              // DNS client
#define STACK_USE_NBNS               // NetBIOS Name Service Server
//#define STACK_USE_UDPTEST          // Enable UDP Test code


//*****************************************************************************
// Some time related definitions
//
// Define Ticks per second for the tick manager
//
#define TICKS_PER_SECOND     (100)   // 10ms

//#define USE_TIME                     // Include time routines
#define TIME_SOURCE_TICK             // Time source is Timer0 Tick counter
//#define TIME_SOURCE_32KTIMER

//#define TZ_OFFSET            (-5)    // Time Zone offset (negative west of GMT)
//#define SNTP_UPDATE_SECS     (43200) // SNTP update interval in seconds (12hrs)


//*****************************************************************************
// Miscellaneous Stack Options
//

// Define the Baud Rate for the RS-232 Serial Interface
#define BAUD_RATE (19200)            // bps

// Include the code for the configuration menu via the RS-232 serial interface
//
#define ENABLE_BUTTON0_CONFIG

// Include User process code in main.c
//
//#define ENABLE_USER_PROCESS

// Define Username and Password for the FTP Server
//
//#define FTP_USERNAME "ftp"
//#define FTP_PASSWORD "microchip"
//#define FTP_USER_NAME_LEN (10)

// Define default TCP port for HTTP server
//
#define HTTP_PORT (80)

// Enable Hardware assisted IP checksum calculation
// Some Ethernet controllers such as the ENC28J60 include a feature that 
// permits to use the DMA module in checksum mode to assist in the calculation
// of checksum values. The current silicon revisions of the ENC28J60 (B1-B5)
// have a bug that may produce incoming packet loss if this option is enabled
// and a packet is received when the DMA module is in checksum mode.
// If this option is commented the code will set the STACK_USE_SW_CKSUM and
// include the appropriate code to calculate the checksums by software.
//
//#define STACK_USE_HW_CKSUM

// Uncomment following line if this stack will be used in client mode.
// In client mode, some functions specific to client operation are enabled.
// This option will be enabled by default if you include any stack modules
// in the "Stack Modules" section above that require the stack to operate in
// this particular mode.
//
//#define STACK_CLIENT_MODE

// Comment following line if TCP state machine should wait for acknowledgement
// from the remote host before transmitting another packet.
// Commenting following line may reduce throughput.
//
//#define TCP_NO_WAIT_FOR_ACK

// This macro is specific to the Microchip Ethernet controllers.  
// If a different Ethernet controller is used, this define is not used.
// If a Microchip controller is used and a self memory test should be done 
// when the MACInit() function is called, uncomment this line.
// The test requires ~512 bytes of program memory.
//
//#define MAC_POWER_ON_TEST

// This macro is specific to the Microchip Ethernet controllers.  
// If a different Ethernet controller is used, this define is not used.
// Ideally, when MAC_FILTER_BROADCASTS is defined, all broadcast packets that
// are received would be discarded by the hardware, except for ARP requests for
// our IP address. This could be accomplished by filtering all broadcasts, but
// allowing the ARPs using the pattern match filter.
// The code for this feature has been partially implemented, but it is not
// complete nor tested, so this option should remain unused in this stack 
// version.
//
//#define MAC_FILTER_BROADCASTS

// Maximum number of TCP sockets allowed
// Note that each TCP socket consumes 38 bytes of RAM.
//
#define MAX_SOCKETS          (6u)

// Maximum number of TCP sockets allowed
//
#define MAX_UDP_SOCKETS      (4u)

// Maximum numbers of simultaneous HTTP connections allowed.
// Each connection consumes 10 bytes of RAM.
//
#define MAX_HTTP_CONNECTIONS (3u)


//*****************************************************************************
// Storage options
//
// If you enabled the HTTP server you must choose a storage media for the
// web server documents. The current version supports an external serial
// EEPROM or program memory. The code uses a simple FAT implementation or
// Microchip File System (MPFS) and the image to be stored during compilation
// time (for program memory storage) or to be transferred to the serial EEPROM
// must be generated with the MPFS.EXE utility available in the tools
// directory.
// Remember that the total size available for your web server documents is
// limited by the amount of available program memory and the size of the
// serial EEPROM minus 64 bytes that are reserved to store the configuration
// information.
// If the HTTP server is not enable but you still want to store the 
// configuration information you still need to define MPFS_USE_EEPROM.
//  
//#define MPFS_USE_EEPROM            // Use external serial EEPROM
#define MPFS_USE_PGRM            // Use Program Memory


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///       UNLESS NECESSARY AND YOU REALLY KNOW WHAT YOU ARE DOING YOU       ///
///           SHOULD NOT NEED TO CHANGE ANY OF THE LINES BELOW              ///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/******************************************************************************
 * TCP/IP Stack code modules defines derived from configuration and options   *
 *                                                                            *
 * The following conditional macros will enable compilation of the required   *
 * protocol modules if they have not been previously defined                  *
 ******************************************************************************/

//*****************************************************************************
// Set Baud Rate Generator Register value based on defined baud rate
// and map registers based on UART_NO that has to be 1 or 2 for 16-bit
// devices. For 8-bit if no UART_NO is defined the registers will be mapped
// to the standard register name for devices with one UART module
#if defined(__C30__)
    #define SPBRG_VAL        ((TCY_CLOCK+8ul*BAUD_RATE)/16/BAUD_RATE-1)

    #if UART_NO == 1
        #define UART_BRG       U1BRG
        #define UART_MODE      U1MODE
        #define UART_MODEbits  U1MODEbits
        #define UART_STA       U1STA
        #define UART_STAbits   U1STAbits
        #define UART_TXREG     U1TXREG
        #define UART_RXREG     U1RXREG
    #elif UART_NO == 2
        #define UART_BRG       U2BRG
        #define UART_MODE      U2MODE
        #define UART_MODEbits  U2MODEbits
        #define UART_STA       U2STA
        #define UART_STAbits   U2STAbits
        #define UART_TXREG     U2TXREG
        #define UART_RXREG     U2RXREG
    #else
        #error Incorrect UART Module number
    #endif

#else // PIC18

    #if ((TCY_CLOCK+2*BAUD_RATE)/BAUD_RATE/4 - 1) <= 255
        #define SPBRG_VAL ((TCY_CLOCK+2*BAUD_RATE)/BAUD_RATE/4 - 1)
        #define USART_USE_BRGH_HIGH
    #else
        #define SPBRG_VAL ((TCY_CLOCK+8*BAUD_RATE)/BAUD_RATE/16 - 1)
    #endif

    #if UART_NO == 1
        #define UART_TXSTAbits TXSTA1bits
        #define UART_RCSTAbits RCSTA1bits
        #define UART_TXREG     TXREG1
        #define UART_TXSTA     TXSTA1
        #define UART_RCSTA     RCSTA1
        #define UART_SPBRG     SPBRG1
        #define UART_RCREG     RCREG1
    #elif UART_NO == 2
        #define UART_TXSTAbits TXSTA2bits
        #define UART_RCSTAbits RCSTA2bits
        #define UART_TXREG     TXREG2
        #define UART_TXSTA     TXSTA2
        #define UART_RCSTA     RCSTA2
        #define UART_SPBRG     SPBRG2
        #define UART_RCREG     RCREG2
    #else
        #define UART_TXSTAbits TXSTAbits
        #define UART_RCSTAbits RCSTAbits
        #define UART_TXREG     TXREG
        #define UART_TXSTA     TXSTA
        #define UART_RCSTA     RCSTA
        #define UART_SPBRG     SPBRG
        #define UART_RCREG     RCREG
    #endif
#endif

//*****************************************************************************
// If we are using one of the new PIC18F MCUs with Ethernet interface
// group them under a common macro name
#if defined(__18F97J60) || defined(__18F96J65) || defined(__18F96J60) || defined(__18F87J60) || defined(__18F86J65) || defined(__18F86J60) || defined(__18F67J60) || defined(__18F66J65) || defined(__18F66J60) 
#define __PIC18FXXJ60
#endif

//*****************************************************************************
// Include UDP Protocol Module if required
#if defined(STACK_USE_DHCP) || defined(STACK_USE_DNS) || defined(STACK_USE_NBNS) || defined(STACK_USE_ANNOUNCE) || defined(STACK_USE_TCP_EXAMPLE1) || defined(STACK_USE_UDP_EXAMPLE1) || defined(STACK_USE_UDPTEST) || defined(STACK_USE_SNTP)
    #if !defined(STACK_USE_UDP)
         #define STACK_USE_UDP
    #endif
#endif

//*****************************************************************************
// Include TCP Protocol Module if required
#if defined(STACK_USE_HTTP_SERVER) || defined(STACK_USE_FTP_SERVER) || defined(STACK_USE_TCP_EXAMPLE1)
    #if !defined(STACK_USE_TCP)
        #define STACK_USE_TCP
    #endif
#endif

//*****************************************************************************
// Include DNS name resolution module if required
#if defined(STACK_USE_TCP_EXAMPLE1)
    #if !defined(STACK_USE_DNS)
        #define STACK_USE_DNS
    #endif
#endif

//*****************************************************************************
// Include ICMP Module for obtaining IP address via gleaning method
#if defined(STACK_USE_IP_GLEANING)
    #if !defined(STACK_USE_ICMP)
        #define STACK_USE_ICMP
    #endif
#endif

//*****************************************************************************
// Set client mode for FTP Server
#if defined(STACK_USE_FTP_SERVER) || defined(STACK_USE_DNS) || defined(STACK_USE_TCP_EXAMPLE1) || defined(STACK_USE_SNTP)
    #if !defined(STACK_CLIENT_MODE)
        #define STACK_CLIENT_MODE
    #endif
#endif

// FTP Server not supported when storage is on program memory
#if defined(STACK_USE_FTP_SERVER) && defined(MPFS_USE_PGRM)
    #undef STACK_USE_FTP_SERVER
#endif

//*****************************************************************************
// If checksum calculation method is not defined, define software by default
#if !defined(STACK_USE_HW_CKSUM) && !defined(STACK_USE_SW_CKSUM)
    #define STACK_USE_SW_CKSUM
#endif

//*****************************************************************************
// Set Tx and Rx buffer sizes based on Ethernet controller
#if defined(USE_ENC28J60) || defined(__PIC18FXXJ60)
    #define MAC_TX_BUFFER_SIZE   (576)
    #define MAC_TX_BUFFER_COUNT  (MAX_SOCKETS+1)
#else
    #define MAC_TX_BUFFER_SIZE   (1024)
    #define MAC_TX_BUFFER_COUNT  (1)
#endif

#define MAC_RX_BUFFER_SIZE       (MAC_TX_BUFFER_SIZE)

//*****************************************************************************
// Based on the protocol/applications modules enabled calculate the number
// of available sockets
#define AVAILABLE_SOCKETS        (MAX_SOCKETS)
#define AVAILABLE_UDP_SOCKETS    (MAX_UDP_SOCKETS)

#if defined(STACK_USE_HTTP_SERVER)
    #define AVAILABLE_SOCKETS2   (AVAILABLE_SOCKETS - MAX_HTTP_CONNECTIONS)
#else
    #define AVAILABLE_SOCKETS2   (MAX_SOCKETS)
#endif

#if defined(STACK_USE_FTP_SERVER)
    #define AVAILABLE_SOCKETS3   (AVAILABLE_SOCKETS2 - 2)
#else
    #define AVAILABLE_SOCKETS3   (AVAILABLE_SOCKETS2)
#endif

#if defined(STACK_USE_DHCP)
    #define AVAILABLE_UDP_SOCKETS2 (AVAILABLE_UDP_SOCKETS - 1)
#else
    #define AVAILABLE_UDP_SOCKETS2 AVAILABLE_UDP_SOCKETS
#endif

#if defined(STACK_USE_SNMP_SERVER)
    #define AVAILABLE_UDP_SOCKETS3 (AVAILABLE_UDP_SOCKETS2 - 1)
#else
    #define AVAILABLE_UDP_SOCKETS3 AVAILABLE_UDP_SOCKETS2
#endif

#if defined(STACK_USE_TFTP_CLIENT)
    #define AVAILABLE_UDP_SOCKETS4 (AVAILABLE_UDP_SOCKETS2)
#else
    #define AVAILABLE_UDP_SOCKETS4 AVAILABLE_UDP_SOCKETS3
#endif

//*****************************************************************************
// Select serial EEPROM driver code based on the EEPROM defined in the 
// hardware configuration file. Set the correct buffer and page sizes
// and addressing width.
#if defined(MPFS_USE_EEPROM)
    #define EEPROM_BUFFER_SIZE       (16)
    #define MPFS_RESERVE_BLOCK       (64)
    #if defined(USE_25LC256) || defined(USE_25LC1024)
        #define USE_SPIEEPROM
        #define EEPROM_CONTROL       (0)
        #if defined(USE_25LC1024)
            #define MPFS_USE_24BIT_ADDR
            #define MPFS_WRITE_PAGE_SIZE (256)
        #else
            #define MPFS_WRITE_PAGE_SIZE (64)
        #endif
    #elif defined(USE_24LC256) || defined(USE_24LC512)
        #define USE_I2CEEPROM
        #define EEPROM_CONTROL       (0xa0)
        #define MPFS_WRITE_PAGE_SIZE (128)
        #define MPFS_EEPROM_CLOCK    (400000)  // 400 KHz
    #elif defined(USE_24FC256) || defined(USE_24FC512)
        #define USE_I2CEEPROM
        #define EEPROM_CONTROL       (0xa0)
        #define MPFS_WRITE_PAGE_SIZE (128)
        #define MPFS_EEPROM_CLOCK    (1000000)  // 1 MHz
    #endif
#elif defined(MPFS_USE_PGRM)
    #define MPFS_WRITE_PAGE_SIZE     (8)
    #define MPFS_RESERVE_BLOCK       (0)
#else
    #if defined(STACK_USE_HTTP_SERVER)
        #error CFG035: No storage option defined for HTTP and FTP services
    #endif
#endif // MPFS_USE_EEPROM



/******************************************************************************
 * Configuration and stack options validation macros                          *
 *============================================================================*
 * Normally you should not need to edit/change the macros below, they just    *
 * perform a conditional validation of many hardware and software             *
 * configuration options to verify that all the required objects for each     *
 * particular configuration are properly defined if something is missing,     *
 * the compiler will stop and an error message will be shown for the missing  *
 * or invalid option.                                                         *
 ******************************************************************************/

//*****************************************************************************
// Verify hardware configuration

// Verify that CPU clock frequency is defined
#if !defined(CPU_CLOCK)
    #error CFG002: CPU_CLOCK not defined in hardware configuration file
#endif

#if !defined(TCY_CLOCK)
    #error CFG003: TCY_CLOCK not defined in hardware configuration file
#endif

#if (SPBRG_VAL > 255) && !defined(__C30__)
    #error CFG004: SPBRG value is out of range for defined CPU_CLOCK
#endif

#if !defined(TICKS_PER_SECOND)
    #error CFG005: TICKS_PER_SECOND must be defined
#endif

// Verify Ethernet controller interface configuration
#if defined(USE_ENC28J60)
    #if !defined(ENC_CS_IO)
        #error CFG011: ENC_CS_IO not defined in hardware configuration file
    #endif
    #if !defined(ENC_SPI_IF) || !defined(ENC_SSPBUF) || !defined(ENC_SPISTAT) || !defined(ENC_SPISTATbits) || !defined(ENC_SPICON1) || !defined(ENC_SPICON1bits)
        #error CFG012: Missing SPI configuration registers for ENC28J60
    #endif
#elif defined(USE_RTL8019AS)
    #if !defined(NIC_RESET_IO) || !defined(NIC_IOW_IO) || !defined(NIC_IOR_IO)
        #error CFG013: Missing RTL8019 control signals configuration
    #endif
    #if !defined(NIC_ADDR_IO) || !defined(NIC_DATA_TRIS) || !defined(NIC_DATA_IO)
        #error CFG014: Missing RTL8019 data and/or address bus configuration
    #endif
#elif defined(__PIC18FXXJ60)
    #define INTERNAL_ETH
#else
    #error CFG010: No ethernet controller defined
#endif

// Verify LCD interface configuration
#if defined(USE_LCD)
    #if defined(USE_CM_LCD)
        #if !defined(LCD_USE_BUFFER)
            #error CFG021: LCD Memory buffer not defined
        #endif
        #if defined(LCD_USE_SPI)
            #if !defined(USE_MCP23S08) || !defined(PORTX_CS_IO) || !defined(PORTX_CS_IO) || \
                !defined(PORTX_SPICON1) || !defined(PORTX_SSPBUF) || \
                !defined(PORTX_SPISTAT) || !defined(PORTX_SPISTAT) || \
                !defined(PORTX_ADDRESS)
                #error CFG022: LCD SPI interface not defined
            #endif
        #else
            #if !defined(LCD_DATA_IO) || !defined(LCD_RS_IO) || !defined(LCD_E_IO)
                #error CFG023: Missing LCD data and control signals definitions
            #endif
        #endif
    #else
        #error CFG020: Current firwmare version supports only character mode LCDs
    #endif
#endif

// Verify Serial EEPROM interface configuration
#if defined(MPFS_USE_EEPROM)
    #if defined(USE_25LC256) || defined(USE_25LC1024)
        #if !defined(EEPROM_CS_IO)
            #error CFG031: EEPROM_CS_IO not defined in hardware configuration file
        #endif
        #if !defined(EEPROM_SPI_IF) || !defined(EEPROM_SSPBUF) || \
            !defined(EEPROM_SPISTAT) || !defined(EEPROM_SPISTATbits) || \
            !defined(EEPROM_SPICON1)
            #error CFG032: Missing SPI configuration registers for SPI Serial EEPROM
        #endif
    #elif defined(USE_24LC256) || defined(USE_24FC256) || defined(USE_24LC512) || \
          defined(USE_24FC512)
        #if !defined(EEPROM_SCL_TRIS) || !defined(EEPROM_SDA_TRIS)
            #error CFG033: Missing I2C Serial EEPROM hardware interface configuration
        #endif
        #if !defined(EEPROM_SPI_IF) || !defined(EEPROM_SSPBUF) || \
            !defined(EEPROM_SPISTAT) || !defined(EEPROM_SPISTATbits) || \
            !defined(EEPROM_SPICON1) || !defined(EEPROM_SPICON1bits) || \
            !defined(EEPROM_SPICON2) || !defined(EEPROM_SPICON2bits)
            #error CFG034: Missing SSP configuration registers for I2C Serial EEPROM
        #endif
    #else
        #error CFG030: Serial EEPROM configuration not supported
    #endif
#endif


//*****************************************************************************
// Verify TCP/IP stack options and configuration
//
#if !defined(DEFAULT_MAC_ADDRESS)
    #error CFG050: No MAC Address defined
#endif

#if !defined(DEFAULT_IP_ADDRESS) 
    #error CFG051: No IP Address defined
#endif

#if !defined(DEFAULT_NETMASK)
    #error CFG052: No network mask defined
#endif

#if !defined(DEFAULT_GATEWAY)
    #error CFG053: No default gateway defined
#endif

#if defined(STACK_USE_DNS) && !defined(DEFAULT_NS1)
    #error CFG054: DNS client enabled but no default name server defined
#endif

#if defined(STACK_USE_FTP_SERVER) && (!defined(FTP_USERNAME) || !defined(FTP_PASSWORD))
    #error CFG055: FTP server enabled but username or password not defined
#endif

#if defined(STACK_USE_NBNS) && !defined(DEFAULT_NETBIOS_NAME)
    #error CFG056: NetBIOS Name Service enabled but hostname not defined
#endif

#if (MAX_SOCKETS <= 0 || MAX_SOCKETS > 255)
    #error CFG058: Invalid MAX_SOCKETS value defined
#endif

#if (MAX_UDP_SOCKETS <= 0 || MAX_UDP_SOCKETS > 255 )
    #error CFG059: Invalid MAX_UDP_SOCKETS value defined
#endif

#if (MAC_TX_BUFFER_SIZE <= 0 || MAC_TX_BUFFER_SIZE > 1500 )
    #error CFG060: Invalid MAC_TX_BUFFER_SIZE value defined
#endif

#if ( (MAC_TX_BUFFER_SIZE * MAC_TX_BUFFER_COUNT) > (5 * 1024) )
    #error CFG061: Warning, receive buffer is small.  Excessive packet loss may occur.
#endif

#if defined(STACK_USE_HTTP_SERVER)
    #if (MAX_HTTP_CONNECTIONS <= 0 || MAX_HTTP_CONNECTIONS > 255 )
        #error CFG062: Invalid MAX_HTTP_CONNECTIONS value defined
    #endif
#endif

#if AVAILABLE_SOCKETS3 < 0 || AVAILABLE_SOCKETS3 > MAX_SOCKETS
    #error CFG063: The defined MAX_SOCKETS value is too low
#endif

#if AVAILABLE_UDP_SOCKETS4 < 0 || AVAILABLE_UDP_SOCKETS4 > MAX_UDP_SOCKETS
    #error CFG064: The defined MAX_UDP_SOCKETS value is too low
#endif

#if defined(MPFS_USE_EEPROM) && defined(MPFS_USE_PGRM)
    #error CFG080: You can not define both clases of storage defined
#endif

#if defined(STACK_USE_HTTP_SERVER) && !(defined(MPFS_USE_EEPROM) || defined(MPFS_USE_PGRM))
    #error CFG081: No storage option defined for HTTP Server pages
#endif

#if defined(STACK_USE_FTP_SERVER) && defined(MPFS_USE_PGRM)
    #error CFG082: FTP Server not supported for program memory storage option
#endif

#if defined(STACK_USE_HTTP_SERVER)
    #if (MAC_TX_BUFFER_SIZE <= 130 || MAC_TX_BUFFER_SIZE > 1500 )
        #error HTTP001: Invalid MAC_TX_BUFFER_SIZE value specified
    #endif
#endif


//*****************************************************************************
// Compiler specific replacement macros
#if defined(DEBUG)
    #define DebugPrint(a)       {putrsUART(a);}
#else
    #define DebugPrint(a)       {}
#endif

#if defined(__18CXX)
    #define ROM                  rom
    #define ROMPC                rom far char
    #define strcpypgm2ram(a, b)  strcpypgm2ram(a,(rom far char*)b)
    #define memcpypgm2ram(a,b,c) memcpypgm2ram((void *)a,(const far rom void *)b,c)
    #define memcmppgm2ram(a,b,c) memcmppgm2ram((void *)a,(const far rom void *)b,c)
    #define __attribute__(a)
    #define BusyUART()           BusyUSART()
    #define CloseUART()          CloseUSART()
    #define ConfigIntUART(a)     ConfigIntUSART(a)
    #define DataRdyUART()        DataRdyUSART()
    #define OpenUART(a,b,c)      OpenUSART(a,b,c)
    #define ReadUART()           ReadUSART()
    #define WriteUART(a)         WriteUSART(a)
    #define getsUART(a,b,c)      getsUSART(b,a)
    #define putsUART(a)          putsUSART(a)
    #define getcUART()           ReadUSART()
    #define putcUART(a)          WriteUSART(a)
    #define putrsUART(a)         putrsUSART((rom far char*)a)
    #define printf(a)            printf((rom far char *)a) 
 
#elif defined(__C30__)
    #define ROM                  const
    #define ROMPC                const char
    #define putsUART(a)          putstrUART((unsigned int *)a)
    #define putrsUART(a)         putstrUART((unsigned int *)a)
    #define putcUART(a)          WriteUART(a)
    #define memcmppgm2ram(a,b,c) memcmp(a,b,c)
    #define memcpypgm2ram(a,b,c) memcpy(a,b,c)
    #define strcpypgm2ram(a, b)  strcpy((char*)a,b)
    #define Reset()              asm("reset")

    #if defined(__dsPIC33F__) || defined(__PIC24H__)
        #define AD1PCFGbits      AD1PCFGLbits
        #define AD1CHS           AD1CHS0
    #elif defined(__dsPIC30F__)
        #define ADC1BUF0         ADCBUF0
        #define AD1CHS           ADCHS
        #define AD1CON1          ADCON1
        #define AD1CON2          ADCON2
        #define AD1CON3          ADCON3
        #define AD1PCFGbits      ADPCFGbits
        #define AD1CSSL          ADCSSL
        #define AD1IF            ADIF
        #define AD1IE            ADIE
        #define _ADC1Interrupt   _ADCInterrupt
    #endif

#endif

#endif // _CONFIG_H

