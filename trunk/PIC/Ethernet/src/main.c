
#define _MAIN_C
#include "include/config.h"

/******************************************************************************
 * The following section set the requiredconfiguration bits for each          *
 * processor supported by different development boards and reference designs. *
 *                                                                            *
 * For this application running the current version of the Microchip TCP/IP   *
 * stack, it's important that some particualr configuration bit settings are  *
 * consistent with the hardware configuration. Oscillator configuration and   *
 * options must match the declared CPU_CLOCK, Watchdog Timer (WDT), Low       *
 * Voltage Programming (LVP) and JTAG must be disabled.                       *
 * If your particular hardware design or processor is not included in this    *
 * section you must add the proper configuration bits for it using the        *
 * existing ones and the C18, C30 compilers documentation as a reference.     *
 ******************************************************************************/
#if defined(PIC10T) || defined(MINIPIC10T) || defined(PIC18_NIC28)
#if defined(__18F452)
#pragma config OSC=ECIO, PWRT=ON, BOR=OFF, WDT=OFF, LVP=OFF
#elif defined(__18F4520) || defined(__18F4525) || defined(__18F4620) || defined(__18F2620)
#pragma config OSC=EC, PWRT=ON, BOREN=OFF, WDT=OFF, MCLRE=OFF, PBADEN=OFF, LVP=OFF, XINST=OFF
#elif defined(__18F4580)
#pragma config OSC=EC, PWRT=ON, BOREN=OFF, WDT=OFF, MCLRE=OFF, PBADEN=OFF, LVP=OFF, XINST=OFF
#else
#error Add CPU configuration bits for PIC10T or MINIPIC10T or PIC18_NIC28
#endif

#elif defined(PICNET1)
#if defined(__18F252) || defined(__18F452)
#pragma config OSC=HSPLL, PWRT=ON, BOR=OFF, WDT=OFF, LVP=OFF
#elif defined(__18F2520) || defined(__18F4520) || defined(__18F2525) || \
          defined(__18F4525) || defined(__18F2620) || defined(__18F4620)
#pragma config OSC=HSPLL, PWRT=ON, BOREN=OFF, WDT=OFF, MCLRE=ON, PBADEN=OFF, LVP=OFF, XINST=OFF
#else
#error Add CPU configuration bits for PICNET1
#endif

#elif defined(EIP10)
#pragma config OSC=HSPLL, PWRT=ON, BOREN=OFF, WDT=OFF, MCLRE=ON, PBADEN=OFF, LVP=OFF, XINST=OFF

#elif defined(PICDEM2)
#if defined(__18F252) || defined(__18F452)
#pragma config OSC=HSPLL, PWRT=ON, BOR=OFF, WDT=OFF, LVP=OFF
#elif defined(__18F2520) || defined(__18F4520) || defined(__18F2525) || \
          defined(__18F4525) || defined(__18F2620) || defined(__18F4620)
#pragma config OSC=HSPLL, PWRT=ON, BOREN=OFF, WDT=OFF, MCLRE=ON, PBADEN=OFF, LVP=OFF, XINST=OFF
#else
#error Add CPU configuration bits for PICDEM2
#endif

#elif defined(PICDEMNET)
#if defined(__18F452)
#pragma config OSC=HSPLL, PWRT=ON, BOR=OFF, WDT=OFF, LVP=OFF
#elif defined(__18F4520) || defined(__18F4525) || defined(__18F4620)
#pragma config OSC=HS, PWRT=ON, BOREN=OFF, WDT=OFF, MCLRE=ON, PBADEN=OFF, LVP=OFF, XINST=OFF
#else
#error Add CPU configuration bits for PICDEMNET
#endif

#elif defined(PICDEMNET2) || defined(PICWEB1)
#pragma config XINST=OFF, WDT=OFF, FOSC2=ON, FOSC=HSPLL, ETHLED=ON

#elif defined(HPC_EXPLORER)
#pragma config OSC=HSPLL, PWRT=ON, BOREN=OFF, WDT=OFF, MCLRE=ON, LVP=OFF, XINST=OFF

#elif defined(EXP16_DSPIC33) || defined(EXP16_PIC24H)
_FOSCSEL(FNOSC_PRIPLL) // PLL enabled
_FOSC(OSCIOFNC_OFF & POSCMD_XT) // XT Osc
_FWDT(FWDTEN_OFF) // Disable Watchdog timer

#elif defined(EXP16_PIC24F)
_CONFIG2(FNOSC_PRIPLL & POSCMOD_XT) // Primary XT OSC with 4x PLL
_CONFIG1(JTAGEN_OFF & FWDTEN_OFF) // JTAG off, watchdog timer off

#elif defined(PIC24FJ64_NIC28)
_CONFIG2(FNOSC_PRIPLL & POSCMOD_HS) // Primary HS OSC with 4x PLL
_CONFIG1(JTAGEN_OFF & FWDTEN_OFF) // JTAG off, watchdog timer off

#else
#error MAIN001: Unknown or unsupported board/hardware profile
#endif


/******************************************************************************
 * Include specific headers files required for this application based on the  *
 * hardware configuration and options configured in the config.h file         *
 ******************************************************************************/
#include "include/delay.h"
#include "net/include/stacktsk.h"
#include "net/include/tick.h"
#include "net/include/mac.h"
#include "net/include/helpers.h"
#include "uart/include/uart.h"

#if defined(USE_LCD) && defined(USE_CM_LCD)
#include "lcd/include/cmlcddriver.h"
#endif

#if defined(STACK_USE_DHCP)
#include "net/include/dhcp.h"
#endif

#if defined(MPFS_USE_EEPROM) || defined(MPFS_USE_PGRM)
#include "mpfs/include/mpfs.h"
#endif

#if defined(MPFS_USE_EEPROM)
#include "eeprom/include/xeeprom.h"
#endif

#if defined(STACK_USE_HTTP_SERVER)
#include "net/include/http.h"
#endif

#if defined(STACK_USE_FTP_SERVER)
#include "net/include/ftp.h"
#endif

#if defined(STACK_USE_ANNOUNCE)
#include "net/include/announce.h"
#endif

#if defined(STACK_USE_DNS)
#include "net/include/dns.h"
#endif

#if defined(STACK_USE_TCP_EXAMPLE1)
#include "net/include/tcp_client_ex1.h"
#endif

#if defined(STACK_USE_UDPTEST)
#include "net/include/udptest.h"
#endif

#if defined(USE_TIME)
#include "time/include/time.h"
#endif

#if defined(STACK_USE_SNTP)
#include "net/include/sntp.h"
#endif

/******************************************************************************
 * Local & external variables and constants used by the application           *
 ******************************************************************************/
APP_CONFIG AppConfig ={
    DEFAULT_IP_ADDRESS, DEFAULT_MAC_ADDRESS, DEFAULT_NETMASK,
    DEFAULT_GATEWAY, DEFAULT_NS1,
    {0b00000001}, // Flags, enable DHCP
};

BYTE myDHCPBindCount = 0;
static char AN0String[8];
//static char AN1String[8] = "";
extern unsigned long IP_RX_pktcnt;
extern unsigned long IP_TX_pktcnt;
//ROM char NewIP[] = "New IP Address: ";
ROM char CRLF[] = "\r\n";

#if defined(STACK_USE_DHCP)
extern BYTE DHCPBindCount;
#else
#define DHCPBindCount      (0xFF)
#endif


