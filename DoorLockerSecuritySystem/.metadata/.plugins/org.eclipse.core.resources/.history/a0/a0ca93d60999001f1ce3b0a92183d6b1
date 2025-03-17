/*
 * dc_motor.h
 *
 *  Created on: 6 Oct 2024
 *      Author: HP
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
#include "gpio.h"

typedef enum{
	MOTOR_OFF,MOTOR_CW,MOTOR_ACW
}DcMotor_State;

#define INPUT1_PORT_ID       PORTB_ID
#define INPUT1_PIN_ID        PIN0_ID

#define INPUT2_PORT_ID       PORTB_ID
#define INPUT2_PIN_ID        PIN1_ID

#define ENABLE_PORT_ID       PORTB_ID
#define ENABLE_PIN_ID        PIN3_ID


void DcMotor_init(void);

void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DC_MOTOR_H_ */
