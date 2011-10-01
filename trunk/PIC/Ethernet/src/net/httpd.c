/******************************************************************************
 * HTTP Server Module for Microchip TCP/IP Stack                              *
 *============================================================================*
 *                                                                            *
 * This source code file includes the implementation of a basic HTTP server.  *
 *                                                                            *
 * The main application has to implement the HTTPGetVar() and HTTPExecCmd()   *
 * functions to provide command execution and variable replacement for        *
 * dynamic pages.                                                             *
 *                                                                            *
 * The HTTP server requires a memory storage option defined in the config     *
 * file, the only options supported in the current version are                *
 * MPFS_USE_EEPROM for storage in an external serial EEPROM and MPFS_USE_PGRM *
 * for storage in program memory. For the last option the C language image of *
 * the MPFS structure must be included in the file list at compilation time,  *
 * and modification of this image are not supported during runtime. If the    *
 * image changes you must generate a new C image and compile the code again.  *
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
 * 08/14/01 Nilesh Rajbharti  Original                                        *
 * 09/12/01 Nilesh Rajbharti  Released (Rev 1.0)                              *
 * 02/09/02 Nilesh Rajbharti  Cleanup                                         *
 * 05/22/02 Nilesh Rajbharti  Rev 2.0 (See version.log for detail)            *
 * 07/09/02 Nilesh Rajbharti  Rev 2.1 (Fixed HTTPParse bug)                   *
 * 02/09/05 Howard Schlunder  Fixed variable substitution parsing             *
 *                            (uses hex now)                                  *
 * 04/25/04 Jorge Amodio      More cleanup, file name changed to httpd.c      *
 * 06/26/07 Jorge Amodio      Removed casts from mem manipulation functions   *
 *                            and compatibility with latest (3.12) C18 fix    *
 *                            Correct casts are introduced in config.h        *
 ******************************************************************************/
#include "include/config.h"

#if defined(STACK_USE_HTTP_SERVER)
#include "net/include/stacktsk.h"
#include "net/include/http.h"
#include "net/include/tcp.h"
#include "net/include/helpers.h"
#include "mpfs/include/mpfs.h"

/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
#define FILE_EXT_LEN    (3u)
typedef struct _FILE_TYPES
{
    char fileExt[FILE_EXT_LEN+1];
} FILE_TYPES;

typedef struct _HTTP_CONTENT
{
    ROM char typeString[20];
} HTTP_CONTENT;

// HTTP FSM states for each connection.
typedef enum _SM_HTTP
{
    SM_HTTP_IDLE = 0,
    SM_HTTP_GET,
    SM_HTTP_NOT_FOUND,
    SM_HTTP_GET_READ,
    SM_HTTP_GET_PASS,
    SM_HTTP_GET_DLE,
    SM_HTTP_GET_HANDLE,
    SM_HTTP_GET_HANDLE_NEXT,
    SM_HTTP_GET_VAR,
    SM_HTTP_DISCONNECT,
    SM_HTTP_DISCONNECT_WAIT,
    SM_HTTP_HEADER,
    SM_HTTP_DISCARD
} SM_HTTP;

// Supported HTTP Commands
typedef enum _HTTP_COMMAND
{
    HTTP_GET,
    HTTP_POST,
    HTTP_NOT_SUPPORTED,
    HTTP_INVALID_COMMAND
} HTTP_COMMAND;

// HTTP Connection Info - one for each connection.
typedef struct _HTTP_INFO
{
    TCP_SOCKET socket;
    MPFS file;
    SM_HTTP smHTTP;
    BYTE smHTTPGet;
    WORD VarRef;
    BYTE bProcess;
    BYTE Variable;
    BYTE fileType;
} HTTP_INFO;
typedef BYTE HTTP_HANDLE;

typedef enum
{
    HTTP_NOT_FOUND,
    HTTP_NOT_AVAILABLE
} HTTP_MESSAGES;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
// Each dynamic variable within a CGI file should be preceeded with this character.
#define HTTP_VAR_ESC_CHAR       '%'
#define HTTP_DYNAMIC_FILE_TYPE  (HTTP_CGI)

// HTTP File Types
#define HTTP_TXT        (0u)
#define HTTP_HTML       (1u)
#define HTTP_CGI        (2u)
#define HTTP_XML        (3u)
#define HTTP_GIF        (4u)
#define HTTP_PNG        (5u)
#define HTTP_JPG        (6u)
#define HTTP_JAVA       (7u)
#define HTTP_WAV        (8u)
#define HTTP_UNKNOWN    (9u)