/******************************************************************************
 * Setup interrupt handling for PIC18 Devices                                 *
 *                                                                            *
 * NOTE: Several PICs, including the PIC18F4620 revision A3 have a RETFIE     *
 * FAST/MOVFF bug. The interruptlow keyword is used to work around the bug    *
 * when using the C18 compiler                                                *
 ******************************************************************************/
#if defined(__18CXX)
#pragma interruptlow LowISR

void LowISR(void) {
    TickUpdate();
}

#pragma code lowVector=0x18

void LowVector(void) {
    _asm goto LowISR _endasm
}

#pragma code // Return to default code section
#endif


/******************************************************************************
 * The following section include various support functions for IP<->string    *
 * conversion, LCD display functions and hostname formating                   *
 ******************************************************************************/

//*****************************************************************************
// StringToIPAddress converts the string pointed by str to the internal
// IP address representation pointed by buffer
// If the input string is valid and the conversion is complete it will
// return TRUE otherwise will return FALSE
//

BOOL StringToIPAddress(char *str, IP_ADDR *buffer) {
    BYTE v, byteIndex = 0;
    char *temp;

    temp = str;

    while (v = *str) {
        if (v == '.') {
            *str++ = '\0';
            buffer->v[byteIndex++] = atoi(temp);
            temp = str;
        } else if (v < '0' || v > '9')
            return FALSE;

        str++;
    }

    buffer->v[byteIndex] = atoi(temp);

    return (byteIndex == 3);
}

//*****************************************************************************
// IPAddressToString() converts an IP address value type IP_ADDR pointed
// by IPVal to a character string pointed by str. Make sure that enough
// memory is allocated to hold the resulting string.
//

void IPAddressToString(IP_ADDR *IPVal, char *str) {
    itoa(IPVal->v[0], str);
    str += strlen(str);
    *str++ = '.';
    itoa(IPVal->v[1], str);
    str += strlen(str);
    *str++ = '.';
    itoa(IPVal->v[2], str);
    str += strlen(str);
    *str++ = '.';
    itoa(IPVal->v[3], str);
}

#if defined(USE_LCD)
//*****************************************************************************
// DisplayCounters will convert the Tx and Rx counters to strings and display
// them in the LCD module
//

void DisplayCounters(void) {
    LCDClearBufferRow(LCD_ROWS - 2);
    LCDClearBufferRow(LCD_ROWS - 1);
    strcpypgm2ram((char *) &LCDBuffer[LCD_ROWS - 2][0], (ROM char *) "Tx=");
    strcpypgm2ram((char *) &LCDBuffer[LCD_ROWS - 1][0], (ROM char *) "Rx=");
    ultoa(IP_TX_pktcnt, (char *) &LCDBuffer[LCD_ROWS - 2][3]);
    ultoa(IP_RX_pktcnt, (char *) &LCDBuffer[LCD_ROWS - 1][3]);
}

//*****************************************************************************
//

void UpdateLCD(void) {
    static BYTE lcd_cycle = 0;

#if defined(USE_TIME)
    time_t time;
    tm tm_time;
#endif    

    LCDClearBuffer();

#if LCD_ROWS > 2

    IPAddressToString(&AppConfig.MyIPAddr, (char *) &LCDBuffer[1][0]);
    DisplayCounters();

#if defined(USE_TIME)
    time = GetTimeTick();
    offtime(&tm_time, time, LOCAL_OFFSET_SECS);

#if defined(STACK_USE_SNTP)
    if (!IsClockValid())
        strcpypgm2ram((char *) &LCDBuffer[0][0], (ROM char *) "--/--/-- --:--");
    else
#endif
        asctime(&tm_time, &LCDBuffer[0][0], 7);

#else  // No time to show, copy back the software version
    strcpypgm2ram((char *) &LCDBuffer[0][0], (ROM char *) "TCP/IP " VERSION);
#endif

#else  // We have only 2 rows, cycle the LCD

    if (lcd_cycle < 10) {
        IPAddressToString(&AppConfig.MyIPAddr, (char *) &LCDBuffer[1][0]);

#if defined(USE_TIME)
        time = GetTimeTick();
        offtime(&tm_time, time, LOCAL_OFFSET_SECS);

#if defined(STACK_USE_SNTP)
        if (!IsClockValid())
            strcpypgm2ram((char *) &LCDBuffer[0][0], (ROM char *) "--/--/-- --:--");
        else
#endif
            asctime(&tm_time, &LCDBuffer[0][0], 7);

#else  // No time to show, copy back the software version
        strcpypgm2ram((char *) &LCDBuffer[0][0], (ROM char *) "TCP/IP " VERSION);
#endif
        lcd_cycle++;
    }
    else if (lcd_cycle < 30) {
        DisplayCounters();
        lcd_cycle++;
    } else lcd_cycle = 0;
#endif  // LCD_ROWS > 2

    LCDRefresh();
}
#endif  // USE_LCD

//*****************************************************************************
// FormatNetBIOSName converts the string pointed by Name to the standard
// NetBios format
//

void FormatNetBIOSName(char *Name) {
    BYTE i = 0;

    Name[15] = '\0';
    strupr((char *) Name);

    while (i < 15) {
        if (Name[i] == '\0') {
            while (i < 15) {
                Name[i++] = ' ';
            }
            break;
        }
        i++;
    }
}


/******************************************************************************
 * The following group of functions implement an interactive configuration    *
 * menu over the serial interface.                                            *
 * To enable this feature the macro ENABLE_BUTTON0_CONFIG must be defined,    *
 * if an external serial EEPROM is available the application configuration    *
 * vector (AppConfig) is written into it.                                     *
 ******************************************************************************/

#if defined(MPFS_USE_EEPROM)
//*****************************************************************************
// If an external serial EEPROM is available SaveAppConfig will write the
// application configuration vector (AppConfig) into the reserved memory
// block at the start of the memory address space writing a 0x55 value to
// indicate the presence of a valid configuration vector
//

static void SaveAppConfig(void) {
    BYTE c, *p;

    p = (BYTE*) & AppConfig;
    XEEBeginWrite(EEPROM_CONTROL, 0x00);
    XEEWrite(0x55);

    for (c = 0; c < sizeof (AppConfig); c++) {
        XEEWrite(*p++);
    }

    XEEEndWrite();
}
#else
#define SaveAppConfig()
#endif

//*****************************************************************************
// ROM strings used by the interactive configuration menu via serial interface
//
#if defined(ENABLE_BUTTON0_CONFIG)

#define MAX_USER_RESPONSE_LEN  (20)

ROM char menu[] =
        "\r\nTCP/IP Config Application ("VERSION", " __DATE__ ")\r\n\r\n"
        "\t1: Change Board serial number\r\n"
        "\t2: Change Host Name\r\n"
        "\t3: Change IP address\r\n"
        "\t4: Change Gateway address\r\n"
        "\t5: Change Netmask\r\n"
        "\t6: Change DNS server address\r\n"
        "\t7: Enable DHCP\r\n"
        "\t8: Disable DHCP\r\n"
        "\t0: Save & Quit\r\n"
        "\r\n"
        "Enter a menu choice (1-0):";

