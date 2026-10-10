
/************************ HEADERS **********************************/
#include "..\Header\Compiler.h"
#include "..\Header\GenericTypeDefs.h"
#include "..\Header\Variabili.h"
#include "..\Header\main.h"
#include "..\Header\HardwareProfile.h"

//extern void init_rf530(void);
//extern char PcdRfReset(unsigned char ms);								// reset campo RF

/*********************************************************************
* 
*						void SPIPut2(BYTE v)
*
*			Gestisce la scrittura sul Chip Mifare FM1722
********************************************************************/

void SPIPut1(unsigned char DataToWrite1)
{



#if !defined(SPI_HW)
unsigned char ss;

	SPI_SDO1 = 0;
	SPI_SCK1 = 0;
	
	for(ss = 0; ss < 8; ss++)
		{
		SPI_SDO1 = (DataToWrite1 >> (7-ss));      
		SPI_SCK1 = 1;
		SPI_SCK1 = 0;  
		}  
	SPI_SDO1 = 0; 
#else
unsigned char temp_spi;

	IFS0bits.SPI1IF = 0;
	temp_spi = SPI1BUF;
	SPI1BUF = DataToWrite1;
//	delay_us(10);
	while(IFS0bits.SPI1IF == 0){}
#endif
}

/*********************************************************************
*        
*						 BYTE SPIGet(void)
*
*			Permette la lettura dei dati dal chip mifare FM1722
********************************************************************/

BYTE SPIGet1(void)
{
#if !defined(SPI_HW)
	BYTE i;
	BYTE spidata = 0;
	
	SPI_SDO1 = 0;
	SPI_SCK1 = 0;
	
	for(i = 0; i < 8; i++)
		{
		spidata = (spidata << 1) | SPI_SDI1;  
		SPI_SCK1 = 1;
		SPI_SCK1 = 0; 
		}
	return spidata;
#else 
//	tmp3=SPI1BUF;
	SPIPut1(0x00);
	return SPI1BUF;
#endif
}
