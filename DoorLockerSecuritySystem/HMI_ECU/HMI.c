/*
 * HMI.c
 *
 *  Created on: 2 Nov 2024
 *      Author: NARIMAN AHMED
 */
#include "gpio.h"
#include "uart.h"
#include "timer.h"
#include "keypad.h"
#include "lcd.h"
#include "util/delay.h"
#include "avr/io.h"
#include "avr/interrupt.h"

#define HMI_MC_READY    		  0x10
#define CONTROL_MC_READY 		  0x20

#define OPEN_DOOR     			     1
#define CHANGE_PASS  			     2

#define SUCCESS         		     1
#define FAIL             			 0

#define OPERATION_NEW_PASS     		10
#define OPERATION_MENU_SELECT       20
#define OPERATION_CHANGE_PASS		30
#define OPERATION_OPEN_DOOR			40
#define TRIGGER_ALARM               50
#define DOOR_OPEN_CW                60
#define DOOR_CLOSE_ACW               61
#define DOOR_STOP                   62
#define ALARM_ON                    63
#define ALARM_OFF					64


Timer_ConfigType timer1_config = {0,15625,TIMER1,F_CPU_1024,COMPARE_MODE};
UART_ConfigType uart_config = {8,2,1,9600};

uint8 operation_flag=OPERATION_NEW_PASS;

uint8 pass[5];
uint8 confirmed_pass[5];
uint8 confirmed;
uint8 menuSelection=0;
uint8 change_pass_failed=0;
uint8 open_door_pass_failed=0;
volatile uint8 ticks;

void callBackTimer(void){
	ticks++;
}

void mainMenuSelector(void){
	uint8 key=0;

	LCD_clearScreen();
	LCD_displayString("+ : Open Door");
	LCD_moveCursor(1,0);
	LCD_displayString("- : Change Pass");

	key=KEYPAD_getPressedKey();
	_delay_ms(500);

	if(key=='+')
	{
		menuSelection=OPEN_DOOR;
	}
	else if(key=='-')
	{
		menuSelection=CHANGE_PASS;
	}
}

