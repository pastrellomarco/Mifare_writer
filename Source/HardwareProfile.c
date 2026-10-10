#include "..\Header\Compiler.h"
#include "..\Header\HardwareProfile.h"
//#include <adc.h>
//#include <i2c.h>
#include "..\Header\main.h"
#include "..\Header\Variabili.h"
//#include "..\Header\Orologio.h"


#ifdef DEBUG
	_CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV2 & IOL1WAY_ON)
	_CONFIG1( JTAGEN_OFF &  BKBUG_ON & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2 /*& WDTPS_PS1204 & PLL_96MHZ_ON*/) 
#else
	_CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV2 & IOL1WAY_ON)  // watchdog a 8sec
	_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_ON & ICS_PGx2  & WDTPS_PS4096/* & PLL_96MHZ_ON*/)   // abilitato watchdog
#endif
/***********************************************************************
*
*						USART_Init
*
*				Inizializzazione della porta UARt per la RS485
*
************************************************************************/

void USART_Init(void)
{

// configurazione del registro U1MODE  
U1MODEbits.UARTEN = 0; 				// Bit15 TX, RX DISABLED, ENABLE at end of func  
U1MODEbits.USIDL = 0; 				// Bit13 Continue in Idle  
U1MODEbits.IREN = 0; 				// Bit12 No IR translation  
U1MODEbits.RTSMD = 0; 				// Bit11 Simplex Mode  
U1MODEbits.UEN = 0; 				// Bits8,9 TX,RX enabled, CTS,RTS not
U1MODEbits.WAKE = 0; 				// Bit7 No Wake up (since we don't sleep here)  
U1MODEbits.LPBACK = 0; 				// Bit6 No Loop Back  
U1MODEbits.ABAUD = 0; 				// Bit5 No Autobaud (would require sending '55')  
U1MODEbits.RXINV = 0; 				// Bit4 RX reversed when in IdleState 
U1MODEbits.PDSEL = 0; 				// Bits1,2 8bit, No Parity  
U1MODEbits.STSEL = 0; 				// Bit0 One Stop Bit  

#ifdef UART_HIGHSPEED
	U1MODEbits.BRGH = 1; 				// Bit3 16 clocks per bit period  = high speed mode
	U1BRG   = 3; 	//U1BRG   = (16M/(4 *MYBAUD_RATE))-1; con BRGH = 1 // baudrate = 1M bits/sec 
#else
	U1MODEbits.BRGH = 0; 				// Bit3 16 clocks per bit period  = high speed mode
	U1BRG   = 8; 	//U1BRG   = (16M/(16 *MYBAUD_RATE))-1; con BRGH = 0 //baudrate = 115200 bits/sec 
#endif

// errore = 0,02 %

// configurazione del registro U1STA 
 
U1STAbits.UTXISEL1 = 0; 			// Bit15 Int when Char is transferred (1/2 config!)  
U1STAbits.UTXISEL0 = 1; 			// Bit13 Other half of Bit15  
U1STAbits.UTXINV = 0; 				// Bit14 TX reversed when in IdleState
U1STAbits.UTXBRK = 0; 				// Bit 11 Disabled  
U1STAbits.UTXEN = 0; 				// Bit10 TX pins controlled by periph  
U1STAbits.UTXBF = 0; 				// Bit9 *Read Only Bit*  
U1STAbits.TRMT = 0; 				// Bit8 *Read Only bit*  
U1STAbits.URXISEL = 0; 				// Bits6,7 Int. on character recieved  
U1STAbits.ADDEN = 0; 				// Bit5 Address Detect Disabled  
U1STAbits.RIDLE = 0; 				// Bit4 *Read Only Bit*  
U1STAbits.PERR = 0; 				// Bit3 *Read Only Bit*  
U1STAbits.FERR = 0; 				// Bit2 *Read Only Bit*  
U1STAbits.OERR = 0; 				// Bit1 *Read Only Bit*  
U1STAbits.URXDA = 0; 				// Bit0 *Read Only Bit*  

// Pulizia ed impostazione degli interrupt della porta UART2 - RS485

IFS0bits.U1TXIF = 0; 				// Clear the Transmit Interrupt Flag  
IEC0bits.U1TXIE = 0; 				// disable Transmit Interrupts  
IFS0bits.U1RXIF = 0; 				// Clear the Recieve Interrupt Flag  
IEC0bits.U1RXIE = 1; 				// Enable Recieve Interrupts  

U1MODEbits.UARTEN = 1; 				// Enable UART 
U1STAbits.UTXEN = 1; 				// Enable Transmitter

//IPC7=(IPC7|0x0700);					// Interrupt priority= Priorità Interrupt alta per il canale RS485
IPC2bits.U1RXIP = 6;					// Interrupt priority= Priorità Interrupt alta per il canale RS485

U1MODEbits.PDSEL0=0;   				// TX 8-bit
U1MODEbits.PDSEL1=0;
}	


