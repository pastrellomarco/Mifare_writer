/*
* To read and write from MIFARE PICCs, the MIFARE protocol is used after the PICC has been selected.
* The MIFARE Classic chips and protocol is described in the datasheets:
* 1K: http://www.nxp.com/documents/data_sheet/MF1S503x.pdf
* 4K: http://www.nxp.com/documents/data_sheet/MF1S703x.pdf
* Mini: http://www.idcardmarket.com/download/mifare_S20_datasheet.pdf
* The MIFARE Ultralight chip and protocol is described in the datasheets:
* Ultralight: http://www.nxp.com/documents/data_sheet/MF0ICU1.pdf
* Ultralight C: http://www.nxp.com/documents/short_data_sheet/MF0ICU2_SDS.pdf
*
* MIFARE Classic 1K (MF1S503x):
* Has 16 sectors * 4 blocks/sector * 16 bytes/block = 1024 bytes.
* The blocks are numbered 0-63.
* Block 3 in each sector is the Sector Trailer. See http://www.nxp.com/documents/data_sheet/MF1S503x.pdf sections 8.6 and 8.7:
* Bytes 0-5: Key A
* Bytes 6-8: Access Bits
* Bytes 9: User data
* Bytes 10-15: Key B (or user data)
* Block 0 is read only manufacturer data.
* To access a block, an authentication using a key from the block's sector must be performed first.
* Example: To read from block 10, first authenticate using a key from sector 3 (blocks 8-11).
* All keys are set to FFFFFFFFFFFFh at chip delivery.
* Warning: Please read section 8.7 "Memory Access". It includes this text: if the PICC detects a format violation the whole sector is irreversibly blocked.
* To use a block in "value block" mode (for Increment/Decrement operations) you need to change the sector trailer. Use PICC_SetAccessBits() to calculate the bit patterns.
* MIFARE Classic 4K (MF1S703x):
* Has (32 sectors * 4 blocks/sector + 8 sectors * 16 blocks/sector) * 16 bytes/block = 4096 bytes.
* The blocks are numbered 0-255.
* The last block in each sector is the Sector Trailer like above.
* MIFARE Classic Mini (MF1 IC S20):
* Has 5 sectors * 4 blocks/sector * 16 bytes/block = 320 bytes.
* The blocks are numbered 0-19.
* The last block in each sector is the Sector Trailer like above.
*
* MIFARE Ultralight (MF0ICU1):
* Has 16 pages of 4 bytes = 64 bytes.
* Pages 0 + 1 is used for the 7-byte UID.
* Page 2 contains the last chech digit for the UID, one byte manufacturer internal data, and the lock bytes (see http://www.nxp.com/documents/data_sheet/MF0ICU1.pdf section 8.5.2)
* Page 3 is OTP, One Time Programmable bits. Once set to 1 they cannot revert to 0.
* Pages 4-15 are read/write unless blocked by the lock bytes in page 2.
* MIFARE Ultralight C (MF0ICU2):
* Has 48 pages of 4 bytes = 64 bytes.
* Pages 0 + 1 is used for the 7-byte UID.
* Page 2 contains the last chech digit for the UID, one byte manufacturer internal data, and the lock bytes (see http://www.nxp.com/documents/data_sheet/MF0ICU1.pdf section 8.5.2)
* Page 3 is OTP, One Time Programmable bits. Once set to 1 they cannot revert to 0.
* Pages 4-39 are read/write unless blocked by the lock bytes in page 2.
* Page 40 Lock bytes
* Page 41 16 bit one way counter
* Pages 42-43 Authentication configuration
* Pages 44-47 Authentication key
*/

//Maximum length of the array
#define MAX_LEN 16

/////////////////////////////////////////////////////////////////////
//set the pin
/////////////////////////////////////////////////////////////////////

