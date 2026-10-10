

/************************ HEADERS - GENERICHE **********************************/

#include "Header\main.h"
#include "Header\Variabili.h"
#include "Header\HardwareProfile.h"
#include "Header\compiler.h"
#include "Header\ST7735.h"
#include "Header\Protocollo_0_07.h"
#include "Header\Locazioni CARD.h"
#include "Header\MfRC522.h"
#include "Header\CardMifare522.h"


/************************ HEADERS - USB **********************************/
#include "Header\USB\usb.h"
#include "Header\USB\usb_function_hid.h"

/****************** INDICI CICLI FOR - WHILE **********************************/
unsigned char t;								// variabile per ciclo for ad utilizzo esclusivo dei controlli sui timer degli ingressi

//unsigned char b;								// variabile temporanea per indicare il numero di caratteri del nmero convertito
//unsigned char i;
//unsigned char j;
//unsigned char l;
//unsigned char k;

//unsigned char n;
//unsigned int y;
//unsigned int w;
//unsigned int x;
//unsigned int z;
//unsigned int kk;
//unsigned int ww;
//
unsigned char tmp1,tmp2,tmp3;
//unsigned int temp16_1;
//unsigned int temp16_2;

/************************** TIMERS, OROLOGIO e DELAY ********************************************/

unsigned int Timer_temp4_decimi = 0;					// Contiene un timer temporaneo per l'adattamento dei TEMPI in decimi di secondo
unsigned int Timer_temp4_secondi = 0;					// Contiene un timer temporaneo per l'adattamento dei TEMPI in secondi

unsigned int timer_LED_ROSSO;
unsigned int timer_LED_VERDE;

unsigned char timer_LED_CPU = TIMER_CPU;

unsigned char poll_timer_mifare = 0;					// Contiene il timer per il controllo cadenzato dell'accesso alla Card Mifare

unsigned char Flag_leggi_mifare ;
///************************* BUFFER ******************************************************/
//
//unsigned char Buffer_RS485In[64];						// Buffer per dati in Uccita dalla RS485						
//unsigned char Buffer_RS485Out[64];						// Buffer per dati in Ingresso sulla RS485	
//unsigned char Buffer_485_temp[64];						// Buffer per dati i dati parziali

/************************************** VARIABILI SISTEMA **************************/

unsigned char IP_Dispositivo[4]={IP_DEFAULT_H,IP_DEFAULT_MH,IP_DEFAULT_ML,IP_DEFAULT_L}; 				// Contiene l'indirizzo Fisico dell'apparecchio (quello con cui risponde al BUS)
unsigned char ID_Gruppo; 								// Contiene    il gruppo di Funzionamento dell'apparecchio (quello con cui risponde al BUS)
unsigned int ID_Struttura;								// Contiene il codice identificativo della struttura su cui devono funzionare le Card inserite
unsigned char IP_Address_temp[4];						// Valore utilizzato per convertire l'IP presente nei files di configurazione


//unsigned char Fase_Presenza = 0;

/************************************** VARIABILI DISPLAY **************************/

unsigned char DrawDisplay;

char Stringa_Testo1[] = "Pastrello";
char Stringa_Testo2[] = "Electronic's";
char Stringa_Testo3[] = "Mifare Card R/W";

char Stringa_Versione[] = "Versione: 0.02";

char CardTypebuffer[15];

char Text_UltraLight[] = 		"U_Light";
char Text_MifareOne_S50[] = 	"S50";
char Text_MifareOne_S70[] = 	"S70";
char Text_Pro_X[] = 			"Pro_X";
char Text_DesFire[] = 			"DesFire";

char Text_FormatCard[] = 		"FormatCard";
char Text_NEW_PSC_OK[] =  		"New PSC OK";
char Text_NEW_PSC_KO[] =  		"New PSC KO";

/**************** VARIABILI CARD ***************/

unsigned char Tipo_AccessoCard;				// Tipologia di CArd su cui effettuare le lettura/scrittura durante la masterizzazione

unsigned char settore_temp;					// Settore Accesso Mifare per Lettura/Scrittura durante Masterizzazione
unsigned char blocco_temp;					// Blocco Mifare di Lettura/Scrittura durante Masterizzazione
unsigned char CellaStart_temp;				// Cella Start SLE4442 per Lettura/Scrittura durante Masterizzazione
unsigned char NumeroCelle_temp;				// numero Cella  SLE4442 da Leggere/scrivere durante Masterizzazione

//unsigned char psc_1;
//unsigned char psc_2;
//unsigned char psc_3;
//
/******************* VARIABILI MIFARE **********************/

