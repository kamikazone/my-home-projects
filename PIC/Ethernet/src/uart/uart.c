/******************************************************************************
 * UART Access routines for C18 and C30                                       *
 *============================================================================*
 *                                                                            *
 * The current source code file includes various functions to support serial  *
 * communications over the UART interface.                                    *
 *                                                                            *
 *                                                                            *
 * SOFTWARE LICENSE AGREEMENT                                                 *
 *                                                                            *
 * This software is owned by Microchip Technology Inc. ("Microchip") and is   *
 * supplied to you for use exclusively as described in the associated         *
 * software agreement.  This software is protected by software and other      *
 * intellectual property laws.  Any use in violation of the software license  *
 * may subject the user to criminal sanctions as well as civil liability.     *
 * Copyright 2006 Microchip Technology Inc.  All rights reserved.             *
 *                                                                            *
 * This software is provided "AS IS."  MICROCHIP DISCLAIMS ALL WARRANTIES,    *
 * EXPRESS, IMPLIED, STATUTORY OR OTHERWISE, NOT LIMITED TO MERCHANTABILITY,  *
 * FITNESS FOR A PARTICULAR PURPOSE, AND INFRINGEMENT. Microchip shall in no  *
 * event be liable for special, incidental, or consequential damages.         *
 *                                                                            *
 *- Version Log --------------------------------------------------------------*
 *   Date       Author        Comments                                        *
 *----------------------------------------------------------------------------*
 * 04/04/06 Howard Schlunder  Copied from dsPIC30 libraries                   *
 * 06/16/06 Howard Schlunder  Added PIC18                                     *
 * 04/25/07 Jorge Amodio      Cleanup and moved to its own directory          *
 * 06/21/07 Jorge Amodio      Renamed functions for C30 so UART module can    *
 *                            be selected on hardware configuration file      *
 *                            Now all functions use macro references mapped   *
 *                            to the corresponding registers in config.h      *
 ******************************************************************************/
#include "include/config.h"

#if 1//defined(STACK_USE_UART)
#include "include/uart.h"

/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/
unsigned char ReadStringUART(unsigned char *Dest, unsigned char BufferLen)
{
    unsigned char c, count = 0;

    while(BufferLen--)
    {
        *Dest = '\0';

        while(!DataRdyUART());
        c = ReadUART();

        if(c == '\r' || c == '\n')
            break;

        count++;
        *Dest++ = c;
    }

    return count;
}

#if defined(__C30__)
/******************************************************************************
 * Function Name     : putstrUART                                             *
 * Description       : This function puts the data string to be transmitted   *
 *                     into the transmit buffer (till NULL character)         *
 * Parameters        : unsigned int * address of the string buffer to be      *
 *                     transmitted                                            *
 * Return Value      : None                                                   *
 ******************************************************************************/
void putstrUART(unsigned int *buffer)
{
    char * temp_ptr = (char *) buffer;

    // transmit till NULL character is encountered
    if(UART_MODEbits.PDSEL == 3)        // check if TX is 8bits or 9bits
    {
        while(*buffer != '\0') 
        {
            while(UART_STAbits.UTXBF); // wait if the buffer is full

            UART_TXREG = *buffer++;    // transfer data word to TX reg
        }
    }
    else
    {
        while(*temp_ptr != '\0')
        {
            while(UART_STAbits.UTXBF);  // wait if the buffer is full

            UART_TXREG = *temp_ptr++;   // transfer data byte to TX reg
        }
    }
}

/******************************************************************************
 * Function Name     : getsUART                                               *
 * Description       : This function gets a string of data of specified length*
 *                     if available in the UxRXREG buffer into the buffer     *
 *                     specified.                                             *
 * Parameters        : unsigned int length the length expected                *
 *                     unsigned int *buffer  the received data to be          *
 *                                  recorded to this array                    *
 *                     unsigned int uart_data_wait timeout value              *
 * Return Value      : unsigned int number of data bytes yet to be received   *
 ******************************************************************************/
