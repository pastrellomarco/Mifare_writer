
/************************* FORMATO CARD MIFARE ********************/

#define MIFARE_ULTRALIGHT	255		// Definisce la tipologia di card Ultralight (64 Bytes)
#define MIFARE_ONE_S50		254		// Definisce la tipologia di card Mifare ONE S50 ( 1024 Bytes)
#define MIFARE_ONE_S70		253		// Definisce la tipologia di card Mifare ONE S70 ( 4096 Bytes)
#define MIFARE_PRO_X		252		// Definisce la tipologia di card Mifare PRO ( 1024 Bytes)
#define MIFARE_DESFIRE		251		// Definisce la tipologia di card Mifare DesFire(da 2048 a 8192 bytes)

#define SETTORE_MIFARE_DEFAULT	15	// Definisce il settore MIfare di Default di Microtech

#define PSC1_M			0x41
#define PSC2_M			0x4D
#define PSC3_M			0x50

/**************** TIPOLOGIA DI CARD ****************/

#define CARD_IGNOTA					0	// tipologia Card Sconosciuta / non implementata
#define CARD_CLIENTE				1	// tipologia Cliente
#define CARD_CAMERIERA				2	// tipologia Pass Cameriera
#define CARD_GOVERNANTE				3	// tipologia Pass Governante
#define CARD_MANUTENTORE			4	// tipologia Pass Direttore
#define CARD_DIRETTORE				5	// tipologia Pass Direttore
#define CARD_SUPERPASS				6	// tipologia Super Pass
#define CARD_PROG_ID				7	// tipologia Programmazione ID
#define CARD_PROG_OROLOGIO			8	// tipologia Programmazione orologio
#define CARD_DISABILITA_WL			9	// tipologia Disabilita Card da WL
#define CARD_CANCELLAZIONE_WL		10	// tipologia Cancella WL


/**************** TIPOLOGIA DI CARD ERRORI ****************/

//#define ERR_GENERICO				0	// Errore Generico - Non codificato
#define ERR_SCONOSCIUTA				0	// Errore Generico - Card non riconosciuta
#define CARD_OK						1	// Nessun errore di Accesso
#define ERR_IDSTRUTTURA				2	// Errore ID Struttura
#define ERR_PSC						3	// Errore PSC
#define ERR_IDDEVICE				4	// Errore ID dispositivo
#define ERR_WHITELIST				5	// Errore di Whitelist: Card non present ein WL
#define ERR_SCADENZA				6	// Errore Scadenza: card scaduta
#define ERR_PRIVILEGI				7	// Errore Privilegi

#define ERR_RIAVVIO_FW				254	// Errore Privilegi

/************************* TIPOLOGIA DISPOSITIVI ********************/

#define TIPO_PC 					1	// Definisce il tipo di dispositivo a cui risponde il PC
#define TIPO_MASTERIZZATORE 		2	// Definisce il tipo di dispositivo a cui risponde il masterizzatore
#define TIPO_LETTORE_APRIPORTA 		3	// Definisce il tipo di dispositivo a cui risponde l'apparecchio Apriporta
#define TIPO_LETTORE_PRESENZA 		4	// Definisce il tipo di dispositivo a cui risponde l'apparecchio gestione Luci
#define TIPO_TECNOLOGICA 			5	// Definisce il tipo di dispositivo a cui risponde la TECNOLOGICA
#define TIPO_TERMOSTATO 			6	// Definisce il tipo di dispositivo a cui risponde l'apparecchio TERMOSTATO
#define TIPO_CENTRALINA 			7	// Definisce il tipo di dispositivo a cui risponde l'apparecchio CENTRALINA


/************************* TIPOLOGIA ATTIVAZIONE E RIVELAZIONE ********************/

#define ATT_OFF 				0			// Attiva In OFF
#define ATT_ON 					1			// Attiva In ON
#define ATT_RITARDO_ON			2			// Attiva con ritardo In ON
#define ATT_RITARDO_OFF 		3			// Attiva con ritardo In OFF
#define ATT_IMPULSO_ON			4			// Impulso di ON
#define ATT_IMPULSO_OFF 		5			// Impulso di OFF
#define ATT_SEGUI_STATO			6			// Inverto lo stato di un ingresso
#define ATT_INVERTI_STATO 		7			// Inverto lo stato dell'uscita
#define ATT_INTERMITTENZA		8			// Attivo Stato ad Intermittenza
#define VIRTUALE_EMAIL			9			// Invio Email


#define RIL_DISABILITATA		0			// Disabilta Rilevazione commutazioni
#define RIL_CHIUSURA			1			// Rileva la commutazione in Chiusura
#define RIL_APERTURA			2			// Rileva la commutazione in Apertura
#define RIL_PULSANTE			3			// Rileva la funzione PULSANTE ( chiusura e attesa apertura)
#define RIL_SEGUI_STATO			4			// Rileva il cambiamento dell'ingresso ed ad d ogni variazioni esegue una commutazione sull'scuita
#define RIL_ANALOGICO			5			// Rileva ingresso come analogico			
#define RIL_CONTAIMPULSI		6			// Rileva impulsi dall'ingresso
#define RIL_PIR					7			// Rileva la chiusura e commuta in ON subito, poi all'apertura esegue l'azione programmata

