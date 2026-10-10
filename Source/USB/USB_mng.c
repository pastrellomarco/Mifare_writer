

/************************ HEADERS - USB **********************************/
#include "..\..\Header\USB\usb.h"
#include "..\..\Header\USB\usb_function_hid.h"
#include "..\..\Header\Variabili.h"

extern USB_HANDLE USBOutHandle;
extern USB_HANDLE USBInHandle;

// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************

/******************************************************************************
 * Function:        void USBCBSuspend(void)
 * Overview:        Call back that is invoked when a USB suspend is detected
 *****************************************************************************/
void USBCBSuspend(void)
{
	//Example power saving code.  Insert appropriate code here for the desired
	//application behavior.  If the microcontroller will be put to sleep, a
	//process similar to that shown below may be used:
	
	//ConfigureIOPinsForLowPower();
	//SaveStateOfAllInterruptEnableBits();
	//DisableAllInterruptEnableBits();
	//EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
	//Sleep();
	//RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
	//RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

	//IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is 
	//cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause 
	//things to not work as intended.	
	

//    #if defined(__C30__)
//    	_IPL =1;
//        USBSleepOnSuspend();
//        
//    #endif
}


/******************************************************************************
 * Function:        void _USB1Interrupt(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the USB interrupt bit is set
 *					In this example the interrupt is only used when the device
 *					goes to sleep when it receives a USB suspend command
 *
 * Note:            None
 *****************************************************************************/
//#if 0
//void __attribute__ ((interrupt)) _USB1Interrupt(void)
//{
//    #if !defined(self_powered)
//        if(U1OTGIRbits.ACTVIF)
//        {
//            IEC5bits.USB1IE = 0;
//            U1OTGIEbits.ACTVIE = 0;
//            IFS5bits.USB1IF = 0;
//        
//            //USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
//            USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);
//            //USBSuspendControl = 0;
//        }
//    #endif
//}
//#endif

/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *					suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *					mode, the host may wake the device back up by sending non-
 *					idle state signalling.
 *					
 *					This call back is invoked when a wakeup from USB suspend 
 *					is detected.
 *
 * Note:            None
 *****************************************************************************/
void USBCBWakeFromSuspend(void)
{
	// If clock switching or other power savings measures were taken when
	// executing the USBCBSuspend() function, now would be a good time to
	// switch back to normal full power run mode conditions.  The host allows
	// a few milliseconds of wakeup time, after which the device must be 
	// fully back to normal, and capable of receiving and processing USB
	// packets.  In order to do this, the USB module must receive proper
	// clocking (IE: 48MHz clock must be available to SIE for full speed USB
	// operation).
}

/********************************************************************
 * Function:        void USBCB_SOF_Handler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB host sends out a SOF packet to full-speed
 *                  devices every 1 ms. This interrupt may be useful
 *                  for isochronous pipes. End designers should
 *                  implement callback routine as necessary.
 *
 * Note:            None
 *******************************************************************/
void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
}

/*******************************************************************
 * Function:        void USBCBErrorHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *
 * Note:            None
 *******************************************************************/
void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

	// Typically, user firmware does not need to do anything special
	// if a USB error occurs.  For example, if the host sends an OUT
	// packet to your device, but the packet gets corrupted (ex:
	// because of a bad connection, or the user unplugs the
	// USB cable during the transmission) this will typically set
	// one or more USB error interrupt flags.  Nothing specific
	// needs to be done however, since the SIE will automatically
	// send a "NAK" packet to the host.  In response to this, the
	// host will normally retry to send the packet again, and no
	// data loss occurs.  The system will typically recover
	// automatically, without the need for application firmware
	// intervention.
	
	// Nevertheless, this callback function is provided, such as
	// for debugging purposes.
}


/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 * 					firmware must process the request and respond
 *					appropriately to fulfill the request.  Some of
 *					the SETUP packets will be for standard
 *					USB "chapter 9" (as in, fulfilling chapter 9 of
 *					the official USB specifications) requests, while
 *					others may be specific to the USB device class
 *					that is being implemented.  For example, a HID
 *					class device needs to be able to respond to
 *					"GET REPORT" type of requests.  This
 *					is not a standard USB chapter 9 request, and 
 *					therefore not handled by usb_device.c.  Instead
 *					this request should be handled by class specific 
 *					firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 *******************************************************************/
void USBCBCheckOtherReq(void)
{
    USBCheckHIDRequest();
}//end


/*******************************************************************
 * Function:        void USBCBStdSetDscHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *					called when a SETUP, bRequest: SET_DESCRIPTOR request
 *					arrives.  Typically SET_DESCRIPTOR requests are
 *					not used in most applications, and it is
 *					optional to support this type of request.
 *
 * Note:            None
 *******************************************************************/
void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}//end


/*******************************************************************
 * Function:        void USBCBInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 * 					SET_CONFIGURATION (wValue not = 0) request.  This 
 *					callback function should initialize the endpoints 
 *					for the device's usage according to the current 
 *					configuration.
 *
 * Note:            None
 *******************************************************************/
