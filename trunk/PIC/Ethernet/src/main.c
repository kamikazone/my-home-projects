
#define _MAIN_C
#include "include/config.h"

#pragma config OSC=EC, PWRT=ON, BOREN=OFF, WDT=OFF, MCLRE=OFF, PBADEN=OFF, LVP=OFF, XINST=OFF

/******************************************************************************
 * Include specific headers files required for this application based on the  *
 * hardware configuration and options configured in the config.h file         *
 ******************************************************************************/
#include "include/delay.h"
#include "net/include/stacktsk.h"
#include "net/include/tick.h"
#include "net/include/mac.h"
#include "net/include/helpers.h"


#if defined(STACK_USE_DHCP)
#include "net/include/dhcp.h"
#endif

#if defined(MPFS_USE_EEPROM) || defined(MPFS_USE_PGRM)
#include "mpfs/include/mpfs.h"
#endif



#if defined(STACK_USE_HTTP_SERVER)
#include "net/include/http.h"
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

#pragma interruptlow LowISR
void LowISR(void) {
    TickUpdate();
}

#pragma code lowVector=0x18
void LowVector(void) {
    _asm goto LowISR _endasm
}
#pragma code // Return to default code section


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
                        break;

                    case CMD_LED2: // NAME = 1
                        LED2_IO ^= 1; // Toggle LED
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    case 8:
                        break;
                    case 9:
                        break;
                }
            } else;

            memcpypgm2ram(argv[0], COMMANDS_OK_PAGE, COMMANDS_OK_PAGE_LEN);

            break;

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
            }

            *val = VarString[(BYTE) ref];

            if (VarString[(BYTE) ref] == '\0')
                return HTTP_END_OF_VAR;
            else if (VarString[(BYTE)++ref] == '\0')
                return HTTP_END_OF_VAR;
            return ref;
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
    // Set direction and initial default valuefor GPIO Ports
    LATA = INIT_PORTA;
    TRISA = INIT_TRISA;
    LATB = INIT_PORTB;
    TRISB = INIT_TRISB;
    LATC = INIT_PORTC;
    TRISC = INIT_TRISC;
    // Initialize serial RS232 Interface
    UART_TXSTA = 0b00100000; // Set baud rate and enable UART serial
    UART_RCSTA = 0b10010000; // RS232 interface

#if defined(USART_USE_BRGH_HIGH)
    UART_TXSTAbits.BRGH = 1;
#endif

    UART_SPBRG = SPBRG_VAL;
    ADCON0 = INIT_ADCON0; // Set up analog features of PORTA
    ADCON1 = INIT_ADCON1;
    INTCON2bits.RBPU = 0; // Enable internal PORTB pull-ups
    RCONbits.IPEN = 1; // Enable Interrupts
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    ENC_SPICON1 = ENC_SPICON1_CFG;
    ENC_SPISTAT = ENC_SPISTAT_CFG;
}

//*****************************************************************************
// InitAppConfig sets the value of the DHCP flag and if available checks
// the external serial EEPROM for a valid configuration vector (first byte
// must read 0x55), if so loads the configuration vector with the values
// stored in the serial EEPROM
//

static void InitAppConfig(void) {

#if defined(STACK_USE_DHCP) || defined(STACK_USE_IP_GLEANING)
    AppConfig.Flags.bIsDHCPEnabled = TRUE;
#else
    AppConfig.Flags.bIsDHCPEnabled = FALSE;
#endif

}

/******************************************************************************
 * Main Application code                                                      *
 ******************************************************************************/
void main(void)
{
    char buffer[30];
    static TICK t = 0;
    InitializeBoard(); // Initialize hardware
    TickInit(); // Initialize tick manager
    MPFSInit(); // Initialize file system
    // Load the default NetBIOS Host Name
    memcpypgm2ram(AppConfig.NetBIOSName, DEFAULT_NETBIOS_NAME, 16);
    FormatNetBIOSName((char *) &AppConfig.NetBIOSName);
    InitAppConfig(); // Load configuration vector
    StackInit(); // Initialize TCP/IP stack
    HTTPInit(); // Start HTTP server
#if defined(STACK_USE_DHCP) || defined(STACK_USE_IP_GLEANING)
    if (!AppConfig.Flags.bIsDHCPEnabled) {
        // Force IP address display update.
        myDHCPBindCount = 1;
    #if defined(STACK_USE_DHCP)
        DHCPDisable();
    #endif
    }
#endif

    while (1)
    {
        if (TickGetDiff(TickGet(), t) >= TICK_SECOND / 2)
        {
            t = TickGet();
            LED0_IO ^= 1; // Blink system LED
        }
        StackTask();
        HTTPServer(); // Execute HTTP server FSM
        /*// For DHCP information, display how many times we have renewed the IP
        // configuration since last reset.
        if (DHCPBindCount != myDHCPBindCount) {
            myDHCPBindCount = DHCPBindCount;
            IPAddressToString(&AppConfig.MyIPAddr, buffer);
        }*/
    }
}
