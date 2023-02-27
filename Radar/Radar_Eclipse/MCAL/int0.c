/*
 * int0.c
 *
 *  Created on: Feb 24, 2023
 *      Author: tarek
 */

#include "gpio.h"
#include "../mcu_config/private.h" /* To use Timer0 Registers */
#include "int0.h"
#include <avr/interrupt.h>


static volatile void (*g_callBackPtr)(void) = NULL_PTR;



ISR(INT0_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}

}



void INT0_init(void)
{
	GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT);
	GPIO_writePin(PORTD_ID, PIN2_ID, LOGIC_HIGH);
	MCUCR |=(1<<ISC00);
	GICR |=(1<<INT0);
}



void INT0_setCallBack(void(*a_ptr)(void))
{

	g_callBackPtr=a_ptr;
}

