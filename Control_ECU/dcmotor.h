/*
 * dcmotor.h
 *
 *  Created on: Oct 4, 2022
 *      Author: Mostafa Amr
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"
#include"uart.h"
#include"twi.h"


void DcMotor_Init();
void DcMotor_Rotate(uint8 state);


#endif /* DCMOTOR_H_ */
