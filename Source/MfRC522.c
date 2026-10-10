
#include "..\Header\HardwareProfile.h"
//#include "..\Header\main.h"
#include "..\Header\compiler.h"
//#include "..\Header\Variabili.h"
#include "..\Header\MfRC522.h"

extern void SPIPut1(unsigned char v);
extern unsigned char SPIGet1(void);
extern void delay_ms(unsigned int sleep_ms);
extern void delay_us(unsigned char sleep_us);



/*
 * Function Name: Write_MFRC5200
 * Function Description: To a certain MFRC522 register to write a byte of data
 * Input Parameters: addr - register address; val - the value to be written
 * Return value: None
 */
void MFRC522_WriteRegister(unsigned char Address2, unsigned char value2)
{
MF522_CS = 0;
SPIPut1((Address2 << 1) & 0x7E);	
SPIPut1(value2);
MF522_CS = 1;
}


/*
 * Function Name: MFRC522_ReadRegister
 * Description: From a certain MFRC522 read a byte of data register
 * Input Parameters: addr - register address
 * Returns: a byte of data read from the
 */
unsigned char MFRC522_ReadRegister(unsigned char Address)
{
//unsigned char Address=2;   
unsigned char data_read=6; 

MF522_CS = 0;
SPIPut1(((Address<<1) & 0x7E) | 0x80);	
data_read = SPIGet1();

MF522_CS = 1;

return data_read;
}

/*
 * Function Name: MFRC522_SetBitMask
 * Description: Set RC522 register bit
 * Input parameters: reg - register address; mask - set value
 * Return value: None
 */
void MFRC522_SetBitMask(unsigned char reg, unsigned char mask)
{
  unsigned char tmp;
  tmp = MFRC522_ReadRegister(reg);
  MFRC522_WriteRegister(reg, tmp | mask);  // set bit mask
}


/*
 * Function Name: ClearBitMask
 * Description: clear RC522 register bit
 * Input parameters: reg - register address; mask - clear bit value
 * Return value: None
*/
void MFRC522_ClearBitMask(unsigned char reg, unsigned char mask)
{
  unsigned char tmp;
  unsigned char new_value;

  	tmp = MFRC522_ReadRegister(reg);
	new_value = tmp & (~mask);
  	MFRC522_WriteRegister(reg,new_value );  // clear bit mask
}


/*
 * Function Name: AntennaOn
 * Description: Open antennas, each time you start or shut down the natural barrier between the transmitter should be at least 1ms interval
 * Input: None
 * Return value: None
 */
void AntennaOn(void)
{
unsigned char temp;

	temp = MFRC522_ReadRegister(TxControlReg);
	if (!(temp & 0x03))
		MFRC522_SetBitMask(TxControlReg, 0x03);
}


/*
  * Function Name: AntennaOff
  * Description: Close antennas, each time you start or shut down the natural barrier between the transmitter should be at least 1ms interval
  * Input: None
  * Return value: None
 */
void AntennaOff(void)
{
	MFRC522_ClearBitMask(TxControlReg, 0x03);
}


/*
 * Function Name: ResetMFRC522
 * Description: Reset RC522
 * Input: None
 * Return value: None
 */
void MFRC522_Reset(void)
{
  MFRC522_WriteRegister(CommandReg, PCD_RESETPHASE);
}



void MFRC522_SetTimeOut(unsigned int Tempo)   
{   
    MFRC522_WriteRegister(TReloadRegL, ((unsigned char)(Tempo & 0xff)));   
    MFRC522_WriteRegister(TReloadRegH, ((unsigned char)((Tempo >> 8) & 0xff)));   
}  


/*
 * Function Name: InitMFRC522
 * Description: Initialize RC522
 * Input: None
 * Return value: None
*/
void MFRC522_Init(void)
{

MF522_CS = 1;
MF522_RST = 0;								// Reset Hardware del Chip RC522
delay_ms(50);								// Ritardo Software per evitare che si blocchi il chip e l'SPI
MF522_RST = 1;								// Reset Hardware del Chip RC522

MFRC522_Reset();							// Reset Software del Chip RC522
delay_ms(10);								// Ritardo Software per evitare che si blocchi il chip e l'SPI

//Timer: TPrescaler*TreloadVal/6.78MHz = 24ms

MFRC522_WriteRegister(TModeReg, 0x8D);                //Tauto=1; f(Timer) = 6.78MHz/TPreScaler
MFRC522_WriteRegister(TPrescalerReg, 0x3E);        //TModeReg[3..0] + TPrescalerReg
MFRC522_WriteRegister(TReloadRegL, 30);
MFRC522_WriteRegister(TReloadRegH, 0);

MFRC522_WriteRegister(TxAutoReg, 0x40);                //100%ASK
MFRC522_WriteRegister(ModeReg, 0x3D);                //CRC Initial value 0x6363        ???

//ClearBitMask(Status2Reg, 0x08);                //MFCrypto1On=0
//MFRC522_WriteRegister(RxSelReg, 0x86);                //RxWait = RxSelReg[5..0]
//MFRC522_WriteRegister(TxModeReg, 0x00);                 // 106 kBd

AntennaOn();              						  //Open the antenna
MFRC522_WriteRegister(RFCfgReg, 0x50);                   //RxGain = 48dB
}