// Maximum nuber of arguments supported by this HTTP Server.
#define MAX_HTTP_ARGS       (11)

// Maximum HTML Command String length.
#define MAX_HTML_CMD_LEN    (100)

/******************************************************************************
 * Local & external variables and constants for this module                   *
 ******************************************************************************/
// Each entry in this structure must be in UPPER case.
// Order of these entries must match with those defined by "HTTP File Types" defines.
static ROM FILE_TYPES httpFiles[] =
{
    { "TXT" },          // HTTP_TXT
    { "HTM" },          // HTTP_HTML
    { "CGI" },          // HTTP_CGI
    { "XML" },          // HTTP_XML
    { "GIF" },          // HTTP_GIF
    { "PNG" },          // HTTP_PNG
    { "JPG" },          // HTTP_JPG
    { "CLA" },          // HTTP_JAVA
    { "WAV" },          // HTTP_WAV
    { ""    }           // HTTP_UNKNOWN
};
#define TOTAL_FILE_TYPES  ( sizeof(httpFiles)/sizeof(httpFiles[0]) )

// Content entry order must match with those "HTTP File Types" define's.
static ROM HTTP_CONTENT httpContents[] =
{
    { "text/plain" },            // HTTP_TXT
    { "text/html" },             // HTTP_HTML
    { "text/html" },             // HTTP_CGI
    { "text/xml" },              // HTTP_XML
    { "image/gif" },             // HTTP_GIF
    { "image/png" },             // HTTP_PNG
    { "image/jpeg" },            // HTTP_JPG
    { "application/java-vm" },   // HTTP_JAVA
    { "audio/x-wave" },          // HTTP_WAV
    { "" }                       // HTTP_UNKNOWN
};
#define TOTAL_HTTP_CONTENTS  ( sizeof(httpContents)/sizeof(httpConetents[0]) )

// Following message order must match with that of HTTP_MESSAGES enum.
static ROM char *HTTPMessages[] =
{
        "HTTP/1.0 404 Not found\r\n\r\nNot found\r\n",
        "HTTP/1.0 503 \r\n\r\nService Unavailable\r\n"
};

// Standard HTTP messages.
ROM BYTE HTTP_OK_STRING[] = "HTTP/1.0 200 OK\r\nContent-type: ";
ROM BYTE HTTP_OK_NO_CACHE_STRING[] = "HTTP/1.0 200 OK\r\nDate: Wed, 05 Apr 2006 02:53:05 GMT\r\nExpires: Wed, 05 Apr 2006 02:52:05 GMT\r\nCache-control: private\r\nContent-type: ";
#define HTTP_OK_STRING_LEN  (sizeof(HTTP_OK_STRING)-1)
#define HTTP_OK_NO_CACHE_STRING_LEN  (sizeof(HTTP_OK_NO_CACHE_STRING)-1)
ROM BYTE HTTP_HEADER_END_STRING[] = "\r\n\r\n";
#define HTTP_HEADER_END_STRING_LEN  (sizeof(HTTP_HEADER_END_STRING)-1)

// HTTP Command Strings
ROM BYTE HTTP_GET_STRING[] = "GET";
#define HTTP_GET_STRING_LEN  (sizeof(HTTP_GET_STRING)-1)

// Default HTML file.
ROM BYTE HTTP_DEFAULT_FILE_STRING[] = "INDEX.HTM";
#define HTTP_DEFAULT_FILE_STRING_LEN  (sizeof(HTTP_DEFAULT_FILE_STRING)-1)

static HTTP_INFO HCB[MAX_HTTP_CONNECTIONS];


/******************************************************************************
 * External callback functions                                                *
 ******************************************************************************/
// Main application must implement these callback functions
extern WORD HTTPGetVar(BYTE var, WORD ref, BYTE* val);
extern void HTTPExecCmd(BYTE** argv, BYTE argc);


/******************************************************************************
 * Functions implemented by this module                                       *
 ******************************************************************************/

/******************************************************************************
 * Function:        static BOOL SendFile(HTTP_INFO* ph)
 * PreCondition:    None
 * Input:           ph      -   A HTTP connection info.
 * Output:          File reference by this connection is served.
 * Side Effects:    None
 * Overview:        None
 * Note:            None.
 ******************************************************************************/