/*********************************************************************
*
*						BoardInit
*				Inzializzza le perifercihe HW
 ********************************************************************/
void BoardInit(void)
{
TRISB=0b1111001011111111;
//		5432109876543210
TRISC=0b1001111111111111;
//		5432109876543210
TRISD=0b1111000100111101;
//		5432109876543210
TRISE=0b1111111110000000;
//		5432109876543210
TRISF=0b1111111111110100;
//		5432109876543210
TRISG=0b1111111001111111;





//CLKDIV|=0b0000000001000000; 		// USB/2= 16MHz clock di sistema:importante per funzionamento RFID
CLKDIV=0;
//ADCinit();							// Inzializzazione ADC

__builtin_write_OSCCONL(OSCCON & 0xBF);				// Sblocco registro configurazione

/*************** CONFIGURAZIONE PIEDINO INPUT COMPARE *********************************/


//RPINR7bits.IC1R = 13;  // RP13(RB2) da definire per rtc

/******************* PORTA PWM IR ********************************************/

//RPOR10bits.RP21R = 19;		   		// OUTPUT PWM 2 IR (RP21) con funzione 19

/******************* PORTA PWM BUZZER ********************************************/

//RPOR12bits.RP24R = 18;		   		// OUTPUT PWM 1 Buzzer (RP21) con funzione 18

/*************** CONFIGURAZIONE SPI *********************************/
#if defined(SPI_HW)
    // Configure SPI1 PPS pins (ENC28J60/ENCX24J600/MRF24W or other PICtail Plus cards)
    RPOR2bits.RP4R = 8;        // Assign RP0 to SCK1 (output)
    RPOR1bits.RP3R = 7;        // Assign RP15 to SDO1 - MOSI (output)

    RPINR20bits.SDI1R = 2;     // Assign RP23 to SDI1 - MISO(input)

#endif
//RPINR0bits.INT1R= 3;   				// INT mifare(RP3)
//

/*************** CONFIGURAZIONE USART (RS485) *********************************/
#ifdef USA_485
	RPINR18bits.U1RXR = 21;        		// RX_485 (RP21)
	RPOR13bits.RP26R= 3;          		// TX_485 (RP26) con funzione 3 
#endif

/*************** CONFIGURAZIONE INTERRPUT PULS PROG *********************************/

//RPINR1bits.INT2R = 29;        		// Pulsante Programmazione (RP16)

/*************** CONFIGURAZIONE INTERRPUT INGRESSO OPTO *********************************/

//RPINR1bits.INT3R = 2;        		// Ingresso OptoIsolatore (RP16)


/*************** ASSEGNAZIONE VALORI INIZIALI DEI PIN DELLE PORTE DI COMUNICAZIONE *********************************/
__builtin_write_OSCCONL(OSCCON | 0x40);		// blocco registro configurazione

//	   5432109876543210
LATB=0b0000000000000000;
LATC=0b0000000000000000;
LATD=0b0000000000000000;
LATE=0b0000000000000000;
LATF=0b0000000000000000;
LATG=0b0000000000000000;

/******************* CONFIGURAZIONE ANALOGICHE ************************************/

AD1PCFGH=0x0000;				// Tutti PIN digitali
//			5432109876543210
AD1PCFGL= 0xFFFF;				// Tutte PIN digitali tranne RB0(analogico - Sonda temp)




//CNPU4=0b1111110000000000;  					// abilitazione pull up per dipswitch

/*************** CONFIGURAZIONE TIMER **************/  
   
T4CON = 0;              // Timer reset
IFS1bits.T4IF = 0;      // Reset Timer4 interrupt flag 
IPC6bits.T4IP = 4;      // Timer4 Interrupt priority level=4 
IEC1bits.T4IE = 1;      // Enable Timer4 interrupt   
PR4=625;//104		        // Timer4 period register
T4CONbits.TCS = 0;      // Timer4 Clock= Internal  
T4CONbits.TCKPS=3;		// impostazione rpescaler

T4CONbits.TON = 1;     // Enable Timer1 and start the counter

/*************** ATTIVAZIONE INTERRUPT **************/  

//INTCON2bits.INT0EP = 1;  		// Interruput Mifare con Edge Negativo
#ifdef USA_485       
	IEC0bits.U1RXIE=1;    				// Abilitazione Interrupt porta Seriale
#endif
/*************** ATTIVAZIONE PULL-UP INTERNI **************/  

//CNEN1bits.CN15IE = 1;			// Attivazione pull-up per Cambiamento stato INGRESSO 1 (configurazione 15)
//CNEN2bits.CN16IE = 1;			// Attivazione pull-up per Cambiamento stato INGRESSO 2 (configurazione 16)
  
/********************** IMPOSTAZIONI SPI ***********************/

#if defined(HW_SPI)
	SPI1CON1 = 0b0000001100111011;		// 8mhz
	SPI1STAT = 0x8000;
#endif
}