/*
 * Function Name: MFRC522_Request
 * Description: Find cards, read the card type number
 * Input parameters: reqMode - find cards way
 *                         TagType - Return Card Type
 *                                 0x4400 = Mifare_UltraLight
 *                                0x0400 = Mifare_One(S50)
 *                                0x0200 = Mifare_One(S70)
 *                                0x0800 = Mifare_Pro(X)
 *                                0x4403 = Mifare_DESFire
 * Return value: the successful return MI_OK
 */
unsigned char MFRC522_Request(unsigned char reqMode, unsigned char *TagType)
{
  unsigned char status;
 unsigned int backBits;                        //The received data bits

  MFRC522_WriteRegister(BitFramingReg, 0x07);                //TxLastBists = BitFramingReg[2..0]        ???

  TagType[0] = reqMode;
  status = MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

  if ((status == MI_OK) && (backBits == 0x10))
    return MI_OK;

  return MI_NOTAGERR;
}


/*
 * Function Name: MFRC522_ToCard
 * Description: RC522 and ISO14443 card communication
 * Input Parameters: command - MF522 command word,
 *                         sendData--RC522 sent to the card by the data
 *                         sendLen--Length of data sent
 *                         backData--Received the card returns data,
 *                         backLen--Return data bit length
 * Return value: the successful return MI_OK
 */
unsigned char MFRC522_ToCard(unsigned char command, unsigned char *sendData, unsigned char sendLen, 
                             unsigned char *backData, unsigned int *backLen) {
    unsigned char status = MI_ERR;
    unsigned char irqEn = 0x00;
    unsigned char waitIRq = 0x00;
    unsigned char lastBits;
    unsigned char n;
    unsigned int i;

    // 1. Configura le maschere di interrupt in base al comando richiesto
    if (command == PCD_AUTHENT) {
        irqEn = 0x12;   // Abilita IdleIRq e TxIRq
        waitIRq = 0x10; // Attende solo IdleIRq
    }
    if (command == PCD_TRANSCEIVE) {
        irqEn = 0x77;   // Abilita TxIRq, RxIRq, IdleIRq, HiAlertIRq, LoAlertIRq, ErrIRq, TimerIRq
        waitIRq = 0x30; // Attende RxIRq o IdleIRq
    }

    // 2. Sospende i comandi correnti, pulisce i flag di interrupt e azzera la FIFO
    MFRC522_WriteRegister(CommIEnReg, irqEn | 0x80); // Invia configurazione interrupt
    MFRC522_ClearBitMask(CommIrqReg, 0x80);          // Cancella i bit di interrupt correnti
    MFRC522_SetBitMask(FIFOLevelReg, 0x80);          // Flush del buffer FIFO
    MFRC522_WriteRegister(CommandReg, PCD_IDLE);     // Mette il chip in IDLE

    // 3. Carica i dati da trasmettere all'interno del buffer FIFO dell'MFRC522
    for (i = 0; i < sendLen; i++) {
        MFRC522_WriteRegister(FIFODataReg, sendData[i]);
    }

    // 4. Avvia l'esecuzione del comando inserito
    MFRC522_WriteRegister(CommandReg, command);
    if (command == PCD_TRANSCEIVE) {
        MFRC522_SetBitMask(BitFramingReg, 0x80); // Avvia la trasmissione dei dati (StartSend)
    }

    // 5. Ciclo di polling per attendere la risposta o il timeout temporale
    // Nota: Il valore 2000 è calibrato empiricamente per clock SPI attorno a 4-8MHz. Adattare se necessario.
    i = 2000; 
    do {
        n = MFRC522_ReadRegister(CommIrqReg);
        i--;
    } while ((i != 0) && !(n & 0x01) && !(n & waitIRq)); // Esce se timeout, errore timer o interrupt valido

    MFRC522_ClearBitMask(BitFramingReg, 0x80); // Ferma la trasmissione (StartSend = 0)

    // 6. Analisi dei risultati ottenuti dopo il ciclo di polling
    if (i != 0) { // Se non siamo usciti per timeout software
        if (!(MFRC522_ReadRegister(ErrorReg) & 0x1B)) { // Verifica che non ci siano errori (BufferOvfl, CollErr, ParityErr, ProtocolErr)
            status = MI_OK;

            if (n & irqEn & 0x01) {
                status = MI_NOTAGERR; // Il timer dell'MFRC522 è scaduto senza ricevere risposte dal tag
            }

            if (command == PCD_TRANSCEIVE) {
                // Legge quanti byte sono stati inseriti dal tag nella FIFO del lettore
                n = MFRC522_ReadRegister(FIFOLevelReg);
                lastBits = MFRC522_ReadRegister(ControlReg) & 0x07; // Verifica quanti bit validi ci sono nell'ultimo byte ricevuto
                
                if (lastBits != 0) {
                    *backLen = (n - 1) * 8 + lastBits; // Calcolo esatto della lunghezza in bit
                } else {
                    *backLen = n * 8;
                }

                if (n == 0) {
                    n = 1;
                }
                if (n > 16) { // Protezione per non superare le dimensioni del buffer standard
                    n = 16;
                }

                // Estrae fisicamente i byte ricevuti dalla FIFO e li sposta nella memoria del PIC18
                for (i = 0; i < n; i++) {
                    backData[i] = MFRC522_ReadRegister(FIFODataReg);
                }
            }
        } else {
            status = MI_ERR; // Rilevato un errore hardware o di collisione non gestibile
        }
    }

    return status;
}


