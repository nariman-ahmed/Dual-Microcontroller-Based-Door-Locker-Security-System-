/*
 * lcd.h
 *
 *  Created on: 2 Oct 2024
 *      Author: HP
 */

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include <util/delay.h>
#include <stdlib.h>

//3yzeen ne define el 8 bits lel data wel commands, wel RS wel E pins
//CONFIGURE FOR BOTH 4 BIT AND 8 BIT LCDS!!
#define LCD_DATA_BITS_MODE             8

#define RS_PORT                        PORTD_ID
#define RS_PIN                         PIN0_ID

#define E_PORT                         PORTD_ID
#define E_PIN                          PIN1_ID

#define DATA_PORT_ID                   PORTC_ID

#if(LCD_DATA_BITS_MODE==4)
#define DATA_PORT_FRIST_PIN            PIN3_ID
#endif


//NZABAT EL COMMANDSS
#define LCD_CLEAR_COMMAND               0x01
#define LCD_GO_TO_HOME                  0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE   0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE    0x28

#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1  0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2  0x32

#define LCD_CURSOR_OFF                  0x0C
#define LCD_CURSOR_ON                   0x0E
#define LCD_SET_CURSOR_LOCATION         0x80

//FUNCTIONS: init, send command, send data
void LCD_init(void);

void LCD_sendCommand(uint8 command);

void LCD_displayCharacter(uint8 data);

void LCD_displayString(const char* str);

void LCD_moveCursor(uint8 row, uint8 col);

void LCD_displayStringRowColumn(uint8 row, uint8 col, const char* str);

void LCD_integerToString(int data);

void LCD_clearScreen(void);


#endif /* LCD_H_ */
