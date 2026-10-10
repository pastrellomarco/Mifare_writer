#include "p24FJ256GB106.h"
#include "..\Header\HardwareProfile.h"
#include "..\Header\Variabili.h"
#include "..\Header\main.h"
#include "..\Header\MfRC522.h"
#include "..\Header\CardMifare522.h"
#include "..\Header\Protocollo_0_07.h"


unsigned char cntCardStable = 0;			// cnt to indicate card removed
unsigned char CardPresent = 0;    			// 0 = no card read, 1 = Card presente and stable
unsigned int cardReadType;					// Type of Card read

unsigned char MifareReadBuffer[CARD_BLOCK_SIZE];		// Buffer utilizzato nelle procedure di lettura della Card
unsigned char MifareWriteBuffer[CARD_BLOCK_SIZE];		// Buffer utilizzato nelle procedure di scrittura della Card

unsigned char sectorError = 0;

/**************************************************************************
*				void CheckCardPrecence(void)
*
*		Permette di Verificare la Presenza della Card Mifare 
*		e restituisce il tipo (Formato) di Card Mifare Rilevata
**************************************************************************/

unsigned char MFRC522_DiscoverCard(unsigned char *uid_card)
{
unsigned char status;
unsigned char i;
static unsigned char MifareCardPresent = 0;

	//stato = MFRC522_Request(PICC_REQIDL, str);				// ricerco nel campo radio se è presente una Card Mifare
	status = MFRC522_Request(PICC_REQALL, str);				// ricerco nel campo radio se è presente una Card Mifare
	cardReadType = (str[0] << 8)  + str[1];
	
	if (status == MI_OK)   									// se Card Presente /Rilevata
	{  
		status = MFRC522_Anticoll(str);
	}
		
 	if (status == MI_OK)
	  {
        // --- LA TESSERA HA RISPOSTO ---
        cntCardStable = 0; // Resetta il contatore degli errori
        
        // Copia l'UID appena letto nel buffer principale
        for(i=0; i<4; i++)
	       uid_card[i] = str[i];
   
        if (!MifareCardPresent)
        {
	        MifareCardPresent = 1; // La card è appena entrata stabilmente
	        // Qui puoi inserire un evento (es. Accendi LED, o "Card Rilevata")
        }

        // Mettiamo la card in stato HALT/SLEEP prima del prossimo ciclo, 
        // altrimenti satura il buffer d'antenna
       // MFRC522_Halt(); 
    } 
    else
	{
        // --- LA TESSERA NON HA RISPOSTO (Potrebbe essere un falso contatto o rimozione) ---
        if (MifareCardPresent)
	    {
            cntCardStable++; // Incrementa il contatore degli errori consecutivi
            
            // Se superiamo la soglia impostata, la tessera è stata rimossa sul serio
            if (cntCardStable >= CARD_DEBOUNCE_READ)
	        {
                MifareCardPresent = 0;
                cntCardStable = 0;
                cardReadType = 0;
                // Qui puoi inserire l'evento di rimozione (es. Spegni LED, o "Card Rimossa")
            }
        }
    }

    return MifareCardPresent;
}



unsigned char MFRC522_CheckSectorKey(unsigned char sector, unsigned char authMode, unsigned char *keyToCheck, unsigned char *serNum)
	{
    unsigned char status;
    unsigned char trailerBlock;

    // 1. Calcola l'indirizzo del Blocco Trailer del settore (es. Settore 1 -> Blocco 7)
    trailerBlock = (sector * 4) + 3;

    // 2. Tenta l'autenticazione hardware usando la chiave fornita
    // La riga 'status =' memorizza il verdetto dell'MFRC522
    status = MFRC522_Auth(authMode, trailerBlock, keyToCheck, serNum);

    // 3. Se l'autenticazione ha successo, chiudi immediatamente la sessione cifrata
    // per non lasciare il modulo in uno stato instabile
    if (status == MI_OK)
	{
        MFRC522_StopCrypto1(); // Disattiva Crypto1On nel Status2Reg
        return MI_OK;          // CHIAVE CORRETTA!
    }

    return MI_ERR;             // CHIAVE ERRATA o errore di comunicazione
}



/**
 * @brief Cambia le chiavi di sicurezza (Key A e Key B) di un settore specifico
 * @param sector Il numero del settore da modificare (es. 1)
 * @param oldKey Puntatore alla chiave attuale a 6 byte (usata per l'autenticazione)
 * @param newKeyA Puntatore alla NUOVA Chiave A a 6 byte da impostare
 * @param newKeyB Puntatore alla NUOVA Chiave B a 6 byte da impostare
 * @return unsigned char MI_OK se il cambio è avvenuto con successo
 */

