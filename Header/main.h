
/************************ DEFINIZONE VERSIONE FIRMWARE ********************************/

#define  MAJOR_RELEASE 		0		// Versione principale_ parte Alta
#define  MIDDLE_RELEASE 	0		// Versione principale_ parte Bassa
#define  MINOR_RELEASE		2		// lettera principale

/************************ ATTIVAZIONE DEBUG ********************************/

#define DEBUG									// permette di modificare alcune impostazioni-solamente in debug
//#define VERIFICA_CHECKSUM
/************************ PREFERENZE COMUNICAZIONI ********************************/

#define HW_SPI					// Se definito usa SPI harwdare per accedere al chip Mifare, altrimenti libreria software

//#define USA_USB				// Se definito Attiva Gestione USB

//#define ADDRESS_MEM			0xA8	// indirizzo fisico della memoria I2C su cui caricare/leggere la congiurazione del sistema
//#define ADDRESS_OROLOGIO		0xDE	// indirizzo fisico della memoria I2C su cui caricare/leggere la congiurazione del sistema
//
/************************ DEFINIZIONI TEMPISTICHE SISTEMA ********************************/

//#define TIMER4_CENTESIMI				3			// Costante che definisce le tempistiche del timer 4 per generare degli interrupt di 10ms 
#define TIMER4_DECIMI					10			// Costante che definisce le tempistiche del timer 4 per generare degli interrupt di 100ms 
#define TIMER4_SECONDI					100			// Costante che definisce le tempistiche del timer 4 per generare degli interrupt di 1s 
#define TIMER4_10SECONDI				1000		// Costante che definisce le tempistiche del timer 4 per generare degli interrupt di 10s 

#define LED_TIME_COM					1			// 3 decimi di secondo per l'attivazione dei led delle comunicazioni
#define LED_TIME						1			// 3 decimi di secondo per l'attivazione del led Rosso durante l'apertura della porta

#define TIMER_RELOAD_CONFIGURAZIONE		2			// Timer che consente di ricarica l'intera configurazione dell'EEPROm dopo una scrittura da radio( espresso in secondi)
#define TEMPO_PROGRAMMAZIONE			3			// Definisce i Secondi con cui deve rimanre accesso

//#define TEMPO_MIN_PULSANTE				1			// tempo minimo di ricontrollo della funzioalità pulsante (espresso in decimi di secondo)
#define TEMPO_MIN_uSWITCH				2			// tempo minimo di commutazione del USwitch della card (espresso in decimi di secondo)

#define TEMPO_SECONDI					10			// costante per l'adattamento tempi in secondi

#define TEMPO_POLLING_MIFARE			2			// intertempo interrogazione Card mifare(Espresso in decimi di seocndi)

#define TIMER_CPU						5

/************************************ GESTIONE CARD GENERICHE ***********************************************/

#define NUM_CELLE_MAX					40			// Definisce il numero di Celle massime leggibili dal Sistema
#define NUM_CELLE_DEFAULT				16			// Definsice il numero di Celle massime leggibili di Default

#define NUM_SETTORE_MAX					15			// Definisce il numero di Settori disponibili nella Card
#define NUM_SETTORE_DEFAULT				15			// Definisce il numero di Settore di Default

#define NUM_BLOCCO_START    			0			// definisce il numero di blocco da cui partire con la lettura/scrittura

#define NUM_BLOCCHI_SETTORE    			3			// definisce il numero di blocchi presenti per ciacun settore (data)
#define NUM_BLOCCHI_DEFAULT    			1			// definisce il numero di blocco a cui accedere i caso di errore

#define LETTURA							1			// definisce il comando di Lettura
#define SCRITTURA						0			// definisce il comando di Scrittura


#define SECTOR_INIT_NUMBER				16

//
/*********************** DEFINIZIONE PSC  ************************/

#define PSC1_M			0x41
#define PSC2_M			0x4D
#define PSC3_M			0x50

#define PSC1_V			0xFF
#define PSC2_V			0xFF
#define PSC3_V			0xFF

#define PSC1_T			0xEB
#define PSC2_T			0x36
#define PSC3_T			0x29

/************************************ GESTIONE MIFARE ***********************************************/

