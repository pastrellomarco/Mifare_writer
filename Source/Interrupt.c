
#include <p24FJ256GB106.h>
#include "..\Header\HardwareProfile.h"
#include "..\Header\main.h"
#include "..\Header\Variabili.h"


long tick_cpu;

 /****************************** INTERRUPT TIMER1 *************************/


void __attribute__ ((interrupt, no_auto_psv)) _T4Interrupt(void) 
{ 
IFS1bits.T4IF = 0; 										// entra dentro ogni 10 ~ ms 

	tick_cpu++;

/////////////////////// OPERAZIONI GESTITE OGNI 1 decimo di secondo /////////////////////////
			
	if (++Timer_temp4_decimi >= TIMER4_DECIMI)			// OPERAZIONI GESTITE OGNI 100 millisecondi
	{
		Timer_temp4_decimi = 0;							// ogni 100 ms ~
	
		if(timer_LED_ROSSO)									// Se è stato inizializzzato il Timer ed Acceso il LED_RXUSB
		{
			--timer_LED_ROSSO;								// decremento il timer
			if (!timer_LED_ROSSO)							// se è arrivato a ZERO
				LED_R=0;									// Spengo il LED_VERDE
		}
	
	
		if (++timer_LED_CPU == TIMER_CPU)					
		{
			timer_LED_CPU = 0;
			LED_CPU ^= 1;						
		}
	
		if (++poll_timer_mifare == TEMPO_POLLING_MIFARE)				// Incremento contatore per polling su Card Mifare e se questo risulta più grande di 2 volte quello dello ZIP
		{
			poll_timer_mifare = 0;									// allora ripristino il timer a  ZERO per l'intertempo di lettura					
			Flag_leggi_mifare = 1;											// impongo di leggere la card mifare
		}
	
	}
	
/////////////////////// OPERAZIONI GESTITE OGNI 1 secondo /////////////////////////

	if (++Timer_temp4_secondi>=TIMER4_SECONDI)			
	{
		Timer_temp4_secondi=0;											// ogni 1000 ms ~
	//	Flag_CheckPSC = 1;
	}
	
TMR4 = 0;
}


long tick_elapsed(long tickUser)
{
return (tick_cpu - tickUser);
}

long tick_current(void)
{
	return tick_cpu;
}
