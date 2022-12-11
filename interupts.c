/*
 * interupts.c
 *
 * Created: 2022-12-09 11:56:32
 *  Author: willi
 */ 

#include "led.h"
#include "misc.h"
#include "button.h"

/********************************************************************************
* button_aktivate_interrupt: Aktiverar PCI-avbrott på angiven tryckknapp så att
*                          event på tryckknappens pin medför avbrott, både på
*                          stigande och fallande flank. Kontroll av flank måste
*                          skötas av användaren, förslagsvis via avläsning i
*                          motsvarande avbrottsrutin.
*
*                          Nedan visas sambandet mellan använd I/O-port samt
*                          avbrottsvektorn för motsvarande avbrottsrutin:
*
*                          I/O-port     pin (Arduino Uno)     Avbrottsvektor
*                             B              8 - 13             PCINT0_vect
*                             C             A0 - A5             PCINT1_vect
*                             D              0 - 7              PCINT2_vect
*
*                          - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska aktiveras på.
********************************************************************************/

void button_aktivate_interupts(struct button* self){
	asm("SEI");
	if (self->io_port_button == IO_PORTB)
	{
		PCMSK0 |= (1 << self->pin);
		PCICR |= (1 << PCIE0);
	}
	else if (self->io_port_button == IO_PORTC)
	{
		PCMSK1 |= (1 << self->pin);
		PCICR |= (1 << PCIE1);
	}
	else if (self->io_port_button == IO_PORTD)
	{
		PCMSK2 |= (1 << self->pin);
		PCICR |= (1 << PCIE2);
	}
	return;
}


