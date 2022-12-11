/*
 * led_vect.c
 *
 * Created: 2022-12-06 18:31:29
 *  Author: willi
 */ 


/********************************************************************************
* led_vect.c: Inneh�ller funktionsdefinitioner f�r implementering av dynamiska
*               vektorer f�r lagring och styrning �ver multipla lysdioder eller
*               andra utportar via strukten led_vect.
********************************************************************************/

#include "led_vect.h"

static void delay_ms_with_break(volatile uint16_t* time_delay);

/********************************************************************************
* led_vect_init: Initierar angiven vektor till tom vid start.
*
*                - self: Pekare till vektorn som ska initieras.
********************************************************************************/
void led_vect_init(struct led_vect* self){
	
	self->leds = 0;
	self->size = 0;
	return;
}

/********************************************************************************
* led_vect_push: L�gger till ett nytt led-objekt l�ngst bak i angiven vektor.
*                Vid misslyckad minnesallokering returneras felkod 1.
*                Annars om push-operationen lyckas returneras 0.
*
*                - self*   : Pekare till vektorn som ska tilldelas.
*                - led_ptr*: Det nya led-objekt som ska l�ggas till.
********************************************************************************/
void led_vect_push(struct led_vect* self, struct led* new_led){
	
	struct led* copy = (struct led*)realloc(self->leds,sizeof(struct led*)*(self->size + 1));
	if(!copy) return;
	copy[self->size++]= *new_led;
	self->leds= copy;
	return;
}

/********************************************************************************
* led_vect_pop: Tar bort eventuellt sista led-objekt i angiven vektor genom
*               att minska dess storlek med ett. Vid misslyckad omallokering
*               returneras felkod 1, annars 0.
*
*               - self: Pekare till vektorn vars sista element ska tas bort.
********************************************************************************/
void led_vect_pop(struct led_vect* self){
	if(self->size <= 1){
		led_vect_clear(self);
		return;
	}
	struct led* copy = (struct led*)realloc(self->leds,sizeof(struct led*)*(self->size - 1));
	if(!copy) return;
	self->leds= copy;
	return;
}

/********************************************************************************
* led_vect_clear:T�mmer och nollst�ller angiven vektor.
*
*                - self: Pekare till vektorn som ska t�mmas.
********************************************************************************/
void led_vect_clear(struct led_vect* self){
	free(self->leds);
	self->size = 0;
	self->leds = 0;
}

/********************************************************************************
* led_vect_on: T�nder samtliga lysdioder lagrade i angiven vektor.
*
*              - self: Pekare till vektorn vars lysdioder ska t�ndas.
********************************************************************************/
void led_vect_on(struct led_vect* self){
	
	for(int i = 0 ; i < self->size ; i++){
		led_on(&self->leds[i]);	
	}
	return;
}


/********************************************************************************
* led_vect_off: sl�cker samtliga lysdioder lagrade i angiven vektor.
*
*              - self: Pekare till vektorn vars lysdioder ska sl�ckas.
********************************************************************************/
void led_vect_off(struct led_vect* self){
	
	for(uint8_t i = 0 ; i < self->size ; i++){
		led_off(&self->leds[i]);
	}
	return;
}

/********************************************************************************
* led_vect_blink_sequentially: Genomf�r sekventiell blinkning av samtliga
*                              lysdioder lagrade i angiven vektor. D�rmed
*                              blinkar lysdioderna i en sekvens en efter en.
*
*                                - self      : Pekare till vektorn vars
*                                              lysdioder ska blinkas.
*                                - time_delay: Lysdiodernas blinkhastighet
*                                              m�tt i millisekunder.
********************************************************************************/
void led_vect_blink_sequentally(struct led_vect* self, uint16_t time_delay){
	
	
	for (uint8_t i = 0; i < self->size; i++){
		led_on(&self->leds[i]);
		delay_ms_with_break(time_delay);
		led_off(&self->leds[i]);
	}
	return;
}

/********************************************************************************
* led_vect_blink_collectively: Genomf�r kollektiv (synkroniserad) blinkning
*                              av samtliga lysdioder lagrade i angiven vektor.
*
*                              - self          : Pekare till vektorn vars
*                                                lysdioder ska blinkas.
*                              - time_delay: Lysdiodernas blinkhastighet
*                                            m�tt i millisekunder.
********************************************************************************/
void led_vect_toggle(struct led_vect* self){
	
	for (uint8_t i = 0; i < self->size; i++){
		led_toggle(&self->leds[i]);
	}
	return;
}

/********************************************************************************
* led_vect_toggle: Togglar samtliga lysdioder lagrade i angiven vektor.
*
*                  - self: Pekare till vektorn vars lysdioder ska togglas.
********************************************************************************/
void led_vect_blink_collectively(struct led_vect* self, uint16_t time_delay){
	
	led_vect_toggle(self);
	delay_ms(time_delay);
	return;
}

/********************************************************************************
*  
*  delay_ms_with_break: k�r en delay p� v�rdet p� time_delay i milesecuneder
						kan vid k�rning avbrytas via interupts.
						
					time_delay: pekare som anger hur stor delayen kan vara.
*
********************************************************************************/
void delay_ms_with_break(volatile uint16_t* time_delay)
{	
	for(uint16_t i = 0 ; i < *time_delay; i++)
	{
		delay_ms(1);
	}
}

/********************************************************************************
*  led_vect_blink_sequentally_forward_or_back: Genomf�r kollektiv (synkroniserad) blinkning
*											   av samtliga lysdioder lagrade i angiven vektor.
*											   blinkar fr�n l�gasta till h�gsta pin vid direktion = false
*											   eller �tt andra h�llet vid direktion = true.
*
*											   - self      : Pekare till vektorn vars
*															 lysdioder ska blinkas.
*											   - time_delay: Lysdiodernas blinkhastighet
*															 m�tt i millisekunder.
*											   - direktion: bool tal som anger vilken ricktning
*															dioderna skall blinka i
********************************************************************************/
void led_vect_blink_sequentally_forard_back(struct led_vect* self, uint16_t* time_delay,bool direktion)
{
	led_vect_off(self);
	if (direktion) 
	{
		for (uint8_t i = 0; i < self->size; i++) 
		{
			led_on(&self->leds[self->size-i-1]);
			delay_ms_with_break(time_delay);
			led_off(&self->leds[self->size-i-1]);
		}
	}
	else 
	{
		for (uint8_t i = 0; i < self->size; i++)
		{
			led_on(&self->leds[i]);
			delay_ms_with_break(time_delay);
			led_off(&self->leds[i]);
		}
	}
	return;
}