typedef enum _MENU_CMD {
    MENU_CMD_SERIAL_NUMBER = '1',
    MENU_CMD_HOST_NAME,
    MENU_CMD_IP_ADDRESS,
    MENU_CMD_GATEWAY_ADDRESS,
    MENU_CMD_SUBNET_MASK,
    MENU_CMD_DNS_ADDRESS,
    MENU_CMD_ENABLE_AUTO_CONFIG,
    MENU_CMD_DISABLE_AUTO_CONFIG,
    MENU_CMD_DOWNLOAD_MPFS,
    MENU_CMD_QUIT = '0',
    MENU_CMD_INVALID = MENU_CMD_DOWNLOAD_MPFS + 1
} MENU_CMD;

ROM char * const menuCommandPrompt[] ={
    "\r\nNow running application...\r\n",
    "\r\nSerial Number (",
    "\r\nHost Name (",
    "\r\nIP Address (",
    "\r\nGateway Address (",
    "\r\nNetmask (",
    "\r\nDNS Server Address (",
    "\r\nDHCP\r\n",
    "\r\nDHCP\r\n",
    "\r\nReady to download MPFS image - Use Xmodem protocol\r\n",
};

ROM char InvalidInputMsg[] = "\r\nInvalid input received - Input ignored\r\n"
        "Press any key to continue\r\n";

#if defined(MPFS_USE_EEPROM)
/******************************************************************************
 * Function:        BOOL DownloadMPFS(void)
 * PreCondition:    MPFSInit() is already called.
 * Input:           None
 * Output:          TRUE if successful
 *                  FALSE otherwise
 * Side Effects:    This function uses 128 bytes of Bank 4 using indirect
 *                  pointer.  This requires that no part of code is using 
 *                  this block during or before calling this function.
 *                  Once this function is done, that block of memory is
 *                  available for general use.
 * Overview:        This function implements XMODEM protocol to be able to
 *                  receive a binary file from PC applications such as 
 *                  HyperTerminal or TeraTerm.
 * Note:            The current version does not implement user interface to
 *                  set IP address and other information. User should create
 *                  their own interface to allow user to modify IP information
 *                  Also, this version implements simple user action to start
 *                  file transfer. User may evaulate its own requirements and
 *                  implement an appropriate start action.
 ******************************************************************************/
#define XMODEM_SOH       0x01
#define XMODEM_EOT       0x04
#define XMODEM_ACK       0x06
#define XMODEM_NAK       0x15
#define XMODEM_CAN       0x18
#define XMODEM_BLOCK_LEN 128

static BOOL DownloadMPFS(void) {

    enum SM_MPFS {
        SM_MPFS_SOH,
        SM_MPFS_BLOCK,
        SM_MPFS_BLOCK_CMP,
        SM_MPFS_DATA,
    } state;

    BYTE c, blockLen, lResult, tempData[XMODEM_BLOCK_LEN];
    MPFS handle;
    BOOL lbDone = FALSE;
    TICK lastTick, currentTick;

    state = SM_MPFS_SOH;
    handle = MPFSFormat();

    // Notify the host that we are ready to receive...
    lastTick = TickGet();
    do {
        currentTick = TickGet();
        if (TickGetDiff(currentTick, lastTick) >= (TICK_SECOND / 2)) {
            lastTick = TickGet();

            while (BusyUART());

            WriteUART(XMODEM_NAK);

            /*
             * Blink LED to indicate that we are waiting for
             * host to send the file.
             */
            LED6_IO ^= 1;
        }

    } while (!DataRdyUART());

    while (!lbDone) {
        if (DataRdyUART()) {
            // Toggle LED as we receive the data from host.
            LED6_IO ^= 1;
            c = ReadUART();
        } else {
            // Real application should put some timeout to make sure
            // that we do not wait forever.
            continue;
        }

        switch (state) {
            default:
                if (c == XMODEM_SOH) {
                    state = SM_MPFS_BLOCK;
                } else if (c == XMODEM_EOT) {
                    // Turn off LED when we are done.
                    LED6_IO = 1;

                    MPFSClose();

                    while (BusyUART());

                    WriteUART(XMODEM_ACK);
                    lbDone = TRUE;
                } else {
                    while (BusyUART());

                    WriteUART(XMODEM_NAK);
                }

                break;

            case SM_MPFS_BLOCK:

                // We do not use block information.
                lResult = XMODEM_ACK;
                blockLen = 0;
                state = SM_MPFS_BLOCK_CMP;
                break;

            case SM_MPFS_BLOCK_CMP:

                // We do not use 1's comp. block value.
                state = SM_MPFS_DATA;
                break;

            case SM_MPFS_DATA:

                // Buffer block data until it is over.
                tempData[blockLen++] = c;

                if (blockLen > XMODEM_BLOCK_LEN) {
                    // We have one block data. Write it to EEPROM.
                    MPFSPutBegin(handle);
                    lResult = XMODEM_ACK;

                    for (c = 0; c < XMODEM_BLOCK_LEN; c++)
                        MPFSPut(tempData[c]);

                    handle = MPFSPutEnd();

                    while (BusyUART());

                    WriteUART(lResult);
                    state = SM_MPFS_SOH;
                }
                break;
        }
    }
    return TRUE;
}
#endif

MENU_CMD GetMenuChoice(void) {
    BYTE c;

    while (!DataRdyUART()) {

    }

    c = ReadUART();

    if (c >= '0' && c < MENU_CMD_INVALID)
        return c;
    else
        return MENU_CMD_INVALID;
}

void ExecuteMenuChoice(MENU_CMD choice) {
    char response[MAX_USER_RESPONSE_LEN], buffer[20];
    IP_ADDR tempIPValue, *destIPValue;

    putrsUART(CRLF);
    putrsUART(menuCommandPrompt[choice - '0']);

    switch (choice) {
        case MENU_CMD_SERIAL_NUMBER:
            itoa(AppConfig.SerialNumber.Val, response);
            putsUART(response);
            putrsUART("): ");

            if (ReadStringUART((BYTE *) response, sizeof (response))) {
                AppConfig.SerialNumber.Val = atoi(response);
                AppConfig.MyMACAddr.v[4] = AppConfig.SerialNumber.v[1];
                AppConfig.MyMACAddr.v[5] = AppConfig.SerialNumber.v[0];
            }
            break;

        case MENU_CMD_HOST_NAME:
            putsUART(AppConfig.NetBIOSName);
            putrsUART("): ");
            ReadStringUART((BYTE *) response, sizeof (response) > sizeof (AppConfig.NetBIOSName) ? sizeof (AppConfig.NetBIOSName) : sizeof (response));

            if (response[0] != '\0') {
                memcpy(AppConfig.NetBIOSName, (void*) response, sizeof (AppConfig.NetBIOSName));
                FormatNetBIOSName((char *) &AppConfig.NetBIOSName);
            }
            break;

        case MENU_CMD_IP_ADDRESS:
            destIPValue = &AppConfig.MyIPAddr;
            goto ReadIPConfig;

        case MENU_CMD_GATEWAY_ADDRESS:
            destIPValue = &AppConfig.MyGateway;
            goto ReadIPConfig;

        case MENU_CMD_SUBNET_MASK:
            destIPValue = &AppConfig.MyMask;
            goto ReadIPConfig;

        case MENU_CMD_DNS_ADDRESS:
            destIPValue = &AppConfig.PrimaryDNSServer;

ReadIPConfig:
            IPAddressToString(destIPValue, buffer);
            putsUART(buffer);
            putrsUART("): ");
            ReadStringUART((BYTE *) response, sizeof (response));

            if (!StringToIPAddress(response, &tempIPValue)) {
                putrsUART(InvalidInputMsg);

                while (!DataRdyUART());

                ReadUART();
            } else {
                destIPValue->Val = tempIPValue.Val;
            }
            break;

        case MENU_CMD_ENABLE_AUTO_CONFIG:
            AppConfig.Flags.bIsDHCPEnabled = TRUE;
            break;

        case MENU_CMD_DISABLE_AUTO_CONFIG:
            AppConfig.Flags.bIsDHCPEnabled = FALSE;
            break;

        case MENU_CMD_DOWNLOAD_MPFS:

#if defined(MPFS_USE_EEPROM)
            DownloadMPFS();
#endif

            break;

        case MENU_CMD_QUIT:

#if defined(MPFS_USE_EEPROM)
            SaveAppConfig();
#endif

            break;
    }
}

