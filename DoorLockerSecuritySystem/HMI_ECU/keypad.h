/*
 * keypad.h
 *
 *  Created on: 30 Sept 2024
 *      Author: NARIMAN AHMED
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Std_types.h"

#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID                PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID           PIN0_ID

#define KEYPAD_COL_PORT_ID                PORTB_ID
#define KEYPAD_FIRST_COL_PIN_ID           PIN4_ID

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
