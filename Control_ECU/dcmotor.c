 /******************************************************************************
 *
 * Module: DC MOTOR
 *
 * File Name: dcmotor.c
 *
 * Description: Source file for the dc motor driver
 *
 *
 *******************************************************************************/
#include "gpio.h"
#include "Timer0PWM.h"
#include "dcmotor.h"
#include "uart.h"

void DcMotor_Init()
{
	GPIO_setupPinDirection(PORTB_ID, PIN1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN2_ID, PIN_OUTPUT);
	GPIO_writePin(PORTB_ID, PIN2_ID, LOGIC_LOW);
	GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
}

void DcMotor_Rotate(uint8 state)
{
	if(state==0)
	{
		GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN2_ID, LOGIC_LOW);
	}
	else if(state==1)
	{
		PWM_Timer0_Start(255);
		GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_HIGH);
		GPIO_writePin(PORTB_ID, PIN2_ID, LOGIC_LOW);

	}
	else if(state==2)
	{
		PWM_Timer0_Start(255);
		GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN2_ID, LOGIC_HIGH);

	}

}

