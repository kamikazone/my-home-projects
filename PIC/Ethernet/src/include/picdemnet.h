/******************************************************************************
 * Header file for Microchip's PICDem.Net Development Board                   *
 *============================================================================*
 *                                                                            *
 * This header file defines the hardware configuration and options for the    *
 * Microchip PICDEM.net Development Board.                                    *
 *                                                                            *
 * Detailed information about the PICDEM.net board can be obtained at:        *
 * http://www.microchip.com/                                                  *
 *                                                                            *
 * A detailed shcematic of the PICDEM.net board is available in Appendix A    *
 * of the PICDEM.net User's Guide, Microchip Document # DS39563B.             *
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
 * 07/05/07 Jorge Amodio      Replaced PORTx to LATx mappings for outputs     *
 ******************************************************************************/
#ifndef _PICDEMNET_H
#define _PICDEMNET_H

// Include the appropriate header file for the microcontroller family
#include <p18cxxx.h>

//*****************************************************************************
// Define Microcontroller Clock Frequency in Hertz
#define CPU_CLOCK          (19660800)
#define TCY_CLOCK          (CPU_CLOCK/4)

//*****************************************************************************
// GPIO Ports assignments, configuration and initial default value
// Define the direction for each Input/Output pin (0-Output, 1-Input) and
// the initial state at the application startup
//
// PORTA Direction and initial status
//                     +-------------- n/a OSC1
//                     |+------------- n/a OSC2
//                     ||+------------ RA5 = LCD E
//                     |||+----------- RA4 = LED D4, mapped to software LED2_IO
//                     ||||+---------- RA3 = LED D5, mapped to software LED1_IO
//                     |||||+--------- RA2 = LED D6, mapped to software LED0_IO
//                     ||||||+-------- RA1 = R25 10K Pot
//                     |||||||+------- RA0 = R24 10K Pot
#define INIT_TRISA  (0b00000011)
#define INIT_PORTA  (0b00000000)

// PORTB Direction and initial status
//                     +-------------- RB7 = Used as PGD for ICSP
//                     |+------------- RB6 = Used as PGC for ICSP
//                     ||+------------ RB5 = Pushbutton S3
//                     |||+----------- RB4 = RTL8019 SA0
//                     ||||+---------- RB3 = RTL8019 SA1
//                     |||||+--------- RB2 = RTL8019 SA2
//                     ||||||+-------- RB1 = RTL8019 SA3
//                     |||||||+------- RB0 = RTL8019 SA4
#define INIT_TRISB  (0b00100000)
#define INIT_PORTB  (0b00100000)

// PORTC Direction and initial status
//                     +-------------- RC7 = Used as RX by USART
//                     |+------------- RC6 = Used as TX by USART
//                     ||+------------ RC5 = Used as CTS for USART
//                     |||+----------- RC4 = Used as SDA for I2C interface
//                     ||||+---------- RC3 = Used as SCL for I2C interface
//                     |||||+--------- RC2 = Used as RTS for USART
//                     ||||||+-------- RC1 = n/c
//                     |||||||+------- RC0 = n/c
#define INIT_TRISC  (0b10000100)
#define INIT_PORTC  (0b11100000)

// PORTD Direction and initial status
//                     +-------------- RD7 = RTL8019 SD7
//                     |+------------- RD6 = RTL8019 SD6
//                     ||+------------ RD5 = RTL8019 SD5 & LCD R/W
//                     |||+----------- RD4 = RTL8019 SD4 & LCD RS
//                     ||||+---------- RD3 = RTL8019 SD3 & LCD DB7
//                     |||||+--------- RD2 = RTL8019 SD2 & LCD DB6
//                     ||||||+-------- RD1 = RTL8019 SD1 & LCD DB5
//                     |||||||+------- RD0 = RTL8019 SD0 & LCD DB4
#define INIT_TRISD  (0b00000000)
#define INIT_PORTD  (0b00000000)

// PORTE Direction and initial status
//                          +--------- RE2 = RTL8019 RESET
//                          |+-------- RE1 = RTL8019 IOW
//                          ||+------- RE0 = RTL8019 IOR
#define INIT_TRISE  (0b00000000)
#define INIT_PORTE  (0b00000011)

//*****************************************************************************
// Initialization values for various registers
//
#define INIT_ADCON0 (0b00000001)     // ADON=1, Channel 0
#define INIT_ADCON1 (0b00001101)     // RA0 and RA1 analog inputs
#define INIT_ADCON2 (0b10111110)     // Right justify, 20TAD ACQ time, Fosc/64 (~21.0kHz)

//*****************************************************************************
// Available LEDs and switches macro name definitions for application use
//
#define LED0_IO              (LATAbits.LATA4)
#define LED1_IO              (LATAbits.LATA3)
#define LED2_IO              (LATAbits.LATA2)
#define LED3_IO              (LATAbits.LATA2)  // No LED3 map to LED2
#define LED4_IO              (LATAbits.LATA2)  // No LED4 map to LED2
#define LED5_IO              (LATAbits.LATA2)  // No LED5 map to LED2
#define LED6_IO              (LATAbits.LATA2)  // No LED6 map to LED2
#define LED7_IO              (LATAbits.LATA2)  // No LED7 map to LED2

#define BUTTON0_IO           (PORTBbits.RB5)
#define BUTTON1_IO           (PORTBbits.RB1)   // No BUTTON1 map to BUTTON0
#define BUTTON2_IO           (PORTBbits.RB1)   // No BUTTON2 map to BUTTON0
#define BUTTON3_IO           (PORTBbits.RB1)   // No BUTTON3 map to BUTTON0

//*****************************************************************************
// LCD Module features and configuration
//
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
#define LCD_DATA_TRIS        (((volatile LCD_DATA*)&TRISD)->data)
#define LCD_RW_TRIS          (TRISDbits.TRISD5)
#define LCD_RW_IO            (LATDbits.LATD5)
#define LCD_RS_TRIS          (TRISDbits.TRISD4)
#define LCD_RS_IO            (LATDbits.LATD4)
#define LCD_E_IO             (LATAbits.LATA5)

//*****************************************************************************
// Definitions for Realtek RTL8019AS Ethernet Controller interface
//
#define USE_RTL8019AS
#define NIC_RESET_IO         (LATEbits.LATE2)
#define NIC_IOW_IO           (LATEbits.LATE1)
#define NIC_IOR_IO           (LATEbits.LATE0)
#define NIC_ADDR_IO          (LATB)
#define NIC_DATA_TRIS        (TRISD)
#define NIC_DATA_IO          (PORTD)

//*****************************************************************************
// Definitions for 24LC256, 24LC512, 24FC256, 24FC512
//
#define USE_24FC512
#define EEPROM_SCL_TRIS      (TRISCbits.TRISC3)
#define EEPROM_SDA_TRIS      (TRISCbits.TRISC4)
#define EEPROM_SPI_IF        (PIR1bits.SSPIF)
#define EEPROM_SSPBUF        (SSPBUF)
#define EEPROM_SPICON1       (SSPCON1)
#define EEPROM_SPICON1bits   (SSPCON1bits)
#define EEPROM_SPICON2       (SSPCON2)
#define EEPROM_SPICON2bits   (SSPCON2bits)
#define EEPROM_SPISTAT       (SSPSTAT)
#define EEPROM_SPISTATbits   (SSPSTATbits)

#endif // _PICDEMNET_H

