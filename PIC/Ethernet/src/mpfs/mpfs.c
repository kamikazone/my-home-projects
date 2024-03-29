/******************************************************************************
 * Microchip simple File System Implementation                                *
 *============================================================================*
 *                                                                            *
 * The current source code file implements a basic file system structure for  *
 * storage of html documents and associated files in an external serial       *
 * EEPROM or program memory.                                                  *
 *                                                                            *
 * The file system image must be generated with the MPFS.EXE utility that is  *
 * available in the tools directory. Depending on the type of memory you may  *
 * need to use the /l or /ll options to generate an image with 24 or 32 bit   *
 * addressing. For images to be stored in program memory a C language image   *
 * of the MPFS structure must be included in the file list at compilation     *
 * time, and modification of this image are not supported during runtime.     *
 * If the image changes you must generate a new C image and compile the code  *
 * again.                                                                     *
 *                                                                            *
 * For storage in an external EEPROM memory, the image can be uploaded using  *
 * FTP (of enabled) or via the serial configuration menu using XMODEM protcol.*
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
 * 08/14/01 Nilesh Rajbharti  Original (Rev 1.0)                              *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 03/31/05 Howard Schlunder  Changed MPFS_ENTRY and mpfs_Flags for C30       *
 * 02/25/07 Jorge Amodio      Replaced file name matching code                *
 * 03/30/07 Jorge Amodio      More cleanup                                    *
 * 04/25/07 Jorge Amodio      Moved to it's own directory as a module         *
 * 06/26/07 Jorge Amodio      Removed casts from mem manipulation functions   *
 *                            and compatibility with latest (3.12) C18 fix    *
 *                            Correct casts are introduced in config.h        *
 ******************************************************************************/
#define _MPFS_C
#include "include/config.h"

#if defined(MPFS_USE_EEPROM) || defined(MPFS_USE_PGRM)
#include "mpfs/include/mpfs.h"
#include "net/include/helpers.h"

#if defined(MPFS_USE_EEPROM)
    #include "eeprom/include/xeeprom.h"
#endif


/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/

// This file system supports short file names i.e. 8 + 3.
#define MAX_FILE_NAME_LEN  (12u)

// MPFS Structure:
// MPFS_Start:
//      <MPFS_DATA><Address1><FileName1>
//      <MPFS_DATA><Address2><FileName2>
//      ...
//      <MPFS_ETX><Addressn><FileNamen>
// Address1:
//      <Data1>[<Data2>...<Datan>]<MPFS_ETX><MPFS_INVALID>
//      ...
//
// Note: If File data contains either MPFS_DLE or MPFS_ETX extra MPFS_DLE is
// stuffed before that byte
typedef struct  _MPFS_ENTRY
{
    BYTE Flag __attribute__((__packed__));
    MPFS Address __attribute__((__packed__));
    BYTE Name[MAX_FILE_NAME_LEN] __attribute__((__packed__));
} MPFS_ENTRY;

static union
{
    struct
    {
       BYTE bNotAvailable : 1;
    } bits;
    BYTE Val;
} mpfsFlags;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define MPFS_DATA          (0x00u)
#define MPFS_DELETED       (0x01u)
#define MPFS_DLE           (0x03u)
#define MPFS_ETX           (0x04u)


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
#if defined(MPFS_USE_PGRM)
    // An address where MPFS data starts in program memory.
    extern MPFS MPFS_Start;
#else
    #define MPFS_Start     MPFS_RESERVE_BLOCK
#endif

BYTE mpfsOpenCount;
MPFS _currentHandle;
MPFS _currentFile;
BYTE _currentCount;


/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/

