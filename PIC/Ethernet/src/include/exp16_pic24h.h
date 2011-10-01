/******************************************************************************
 * Header file for Microchip's Explorer 16 Development Board                  *
 *============================================================================*
 *                                                                            *
 * This header file defines the hardware configuration and options for the    *
 * Microchip Explorer 16 Development Board with the PIC24HJ256GP610 PIM and   *
 * Microchip's Ethernet (ENC28J60) PICtail+.                                  *
 *                                                                            *
 * Detailed information about the Explorer 16 board and the PICTail+ can be   *
 * obtained at: http://www.microchip.com/                                     *
 *                                                                            *
 * A detailed shcematic of the Explorer 16 board is available in Appendix A   *
 * of the Explorer 16 User's Guide, Microchip Document # DS51589A.            *
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
 * 04/15/07 Jorge Amodio      Initial Version                                 *
 * 07/05/07 Jorge Amodio      Replaced PORTx to LATx mappings for outputs     *
 ******************************************************************************/
#ifndef _EXP16_PIC24H_H
#define _EXP16_PIC24H_H

// Include the appropriate header file for the microcontroller family
#include <p24Hxxxx.h>

//*****************************************************************************
// Define Microcontroller Clock Frequency in Hertz
#define CPU_CLOCK          (80000000)
#define TCY_CLOCK          (CPU_CLOCK/2)

//*****************************************************************************
// GPIO Ports assignments, configuration and initial default value
// Define the direction for each Input/Output pin (0-Output, 1-Input) and
// the initial state at the application startup
//
// PORTA Direction and initial status
//                     +---------------- RA15 = n/c?
//                     |+--------------- RA14 = n/c?
//                     ||+-------------- RA13 = INT2 ENC28J60 INT
//                     |||+------------- RA12 = n/c?
//                     ||||+------------ Unimplemented
//                     |||||+----------- RA10 = n/c?
//                     ||||||+---------- RA9  = n/c?
//                     |||||||+--------- Unimplemented
//                     ||||||||+-------- RA7  = LED D10 & S5 Push Button
//                     |||||||||+------- RA6  = LED D9
//                     ||||||||||+------ RA5  = LED D8
//                     |||||||||||+----- RA4  = LED D7
//                     ||||||||||||+---- RA3  = LED D6
//                     |||||||||||||+--- RA2  = LED D5
//                     ||||||||||||||+-- RA1  = LED D4
//                     |||||||||||||||+- RA0  = LED D3
#define INIT_TRISA  (0b0010000010000000)
#define INIT_PORTA  (0b0000000000000000)

// PORTB Direction and initial status
//                     +---------------- RB15 = LCD RS
//                     |+--------------- RB14 = U1RX/U1TX x-over control
//                     ||+-------------- RB13 = U1CTS/U1RTS x-over control
//                     |||+------------- RB12 = SDI1/SDO2 x-over control
//                     ||||+------------ RB11 = n/c?
//                     |||||+----------- RB10 = n/c?
//                     ||||||+---------- RB9  = n/c?
//                     |||||||+--------- RB8  = n/c?
//                     ||||||||+-------- RB7  = Used as PGD for ICSP
//                     |||||||||+------- RB6  = Used as PGC for ICSP
//                     ||||||||||+------ RB5  = AN5 R6 10K Pot
//                     |||||||||||+----- RB4  = AN4 TC1047A (U4) Vout
//                     ||||||||||||+---- RB3  = n/c?
//                     |||||||||||||+--- RB2  = to RA5 U2 PIC18F4550
//                     ||||||||||||||+-- RB1  = n/c ?
//                     |||||||||||||||+- RB0  = n/c ?
#define INIT_TRISB  (0b0000000000110000)
#define INIT_PORTB  (0b0111000000000000)

// PORTC Direction and initial status
//                     +---------------- RC15 = Used as OSC2 (8MHz xtal)
//                     |+--------------- RC14 = Used as SOSCO/TCK1 (32KHz xtal)
//                     ||+-------------- RC13 = Used as SOSCI (32KHz xtal)
//                     |||+------------- RC12 = Used as OSC1 (8MHz xtal)
//                     ||||   +--------- Unimplemented
//                     ||||   |   +----- RC4  = n/c (Graphics LCD pin 2)
//                     ||||   |   |+---- RC3  = n/c (Graphics LCD pin 3)
//                     ||||   |   ||+--- RC2  = n/c?
//                     ||||   |   |||+-- RC1  = n/c?
//                     ||||___|___||||+- Unimplemented
#define INIT_TRISC  (0b0000000000000000)
#define INIT_PORTC  (0b0000000000000000)

