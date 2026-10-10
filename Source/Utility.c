
#include "..\Header\Variabili.h"
#include "..\Header\compiler.h"
#include "..\Header\HardwareProfile.h"

#include <libpic30.h> 

//extern unsigned int Numero_Intermittenze;
//extern unsigned char Attivazione_intermittenza;
//extern unsigned int	timer_BUZZER_intermittenza;
//extern unsigned int	timer_BUZZER_On;
//extern unsigned int	timer_BUZZER_Off;

//void __delay_us(unsigned int time); 
//void __delay_ms(unsigned int time); 
//


/******************************************************************
*
*					AttivazioneIntermittenze
*
*	unsigned char TempoON	=	Tempo di accensione del timer
*	unsigned char TempoOff 	=	tempo di spegnemtno del Timer
*	unsigned char Numero 	=	numero di intermittenze
*******************************************************************/

//void AttivazioneIntermittenze(unsigned int TempoON,unsigned int TempoOff,unsigned int Numero)
//{
//Attivazione_intermittenza=1;					// Ativazione Ciclo Intermittenza Buzzer
//timer_BUZZER_On=TempoON;						// Tempo da Caricare per l'accensione del Buzzer
//timer_BUZZER_Off=TempoOff;						// Tempo da Caricare per lo spegnimento del Buzzer
//Numero_Intermittenze=(Numero+1);					// Numero di intermittenze (numero di beep) da effettuare
//timer_BUZZER_intermittenza=5;					// Impostato per default il tempo del tiemr da caricare in partenza
//}


/******************************************************************
*
*					bcd2hex(num)
*		PERMETTE DI CONVERTIRE DA DECIMALE IN ESADECIMALE
*******************************************************************/


unsigned char bcd2hex(unsigned char num)
{
    return(((num >> 4) & 0x0F) * 10 + (num & 0x0F));
}

/******************************************************************
*
*					hex2bcd(num)
*		PERMETTE DI CONVERTIRE DA ESADECIMALE IN DECIMALE
*******************************************************************/
unsigned char hex2bcd(unsigned char num)
{
    return((((num / 10) << 4) + (num % 10)) & 0xFF);
}


char xtod(char c)
{
if (c>='0' && c<='9') return c-'0';
if (c>='A' && c<='F') return c-'A'+10;
if (c>='a' && c<='f') return c-'a'+10;
return c=0; // not Hex digit
}
  
unsigned int HextoDec(char *hex)
{
	if (*hex==0)
		return 0;
		
	return (HextoDec(hex-1)*16 + xtod(*hex));
}

unsigned int xstrtoi(unsigned char *hex)  // hex string to integer
{
return (HextoDec(hex + strlen(hex)-1));
}
/******************************************************************
*
*	char *u16toa (unsigned int value, char *pBuffer, unsigned char radix,unsigned char GrandezzaNumero )
*
*		PERMETTE DI CONVERTIRE un intero in caratteri 

*
*	unsigned int value 		= Valore da convertire
*	char *pBuffer 			= Buffer su cui salvare i dati
*	unsigned char radix		= base su cui convertire il valore ( 2 - 10 - 16)
*	return = N° di cifre convertite
*******************************************************************/
unsigned char u16toa (unsigned int value,char *pBuffer, unsigned char radix)
{
unsigned char digit;
unsigned char GrandezzaNumero; 

//if (value<10000)						// se il paarametro da elaborare ha valore è inferiore a 100
	GrandezzaNumero=5;										// 3 cifre da convertire
if (value<10000)						// se il paarametro da elaborare ha valore è inferiore a 100
	GrandezzaNumero=4;										// 2 cifre da convertire
if (value<1000)						// se il paarametro da elaborare ha valore è inferiore a 10
	GrandezzaNumero=3;										// 1 cifra da convertire
if (value<100)							// se il paarametro da elaborare ha valore è inferiore a 100
	GrandezzaNumero=2;										// 2 cifre da convertire
if (value<10)							// se il paarametro da elaborare ha valore è inferiore a 10
	GrandezzaNumero=1;

pBuffer += GrandezzaNumero+1;
*--pBuffer = '\0';
  
do
	{
	digit = value % radix;
	*--pBuffer = '0' + digit + ((digit > 9) ? 7 : 0);
	}
while ((value /= radix) != 0);

return GrandezzaNumero;
}
 