//MF522 Command word
#define PCD_IDLE              0x00               //NO action; Cancel the current command
#define PCD_AUTHENT           0x0E               //Authentication Key
#define PCD_RECEIVE           0x08               //Receive Data
#define PCD_TRANSMIT          0x04               //Transmit data
#define PCD_TRANSCEIVE        0x0C               //Transmit and receive data,
#define PCD_RESETPHASE        0x0F               //Reset
#define PCD_CALCCRC           0x03               //CRC Calculate

// Mifare_One card command word
#define PICC_REQIDL          0x26               // find the antenna area does not enter hibernation
#define PICC_REQALL          0x52               // find all the cards antenna area
#define PICC_ANTICOLL        0x93               // anti-collision
#define PICC_SElECTTAG       0x93               // election card
#define PICC_AUTHENT1A       0x60               // authentication key A
#define PICC_AUTHENT1B       0x61               // authentication key B
#define PICC_READ            0x30               // Read Block
#define PICC_WRITE           0xA0               // write block
#define PICC_DECREMENT       0xC0               // debit
#define PICC_INCREMENT       0xC1               // recharge
#define PICC_RESTORE         0xC2               // transfer block data to the buffer
#define PICC_TRANSFER        0xB0               // save the data in the buffer
#define PICC_HALT            0x50               // Sleep

//And MF522 The error code is returned when communication
#define MI_OK                 0
#define MI_NOTAGERR           1
#define MI_ERR                2

//------------------MFRC522 Register---------------
//Page 0:Command and Status
#define     Reserved00            0x00
#define     CommandReg            0x01
#define     CommIEnReg            0x02
#define     DivlEnReg             0x03
#define     CommIrqReg            0x04
#define     DivIrqReg             0x05
#define     ErrorReg              0x06
#define     Status1Reg            0x07
#define     Status2Reg            0x08
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     Reserved01            0x0F

//Page 1:Command
#define     Reserved10            0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     Reserved11            0x1A
#define     Reserved12            0x1B
#define     MifareReg             0x1C
#define     Reserved13            0x1D
#define     Reserved14            0x1E
#define     SerialSpeedReg        0x1F

//Page 2:CFG
#define     Reserved20            0x20
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     Reserved21            0x23
#define     ModWidthReg           0x24
#define     Reserved22            0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsPReg              0x28
#define     ModGsPReg             0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F

//Page 3:TestRegister
#define     Reserved30            0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39
#define     TestDAC2Reg           0x3A
#define     TestADCReg            0x3B
#define     Reserved31            0x3C
#define     Reserved32            0x3D
#define     Reserved33            0x3E
#define     Reserved34            0x3F
//-----------------------------------------------

#define KEY_A	0x60		
#define KEY_B	0x61		


/*********************** FUNCTION PROTOTYPEs ****************/

void MFRC522_WriteRegister(unsigned char Address2, unsigned char value2);
unsigned char MFRC522_ReadRegister(unsigned char Address);

void MFRC522_SetBitMask(unsigned char reg, unsigned char mask);
void MFRC522_ClearBitMask(unsigned char reg, unsigned char mask);

void AntennaOn(void);
void AntennaOff(void);

void MFRC522_Reset(void);
void MFRC522_SetTimeOut(unsigned int Tempo);
void MFRC522_Init(void);
unsigned char MFRC522_Request(unsigned char reqMode, unsigned char *TagType);
unsigned char MFRC522_ToCard(unsigned char command, unsigned char *sendData, unsigned char sendLen,unsigned char *backData, unsigned int *backLen);
unsigned char MFRC522_Anticoll(unsigned char *serNum);
void MFRC522_CalculateCRC(unsigned char *pIndata, unsigned char len, unsigned char *pOutData);
unsigned char MFRC522_SelectTag(unsigned char *serNum);
unsigned char MFRC522_Auth(unsigned char authMode, unsigned char BlockAddr, unsigned char *Sectorkey, unsigned char *serNum);
unsigned char MFRC522_Read(unsigned char blockAddr, unsigned char *recvData);
unsigned char MFRC522_Write(unsigned char blockAddr, unsigned char *writeData);
void MFRC522_Halt(void);
void MFRC522_StopCrypto1(void);
