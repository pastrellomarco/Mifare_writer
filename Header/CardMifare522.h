

#define CARD_DEBOUNCE_READ 		5
#define CARD_BLOCK_SIZE 		16
#define CARD_SECTOR_NUMBER 		16

extern unsigned char cntCardStable;
extern unsigned char CardPresent; 
extern unsigned int cardReadType;

extern unsigned char MifareReadBuffer[CARD_BLOCK_SIZE];
extern unsigned char MifareWriteBuffer[CARD_BLOCK_SIZE];


extern unsigned char MFRC522_DiscoverCard(unsigned char *uid_card);
extern unsigned char MFRC522_CheckSectorKey(unsigned char sector, unsigned char authMode, unsigned char *keyToCheck, unsigned char *serNum);
extern unsigned char MFRC522_ChangeSectorKey(unsigned char sector, unsigned char *oldKey, unsigned char *newKeyA, unsigned char *newKeyB);
extern unsigned char MFRC522_ChangeAllKeys(unsigned char *uid, unsigned char StartSector, unsigned char StopSector, unsigned char *oldKey, unsigned char *newKeyA, unsigned char *newKeyB);
extern unsigned char LetturaBloccoMifare(unsigned char Settore,unsigned char BloccoLettura);
extern unsigned char ScritturaBloccoMifare(unsigned char Settore,unsigned char BloccoScrittura);

