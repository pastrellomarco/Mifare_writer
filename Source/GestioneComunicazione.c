#include "..\Header\HardwareProfile.h"
#include "..\Header\main.h"
#include "..\Header\Variabili.h"
#include "..\Header\Protocollo_0_07.h"
//#include "..\Header\Strutture Dati.h"
#include "..\Header\compiler.h"
/******************************** PROTOTIPI di FUNZIONI ************************************/

extern void delay_us(unsigned char pausa_us);		// main.c
extern void delay_ms(unsigned char sleep_ms);		// main.c

extern void Attivazione_Uscite(unsigned char NumeroOut,unsigned char ModalitaOut,unsigned int infouscita,unsigned long TempoTimer,unsigned char cmd_remoto ) ;
extern void VerificaFasceOrarie (void);


//void GestioneRicezioneWifi (void);
void SmistaMessaggio485 (void);
void SmistaMessaggioWifi (void);
void RispondiWifi(unsigned char *IndirizzoIPMittente,unsigned char TipoMittente,unsigned char GruppoMittente,unsigned char *IndirizzoIPDestinatario,
						unsigned char TipoDestinatario,unsigned char GruppoDestinatario,unsigned char Comando,unsigned char *BufferRisposta);

void GestioneRicezioneComandi(unsigned char TipoCanale, unsigned char *BufferRicezione)	;

/***************************************************************************
*
*         	void InvioComandoRemoto(buffer_ID_dest_ING1[index_ing1],buffer_uscita_dest1[index_ing1],mod_out_Ing1,info_uscita_Ing1,timer_Ing1);
*
*		Invia il comadno di attivazione remota
*****************************************************************************/
void InvioComandoRemoto(unsigned char *IndirizzoIPMittente,unsigned char TipoMittente,unsigned char GruppoMittente,unsigned char *IndirizzoIPDestinatario,
						unsigned char TipoDestinatario,unsigned char GruppoDestinatario,unsigned char MappaBitOut,unsigned char ModalitaOUT,unsigned long TimerOut,unsigned int InfoOut,unsigned char numING,unsigned char IndexList )			// Invio il Cmd Attivazione REMOTA
{
unsigned char checksum=0;

for(i=0;i<64;i++)											// tramite un ciclo for
	Buffer_RS485Out[i]=0x00;								// Azzero il contenuto del buffer di risposta

Buffer_RS485Out[0]=START;									// Preparo il byte di START
Buffer_RS485Out[63]=STOP;									// Preparo il byte di STOP

for (i=0;i<4;i++)							// tramite un ciclo for	
	Buffer_RS485Out[POS_MIT+i]=*IndirizzoIPMittente++;						// inserisco i dati elabiorati nel buffer di risposta

Buffer_RS485Out[5]=TipoMittente;							// Preparo il TIPO PRODOTTO
Buffer_RS485Out[6]=GruppoMittente;							// Preparo il gruppo di comunicazione

for (i=0;i<4;i++)							// tramite un ciclo for	
	Buffer_RS485Out[POS_DEST+i]=*IndirizzoIPDestinatario++;						// inserisco i dati elabiorati nel buffer di risposta

Buffer_RS485Out[11]=TipoDestinatario;							// Preparo il TIPO PRODOTTO
Buffer_RS485Out[12]=GruppoDestinatario;							// Preparo il gruppo di comunicazione

Buffer_RS485Out[POS_CMD]=ATT_OUT_REMOTA;							// COMANDO ATTIVAZIONE OUT REMOTA


Buffer_RS485Out[14]=numING;									// Inserisco il Numero dell'Uscita da Comandare
Buffer_RS485Out[15]=IndexList;
Buffer_RS485Out[17]=(unsigned char)(TimerOut>>16);			// Inserisco il Timer dell'Uscita_ ORE
Buffer_RS485Out[18]=(unsigned char)(TimerOut>>8);			// Inserisco il Timer dell'Uscita_ MINUTI
Buffer_RS485Out[19]=(unsigned char)TimerOut;				// Inserisco il Timer dell'Uscita_ SECONDI
Buffer_RS485Out[20]=(unsigned char)(InfoOut>>8);							// Inserisco Info Uscita_ Parte H
Buffer_RS485Out[21]=InfoOut;								// Inserisco Info Uscita_ Parte L
Buffer_RS485Out[22]=ModalitaOUT;							// Inserisco la Modalità dell'Uscita da Comandare
Buffer_RS485Out[23]=MappaBitOut;							// Inserisco il Numero dell'Uscita da Comandare

for(i=1;i<63;i++)											// tramite un ciclo for
	checksum = checksum + Buffer_RS485Out[i];				// Calcolo la somma Algebrica di tutti i byte contenuti nel pacchetto

Buffer_RS485Out[POS_CSUM]=checksum;								// Inserisco il valore della CheckSum Calcolata

EN_485=1;													// Attivo 485 in trasmissione
													
for (i=0;i<DIM_PACCHETTO;i++)								// tramite un ciclo for
	{
	U1TXREG=Buffer_RS485Out[i];								// inizo trasmissione di ciascun singolo byte
	while (!U1STAbits.TRMT){};
	}
EN_485=0;													// Abbasso la Linea per mettermi in Ricezione su RS485	
}

/***************************************************************************
*
*         			Rispondi485(void)
*
*		Invia la risposta al mittente su bus RS485
*****************************************************************************/