/******************************************************************************
 * Function:        BOOL MPFSInit(void)
 * PreCondition:    None
 * Input:           None
 * Output:          TRUE, if MPFS Storage access is initialized and
 *                          MPFS is ready to be used.
 *                  FALSE otherwise
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
BOOL MPFSInit(void)
{
    mpfsOpenCount = 0;
    mpfsFlags.Val = 0;
    return TRUE;
}

/******************************************************************************
 * Function:        MPFS MPFSOpen(BYTE* file)
 * PreCondition:    None
 * Input:           file        - NULL terminated file name.
 * Output:          A handle if file is found
 *                  MPFS_INVALID if file is not found.
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
MPFS MPFSOpen(BYTE* file)
{
    MPFS_ENTRY entry;
    MPFS FAT;
    BYTE i;
    BOOL match;

    if( mpfsFlags.bits.bNotAvailable )
        return MPFS_NOT_AVAILABLE;

#if defined(MPFS_USE_PGRM)
    FAT = (MPFS)&MPFS_Start;
#else
    FAT = MPFS_Start;
#endif

    // If string is empty, do not attempt to find it in FAT.
    if ( *file == '\0' )
        return MPFS_INVALID;

    file = (BYTE*)strupr((char*)file);

    while(1)
    {

#if defined(MPFS_USE_PGRM)
        // Bring current FAT entry into RAM.
        memcpypgm2ram( &entry, FAT, sizeof(entry));
#else
        XEEReadArray(EEPROM_CONTROL, FAT, (BYTE*)&entry, sizeof(entry));
#endif

        // Make sure that it is a valid entry.
        if (entry.Flag == MPFS_DATA)
        {
            i = 0;
            match = TRUE;
             
            while ( i < MAX_FILE_NAME_LEN )
            {
                if ( entry.Name[i] == ' ' || entry.Name[i] == MPFS_ETX )
                    break;
                 
                if ( file[i] != entry.Name[i] ) {
                    match = FALSE;
                    break;
                }
                i++;
            }

            if ( match && i > 0 ) 
            {
                _currentFile = (MPFS)entry.Address;
                mpfsOpenCount++;
                return entry.Address;
            } else
                FAT += sizeof(entry);      // No match.  Try next entry

        }
        else if ( entry.Flag == MPFS_ETX )
        {
            if ( entry.Address != (MPFS)MPFS_INVALID )
                FAT = (MPFS)entry.Address;
            else
                break;
        }
        else
            return (MPFS)MPFS_INVALID;
    }
    return (MPFS)MPFS_INVALID;
}

/******************************************************************************
 * Function:        void MPFSClose(void)
 * PreCondition:    None
 * Input:           handle      - File handle to be closed
 * Output:          None
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ******************************************************************************/
void MPFSClose(void)
{
    _currentCount = 0;
    mpfsFlags.bits.bNotAvailable = FALSE;

    if ( mpfsOpenCount ) mpfsOpenCount--;
}

/******************************************************************************
 * Function:        BYTE MPFSGet(void)
 * PreCondition:    MPFSOpen() != MPFS_INVALID &&
 *                  MPFSGetBegin() == TRUE
 * Input:           None
 * Output:          Data byte from current address.
 * Side Effects:    None
 * Overview:        Reads a byte from current address.
 * Note:            Caller must call MPFSIsEOF() to check for end of
 *                  file condition
 ******************************************************************************/
BYTE MPFSGet(void)
{
    BYTE t;
    
#if defined(MPFS_USE_PGRM)
    t = (BYTE)*_currentHandle;
#else
    t = XEERead();
#endif

    _currentHandle++;

    if ( t == MPFS_DLE )
    {

#if defined(MPFS_USE_PGRM)
        t = (BYTE)*_currentHandle;
#else
        t = XEERead();
#endif

        _currentHandle++;
    }
    else if ( t == MPFS_ETX )
    {
        _currentHandle = MPFS_INVALID;
    }

    return t;
}

/******************************************************************************
 * Function:        MPFS MPFSFormat(void)
 * PreCondition:    None
 * Input:           None
 * Output:          A valid MPFS handle that can be used for MPFSPut
 * Side Effects:    None
 * Overview:        Prepares MPFS image to get re-written
 *                  Declares MPFS as in use.
 * Note:            MPFS will be unaccessible until MPFSClose is
 *                  called.
 ******************************************************************************/
MPFS MPFSFormat(void)
{
    mpfsFlags.bits.bNotAvailable = TRUE;

    return (MPFS)MPFS_RESERVE_BLOCK;
}

/******************************************************************************
 * Function:        BOOL MPFSPut(BYTE b)
 * PreCondition:    MPFSFormat() or MPFSCreate() must be called
 *                  MPFSPutBegin() is already called.
 * Input:           b       - data to write.
 * Output:          TRUE if successfull
 *                  !TRUE if failed.
 * Side Effects:    Original MPFS handle is no longer valid.
 *                  Updated MPFS handle must be obtained by calling
 *                  MPFSPutEnd().
 * Overview:        None
 * Note:            Actual write may not get started until internal
 *                  write page is full.  To ensure that previously
 *                  data gets written, caller must call MPFSPutEnd()
 *                  after last call to MPFSPut().
 ******************************************************************************/
