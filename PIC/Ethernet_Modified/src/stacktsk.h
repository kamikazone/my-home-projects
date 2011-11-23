
#ifndef _STACKTSK_H
#define _STACKTSK_H

#include "config.h"
#include "generic_typedefs.h"


/******************************************************************************
 * Specific types and structures definitions for this module                  *
 ******************************************************************************/
typedef BYTE BUFFER;

typedef struct _MAC_ADDR
{
    BYTE v[6];
} MAC_ADDR;

typedef union _IP_ADDR
{
    BYTE        v[4];
    DWORD       Val;
} IP_ADDR;

typedef struct _NODE_INFO
{
    MAC_ADDR    MACAddr;
    IP_ADDR     IPAddr;
} NODE_INFO;

typedef struct _APP_CONFIG
{
    IP_ADDR     MyIPAddr;
    MAC_ADDR    MyMACAddr;
    IP_ADDR     MyMask;
    IP_ADDR     MyGateway;
    IP_ADDR     PrimaryDNSServer;
    struct
    {
        unsigned char bIsDHCPEnabled : 1;
        unsigned char bInConfigMode : 1;
    } Flags;
    WORD_VAL    SerialNumber;
    IP_ADDR     SMTPServerAddr;     // Not used.
    IP_ADDR     TFTPServerAddr;     // Not used.
    BYTE        NetBIOSName[16];
} APP_CONFIG;


/******************************************************************************
 * Specific value macro defines for this module                               *
 ******************************************************************************/
#define MAC_ADDR_ZERO     {0x00,0x00,0x00,0x00,0x00,0x00}
#define MAC_ADDR_BCAST    {0xff,0xff,0xff,0xff,0xff,0xff}


/******************************************************************************
 * Local & external variables for this module                                 *
 ******************************************************************************/
#if !defined(_MAIN_C)
  extern APP_CONFIG AppConfig;
#endif


/******************************************************************************
 * Code replacement macros for this module                                    *
 ******************************************************************************/
#if defined(STACK_USE_IP_GLEANING) || defined(STACK_USE_DHCP)
  #define StackIsInConfigMode()  (AppConfig.Flags.bInConfigMode)
#else
  #define StackIsInConfigMode()  (FALSE)
#endif


/******************************************************************************
 * Functions implemented by this module  (see source file for details)        *
 ******************************************************************************/
void StackInit(void);
void StackTask(void);

#endif // _STACKTSK_H