static void SetConfig(void) {
    MENU_CMD choice;

    do {
        putrsUART(menu);
        choice = GetMenuChoice();

        if (choice != MENU_CMD_INVALID)
            ExecuteMenuChoice(choice);

    } while (choice != MENU_CMD_QUIT);

}
#endif  // ENABLE_BUTTON0_CONFIG


/******************************************************************************
 * If enabled the HTTP Server requires the main application to implement two  *
 * callback functions to handle http requests that include dynamic content or *
 * execution of a particular command.                                         *
 ******************************************************************************/
#if defined(STACK_USE_HTTP_SERVER)
// CGI Command Codes
#define CGI_CMD_DIGOUT      (0)
#define CGI_CMD_LCDOUT      (1)
#define CGI_CMD_RECONFIG    (2)

// CGI Variable codes. - There could be 00h-FFh variables.
// NOTE: When specifying variables in your dynamic pages (.cgi), use a two
//       digit hexadecimal notation. Ex: "%04", "%2C"; not "%4" or "%02C"
#define VAR_LED0            (0x00)
#define VAR_LED1            (0x01)
#define VAR_LED2            (0x10)
#define VAR_LED3            (0x11)
#define VAR_LED4            (0x12)
#define VAR_LED5            (0x13)
#define VAR_LED6            (0x14)
#define VAR_LED7            (0x15)
#define VAR_ANAIN_AN0       (0x02)
#define VAR_ANAIN_AN1       (0x03)
#define VAR_DIGIN0          (0x04)     // Button0 on Explorer16
#define VAR_DIGIN1          (0x0D)     // Button1 on Explorer16
#define VAR_DIGIN2          (0x0E)     // Button2 on Explorer16
#define VAR_DIGIN3          (0x0F)     // Button3 on Explorer16
#define VAR_STACK_VERSION   (0x16)
#define VAR_STACK_DATE      (0x17)
#define VAR_STROUT_LCD      (0x05)
#define VAR_MAC_ADDRESS     (0x06)
#define VAR_SERIAL_NUMBER   (0x07)
#define VAR_IP_ADDRESS      (0x08)
#define VAR_SUBNET_MASK     (0x09)
#define VAR_GATEWAY_ADDRESS (0x0A)
#define VAR_DHCP            (0x0B)     // Use this variable when the web page is updating us
#define VAR_DHCP_TRUE       (0x0B)     // Use this variable when we are generating the web page
#define VAR_DHCP_FALSE      (0x0C)     // Use this variable when we are generating the web page
#define VAR_IPCNTR_TX       (0x20)
#define VAR_IPCNTR_RX       (0x21)
#define VAR_DATE            (0x22)
#define VAR_TIME            (0x23)

// CGI Command codes (CGI_CMD_DIGOUT).
// Should be a one digit numerical value
#define CMD_LED1            (0x0)
#define CMD_LED2            (0x1)

ROM char COMMANDS_OK_PAGE[] = "INDEX.CGI";
ROM char CONFIG_UPDATE_PAGE[] = "CONFIG.CGI";
ROM char CMD_UNKNOWN_PAGE[] = "INDEX.CGI";

// Copy string with NULL termination.
#define COMMANDS_OK_PAGE_LEN    (sizeof(COMMANDS_OK_PAGE))
#define CONFIG_UPDATE_PAGE_LEN  (sizeof(CONFIG_UPDATE_PAGE))
#define CMD_UNKNOWN_PAGE_LEN    (sizeof(CMD_UNKNOWN_PAGE))

/******************************************************************************
 * Function:        void HTTPExecCmd(BYTE** argv, BYTE argc)
 * PreCondition:    None
 * Input:           argv        - List of arguments
 *                  argc        - Argument count.
 * Output:          None
 * Side Effects:    None
 * Overview:        This function is a "callback" from HTTPServer task.
 *                  Whenever a remote node performs interactive task on page
 *                  that was served, HTTPServer calls this functions with
 *                  action arguments info.
 *                  Main application should interpret this argument and act
 *                  accordingly.
 *                  Following is the format of argv:
 *                  If HTTP action was : thank.htm?name=Joe&age=25
 *                      argv[0] => thank.htm
 *                      argv[1] => name
 *                      argv[2] => Joe
 *                      argv[3] => age
 *                      argv[4] => 25
 *                  Use argv[0] as a command identifier and rests of the
 *                  items as command arguments.
 * Note:            THIS IS AN EXAMPLE CALLBACK.
 ******************************************************************************/
