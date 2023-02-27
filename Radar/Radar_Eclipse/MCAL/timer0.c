/******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: timer0.c
 *
 * Description: Source file for the AVR Timer0 driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#include "gpio.h"
#include "../mcu_config/private.h" /* To use Timer0 Registers */
#include "timer0.h"
#include <avr/interrupt.h>


static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*
 * Description :
 * Initialize the PWM module by:
 * 1. Trigger Timer0 with PWM Mode.
 * 2. Setup the PWM mode with Non-Inverting.
 * 3. Setup the prescaler with F_CPU/8
 * 4. Setup the compare value based on the required input duty cycle
 * 5. Setup the direction for OC0 as output pin
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0; /* Timer0 initial value */

	OCR0  = ((float)duty_cycle / 100) * 255; /* Set Compare value */

	/*
	 * Configure Timer0 control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

	/* Configure PB3/ OC0 as output pin --> pin where the PWM signal is generated from Timer0 */
	GPIO_setupPinDirection(TIMER0_OCO_PORT_ID,TIMER0_OCO_PIN_ID,PIN_OUTPUT);
}





ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}

}



void Timer0_Ovf_Start(void)
{
	TCNT0=0;

	TCCR0 |=(1<<FOC0) |(1<<CS00);


	TIMSK |=(1<<TOIE0);
}



void Timer0_setCallBack(void(*a_ptr)(void))
{

	g_callBackPtr=a_ptr;
}

