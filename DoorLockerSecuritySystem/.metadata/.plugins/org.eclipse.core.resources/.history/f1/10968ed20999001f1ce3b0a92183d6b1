/*
 * dc_motor.c
 *
 *  Created on: 6 Oct 2024
 *      Author: HP
 */
#include "dc_motor.h"
#include "pmw.h"

//IN1/PB0 and IN2/PB1 control motor CW, anti-CW or motor STOP

/*ENABLE at PB3/OC0 is configured as output in PMW module
 * this is because this pin can change depending on weather i use TIMER0,1,2*/

void DcMotor_init(void){

	/*configure IN1,IN2 pins as output*/
	GPIO_setupPinDirection(INPUT1_PORT_ID,INPUT1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(INPUT2_PORT_ID,INPUT2_PIN_ID,PIN_OUTPUT);

	/*motor initially stopped, INT1 and IN2 = 0*/
	GPIO_writePin(INPUT1_PORT_ID,INPUT1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(INPUT2_PORT_ID,INPUT2_PIN_ID,LOGIC_LOW);

}

void DcMotor_Rotate(DcMotor_State state, uint8 speed){

	switch(state){
	case MOTOR_OFF:
		GPIO_writePin(INPUT1_PORT_ID,INPUT1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(INPUT2_PORT_ID,INPUT2_PIN_ID,LOGIC_LOW);
		break;
	case MOTOR_CW:
		GPIO_writePin(INPUT1_PORT_ID,INPUT1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(INPUT2_PORT_ID,INPUT2_PIN_ID,LOGIC_HIGH);
		break;
	case MOTOR_ACW:
		GPIO_writePin(INPUT1_PORT_ID,INPUT1_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(INPUT2_PORT_ID,INPUT2_PIN_ID,LOGIC_LOW);
		break;
	default:
		break;
	}

	PWM_Timer0_Start(speed);

}


