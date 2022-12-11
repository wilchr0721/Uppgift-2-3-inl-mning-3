/*
 * button.c
 *
 * Created: 2022-12-09 11:54:26
 *  Author: willi
 */ 

/********************************************************************************
* button.h: Inneh�ller funktionsdefinitioner f�r enkel implementering av
*           tryckknappar samt andra digitala inportar via strukten button.
********************************************************************************/
#include "button.h"

/********************************************************************************
* button_init: Initierar ny tryckknapp p� angiven pin.
*
*              - self: Pekare till tryckknappen som ska initieras.
*              - pin : Tryckknappens pin-nummer p� Arduino Uno, exempelvis 13.
*                      Alternativt kan motsvarande port-nummer p� ATmega328P
*                      anges, exempelvis B5 f�r pin 13 eller D3 f�r pin 3.
********************************************************************************/
void button_init(struct button* self, uint8_t pin){
	if (pin >= 0  && pin <= 7)
	{
		self->io_port_button = IO_PORTD;
		self->pin = pin;
		PORTD |= (1 << pin);
	}
	else if (pin >= 8 && pin <= 13)
	{
		self->io_port_button = IO_PORTB;
		self->pin = pin-8;
		PORTB |= (1 << (pin-8));
	}
	return;
}

/********************************************************************************
* button_clear: Nollst�ller tryckknapp samt motsvarande pin.
*
*               - self: Pekare till tryckknappen som ska nollst�llas.
********************************************************************************/
void button_clear(struct button* self)
{

	if (self->io_port_button == IO_PORTB)
	{
		PORTB &= ~(1 << self->pin);
	}
	else if (self->io_port_button == IO_PORTC)
	{
		PORTC &= ~(1 << self->pin);
	}
	else if (self->io_port_button == IO_PORTD)
	{
		PORTD &= ~(1 << self->pin);
	}

	self->io_port_button = IO_PORT_NONE;
	self->pin = 0;
	return;
}

/********************************************************************************
* button_is_pressed: L�ser av tryckknappens pin och indikerar ifall denna �r
*                    nedtryckt. I s� fall returneras true, annars false.
*
*                    - self: Pekare till tryckknappen som ska l�sas av.
********************************************************************************/
bool button_is_pressed(struct button* self){
	if (self->io_port_button == IO_PORTB)
	{
		return (PINB & (1 << (self->pin)));
	}
	else if (self->io_port_button == IO_PORTD)
	{
		return (PIND & (1 << (self->pin)));
	}
	else if (self->io_port_button == IO_PORTC)
	{
		return (PINC & (1 << (self->pin)));
	}
	else{return false; }
	
}
