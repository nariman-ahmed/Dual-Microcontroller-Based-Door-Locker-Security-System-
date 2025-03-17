/*
 * pmw.c
 *
 *  Created on: 6 Oct 2024
 *      Author: HP
 */
#include "pmw.h"
#include "gpio.h"
#include "avr/io.h"

void PWM_Timer0_Start(uint8 duty_cycle){

	/*initialize TIMER0 with PMW*/
	TCCR0=(1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS02)|(1<<CS00);
	TCNT0=0;
	TIMSK|=(1<<OCIE0);

	/*CONFIGURE OC0/PB3 as output pin*/
	GPIO_setupPinDirection(PMW_OUTPUT_PORT_ID,PMW_OUTPUT_PIN_ID,PIN_OUTPUT);

	/*use the function paramater to control duty cycle*/
	switch(duty_cycle){
	case 100:
		OCR0=255;     /*100% OF 256*/
		break;
	case 75:
		OCR0=192;     /*75% OF 256*/
		break;
	case 50:
		OCR0=128;     /*50% OF 256*/
		break;
	case 25:
		OCR0=64;      /*25% OF 256*/
		break;
	case 0:
		OCR0=0;       /*0% OF 255*/
		break;
	default:
		break;
	}
}


