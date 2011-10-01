/******************************************************************************
 * Header file for Microchip's PICDEM HPC Explorer Development Board          *
 *============================================================================*
 *                                                                            *
 * This header file defines the hardware configuration and options for the    *
 * Microchip HPC Explorer demo board with a PIC18F8722 and an Ethernet        *
 * PICtail like board featuring the ENC28J60 Ethernet Controller.             *
 *                                                                            *
 * Detailed information about this project including schematics can be        *
 * obtained at: http://www.ljcv.net/projects/                                 *
 *                                                                            *
 * Reference schematics are also available at:                                *
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
 * 07/09/07 Jorge Amodio      Initial Version                                 *
 ******************************************************************************/
#ifndef _HPC_EXPLORER_H
#define _HPC_EXPLORER_H

// Include the appropriate header file for the microcontroller family
#include <p18f8722.h>

//*****************************************************************************
// Define Microcontroller Clock Frequency in Hertz
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
//                     ||+------------ RA5 = n/c
//                     |||+----------- RA4 = n/c
//                     ||||+---------- RA3 = n/c
//                     |||||+--------- RA2 = n/c
//                     ||||||+-------- RA1 = n/c
//                     |||||||+------- RA0 = AN0 R3 10K Pot
#define INIT_TRISA  (0b00000001)
#define INIT_PORTA  (0b00000000)

// PORTB Direction and initial status
//                     +-------------- RB7 = Used as PGD for ICSP
//                     |+------------- RB6 = Used as PGC for ICSP
//                     ||+------------ RB5 = n/c (ENC28J60 RESET)
//                     |||+----------- RB4 = (25LC256/1024 EEPROM CS)
//                     ||||+---------- RB3 = (ENC28J60 CS)
//                     |||||+--------- RB2 = CTS
//                     ||||||+-------- RB1 = RTS
//                     |||||||+------- RB0 = Pushbutton S1
#define INIT_TRISB  (0b00000011)
#define INIT_PORTB  (0b00011000)

// PORTC Direction and initial status
//                     +-------------- RC7 = Used as RX1 by USART
//                     |+------------- RC6 = Used as TX1 by USART
//                     ||+------------ RC5 = Used as SDO1
//                     |||+----------- RC4 = SDA1 | Used as SDI1
//                     ||||+---------- RC3 = SCL1 | Used as SCK1
//                     |||||+--------- RC2 = n/c
//                     ||||||+-------- RC1 = T1OSCI 32KHz xtal
//                     |||||||+------- RC0 = T1OSCO 32KHz xtal
#define INIT_TRISC  (0b10010000)
#define INIT_PORTC  (0b11000000)

// PORTD Direction and initial status
//                     +-------------- RD7 = LED D8
//                     |+------------- RD6 = LED D7
//                     ||+------------ RD5 = LED D6
//                     |||+----------- RD4 = LED D5
//                     ||||+---------- RD3 = LED D4
//                     |||||+--------- RD2 = LED D3
//                     ||||||+-------- RD1 = LED D2
//                     |||||||+------- RD0 = LED D1
#define INIT_TRISD  (0b00000000)
#define INIT_PORTD  (0b00000000)

// PORTE Direction and initial status
//                     +-------------- RE7 = n/c
//                     |+------------- RE6 = n/c
//                     ||+------------ RE5 = n/c
//                     |||+----------- RE4 = n/c
//                     ||||+---------- RE3 = n/c
//                     |||||+--------- RE2 = n/c
//                     ||||||+-------- RE1 = n/c
//                     |||||||+------- RE0 = n/c
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
//                     |||||||+------- RF0 = n/c
#define INIT_TRISF  (0b00000000)
#define INIT_PORTF  (0b00000000)

// PORTG Direction and initial status
//                     +-------------- RG7 = n/c
//                     |+------------- RG6 = n/c
//                     ||+------------ RG5 = n/c
//                     |||+----------- RG4 = n/c 
//                     ||||+---------- RG3 = n/c
//                     |||||+--------- RG2 = n/c
//                     ||||||+-------- RG1 = n/c
//                     |||||||+------- RG0 = n/c
#define INIT_TRISG  (0b00000000)
#define INIT_PORTG  (0b00000000)

