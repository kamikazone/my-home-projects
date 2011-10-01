/******************************************************************************
 * Header file for LCJV Electronics eIP-10 Development board                  *
 *============================================================================*
 *                                                                            *
 * This header file defines the hardware configuration and options for the    *
 * LJCV Electronics eIP-10 Development Board.                                 *
 *                                                                            *
 * Detailed information about the eIP-10 board can be obtained at:            *
 * http://www.ljcv.net/eip10/                                                 *
 *                                                                            *
 * A detailed shcematic of the eIP-10 board and an schematic showing          *
 * suggested minimum connections to it can also be obtained at:               *
 * http://www.ljcv.net/library/                                               *
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
 * 02/11/07 Jorge Amodio      Initial Version                                 *
 * 07/03/07 Jorge Amodio      Corrected SSPEN/SPIEN macro mappings            *
 * 07/05/07 Jorge Amodio      Replaced PORTx to LATx mappings for outputs     *
 ******************************************************************************/
#ifndef _EIP10_H
#define _EIP10_H

// Include the appropriate header file for the microcontroller family
#include <p18cxxx.h>

//*****************************************************************************
// Define Microcontroller Clock Frequency in Hertz
//
#define CPU_CLOCK          (40000000)
#define TCY_CLOCK          (CPU_CLOCK/4)


//*****************************************************************************
// GPIO Ports assignments, configuration and initial default value
// Define the direction for each Input/Output pin (0-Output, 1-Input) and
// the initial state at the application startup
//
// PORTA Direction and initial status
//                     +-------------- n/a OSC1
//                     |+------------- n/a OSC2
//                     ||+------------ RA5 = LED3, mapped to software LED2_IO
//                     |||+----------- RA4 = LED2, mapped to software LED1_IO
//                     ||||+---------- RA3 = LED1, mapped to software LED0_IO
//                     |||||+--------- RA2 = n/c, J1-16
//                     ||||||+-------- RA1 = n/c, J1-18
//                     |||||||+------- RA0 = n/c, J1-20
#define INIT_TRISA  (0b00000000)
#define INIT_PORTA  (0b00000000)

// PORTB Direction and initial status
//                     +-------------- RB7 = Used as PGD for ICSP, J1-13
//                     |+------------- RB6 = Used as PGC for ICSP, J1-11
//                     ||+------------ RB5 = n/c, J1-9
//                     |||+----------- RB4 = n/c, J1-7
//                     ||||+---------- RB3 = n/c, J1-5
//                     |||||+--------- RB2 = n/c, J1-3
//                     ||||||+-------- RB1 = n/c, J1-1
//                     |||||||+------- RB0 = n/c, J1-2
#define INIT_TRISB  (0b00000000)
#define INIT_PORTB  (0b00000000)

// PORTC Direction and initial status
//                     +-------------- RC7 = Used as RX by USART, J1-8
//                     |+------------- RC6 = Used as TX by USART, J1-6
//                     ||+------------ RC5 = Used as SDO for SPI interface, J1-14
//                     |||+----------- RC4 = Used as SDI for SPI interface, J1-10
//                     ||||+---------- RC3 = Used as SCK for SPI interface, J1-12
//                     |||||+--------- RC2 = n/c, J1-4 (Optional Push Button mapped to BUTTON0_IO)
//                     ||||||+-------- RC1 = 25LC256 Serial EEPROM CS
//                     |||||||+------- RC0 = ENC28J60 CS
#define INIT_TRISC  (0b10010100)
#define INIT_PORTC  (0b00000011)

//*****************************************************************************
// Initialization values for various registers
//
#define INIT_ADCON0 (0b00000000)     // ADON=0, Channel 0
#define INIT_ADCON1 (0b00001111)     // No analog inputs
#define INIT_ADCON2 (0b10111110)     // Right justify, 20TAD ACQ time, Fosc/64 (~21.0kHz)


//*****************************************************************************
// Available LEDs and switches macro name definitions for application use
#define LED0_IO              (LATAbits.LATA3)
#define LED1_IO              (LATAbits.LATA4)
#define LED2_IO              (LATAbits.LATA5)
#define LED3_IO              (LATAbits.LATA5)  // No LED3 map to LED2
#define LED4_IO              (LATAbits.LATA5)  // No LED4 map to LED2
#define LED5_IO              (LATAbits.LATA5)  // No LED5 map to LED2
#define LED6_IO              (LATAbits.LATA5)  // No LED6 map to LED2
#define LED7_IO              (LATAbits.LATA5)  // No LED7 map to LED2

#define BUTTON0_IO           (PORTCbits.RC2)
#define BUTTON1_IO           (PORTCbits.RC2)   // No BUTTON2 map to BUTTON0
#define BUTTON2_IO           (PORTCbits.RC2)   // No BUTTON2 map to BUTTON0
#define BUTTON3_IO           (PORTCbits.RC2)   // No BUTTON3 map to BUTTON0


//*****************************************************************************
// Definitions for ENC28J60 Ethernet Controller interface
//
#define USE_ENC28J60
#define ENC_CS_IO            (LATCbits.LATC0)
#define ENC_SPI_IF           (PIR1bits.SSPIF)
#define ENC_SSPBUF           (SSPBUF)
#define ENC_SPISTAT          (SSPSTAT)
#define ENC_SPISTATbits      (SSPSTATbits)
#define ENC_SPICON1          (SSPCON1)
#define ENC_SPICON1bits      (SSPCON1bits)
#define ENC_SPIEN            (SSPCON1bits.SSPEN)
#define ENC_SPICON1_CFG      (0x20)
#define ENC_SPISTAT_CFG      (0x40)
//#define ENC_SAVE_SPI_CFG

//*****************************************************************************
// Definitions for 25LC256 or 25LC1024 Serial EEPROM interface
//
#define USE_25LC256
#define EEPROM_CS_IO         (LATCbits.LATC1)
#define EEPROM_SPI_IF        (PIR1bits.SSPIF)
#define EEPROM_SSPBUF        (SSPBUF)
#define EEPROM_SPICON1       (SSPCON1)
#define EEPROM_SPISTAT       (SSPSTAT)
#define EEPROM_SPISTATbits   (SSPSTATbits)
#define EEPROM_SPIEN         (SSPCON1bits.SSPEN)
//#define EEPROM_SPICON1_CFG (0x20)      // SPI is shared with the ENC28J60    
//#define EEPROM_SPISTAT_CFG (0x40)      // we use the same SPI configuration
//#define EEPROM_SAVE_SPI_CFG            // defined for it

#endif // _EIP10_H