static BOOL SendFile(HTTP_INFO* ph)
{
    BOOL lbTransmit;
    BYTE c;
    WORD_VAL HexNumber;

    MPFSGetBegin(ph->file);

    // Check if file is dynamic (.cgi) -- need to look for and 
    // process escape sequences
    if(ph->bProcess)
    {
        while(TCPIsPutReady(ph->socket))
        {
            lbTransmit = FALSE;

            if(ph->smHTTPGet != SM_HTTP_GET_VAR)
            {
                c = MPFSGet();
                if(MPFSIsEOF())
                {
                    MPFSGetEnd();
                    TCPFlush(ph->socket);
                    return TRUE;
                }
            }

            switch(ph->smHTTPGet)
            {
            case SM_HTTP_GET_READ:
                if ( c == HTTP_VAR_ESC_CHAR )
                    ph->smHTTPGet = SM_HTTP_GET_DLE;
                else
                    lbTransmit = TRUE;
                break;

            case SM_HTTP_GET_DLE:
                if ( c == HTTP_VAR_ESC_CHAR )
                {
                    lbTransmit = TRUE;
                    ph->smHTTPGet = SM_HTTP_GET_READ;
                }
                else
                {
                    HexNumber.v[1] = c;
                    ph->smHTTPGet = SM_HTTP_GET_HANDLE;
                }
                break;

            case SM_HTTP_GET_HANDLE:
                HexNumber.v[0] = c;
                ph->Variable = hexatob(HexNumber);
                ph->smHTTPGet = SM_HTTP_GET_VAR;
                ph->VarRef = HTTP_START_OF_VAR;
                break;

            case SM_HTTP_GET_VAR:
                ph->VarRef = HTTPGetVar(ph->Variable, ph->VarRef, &c);
                lbTransmit = TRUE;
                if ( ph->VarRef == HTTP_END_OF_VAR )
                    ph->smHTTPGet = SM_HTTP_GET_READ;
                break;
            }

            if(lbTransmit)
                TCPPut(ph->socket, c);
        }
    }    
    else    // Static page content -- no processing required
    {
        while(TCPIsPutReady(ph->socket))
        {
            c = MPFSGet();
            if(MPFSIsEOF())
            {
                MPFSGetEnd();
                TCPFlush(ph->socket);
                return TRUE;
            }
            else
                TCPPut(ph->socket, c);
        }
    }

    ph->file = MPFSGetEnd();

    // We are not done sending a file yet...
    return FALSE;
}

/******************************************************************************
 * Function:        static HTTP_COMMAND HTTPParse(BYTE *string,
 *                                              BYTE** arg,
 *                                              BYTE* argc,
 *                                              BYTE* type)
 * PreCondition:    None
 * Input:           string      - HTTP Command String
 *                  arg         - List of string pointer to hold
 *                                HTTP arguments.
 *                  argc        - Pointer to hold total number of
 *                                arguments in this command string/
 *                  type        - Pointer to hold type of file
 *                                received.
 *                                Valid values are:
 *                                  HTTP_TXT
 *                                  HTTP_HTML
 *                                  HTTP_GIF
 *                                  HTTP_CGI
 *                                  HTTP_UNKNOWN
 * Output:          HTTP FSM and connections are initialized
 * Side Effects:    None
 * Overview:        None
 * Note:            This function parses URL that may or may not
 *                  contain arguments.
 *                  e.g. "GET HTTP/1.0 thank.htm?name=MCHP&age=12"
 *                      would be returned as below:
 *                          arg[0] => GET
 *                          arg[1] => thank.htm
 *                          arg[2] => name
 *                          arg[3] => MCHP
 *                          arg[4] => 12
 *                          argc = 5
 *                  This parses does not "de-escape" URL string.
 ******************************************************************************/