unsigned char Esito_Mifare;
//unsigned char status;										// coneine l'esito delle operazione di accesso alla card MIFARE
//unsigned char blockAddr;        							// Selection operation block address 0 to 63


unsigned char myUID[5];										// contiene il codice seriale della card con cui interagire						

//unsigned char Fase_Masterizzazione;
unsigned char str[16];										// Contiene il codice seriale e i dati prelevati dalla card Mifare durante il primo avvicinamneto della Card

	
//unsigned char FormatoCardRilevata=0;

unsigned char InizializzaMifare;


//unsigned char Sectorkey_Nuovo[6]={0,0,0,0,0,0};

unsigned char Sectorkey[6]={0,0,0,0,0,0};
unsigned char Default_Key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    // Le nostre nuove chiavi personalizzate
unsigned char New_KeyA[6] = {0x00, 0xEB, 0x00, 0x36, 0x00, 0x29};
unsigned char New_KeyB[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};



//unsigned char Card_Presente_Mifare= 0;
//unsigned char Tipo_CardPresente_Mifare=0;					// Tipologia di Card presente nel Masterizzatore
unsigned char TipologiaCard;

/**************************************** USB ******************************/

unsigned char ReceivedDataBuffer[64];			// Buffer utilizzato per ospitare i dati arrivati da USB
unsigned char ToSendDataBuffer[64];				// Buffer utilizzato per ospitare i dati da spedire su USB


unsigned char invia_usb = 1;					// Definisce se dopo aver ricevuto un comando da radio può e deve anche risondere sul canale USB. 0= non deve rispondere, 1= deve rispondere
unsigned char rispondi_usb = 0;					// eprmette di rispondere sul bus USB: 0= nessuna risposta , 1= risposta da inviare
unsigned char checksumUSB_RX = 0;				// Contiene il valore della checksum calcolata per i dati provenienti dall'USB (dal PC alla Seriale)
unsigned char checksumUSB_TX = 0;				// Contiene il valore della checksum calcolata per i dati uscenti dall'USB (dalla seriale al PC)


#pragma udata

USB_HANDLE USBOutHandle = 0;
USB_HANDLE USBInHandle = 0;


unsigned char ActualPSCType = 0;
unsigned char NewPSCType = 1;
unsigned char NumberOfCardsToDo = 100;
unsigned char StartFormatCard = 1;


/****************************** PROTOTIPI DI FUNZIONE INTERNE *************************/

void ProcessUSB(void);
void AnalisiMifareCard(void);
void VerificaPresenzaCard(void);

/********************************** PROTOTIPI DI FUNZIONI *******************************/

extern void InterruptHandlerHigh (void);

extern void BoardInit(void);
extern void ST7735_Init(void);

extern void delay_ms(unsigned int sleep_ms);
extern long tick_elapsed(long tickUser);
extern long tick_current(void);


extern unsigned char u16toa (unsigned int value,char *pBuffer, unsigned char radix);



/******************************** INIZIALIZZAZIONE STRUTTURE *************************/

