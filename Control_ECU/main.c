/*
 * main.c
 *
 *  Created on: Oct 31, 2022
 *      Author: Mostafa Amr
 */

#include "buzzer.h"
#include "external_eeprom.h"
#include "dcmotor.h"
#include <avr/io.h>
#include "string.h"
#include <util/delay.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define receivenewPassw 10
#define lock_System 11
#define readPassw 12
#define open_Door 13

uint8 pass[6],check[6];
uint16 g_tick=0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void timerTick()
{
	g_tick++;
}

void lockSystem()
{
	Buzzer_on();
	g_tick=0;
	while(g_tick<=60)
	{
	}
	Buzzer_off();

}

void receivenewPass()
{
	uint8 i;
	UART_receiveString(pass);
	_delay_ms(15);
	UART_receiveString(check);

	if(!(strcmp(pass,check)))
	{
		UART_sendByte(1);
		for(i=0;i<5;i++)
		{
			EEPROM_writeByte(0x0311+i, pass[i]);
			_delay_ms(10);

		}   /* Write password in the external EEPROM */



	}
	else
	{
		UART_sendByte(0);
	}



}

void openDoor()
{
	g_tick=0;
	DcMotor_Rotate(1);
	while(g_tick<=15)
	{
	}

	g_tick=0;
	DcMotor_Rotate(0);
	while(g_tick<=3)
	{
	}
	g_tick=0;
	DcMotor_Rotate(2);

	while(g_tick<=15)
	{
	}
	DcMotor_Rotate(0);

}

void readPass()
{
	uint8 i;

	UART_receiveString(check);
	uint8 pass2[6];
	for(i=0;i<5;i++)
	{

		EEPROM_readByte(0x0311+i,(pass2+i));
		_delay_ms(10);

	}
	pass2[5]='\0';

	if(!(strcmp(pass2,check)))
	{
		UART_sendByte(1);  // g_compare=1
	}
	else
	{
		UART_sendByte(0);

	}
}

int main()
{
	uint8 call;
	/*
	 * Set the I-bit to 1.
	 */
	SREG|=(1<<7);

	/*
	 * Initialize the buzzer and motor drivers.
	 */

	DcMotor_Init();
	Buzzer_init();

	/*
	 * Initialize the Uart driver with the required configurations
	 */

	UART_ConfigType o_uartConfig;
	o_uartConfig.bit_data=bit8;
	o_uartConfig.parity=NoParity;
	o_uartConfig.baud_rate=9600;
	UART_init(&o_uartConfig);

	/*
	 * Initialize the I2C driver with the required configurations
	 */

	TWI_ConfigType o_twiConfig;
	o_twiConfig.address=0x02;
	o_twiConfig.bit_rate=2;
	TWI_init(&o_twiConfig);

	/*
	 * Initialize the timer driver with the required configurations
	 * and set the callback function.
	 */

	Timer1_ConfigType o_timerConfig;
	o_timerConfig.initial_value=0;
	o_timerConfig.mode=CompareMode;
	o_timerConfig.prescaler=clk1024;
	o_timerConfig.compare_value=7812;
	Timer1_init(&o_timerConfig);
	Timer1_setCallBack(timerTick);


	while(1)
	{
		call=UART_recieveByte();
		switch(call)
		{
		case receivenewPassw:
			receivenewPass();
			break;
		case readPassw:
			readPass();
			break;
		case lock_System:
			lockSystem();
			break;
		case open_Door:
			openDoor();
			break;
		}


	}

}
