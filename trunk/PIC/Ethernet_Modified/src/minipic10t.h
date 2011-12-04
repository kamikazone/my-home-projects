
#ifndef _MINIPIC10T_H
#define _MINIPIC10T_H

#include <p18cxxx.h>

#define CPU_CLOCK          (25000000)
#define TCY_CLOCK          (CPU_CLOCK/8)

#define INIT_TRISA  (0b00000001)
#define INIT_PORTA  (0b00000000)
#define INIT_TRISB  (0b00000001)
#define INIT_PORTB  (0b00010000)
#define INIT_TRISC  (0b10010000)
#define INIT_PORTC  (0b11000000)

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