void FormatCard(void)
{
static unsigned char FormatCard_state = 0;	
static char BufferPSC_Status[SECTOR_INIT_NUMBER+1];
char bufferCardDone[4];
static unsigned char NumOfCardDone = 0;
static unsigned char IndexSector;
unsigned int tmpText = 0;
unsigned char id,numberSEC_OK;
static long tick_PSC_check;
unsigned char status;

enum formatStatus {FORMAT_INIT = 0, CHECK_INITIAL_PSC, FORMAT_NEW_CARD, CHECK_RIGHT_PSC,  WAIT_NEXT_CARD};
	
	
	switch (FormatCard_state)
	{
		case FORMAT_INIT:
		{
			if (StartFormatCard == 1)
			{
				//Fase_Presenza = 1;
				FormatCard_state = FORMAT_NEW_CARD;
				IndexSector = 0;
				memset (BufferPSC_Status, 0x00, SECTOR_INIT_NUMBER+1);
				ST7735_fillRect(0, 110, 128, 16, ST7735_BLACK);		// STATUS check PSC
				ST7735_fillRect(0, 20, 128, 8, ST7735_BLACK);		// first check PSC
				ST7735_fillRect(0, 30, 128, 8, ST7735_BLACK);		// final check PSC
				
				tmpText = strlen(Text_FormatCard);
				ST7735_drawString((SCREEN_WIDTH -(tmpText * 12))/2, 10, Text_FormatCard, ST7735_ORANGE, 1);
								
				memset (bufferCardDone, 0x00, 4);
				
				ST7735_fillRect(0, 60, 32, 16, ST7735_BLACK);		// final check PSC
				tmpText = u16toa (NumOfCardDone, bufferCardDone, 10);		// eseguo conversione nuemri in caratteri
				ST7735_drawString(0, 60, bufferCardDone, ST7735_BLUE, 2);

			}
		}	
		break;

		case FORMAT_NEW_CARD:
		{
			if (CardPresent && (NumOfCardDone < NumberOfCardsToDo))
			{
				if (tick_elapsed(tick_PSC_check) >= 10)
				{
					tick_PSC_check = tick_current();
	
					status = MFRC522_ChangeSectorKey(IndexSector, Default_Key, New_KeyA, New_KeyB);		//Eseguo Sostituzione DLE PSC
					
					if (status == MI_OK)
					{
						BufferPSC_Status[IndexSector] = '0';
					}
					else
					{
						BufferPSC_Status[IndexSector] = 'E';
					}
					
					if(++IndexSector == SECTOR_INIT_NUMBER)
					{
						ST7735_drawString(0, 20, BufferPSC_Status, ST7735_PINK, 1);
						memset (BufferPSC_Status, 0x00, SECTOR_INIT_NUMBER+1);
						IndexSector = 0;
						ActualPSCType = 1;
						FormatCard_state = CHECK_RIGHT_PSC;
					}
				}
			}	
		}
		break;
		
		case CHECK_RIGHT_PSC:
		{
			if (tick_elapsed(tick_PSC_check) >= 10)
			{
				tick_PSC_check = tick_current();
	
       			status = MFRC522_Auth(PICC_AUTHENT1A, IndexSector, New_KeyA, str);
    
    			if (status == MI_OK)
				{
					BufferPSC_Status[IndexSector] = '0';
				}
				else
				{
					BufferPSC_Status[IndexSector] = 'E';
				}
				
				if(++IndexSector == SECTOR_INIT_NUMBER)
				{
					numberSEC_OK = 0;
					for (id = 0; id < SECTOR_INIT_NUMBER; id++)
				 	{
						if (BufferPSC_Status[id] == '0')
							numberSEC_OK++;
					}
					
					if (numberSEC_OK == SECTOR_INIT_NUMBER)
					{
						//good
						tmpText = (unsigned)strlen(Text_NEW_PSC_OK);
						ST7735_drawString((SCREEN_WIDTH -(tmpText * 12))/2, 110, Text_NEW_PSC_OK, ST7735_GREEN, 2);
						
						NumOfCardDone++;
						memset (bufferCardDone, 0x00, 4);
						tmpText = u16toa (NumOfCardDone, bufferCardDone, 10);
						ST7735_fillRect(0, 60, 40, 16, ST7735_BLACK);		// final check PSC
						ST7735_drawString(0, 60, bufferCardDone, ST7735_BLUE, 2);
					}
					else
					{
						//wrong
						tmpText = (unsigned)strlen(Text_NEW_PSC_KO);
						ST7735_drawString((SCREEN_WIDTH -(tmpText * 12))/2, 110, Text_NEW_PSC_KO, ST7735_RED, 2);
					}	
		
					ST7735_drawString(0, 30, BufferPSC_Status, ST7735_WHITE, 1);
					FormatCard_state = WAIT_NEXT_CARD;
				}
			}
		}
		break;
		
	
		case WAIT_NEXT_CARD:
		{
			
			if (CardPresent == 0)
			{
				FormatCard_state = FORMAT_INIT;
				
				if (NumOfCardDone > NumberOfCardsToDo)
				{
					StartFormatCard = 0;
				}
			}	
		}	
		break;
	}
}


/************************************************************
*
*				void VerificaPresenzaCard(void)
*
*	Permette di analizzare il uswitch e/o il campo Mifare per capire
*	se è stata inserita una card e nel caso in cui l'esito sia positivo, 
*	la procedura preleva i dati dalla card per verificare l'accesso
**************************************************************/