static HTTP_COMMAND HTTPParse(BYTE *string, BYTE** arg, BYTE* argc, BYTE* type)
{
    BYTE i, smParse, *ext, c;
    HTTP_COMMAND cmd;
    ROM char * fileType;

    enum
    {
        SM_PARSE_IDLE,
        SM_PARSE_ARG,
        SM_PARSE_ARG_FORMAT
    };

    smParse = SM_PARSE_IDLE;
    ext = NULL;
    i = 0;

    // Only "GET" is supported for time being.
    if ( !memcmppgm2ram(string, HTTP_GET_STRING, HTTP_GET_STRING_LEN) )
    {
        string += (HTTP_GET_STRING_LEN + 1);
        cmd = HTTP_GET;
    }
    else
    {
        return HTTP_NOT_SUPPORTED;
    }

    // Skip white spaces.
    while( *string == ' ' ) string++;

    c = *string;

    while ( c != ' ' &&  c != '\0' && c != '\r' && c != '\n' )
    {
        // Do not accept any more arguments than we haved designed to.
        if ( i >= *argc )
            break;

        switch(smParse)
        {
        case SM_PARSE_IDLE:
            arg[i] = string;
            c = *string;

            if ( c == '/' || c == '\\' )
                smParse = SM_PARSE_ARG;
            break;

        case SM_PARSE_ARG:
            arg[i++] = string;
            smParse = SM_PARSE_ARG_FORMAT;
            // Do not break, parameter may be empty.
            
        case SM_PARSE_ARG_FORMAT:
            c = *string;

            if ( c == '?' || c == '&' )
            {
                *string = '\0';
                smParse = SM_PARSE_ARG;
            }
            else
            {
                // Recover space characters.
                if ( c == '+' )
                    *string = ' ';

                // Remember where file extension starts.
                else if ( c == '.' && i == 1u )
                {
                    ext = ++string;
                }
                else if ( c == '=' )
                {
                    *string = '\0';
                    smParse = SM_PARSE_ARG;
                }

                // Only interested in file name - not a path.
                else if ( c == '/' || c == '\\' )
                    arg[i-1] = string+1;
            }
            break;
        }
        string++;
        c = *string;
    }

    *string = '\0';
    *type = HTTP_UNKNOWN;

    if ( ext != NULL )
    {
        ext = (BYTE*)strupr((char*)ext);
        fileType = httpFiles[0].fileExt;

        for ( c = 0; c < TOTAL_FILE_TYPES; c++ )
        {
            if ( !memcmppgm2ram( ext, fileType, FILE_EXT_LEN) )
            {
                *type = c;
                break;
            }
            fileType += sizeof(FILE_TYPES);
        }
    }

    if ( i == 0u )
    {
        memcpypgm2ram( arg[0], HTTP_DEFAULT_FILE_STRING,HTTP_DEFAULT_FILE_STRING_LEN);
        arg[0][HTTP_DEFAULT_FILE_STRING_LEN] = '\0';
        *type = HTTP_HTML;
        i++;
    }
    *argc = i;

    return cmd;
}

/******************************************************************************
 * Function:        static BOOL HTTPProcess(HTTP_HANDLE h)
 * PreCondition:    HTTPInit() called.
 * Input:           h   -   Index to the handle which needs to be
 *                          processed.
 * Output:          Connection referred by 'h' is served.
 * Side Effects:    None
 * Overview:
 * Note:            None.
 ******************************************************************************/
