/*
 * misc.c
 *
 * Created: 2022-12-06 18:30:54
 *  Author: willi
 */ 

/********************************************************************************
* misc.c: Inneh�ller diverse funktionsdefinitioner.
********************************************************************************/
#include "misc.h"

/********************************************************************************
* delay_ms: Genererar f�rdr�jning m�tt i millisekunder.
*
*           - delay_time_ms: Angiven f�rdr�jningstid i millisekunder.
********************************************************************************/
void delay_ms( volatile uint16_t delay_time_ms)
{
	for (uint16_t i = 0; i < delay_time_ms; ++i)
	{
		_delay_ms(1);
	}

	return;
}

void delay_us( const uint16_t delay_time_us)
{
	for (uint16_t i = 0; i < delay_time_us; ++i)
	{
		_delay_us(1);
	}

	return;
}