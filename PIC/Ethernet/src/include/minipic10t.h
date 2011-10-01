/******************************************************************************
 * Header file for Jorge Amodio's miniPIC10T Project                          *
 *============================================================================*
 *                                                                            *
 * This header file defines the hardware configuration and options for the    *
 * "miniPIC10T - Internetworking with Microcontrollers Project" published by  *
 * Jorge Amodio.                                                              *
 *                                                                            *
 * Detailed information about this project including schematics can be        *
 * obtained at: http://www.ljcv.net/projects/minipic10t/                      *
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
 * 07/05/07 Jorge Amodio      Replaced PORTx to LATx mappings for outputs     *
 ******************************************************************************/
#ifndef _MINIPIC10T_H
#define _MINIPIC10T_H

// Include the appropriate header file for the microcontroller family
#include <p18cxxx.h>

//*****************************************************************************
// Define Microcontroller Clock Frequency in Hertz
//#define CPU_CLOCK          (25000000)
#define CPU_CLOCK          (25000000)
//#define TCY_CLOCK          (CPU_CLOCK/4)
#define TCY_CLOCK          (CPU_CLOCK/8)

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
//                     |||||+--------- RA2 = n/c
//                     ||||||+-------- RA1 = n/c
//                     |||||||+------- RA0 = n/c
#define INIT_TRISA  (0b00000001)
#define INIT_PORTA  (0b00000000)

// PORTB Direction and initial status
//                     +-------------- RB7 = Used as PGD for ICSP
//                     |+------------- RB6 = Used as PGC for ICSP
//                     ||+------------ RB5 = n/c
//                     |||+----------- RB4 = ENC28J60 CS
//                     ||||+---------- RB3 = n/c
//                     |||||+--------- RB2 = n/c
//                     ||||||+-------- RB1 = n/c
//                     |||||||+------- RB0 = S2 Push Button, mapped to BUTTON0_IO
#define INIT_TRISB  (0b00000001)
#define INIT_PORTB  (0b00010000)

// PORTC Direction and initial status
//                     +-------------- RC7 = (Used as RX by USART)
//                     |+------------- RC6 = (Used as TX by USART)
//                     ||+------------ RC5 = Used as SDO for SPI interface
//                     |||+----------- RC4 = Used as SDI for SPI interface
//                     ||||+---------- RC3 = Used as SCK for SPI interface
//                     |||||+--------- RC2 = n/c
//                     ||||||+-------- RC1 = n/c
//                     |||||||+------- RC0 = n/c
#define INIT_TRISC  (0b10010000)
#define INIT_PORTC  (0b11000000)


//*****************************************************************************
// Initialization values for various registers
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
#define LED5_IO              (LATAbits.LATA5)  // No LED5 map to LED4
#define LED6_IO              (LATAbits.LATA5)  // No LED6 map to LED2
#define LED7_IO              (LATAbits.LATA5)  // No LED7 map to LED2

#define BUTTON0_IO           (PORTAbits.RA0)
#define BUTTON1_IO           (PORTBbits.RB0)   // No BUTTON1 map to BUTTON0
#define BUTTON2_IO           (PORTBbits.RB0)   // No BUTTON2 map to BUTTON0
#define BUTTON3_IO           (PORTBbits.RB0)   // No BUTTON3 map to BUTTON0


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

#endif // _MINIPIC10T_H
