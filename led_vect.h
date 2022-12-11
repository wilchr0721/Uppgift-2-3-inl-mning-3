/*
 * led_vect.h
 *
 * Created: 2022-12-06 18:31:48
 *  Author: willi
 */ 

/********************************************************************************
* led_vect.h: Inneh�ller funktionalitet f�r implementering av dynamiska
*               vektorer f�r lagring och styrning �ver multipla lysdioder eller
*               andra utportar, realiserat via strukten led_vect samt
*               associerade funktioner.
********************************************************************************/

#ifndef LED_VECT_H_
#define LED_VECT_H_

/* Inkluderingsdirektiv: */

#include "led.h"
#include "misc.h"
#include "main_header.h"

/********************************************************************************
* led_vect: Dynamisk vektor f�r lagring och styrning av led-objekt, vilket
*             kan utg�ras av lysdioder eller andra digitala utportar.
********************************************************************************/

struct led_vect {
	struct led* leds;	/* Pekare till array inneh�llande led-objekt. */
	size_t size;		/* Vektorns storlek, dvs. antalet befintliga led-objekt. */
};


/********************************************************************************
* led_vect_init: Initierar angiven vektor till tom vid start.
*
*                - self: Pekare till vektorn som ska initieras.
********************************************************************************/
void led_vect_init(struct led_vect* self);

/********************************************************************************
* led_vect_push: L�gger till ett nytt led-objekt l�ngst bak i angiven vektor.
*                Vid misslyckad minnesallokering returneras felkod 1.
*                Annars om push-operationen lyckas returneras 0.
*
*                - self*   : Pekare till vektorn som ska tilldelas.
*                - led_ptr*: Det nya led-objekt som ska l�ggas till.
********************************************************************************/
void led_vect_push(struct led_vect* self, struct led* led_ptr);

/********************************************************************************
* led_vect_pop: Tar bort eventuellt sista led-objekt i angiven vektor genom
*               att minska dess storlek med ett. Vid misslyckad omallokering
*               returneras felkod 1, annars 0.
*
*               - self: Pekare till vektorn vars sista element ska tas bort.
********************************************************************************/
void led_vect_pop(struct led_vect* self);

/********************************************************************************
* led_vect_clear:T�mmer och nollst�ller angiven vektor.
*
*                - self: Pekare till vektorn som ska t�mmas.
********************************************************************************/
void led_vect_clear(struct led_vect* self);

/********************************************************************************
* led_vect_on: T�nder samtliga lysdioder lagrade i angiven vektor.
*
*              - self: Pekare till vektorn vars lysdioder ska t�ndas.
********************************************************************************/
void led_vect_on(struct led_vect* self);

/********************************************************************************
* led_vect_off: sl�cker samtliga lysdioder lagrade i angiven vektor.
*
*              - self: Pekare till vektorn vars lysdioder ska sl�ckas.
********************************************************************************/
void led_vect_off(struct led_vect* self);

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
void led_vect_blink_sequentally(struct led_vect* self, uint16_t time_delay);

/********************************************************************************
* led_vect_blink_collectively: Genomf�r kollektiv (synkroniserad) blinkning
*                              av samtliga lysdioder lagrade i angiven vektor.
*
*                              - self      : Pekare till vektorn vars
*                                                lysdioder ska blinkas.
*                              - time_delay: Lysdiodernas blinkhastighet
*                                            m�tt i millisekunder.
********************************************************************************/
void led_vect_blink_collectively(struct led_vect* self, uint16_t time_delay);

/********************************************************************************
* led_vect_toggle: Togglar samtliga lysdioder lagrade i angiven vektor.
*
*                  - self: Pekare till vektorn vars lysdioder ska togglas.
********************************************************************************/
void led_vect_toggle(struct led_vect* self);

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
void led_vect_blink_sequentally_forard_back(struct led_vect* self, uint16_t* time_delay,bool direktion);

#endif /* LED_VECT_H_ */