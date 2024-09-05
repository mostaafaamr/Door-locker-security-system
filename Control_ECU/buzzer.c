/*
 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the buzzer driver
 *
 *
 *******************************************************************************/
#include <avr/io.h>
#include "gpio.h"
#include "buzzer.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Buzzer_init()
{
	GPIO_setupPinDirection(buzzerPort, buzzerPin, PIN_OUTPUT);
	GPIO_writePin(buzzerPort, buzzerPin, LOGIC_LOW);

}

void Buzzer_on(void)
{
	GPIO_writePin(buzzerPort, buzzerPin, LOGIC_HIGH);
}

void Buzzer_off(void)
{
	GPIO_writePin(buzzerPort, buzzerPin, LOGIC_LOW);
}