void HTTPExecCmd(BYTE** argv, BYTE argc) {
    BYTE command, var;
/*
    ///////////////////////////////////////////////////////////////////////////
    BYTE i;
    // Go through each parameters for current form command.
    // We are skipping form action name, so i starts at 1...
    for (i = 1; i < argc; i++) {
        // Identify parameter.
        if (argv[i][0] == 'P') // Is this power level?
        {
            // Next parameter is the Power level value.
            //PowerLevel = atoi(argv[++i]);
            putrsUART("\r\nP**\r\n");
        } else if (argv[i][0] == 'L') // Is this Low Power Setting?
            //LowPowerSetting = atoi(argv[++i]);
            putrsUART("\r\nL**\r\n");
        else if (argv[i][0] == 'H') // Is this High Power Setting?
            //HighPowerSetting = atoi(argv[++i]);
            putrsUART("\r\nH**\r\n");
    }
    // If another page is to be displayed as a result of this command, copy
    // its upper case name into argv[0]
    strcpy(argv[0], "index.htm");

    ////////////////////////////////////////////////////////////////////////////
*/
#if defined(ENABLE_REMOTE_CONFIG)
    BYTE CurrentArg;
    WORD_VAL TmpWord;
#endif

    // Design your pages such that they contain command code as a one
    // character numerical value.
    // Being a one character numerical value greatly simplifies the job
    command = argv[0][0] - '0';

    // Find out the cgi file name and interpret parameters accordingly
    switch (command) {
        case CGI_CMD_DIGOUT: // ACTION = 0

            // Identify the parameters. Compare it in upper case format
            var = argv[1][0] - '0';
            if (argv[1][1] == 0) {
                switch (var) {
                    case CMD_LED1: // NAME = 0
                        LED1_IO ^= 1; // Toggle LED
                        putrsUART("\r\nLED1\r\n");
                        break;

                    case CMD_LED2: // NAME = 1
                        LED2_IO ^= 1; // Toggle LED
                        putrsUART("\r\nLED2\r\n");
                        break;
                    case 2:
                        putrsUART("\r\nTest1\r\n");
                        break;
                    case 3:
                        putrsUART("\r\nTest2\r\n");
                        break;
                    case 4:
                        putrsUART("\r\nTest3\r\n");
                        break;
                    case 5:
                        putrsUART("\r\nTest4\r\n");
                        break;
                    case 6:
                        putrsUART("\r\nTest5\r\n");
                        break;
                    case 7:
                        putrsUART("\r\nTest6\r\n");
                        break;
                    case 8:
                        putrsUART("\r\nTest7\r\n");
                        break;
                    case 9:
                        putrsUART("\r\nTest8\r\n");
                        break;
                }
            } else
                putrsUART("\r\nNone...\r\n");

            memcpypgm2ram(argv[0], COMMANDS_OK_PAGE, COMMANDS_OK_PAGE_LEN);

            break;
            /*
            // TODO change code to use new lcd driver
            #if defined(USE_LCD)
                case CGI_CMD_LCDOUT:     // ACTION=1
                    if(argc > 2)         // Text provided in argv[2]
                    {
                        // Write 32 received characters or less to LCDText
                        if(strlen(argv[2]) < 32)
                        {
                            memset(LCDText, ' ', 32);
                            strcpy(LCDText, argv[2]);
                        }
                        else
                        {
                            memcpy(LCDText, (void*)argv[2], 32);
                        }

                        // Write LCDText to the LCD
                        LCDUpdate();
                    }
                    else                 // No text provided
                    {
                        LCDErase();
                    }
                    memcpypgm2ram(argv[0], COMMANDS_OK_PAGE, COMMANDS_OK_PAGE_LEN);
                    break;
            #endif
             */

#if ENABLE_REMOTE_CONFIG
            // Possibly useful code for remotely reconfiguring the board through HTTP
        case CGI_CMD_RECONFIG: // ACTION=2
            // Loop through all variables that we've been given
            CurrentArg = 1;

            while (argc > CurrentArg) {
                // Get the variable identifier (HTML "name"), and
                // increment to the variable's value
                TmpWord.byte.MSB = argv[CurrentArg][0];
                TmpWord.byte.LSB = argv[CurrentArg++][1];
                var = hexatob(TmpWord);

                // Make sure the variable's value exists
                if (CurrentArg >= argc)
                    break;

                // Take action with this variable/value
                switch (var) {
                    case VAR_SERIAL_NUMBER:
                        AppConfig.SerialNumber.Val = atoi(argv[CurrentArg]);
                        AppConfig.MyMACAddr.v[4] = AppConfig.SerialNumber.byte.MSB;
                        AppConfig.MyMACAddr.v[5] = AppConfig.SerialNumber.byte.LSB;
                        break;

                    case VAR_IP_ADDRESS:
                    case VAR_SUBNET_MASK:
                    case VAR_GATEWAY_ADDRESS:
                    {
                        DWORD TmpAddr;

                        // Convert the returned value to the 4 octect
                        // binary representation
                        if (!StringToIPAddress(argv[CurrentArg], (IP_ADDR*) & TmpAddr))
                            break;

                        // Reconfigure the App to use the new values
                        if (var == VAR_IP_ADDRESS) {
                            // Cause the IP address to be rebroadcast
                            // through Announce.c or the RS232 port since
                            // we now have a new IP address
                            if (TmpAddr != *(DWORD*) & AppConfig.MyIPAddr)
                                DHCPBindCount++;

                            // Set the new address
                            memcpy((void*) &AppConfig.MyIPAddr, (void*) &TmpAddr, sizeof (AppConfig.MyIPAddr));
                        } else if (var == VAR_SUBNET_MASK)
                            memcpy((void*) &AppConfig.MyMask, (void*) &TmpAddr, sizeof (AppConfig.MyMask));
                        else if (var == VAR_SUBNET_MASK)
                            memcpy((void*) &AppConfig.MyGateway, (void*) &TmpAddr, sizeof (AppConfig.MyGateway));
                    }
                        break;

                    case VAR_DHCP:
                        if (AppConfig.Flags.bIsDHCPEnabled) {
                            if (!(argv[CurrentArg][0] - '0')) {
                                AppConfig.Flags.bIsDHCPEnabled = FALSE;
                            }
                        } else {
                            if (argv[CurrentArg][0] - '0') {
                                AppConfig.MyIPAddr.Val = 0x00000000ul;
                                AppConfig.Flags.bIsDHCPEnabled = TRUE;
                                AppConfig.Flags.bInConfigMode = TRUE;
                                DHCPReset();
                            }
                        }
                        break;
                }

                // Advance to the next variable (if present)
                CurrentArg++;
            }

            // Save any changes to non-volatile memory
            SaveAppConfig();

            // Return the same CONFIG.CGI file as a result.
            memcpypgm2ram(argv[0], CONFIG_UPDATE_PAGE, CONFIG_UPDATE_PAGE_LEN);
            break;
#endif

        default:
            memcpypgm2ram(argv[0], COMMANDS_OK_PAGE, COMMANDS_OK_PAGE_LEN);
            break;
    }
}

/******************************************************************************
 * Function:        WORD HTTPGetVar(BYTE var, WORD ref, BYTE* val)
 * PreCondition:    None
 * Input:           var         - Variable Identifier
 *                  ref         - Current callback reference with
 *                                respect to 'var' variable.
 *                  val         - Buffer for value storage.
 * Output:          Variable reference as required by application.
 * Side Effects:    None
 * Overview:        This is a callback function from HTTPServer
 *                  Whenever a variable substitution is required on any html
 *                  pages, HTTPServer calls this function 8-bit variable 
 *                  identifier, variable reference, which indicates whether
 *                  this is a first call or not.  Application should return
 *                  one character at a time as a variable value.
 * Note:            Since this function only allows one character to be 
 *                  returned at a time as part of variable value, HTTPServer()
 *                  calls this function multiple times until main application
 *                  indicates that there is no more value left for this
 *                  variable.
 *                  On begining, HTTPGetVar() is called with
 *                  ref = HTTP_START_OF_VAR to indicate that this is a first
 *                  call.  Application should use this reference to start the
 *                  variable value extraction and return updated reference.
 *                  If there is no more values left for this variable
 *                  application should send HTTP_END_OF_VAR. If there are any
 *                  bytes to send, application should return other than
 *                  HTTP_START_OF_VAR and HTTP_END_OF_VAR reference.
 *
 *                  THIS IS AN EXAMPLE CALLBACK.
 *                  MODIFY THIS AS PER YOUR REQUIREMENTS.
 ******************************************************************************/