/*
 * Function Name: MFRC522_Anticoll
 * Description: Anti-collision detection, reading selected card serial number card
 * Input parameters: serNum - returns 4 bytes card serial number, the first 5 bytes for the checksum byte
 * Return value: the successful return MI_OK
 */
unsigned char MFRC522_Anticoll(unsigned char *serNum) {
    unsigned char status;
    unsigned char i;
    unsigned char serNumCheck = 0;
    unsigned int unLen;

    // 1. Configura il registro dei bit per eliminare l'allineamento parziale (azzera i bit residui)
    MFRC522_WriteRegister(BitFramingReg, 0x00);

    // 2. Prepara il comando di anticollisione (0x93) e il valore NVB (0x20 = 2 byte validi trasmessi)
    serNum[0] = PICC_ANTICOLL;
    serNum[1] = 0x20;

    // 3. Invia la richiesta e attende la risposta completa (UID + Checksum) dal tag
    status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

    if (status == MI_OK) {
        // 4. Verifica la validità matematica del codice (BCC Checksum)
        // Lo XOR consecutivo dei primi 4 byte dell'UID deve coincidere con il 5° byte (BCC)
        for (i = 0; i < 4; i++) {
            serNumCheck ^= serNum[i];
        }
        
        if (serNumCheck != serNum[4]) {
            status = MI_ERR; // Errore di checksum: dati corrotti durante la trasmissione
        }
    }

    return status;
}


/*
 * Function Name: MFRC522_CalculateCRC
 * Description: CRC calculation with MF522
 * Input parameters: pIndata - To read the CRC data, len - the data length, pOutData - CRC calculation results
 * Return value: None
 */
void MFRC522_CalculateCRC(unsigned char *pIndata, unsigned char len, unsigned char *pOutData)
{
  unsigned char ee, n;

  MFRC522_ClearBitMask(DivIrqReg, 0x04);                        //CRCIrq = 0
  MFRC522_SetBitMask(FIFOLevelReg, 0x80);                        //Clear the FIFO pointer
  //MFRC522_WriteRegister(CommandReg, PCD_IDLE);

  //Writing data to the FIFO
  for (ee=0; ee<len; ee++)
  {
    MFRC522_WriteRegister(FIFODataReg, *(pIndata+ee));
  }
  MFRC522_WriteRegister(CommandReg, PCD_CALCCRC);

  //Wait CRC calculation is complete
  ee = 0xFF;
  do
  {
    n = MFRC522_ReadRegister(DivIrqReg);
    ee--;
  }
  while ((ee!=0) && !(n&0x04));                        //CRCIrq = 1

  //Read CRC calculation result
  pOutData[0] = MFRC522_ReadRegister(CRCResultRegL);
  pOutData[1] = MFRC522_ReadRegister(CRCResultRegM);
}
/*
 * Function Name: MFRC522_SelectTag
 * Description: Selection card, read the card memory capacity
 * Input parameters: serNum - Incoming card serial number
 * Return value: the successful return of card capacity
 */
