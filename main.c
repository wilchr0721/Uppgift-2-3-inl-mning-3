/*
 * Uppgift_3.c
 *
 * Created: 2022-12-06 12:56:01
 * Author : willi
 */ 
/**********************************************************************

	mian_header.h includerar samtliga headers f�r alla includerade funtioner.
	
**********************************************************************/
#include "main_header.h"


static  uint16_t blink_speed_ms; /*blink hastighet i milesecunder*/
static bool led_enabeld;		 /*varabel som best�mmer om leds skall blinka eller inte*/
static bool direktion;			 /*anger vilken riktning som dioderna skall blinka*/
static uint8_t counter;          /*r�knar antal g�nger dioderna har varit t�nda*/

/**********************************************************************

	ISR (PCINT0_vect): avbrytter vid intryckning av trycknappen ansluten till pin 13.
					   led_enabel togglas.
					   om leds blinkar s� sl�cks dom och r�knaren �kar med 1.
	
**********************************************************************/
ISR (PCINT0_vect){
	if(button_is_pressed(&b1))
	{
		if (led_enabeld == true) 
		{
			blink_speed_ms = 0;
			counter++;
		}
		led_enabeld=!led_enabeld;
	}
}

/**********************************************************************

	*mian: program som blinkar med hastigheten 100 milisekunder som ges av blink_speed_ms
		   leds fram�t och back�t vid intryckning av trycknappen ansluten till pin 13. 
		   N�r ledsen har t�nds och sl�ckts 5 g�nger s� �ndrar blinkningen ricktning.
		   
		   -blink_speed_ms: anger hastigheten p� blinkningen.
		   
		   -counter:  r�knar hur m�nga g�nger som dioderna har t�ndits och sl�ckts i en ricktning
				      nollst�ls n�r dioden dioderna t�nds och sl�ckts 5 g�nger.
		   
		   -led_enabeld: n�r dena varabel �r true s� blinkar dioderna.
		   
		   -direktion: anger i vilken ricktging som dioderna blinkar.
					   vid true s� blinkar dom fr�n h�gsta pin till l�gsta.
					   vis false s� blinkar dom fr�n l�gsta till h�gsta.
		   
	
**********************************************************************/
int main(void)
{
	setup();
	blink_speed_ms= 200;
    counter = 0;
	direktion = false;
	
    
    while (1) 
	{
		if (counter >= 5)
		{
			direktion = !direktion;
			counter = 0;
		}
		if(led_enabeld)
		{
			blink_speed_ms = 200;
			led_vect_blink_sequentally_forard_back(&v1,&blink_speed_ms,direktion);
		}
		
	}
}