static void HTTPProcess(HTTP_HANDLE h)
{
    BYTE httpData[MAX_HTML_CMD_LEN+1], *arg[MAX_HTTP_ARGS], argc, i;
    HTTP_COMMAND httpCommand;
    WORD httpLength;
    BOOL lbContinue;
    HTTP_INFO* ph;
    ROM char* romString;

    ph = &HCB[h];

    do
    {
        lbContinue = FALSE;

        // If during handling of HTTP socket, it gets disconnected,
        // forget about previous processing and return to idle state.
        if(!TCPIsConnected(ph->socket))
        {
            ph->smHTTP = SM_HTTP_IDLE;
            break;
        }

        switch(ph->smHTTP)
        {
        case SM_HTTP_IDLE:
            if(TCPIsGetReady(ph->socket))
            {
                lbContinue = TRUE;
                httpLength = 0;

                while(httpLength < MAX_HTML_CMD_LEN &&
                      TCPGet(ph->socket, &httpData[httpLength++]) );
                httpData[httpLength] = '\0';
                TCPDiscard(ph->socket);
                ph->smHTTP = SM_HTTP_NOT_FOUND;
                argc = MAX_HTTP_ARGS;
                httpCommand = HTTPParse(httpData, arg, &argc, &ph->fileType);

                if ( httpCommand == HTTP_GET )
                {
                    // If there are any arguments, this must be a remote command.
                    // Execute it and then send the file.
                    // The file name may be modified by command handler.
                    if ( argc > 1u )
                    {
                        // Let main application handle this remote command.
                        HTTPExecCmd(&arg[0], argc);

                        // Command handler must have modified arg[0] which now
                        // points to actual file that will be sent as a result of
                        // this remote command.

                        // Assume that Web author will only use CGI or HTML
                        // file for remote command.
                        ph->fileType = HTTP_CGI;
                    }

                    ph->file = MPFSOpen(arg[0]);

                    if ( ph->file == MPFS_INVALID )
                    {
                        ph->Variable = HTTP_NOT_FOUND;
                        ph->smHTTP = SM_HTTP_NOT_FOUND;
                    }
                    else if ( ph->file == MPFS_NOT_AVAILABLE )
                    {
                        ph->Variable = HTTP_NOT_AVAILABLE;
                        ph->smHTTP = SM_HTTP_NOT_FOUND;
                    }
                    else
                    {
                        ph->smHTTP = SM_HTTP_HEADER;
                    }
                }
            }
            break;

        case SM_HTTP_NOT_FOUND:
            if ( TCPIsPutReady(ph->socket) )
            {
                romString = HTTPMessages[ph->Variable];

                while( (i = *romString++) )
                    TCPPut(ph->socket, i);

                TCPFlush(ph->socket);
                ph->smHTTP = SM_HTTP_DISCONNECT;
            }
            break;

        case SM_HTTP_HEADER:
            if ( TCPIsPutReady(ph->socket) )
            {
                lbContinue = TRUE;

                if ( ph->fileType == HTTP_DYNAMIC_FILE_TYPE )
                {
                    ph->bProcess = TRUE;

                    for ( i = 0; i < HTTP_OK_NO_CACHE_STRING_LEN; i++ )
                        TCPPut(ph->socket, HTTP_OK_NO_CACHE_STRING[i]);
                }
                else
                {
                    ph->bProcess = FALSE;

                    for ( i = 0; i < HTTP_OK_STRING_LEN; i++ )
                        TCPPut(ph->socket, HTTP_OK_STRING[i]);
                }

                romString = httpContents[ph->fileType].typeString;

                while( (i = *romString++) )
                    TCPPut(ph->socket, i);

                for ( i = 0; i < HTTP_HEADER_END_STRING_LEN; i++ )
                    TCPPut(ph->socket, HTTP_HEADER_END_STRING[i]);

                ph->smHTTPGet = SM_HTTP_GET_READ;
                ph->smHTTP = SM_HTTP_GET;
            }
            break;

        case SM_HTTP_GET:
            if ( TCPIsGetReady(ph->socket) )
                TCPDiscard(ph->socket);

            if ( SendFile(ph) )
            {
                MPFSClose();
                ph->smHTTP = SM_HTTP_DISCONNECT;
            }
            break;

        case SM_HTTP_DISCONNECT:
            if(TCPIsConnected(ph->socket))
            {
                if(TCPIsPutReady(ph->socket))
                {
                    TCPDisconnect(ph->socket);

                    // Switch to not-handled state.  This FSM has
                    // one common action that checks for disconnect
                    // condition and returns to Idle state.
                    ph->smHTTP = SM_HTTP_DISCONNECT_WAIT;
                }
            }
            break;

        }
    } while( lbContinue );
}

/******************************************************************************
 * Function:        void HTTPServer(void)
 * PreCondition:    HTTPInit() must already be called.
 * Input:           None
 * Output:          Opened HTTP connections are served.
 * Side Effects:    None
 * Overview:        Browse through each connections and let it
 *                  handle its connection.
 *                  If a connection is not finished, do not process
 *                  next connections.  This must be done, all
 *                  connections use some static variables that are
 *                  common.
 * Note:            This function acts as a task (similar to one in
 *                  RTOS).  This function performs its task in
 *                  co-operative manner.  Main application must call
 *                  this function repeatdly to ensure all open
 *                  or new connections are served on time.
 ******************************************************************************/
void HTTPServer(void)
{
    BYTE conn;

    for ( conn = 0;  conn < MAX_HTTP_CONNECTIONS; conn++ )
        HTTPProcess(conn);
}

/******************************************************************************
 * Function:        void HTTPInit(void)
 * PreCondition:    TCP must already be initialized.
 * Input:           None
 * Output:          HTTP FSM and connections are initialized
 * Side Effects:    None
 * Overview:        Set all HTTP connections to Listening state.
 *                  Initialize FSM for each connection.
 * Note:            This function is called only one during lifetime
 *                  of the application.
 ******************************************************************************/
void HTTPInit(void)
{
    BYTE i;

    for ( i = 0; i <  MAX_HTTP_CONNECTIONS; i++ )
    {
        HCB[i].socket = TCPListen(HTTP_PORT);
        HCB[i].smHTTP = SM_HTTP_IDLE;
    }
}

#endif  // STACK_USE_HTTP_SERVER
