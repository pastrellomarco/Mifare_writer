/****************** INDICI CICLI FOR - WHILE **********************************/
extern unsigned char t;

extern unsigned char b;
extern unsigned char i;
extern unsigned char j;
extern unsigned char l;
extern unsigned char k;

extern unsigned int y;
extern unsigned int w;
extern unsigned int x;
extern unsigned int z;
extern unsigned int kk;
extern unsigned int ww;

extern unsigned char tmp1,tmp2,tmp3;

extern unsigned int temp16_1;
extern unsigned int temp16_2;
extern unsigned int Index_wl;

/********************************** VARIABILI RS485 ***************************************/

extern unsigned char dato_485;
extern unsigned char index_485;
extern unsigned char msg_ready_485;
extern unsigned char checksum_485;

extern unsigned char IP_Mittente_In[4];
extern unsigned char TipoProdotto_Mit_In;
extern unsigned char Gruppo_Mit_In;

extern unsigned char IP_Destinatario_In[4];
extern unsigned char TipoProdotto_Dest_In;
extern unsigned char Gruppo_Dest_In;

extern unsigned char Comando_In;

extern unsigned char CicloRichiestaInfoAvvio;

extern unsigned char Invio_msgTest_485;
	
/************************** TIMERS, OROLOGIO e DELAY ********************************************/

extern unsigned char Timer_temp4_centesimi;
extern unsigned int Timer_temp4_decimi;	
extern unsigned int Timer_temp4_mezzosecondo;
extern unsigned int Timer_temp4_secondi;
extern unsigned int Timer_temp4_10secondi;

extern unsigned int timer_LED_VERDE;
extern unsigned int timer_LED_ROSSO;
extern unsigned char timer_LED_CPU;
extern unsigned char Timer_Presenza;

extern unsigned char Timer_Reset;

extern unsigned int Timer_Valida485;



/************************* BUFFER ******************************************************/

extern unsigned char Buffer_RS485In[64];						
extern unsigned char Buffer_RS485Out[64];
extern unsigned char Buffer_485_temp[64];

/************************************** VARIABILI SISTEMA **************************/

extern unsigned char IP_Dispositivo[4]; 
extern unsigned char ID_Gruppo; 
extern unsigned int ID_Struttura;	
extern unsigned char IP_Address_temp[4];

extern unsigned char BufferPresenza[5];

extern unsigned char Stato_Presenza;
extern unsigned char Fase_Presenza;
/************************************** VARIABILI DISPLAY **************************/

extern unsigned char DisegnaStato;

/******************* VARIABILI MIFARE **********************/

extern unsigned char status;
extern unsigned char blockAddr; 
extern unsigned char serNum[5];	
extern unsigned char Fase_Masterizzazione;
extern unsigned char SerialeCard[5];			
extern unsigned char str[16];
extern unsigned char Buffer_Mifare[16];
extern unsigned char Buffer_Scrittura_Mifare[16];
extern unsigned char FormatoCardRilevata;
extern unsigned char RegistriMifare[48];
//extern unsigned char blocco_card;
extern unsigned char InizializzaMifare;

extern unsigned char Sectorkey_Nuovo[6];
extern unsigned char Sectorkey[6];

extern unsigned char cnt_letturePerse;
extern unsigned char Card_Presente_Mifare;
extern unsigned char Tipo_CardPresente_Mifare;

//extern unsigned char smartcardresult=0;
extern unsigned char CardMifare;
extern unsigned char Flag_PresenzaCardMifare;		
extern unsigned char Flag_PresenzaCardMifare_old;	

extern unsigned char Flag_leggi_mifare;
extern unsigned char poll_timer_mifare;

extern unsigned char Flag_CheckPSC;

/**************************************** USB ******************************/

extern unsigned char ReceivedDataBuffer[64];
extern unsigned char ToSendDataBuffer[64];

extern unsigned char invia_usb;
extern unsigned char rispondi_usb;		
extern unsigned char checksumUSB_RX;	
extern unsigned char checksumUSB_TX;