WORD HTTPGetVar(BYTE var, WORD ref, BYTE* val) {
    // Temporary variables designated for storage of a whole return result
    // to simplify logic needed since one byte must be returned at a time.
    static BYTE VarString[32];

#if ENABLE_REMOTE_CONFIG
    static BYTE VarStringLen;
    BYTE *VarStringPtr, i, *DataSource;
#endif

#if defined(USE_TIME)
    time_t time;
    tm tm_time;
#endif    

    // Identify variable
    switch (var) {
        case VAR_LED0:
            *val = LED0_IO ? '1' : '0';
            break;

        case VAR_LED1:
            *val = LED1_IO ? '1' : '0';
            break;

        case VAR_LED2:
            *val = LED2_IO ? '1' : '0';
            break;

        case VAR_LED3:
            *val = LED3_IO ? '1' : '0';
            break;

        case VAR_LED4:
            *val = LED4_IO ? '1' : '0';
            break;

        case VAR_LED5:
            *val = LED5_IO ? '1' : '0';
            break;

        case VAR_LED6:
            *val = LED6_IO ? '1' : '0';
            break;

        case VAR_LED7:
            *val = LED7_IO ? '1' : '0';
            break;

#if defined(ENABLE_USER_PROCESS)
        case VAR_ANAIN_AN0:
            *val = AN0String[(BYTE) ref];

            if (AN0String[(BYTE) ref] == '\0')
                return HTTP_END_OF_VAR;
            else if (AN0String[(BYTE)++ref] == '\0')
                return HTTP_END_OF_VAR;
            return ref;

            //    case VAR_ANAIN_AN1:
            //        *val = AN1String[(BYTE)ref];
            //        if(AN1String[(BYTE)ref] == '\0')
            //            return HTTP_END_OF_VAR;
            //        else if(AN1String[(BYTE)++ref] == '\0' )
            //            return HTTP_END_OF_VAR;
            //        return ref;
#endif

        case VAR_DIGIN0:
            *val = BUTTON0_IO ? '1' : '0';
            break;

        case VAR_DIGIN1:
            *val = BUTTON1_IO ? '1' : '0';
            break;

        case VAR_DIGIN2:
            *val = BUTTON2_IO ? '1' : '0';
            break;

        case VAR_DIGIN3:
            *val = BUTTON3_IO ? '1' : '0';
            break;

        case VAR_STACK_VERSION:

            if (ref == HTTP_START_OF_VAR) {
                strcpypgm2ram(VarString, VERSION);
            }

            *val = VarString[(BYTE) ref];

            if (VarString[(BYTE) ref] == '\0')
                return HTTP_END_OF_VAR;
            else if (VarString[(BYTE)++ref] == '\0')
                return HTTP_END_OF_VAR;
            return ref;

        case VAR_STACK_DATE:
            if (ref == HTTP_START_OF_VAR) {
                strcpypgm2ram(VarString, __DATE__ " " __TIME__);
            }

            *val = VarString[(BYTE) ref];

            if (VarString[(BYTE) ref] == '\0')
                return HTTP_END_OF_VAR;
            else if (VarString[(BYTE)++ref] == '\0')
                return HTTP_END_OF_VAR;
            return ref;

        case VAR_IPCNTR_TX:
            if (ref == HTTP_START_OF_VAR) {
                ultoa(IP_TX_pktcnt, (char *) VarString);
            }

            *val = VarString[(BYTE) ref];

            if (VarString[(BYTE) ref] == '\0')
                return HTTP_END_OF_VAR;
            else if (VarString[(BYTE)++ref] == '\0')
                return HTTP_END_OF_VAR;
            return ref;

        case VAR_IPCNTR_RX:
            if (ref == HTTP_START_OF_VAR) {
                ultoa(IP_RX_pktcnt, (char *) VarString);
            }

            *val = VarString[(BYTE) ref];

            if (VarString[(BYTE) ref] == '\0')
                return HTTP_END_OF_VAR;
            else if (VarString[(BYTE)++ref] == '\0')
                return HTTP_END_OF_VAR;
            return ref;

        case VAR_DATE:
        case VAR_TIME:
            if (ref == HTTP_START_OF_VAR) {
#if defined(USE_TIME)
                if (!IsClockValid()) {
                    if (var == VAR_DATE)
                        strcpypgm2ram(VarString, "--/--/--");
                    else
                        strcpypgm2ram(VarString, "--:--");
                } else {
                    time = GetTimeTick();
                    offtime(&tm_time, time, LOCAL_OFFSET_SECS);
                    if (var == VAR_DATE)
                        asctime(&tm_time, &VarString[0], 3);
                    else
                        asctime(&tm_time, &VarString[0], 6);
                }
#else
                strcpypgm2ram(VarString, "n/a");
#endif
            }

            *val = VarString[(BYTE) ref];

            if (VarString[(BYTE) ref] == '\0')
                return HTTP_END_OF_VAR;
            else if (VarString[(BYTE)++ref] == '\0')
                return HTTP_END_OF_VAR;
            return ref;

#if ENABLE_REMOTE_CONFIG
        case VAR_MAC_ADDRESS:
            if (ref == HTTP_START_OF_VAR) {
                VarStringLen = 2 * 6 + 5; // 17 bytes: 2 for each of the 6 address bytes + 5 octet spacers

                // Format the entire string
                i = 0;
                VarStringPtr = VarString;

                while (1) {
                    *VarStringPtr++ = btohexa_high(AppConfig.MyMACAddr.v[i]);
                    *VarStringPtr++ = btohexa_low(AppConfig.MyMACAddr.v[i]);
                    if (++i == 6)
                        break;
                    *VarStringPtr++ = '-';
                }
            }

            // Send one byte back to the calling function (the HTTP Server)
            *val = VarString[(BYTE) ref];

            if ((BYTE)++ref == VarStringLen)
                return HTTP_END_OF_VAR;

            return ref;

        case VAR_SERIAL_NUMBER:
            if (ref == HTTP_START_OF_VAR) {
                // Obtain the serial number.  For this demo, we will call
                // the two low bytes of our MAC address (required to be
                // organization assigned) our board's serial number
                itoa(AppConfig.SerialNumber.Val, VarString);
                VarStringLen = strlen(VarString);
            }

            // Send one byte back to the calling function (the HTTP Server)
            *val = VarString[(BYTE) ref];

            // If this is the last byte to be returned, return
            // HTTP_END_OF_VAR so the HTTP server won't keep calling this
            // application callback function
            if ((BYTE)++ref == VarStringLen)
                return HTTP_END_OF_VAR;

            return ref;

        case VAR_IP_ADDRESS:
        case VAR_SUBNET_MASK:
        case VAR_GATEWAY_ADDRESS:
            // Check if ref == 0 meaning that the first character of this
            // variable needs to be returned
            if (ref == HTTP_START_OF_VAR) {
                // Decide which 4 variable bytes to send back
                if (var == VAR_IP_ADDRESS)
                    DataSource = (BYTE*) & AppConfig.MyIPAddr;
                else if (var == VAR_SUBNET_MASK)
                    DataSource = (BYTE*) & AppConfig.MyMask;
                else if (var == VAR_GATEWAY_ADDRESS)
                    DataSource = (BYTE*) & AppConfig.MyGateway;

                // Format the entire string
                VarStringPtr = VarString;
                i = 0;

                while (1) {
                    itoa((WORD) * DataSource++, VarStringPtr);
                    VarStringPtr += strlen(VarStringPtr);
                    if (++i == 4)
                        break;
                    *VarStringPtr++ = '.';
                }
                VarStringLen = strlen(VarString);
            }

            // Send one byte back to the calling function (the HTTP Server)
            *val = VarString[(BYTE) ref];

            // If this is the last byte to be returned, return
            // HTTP_END_OF_VAR so the HTTP server won't keep calling this
            // application callback function
            if ((BYTE)++ref == VarStringLen)
                return HTTP_END_OF_VAR;

            return ref;

        case VAR_DHCP_TRUE:
        case VAR_DHCP_FALSE:
            // Check if ref == 0 meaning that the first character of this
            // variable needs to be returned
            if (ref == HTTP_START_OF_VAR) {
                if ((var == VAR_DHCP_TRUE) ^ AppConfig.Flags.bIsDHCPEnabled)
                    return HTTP_END_OF_VAR;

                VarStringLen = 7;
                memcpypgm2ram(VarString, "checked", 7);
            }

            *val = VarString[(BYTE) ref];

            if ((BYTE)++ref == VarStringLen)
                return HTTP_END_OF_VAR;

            return ref;
#endif
    }

    return HTTP_END_OF_VAR;
}
#endif

