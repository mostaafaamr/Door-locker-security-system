/*
 /******************************************************************************
 *
 * Module: TIMER 1
 *
 * File Name: Timer1.h
 *
 * Description: Header file for the timer 1 driver
 *
 *
 *******************************************************************************/
#ifndef TIMER1_H_
#define TIMER1_H_

#include"std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	noClk,clk1,clk8,clk64,clk256,clk1024,externalFalling,externalRising
}Timer1_Prescaler;

typedef enum{
	Normal,CompareMode=8
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for Initialize the Timer 1 by:
 * 1. Setup the initial value for the timer.
 * 2. Setup the timer mode.
 * 3. Setup the compare value for compare mode.
 * 4. Setup the pre-scaler value.
 */

void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for reseting the Timer.
 */

void Timer1_deInit(void);

/*
 * Description :
 * Function to set the Call Back function address.
 */

void Timer1_setCallBack(void(*a_ptr)(void));





#endif /* TIMER1_H_ */
