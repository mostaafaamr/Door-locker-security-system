/*
 /******************************************************************************
 *
 * Module: TIMER 1
 *
 * File Name: Timer1.c
 *
 * Description: Source file for the timer 1 driver
 *
 *
 *******************************************************************************/
#include"Timer1.h"
#include<avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application at the timer compare value  */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for Initialize the Timer 1 by:
 * 1. Setup the initial value for the timer.
 * 2. Setup the timer mode.
 * 3. Setup the compare value for compare mode.
 * 4. Setup the pre-scaler value.
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCCR1A=(1<<FOC1A);
	TCCR1B=Config_Ptr->mode;
	TCCR1B|=Config_Ptr->prescaler;
	TCNT1=Config_Ptr->initial_value;
	OCR1A=Config_Ptr->compare_value;
	TIMSK=(1<<OCIE1A);
}

/*
 * Description :
 * Function responsible for reseting the Timer.
 */

void Timer1_deInit(void)
{
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	OCR1A=0;
	TIMSK=0;
}

/*
 * Description: Function to set the Call Back function address.
 */

void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;

}
