/******************************************************************************
 *
 * Module: Servo Motor
 *
 * File Name: Servo_motor.c
 *
 * Description: source file for the DC-Motor driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#include "servo_motor.h"

#include "../MCAL/gpio.h"
#include "../MCAL/timer1.h"

/*
 * Description :
 * Initialize the Servo Motor by:
 * 1. Setup the timer1 for motor.
 * 2. Stop the motor at the beginning
 */
void ServoMotor_Init(void)
{
	GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
	Timer1_ConfigType timer1_config_ptr={0,750 ,19999,F_CPU_8_TIMER1,FAST_PWM_ICR1};
	/* Setup the two motor pins as output pins */
	Timer1_init(&timer1_config_ptr);

}


void SERVO_set_angle(uint8 angle)
{
	uint16 U = Map(0 , 180 ,750 ,2500 , angle);
	TIMER1_set_OCR1A(U);
}

uint16 Map(sint32 Copy_sint32InputMin , sint32 Copy_sint32InputMax , sint32 Copy_sint32OutputMin , sint32 Copy_sint32OutputMax , sint32 Copy_sint32InputVal)
{
	sint32 Loacl_sint32Value = Copy_sint32InputVal - Copy_sint32InputMin;
	Loacl_sint32Value = Loacl_sint32Value * (Copy_sint32OutputMax - Copy_sint32OutputMin);
	Loacl_sint32Value = Loacl_sint32Value / (Copy_sint32InputMax - Copy_sint32InputMin);
	Loacl_sint32Value = Loacl_sint32Value + Copy_sint32OutputMin;
	return Loacl_sint32Value;
}