void CheckCardPresence(void)
{
static unsigned char previousCardStatus = 0;
unsigned char cardStatus;
unsigned char status;


	if (Flag_leggi_mifare)												// 
	{
		Flag_leggi_mifare = 0;											// 

	 	cardStatus = MFRC522_DiscoverCard(myUID);


        // Rilevamento dei fronti (Cambiamento di stato)
        if ((cardStatus == 1) && (previousCardStatus == 0))
	    {
            // EVENTO: Tessera appena appoggiata in modo STABILE
            
            if (MFRC522_SelectTag(str) != 0)
	        {
	            LED_7 = 1;
	            previousCardStatus = 1;
	            CardPresent = 1;
	   			DrawDisplay = 1;
	   			
//				status = MFRC522_ChangeAllKeys(myUID, 0, CARD_SECTOR_NUMBER, Default_Key, New_KeyA, New_KeyB);
//                    
//              if (status == MI_OK)
//             	 {
//                    // Successo! La tessera ora è protetta dalle tue nuove chiavi.
//                    // Segnala l'evento (es. un bip lungo del buzzer o un LED verde)
//                }
//                else
//                {
//                    // Errore: la tessera potrebbe essere stata allontanata durante il loop 
//                    // o uno dei settori aveva già una chiave diversa.
//                    
//                DrawDisplay = 1;
//                }
                
			//	MFRC522_Halt();
	   			
	   		}
        } 
        else if ((cardStatus == 0) && (previousCardStatus == 1))
	    {
            // EVENTO: Tessera appena rimossa
           LED_7 = 0;
           previousCardStatus = 0;
           CardPresent = 0;
           DrawDisplay = 1;
        }
        

	}
}


/***************************************************************************
*
*         		void SplashScreen(void)
*
*		Visualizza Schermata Iniziale
****************************************************************************/

void SplashScreen(void)
{
//ST7735_DrawBitmap(0, 0, Logo, SCREEN_WIDTH, SCREEN_HEIGHT);

ST7735_fillScreen(ST7735_BLACK);

ST7735_drawString(37, 4, Stringa_Testo1, ST7735_RED, 1);
ST7735_drawString(28, 10, Stringa_Testo2, ST7735_RED, 1);
ST7735_drawString(19, 40, Stringa_Testo3, ST7735_CYAN, 1);

ST7735_drawString(22, 60, Stringa_Versione, ST7735_ORANGE, 1);
}

/***************************************************************************
*
*         	void UpgradeDisplay(void)
*
*		Aggiorna contenuto grafico del display
****************************************************************************/

void UpgradeDisplay(void)
{
unsigned char tmp_len;

	if (DrawDisplay)
	{
		DrawDisplay = 0;
		ST7735_drawString(30, 60, "CARD:", ST7735_WHITE, 2);
		ST7735_fillRect(90, 60, 80, 20, ST7735_BLACK);			// Status Card presence YES/NO
		ST7735_fillRect(0, 90, 128, 20, ST7735_BLACK);			// Card Type
		
		if (CardPresent)
		{
			ST7735_drawString(90, 60, "SI", ST7735_WHITE, 2);
			memset(CardTypebuffer, 0x00, 15);
			
			switch (TipologiaCard)
			{
				case MIFARE_ULTRALIGHT:		strcpy (CardTypebuffer, Text_UltraLight);		break;
				case MIFARE_ONE_S50:		strcpy (CardTypebuffer, Text_MifareOne_S50);	break;
				case MIFARE_ONE_S70:		strcpy (CardTypebuffer, Text_MifareOne_S70);	break;
				case MIFARE_PRO_X:			strcpy (CardTypebuffer, Text_Pro_X);			break;
				case MIFARE_DESFIRE:		strcpy (CardTypebuffer, Text_DesFire);		break;
			}
				
			tmp_len = (unsigned)strlen(CardTypebuffer);
			ST7735_drawString((SCREEN_WIDTH -(tmp_len *12))/2, 90, CardTypebuffer, ST7735_YELLOW, 2);
		}
		else
			ST7735_drawString(90, 60, "NO", ST7735_WHITE, 2);
	}
}


/***************************************************************************
*
*         				int main(void)
*
****************************************************************************/

void main(void)
{
BoardInit();


#ifdef USA_USB

	#if defined(USE_USB_BUS_SENSE_IO)
		tris_usb_bus_sense = INPUT_PIN; 			// See HardwareProfile.h
	#endif
	
	#if defined(USE_SELF_POWER_SENSE_IO)
		tris_self_power = INPUT_PIN;				// See HardwareProfile.h
	#endif
	
	USBDeviceInit();								//  Initializes USB module SFRs and firmware
	
	#if defined(USB_INTERRUPT)
	   USBDeviceAttach();
	#endif
#endif

MFRC522_Init();  									// Init Mifare

ST7735_Init();										// Init Display
SplashScreen();										// Schermata 	

delay_ms(1500);

ST7735_fillScreen(ST7735_BLACK);
DrawDisplay = 1;

	while (1)							 					// Ciclo principale del programma
    	{
		ClrWdt();											// Resetto Watchdog
		CheckCardPresence();								// Verifica la presenza della card Mifare e/o Smart
		FormatCard();

		UpgradeDisplay();

#ifdef USA_USB
       	#if defined(USB_POLLING)
       		USBDeviceTasks(); 
       	#endif

		ProcessUSB(); 
#endif
    }	// fine while (1)
}


