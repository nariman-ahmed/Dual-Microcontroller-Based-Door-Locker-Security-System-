/*
 * keypad.c
 *
 *  Created on: 30 Sept 2024
 *      Author: NARIMAN AHMED
 */

#include "keypad.h"
#include "gpio.h"
#include <util/delay.h>

//#define STANDARD_KEYPAD

#ifndef STANDARD_KEYPAD
	#if(KEYPAD_NUM_COLS==3)
	static uint8 KEYPAD_adjust_nonstandard_4x3(uint8 key);
	#elif(KEYPAD_NUM_COLS==4)
	static uint8 KEYPAD_adjust_nonstandard_4x4(uint8 key);
	#endif
#else
static uint8 KEYPAD_adjust_standard_4x4(uint8 key);
#endif

uint8 KEYPAD_getPressedKey(void){
	//set up row pins
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+2,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+3,PIN_INPUT);

	//set up col pins
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+2,PIN_INPUT);
#if(KEYPAD_NUM_COLS==4)
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+3,PIN_INPUT);
#endif

	uint8 key;
	uint8 row, col;

	while(1){
		//loop on rows
		for(row=0;row<KEYPAD_NUM_ROWS;row++)
		{
			//set chosen row as output and to high
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_OUTPUT);
			GPIO_writePin(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,KEYPAD_BUTTON_PRESSED);

			//loop on columns and read pin
			for(col=0;col<KEYPAD_NUM_COLS;col++)
			{
				if(GPIO_readPin(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+col)==KEYPAD_BUTTON_PRESSED)
				{
					key=((row*KEYPAD_NUM_COLS)+col+1);

					#if(KEYPAD_NUM_COLS==3)
						#ifdef STANDARD_KEYPAD
							if(key>=1 && key<=9)
							{
								return key;
							}
							else if(key==10)
							{
								return '*';     //ASCII OF * is 42
							}
							else if(key==11)
							{
								return 0;
							}
							else if(key==12)
							{
								return '#';    //ASCII OF # is 35
							}
						#else
							return KEYPAD_adjust_nonstandard_4x3(key);
						#endif
                    #elif(KEYPAD_NUM_COLS==4)
						#ifdef STANDARD_KEYPAD
							return KEYPAD_adjust_standard_4x4(key);
						#else
							return KEYPAD_adjust_nonstandard_4x4(key);
						#endif
					#endif
				}
			}
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
			_delay_ms(5);
		}
	}

}

static uint8 KEYPAD_adjust_standard_4x4(uint8 key){
	switch(key)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	case 4:
		return 'A';
	case 5:
		return 4;
	case 6:
		return 5;
	case 7:
		return 6;
	case 8:
		return 'B';
	case 9:
		return 7;
	case 10:
		return 8;
	case 11:
		return 9;
	case 12:
		return 'C';
	case 13:
		return '*';
	case 14:
		return 0;
	case 15:
		return '#';
	case 16:
		return 'D';
	default:
		break;
	}
}

#ifndef STANDARD_KEYPAD

#if(KEYPAD_NUM_COLS==3)

static uint8 KEYPAD_adjust_nonstandard_4x3(uint8 key){
	switch(key)
	{
	case 1:
		return 7;
	case 2:
		return 8;
	case 3:
		return 9;
	case 4:
		return 4;
	case 5:
		return 5;
	case 6:
		return 6;
	case 7:
		return 1;
	case 8:
		return 2;
	case 9:
		return 3;
	case 10:
		return '*';
	case 11:
		return 0;
	case 12:
		return '#';
	default:
		break;
	}
}

#elif(KEYPAD_NUM_COLS==4)

static uint8 KEYPAD_adjust_nonstandard_4x4(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
		case 1: keypad_button = 7;
				break;
		case 2: keypad_button = 8;
				break;
		case 3: keypad_button = 9;
				break;
		case 4: keypad_button = '%'; // ASCII Code of %
				break;
		case 5: keypad_button = 4;
				break;
		case 6: keypad_button = 5;
				break;
		case 7: keypad_button = 6;
				break;
		case 8: keypad_button = '*'; /* ASCII Code of '*' */
				break;
		case 9: keypad_button = 1;
				break;
		case 10: keypad_button = 2;
				break;
		case 11: keypad_button = 3;
				break;
		case 12: keypad_button = '-'; /* ASCII Code of '-' */
				break;
		case 13: keypad_button = 13;  /* ASCII of Enter */
				break;
		case 14: keypad_button = 0;
				break;
		case 15: keypad_button = '='; /* ASCII Code of '=' */
				break;
		case 16: keypad_button = '+'; /* ASCII Code of '+' */
				break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}

#endif

#endif


