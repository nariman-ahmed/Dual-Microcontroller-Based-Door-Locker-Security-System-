/*
 * buxxer.c
 *
 *  Created on: 5 Oct 2024
 *      Author: NARIMAN AHMED
 */
#include "buzzer.h"

void BUZZER_init(Buzzer_Config * config) {

    GPIO_setupPinDirection(config->port, config->pin, PIN_OUTPUT);
    GPIO_writePin(config->port, config->pin, LOGIC_LOW);
}


void BUZZER_on(Buzzer_Config * config) {
    GPIO_writePin(config->port, config->pin, LOGIC_HIGH);
}


void BUZZER_off(Buzzer_Config * config) {
    GPIO_writePin(config->port, config->pin, LOGIC_LOW);
}


