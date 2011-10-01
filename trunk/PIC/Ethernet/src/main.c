
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

#if defined(MPFS_USE_EEPROM) || defined(MPFS_USE_PGRM)
    MPFSInit(); // Initialize file system
#endif

    // Load the default NetBIOS Host Name
    memcpypgm2ram(AppConfig.NetBIOSName, DEFAULT_NETBIOS_NAME, 16);
    FormatNetBIOSName((char *) &AppConfig.NetBIOSName);

    InitAppConfig(); // Load configuration vector
    StackInit(); // Initialize TCP/IP stack

#if defined(STACK_USE_HTTP_SERVER)
    HTTPInit(); // Start HTTP server
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

        }

        // This task performs normal stack task including checking for
        // incoming packet, type of packet and calls appropriate stack
        // function to process it
        StackTask();

#if defined(STACK_USE_HTTP_SERVER)
        HTTPServer(); // Execute HTTP server FSM
#endif

        // For DHCP information, display how many times we have renewed the IP
        // configuration since last reset.
        if (DHCPBindCount != myDHCPBindCount) {
            myDHCPBindCount = DHCPBindCount;
            IPAddressToString(&AppConfig.MyIPAddr, buffer);
        }
    }
}