void USBCBInitEP(void)
{
    //enable the HID endpoint
    USBEnableEndpoint(HID_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,64);
}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 * 					peripheral devices to wake up a host PC (such
 *					as if it is in a low power suspend to RAM state).
 *					This can be a very useful feature in some
 *					USB applications, such as an Infrared remote
 *					control	receiver.  If a user presses the "power"
 *					button on a remote control, it is nice that the
 *					IR receiver can detect this signalling, and then
 *					send a USB "command" to the PC to wake up.
 *					
 *					The USBCBSendResume() "callback" function is used
 *					to send this special USB signalling which wakes 
 *					up the PC.  This function may be called by
 *					application firmware to wake up the PC.  This
 *					function should only be called when:
 *					
 *					1.  The USB driver used on the host PC supports
 *						the remote wakeup capability.
 *					2.  The USB configuration descriptor indicates
 *						the device is remote wakeup capable in the
 *						bmAttributes field.
 *					3.  The USB host PC is currently sleeping,
 *						and has previously sent your device a SET 
 *						FEATURE setup packet which "armed" the
 *						remote wakeup capability.   
 *
 *					This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            Interrupt vs. Polling
 *                  -Primary clock
 *                  -Secondary clock ***** MAKE NOTES ABOUT THIS *******
 *                   > Can switch to primary first by calling USBCBWakeFromSuspend()
 
 *                  The modifiable section in this routine should be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of 1-13 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at least 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void)
{
    static WORD delay_count;
    
    USBResumeControl = 1;                // Start RESUME signaling
    
    delay_count = 1800U;                // Set RESUME line for 1-13 ms
    do
    {
        delay_count--;
    }while(delay_count);
    USBResumeControl = 0;
}


/*******************************************************************
 * Function:        BOOL USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, WORD size)
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER:
            Nop();
            break;
        default:
            break;
    }      
    return TRUE; 
}



#ifdef USA_USB
/********************************************************************
*
*						ProcessUSB
*		Analizza i dati provenienti dal Canale USB
*
 *******************************************************************/
