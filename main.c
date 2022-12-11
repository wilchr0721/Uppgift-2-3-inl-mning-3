/*
 * Uppgift_3.c
 *
 * Created: 2022-12-06 12:56:01
 * Author : willi
 */ 
/**********************************************************************

	mian_header.h includerar samtliga headers för alla includerade funtioner.
	
**********************************************************************/
#include "main_header.h"


static  uint16_t blink_speed_ms; /*blink hastighet i milesecunder*/
static bool led_enabeld;		 /*varabel som bestämmer om leds skall blinka eller inte*/
static bool direktion;			 /*anger vilken riktning som dioderna skall blinka*/
static uint8_t counter;          /*räknar antal gånger dioderna har varit tända*/

/**********************************************************************

	ISR (PCINT0_vect): avbrytter vid intryckning av trycknappen ansluten till pin 13.
					   led_enabel togglas.
					   om leds blinkar så släcks dom och räknaren ökar med 1.
	
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
		   leds framåt och backåt vid intryckning av trycknappen ansluten till pin 13. 
		   När ledsen har tänds och släckts 5 gånger så ändrar blinkningen ricktning.
		   
		   -blink_speed_ms: anger hastigheten på blinkningen.
		   
		   -counter:  räknar hur många gånger som dioderna har tändits och släckts i en ricktning
				      nollstäls när dioden dioderna tänds och släckts 5 gånger.
		   
		   -led_enabeld: när dena varabel är true så blinkar dioderna.
		   
		   -direktion: anger i vilken ricktging som dioderna blinkar.
					   vid true så blinkar dom från högsta pin till lägsta.
					   vis false så blinkar dom från lägsta till högsta.
		   
	
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

