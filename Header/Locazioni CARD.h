
#define PARTENZA_SMART			0x20	// definisce la cella di partenza dei dati sulla card SLE4442
#define PARTENZA_MIFARE			0x20	// definisce la cella di partenza dei dati sulla card SLE4442

#define LOC_TIPOCARD			0x20	// Tipologia Card:1 = Cliente,2 = Pass,3 = Super Pass,4 = Programmazione ID e Configurazione 
#define LOC_ID_CARD_H			0x21	// Contiene l'ID identificativo della Card_H 
#define LOC_ID_CARD_L			0x22	// Contiene l'ID identificativo della Card_L  
#define LOC_FLAG_NUOVA			0x23	// Contiene un info di Card Nuova
//#define LOC_INDEX_PROG			0x28	// Contiene l'ID identificativo della Card_L  	


#define LOC_ID_DEVICE			0x24	// Contiene l'ID del dispositivo su cui PUò funzioanre
//#define LOC_ID_DEVICE_MH		0x25	// Contiene l'ID identificativo  su cui PUò funzioanre
//#define LOC_ID_DEVICE_ML		0x26	// Contiene l'ID identificativo  su cui PUò funzioanre
//#define LOC_ID_DEVICE_L			0x27	// Contiene l'ID identificativo  su cui PUò funzioanre
	
	
#define LOC_ID_STRUTTURA_H		0x28	// Contiene l'ID Struttura_Parte H
#define LOC_ID_STRUTTURA_L		0x29	// Contiene l'ID Struttura_Parte L		

#define LOC_TIMER_PRESENZA		0x2A	// Timer Distacco Energia Elettrica
#define LOC_TIMER_CREDITI		0x2B	// Timer Distacco Out Crediti
#define LOC_TIMER_SERRATURA		0x2C	// Timer Elettroserratura
#define LOC_TIMER_LUCECORTESIA	0x2D	// Timer Distacco LuceCorteisa
#define LOC_TIMER_GENERICO		0x2E	// Timer Distacco Out Generico
#define LOC_TIMER_INVIO_IR		0x2F	// Timer Riproduzione Infrarosso

#define LOC_CREDITO_ENERGY_H		0x30	// Credito Energetico_Parte H
#define LOC_CREDITO_ENERGY_M		0x31	// Credito Energetico_Parte M		
#define LOC_CREDITO_ENERGY_L		0x32	// Credito Energetico_Parte L		
#define LOC_CREDITO_GENERALE1_H		0x33	// Credito Generico 1_Parte H
#define LOC_CREDITO_GENERALE1_L		0x34	// Credito Generico 1_Parte L	
#define LOC_CREDITO_GENERALE2_H		0x35	// Credito Generico 2_Parte H
#define LOC_CREDITO_GENERALE2_L		0x36	// Credito Generico 2_Parte L	
#define LOC_CREDITO_GENERALE3_H		0x37	// Credito Generico 3_Parte H
#define LOC_CREDITO_GENERALE3_L		0x38	// Credito Generico 3_Parte L	
#define LOC_CREDITO_GENERALE4_H		0x39	// Credito Generico 4_Parte H
#define LOC_CREDITO_GENERALE4_L		0x3A	// Credito Generico 4_Parte L	
#define LOC_CREDITO_GENERALE5_H		0x3B	// Credito Generico 5_Parte H
#define LOC_CREDITO_GENERALE5_L		0x3C	// Credito Generico 5_Parte L	

#define LOC_SCADENZA_GIORNO			0x40	// Scadenza Giorno
#define LOC_SCADENZA_MESE			0x41	// Scadenza mese
#define LOC_SCADENZA_ANNO			0x42	// Scadenza anno
#define LOC_SCADENZA_ORA			0x43	// Scadenza ora
#define LOC_SCADENZA_MINTUI			0x44	// Scadenza minuti


#define LOC_ZC_START				0x60	// Contiene il primo ID delle ZC 