void enterPassword(void){

	uint8 num=0, i=0;

	LCD_clearScreen();
	LCD_displayString("Enter new pass:");
	LCD_moveCursor(1,0);

	num = KEYPAD_getPressedKey();

	while(num!='=')
	{
		pass[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		i++;
		_delay_ms(500);
		num=KEYPAD_getPressedKey();
	}

}

void enterConfirmedPassowrd(void){

	uint8 num=0, i=0;

	LCD_clearScreen();
	LCD_displayString("Enter same pass:");
	LCD_moveCursor(1,0);

	num = KEYPAD_getPressedKey();

	while(num!='=')
	{
		confirmed_pass[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		i++;
		_delay_ms(500);
		num=KEYPAD_getPressedKey();
	}

}

void sendPassword(void){

	UART_sendByte(HMI_MC_READY);
	for(int i=0;i<5;i++)
	{
		UART_sendByte(pass[i]);
	}
}

void sendConfirmedPassword(void){

	UART_sendByte(HMI_MC_READY);
	for(int i=0;i<5;i++)
	{
		UART_sendByte(confirmed_pass[i]);
	}
}

void receive_newPasswordConfirmation(void){

	while(UART_recieveByte()!=CONTROL_MC_READY){}

	confirmed=UART_recieveByte();
}

void newPasswordSequence(void){

	enterPassword();

	_delay_ms(500);

	enterConfirmedPassowrd();

	sendPassword();
	sendConfirmedPassword();

	receive_newPasswordConfirmation();

	_delay_ms(500);

	LCD_clearScreen();
	if(confirmed)
	{
		LCD_displayString("CONFIRMED");
		_delay_ms(1000);
		return;
	}
	else
	{
		LCD_displayString("UNMATCHED");
		_delay_ms(1000);
		LCD_clearScreen();
		newPasswordSequence();
	}

}

uint8 currentPasswordAuthentication(void){

	uint8 status=0, num=0, i=0;
	uint8 current_pass[5];

	LCD_clearScreen();
	LCD_displayString("Enter current");
	LCD_moveCursor(1,0);
	LCD_displayString("password:");
	while(num!='=')
	{
		current_pass[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		i++;
		_delay_ms(500);
		num=KEYPAD_getPressedKey();
	}

	UART_sendByte(HMI_MC_READY);

	for(int i=0;i<5;i++)
	{
		UART_sendByte(current_pass[i]);
	}

	status=UART_recieveByte();

	return status;
}

void alarm(void){
	while(UART_recieveByte()!=ALARM_ON){}
	LCD_clearScreen();
	LCD_displayString("SYSTEM LOCKED");
//	ticks=0;
//	while(ticks<3);
	while(UART_recieveByte()!=ALARM_OFF){}
	LCD_clearScreen();
	LCD_displayString("SYSTEM UNLOCKED");
	_delay_ms(1000);
}

void changePassword(void){

	uint8 authentication=0;

	authentication=currentPasswordAuthentication(); //can be SUCCCESS or FAIL

	if(authentication==SUCCESS)
	{
		UART_sendByte(SUCCESS);
		change_pass_failed=0;
		newPasswordSequence();
	}
	else if(authentication==FAIL)
	{
		change_pass_failed++;
		if(change_pass_failed<3)   //entered wrong once or twice
		{
			UART_sendByte(FAIL);
			LCD_clearScreen();
			LCD_displayString("fail count: ");
			LCD_integerToString(change_pass_failed);
			_delay_ms(500);
			changePassword();  //again
		}
		else if(change_pass_failed==3)   //third time, reset failed variable, lock for 1 min, trigger alarm.
		{
			UART_sendByte(TRIGGER_ALARM);
			change_pass_failed=0;
			LCD_clearScreen();
			LCD_displayString("fail count:3");
			//send for CONTROL to trigger alarm
		}
	}

}

void openDoor(void){

	uint8 authentication=0;

	authentication=currentPasswordAuthentication(); //can be SUCCCESS or FAIL

	if(authentication==SUCCESS)
	{
		//MOTOR STUFF AND OPEN DOOR FOR 15 SEC AND PIR
		open_door_pass_failed=0;
		LCD_clearScreen();
		LCD_displayString("SUCCESS");
		UART_sendByte(SUCCESS);

		//LCD EL DOORRRR
		while(UART_recieveByte()!=DOOR_OPEN_CW){}
		LCD_clearScreen();
		LCD_displayString("Door Opening");
		while(UART_recieveByte()!=DOOR_CLOSE_ACW){}
		LCD_clearScreen();
		LCD_displayString("Door Closing");
		while(UART_recieveByte()!=DOOR_STOP){}
		LCD_clearScreen();
		LCD_displayString("Door closed");
		LCD_moveCursor(1,0);
		LCD_displayString("successfully.");
	}
	else if(authentication==FAIL)
	{
		open_door_pass_failed++;
		if(open_door_pass_failed<3)   //entered wrong once or twice
		{
			UART_sendByte(FAIL);
			LCD_clearScreen();
			LCD_displayString("try again.");
			_delay_ms(50);
			openDoor();  //again
		}
		else if(open_door_pass_failed==3)   //third time, reset failed variable, lock for 1 min, trigger alarm.
		{
			UART_sendByte(TRIGGER_ALARM);
			open_door_pass_failed=0;
			alarm();
		}
	}

}





int main(void){


	SREG|=(1<<7);

	LCD_init();
	Timer_init(&timer1_config);
	Timer_setCallBack(callBackTimer,TIMER1);
	Timer_setCallBack(&callBackTimer,TIMER1);
	UART_init(&uart_config);

	newPasswordSequence();

	while(1)
	{
		//start up with password setup
		mainMenuSelector();
		//hayen2el 3al menu lewahdo
		UART_sendByte(HMI_MC_READY);

		if(menuSelection==OPEN_DOOR)
		{
			UART_sendByte(OPERATION_OPEN_DOOR);     //SEND CURRENT OPERATION
			openDoor();
		}
		else if(menuSelection==CHANGE_PASS)
		{
			UART_sendByte(OPERATION_CHANGE_PASS);
			changePassword();
		}

		LCD_clearScreen();
		LCD_displayString("resettingg");

		while(UART_recieveByte()!=CONTROL_MC_READY);












//		UART_sendByte(HMI_MC_READY);
//		UART_sendByte(operation_flag);
//
//		if(operation_flag==OPERATION_NEW_PASS)
//		{
//			newPasswordSequence();
//			//going to main menu at success
//			operation_flag=OPERATION_MENU_SELECT;
//		}
//		else if(operation_flag==OPERATION_MENU_SELECT)
//		{
//			mainMenuSelector();
//			if(menuSelection==OPEN_DOOR)
//			{
//
//			}
//			else if(menuSelection==CHANGE_PASS)
//			{
//
//			}
//		}
//		else if(operation_flag==OPERATION_CHANGE_PASS)
//		{
//
//		}
//		else if(operation_flag==OPERATION_OPEN_DOOR)
//		{
//
//		}

	}



	return 0;
}


