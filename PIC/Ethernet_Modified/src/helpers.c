
#include "config.h"
#include "helpers.h"
#include "mac.h"


/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/

/******************************************************************************
 * Function:        BYTE hexatob(WORD_VAL AsciiChars)
 * PreCondition:    None
 * Input:           Two ascii bytes; each ranged '0'-'9', 'A'-'F', or
 *                  'a'-'f'
 * Output:          The resulting packed byte: 0x00-0xFF
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
BYTE hexatob(WORD_VAL AsciiChars)
{
    // Convert lowercase to uppercase
    if(AsciiChars.v[1] > 'F') AsciiChars.v[1] -= 'a'-'A';

    if(AsciiChars.v[0] > 'F') AsciiChars.v[0] -= 'a'-'A';

    // Convert 0-9, A-F to 0x0-0xF
    if(AsciiChars.v[1] > '9')
        AsciiChars.v[1] -= 'A' - 10;
    else
        AsciiChars.v[1] -= '0';

    if(AsciiChars.v[0] > '9')
        AsciiChars.v[0] -= 'A' - 10;
    else
        AsciiChars.v[0] -= '0';

    // Concatenate
    return (AsciiChars.v[1]<<4) |  AsciiChars.v[0];
}

/******************************************************************************
 * Function:        BYTE btohexa_high(BYTE b)
 * PreCondition:    None
 * Input:           One byte ranged 0x00-0xFF
 * Output:          An ascii byte (always uppercase) between '0'-'9' 
 *                  or 'A'-'F' that corresponds to the upper 4 bits of
 *                  the input byte.
 *                  ex: b = 0xAE, btohexa_high() returns 'A'
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
BYTE btohexa_high(BYTE b)
{
    b >>= 4;
    return (b>0x9) ? b+'A'-10:b+'0';
}

/******************************************************************************
 * Function:        BYTE btohexa_low(BYTE b)
 * PreCondition:    None
 * Input:           One byte ranged 0x00-0xFF
 * Output:          An ascii byte (always uppercase) between '0'-'9' 
 *                  or 'A'-'F' that corresponds to the lower 4 bits of
 *                  the input byte.
 *                  ex: b = 0xAE, btohexa_low() returns 'E'
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
BYTE btohexa_low(BYTE b)
{
    b &= 0x0F;
    return (b>9) ? b+'A'-10:b+'0';
}

WORD swaps(WORD v)
{
    WORD_VAL t;
    BYTE b;

    t.Val = v;
    b = t.v[1];
    t.v[1] = t.v[0];
    t.v[0] = b;

    return t.Val;
}

DWORD swapl(DWORD v)
{
    BYTE b;
    DWORD myV;
    DWORD_VAL *myP;

    myV = v;
    myP = (DWORD_VAL*)&myV;

    b = myP->v[3];
    myP->v[3] = myP->v[0];
    myP->v[0] = b;

    b = myP->v[2];
    myP->v[2] = myP->v[1];
    myP->v[1] = b;

    return myV;
}

WORD CalcIPChecksum(BYTE* buffer, WORD count)
{
    WORD i, *val;

    union
    {
        DWORD Val;
        struct
        {
            WORD_VAL LSB;
            WORD_VAL MSB;
        } words;
    } tempSum, sum;

    sum.Val = 0;

    i = count >> 1;
    val = (WORD *)buffer;

    while( i-- )
        sum.Val += *val++;

    if ( count & 1 ) sum.Val += *(BYTE *)val;

    tempSum.Val = sum.Val;

    while( (i = tempSum.words.MSB.Val) != 0u )
    {
        sum.words.MSB.Val = 0;
        sum.Val = (DWORD)sum.words.LSB.Val + (DWORD)i;
        tempSum.Val = sum.Val;
    }

    return (~sum.words.LSB.Val);
}

#if defined(STACK_USE_SW_CKSUM)
/******************************************************************************
 * Function:        WORD CalcIPBufferChecksum(WORD len)
 * PreCondition:    TCPInit() is already called     AND
 *                  MAC buffer pointer set to starting of buffer
 * Input:           len     - Total number of bytes to calculate
 *                            checksum for.
 * Output:          16-bit checksum as defined by rfc 793.
 * Side Effects:    None
 * Overview:        This function performs checksum calculation in
 *                  MAC buffer itself.
 * Note:            None
 ******************************************************************************/
WORD CalcIPBufferChecksum(WORD len)
{
    BOOL lbMSB;
    WORD_VAL checkSum;
    BYTE Checkbyte;

    lbMSB = TRUE;
    checkSum.Val = 0;

    while( len-- )
    {
        Checkbyte = MACGet();

        if ( !lbMSB )
        {
            if ( (checkSum.v[0] = Checkbyte+checkSum.v[0]) < Checkbyte)
            {
                if ( ++checkSum.v[1] == 0 ) checkSum.v[0]++;
            }
        }
        else
        {
            if ( (checkSum.v[1] = Checkbyte+checkSum.v[1]) < Checkbyte)
            {
                if ( ++checkSum.v[0] == 0 ) checkSum.v[1]++;
            }
        }

        lbMSB = !lbMSB;
    }

    checkSum.v[1] = ~checkSum.v[1];
    checkSum.v[0] = ~checkSum.v[0];

    return checkSum.Val;
}
#endif