void Rispondi485(unsigned char *IndirizzoIPMittente,unsigned char TipoMittente,unsigned char GruppoMittente,unsigned char *IndirizzoIPDestinatario,
						unsigned char TipoDestinatario,unsigned char GruppoDestinatario,unsigned char Comando,unsigned char *BufferRisposta)
{
unsigned char checksum=0;

for(i=0;i<64;i++)											// tramite un ciclo for
	Buffer_RS485Out[i]=0x00;								// Azzero il contenuto del buffer di risposta

Buffer_RS485Out[0]=START;									// Preparo il byte di START
Buffer_RS485Out[63]=STOP;									// Preparo il byte di STOP

for (i=0;i<4;i++)							// tramite un ciclo for	
	Buffer_RS485Out[POS_MIT+i]=*IndirizzoIPMittente++;						// inserisco i dati elabiorati nel buffer di risposta

Buffer_RS485Out[5]=TipoMittente;							// Preparo il TIPO PRODOTTO
Buffer_RS485Out[6]=GruppoMittente;							// Preparo il gruppo di comunicazione

for (i=0;i<4;i++)							// tramite un ciclo for	
	Buffer_RS485Out[POS_DEST+i]=*IndirizzoIPDestinatario++;						// inserisco i dati elabiorati nel buffer di risposta

Buffer_RS485Out[11]=TipoDestinatario;							// Preparo il TIPO PRODOTTO
Buffer_RS485Out[12]=GruppoDestinatario;							// Preparo il gruppo di comunicazione

Buffer_RS485Out[POS_CMD]=Comando;							// COMANDO ATTIVAZIONE OUT REMOTA

for (i=0;i<49;i++)							// tramite un ciclo for	
	Buffer_RS485Out[POS_DATA+i]=*BufferRisposta++;						// inserisco i dati elabiorati nel buffer di risposta


for(i=1;i<62;i++)											// tramite un ciclo for
	checksum = checksum + Buffer_RS485Out[i];				// Calcolo la somma Algebrica di tutti i byte contenuti nel pacchetto

Buffer_RS485Out[POS_CSUM]=checksum;								// Inserisco il valore della CheckSum Calcolata

EN_485=1;													// Attivo 485 in trasmissione
												
for (i=0;i<DIM_PACCHETTO;i++)								// tramite un ciclo for
	{
	U1TXREG=Buffer_RS485Out[i];								// inizo trasmissione di ciascun singolo byte
	while (!U1STAbits.TRMT){};
	}
EN_485=0; 
}


/************************************************************************
*                	 GesetioneRadio(void)    							*
*                                                  						*
*			Esegue L'analisi dei comandi Arrivato Per Radio				*
************************************************************************/

void GestioneRicezione485(void)		
{
unsigned char RispondiBus=1;				// permette di rispondere al BUS 485
//unsigned char cnt_tmp=0;					// permette di rispondere al BUS 485
//
//unsigned long temp16_Long;
//unsigned int Loc_Start;

for (i=0;i<DIM_PACCHETTO;i++)				// tramite un ciclo for
	Buffer_485_temp[i]=0;					// pulisco il buffer di risposta (metto a ZERO i byte non UTILIZZTAI)


	switch (Buffer_RS485In[POS_CMD])								// identifico il comadno arrivato
		{

		case STATO_MODULO:											// COMANDO STATO_MODULO
			{
			if ((TipoProdotto_Mit_In == TIPO_LETTORE_PRESENZA) && (CicloRichiestaInfoAvvio==1))			// se è una risposta ad un mio comadno di richiesta STATO MODULO
				{
				CicloRichiestaInfoAvvio =2;								// informo che ho ricedvuto e prelevo i dati
				RispondiBus=0;											// blocco risposta sul BUS	
				DisegnaStato=1;
//				Tipo_Card_Presenza=Buffer_RS485In[22];					// Tipo card presente
//				Esito_Card_Presenza=Buffer_RS485In[26];					// esito presenza
				Stato_Presenza=Buffer_RS485In[25];						// Aggiorno lo stato di rpesenza sul lettore
				}
			else
				{
//				LetturaStatoInOut();									// Lettura Immediata Ingressi e Uscite
			
				Buffer_485_temp[38]=MAJOR_RELEASE;						// Versione Firmware_H
				Buffer_485_temp[39]=MIDDLE_RELEASE;						// Versione Firmware_M
				Buffer_485_temp[40]=MINOR_RELEASE;						// Versione Firmware_L
				}
			}
		break;

		case EVENTO_PRESENZA:										//
			{
			if (Buffer_RS485In[14] && (Buffer_RS485In[14] < CARD_PROG_ID) &&				// Solo se NON è una card di MANUTENZIONE( prog, Whitelist, orologio etc etc...)
			(Buffer_RS485In[15]||Buffer_RS485In[16]) && (Buffer_RS485In[18]==1))			// e codice Card presente e Accesso VALIDO
				{

				if (Buffer_RS485In[17]==1)													// se Inserimento
					Stato_Presenza=1;														// Attivo LED ROSSO nel SISTEMA
				else																		// Altrimenti
					{
					Stato_Presenza=2;														// Indico al sistema presenza in Usicta
					Timer_Presenza = Buffer_RS485In[20];									// Carico timer Distacco
					}

				DisegnaStato = 1;

				}
			}
		break;

//
	} // fine switch Comandi

for (i=0;i<DIM_PACCHETTO;i++)
	Buffer_RS485In[i]=0x00;

//if (!TipoProdotto_Dest_In)
//	delay_ms(20 * TIPO_TERMOSTATO);
//
if (RispondiBus)
	Rispondi485(IP_Dispositivo,TIPO_TERMOSTATO,ID_Gruppo,IP_Mittente_In,TipoProdotto_Mit_In,Gruppo_Mit_In,Comando_In,&Buffer_485_temp[14]);
}