/******************************************************************************
 * The following functions provide the specific hardware and application      *
 * configuration initialization                                               *
 ******************************************************************************/

//*****************************************************************************
// InitializeBoard sets the direction and initial value for all I/O ports
// and peripheral configurations including the serial SPI interface and 
// UART interface
//
// To avoid undesired results is important that the correct values for each
// configuration macros is defined in the hardware configuration file for 
// each particular development board or reference design.
//
// You may need to modify the code below according to your particular hardware 
// configuration and application.
//

static void InitializeBoard(void) {

    // Oscillator configuration / tunning for specific devices
#if defined(__dsPIC33F__) || defined(__PIC24H__)
    PLLFBD = 38; // Multiply by 40 for 160MHz VCO output
    // (8MHz XT oscillator)
    CLKDIV = 0x0000; // FRC: divide by 2, PLLPOST: divide by 2,
    // PLLPRE: divide by 2
#elif defined(__PIC18FXXJ60)
    OSCTUNE = 0x40; // Enable 4 x PLL
#endif

    // I/O Peripheral Pin Select configuration for specific devices
#if defined(PIC24FJ64_NIC28)
    // The PIC24FJ64GA002 supports Peripheral Pin Select, then before we
    // initialize all I/O ports and peripheral registers we must map
    // the I/O of the peripherals we'll use to their assigned pins

    // SPI1 Interface Pin Assignments
    RPINR20bits.SDI1R = 9; // Make SDI1 RP9
    RPOR4bits.RP8R = 7; // Make RP8 SDO1
    RPOR3bits.RP7R = 8; // Make RP7 SCK1 OUT

    // UART RS232 Interface RX & TX Pin Assignments    
#if UART_NO == 1
    // UART1 Interface Pin Assignments
    RPINR18bits.U1RXR = 15; // Make UART1 RX RP15 Test with UART 1
    RPOR7bits.RP14R = 3; // Make RP14 UART1 TX Test with UART 1
#else
    // UART2 Interface Pin Assignments
    RPINR19bits.U2RXR = 15; // Make UART2 RX RP15 Test with UART 2
    RPOR7bits.RP14R = 5; // Make RP14 UART2 TX Test with UART 2
#endif

    AD1PCFG = 0x1fff; // All Digital I/O

#endif // PIC24FJ64_NIC28

    // Set direction and initial default valuefor GPIO Ports
#if defined(INIT_PORTA)
    LATA = INIT_PORTA;
    TRISA = INIT_TRISA;
#endif

#if defined(INIT_PORTB)
    LATB = INIT_PORTB;
    TRISB = INIT_TRISB;
#endif

#if defined(INIT_PORTC)
    LATC = INIT_PORTC;
    TRISC = INIT_TRISC;
#endif

#if defined(INIT_PORTD)
    LATD = INIT_PORTD;
    TRISD = INIT_TRISD;
#endif

#if defined(INIT_PORTE)
    LATE = INIT_PORTE;
    TRISE = INIT_TRISE;
#endif

#if defined(INIT_PORTF)
    LATF = INIT_PORTF;
    TRISF = INIT_TRISF;
#endif

#if defined(INIT_PORTG)
    LATG = INIT_PORTG;
    TRISG = INIT_TRISG;
#endif

#if defined(INIT_PORTH)
    LATH = INIT_PORTH;
    TRISH = INIT_TRISH;
#endif

#if defined(INIT_PORTJ)
    LATJ = INIT_PORTJ;
    TRISJ = INIT_TRISJ;
#endif

    // Initialize serial RS232 Interface
#if defined(__C30__)
    UART_BRG = SPBRG_VAL; // Set baud rate and enable UART serial
    UART_MODE = 0x8000; // RS232 interface
    UART_STA = 0x0400;
    __C30_UART = UART_NO;
#else
    UART_TXSTA = 0b00100000; // Set baud rate and enable UART serial
    UART_RCSTA = 0b10010000; // RS232 interface

#if defined(USART_USE_BRGH_HIGH)
    UART_TXSTAbits.BRGH = 1;
#endif

    UART_SPBRG = SPBRG_VAL;
#endif      

#if defined(__C30__)
    /* JA 061807 Analog features commented for this version ...
        // ADC
        AD1CON1 = 0x84E4;          // Turn on, auto sample start, auto-convert,
                                   // 12 bit mode (on parts with a 12bit A/D)
        AD1CON2 = 0x0404;          // AVdd, AVss, int every 2 conversions,
                                   // MUXA only, scan
        AD1CON3 = 0x1003;          // 16 Tad auto-sample, Tad = 3*Tcy
        AD1CHS = 0;                // Input to AN0 (potentiometer)
        AD1PCFGbits.PCFG5 = 0;     // Disable digital input on AN5 (pot)
        AD1PCFGbits.PCFG4 = 0;     // Disable digital input on AN4 (temp sensor)
        AD1CSSL = 1<<5;            // Scan pot

    //    IFS0bits.AD1IF = 0;      // Enable ADC interrupt
    //    IEC0bits.AD1IE = 1;

     */
#else  // PIC18 

    ADCON0 = INIT_ADCON0; // Set up analog features of PORTA
    ADCON1 = INIT_ADCON1;

#if defined(ADCON2) && defined(INIT_ADCON2)
    ADCON2 = INIT_ADCON2;
#endif

    //    PIR1bits.ADIF = 0;       // Enable ADC interrupt
    //    PIE1bits.ADIE = 1;

    INTCON2bits.RBPU = 0; // Enable internal PORTB pull-ups

    RCONbits.IPEN = 1; // Enable Interrupts
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
#endif

    // If the ENC28J60 Ethernet controller is used set the proper
    // configuration for the SPI serial interface.
    // The ENC_SPICON1_CFG configuration value must be defined in the
    // hardware configuration file.
#if defined(USE_ENC28J60)
    ENC_SPICON1 = ENC_SPICON1_CFG;
#if defined(ENC_SPICON2)
    ENC_SPICON2 = ENC_SPICON2_CFG;
#endif
    ENC_SPISTAT = ENC_SPISTAT_CFG;
#endif

    // If an external serial EEPROM with SPI interface is used, check if the
    // interface is shared with the Ethernet controller if not we must set
    // the proper configuration.
    // The EEPROM_SPICON1_CFG configuration value must be defined in the
    // hardware configuration file.
    // If the ENC27J60 and serial EEPROM share the SPI interface the
    // configuration must support both devices, if a different clock speed or
    // configuration is required for the serial EEPROM define the proper
    // configuration and the EEPROM_SAVE_SPI_CFG macro in the hardwware
    // configuration file.
#if defined(USE_SPIEEPROM) && ((EEPROM_SPICON1 != ENC_SPICON1) || !defined(USE_ENC28J60))
    EEPROM_SPICON1 = EEPROM_SPICON1_CFG;
#if defined(EEPROM_SPICON2)
    EEPROM_SPICON2 = EEPROM_SPICON2_CFG;
#endif
    EEPROM_SPISTAT = EEPROM_SPISTAT_CFG;
#endif
}

//*****************************************************************************
// InitAppConfig sets the value of the DHCP flag and if available checks
// the external serial EEPROM for a valid configuration vector (first byte
// must read 0x55), if so loads the configuration vector with the values
// stored in the serial EEPROM
//