unsigned char MFRC522_SelectTag(unsigned char *serNum)
{
  unsigned char i;
  unsigned char status;
  unsigned char size;
  unsigned int recvBits;
  unsigned char buffer[9];

  buffer[0] = PICC_SElECTTAG;
  buffer[1] = 0x70;
  
  for (i = 0; i < 5; i++)
	{
        buffer[i + 2] = *(serNum + i);
    }
    
  MFRC522_CalculateCRC(buffer, 7, &buffer[7]);                //??
  status = MFRC522_ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);

  if ((status == MI_OK) && (recvBits == 0x18))
  {
    size = buffer[0];
  }
  else
  {
    size = 0;
  }

  return size;
}
/*
 * Function Name: MFRC522_Auth
 * Description: Verify card password
 * Input parameters: authMode - Password Authentication Mode
                 0x60 = authentication Key A
                 0x61 = Authentication Key B
             BlockAddr--Block address
             Sectorkey--Sector password
             serNum--Card serial number, 4-byte
 * Return value: the successful return MI_OK
 */
unsigned char MFRC522_Auth(unsigned char authMode, unsigned char BlockAddr, unsigned char *Sectorkey, unsigned char *serNum)
{
  unsigned char status;
  unsigned int recvBits;
  unsigned char buff[16];
  unsigned char i;
//unsigned char StatusRegister=0;

  //Verify the command block address + sector + password + card serial number
  buff[0] = authMode;
  buff[1] = BlockAddr;
  
    // Copia la chiave di cifratura a 6 byte nel buffer
    for (i = 0; i < 6; i++)
	{    
        buff[i + 2] = *(Sectorkey + i);   
    }
    
    // Copia i primi 4 byte del numero di serie (UID) della tessera nel buffer
    for (i = 0; i < 4; i++)
	{    
        buff[i + 8] = *(serNum + i);   
    }
    
    // 2. Invia i dati accumulati alla card eseguendo il comando di cifratura hardware PCD_AUTHENT
    status = MFRC522_ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);
    
    // 3. Verifica nel registro di stato dell'MFRC522 se la crittografia Crypto1On è attiva
    if ((status != MI_OK) || (!(MFRC522_ReadRegister(Status2Reg) & 0x08))) {   
        status = MI_ERR;   
    }

  return status;
}
/*
 * Function Name: MFRC522_Read
 * Description: Read block data
 * Input parameters: blockAddr - block address; recvData - read block data
 * Return value: the successful return MI_OK
 */
unsigned char MFRC522_Read(unsigned char blockAddr, unsigned char *recvData)
{
  unsigned char status;
  unsigned int unLen;

  recvData[0] = PICC_READ;
  recvData[1] = blockAddr;
  MFRC522_CalculateCRC(recvData,2, &recvData[2]);
  status = MFRC522_ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

  if ((status != MI_OK) || (unLen != 0x90))
  {
    status = MI_ERR;
  }

  return status;
}
/*
 * Function Name: MFRC522_Write
 * Description: Write block data
 * Input parameters: blockAddr - block address; writeData - to 16-byte data block write
 * Return value: the successful return MI_OK
 */
unsigned char MFRC522_Write(unsigned char blockAddr, unsigned char *writeData)
{
  unsigned char status;
  unsigned int recvBits;
  unsigned char i;
  unsigned char buff[18];

  buff[0] = PICC_WRITE;
  buff[1] = blockAddr;
  MFRC522_CalculateCRC(buff, 2, &buff[2]);
  status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

  if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
  {
    status = MI_ERR;
  }

  if (status == MI_OK)
  {
    for (i=0; i<16; i++)                //Data to the FIFO write 16Byte
    {
      buff[i] = *(writeData+i);
    }
    MFRC522_CalculateCRC(buff, 16, &buff[16]);
    status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);

    if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
    {
      status = MI_ERR;
    }
  }

  return status;
}
/*
 * Function Name: MFRC522_Halt
 * Description: Command card into hibernation
 * Input: None
 * Return value: None
 */
void MFRC522_Halt(void)
{
  unsigned char status;
  unsigned int unLen;
  unsigned char buff[4];

  buff[0] = PICC_HALT;
  buff[1] = 0;
  MFRC522_CalculateCRC(buff, 2, &buff[2]);

  status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff,&unLen);
}

void MFRC522_StopCrypto1(void)
{
MFRC522_ClearBitMask(Status2Reg, 0x08);
}
