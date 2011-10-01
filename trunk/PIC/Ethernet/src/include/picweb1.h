/******************************************************************************
 * Header file for Celeritous PICWEB1 (PIC18F67J60) Web Server Module         *
 *============================================================================*
 *                                                                            *
 * This header file defines the hardware configuration and options for the    *
 * Celeritous PICWEB1 Web Server Module featuring the new PIC18F67J60         *
 * Microchip microcontroller with internal ethernet peripheral module.        *
 *                                                                            *
 * Detailed information about the PICWEB1 module and associated development   *
 * kit can be obtained at: http://www.celeritous.com/                         *
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
 * 07/10/07 Jorge Amodio      Initial Version                                 *
 ******************************************************************************/
#ifndef _CL_PICWEB1_H
#define _CL_PICWEB1_H

// Include the appropriate header file for the microcontroller family
#include <p18f67j60.h>

//*****************************************************************************
// Define Microcontroller Clock Frequency in Hertz
#define CPU_CLOCK          (41666667)
#define TCY_CLOCK          (CPU_CLOCK/4)

//*****************************************************************************
// GPIO Ports assignments, configuration and initial default value
// Define the direction for each Input/Output pin (0-Output, 1-Input) and
// the initial state at the application startup
//
// PORTA Direction and initial status
//                     +-------------- n/a OSC1
//                     |+------------- n/a OSC2
//                     ||+------------ RA5 = n/c
//                     |||+----------- RA4 = n/c
//                     ||||+---------- RA3 = n/c
//                     |||||+--------- RA2 = n/c
//                     ||||||+-------- RA1 = (Ethernet module LEDB)
//                     |||||||+------- RA0 = (Ethernet module LEDA)
#define INIT_TRISA  (0b00000000)
#define INIT_PORTA  (0b00000000)

// PORTB Direction and initial status
//                     +-------------- RB7 = Used as PGD for ICSP
//                     |+------------- RB6 = Used as PGC for ICSP
//                     ||+------------ RB5 = n/c
//                     |||+----------- RB4 = n/c
//                     ||||+---------- RB3 = Pushbutton S4 (Demo board)
//                     |||||+--------- RB2 = Pushbutton S3 (Demo board)
//                     ||||||+-------- RB1 = Pushbutton S2 (Demo board)
//                     |||||||+------- RB0 = Pushbutton S1 (Demo board)
#define INIT_TRISB  (0b01001111)
#define INIT_PORTB  (0b00000000)

// PORTC Direction and initial status
//                     +-------------- RC7 = (USART RX1) to USBTX via P3
//                     |+------------- RC6 = (USART TX1) to USBRX via P4
//                     ||+------------ RC5 = Used as SDO1
//                     |||+----------- RC4 = Used as SDI1
//                     ||||+---------- RC3 = Used as SCK1
//                     |||||+--------- RC2 = n/c
//                     ||||||+-------- RC1 = T1OSCI 32KHz xtal
//                     |||||||+------- RC0 = T1OSCO 32KHz xtal
#define INIT_TRISC  (0b10010000)
#define INIT_PORTC  (0b11000000)

// PORTD Direction and initial status
//                       +------------ n/a
//                       |  +--------- RD2 = n/c
//                       |  |+-------- RD1 = TMP121 Temp Sens CS (Demo Board)
//                     __|__||+------- RD0 = 25LC256 EEPROM CS 
#define INIT_TRISD  (0b00000000)
#define INIT_PORTD  (0b00000011)

// PORTE Direction and initial status
//                     +-------------- n/a
//                     |+------------- n/a
//                     ||+------------ RE5 = n/c
//                     |||+----------- RE4 = n/c
//                     ||||+---------- RE3 = LED D4 (Demo board)
//                     |||||+--------- RE2 = LED D3 (Demo board)
//                     ||||||+-------- RE1 = LED D2 (Demo board)
//                     |||||||+------- RE0 = LED D1 (Demo board)
#define INIT_TRISE  (0b00000000)
#define INIT_PORTE  (0b00000000)

// PORTF Direction and initial status
//                     +-------------- RF7 = n/c
//                     |+------------- RF6 = n/c
//                     ||+------------ RF5 = n/c
//                     |||+----------- RF4 = n/c
//                     ||||+---------- RF3 = n/c
//                     |||||+--------- RF2 = n/c
//                     ||||||+-------- RF1 = n/c
//                     |||||||+------- n/a
#define INIT_TRISF  (0b00000000)
#define INIT_PORTF  (0b00000000)

// PORTG Direction and initial status
//                      +------------- n/a
//                      | +----------- RG4 = (1-Wire DS2401)
//                      | | +--------- n/a
//                      | | |                    
//                     _|_|_|_
#define INIT_TRISG  (0b00000100)
#define INIT_PORTG  (0b00000100)

//*****************************************************************************
// Initialization values for various registers
//
#define INIT_ADCON0 (0b00000000)     // ADC Disabled
#define INIT_ADCON1 (0b00001101)
#define INIT_ADCON2 (0b10111110)


//*****************************************************************************
// Available LEDs and switches macro name definitions for application use
//
#define LED0_IO              (LATEbits.LATE0)
#define LED1_IO              (LATEbits.LATE1)
#define LED2_IO              (LATEbits.LATE2)
#define LED3_IO              (LATEbits.LATE3)
#define LED4_IO              (LATEbits.LATE3)    // No LED4 map to LED3
#define LED5_IO              (LATEbits.LATE3)    // No LED5 map to LED3
#define LED6_IO              (LATEbits.LATE3)    // No LED6 map to LED3
#define LED7_IO              (LATEbits.LATE3)    // No LED7 map to LED3

#define BUTTON0_IO           (PORTBbits.RB0)
#define BUTTON1_IO           (PORTBbits.RB1)
#define BUTTON2_IO           (PORTBbits.RB2)
#define BUTTON3_IO           (PORTBbits.RB3)


//*****************************************************************************
// Definitions for 25LC256
//
#define USE_25LC256
#define EEPROM_CS_IO         (LATDbits.LATD0)
#define EEPROM_SPI_IF        (PIR1bits.SSPIF)
#define EEPROM_SSPBUF        (SSP1BUF)
#define EEPROM_SPICON1       (SSP1CON1)
#define EEPROM_SPISTAT       (SSP1STAT)
#define EEPROM_SPISTATbits   (SSP1STATbits)
#define EEPROM_SPIEN         (SSP1CON1bits.SSPEN)
#define EEPROM_SPICON1_CFG   (0x21)      // SCK = Fosc/16
#define EEPROM_SPISTAT_CFG   (0x40)
//#define EEPROM_SAVE_SPI_CFG

#endif // _CL_PICWEB1_H

