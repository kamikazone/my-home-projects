/******************************************************************************
 * Header file for Microchip's PICDEM.net 2 Development Board                 *
 *============================================================================*
 *                                                                            *
 * This header file defines the hardware configuration and options for the    *
 * Microchip PICDEM.net 2 Development Board featuring the new PIC18F97J60     *
 * family of microcontrollers with internal ethernet peripheral module.       *
 *                                                                            *
 * Note: The current version (3.75.6) of the modified TCP/IP Stack has not    *
 * been tested with the external stand alone ENC28J60 controller for this     *
 * development board.                                                         *
 *                                                                            *
 * Detailed information about the PICDEM.net 2 board can be obtained at:      *
 * http://www.microchip.com/                                                  *
 *                                                                            *
 * A detailed shcematic of the PICDEM.net board is available in Appendix A    *
 * of the PICDEM.net 2 User's Guide, Microchip Document # DS51623A            *
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
 * 07/03/07 Jorge Amodio      Initial Version                                 *
 * 07/05/07 Jorge Amodio      Replaced PORTx to LATx mappings for outputs     *
 ******************************************************************************/
#ifndef _PICDEMNET2_H
#define _PICDEMNET2_H

// Include the appropriate header file for the microcontroller family
#include <p18f97j60.h>

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
//                     ||||+---------- RA3 = AN3 TC1047 Vout
//                     |||||+--------- RA2 = AN2 R38 10K Pot
//                     ||||||+-------- RA1 = (Ethernet module LEDB)
//                     |||||||+------- RA0 = (Ethernet module LEDA)
#define INIT_TRISA  (0b00001100)
#define INIT_PORTA  (0b00000000)

// PORTB Direction and initial status
//                     +-------------- RB7 = Used as PGD for ICSP
//                     |+------------- RB6 = Used as PGC for ICSP
//                     ||+------------ RB5 = n/c
//                     |||+----------- RB4 = n/c
//                     ||||+---------- RB3 = Pushbutton S5
//                     |||||+--------- RB2 = Pushbutton S4
//                     ||||||+-------- RB1 = Pushbutton S3
//                     |||||||+------- RB0 = Pushbutton S2 (ENC28J60 INT via JP9)
#define INIT_TRISB  (0b01001111)
#define INIT_PORTB  (0b00000000)

// PORTC Direction and initial status
//                     +-------------- RC7 = Used as RX1 by USART
//                     |+------------- RC6 = Used as TX1 by USART
//                     ||+------------ RC5 = Used as SDO1
//                     |||+----------- RC4 = Used as SDI1
//                     ||||+---------- RC3 = Used as SCK1
//                     |||||+--------- RC2 = n/c
//                     ||||||+-------- RC1 = T1OSCI 32KHz xtal
//                     |||||||+------- RC0 = T1OSCO 32KHz xtal
#define INIT_TRISC  (0b10010000)
#define INIT_PORTC  (0b11000000)

// PORTD Direction and initial status
//                     +-------------- RD7 = 25LC256 (U4) EEPROM CS
//                     |+------------- RD6 = n/c
//                     ||+------------ RD5 = n/c
//                     |||+----------- RD4 = n/c
//                     ||||+---------- RD3 = ENC28J60 CS
//                     |||||+--------- RD2 = (ENC28J60 RESET via JP5)
//                     ||||||+-------- RD1 = n/c
//                     |||||||+------- RD0 = n/c
#define INIT_TRISD  (0b00000000)
#define INIT_PORTD  (0b10001000)

// PORTE Direction and initial status
//                     +-------------- RE7 = LCD DB7
//                     |+------------- RE6 = LCD DB6
//                     ||+------------ RE5 = LCD DB5
//                     |||+----------- RE4 = LCD DB4
//                     ||||+---------- RE3 = LCD DB3
//                     |||||+--------- RE2 = LCD DB2
//                     ||||||+-------- RE1 = LCD DB1
//                     |||||||+------- RE0 = LCD DB0
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
#define INIT_PORTF  (0b00000011)

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
#define INIT_PORTG  (0b00000011)

// PORTH Direction and initial status
//                     +-------------- RH7 = (n/c J3-3)
//                     |+------------- RH6 = (n/c J3-2)
//                     ||+------------ RH5 = n/c
//                     |||+----------- RH4 = n/c
//                     ||||+---------- RH3 = n/c
//                     |||||+--------- RH2 = LCD RS
//                     ||||||+-------- RH1 = LCD R/W
//                     |||||||+------- RH0 = LCD E
#define INIT_TRISH  (0b00000000)
#define INIT_PORTH  (0b00000000)

