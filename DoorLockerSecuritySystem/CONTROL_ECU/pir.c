/*
 * pir.c
 *
 *  Created on: 2 Nov 2024
 *      Author: NARIMAN AHMED
 */
#include "pir.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void PIR_init(void)
{
    GPIO_setupPinDirection(PIR_PORT,PIR_PIN,PIN_INPUT);
}

uint8 PIR_getState(void)
{
    /* Read the state of the PIR sensor pin */
    if (GPIO_readPin(PIR_PORT,PIR_PIN)==LOGIC_HIGH)
    {
        return 1; // Motion detected
    }
    else
    {
        return 0; // No motion detected
    }
}



