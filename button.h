/*
 * button.h
 *
 * Created: 2022-12-09 11:54:08
 *  Author: willi
 */ 

/********************************************************************************
* button.h: Inneh�ller funktionalitet f�r enkel implementering av tryckknappar
*           via strukten button samt associerade funktioner. Denna strukt
*           fungerar ocks� utm�rkt f�r andra digitala inportar d�r insignalen
*           ska kunna l�sas av samt avbrott ska kunna genereras vid ett
*           godtyckligt event.
********************************************************************************/

#ifndef BUTTON_H_
#define BUTTON_H_

/* Inkluderingsdirektiv: */
#include "misc.h"

/********************************************************************************
* button: Strukt f�r implementering av tryckknappar och andra digitala inportar.
*    
********************************************************************************/

struct button
{
	uint8_t pin;					/* Tryckknappens pin-nummer p� aktuell I/O-port. */
	enum io_port io_port_button;	/* I/O-port som lysdioden �r ansluten till. */
};


/********************************************************************************
* button_init: Initierar ny tryckknapp p� angiven pin.
*
*              - self: Pekare till tryckknappen som ska initieras.
*              - pin : Tryckknappens pin-nummer p� Arduino Uno, exempelvis 13.
*                      Alternativt kan motsvarande port-nummer p� ATmega328P
*                      anges, exempelvis B5 f�r pin 13 eller D3 f�r pin 3.
********************************************************************************/
void button_init(struct button* self, uint8_t pin);

/********************************************************************************
* button_is_pressed: L�ser av tryckknappens pin och indikerar ifall denna �r
*                    nedtryckt. I s� fall returneras true, annars false.
*
*                    - self: Pekare till tryckknappen som ska l�sas av.
********************************************************************************/
bool button_is_pressed(struct button* self);

/********************************************************************************
* button_clear: Nollst�ller tryckknapp samt motsvarande pin.
*
*               - self: Pekare till tryckknappen som ska nollst�llas.
********************************************************************************/
void button_clear(struct button* self);

/********************************************************************************
* button_aktivate_interrupt: Aktiverar PCI-avbrott p� angiven tryckknapp s� att
*							event p� tryckknappens pin medf�r avbrott, b�de p�
*							stigande och fallande flank. Kontroll av flank m�ste
*							sk�tas av anv�ndaren, f�rslagsvis via avl�sning i
*							motsvarande avbrottsrutin.
*
*							Nedan visas sambandet mellan anv�nd I/O-port samt
*							avbrottsvektorn f�r motsvarande avbrottsrutin:
*
*							I/O-port     pin (Arduino Uno)     Avbrottsvektor
*                             B              8 - 13             PCINT0_vect
*                             C             A0 - A5             PCINT1_vect
*                             D              0 - 7              PCINT2_vect
*
*                          - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska aktiveras p�.
********************************************************************************/
void button_aktivate_interupts(struct button* self);


#endif /* BUTTON_H_ */