/*
 * main.c
 *
 *  Created on: Oct 31, 2022
 *      Author: Mostafa Amr
 */

#include "lcd.h"
#include "keypad.h"
#include <avr/io.h>
#include <util/delay.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define receivenewPassw 10
#define lock_System 11
#define readPassw 12
#define open_Door 13


uint8 pass[6]={},check[6];
uint8 g_compare,g_checkCount=0,g_tick=0,g_enter;

void mainOptions();

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void timerTick()
{
	g_tick++;
}



void newPass()
{
	uint8 i;
	LCD_clearScreen();
	LCD_displayString("Enter new pass:");
	LCD_moveCursor(1,0);
	for(i=0;i<5;i++)
	{
		pass[i]=KEYPAD_getPressedKey()+48;
		_delay_ms(100);
		LCD_displayCharacter('*');
		_delay_ms(100);


	}
	_delay_ms(100);
	while(KEYPAD_getPressedKey()!='=')
	{
	}
	pass[i]='=';
	_delay_ms(50);
	UART_sendByte(receivenewPassw);
	_delay_us(50);

	UART_sendString(pass);
	_delay_ms(50);
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Re-enter pass:");
	LCD_moveCursor(1,0);
	for(i=0;i<5;i++)
	{
		check[i]=KEYPAD_getPressedKey()+48;
		_delay_ms(100);
		LCD_displayCharacter('*');
		_delay_ms(100);
	}
	_delay_ms(100);
	while(KEYPAD_getPressedKey()!='=')
	{
	}
	check[i]='=';
	_delay_ms(50);
	LCD_clearScreen();
	UART_sendString(check);
	_delay_ms(20);
	LCD_clearScreen();


	g_compare=UART_recieveByte();


	if(g_compare==1)
		{
		return;
		}
	else if(g_compare==0)
		newPass();



}

void enterPass()
{
	LCD_clearScreen();
	LCD_displayString("plz enter pass");
	LCD_moveCursor(1, 0);
	UART_sendByte(readPassw);
	uint8 i;
	for(i=0;i<5;i++)
	{
		pass[i]=KEYPAD_getPressedKey()+48;
		_delay_ms(100);
		LCD_displayCharacter('*');
		_delay_ms(100);
	}
	_delay_ms(100);
	while(KEYPAD_getPressedKey()!='=')
	{
	}
	pass[i]='=';
	_delay_ms(50);

	UART_sendString(pass);
	g_compare=UART_recieveByte();   //Check if password is right

	while(g_checkCount<2)
	{
		if(g_compare==1)
		{
			g_checkCount=0;
			return;
		}
		else if(g_compare==0)
		{
			g_checkCount++;
			enterPass();
		}
	}
	if(g_checkCount==2)
	{
		_delay_ms(50);
		UART_sendByte(lock_System);
		_delay_ms(50);
		g_checkCount=0;

		LCD_clearScreen();

		LCD_displayString("Error");
		g_tick=0;
		while(g_tick<=60)
		{
		}
		LCD_clearScreen();
		mainOptions();
	}


}

void mainOptions()
{
	g_enter=1;
	LCD_clearScreen();
	LCD_displayString("+: Open door");
	LCD_moveCursor(1, 0);
	LCD_displayString("-: Change pass");
	if(KEYPAD_getPressedKey()=='+')
	{
		_delay_ms(100);
		enterPass();
		if(g_enter==0)
			return;
		UART_sendByte(open_Door);

		g_tick=0;
		LCD_clearScreen();
		LCD_displayString("Door unlocking");
		while(g_tick<=15)
		{

		}

		LCD_clearScreen();
		LCD_displayString("...");
		g_tick=0;
		while(g_tick<=3)
		{

		}

		g_tick=0;
		LCD_clearScreen();
		LCD_displayString("Door locking");
		while(g_tick<=15)
		{
		}

	}
	else if(KEYPAD_getPressedKey()=='-')
	{
		g_enter=0;
		_delay_ms(100);
		enterPass();
		newPass();
	}
}




int main()
{
	/*
	 * Set the I-bit to 1.
	*/
	SREG|=(1<<7);
	Timer1_ConfigType o_timerConfig;

	/*
	 * Initialize the Uart driver with the required configurations
	*/

	UART_ConfigType o_uartConfig;
	o_uartConfig.bit_data=bit8;
	o_uartConfig.parity=NoParity;
	o_uartConfig.baud_rate=9600;
	UART_init(&o_uartConfig);

	LCD_init();

	/*
	 * Initialize the timer driver with the required configurations
	 * and set the callback function.
	 */

	o_timerConfig.initial_value=0;
	o_timerConfig.mode=CompareMode;
	o_timerConfig.prescaler=clk1024;
	o_timerConfig.compare_value=7812;
	Timer1_init(&o_timerConfig);
	Timer1_setCallBack(timerTick);

	/*
	 * Set a new password for the system at the beginning of the application
	 */

	newPass();


	while (1)
	{
		mainOptions();


	}

}
