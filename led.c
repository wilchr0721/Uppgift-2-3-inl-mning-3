/*
 * led.c
 *
 * Created: 2022-12-06 18:28:23
 *  Author: willi
 */ 

/********************************************************************************
* led.c: Inneh�ller funtioner f�r t�ndning och sl�ckning av leds.
********************************************************************************/
#include "led.h"

/********************************************************************************
* led_init: initierar en led strukt f�r andv�dning p� port B eller D
			 och s�tter porten som en utg�ng. 
*
*           - self: led pekare f�r en led koplad till arduinon.
*           - pin: anger vilken pin som skall tilldelas led strukten.
********************************************************************************/
void led_init(struct led* self,const uint8_t pin){
	
	if (pin >= 0 && pin <= 7){

		self->io_port_led = IO_PORTD;
		self->pin = pin;
		DDRD |= ( 1 << pin);
		self->enabled = false;
	}
	
	else if(pin >= 8 && pin <= 13 ){
		self->pin = pin-8;
		self->io_port_led = IO_PORTB;
		DDRB |= ( 1 << (pin-8));
		self->enabled = false;
	}
	return;
}

/********************************************************************************
* led_on: t�nder ledden p� uttg�ngen som skikas.
*
*           - struct led* self: led strukt pekare f�r en led koplad till arduinon.
********************************************************************************/
void led_on(struct led* self){
	if (self->io_port_led == IO_PORTB){
		PORTB |= ( 1 << (self->pin));
		self->enabled=true;
	}
	else if (self->io_port_led == IO_PORTD){
		PORTD  |= ( 1 << (self->pin));
		self->enabled=true;
	}
	return;
}

/********************************************************************************
* led_toggle: t�nder eller sl�cker en led beroende p� des tidiggare tillst�nd.
*
*           - struct led* self: led strukt pekare f�r en led koplad till arduinon.
********************************************************************************/
void led_toggle(struct led* self){
	if (self->enabled == true)
	{
		led_off(self);
		self->enabled = false;
		return;
	}
	else if(self->enabled == false)
	{
		led_on(self);
		self->enabled = true;
		return;
	}
	return;
}

/********************************************************************************
* led_off: sl�cker ledden p� uttg�ngen som skikas.
*
*           - struct led* self: led strukt pekare f�r en led koplad till arduinon.
********************************************************************************/
void led_off(struct led* self){
	if (self->io_port_led == IO_PORTB){
		PORTB &= ~( 1 << (self->pin));
		self->enabled = false;
	}
	else if (self->io_port_led == IO_PORTD){
		PORTD  &= ~( 1 << (self->pin));
		self->enabled = false;
	}
}