// PORTD Direction and initial status
//                     +---------------- RD15 = ENC28J60 RESET (Pictail+ n/c)
//                     |+--------------- RD14 = ENC28J60 CS (Pictail+)
//                     ||+-------------- RD13 = S4 Push Button
//                     |||+------------- RD12 = 25LC256 (U5) EEPROM CS
//                     ||||+------------ RD11 = n/c?
//                     |||||+----------- RD10 = n/c?
//                     ||||||+---------- RD9  = n/c?
//                     |||||||+--------- RD8  = n/c?
//                     ||||||||+-------- RD7  = S6 Push Button
//                     |||||||||+------- RD6  = S3 Push Button
//                     ||||||||||+------ RD5  = LCD R/W
//                     |||||||||||+----- RD4  = LCD E
//                     ||||||||||||+---- RD3  = n/c?
//                     |||||||||||||+--- RD2  = n/c?
//                     ||||||||||||||+-- RD1  = n/c?
//                     |||||||||||||||+- RD0  = n/c?
#define INIT_TRISD  (0b0010000011000000)
#define INIT_PORTD  (0b1101000000000000)

// PORTE Direction and initial status
//                        +------------- Unimplemented
//                        |    +-------- RE7  = LCD DB7
//                        |    |+------- RE6  = LCD DB6
//                        |    ||+------ RE5  = LCD DB5
//                        |    |||+----- RE4  = LCD DB4
//                        |    ||||+---- RE3  = LCD DB3
//                        |    |||||+--- RE2  = LCD DB2
//                        |    ||||||+-- RE1  = LCD DB1
//                     ___|____|||||||+- RE0  = LCD DB0
#define INIT_TRISE  (0b0000000000000000)
#define INIT_PORTE  (0b0000000000000000)

// PORTF Direction and initial status
//                      +--------------- Unimplemented
//                      |+-------------- RF13 = RTS for RS232 interface
//                      ||+------------- RF12 = CTS for RS232 interface
//                      ||| +----------- Unimplemented
//                      ||| | +--------- RF8  = Used as SDO1 to ENC28J60 (Pictail+)
//                      ||| | |+-------- RF7  = Used as SDI1 to ENC28J60 (Pictail+)
//                      ||| | ||+------- RF6  = Used as SCK1 to ENC28J60 (Pictail+)
//                      ||| | |||+------ RF5  = Used as U2TX for RS232 interface
//                      ||| | ||||+----- RF4  = used as U2RX for RS232 interface
//                      ||| | |||||+---- RF3  = Used as U1TX via 4053 x-over
//                      ||| | ||||||+--- RF2  = Used as U1RX via 4053 x-over
//                      ||| | |||||||+-- RF1  = n/c (to RB3 U2 PIC18F4550)
//                     _|||_|_||||||||+- RF0  = n/c (to RB4 U2 PIC18F4550)
#define INIT_TRISF  (0b0001000010010100)
#define INIT_PORTF  (0b0000000000000000)

// PORTG Direction and initial status
//                     +---------------- RG15 = n/c?
//                     |+--------------- RG14 = n/c?
//                     ||+-------------- RG13 = n/c?
//                     |||+------------- RG12 = n/c?
//                     |||| +----------- Unimplemented
//                     |||| |+---------- RG9  = n/c?
//                     |||| ||+--------- RG8  = Used as SDO2 to 25LC256 (U5)
//                     |||| |||+-------- RG7  = Used as SDI2 to 25LC256 (U5)
//                     |||| ||||+------- RG6  = Used as SCK2 to 25LC256 (U5)
//                     |||| ||||| +----- Unimplemented
//                     |||| ||||| |+---- RG3  = n/c?
//                     |||| ||||| ||+--- RG2  = n/c?
//                     |||| ||||| |||+-- RG1  = n/c?
//                     ||||_|||||_||||+- RG0  = n/c?
#define INIT_TRISG  (0b0000000010000000)
#define INIT_PORTG  (0b0000000000000000)


//*****************************************************************************
// Available LEDs and switches macro name definitions for application use
//
#define LED0_IO              (LATAbits.LATA0)
#define LED1_IO              (LATAbits.LATA1)
#define LED2_IO              (LATAbits.LATA2)
#define LED3_IO              (LATAbits.LATA3)
#define LED4_IO              (LATAbits.LATA4)
#define LED5_IO              (LATAbits.LATA5)
#define LED6_IO              (LATAbits.LATA6)
#define LED7_IO              (LATAbits.LATA7)  // No LED7 map to LED2

