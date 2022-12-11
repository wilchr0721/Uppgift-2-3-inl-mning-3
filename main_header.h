/*
 * IncFile1.h
 *
 * Created: 2022-12-09 11:58:48
 *  Author: willi
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

/**********************************************************************

	*main.header.h: includerar headers för samtliga funtioner som finns tillgängliga för användning.
	
**********************************************************************/

#include "misc.h"
#include "led.h"
#include "led_vect.h"
#include "button.h"

extern struct led l1,l2,l3;
extern struct button b1;
extern struct led_vect v1;

void setup(void);


#endif /* INCFILE1_H_ */