void ProcessUSB(void)
{   

unsigned char checksum_USB;
//    // User Application USB tasks
if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

	if(!HIDRxHandleBusy(USBOutHandle))					//Controlla se sono arrivati messaggi dall' host.
    	{ 
		rispondi_usb=1;									// imposto per dafault la risposta anche da USB: Solo il reset dell'evento non deve inviare: verrà quinidi impostato a ZERO su tutti gli eventi

		for (tmp3=1;tmp3<POS_CSUM;tmp3++)				// tramite un ciclo for
			checksum_USB += ReceivedDataBuffer[tmp3];	// calcolo la checksum del pacchetto Arrivato

#ifdef VERIFICA_CHECKSUM			// Se defino il controllo sulle CHECKSUM
					// se START E STOP e CHECKSUM risultano corrette
		if ((ReceivedDataBuffer[POS_START]==START)&&(ReceivedDataBuffer[POS_STOP]==STOP)&&(ReceivedDataBuffer[POS_CSUM]== checksum_USB))	
#else		// altriemtni
			// se solo START E STOP e risultano corrette					
		if ((ReceivedDataBuffer[POS_START]==START)&&(ReceivedDataBuffer[POS_STOP]==STOP))
#endif	
			{
			// se Tipologia di Apparecchio
			if (((ReceivedDataBuffer[POS_TIPO_DEST]==TIPO_MASTERIZZATORE)&&(ReceivedDataBuffer[POS_GRUPPO_DEST]==GRUPPO_MASTERIZZATORE))
			// 	se INDIRIZZO DESTINATARIO CORRISPONDE A QUELLO DEL PC
			&&((ReceivedDataBuffer[POS_DEST]==IP_MASTERIZZATORE_H)&&(ReceivedDataBuffer[POS_DEST+1]==IP_MASTERIZZATORE_MH)&&(ReceivedDataBuffer[POS_DEST+2]==IP_MASTERIZZATORE_ML)&&(ReceivedDataBuffer[POS_DEST+3]==IP_MASTERIZZATORE_L)))
				{
					LED_R=1;									// Attivo Led RXUSB per indicare ricezione comunicazione lato USB
					timer_LED_ROSSO=LED_TIME;						// Attivo il timer per la gestione dello spegnimento automatico in ritardo 

					for(i=14;i<62;i++)											// tramite un ciclo for
						ToSendDataBuffer[i]=0x00;								// Azzero il contenuto del buffer di risposta

					ToSendDataBuffer[0]=START;									// Preparo il byte di START
					ToSendDataBuffer[63]=STOP;									// Preparo il byte di STOP

					ToSendDataBuffer[1]=IP_MASTERIZZATORE_H;					// Inserisco ID Mittente H
					ToSendDataBuffer[2]=IP_MASTERIZZATORE_MH;					// Inserisco ID Mittente MH
					ToSendDataBuffer[3]=IP_MASTERIZZATORE_ML;					// Inserisco ID Mittente ML
					ToSendDataBuffer[4]=IP_MASTERIZZATORE_L;					// Inserisco ID Mittente L
					ToSendDataBuffer[5]=TIPO_MASTERIZZATORE;					// Inserisco Tipologia Mittente 
					ToSendDataBuffer[6]=GRUPPO_MASTERIZZATORE;					// Inserisco Gruppo Mittente

					ToSendDataBuffer[7]=IP_PC_H;								// Inserisco ID Destinatario H
					ToSendDataBuffer[8]=IP_PC_MH;								// Inserisco ID Destinatario MH
					ToSendDataBuffer[9]=IP_PC_ML;								// Inserisco ID Destinatario ML
					ToSendDataBuffer[10]=IP_PC_L;								// Inserisco ID Destinatario L
					ToSendDataBuffer[11]=TIPO_PC;								// Inserisco Tipologia Destinatario 
					ToSendDataBuffer[12]=GRUPPO_PC;								// Inserisco Gruppo Destinatario

					ToSendDataBuffer[POS_CMD]=ReceivedDataBuffer[POS_CMD];		// Inserisco CODICE COMANDO

					switch (ReceivedDataBuffer[POS_CMD])								// decodifico il tipo di comando
						{
						case 22:
						{
							if (Flag_PresenzaCardMifare)							// se card Mifare
							{
								ActualPSCType = ReceivedDataBuffer[14];
								NewPSCType = ReceivedDataBuffer[15];
								NumberOfCardsToDo = ReceivedDataBuffer[16];
								
								StartFormatCard = 1;
							}
						}
						break;

						case LETTURA_CELLE_CARD:								// COMANDO di LETTURA CARD 
							{
							for(i=14;i<20;i++)									// tramite un ciclo for
								ToSendDataBuffer[i]=ReceivedDataBuffer[i];		// ricopio i dati ricevuti

							Tipo_AccessoCard = ReceivedDataBuffer[14];			// prelevo il tipo di Card su cui effettuare le operazioni

 							/******************* SE CARD A CHIP SLE4442 ****************/
//
//							if ((Tipo_AccessoCard == TIPO_LETTURA_SMART) || (Tipo_AccessoCard == TIPO_LETTURA_AUTO))
//								{
//								CellaStart_temp = ReceivedDataBuffer[15];				// Recupero la cella di Partenza
//								NumeroCelle_temp = ReceivedDataBuffer[16];			// Recupero il numero di celle da leggere
//
//								if (NumeroCelle_temp>NUM_CELLE_MAX)					// se il numero di celle da Leggere è superiori al massimo
//									NumeroCelle_temp=NUM_CELLE_DEFAULT;				// impongo il DEFAULT
//
//								if ((Flag_PresenzaCardSmart)&&(!Flag_PresenzaCardMifare))
//									{
//									Flag_AccessoCard=1;													// Blocco Accesso alla Card SMart
//	
//									AnswerToReset();
//									ReadSimSLE4442(READ_CARD, CellaStart_temp, 0x00, NumeroCelle_temp, &ToSendDataBuffer[21]);
//
//									ToSendDataBuffer[20]= OK;											// Se lettura con esito POSITIVO (tutto a posto)
//
//									Flag_AccessoCard=0;													// Sblocco Accesso alla Card SMart
//									}
//								else																	// altrimetni
//									ToSendDataBuffer[20]= 2;											// CARD NON PRESENTE
//								}

							/******************* SE CARD MIFARE ****************/

								if ((Tipo_AccessoCard == TIPO_LETTURA_MIFARE) || (Tipo_AccessoCard == TIPO_LETTURA_AUTO))
									{
	
									settore_temp = ReceivedDataBuffer[17];				// Recupero il numero di Settore da cui leggere
									blocco_temp = ReceivedDataBuffer[18];				// Recupero il numero di Settore da cui leggere
	
									if (settore_temp>NUM_SETTORE_MAX)						// Se il settore è fuori range
										settore_temp=NUM_SETTORE_DEFAULT;					// impongo il DEFAULT	
	
									if (blocco_temp>NUM_BLOCCHI_SETTORE)				// Se il blocco di aprtenza è fuori range
										blocco_temp=NUM_BLOCCHI_DEFAULT;				// impongo il DEFAULT
	
									ST7735_drawString(2, 12, "Lettura:", ST7735_YELLOW, 1);
									ST7735_fillRect(50, 12, 80, 20, ST7735_BLACK);

									if (Flag_PresenzaCardMifare)							// se card Mifare
										{
										Esito_Mifare = LetturaBloccoMifare(settore_temp,blocco_temp);		// Leggo nel settore desiderato, il blocco scelto
	
	
										if (!Esito_Mifare)											// Se lettura con esito POSITIVO (tutto a posto)
											ST7735_drawString(50, 12, "OK!", ST7735_YELLOW, 1);
										else
											ST7735_drawString(50, 12, "ERROR", ST7735_RED, 1);
	
										if (!Esito_Mifare)											// Se lettura con esito POSITIVO (tutto a posto)
											ToSendDataBuffer[19]= OK;
										else
											ToSendDataBuffer[19]= KO;
	
										if (!Esito_Mifare)															// tramite un ciclo for
											{
											for(i=0;i<16;i++)														// Se esito POSITIVO (tutto a posto)
												ToSendDataBuffer[20+i]=Buffer_Mifare[i];									// Inserisco il contenuto dei primi 16byte dati nel buffer di risposta
											}
										else
											for(i=0;i<16;i++)														// Se esito POSITIVO (tutto a posto)
												ToSendDataBuffer[20+i]=0x00;									// Inserisco il contenuto dei primi 16byte dati nel buffer di risposta

										}	// fine contorllo presenza card mifare
									else
										{
										ToSendDataBuffer[19]= 2;			//NESSUNA CARD PRESENTE
										ST7735_drawString(50, 12, "No Card", ST7735_RED, 1);
										}
									}	// fine lettura su MIFARE
								}
							break;

						case SCRITTURA_CELLE_CARD:									// COMANDO di SCRITTURA CARD 
							{
							for(i=14;i<20;i++)										// tramite un ciclo for
								ToSendDataBuffer[i]=ReceivedDataBuffer[i];			// ricopio i dati ricevuti

							Tipo_AccessoCard = ReceivedDataBuffer[14];				// prelevo il tipo di Card su cui effettuare le operazioni

 							/******************* SE CARD A CHIP SLE4442 ****************/
//
//							if ((Tipo_AccessoCard == TIPO_LETTURA_SMART) || (Tipo_AccessoCard == TIPO_LETTURA_AUTO))
//								{
//								CellaStart_temp = ReceivedDataBuffer[15];				// Recupero la cella di Partenza
//								NumeroCelle_temp = ReceivedDataBuffer[16];				// Recupero il numero di celle da leggere
//
//								if (NumeroCelle_temp>NUM_CELLE_MAX)						// se il numero di celle da Leggere è superiori al massimo
//									NumeroCelle_temp=NUM_CELLE_DEFAULT;					// impongo il DEFAULT
//
//								if ((Flag_PresenzaCardSmart)&&(!Flag_PresenzaCardMifare))
//									{
//									Flag_AccessoCard=1;													// Blocco Accesso alla Card SMart
//	
//									WriteSimSLE4442(WRITE_CARD, CellaStart_temp, NumeroCelle_temp, &ReceivedDataBuffer[20]);	// Allora scrivo le celle interessate
//	
//									Flag_AccessoCard=0;													// Sblocco Accesso alla Card SMart
//									}
//								else																	// altrimetni
//									ToSendDataBuffer[20]= 2;											// CARD NON PRESENTE
//								}

							/******************* SE CARD MIFARE ****************/

							if ((Tipo_AccessoCard == TIPO_LETTURA_MIFARE) || (Tipo_AccessoCard == TIPO_LETTURA_AUTO))
								{

								settore_temp = ReceivedDataBuffer[17];				// Recupero il numero di Settore da cui leggere
								blocco_temp = ReceivedDataBuffer[18];				// Recupero il numero di Settore da cui leggere

								if (settore_temp>NUM_SETTORE_MAX)					// Se il settore è fuori range
									settore_temp=NUM_SETTORE_DEFAULT;				// impongo il DEFAULT	

								if (blocco_temp>NUM_BLOCCHI_SETTORE)				// Se il blocco di aprtenza è fuori range
									blocco_temp=NUM_BLOCCHI_DEFAULT;				// impongo il DEFAULT

								ST7735_drawString(2, 22, "Scrittura:", ST7735_ORANGE, 1);
								ST7735_fillRect(60, 22, 90, 30, ST7735_BLACK);

								if (Flag_PresenzaCardMifare)							// se card Mifare
									{
									for (i=0;i<16;i++)
										Buffer_Scrittura_Mifare[i]=ReceivedDataBuffer[19+i];

									Esito_Mifare = ScritturaBloccoMifare(settore_temp,blocco_temp);

									if (!Esito_Mifare)											// Se lettura con esito POSITIVO (tutto a posto)
										{
										ToSendDataBuffer[19]= OK;
										for (i=0;i<16;i++)
											ToSendDataBuffer[20+i]=ReceivedDataBuffer[19+i];
										ST7735_drawString(60, 22, "OK!", ST7735_ORANGE, 1);
										}
									else
										{
										ToSendDataBuffer[19]= KO;
										ST7735_drawString(60, 22, "ERROR", ST7735_RED, 1);
										}
									}	// fine controllo presenza card mifare
								else
									{
									ToSendDataBuffer[19]= 2;			//NESSUNA CARD PRESENTE
									ST7735_drawString(60, 22, "NO CARD", ST7735_RED, 1);
									}
								}	// fien lettura su MIFARE
							}
						break;
				
						case CONFRONTA_PSC:											// COMANDO per verificare PSC
							{

							for(i=14;i<20;i++)										// tramite un ciclo for
								ToSendDataBuffer[i]=ReceivedDataBuffer[i];			// ricopio i dati ricevuti

							Tipo_AccessoCard = ReceivedDataBuffer[14];				// prelevo il tipo di Card su cui effettuare le operazioni
							DisegnaStato = 1;
 							/******************* SE CARD A CHIP SLE4442 ****************/

//							if ((Tipo_AccessoCard == TIPO_LETTURA_SMART) || (Tipo_AccessoCard == TIPO_LETTURA_AUTO))
//								{
//								if ((Flag_PresenzaCardSmart)&&(!Flag_PresenzaCardMifare))
//									{
//									Flag_AccessoCard=1;										// Blocco Accesso alla Card SMart
//	
//									switch (ReceivedDataBuffer[15])
//										{
//										case 0:												// PSC Vuoto
//											psc_1=PSC1_V;	
//											psc_2=PSC2_V;
//											psc_3=PSC3_V;
//										break;
//
//										case 1:												// PSC TEST
//											psc_1=PSC1_T;	
//											psc_2=PSC2_T;
//											psc_3=PSC3_T;
//										break;
//
//										case 2:												// PSC Microtech
//											psc_1=PSC1_M;	
//											psc_2=PSC2_M;
//											psc_3=PSC3_M;
//										break;
//
//										case 3:												// PSC Custom (passato dal Software)
//											psc_1=ReceivedDataBuffer[16];	
//											psc_2=ReceivedDataBuffer[17];
//											psc_3=ReceivedDataBuffer[18];
//										break;
//										}
//
//									AnswerToReset();
//									PscVerifySLE4442(psc_1,psc_2,psc_3);
//	
//									if (PscErrorSLE4442)
//										ToSendDataBuffer[20]=0x01;							// indico PSC valido
//									else
//										ToSendDataBuffer[20]=0x00;							// indico PSC ERRATO
//	
//									Flag_AccessoCard=0;										// Sblocco Accesso alla Card SMart
//									}
//								}
//
							/******************* SE CARD MIFARE ****************/

							if ((Tipo_AccessoCard == TIPO_LETTURA_MIFARE) || (Tipo_AccessoCard == TIPO_LETTURA_AUTO))
								{
								if (Flag_PresenzaCardMifare)
									{
									settore_temp = ReceivedDataBuffer[19];				// Recupero il numero di Settore da cui leggere

									for(i=14;i<20;i++)									// tramite un ciclo for
										ToSendDataBuffer[i]=ReceivedDataBuffer[i];		// Azzero il contenuto del buffer di risposta
									
									LED_5=0;
	
									switch (ReceivedDataBuffer[15])
										{
										case 0:												// PSC Vuoto
											Sectorkey[0]=PSC1_V;	
											Sectorkey[1]=PSC2_V;
											Sectorkey[2]=PSC3_V;
											Sectorkey[3]=PSC1_V;	
											Sectorkey[4]=PSC2_V;
											Sectorkey[5]=PSC3_V;
										break;

										case 1:												// PSC TEST
											Sectorkey[0]=0;	
											Sectorkey[1]=PSC1_T;
											Sectorkey[2]=0;
											Sectorkey[3]=PSC2_T;	
											Sectorkey[4]=0;
											Sectorkey[5]=PSC3_T;
										break;

										case 2:												// PSC Microtech
											Sectorkey[0]=PSC1_M;	
											Sectorkey[1]=PSC1_M;
											Sectorkey[2]=PSC2_M;
											Sectorkey[3]=PSC2_M;	
											Sectorkey[4]=PSC3_M;
											Sectorkey[5]=PSC3_M;
										break;

										default:												// PSC Custom (passato dal Software)
											Sectorkey[0]=ReceivedDataBuffer[16];	
											Sectorkey[1]=ReceivedDataBuffer[16];
											Sectorkey[2]=ReceivedDataBuffer[17];
											Sectorkey[3]=ReceivedDataBuffer[17];	
											Sectorkey[4]=ReceivedDataBuffer[18];
											Sectorkey[5]=ReceivedDataBuffer[18];
										break;
										}

								//	Esito_Mifare = VerificaPSCMifare((unsigned char)settore_temp,(unsigned char)FormatoCardRilevata);

									Esito_Mifare = MFRC522_CheckSectorKey(settore_temp, PICC_AUTHENT1A, Sectorkey, str);
			
									ST7735_drawString(2, 2, "PSC:", ST7735_BLUE, 1);
									ST7735_fillRect(26, 2, 60, 10, ST7735_BLACK);

									if (Esito_Mifare)											// Se lettura con esito POSITIVO (tutto a posto)
										{
										ToSendDataBuffer[20]= OK;
										LED_5=1;
										ST7735_drawString(30, 2, "OK!", ST7735_BLUE, 1);
										}
									else
										{
										ToSendDataBuffer[20]= KO;
										ST7735_drawString(30, 2, "ERROR", ST7735_RED, 1);
										}
//									Esito_Mifare = VerificaPSCMifare(0,(unsigned char)FormatoCardRilevata);

									}
								else															// Altrimetni 
									{
									ToSendDataBuffer[20]= 2;									// CARD NON INSERITA
									ST7735_drawString(30, 2, "NO CARD", ST7735_RED, 1);	
									}	
								}		// fine confronto PSC MIFARE
							}
						break;
				
						case SOSTITUZIONE_PSC:													// COMANDO per cambio PSC
							{

							for(i=14;i<24;i++)										// tramite un ciclo for
								ToSendDataBuffer[i]=ReceivedDataBuffer[i];			// ricopio i dati ricevuti

							Tipo_AccessoCard = ReceivedDataBuffer[14];				// prelevo il tipo di Card su cui effettuare le operazioni

 							/******************* SE CARD A CHIP SLE4442 ****************/

//							if ((Tipo_AccessoCard == TIPO_LETTURA_SMART) || (Tipo_AccessoCard == TIPO_LETTURA_AUTO))
//								{
//								if ((Flag_PresenzaCardSmart)&&(!Flag_PresenzaCardMifare))			// se c'è la SLE4442
//									{
//									Flag_AccessoCard=1;											// Blocco Accesso alla Card SMart
//	
//									switch (ReceivedDataBuffer[15])
//										{
//										case 0:												// PSC Vuoto
//											psc_1=PSC1_V;	
//											psc_2=PSC2_V;
//											psc_3=PSC3_V;
//										break;
//
//										case 1:												// PSC TEST
//											psc_1=PSC1_T;	
//											psc_2=PSC2_T;
//											psc_3=PSC3_T;
//										break;
//
//										case 2:												// PSC Microtech
//											psc_1=PSC1_M;	
//											psc_2=PSC2_M;
//											psc_3=PSC3_M;
//										break;
//
//										default:												// PSC Custom (passato dal Software)
//											psc_1=ReceivedDataBuffer[16];	
//											psc_2=ReceivedDataBuffer[17];
//											psc_3=ReceivedDataBuffer[18];
//										break;
//										}
//
//									AnswerToReset();
//									PscVerifySLE4442(psc_1,psc_2,psc_3);	
//								
//									if (PscErrorSLE4442)										// se conferma PSC corretto
//										{
//
//										switch (ReceivedDataBuffer[20])							// Verifico Nuova Tipologia di pre-impostazione
//											{
//											case 0:												// PSC Vuoto
//												psc_1=PSC1_V;	
//												psc_2=PSC2_V;
//												psc_3=PSC3_V;
//											break;
//	
//											case 1:												// PSC TEST
//												psc_1=PSC1_T;	
//												psc_2=PSC2_T;
//												psc_3=PSC3_T;
//											break;
//	
//											case 2:												// PSC Microtech
//												psc_1=PSC1_M;	
//												psc_2=PSC2_M;
//												psc_3=PSC3_M;
//											break;
//	
//											default:												// PSC Custom (passato dal Software)
//												psc_1=ReceivedDataBuffer[21];	
//												psc_2=ReceivedDataBuffer[22];
//												psc_3=ReceivedDataBuffer[23];
//											break;
//											}
//
//
//								        WriteSimSLE4442(WRITE_SECURITY_MEMORY,0x01,1, &psc_1);  // scrittura PSC1
//								        WriteSimSLE4442(WRITE_SECURITY_MEMORY,0x02,1, &psc_2); // scrittura PSC2
//								        WriteSimSLE4442(WRITE_SECURITY_MEMORY,0x03,1, &psc_3); // scrittura PSC3
//	
//										PscVerifySLE4442(psc_1,psc_2,psc_3); 					// verifico il nuovo PSC
//	
//										if (PscErrorSLE4442)									// se conferma PSC corretto
//											ToSendDataBuffer[22]=OK;							// indico al PC che è andato tutto a posto
//									    } 
//									else
//										ToSendDataBuffer[22]=KO;								// indico al PC che PSC orginale, è sbalgiato
//	
//									Flag_AccessoCard=0;											// Sblocco Accesso alla Card SMart
//									}
//								else
//									ToSendDataBuffer[22]=0x02;						// card NON RPESENTE
//								}

							/******************* SE CARD MIFARE ****************/

							if ((Tipo_AccessoCard == TIPO_LETTURA_MIFARE) || (Tipo_AccessoCard == TIPO_LETTURA_AUTO))
								{
								if (Flag_PresenzaCardMifare)
									{
									settore_temp = ReceivedDataBuffer[19];				// Recupero il numero di Settore da cui leggere
	
									for(i=14;i<20;i++)									// tramite un ciclo for
										ToSendDataBuffer[i]=ReceivedDataBuffer[i];		// Azzero il contenuto del buffer di risposta
	
									switch (ReceivedDataBuffer[15])
										{
										case 0:												// PSC Vuoto
											Sectorkey[0]=PSC1_V;	
											Sectorkey[1]=PSC2_V;
											Sectorkey[2]=PSC3_V;
											Sectorkey[3]=PSC1_V;	
											Sectorkey[4]=PSC2_V;
											Sectorkey[5]=PSC3_V;
										break;

										case 1:												// PSC TEST
											Sectorkey[0]=0;	
											Sectorkey[1]=PSC1_T;
											Sectorkey[2]=0;
											Sectorkey[3]=PSC2_T;	
											Sectorkey[4]=0;
											Sectorkey[5]=PSC3_T;
										break;

										case 2:												// PSC Microtech
											Sectorkey[0]=PSC1_M;	
											Sectorkey[1]=PSC1_M;
											Sectorkey[2]=PSC2_M;
											Sectorkey[3]=PSC2_M;	
											Sectorkey[4]=PSC3_M;
											Sectorkey[5]=PSC3_M;
										break;

										default:												// PSC Custom (passato dal Software)
											Sectorkey[0]=ReceivedDataBuffer[16];	
											Sectorkey[1]=ReceivedDataBuffer[16];
											Sectorkey[2]=ReceivedDataBuffer[17];
											Sectorkey[3]=ReceivedDataBuffer[17];	
											Sectorkey[4]=ReceivedDataBuffer[18];
											Sectorkey[5]=ReceivedDataBuffer[18];
										break;
										}

									switch (ReceivedDataBuffer[20])
										{
										case 0:												// PSC Vuoto
											Sectorkey_Nuovo[0]=PSC1_V;	
											Sectorkey_Nuovo[1]=PSC2_V;
											Sectorkey_Nuovo[2]=PSC3_V;
											Sectorkey_Nuovo[3]=PSC1_V;	
											Sectorkey_Nuovo[4]=PSC2_V;
											Sectorkey_Nuovo[5]=PSC3_V;
										break;

										case 1:												// PSC TEST
											Sectorkey_Nuovo[0]=0;	
											Sectorkey_Nuovo[1]=PSC1_T;
											Sectorkey_Nuovo[2]=0;
											Sectorkey_Nuovo[3]=PSC2_T;	
											Sectorkey_Nuovo[4]=0;
											Sectorkey_Nuovo[5]=PSC3_T;
										break;

										case 2:												// PSC Microtech
											Sectorkey_Nuovo[0]=PSC1_M;	
											Sectorkey_Nuovo[1]=PSC1_M;
											Sectorkey_Nuovo[2]=PSC2_M;
											Sectorkey_Nuovo[3]=PSC2_M;	
											Sectorkey_Nuovo[4]=PSC3_M;
											Sectorkey_Nuovo[5]=PSC3_M;
										break;

										default:												// PSC Custom (passato dal Software)
											Sectorkey_Nuovo[0]=ReceivedDataBuffer[21];	
											Sectorkey_Nuovo[1]=ReceivedDataBuffer[21];
											Sectorkey_Nuovo[2]=ReceivedDataBuffer[22];
											Sectorkey_Nuovo[3]=ReceivedDataBuffer[22];	
											Sectorkey_Nuovo[4]=ReceivedDataBuffer[23];
											Sectorkey_Nuovo[5]=ReceivedDataBuffer[23];
										break;
										}
//									Fase_Masterizzazione=1;

									ST7735_drawString(2, 42, "Cambio:", ST7735_PINK, 1);
									ST7735_fillRect(42, 42, 128, 50, ST7735_BLACK);

									Esito_Mifare = ModificaPSC(settore_temp,FormatoCardRilevata,Sectorkey_Nuovo);		//Eseguo Sostituzione DLE PSC
	
									if (Esito_Mifare==3)							// Se PSC ORIGINALE è SBAGLIATO
										{
										ToSendDataBuffer[24]=KO;					// indico Sostituzione NON AVVENUTA con problemi
										ST7735_drawString(42, 42, "PSC1 Errato", ST7735_RED, 1);
										}
									else
										{
										ToSendDataBuffer[24]=OK;					// indico Sostituzione OK
										ST7735_drawString(42, 42, "OK", ST7735_PINK, 1);
										}
									}
								else
									{
									ToSendDataBuffer[24]=2;						// CARD NON PRESENTE
									ST7735_drawString(42, 42, "NO Card", ST7735_RED, 1);
									}
								}
							}
						break;
				
						case STATO_MODULO:									// COMANDO POLLING
							{

							if (Flag_PresenzaCardMifare)
								{
								ToSendDataBuffer[18]= 0x80;
	
//								if (Flag_PresenzaCardSmart)
//									ToSendDataBuffer[22]= 1;
//								
								if (Flag_PresenzaCardMifare)
									{
									switch (FormatoCardRilevata)
										{
										case MIFARE_ULTRALIGHT:		ToSendDataBuffer[22]= 2;	break;
										case MIFARE_ONE_S50:		ToSendDataBuffer[22]= 3;	break;
										case MIFARE_ONE_S70:		ToSendDataBuffer[22]= 4;	break;
										case MIFARE_PRO_X:			ToSendDataBuffer[22]= 5;	break;
										case MIFARE_DESFIRE:		ToSendDataBuffer[22]= 6;	break;
										}
									}
								}

							ToSendDataBuffer[38]=MAJOR_RELEASE;					// inserisco la versione firmware_principale
							ToSendDataBuffer[39]=MIDDLE_RELEASE;					// inserisco la versione firmware_media
							ToSendDataBuffer[40]=MINOR_RELEASE;					// inserisco la versione firmware_bassa

//							if (Flag_PresenzaCardSmart)							// Se c'è la SLE4442 Inserita
//								ToSendDataBuffer[13]=1;							// Indico SmartCard presente
//							else												// altrimenti
//								{
								if(!Flag_PresenzaCardMifare)						// se c'è la MIFARE
									ToSendDataBuffer[13]=2;						// Indico Mifare presente
//								}
							}
						break;
					
//						case AGGIORNA_FW:										// COMANDO AGGIORNA FW
//							{
//							Timer_Reset=ReceivedDataBuffer[10];					// Carico il timer del Riavvio
//							ToSendDataBuffer[10]=ReceivedDataBuffer[10];			// Azzero il contenuto del buffer di risposta
////							WRITE_EEPROM_I2C(ADDRESS_MEM, STATO_BOOTLOADER_EE,1);						
//							ToSendDataBuffer[11]=1;								// Consenso Riavvio immiennte
//							}

						case TERMINA_PROGRAMMAZIONE_CARD: 
							{
							Fase_Masterizzazione = 0;
							ToSendDataBuffer[14] = 1;									// Azzero il contenuto del buffer di risposta
							ST7735_drawString(2, 110, "Sistema Ripristinato", ST7735_GREEN, 1);		// x,y, testo, colore, dimensione
							LED_5 = 0;
							MFRC522_Halt();
							MFRC522_ResetEncrypt();

							}

//						case LEGGI_CELLE_EEPROM:									// COMANDO LEGGI_CONFIGURAZIONE_USB
//							{
//							temp16_1 = ReceivedDataBuffer[15];
//							temp16_1 = temp16_1 <<8;
//							temp16_1 += ReceivedDataBuffer[16];
//	
//							NumeroCelle_temp=ReceivedDataBuffer[17];				// Recupero il numero di celle da leggere
//
//							for(i=14;i<18;i++)										// tramite un ciclo for
//								ToSendDataBuffer[i]=ReceivedDataBuffer[i];			// ricopio buffer in ingresso su quello d'uscita
//
//							if (!ReceivedDataBuffer[14])							// se Memmroia PRINCIPALE
//								{
//								for(i=temp16_1; i<(temp16_1+NumeroCelle_temp); temp16_1++)		// tramite un ciclo for	
//									ToSendDataBuffer[18+i]=READ_EEPROM_I2C(ADDRESS_MEM, temp16_1);			// Inserisco nel buffer i uscita i dati letti dall'EEPROM
//								}
//							}
//						break;
//
//						case SCRIVI_CELLE_EEPROM:									// COMANDO SCRIVI_CONFIGURAZIONE_USB
//							{
//							temp16_2 = ReceivedDataBuffer[15];
//							temp16_2 = temp16_2 <<8;
//							temp16_2 += ReceivedDataBuffer[16];
//	
//							NumeroCelle_temp=ReceivedDataBuffer[17];				// Recupero il numero di celle da leggere
//
//							for(i=14; i<(18+NumeroCelle_temp); i++)					// tramite un ciclo for
//								ToSendDataBuffer[i]=ReceivedDataBuffer[i];			// ricopio buffer in ingresso su quello d'uscita
//
//							for(i=temp16_2; i<(temp16_2+NumeroCelle_temp); temp16_2++)				// tramite un ciclo for	
//								WRITE_EEPROM_I2C(ADDRESS_MEM, temp16_2,ReceivedDataBuffer[18+temp16_2]);		// scrivo in EEPROM i VALORI passatogli da USB
//
//							CaricaConfigurazione();									// Carico Configurazione
//							}
//						break;
//
//						case RICHIESTA_INSERIMENTO:								// Reset RICHESTA INSERIMENTO/ESTRAZIONE CARD
//							{
//							rispondi_usb=0;										// non inviare altri dati su USB
//							InvioCard_Inserita=0;								// Blocco invio di Card Inserita/estratta
//							Timer_EventiCard=0;									// Blocco timer invo evento
//
//							if(Flag_PresenzaCardSmart)
//								InvioCard_Inserita_old=1;
//
//							if(!Flag_PresenzaCardSmart)
//								InvioCard_Inserita_old=0;
//
//							TentativiEventi_Card=NUM_TENTATIVI_EVENTI;			// ripristino il numero dei tentativi degli evetni	
//							}
//						break;
						}
				
					if((!HIDTxHandleBusy(USBInHandle))&&(rispondi_usb==1))						// se il cnaale in uscita è libero ed i comandi hanno dato il consensonel rispondere sull'USB
						USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],64);		// allora invia il pacchetto dati
				
				}	// fine mittente=PC, destinatario= MASTERIZZATORE
		}	// fine START e STOP

	USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,64);        // Rispondi sull'USb e predisponiti per un nuovo pacchetto dati USB
    }
}//end ProcessIO
#endif