BOOL MPFSPut(BYTE b)
{
#if defined(MPFS_USE_EEPROM)
    if ( XEEWrite(b) )
        return FALSE;

    _currentCount++;
    _currentHandle++;

    if ( _currentCount >= MPFS_WRITE_PAGE_SIZE )
    {
        MPFSPutEnd();
        XEEBeginWrite(EEPROM_CONTROL, _currentHandle);
    }
#endif
    return TRUE;
}

/******************************************************************************
 * Function:        MPFS MPFSPutEnd(void)
 * PreCondition:    MPFSPutBegin() is already called.
 * Input:           None
 * Output:          Up-to-date MPFS handle
 * Side Effects:    Original MPFS handle is no longer valid.
 *                  Updated MPFS handle must be obtained by calling
 *                  MPFSPutEnd().
 * Overview:        None
 * Note:            Actual write may not get started until internal
 *                  write page is full.  To ensure that previously
 *                  data gets written, caller must call MPFSPutEnd()
 *                  after last call to MPFSPut().
 ******************************************************************************/
MPFS MPFSPutEnd(void)
{
#if defined(MPFS_USE_EEPROM)
    _currentCount = 0;
    XEEEndWrite();
    while( XEEIsBusy(EEPROM_CONTROL) );
#endif

    return _currentHandle;
}

/******************************************************************************
 * Function:        MPFS MPFSSeek(MPFS_OFFSET offset)
 * PreCondition:    MPFSGetBegin() is already called.
 * Input:           offset      - Offset from current pointer
 * Output:          New MPFS handle located to given offset
 * Side Effects:    None.
 * Overview:        None
 * Note:            None.
 ******************************************************************************/
MPFS MPFSSeek(MPFS_OFFSET offset)
{
    WORD i = 0;

    MPFSGetBegin(_currentFile);

    while(i++ != offset)
        MPFSGet();

    MPFSGetEnd();

    return _currentHandle;
}

#if defined(MPFS_USE_EEPROM)
/******************************************************************************
 * Function:        BOOL MPFSGetBegin(MPFS handle)
 * PreCondition:    MPFSOpen() != MPFS_INVALID &&
 * Input:           handle      - handle of file that is to be read
 * Output:          TRUE if successful
 *                  !TRUE otherwise
 * Side Effects:    None
 * Overview:        Prepares MPFS storage media for subsequent reads.
 * Note:            None
 ******************************************************************************/
BOOL MPFSGetBegin(MPFS handle)
{
    _currentHandle = handle;

    return (XEEBeginRead(EEPROM_CONTROL, handle) == XEE_SUCCESS);
}

/******************************************************************************
 * Function:        MPFS MPFSGetEnd(void)
 * PreCondition:    MPFSOpen() != MPFS_INVALID &&
 *                  MPFSGetBegin() = TRUE
 * Input:           None
 * Output:          Current mpfs handle.
 * Side Effects:    None
 * Overview:        Ends on-going read cycle.
 *                  MPFS handle that is returned must be used
 *                  for subsequent begin gets..
 * Note:            None
 ******************************************************************************/
MPFS MPFSGetEnd(void)
{
    XEEEndRead();

    return _currentHandle;
}

/******************************************************************************
 * Function:        BOOL MPFSPutBegin(MPFS handle)
 * PreCondition:    MPFSInit() and MPFSFormat() are already called.
 * Input:           handle  - handle to where put to begin
 * Output:          TRUE if successful
 *                  !TRUE otherwise
 * Side Effects:    None
 * Overview:        Prepares MPFS image to get re-written
 * Note:            MPFS will be unaccessible until MPFSClose is
 *                  called.
 ******************************************************************************/
BOOL MPFSPutBegin(MPFS handle)
{
    //_currentCount = 0;
    _currentHandle = handle;
    _currentCount = (BYTE)handle;
    _currentCount &= (MPFS_WRITE_PAGE_SIZE-1);

    return (XEEBeginWrite(EEPROM_CONTROL, handle) == XEE_SUCCESS);
}
#endif  // MPFS_USE_EEPROM

#endif  // MPFS_USE_EEPROM || MPFS_USE_PRGM

