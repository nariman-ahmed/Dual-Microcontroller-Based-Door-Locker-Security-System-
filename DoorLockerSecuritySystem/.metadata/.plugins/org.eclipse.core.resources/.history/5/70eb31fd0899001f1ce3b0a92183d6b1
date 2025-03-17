/*
 * lcd.c
 *
 *  Created on: 2 Oct 2024
 *      Author: HP
 */
#include "lcd.h"
#include "gpio.h"
#include "common_macros.h"


void LCD_init(void){

	//set up RS,E,DATA
	GPIO_setupPinDirection(RS_PORT,RS_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(E_PORT,E_PIN,PIN_OUTPUT);

#if(LCD_DATA_BITS_MODE==8)
	GPIO_setupPortDirection(DATA_PORT_ID,PORT_OUTPUT);

	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#elif(LCD_DATA_BITS_MODE==4)
	GPIO_setupPinDirection(DATA_PORT_ID,DATA_PORT_FRIST_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DATA_PORT_ID,DATA_PORT_FRIST_PIN+1,PIN_OUTPUT);
	GPIO_setupPinDirection(DATA_PORT_ID,DATA_PORT_FRIST_PIN+2,PIN_OUTPUT);
	GPIO_setupPinDirection(DATA_PORT_ID,DATA_PORT_FRIST_PIN+3,PIN_OUTPUT);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#endif

	_delay_ms(20);
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);

}

void LCD_sendCommand(uint8 command){

	//RS=O,E=1,SEND,E=0, and delay between
	GPIO_writePin(RS_PORT,RS_PIN,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE==8)
	GPIO_writePort(DATA_PORT_ID,command);
#elif(LCD_DATA_BITS_MODE==4)
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN,GET_BIT(command,4));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+1,GET_BIT(command,5));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+2,GET_BIT(command,6));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+3,GET_BIT(command,7));

	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN,GET_BIT(command,0));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+1,GET_BIT(command,1));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+2,GET_BIT(command,2));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+3,GET_BIT(command,3));
#endif

	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);

}

void LCD_displayCharacter(uint8 data){

	//RS=1,E=1,SEND,E=0, and delay between
	GPIO_writePin(RS_PORT,RS_PIN,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE==8)
	GPIO_writePort(DATA_PORT_ID,data);
#elif(LCD_DATA_BITS_MODE==4)
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN,GET_BIT(data,4));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+1,GET_BIT(data,5));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+2,GET_BIT(data,6));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+3,GET_BIT(data,7));

	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN,GET_BIT(data,0));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+1,GET_BIT(data,1));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+2,GET_BIT(data,2));
	GPIO_writePin(DATA_PORT_ID,DATA_PORT_FRIST_PIN+3,GET_BIT(data,3));

#endif

	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);

}

void LCD_displayString(const char* str){

	for(int i=0;str[i]!='\0';i++)
	{
		LCD_displayCharacter(str[i]);
	}

}

void LCD_moveCursor(uint8 row, uint8 col){

	uint8 LCD_address;

	switch(row){
	case 0:
		LCD_address = 0x00+col;
		break;
	case 1:
		LCD_address = 0x40+col;
		break;
	case 2:
		LCD_address = 0x10+col;
		break;
	case 3:
		LCD_address = 0x50+col;
		break;
	default:
		break;
	}

	LCD_sendCommand(LCD_address | LCD_SET_CURSOR_LOCATION);

}

void LCD_displayStringRowColumn(uint8 row, uint8 col, const char* str){

	LCD_moveCursor(row,col);
	LCD_displayString(str);

}

void LCD_integerToString(int data){

	char buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);

}

void LCD_clearScreen(void){

	LCD_sendCommand(LCD_CLEAR_COMMAND);

}