#define RIL_VIRTUALE			254			// Modalità virtuale per cambiamento(parametri interni software e non fisici)


/************************* SPECIFICHE WIFI e ETHERNET********************/

#define RESTORE_MICROTECH		1
#define RESTORE_FACTORY			2
#define CUSTOM_USER				3


/************************* SPECIFICHE COMUNICAZIONE PROTOCOLLO ********************/

#define START						2	// Definisce il codice del valore del byte di START
#define STOP						3	// Definisce il codice del valore del byte di STOP
#define DIM_PACCHETTO				64	// Definisce il numeor di byte utilizzato dal protocollo


#define POS_START					0	// N° byte in cui è posizionato START
#define POS_STOP					63	// N° byte in cui è posizionato STOP

#define POS_MIT						1	// N° byte in cui è posizionato il 1° byte del Mittente
#define POS_TIPO_MIT				5	// N° byte in cui è posizionato il 1° byte del Tipo Destinatario
#define POS_GRUPPO_MIT				6	// N° byte in cui è posizionato il 1° byte del Gruppo Destinatario

#define POS_DEST					7	// N° byte in cui è posizionato il 1° byte del Destinatario
#define POS_TIPO_DEST				11	// N° byte in cui è posizionato il 1° byte del Tipo Destinatario
#define POS_GRUPPO_DEST				12	// N° byte in cui è posizionato il 1° byte del Gruppo Destinatario

#define POS_CMD						13	// N° byte in cui è posizionato il CMD vero e Proprio del protocoolo
#define POS_DATA					14	// N° byte in cui è posizionato il CMD vero e Proprio del protocoolo

#define POS_CSUM					62	// N° byte in cui è posizionato il byte della Checksum

#define LUNGHEZZA_STRINGHE			32	// N° byte Max per la lunghezza delle stringhe

/***************************  VALORI DEFUALT COMUNICAZIONE ***************************************************/

#define ID_BROADCAST  				0	// Definisce l'ID univoco del PC 
//#define ID_PC  						1	// Definisce l'ID univoco del PC 
#define IP_MASTERIZZATORE_H			255	
#define IP_MASTERIZZATORE_MH		255
#define IP_MASTERIZZATORE_ML		255
#define IP_MASTERIZZATORE_L			255
#define GRUPPO_MASTERIZZATORE		254		// definisce il codice GRUPPO del Masterizzatore

#define IP_PC_H			255	
#define IP_PC_MH		255
#define IP_PC_ML		255
#define IP_PC_L			255
#define GRUPPO_PC		255		// definisce il codice GRUPPO del PC


#define IP_DEFAULT_H		1	
#define IP_DEFAULT_MH		1
#define IP_DEFAULT_ML		1
#define IP_DEFAULT_L		1

#define IP_GRUPPO_DEFAULT	1

#define IP_STRUTTURA_DEFAULT	1

#define PORTA_COM_DEFAULT		1234
#define PORTA_SMTP_DEFAULT		587

//#define TIMER_SALVA_CREDITI				300			// Numero di secondi che devono trascorrere per eseguire aggionrare in EEPROm i crediti ei secondi di utilizzo

/************************* PRIVILEGI ACCESSO ********************/

#define ACCESSO_CAMERIERA   	1			// Definisce il bit da confrontare per i privilegi di accesso

/**************************** DEFINIZIONI TERMOSTATO ***************/

#define STAGIONE_ESTATE             0
#define STAGIONE_INVERNO            1

#define TERMOSTATO_ACCESO           1
#define TERMOSTATO_SPENTO           0

#define TERMOSTATO_MAN              0
#define TERMOSTATO_FO               1

// --------------------------------------------------------------------------------- //

#define ON_ON							1			// Cmd di accensione
#define OFF_OFF							0			// cmd di Spegnimento
#define MODALITA_IR_BASE                0           // definisce la modalità di BAse (4 cmd)
#define MODALITA_IR_AVANZATA            1           // definisce la modalità Avanzata (tutti cmd)

#define NUM_COMANDI_IR					17			// numero di comandi acquisiti per il range di temperatura

#define RAFFREDDAMENTO					1			// Comando identificativo di RAFFREDDAMENTO
#define RISCALDAMENTO					2			// Comando identificativo di RISCALDAMENTO
#define DEUMIDIFICAZIONE				3			// Comando identificativo di DEUMIDIFICAZIONE
#define VENTILAZIONE					4			// Comando identificativo di VENTILAZIONE

