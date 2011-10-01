/******************************************************************************
 * Microchip MCP23S08 I/O Port Extender definitions                           *
 *============================================================================*
 *                                                                            *
 * See "mcp23s08.c" for details.                                              *
 *                                                                            *
 * SOFTWARE LICENSE AGREEMENT                                                 *
 *                                                                            *
 * This software is provided to you free of charge with the sole condition    *
 * of preserving this Copyright Notice. This software is provided "AS IS".    *
 * LJCV Eelectronics disclaims all warranties, express, implied, statutory or *
 * otherwise, not limited to merchantability, fitness for a particular        *
 * purporse, and infringement. LJCV Electronics shall in no event be liable   *
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
 * 02/11/07  Jorge Amodio     Initial Version                                 *
 ******************************************************************************/
#ifndef _MCP23S08_H
#define _MCP23S08_H

// MCP23S08 Commands
#define PXWRITE      0x40
#define PXREAD       0x41

// MC23S08 Register Addresses
#define PXIODIR      0x00              // I/O Direccion Register
#define PXIPOL       0x01              // Input Polarity Register
#define PXGPINTEN    0x02              // Interrupt-On-Change Control Register
#define PXDEFVAL     0x03              // Default compare for Interrupt-OC
#define PXINTCON     0x04              // Interupt Control Register
#define PXIOCON      0x05              // Configuration Register
#define PXGPPU       0x06              // Pull-Up Configuration Register
#define PXINTF       0x07              // Interrupt Flag Register
#define PXINTCAP     0x08              // Interupt Capture Register
#define PXGPIO       0x09              // General Purporse I/O Register
#define PXOLAT       0x0a              // Output Latch Register

// IOCON Configuration Register individual bits
#define PXIOCON_SEQOP      (1<<5)      // Sequential Operation mode
#define PXIOCON_DISSLW     (1<<4)      // SDA Slew Rate control bit
#define PXIOCON_ODR        (1<<2)      // Open drain INT output
#define PXIOCON_INTPOL     (1<<1)      // INT output polarity

#endif // _MCP23S08_H