static void InitAppConfig(void) {
#if defined(MPFS_USE_EEPROM)
    BYTE c, *p;
#endif

#if defined(STACK_USE_DHCP) || defined(STACK_USE_IP_GLEANING)
    AppConfig.Flags.bIsDHCPEnabled = TRUE;
#else
    AppConfig.Flags.bIsDHCPEnabled = FALSE;
#endif

#if defined(MPFS_USE_EEPROM)
    p = (BYTE*) & AppConfig;

    XEEBeginRead(EEPROM_CONTROL, 0x00);
    c = XEERead();
    XEEEndRead();

    // Check for a valid configuration vector
    if (c == 0x55) {
        XEEBeginRead(EEPROM_CONTROL, 0x01);

        for (c = 0; c < sizeof (AppConfig); c++)
            *p++ = XEERead();

        XEEEndRead();
    } else
        SaveAppConfig();
#endif
}


/******************************************************************************
 * The following function shows how to implement a process that is called     *
 * periodically from the main application to perform a specific task such as  *
 * acquiring the value for an analog input and converting it to a string      *
 ******************************************************************************/
#if defined(ENABLE_USER_PROCESS)

static void ProcessIO(void) {
#if defined(__C30__)
    //  Note: floats and sprintf uses a lot of program memory/CPU cycles, so it's commented out
    //    float Temperature;
    //
    //    // Convert temperature result into ASCII string
    //    Temperature = ((float)(ADC1BUF0)*(3.3/1024.)-0.500)*100.;
    //    sprintf(AN1String, "%3.1f�C", Temperature);

    // Convert potentiometer result into ASCII string
    itoa((unsigned) ADC1BUF0, AN0String);
#else
    // AN0 should already be set up as an analog input
    ADCON0bits.GO = 1;

    // Wait until A/D conversion is done
    while (ADCON0bits.GO);

    // AD converter errata work around (ex: PIC18F87J10 A2)
#if !defined(__18F452)
    PRODL = ADCON2;
    ADCON2bits.ADCS0 = 1;
    ADCON2bits.ADCS1 = 1;
    ADCON2 = PRODL;
#endif

    // Convert 10-bit value into ASCII string
    itoa(*((WORD*) (&ADRESL)), AN0String);
#endif
}
#endif // ENABLE_USER_PROCESS

/******************************************************************************
 * Main Application code                                                      *
 ******************************************************************************/
#if defined(__C30__)
int main(void)
#else

void main(void)
#endif
{
#if defined(USE_LCD) && (LCD_ROWS == 2)
    BYTE lcd_cycle = 0;
#endif

#if defined(USE_TIME)
    time_t time;
    tm tm_time;
#endif

    char buffer[30];
    static TICK t = 0;

    InitializeBoard(); // Initialize hardware

#if defined(USE_LCD)
    LCDInit(); // Initialize LCD module
    DelayMs(50);

    // Load in some custom chars on the LCD character generation RAMsadas
    LCDLoadCGRAM(1, (ROM char *) &CGCHAR01);
    LCDLoadCGRAM(2, (ROM char *) &CGCHAR02);
    LCDLoadCGRAM(3, (ROM char *) &CGCHAR03);
    LCDLoadCGRAM(4, (ROM char *) &CGCHAR04);
    LCDLoadCGRAM(5, (ROM char *) &CGCHAR05);
    LCDLoadCGRAM(6, (ROM char *) &CGCHAR06);

    // Display software version and current IP address
    strcpypgm2ram((char *) &LCDBuffer[0][0], (ROM char *) "\001\002\003Microchip TCP");
    strcpypgm2ram((char *) &LCDBuffer[1][0], (ROM char *) "\004\005\006 v" VERSION);

    LCDRefresh();
    DelayMs(250);
#endif

#if defined(USE_TIME)
    SetTimeTick(220924800ul); // Jan 1 2007, 00:00:00 UTC
#endif

    TickInit(); // Initialize tick manager

#if defined(USE_TIME) && defined(TIME_SOURCE_32KTIMER)
    Init32KTimer();
#endif

#if defined(MPFS_USE_EEPROM) || defined(MPFS_USE_PGRM)
    MPFSInit(); // Initialize file system
#endif

    // Load the default NetBIOS Host Name
    memcpypgm2ram(AppConfig.NetBIOSName, DEFAULT_NETBIOS_NAME, 16);
    FormatNetBIOSName((char *) &AppConfig.NetBIOSName);

    InitAppConfig(); // Load configuration vector

#if defined(ENABLE_BUTTON0_CONFIG)
    if (BUTTON0_IO == 0) {
        // If BUTTON0 is pressed during startup initiate the
        // configuration menu via the serial interface
        SetConfig();
    }
#endif

    StackInit(); // Initialize TCP/IP stack

#if defined(STACK_USE_HTTP_SERVER)
    HTTPInit(); // Start HTTP server
#endif

#if defined(STACK_USE_FTP_SERVER)
    FTPInit(); // Start FTP server
#endif

#if defined(STACK_USE_DHCP) || defined(STACK_USE_IP_GLEANING)
    if (!AppConfig.Flags.bIsDHCPEnabled) {
        // Force IP address display update.
        myDHCPBindCount = 1;

#if defined(STACK_USE_DHCP)
        DHCPDisable();
#endif
    }

#endif

    // Once all items are initialized, go into infinite loop and let stack
    // items execute their tasks.
    // If application needs to perform its own task, it should be done at
    // the end of while loop.
    //
    // Note that this is a "co-operative mult-tasking" mechanism where every
    // task performs its job (whether all in one shot or part of it) and
    // returns so that other tasks can do their job.
    // If a task needs very long time to do its job, it must broken
    // down into smaller pieces so that other tasks can have CPU time.

    while (1) {
        if (TickGetDiff(TickGet(), t) >= TICK_SECOND / 2) {
            t = TickGet();
            LED0_IO ^= 1; // Blink system LED

#if defined(USE_LCD)
            UpdateLCD();
#endif
        }

        // This task performs normal stack task including checking for
        // incoming packet, type of packet and calls appropriate stack
        // function to process it
        StackTask();

#if defined(STACK_USE_HTTP_SERVER)
        HTTPServer(); // Execute HTTP server FSM
#endif

#if defined(STACK_USE_FTP_SERVER)
        FTPServer(); // Execute FTP server FSM
#endif

#if defined(STACK_USE_ANNOUNCE)
        DiscoveryTask(); // Execute announce function
#endif

#if defined(STACK_USE_TCP_EXAMPLE1)
        GenericTCPClient(); // Execute client example
#endif

#if defined(STACK_USE_UDPTEST)
        UDPTest(); // Execute UDP Test routine
#endif

#if defined(ENABLE_USER_PROCESS)     
        ProcessIO(); // Execute analog I/O process

        // ADD YOUR SPECIFIC TASKS HERE //
#endif

        // For DHCP information, display how many times we have renewed the IP
        // configuration since last reset.
        if (DHCPBindCount != myDHCPBindCount) {
            myDHCPBindCount = DHCPBindCount;
            //putrsUART(NewIP);
            IPAddressToString(&AppConfig.MyIPAddr, buffer);
            //putsUART(buffer);
            //putrsUART(CRLF);

#if defined(STACK_USE_ANNOUNCE)
            AnnounceIP();
#endif

        }
    }
}