#define BUTTON0_IO           (PORTDbits.RD13)
#define BUTTON1_IO           (PORTAbits.RA7)
#define BUTTON2_IO           (PORTDbits.RD7)   // No BUTTON2 map to BUTTON0
#define BUTTON3_IO           (PORTDbits.RD6)


//*****************************************************************************
// Select UART Module Number for RS232 Interface
// Valid values are 1 for UART1 and 2 for UART2
//
#define UART_NO 2


//*****************************************************************************
// LCD Module features and configuration
//
#define USE_LCD
#define USE_CM_LCD                 // Include Character Mode LCD Driver
#define LCD_USE_BUFFER             // Enable local RAM LCD Buffer
#define LCD_USE_CGCHARS            // Enable Custom Characters support
//#define LCD_4BIT_IFACE
#define LCD_ROWS 2
#define LCD_COLS 16

typedef struct
{
    unsigned char data : 8;  // Bits 0 through 7
    unsigned char : 8;       // Bits 8 through 15
} LCD_DATA;

#define LCD_DATA_IO          (((volatile LCD_DATA*)&LATE)->data)
#define LCD_RW_IO            (LATDbits.LATD5)
#define LCD_RS_IO            (LATBbits.LATB15)
#define LCD_E_IO             (LATDbits.LATD4)


//*****************************************************************************
// Definitions for ENC28J60 Ethernet controller
// Note: Some early engineering samples of the dsPIC33F have a silicon bug
// that produces the CLKRDY incorrectly reported as being clear.  The
// work around is to set SCK = 8MHz -> #define ENC_SPICON1_CFG (0x12f)
//
#define USE_ENC28J60
#define ENC_RST_TRIS         (TRISDbits.TRISD15) // Not connected by default
#define ENC_RST_IO           (LATDbits.LATD15)
#define ENC_CS_TRIS          (TRISDbits.TRISD14)
#define ENC_CS_IO            (LATDbits.LATD14)
#define ENC_SCK_TRIS         (TRISFbits.TRISF6)
#define ENC_SDI_TRIS         (TRISFbits.TRISF7)
#define ENC_SDO_TRIS         (TRISFbits.TRISF8)
#define ENC_SPI_IF           (IFS0bits.SPI1IF)
#define ENC_SSPBUF           (SPI1BUF)
#define ENC_SPISTAT          (SPI1STAT)
#define ENC_SPISTATbits      (SPI1STATbits)
#define ENC_SPICON1          (SPI1CON1)
#define ENC_SPICON1bits      (SPI1CON1bits)
#define ENC_SPICON2          (SPI1CON2)
#define ENC_SPICON1_CFG      (0x013e)  // SPI master, 8-bit mode, Rx sample midle
                                       // clock idle low, SCK = 10MHz (@ 40MIPS)
#define ENC_SPICON2_CFG      (0x0000)  // No framing
#define ENC_SPISTAT_CFG      (0x8000)  // Enable SPI interface
#define ENC_DEBUG


//*****************************************************************************
// Definitions for 25LC256 serial EEPROM
//
#define USE_25LC256
#define EEPROM_CS_TRIS       (TRISDbits.TRISD12)
#define EEPROM_CS_IO         (LATDbits.LATD12)
#define EEPROM_SCK_TRIS      (TRISGbits.TRISG6)
#define EEPROM_SDI_TRIS      (TRISGbits.TRISG7)
#define EEPROM_SDO_TRIS      (TRISGbits.TRISG8)
#define EEPROM_SPI_IF        (IFS2bits.SPI2IF)
#define EEPROM_SSPBUF        (SPI2BUF)
#define EEPROM_SPICON1       (SPI2CON1)
#define EEPROM_SPICON1bits   (SPI2CON1bits)
#define EEPROM_SPICON2       (SPI2CON2)
#define EEPROM_SPISTAT       (SPI2STAT)
#define EEPROM_SPISTATbits   (SPI2STATbits)
#define EEPROM_SPICON1_CFG   (0x013e)  // SPI master, 8-bit mode, Rx sample midle
                                       // clock idle low, SCK = 10MHz (@ 40MIPS)
#define EEPROM_SPICON2_CFG   (0x0000)  // No framing
#define EEPROM_SPISTAT_CFG   (0x8000)  // Enable SPI interface

#endif // _EXP16_PIC24H_H