#define ON_FREDDO						1			// indico la locazione da cui caricare il CMD di On RAFREDDAMENTO
#define OFF_FREDDO						0			// indico la locazione da cui caricare il CMD di OFF RAFREDDAMENTO
#define ON_CALDO						273			// indico la locazione da cui caricare il CMD di On RISCALDAMENTO
#define OFF_CALDO						0			// indico la locazione da cui caricare il CMD di OFF RISCALDAMENTO
#define ON_DEUMDIFICAZONE				544			// indico la locazione da cui caricare il CMD di On DEUMDIFICAZONE
#define OFF_DEUMDIFICAZONE				0			// indico la locazione da cui caricare il CMD di OFF DEUMDIFICAZONE
#define ON_VENTILAZIONE					819			// indico la locazione da cui caricare il CMD di On VENTILAZIONE
#define OFF_VENTILAZIONE				0			// indico la locazione da cui caricare il CMD di OFF VENTILAZIONE


#define SWING_ALTO						0			// Indice da Cui caricare lo swing Alto
#define SWING_CENTRO					1			// Indice da Cui caricare lo swing Centrale
#define SWING_BASSO						2			// Indice da Cui caricare lo swing Basso
#define SWING_AUTO						3			// Indice da Cui caricare lo swing Auto

#define VEL_1							0			// Indice da Cui caricare la Velocità UNO
#define VEL_2							1			// Indice da Cui caricare la Velocità DUE
#define VEL_3							2			// Indice da Cui caricare la Velocità TRE
#define VEL_AUTO						3			// Indice da Cui caricare la Velocità AUTO

#define DIST_VEL						68			// Indice la distanza tra le varie velocità



/************************* COMANDI ********************/

#define TRASFERIMENTO_CONFIGURAZIONE   	0	// Definisce il comando di Traferimento Programamzione
#define STATO_MODULO					1	// Definisce il comando di STATO MODULO
#define ATTIVA_TERMOREGOLAZIONE			2	// Definisce il comando di ATTIVA_TERMOREGOLAZIONE
#define ACQUISIZIONE_INFRAROSSO			3	// Definisce il comando di ACQUISIZIONE_INFRAROSSO
#define GESTIONE_OROLOGIO				4 	// Definisce il comando di GESTIONE_OROLOGIO
#define FORMATTAZIONE_MEMORIA 			5 	// Definisce il comando di FORMATTAZIONE_MEMORIA
#define LEGGI_CELLE_EEPROM				6	// Definisce il comando di lettura EEPROM
#define SCRIVI_CELLE_EEPROM				7	// Definisce il comando di scrittura EEPROM
#define FASCE_ORARIE_TERMOSTATO			8	// Definisce il comando di impostazione FASCE ORARIE
#define LETTURA_CELLE_CARD				9	// Definisce il comando di Lettura Card
#define SCRITTURA_CELLE_CARD			10	// Definisce il comando di Scrittura Card
#define CONFRONTA_PSC					11	// Definisce il comando di verifica PSC
#define SOSTITUZIONE_PSC				12	// Definisce il comando di sostituzione PSC
#define TERMINA_PROGRAMMAZIONE_CARD		13	// Definisce il comadno di Chiusura programmazione Card
#define RIAVVIA_FW						14	// Definisce il comando di Riavviare firmware
#define ABILITA_CODICE_WL				15	// Definisce il comando di ABILITAZIONE CODICE in WL
#define DISABILITA_CODICE_WL			16	// Definisce il comando di DISABILITAZIONE CODICE in WL
#define LETTURA_WL						17	// Definisce il comando di lettura WL
#define ATT_OUT_REMOTA					18	// Definisce il comando di Attivazioen Uscita remota
#define LETTURA_CONSUMI_CARICHI			19	// Definisce il comando per la lettura dei consumi elettrici


#define RICHIESTA_INDIRIZZAMENTO		255		// Definisce il comadno per l'evento INDIRIZZAMENTO
#define RICHIESTA_INSERIMENTO			254		// Definisce il comadno per l'evento INSERIMENTO/ESTRAZIONE CARD MASTERIZZATORE
#define EVENTO_ACCESSO					253		// Definisce il comadno per l'evento ACCESSO
#define EVENTO_PRESENZA					252		// Definisce il comadno per l'evento PRESENZA
#define EVENTO_TEMPERATURA				251		// Definisce il comadno per l'evento CAMBIAMENTO TEMPERATURA
#define EVENTO_CAMBIAMENTO_IO			250		// Definisce il comadno per l'evento CAMBIAMENTO INGRESSI e USICTE


/**************************** STRINGHE NOME PRODOTTI ********************/

//const char NomeApriporta[]= 		"READ";			// Nome Associato Al prodotto ApriPorta con Card
//const char NomeGestioneLUCI[]= 		"LIGHT";		// Nome Associato Al prodotto Gestione Attivazioni Luci con Card
//const char NomeCentralina[]=		"NET";			// Nome Associato Al prodotto Centrlaina di Stanza
//const char NomeTermostato[]=		"CLIMA";		// Nome Associato Al prodotto Termostato
//const char NomeTECNO[]= 			"TECNO";		// Nome Associato Al prodotto TECNOLOGICO


/**************************** STRINGHE GIORNI SETTIMANA ********************/





