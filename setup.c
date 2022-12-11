/*
 * setup.c
 *
 * Created: 2022-12-11 21:03:56
 *  Author: willi
 */ 
#include "main_header.h"

struct led l1,l2,l3;
struct led_vect v1;
struct button b1;

void setup(void){
	
	led_init(&l1,8);
	led_init(&l2,9);
	led_init(&l3,10);
	
	button_init(&b1,13);
	
	led_vect_init(&v1);
	led_vect_push(&v1,&l1);
	led_vect_push(&v1,&l2);
	led_vect_push(&v1,&l3);
	
	button_aktivate_interupts(&b1);
}