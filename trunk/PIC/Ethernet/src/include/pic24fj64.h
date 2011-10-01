/******************************************************************************
 * Header file for PIC24FJ64GA002 + nic28 Test Prototype                      *
 *============================================================================*
 *                                                                            *
 * This header file defines the hardware configuration and options for the    *
 * "PIC24FJ64 - Internetworking with Microcontrollers Project" published by   *
 * Jorge Amodio.                                                              *
 *                                                                            *
 * Detailed information about this project including schematics can be        *
 * obtained at: http://www.ljcv.net/projects/pic24fj64/                       *
 *                                                                            *
 * Reference schematics are also available at:                                *
 * http://www.ljcv.net/library/                                               *
 *                                                                            *
 *                                                                            *
 * SOFTWARE LICENSE AGREEMENT                                                 *
 *                                                                            *
 * This software is provided to you free of charge with the sole condition    *
 * of preserving this Copyright Notice. This software is provided "AS IS".    *
 * LJCV Electronics disclaims all warranties, express, implied, statutory or  *
 * otherwise, not limited to merchantability, fitness for a particular        *
 * purpose, and infringement. LJCV Electronics shall in no event be liable    *
 * for special, incidental, or consequential damages. By using this software  *
 * or incorporating parts of it in your particular design or application you  *
 * are accepting the terms of this agreement.                                 *
 *                                                                            *
 * LJCV ELECTRONICS ASSUMES NO OBLIGATION TO PROVIDE ANY WARRANTY OR SUPPORT. *
 *                                                                            *
 * Copyright (c) 2007, LJCV Electronics. All Rights Reserved                  *
 * San Antonio, Texas, USA. info@ljcv.net, www.ljcv.net                       *
 *                                                                            *
 *- Version Log --------------------------------------------------------------*
 *   Date       Author        Comments                                        *
 *----------------------------------------------------------------------------*
 * 06/17/07 Jorge Amodio      Initial Version                                 *
 * 07/03/07 Jorge Amodio      Corrected SSPEN/SPIEN macro mappings            *
 * 07/05/07 Jorge Amodio      Replaced PORTx to LATx mappings for outputs     *
 ******************************************************************************/
#ifndef _PIC24FJ64_H
#define _PIC24FJ64_H

// Include the appropriate header file for the microcontroller family
#include <p24Fxxxx.h>

//*****************************************************************************
// Define Microcontroller Clock Frequency in Hertz
#define CPU_CLOCK          (32000000)
#define TCY_CLOCK          (CPU_CLOCK/2)

//*****************************************************************************
// GPIO Ports assignments, configuration and initial default value
// Define the direction for each Input/Output pin (0-Output, 1-Input) and
// the initial state at the application startup
//
// PORTA Direction and initial status
//                          +----------- Unimplemented
//                          |     +----- RA4  = Used as SOSCO for RTCC Clock
//                          |     |+---- RA3  = Used as OSCO
//                          |     ||+--- RA2  = Used as OSCI
//                          |     |||+-- RA1  = n/c, Reserved for analog input
//                     _____|_____||||+- RA0  = n/c, (mapped to LED3_IO)
#define INIT_TRISA  (0b0000000000000000)
#define INIT_PORTA  (0b0000000000000000)

// PORTB Direction and initial status
//                     +---------------- RB15 = n/c (mapped to LED2_IO)
//                     |+--------------- RB14 = LED 2 mapped to LED1_IO
//                     ||+-------------- RB13 = LED 1 mapped to LED0_IO
//                     |||+------------- RB12 = n/c
//                     ||||+------------ RB11 = 25LC256 CS
//                     |||||+----------- RB10 = nic 28 CS
//                     ||||||+---------- RB9  = (RP9) Used for SPI1 SDI
//                     |||||||+--------- RB8  = (RP8) Used for SPI1 SDO
//                     ||||||||+-------- RB7  = (RP7) Used for SPI1 SCK
//                     |||||||||+------- RB6  = (RP6) Used for UART1 RX
//                     ||||||||||+------ RB5  = (RP5) Used for UART1 TX
//                     |||||||||||+----- RB4  = Used as SOSCI for RTCC Clock
//                     ||||||||||||+---- RB3  = S3
//                     |||||||||||||+--- RB2  = S2
//                     ||||||||||||||+-- RB1  = Used as PGC1 for ICSP
//                     |||||||||||||||+- RB0  = Used as PGD1 for ICSP
#define INIT_TRISB  (0b0000001001001100)
#define INIT_PORTB  (0b0001110000000000)