// PORTH Direction and initial status
//                     +-------------- RH7 = n/c
//                     |+------------- RH6 = n/c
//                     ||+------------ RH5 = n/c
//                     |||+----------- RH4 = n/c
//                     ||||+---------- RH3 = n/c
//                     |||||+--------- RH2 = n/c
//                     ||||||+-------- RH1 = n/c
//                     |||||||+------- RH0 = n/c
#define INIT_TRISH  (0b00000000)
#define INIT_PORTH  (0b00000000)

// PORTJ Direction and initial status
//                     +-------------- RJ7 = n/c
//                     |+------------- RJ6 = n/c
//                     ||+------------ RJ5 = n/c
//                     |||+----------- RJ4 = n/c
//                     ||||+---------- RJ3 = n/c
//                     |||||+--------- RJ2 = n/c
//                     ||||||+-------- RJ1 = n/c
//                     |||||||+------- RJ0 = n/c
#define INIT_TRISJ  (0b00000000)
#define INIT_PORTJ  (0b00000000)


//*****************************************************************************
// Initialization values for various registers
#define INIT_ADCON0 (0b00000000)     // ADON=0, Channel 0
#define INIT_ADCON1 (0b00001111)     // No analog inputs


//*****************************************************************************
// Available LEDs and switches macro name definitions for application use
#define LED0_IO              (LATDbits.LATD0)
#define LED1_IO              (LATDbits.LATD1)
#define LED2_IO              (LATDbits.LATD2)
#define LED3_IO              (LATDbits.LATD3)
#define LED4_IO              (LATDbits.LATD4)
#define LED5_IO              (LATDbits.LATD5)
#define LED6_IO              (LATDbits.LATD6)
#define LED7_IO              (LATDbits.LATD7)

#define BUTTON0_IO           (PORTBbits.RB0)
#define BUTTON1_IO           (PORTBbits.RB0)   // No BUTTON1 map to BUTTON0
#define BUTTON2_IO           (PORTBbits.RB0)   // No BUTTON2 map to BUTTON0
#define BUTTON3_IO           (PORTBbits.RB0)   // No BUTTON3 map to BUTTON0


//*****************************************************************************
// Select UART Module Number for RS232 Interface
// Valid values are 1 for UART1 and 2 for UART2
//
#define UART_NO 1


//*****************************************************************************
// Definitions for ENC28J60 Ethernet Controller interface
#define USE_ENC28J60
#define ENC_CS_IO            (LATBbits.LATB3)
#define ENC_SPI_IF           (PIR1bits.SSPIF)
#define ENC_SSPBUF           (SSP1BUF)
#define ENC_SPISTAT          (SSP1STAT)
#define ENC_SPISTATbits      (SSP1STATbits)
#define ENC_SPICON1          (SSP1CON1)
#define ENC_SPICON1bits      (SSP1CON1bits)
#define ENC_SPIEN            (SSP1CON1bits.SSPEN)
#define ENC_SPICON1_CFG      (0x20)
#define ENC_SPISTAT_CFG      (0x40)
//#define ENC_SAVE_SPI_CFG
//#define ENC_DEBUG


//*****************************************************************************
// Definitions for 25LC256 or 25LC1024 Serial EEPROM interface
//
//#define USE_25LC256
#define USE_25LC1024
#define EEPROM_CS_IO         (LATBbits.LATB4)
#define EEPROM_SPI_IF        (PIR1bits.SSPIF)
#define EEPROM_SSPBUF        (SSP1BUF)
#define EEPROM_SPICON1       (SSP1CON1)
#define EEPROM_SPISTAT       (SSP1STAT)
#define EEPROM_SPISTATbits   (SSP1STATbits)
#define EEPROM_SPIEN         (SSP1CON1bits.SSPEN)
//#define EEPROM_SPICON1_CFG (0x20)      // SPI is shared with the ENC28J60    
//#define EEPROM_SPISTAT_CFG (0x40)      // we use the same SPI configuration
//#define EEPROM_SAVE_SPI_CFG            // defined for it

#endif // _HPC_EXPLORER_H

