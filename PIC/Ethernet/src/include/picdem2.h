/******************************************************************************
 * Header file for Microchip's PICDEM 2 Plus Development Board                *
 *============================================================================*
 *                                                                            *
 * This header file defines the hardware configuration and options for the    *
 * "Adding Ethernet to your PICDEM 2+ Project" published by Jorge Amodio.     *
 *                                                                            *
 * Detailed information about this project including schematics can be        *
 * obtained at: http://www.ljcv.net/projects/picdem2/                         *
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
 * 02/11/07 Jorge Amodio      Initial Version                                 *
 * 05/01/07 Jorge Amodio      Added USE_25LC256 and USE_25LC1024 macros       *
 * 07/03/07 Jorge Amodio      Corrected SSPEN/SPIEN macro mappings            *
 * 07/05/07 Jorge Amodio      Replaced PORTx to LATx mappings for outputs     *
 ******************************************************************************/
#ifndef _PICDEM2_H
#define _PICDEM2_H

// Include the appropriate header file for the microcontroller family
#include <p18cxxx.h>

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
//                     |||+----------- RA4 = S2 Push Button, mapped to BUTTON0_IO
//                     ||||+---------- RA3 = LCD RS
//                     |||||+--------- RA2 = LCD R/W
//                     ||||||+-------- RA1 = LCD E
//                     |||||||+------- RA0 = R16 5K Pot
#define INIT_TRISA  (0b00010001)
#define INIT_PORTA  (0b00000000)

// PORTB Direction and initial status
//                     +-------------- RB7 = Used as PGD for ICSP
//                     |+------------- RB6 = Used as PGC for ICSP
//                     ||+------------ RB5 = 25LC256 Serial EEPROM CS
//                     |||+----------- RB4 = nic28/ENC28J60 CS
//                     ||||+---------- RB3 = LED D5, mapped to LED2_IO
//                     |||||+--------- RB2 = LED D4, mapped to LED1_IO
//                     ||||||+-------- RB1 = LED D3, mapped to LED0_IO
//                     |||||||+------- RB0 = S3 Push Button, mapped to BUTTON1_IO
#define INIT_TRISB  (0b00000001)
#define INIT_PORTB  (0b00110000)

// PORTC Direction and initial status
//                     +-------------- RC7 = Used as RX by USART
//                     |+------------- RC6 = Used as TX by USART
//                     ||+------------ RC5 = Used as SDO for SPI interface
//                     |||+----------- RC4 = Used as SDI for SPI interface
//                     ||||+---------- RC3 = Used as SCK for SPI interface
//                     |||||+--------- RC2 = Buzzer
//                     ||||||+-------- RC1 = Used as T1OSI, 32KHz xtal
//                     |||||||+------- RC0 = Used as T1OSO, 32KHz xtal
#define INIT_TRISC  (0b10010000)
#define INIT_PORTC  (0b11000000)

#if defined(__18F452) || defined(__18F4520) || defined(__18F4620) || \
    defined(__18F4525)

// PORTD Direction and initial status
//                     +-------------- RD7 = n/c
//                     |+------------- RD6 = n/c
//                     ||+------------ RD5 = n/c
//                     |||+----------- RD4 = n/c
//                     ||||+---------- RD3 = LCD DB7
//                     |||||+--------- RD2 = LCD DB6
//                     ||||||+-------- RD1 = LCD DB5
//                     |||||||+------- RD0 = LCD DB4
#define INIT_TRISD  (0b00000000)
#define INIT_PORTD  (0b00000000)

// PORTE Direction and initial status
//                          +--------- RE2 = n/c
//                          |+-------- RE1 = n/c
//                          ||+------- RE0 = n/c
#define INIT_TRISE  (0b00000000)
#define INIT_PORTE  (0b00000000)
#endif


//*****************************************************************************
// Initialization values for various registers
#define INIT_ADCON0 (0b00000000)     // ADON=0, Channel 0
#define INIT_ADCON1 (0b00001111)     // No analog inputs

#if defined(__18F2620) || defined(__18F4620) || defined(__18F4525)
#define INIT_ADCON2 (0b10111110)     // Right justify, 20TAD ACQ time, Fosc/64 (~21.0kHz)
#endif


//*****************************************************************************
// Available LEDs and switches macro name definitions for application use
#define LED0_IO              (LATBbits.LATB1)
#define LED1_IO              (LATBbits.LATB2)
#define LED2_IO              (LATBbits.LATB3)
#define LED3_IO              (LATBbits.LATB3)  // No LED3 map to LED2
#define LED4_IO              (LATBbits.LATB3)  // No LED4 map to LED2
#define LED5_IO              (LATBbits.LATB3)  // No LED5 map to LED2
#define LED6_IO              (LATBbits.LATB3)  // No LED6 map to LED2
#define LED7_IO              (LATBbits.LATB3)  // No LED7 map to LED2

#define BUTTON0_IO           (PORTAbits.RA4)
#define BUTTON1_IO           (PORTBbits.RB0)
#define BUTTON2_IO           (PORTBbits.RB0)   // No BUTTON2 map to BUTTON1
#define BUTTON3_IO           (PORTBbits.RB0)   // No BUTTON3 map to BUTTON1


//*****************************************************************************
// LCD Module features and configuration
//
#if defined(__18F452) || defined(__18F4520) || defined(__18F4620) || \
    defined(__18F4525)
#define USE_LCD
#define USE_CM_LCD                 // Include Character Mode LCD Driver
#define LCD_USE_BUFFER             // Enable local RAM LCD Buffer
#define LCD_USE_CGCHARS            // Enable Custom Characters support
#define LCD_4BIT_IFACE
#define LCD_ROWS 2
#define LCD_COLS 16

typedef struct
{
    unsigned char data : 4;  // Lower nibble
    unsigned char : 4;
} LCD_DATA;

#define LCD_DATA_IO          (((volatile LCD_DATA*)&LATD)->data)
#define LCD_RW_IO            (LATAbits.LATA2)
#define LCD_RS_IO            (LATAbits.LATA3)
#define LCD_E_IO             (LATAbits.LATA1)
#endif


//*****************************************************************************
// Definitions for ENC28J60 Ethernet Controller interface
#define USE_ENC28J60
#define ENC_CS_IO            (LATBbits.LATB4)
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
//#define ENC_DEBUG

//*****************************************************************************
// Definitions for 25LC256 or 25LC1024 Serial EEPROM interface
//
#define USE_25LC256
//#define USE_25LC1024
#define EEPROM_CS_IO         (LATBbits.LATB5)
#define EEPROM_SPI_IF        (PIR1bits.SSPIF)
#define EEPROM_SSPBUF        (SSPBUF)
#define EEPROM_SPICON1       (SSPCON1)
#define EEPROM_SPISTAT       (SSPSTAT)
#define EEPROM_SPISTATbits   (SSPSTATbits)
#define EEPROM_SPIEN         (SSPCON1bits.SSPEN)
//#define EEPROM_SPICON1_CFG (0x20)      // SPI is shared with the ENC28J60    
//#define EEPROM_SPISTAT_CFG (0x40)      // we use the same SPI configuration
//#define EEPROM_SAVE_SPI_CFG            // defined for it

#endif // _PICDEM2_H