unsigned int getsUART(unsigned int length,unsigned int *buffer,
                       unsigned int uart_data_wait)
{
    unsigned int wait = 0;
    char *temp_ptr = (char *) buffer;

    while(length)                         // read till length is 0
    {
        while(!DataRdyUART())
        {
            if(wait < uart_data_wait)
                wait++ ;                  // wait for more data
            else
                return(length);           // Time out- Return words/bytes to be read
        }
        wait=0;
        if(UART_MODEbits.PDSEL == 3)         // check if TX/RX is 8bits or 9bits
            *buffer++ = UART_RXREG;          // data word from HW buffer to SW buffer
        else
            *temp_ptr++ = UART_RXREG & 0xFF; // data byte from HW buffer to SW buffer

        length--;
    }

    return(length);                       // number of data yet to be received i.e.,0
}

/******************************************************************************
 * Function Name     : DataRdyUart                                            *
 * Description       : This function checks whether there is any data         *
 *                     that can be read from the input buffer, by             *
 *                     checking URXDA bit                                     *
 * Parameters        : None                                                   *
 * Return Value      : char if any data available in buffer                   *
 ******************************************************************************/
char DataRdyUART(void)
{
    return(UART_STAbits.URXDA);
}

/******************************************************************************
 * Function Name     : BusyUART                                               *
 * Description       : This returns status whether the transmission           *
 *                     is in progress or not, by checking Status bit TRMT     *
 * Parameters        : None                                                   *
 * Return Value      : char info whether transmission is in progress          *
 ******************************************************************************/
char BusyUART(void)
{  
    return(!UART_STAbits.TRMT);
}

/******************************************************************************
 * Function Name     : ReadUART                                               *
 * Description       : This function returns the contents of UxRXREG buffer   *
 * Parameters        : None                                                   *
 * Return Value      : unsigned int value from UxRXREG receive buffer         *
 ******************************************************************************/
unsigned int ReadUART(void)
{
    if(UART_MODEbits.PDSEL == 3)
        return (UART_RXREG);
    else
        return (UART_RXREG & 0xFF);
}

/******************************************************************************
 * Function Name     : WriteUART                                              *
 * Description       : This function writes data into the UxTXREG,            *
 * Parameters        : unsigned int data the data to be written               *
 * Return Value      : None                                                   *
 ******************************************************************************/
void WriteUART(unsigned int data)
{
    if(UART_MODEbits.PDSEL == 3)
        UART_TXREG = data;
    else
        UART_TXREG = data & 0xFF;  
}


#elif defined(__18CXX)

char BusyUSART(void)
{
    return !UART_TXSTAbits.TRMT;
}

void CloseUSART(void)
{
    UART_RCSTA &= 0b01001111;  // Disable the receiver
    UART_TXSTAbits.TXEN = 0;   // and transmitter
    PIE1 &= 0b11001111;   // Disable both interrupts
}

char DataRdyUSART(void)
{
    if(UART_RCSTAbits.OERR)
    {
        UART_RCSTAbits.CREN = 0;
        UART_RCSTAbits.CREN = 1;
    }
  return PIR1bits.RCIF;
}

char ReadUSART(void)
{
    return UART_RCREG;         // Return the received data
}

void WriteUSART(char data)
{
    UART_TXREG = data;         // Write the data byte to the USART
}

void getsUSART(char *buffer, unsigned char len)
{
    char i;                    // Length counter
    unsigned char data;

    for(i=0;i<len;i++)         // Only retrieve len characters
    {
        while(!DataRdyUSART());// Wait for data to be received

        data = getcUART();     // Get a character from the USART
                               // and save in the string
        *buffer = data;
        buffer++;              // Increment the string pointer
    }
}

void putsUSART(char *data)
{
    do
    {  // Transmit a byte
        while(BusyUSART());

        putcUART(*data);

    } while( *data++ );
}

void putrsUSART(far rom char *data)
{
    do
    {  // Transmit a byte
        while(BusyUSART());

        putcUART(*data);

    } while( *data++ );
}

#endif

#endif  // STACK_USE_UART
