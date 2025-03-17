/*
 * buzzer.h
 *
 *  Created on: 5 Oct 2024
 *      Author: NARIMAN AHMED
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "gpio.h"

typedef struct {
    uint8 port;
    uint8 pin;
} Buzzer_Config;

void BUZZER_init(Buzzer_Config * config);

void BUZZER_on(Buzzer_Config * config);

void BUZZER_off(Buzzer_Config * config);


#endif /* BUZZER_H_ */