// PORTJ Direction and initial status
//                     +-------------- RJ7 = LED D1
//                     |+------------- RJ6 = LED D2
//                     ||+------------ RJ5 = LED D3
//                     |||+----------- RJ4 = LED D4
//                     ||||+---------- RJ3 = LED D5
//                     |||||+--------- RJ2 = LED D6
//                     ||||||+-------- RJ1 = LED D7
//                     |||||||+------- RJ0 = LED D8
#define INIT_TRISJ  (0b00000000)
#define INIT_PORTJ  (0b00000000)

//*****************************************************************************
// Initialization values for various registers
//
#define INIT_ADCON0 (0b00000001)     // ADON=1, Channel 0
#define INIT_ADCON1 (0b00001101)     // RA0 and RA1 analog inputs
#define INIT_ADCON2 (0b10111110)     // Right justify, 20TAD ACQ time, Fosc/64 (~21.0kHz)

//*****************************************************************************
// Available LEDs and switches macro name definitions for application use
//
#define LED0_IO              (LATJbits.LATJ0)
#define LED1_IO              (LATJbits.LATJ1)
#define LED2_IO              (LATJbits.LATJ2)
#define LED3_IO              (LATJbits.LATJ3)
#define LED4_IO              (LATJbits.LATJ4)
#define LED5_IO              (LATJbits.LATJ5)
#define LED6_IO              (LATJbits.LATJ6)
#define LED7_IO              (LATJbits.LATJ7)

#define BUTTON0_IO           (PORTBbits.RB3)
#define BUTTON1_IO           (PORTBbits.RB2)
#define BUTTON2_IO           (PORTBbits.RB1)
#define BUTTON3_IO           (PORTBbits.RB0)

//*****************************************************************************
// Select UART Module Number for RS232 Interface
// Valid values are 1 for UART1 and 2 for UART2
//
#define UART_NO 1

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

#define LCD_DATA_IO          (LATE)
#define LCD_DATA_TRIS        (TRISE)
#define LCD_RW_TRIS          (TRISHbits.TRISH1)
#define LCD_RW_IO            (LATHbits.LATH1)
#define LCD_RS_TRIS          (TRISHbits.TRISH2)
#define LCD_RS_IO            (LATHbits.LATH2)
#define LCD_E_IO             (LATHbits.LATH0)


//*****************************************************************************
// Definitions for ENC28J60 Ethernet Controller interface
// If you define the ENC28J60 macro the code will compile the driver for
// the standalone ethernet interface instead for the internal ethernet
// peripheral module in the PIC18F97J60
//
//#define USE_ENC28J60
#define ENC_RST_IO           (LATDbits.LATD2)
#define ENC_CS_IO            (LATDbits.LATD3)
#define ENC_SPI_IF           (PIR1bits.SSPIF)
#define ENC_SSPBUF           (SSP1BUF)
#define ENC_SPISTAT          (SSP1STAT)
#define ENC_SPISTATbits      (SSP1STATbits)
#define ENC_SPICON1          (SSP1CON1)
#define ENC_SPICON1bits      (SSP1CON1bits)
#define ENC_SPIEN            (SSP1CON1bits.SSPEN)
#define ENC_SPICON1_CFG      (0x20)  // SPI master, SCK=Fosc/4, idle low
#define ENC_SPISTAT_CFG      (0x40)  // Tx on transition from active to idle clock
                                     // Rx sampe at middle of data output time
//#define ENC_DEBUG
//#define ENC_SAVE_SPI_CFG


//*****************************************************************************
// Definitions for 25LC256
//
#define USE_25LC256
#define EEPROM_CS_IO         (LATDbits.LATD7)
#define EEPROM_SPI_IF        (PIR1bits.SSPIF)
#define EEPROM_SSPBUF        (SSP1BUF)
#define EEPROM_SPICON1       (SSP1CON1)
#define EEPROM_SPISTAT       (SSP1STAT)
#define EEPROM_SPISTATbits   (SSP1STATbits)
#define EEPROM_SPIEN         (SSP1CON1bits.SSPEN)
#define EEPROM_SPICON1_CFG   (0x21)      // SCK = Fosc/16
#define EEPROM_SPISTAT_CFG   (0x40)
//#define EEPROM_SAVE_SPI_CFG

#endif // _PICDEMNET2_H

