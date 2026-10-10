
/************************** INGRESSI ********************/

#define ING_1	 	    PORTDbits.RD2		// Ingresso OPTO_1 Esterno
#define ING_2	 	    PORTDbits.RD3		// Ingresso OPTO_2 Esterno
#define ING_3	 	    PORTDbits.RD4		// Ingresso OPTO_3 Esterno
#define ING_4	 	    PORTBbits.RB12		// Ingresso OPTO_4 Esterno
#define ING_5	 	    PORTBbits.RB13		// Ingresso OPTO_4 Esterno

#define ING_CHIUSO		0		// indico lo stato logico dell'ingresso quando viene chiuso
#define ING_APERTO		1		// indico lo stato logico dell'ingresso quando viene Aperto



/************************** USCITE ********************/

//#define LED_TX_485          LATEbits.LATE6   		// Led verde
//#define LED_RX_485         	LATEbits.LATE7   		// Led rosso
//
#define LED_0		LATBbits.LATB11    			 	// Elettroserratura	(OC)	(OUT1)			
#define LED_1		LATBbits.LATB10   			 	// Elettroserratura	(OC)	(OUT1)			
#define LED_2		LATGbits.LATG8    			 	// Elettroserratura	(OC)	(OUT1)			
#define LED_3		LATDbits.LATD6    			 	// Elettroserratura	(OC)	(OUT1)			
#define LED_4		LATDbits.LATD7    			 	// Elettroserratura	(OC)	(OUT1)			
#define LED_5		LATEbits.LATE0    			 	// Elettroserratura	(OC)	(OUT1)			
#define LED_6		LATFbits.LATF1    			 	// Elettroserratura	(OC)	(OUT1)			
#define LED_7		LATFbits.LATF0    			 	// Elettroserratura	(OC)	(OUT1)			


#define LED_R		LED_2   			 	// Elettroserratura	(OC)	(OUT1)			
#define LED_CPU           	LATBbits.LATB8   		// Led Rosso
#define LED_NET          	LATEbits.LATE6   		// Led Blue


/************************ SPI - DISPLAY ************************/

#define LED_RETRO_TFT   	LATEbits.LATE3           // I

#define CS_TFT   	LATEbits.LATE1           // I
#define RST_TFT   	LATEbits.LATE2           // I
#define RS_TFT   	LATEbits.LATE4           // I

#define SPI_SDO1 	LATDbits.LATD10	
#define SPI_SCK1 	LATDbits.LATD9
#define SPI_SDI1	PORTDbits.RD8 

#define LCD_SCK_TFT 	SPI_SCK1       //clock the byte out
#define LCD_SDO_TFT		SPI_SDO1
#define LCD_SDI_TFT		SPI_SDI1


//#define IRQ 		    PORTDbits.RD10   				// int mifare
#define SDO1 		    LATDbits.LATD10   				// MOSI MIfare
#define SCK1 		    LATDbits.LATD9   				// CLOCK MIfare   
#define SDI1 		    PORTDbits.RD8    				// MISO MIfare

#define MF522_RST	    LATCbits.LATC13   				// RESET MIfare
#define MF522_CS 	    LATDbits.LATD11  				// CHIP SELECT MIfare

/************************ RS485 ************************/

#define EN_485 		    LATEbits.LATE5   			// Enable 485
//#define TX_485 		    LATFbits.LATF4   			// PIn trasmissione 485
//#define RX_485 		    PORTFbits.RF3    			// PIn ricezione 485
//


/************************** INTERRUPT *******************/

//#define CARDIF          IFS0bits.INT0IF
//#define CARDIE          IEC0bits.INT0IE
//
#define CHANGE_F		   IFS1bits.CNIF	
/******************** TIMERS *******************/

#define TMRL                TMR2

#define FCY 16000000UL


#define USE_USB_INTERFACE               // USB host MSD library

//#define GetSystemClock()            32000000UL
//#define GetInstructionClock()       (GetSystemClock() / 2)

#if defined(USE_SELF_POWER_SENSE_IO)
	#define self_power          PORTBbits.RB5
#else
	#define self_power          1 
#endif