unsigned char MFRC522_ChangeSectorKey(unsigned char sector, unsigned char *oldKey, unsigned char *newKeyA, unsigned char *newKeyB)
{
    unsigned char status;
    unsigned char i;
    unsigned char trailerBlock;
    unsigned char buffer[16];
    
    // 1. Calcola l'indirizzo del Blocco Trailer del settore richiesto
    // Per MIFARE 1K ogni settore ha 4 blocchi. Il trailer è: (sector * 4) + 3
    trailerBlock = (sector * 4) + 3;
    
    // 2. Prepara il buffer da 16 byte da scrivere nel Sector Trailer
    // Byte 0-5: Nuova Chiave A
    for(i = 0; i < 6; i++) {
        buffer[i] = newKeyA[i];
    }
    
    // Byte 6-9: Bit di Accesso Standard di fabbrica (FF 07 80 69)
    // Questa configurazione permette di usare sia Key A che Key B per leggere/scrivere i dati
    buffer[6] = 0xFF;
    buffer[7] = 0x07;
    buffer[8] = 0x80;
    buffer[9] = 0x69; // User byte generico
    
    // Byte 10-15: Nuova Chiave B
    for(i = 0; i < 6; i++)
        buffer[i + 10] = newKeyB[i];
    
    // 3. Esegui l'autenticazione sul blocco trailer usando la VECCHIA chiave
    // (Presuppone che tu abbia già l'UID della tessera salvato in un array globale o letto in precedenza)
    // Nota: 'str' deve contenere l'UID a 4 byte ottenuto dall'anticollisione
    status = MFRC522_Auth(PICC_AUTHENT1A, trailerBlock, oldKey, str);
    
    if (status == MI_OK)
	{
        // 4. Scrivi il nuovo blocco trailer nella memoria del tag
        status = MFRC522_Write(trailerBlock, buffer);
        
        // Disattiva sempre la cifratura dopo la scrittura
        MFRC522_StopCrypto1();
    }
    
    return status;
}

unsigned char MFRC522_ChangeAllKeys(unsigned char *uid, unsigned char StartSector,unsigned char StopSector, unsigned char *oldKey, unsigned char *newKeyA, unsigned char *newKeyB)
{
    unsigned char sector;
    unsigned char status;

    // Cicla attraverso tutti i 16 settori della MIFARE Classic 1K
    for (sector = StartSector; sector < StopSector; sector++) {
        
        // Chiamata alla funzione sviluppata in precedenza per il singolo settore
        status = MFRC522_ChangeSectorKey(sector, oldKey, newKeyA, newKeyB);
        
        // Se anche un solo settore fallisce l'aggiornamento, interrompiamo per sicurezza
        if (status != MI_OK) {
            // Nota: Se fallisce, i settori precedenti saranno aggiornati, quelli successivi no.
            sectorError = sector;
            return MI_ERR; 
        }
    }

    return MI_OK; // Tutte le chiavi di tutti i settori cambiate con successo!
}



/**************************************************************************
*		
*			LetturaBloccoMifare(unsigned char BloccoLettura)
*
*	Legge un blocco di 16 Byte dalla tessera Mifare	(una riga )
*
*	unsigned char Settore = indica il Settore Su cui effettuare la lettura
*	unsigned char BloccoLettura = indica il Blocco di Lettura sulla Card
**************************************************************************/

unsigned char MFRC522_ReadCardBlock(unsigned char sector,unsigned char block)
{
unsigned char tmpReadBlock;

tmpReadBlock = (sector * 4)+ block;

return MFRC522_Read(tmpReadBlock, MifareReadBuffer);					// inizia la lettura del blocco
}

/**************************************************************************
*		
*			LetturaBloccoMifare(unsigned char BloccoLettura)
*
*	Legge un blocco di 16 Byte dalla tessera Mifare	(una riga )
*
*	unsigned char Settore = indica il Settore Su cui effettuare la lettura
*	unsigned char BloccoScrittura = indica il Blocco su cui scrivere sulla Card
**************************************************************************/

unsigned char MFRC522_WriteCardBlock(unsigned char sector,unsigned char block)
{
unsigned char tmpWriteBlock;

tmpWriteBlock = (sector * 4)+ block;
return MFRC522_Write(tmpWriteBlock, MifareWriteBuffer);					// inizia la lettura del blocco
}