//*****************************************************************************
// Initialization values for various registers
//
#define INIT_ADCON0 (0b00000001)     // ADON=1, Channel 0
#define INIT_ADCON1 (0b00001101)     // RA0 and RA1 analog inputs
#define INIT_ADCON2 (0b10111110)     // Right justify, 20TAD ACQ time, Fosc/64 (~21.0kHz)

//*****************************************************************************
// Available LEDs and switches macro name definitions for application use
//
#define LED0_IO              (LATAbits.LATA0)
#define LED1_IO              (LATAbits.LATA1)
#define LED2_IO              (LATAbits.LATA1)   // No LED2 map to LED1
#define LED3_IO              (LATAbits.LATA1)   // No LED3 map to LED1
#define LED4_IO              (LATAbits.LATA1)   // No LED4 map to LED1
#define LED5_IO              (LATAbits.LATA1)   // No LED5 map to LED1
#define LED6_IO              (LATAbits.LATA1)   // No LED6 map to LED1
#define LED7_IO              (LATAbits.LATA1)   // No LED7 map to LED1

#define BUTTON0_IO           (PORTBbits.RB2)
#define BUTTON1_IO           (PORTBbits.RB3)
#define BUTTON2_IO           (PORTBbits.RB3)   // No BUTTON2 map to BUTTON1
#define BUTTON3_IO           (PORTBbits.RB3)   // No BUTTON3 map to BUTTON1

//*****************************************************************************
// Select UART Module Number for RS232 Interface
// Valid values are 1 for UART1 and 2 for UART2
//
#define UART_NO 1

//*****************************************************************************
// Definitions for ENC28J60 Ethernet controller
//
#define USE_ENC28J60
#define ENC_CS_IO            (LATBbits.LATB10)
#define ENC_SPI_IF           (IFS0bits.SPI1IF)
#define ENC_SSPBUF           (SPI1BUF)
#define ENC_SPICON1          (SPI1CON1)
#define ENC_SPICON1bits      (SPI1CON1bits)
#define ENC_SPICON2          (SPI1CON2)
#define ENC_SPISTAT          (SPI1STAT)
#define ENC_SPISTATbits      (SPI1STATbits)
#define ENC_SPIEN            (SPI1STATbits.SPIEN)
#define ENC_SPICON1_CFG      (0x013b)  // SPI master, 8-bit mode, Rx sample midle
                                       // clock idle low, SCK = 8MHz (@ 40MIPS)
                                       // 1:1 primary, 5:1 secondary, preescalers
#define ENC_SPICON2_CFG      (0x0000)  // No framing
#define ENC_SPISTAT_CFG      (0x8000)  // Enable SPI interface
#define ENC_SAVE_SPI_CFG
//#define ENC_DEBUG

//*****************************************************************************
// Definitions for 25L1024 serial EEPROM
//
#define USE_25LC256
#define EEPROM_CS_IO         (LATBbits.LATB11)
#define EEPROM_SPI_IF        (IFS0bits.SPI1IF)
#define EEPROM_SSPBUF        (SPI1BUF)
#define EEPROM_SPICON1       (SPI1CON1)
#define EEPROM_SPICON1bits   (SPI1CON1bits)
#define EEPROM_SPICON2       (SPI1CON2)
#define EEPROM_SPISTAT       (SPI1STAT)
#define EEPROM_SPISTATbits   (SPI1STATbits)
#define EEPROM_SPIEN         (SPI1STATbits.SPIEN)
#define EEPROM_SPICON1_CFG   (0x0133)  // SPI master, 8-bit mode, Rx sample midle
                                       // clock idle low, SCK = 8MHz (@ 40MIPS)
                                       // 1:1 primary, 5:1 secondary, preescalers
#define EEPROM_SPICON2_CFG   (0x0000)  // No framing
#define EEPROM_SPISTAT_CFG   (0x8000)  // Enable SPI interface
#define EEPROM_SAVE_SPI_CFG

#endif // _PIC24FJ64_H
