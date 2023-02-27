 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: survo_motor.h
 *
 * Description: header file for the Survo-Motor driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_

#include "../mcu_config/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize the DC Motor by:
 * 1. Setup the direction of the two motor pins as output by send the request to GPIO driver.
 * 2. Stop the motor at the beginning
 */
void ServoMotor_Init(void);



void SERVO_set_angle(uint8 angle);



uint16 Map(sint32 Copy_sint32InputMin , sint32 Copy_sint32InputMax , sint32 Copy_sint32OutputMin , sint32 Copy_sint32OutputMax , sint32 Copy_sint32InputVal);

#endif /* SERVO_MOTOR_H_ */
