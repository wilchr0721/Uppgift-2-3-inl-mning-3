/*
 * led.h
 *
 * Created: 2022-12-06 18:28:46
 *  Author: willi
 */ 


#ifndef LED_H_
#define LED_H_

#include "misc.h"

struct led
{
	uint8_t pin;
	enum io_port io_port_led;
	bool enabled;
};

/********************************************************************************
* led_init: initierar en led strukt f�r andv�dning p� port B eller D
			 och s�tter porten som en utg�ng. 
*
*           - struct led* self: led strukt pekare f�r en led koplad till arduinon.
*           - const uint8_t pin: anger vilken pin som skall tilldelas led strukten.
********************************************************************************/
void led_init(struct led* self,const uint8_t pin);

/********************************************************************************
* led_on: t�nder ledden p� uttg�ngen som skikas.
*
*           - struct led* self: led strukt pekare f�r en led koplad till arduinon.
********************************************************************************/
void led_on(struct led* self);

/********************************************************************************
* led_off: sl�cker ledden p� uttg�ngen som skikas.
*
*           - struct led* self: led strukt pekare f�r en led koplad till arduinon.
********************************************************************************/
void led_off(struct led* self);

/********************************************************************************
* led_toggle: t�nder eller sl�cker en led beroende p� des tidiggare tillst�nd.
*
*           - struct led* self: led strukt pekare f�r en led koplad till arduinon.
********************************************************************************/
void led_toggle(struct led* self);



#endif /* LED_H_ */