///******************************************************************
//*
//*			void ConvertIPtoString(unsigned char *buffer_Mittente)
//*		PERMETTE DI CONVERTIRE l'IP da formato numerico (contenuto nel buffer) a stringa
//*		durante la programamzione dell'antenna: vengono converti i 4 byte ed inseriti i punti di separazione
//*		il risultato viene spostato sul buffer_IP
//*******************************************************************/
//unsigned char ConvertIPtoString(unsigned char *buffer_daElaborare)
//{
//unsigned char cnt_char=0;
//
//for (z=0;z<4;z++)   											// tramite un ciclo for 
//	My_IpTemp[z]=*buffer_daElaborare++;							// ricopio nel buffer temporaneo il buffer da elaborare
//
//for (z=0;z<20;z++)   											// tramite un ciclo for 
//	buffer_IPConverted[z]=0;
//
//for (x=0;x<4;x++)												// tramite un ciclo for elaboro la conversione della stringa
//	{
//	b=u16toa (My_IpTemp[x], buffer_temp, 10);		// eseguo conversione nuemri in caratteri
//
////	if (b==1)
////		{	
////		buffer_IPConverted[cnt_char]=buffer_temp[0];			// ricopio la prima cifra
////		buffer_IPConverted[b+cnt_char]='.';						// Aggiungo Punto
////		}
////	if (b==2)
////		{	
////		buffer_IPConverted[cnt_char]=buffer_temp[0];			// ricopio la prima cifra
////		buffer_IPConverted[1+cnt_char]=buffer_temp[1];			// ricopio la seconda cifra
////		buffer_IPConverted[b+cnt_char]='.';						// Aggiungo Punto
////		}
////	if (b==3)
////		{	
////		buffer_IPConverted[cnt_char]=buffer_temp[0];			// ricopio la prima cifra
////		buffer_IPConverted[1+cnt_char]=buffer_temp[1];			// ricopio la seconda cifra
////		buffer_IPConverted[2+cnt_char]=buffer_temp[2];			// ricopio la seconda cifra
////		buffer_IPConverted[b+cnt_char]='.';						// Aggiungo Punto
////		}
//
//	buffer_IPConverted[cnt_char]=buffer_temp[0];			// ricopio la prima cifra
//
//	if (b==2)
//		buffer_IPConverted[1+cnt_char]=buffer_temp[1];			// ricopio la seconda cifra
//
//	if (b==3)
//		{
//		buffer_IPConverted[1+cnt_char]=buffer_temp[1];			// ricopio la seconda cifra
//		buffer_IPConverted[2+cnt_char]=buffer_temp[2];			// ricopio la seconda cifra
//		}
//	buffer_IPConverted[b+cnt_char]='.';						// Aggiungo Punto
//
//	cnt_char=cnt_char+b+1;										// aggiungo il nuemro dei cartteri utilizzati per aggiungere correttametne nella stringa gli altri numeri
//	}
//buffer_IPConverted[cnt_char-1]= 0x00;
//return cnt_char;			// ritono l quantittà di cifre convertite
//
//}
/******************************************************************
*
*					hex2bcd(num)
*		PERMETTE DI CONVERTIRE il contneuto del buffer passatogli in un intero decimale o Esadecimale
*	
*	unsigned char *BufferdaConvertire = Buffer da Convertire
*	unsigned char NumeroValori = ordine di grandezza del numero (10 * NumeroValori)
*	unsigedn char TipoConversione = 0= Decimale, 1 = Esadecimale
*******************************************************************/
unsigned int ConvertiToIntero(char *BufferdaConvertire, unsigned char NumeroValori, unsigned char TipoConversione)
{
unsigned int kk = 0;	
	
if (!TipoConversione)
	{
	switch (NumeroValori)
		{
		case 1:
			kk = BufferdaConvertire[0];
		break;
	
		case 2:
			{
			kk = (BufferdaConvertire[0] * 10);
			kk += BufferdaConvertire[1];
			}
		break;
	
		case 3:
			{
			kk = (BufferdaConvertire[0] * 100);
			kk += (BufferdaConvertire[1] * 10);
			kk += BufferdaConvertire[2];
			}
		break;
	
		case 4:
			{
			kk = (BufferdaConvertire[0] * 1000);
			kk += (BufferdaConvertire[1] * 100);
			kk += (BufferdaConvertire[2] * 10);
			kk += BufferdaConvertire[3];
			}
		break;
	
		case 5:
			{
			kk = (BufferdaConvertire[0] * 10000);
			kk += (BufferdaConvertire[1] * 1000);
			kk += (BufferdaConvertire[2] * 100);
			kk += (BufferdaConvertire[3] * 10);
			kk += BufferdaConvertire[4];
			}
		break;
		}	// fine switch
	}
else
	{
	switch (NumeroValori)
		{
		case 1:
			kk = BufferdaConvertire[0];
		break;
		
		case 2:
			{
			kk = (BufferdaConvertire[0] * 16);
			kk += BufferdaConvertire[1];
			}
		break;
		
		case 3:
			{
			kk = (BufferdaConvertire[0] * 256);
			kk += (BufferdaConvertire[1] * 16);
			kk += BufferdaConvertire[2];
			}
		break;
	
		case 4:
			{
			kk = (BufferdaConvertire[0] * 4096);
			kk += (BufferdaConvertire[1] * 256);
			kk += (BufferdaConvertire[2] * 16);
			kk += BufferdaConvertire[3];
			}
		break;
		}	// fine switch
	} // fine else


return kk;
}



//
//void delay_us(unsigned char sleep_us)
//{
//    do
//    {
//        Nop(); //6 nop per 1us
//        Nop();
//        Nop();
//        Nop();
//        Nop();
//        Nop();
//
//        Nop(); //6 nop per 1us
//        Nop();
//        Nop();
//        Nop();
//        Nop();
//        Nop();
//
//        Nop(); //6 nop per 1us
//        Nop();
//        Nop();
//        Nop();
//        Nop();
//        Nop();
//// ----
//
//    }
//    while (--sleep_us);		// 4nop 
//}
//
//void delayM_ms(unsigned int sleep_ms)
//{
//unsigned int count;
//
//	do
//	{
//	count=3000;   						// clock pic  USB @16MHz(32MHzdiv2)
//	while (--count);				
//	}
//while (--sleep_ms);				
//}

void delay_ms(unsigned int sleep_ms)
{
	__delay_ms(sleep_ms);
}

void delay_us(unsigned int sleep_us)
{
	__delay_us(sleep_us);
}

