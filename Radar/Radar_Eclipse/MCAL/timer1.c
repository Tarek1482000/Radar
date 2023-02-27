/******************************************************************************
 *
 * Module: Timer 1
 *
 * File Name: timer1.h
 *
 * Description: Source file for the Timer1 driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#include "timer1.h"
#include "gpio.h"
#include "../mcu_config/common_macros.h"
#include "../mcu_config/private.h"
#include <avr/interrupt.h>

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER1_COMPA_vect)
{

	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}

}


ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}


void Timer1_init(const Timer1_ConfigType *Config_Ptr)
{
	TCNT1=Config_Ptr->initial_value;

	OCR1A=Config_Ptr->compare_value; //750-2500

	ICR1=Config_Ptr->ICR1_value;

	if((Config_Ptr->mode)==NORMAL)
	{
		TIMSK |= (1<<TOIE1);

	}
	else if((Config_Ptr->mode)==CTC)
	{
		TIMSK |= (1<<OCIE1A);
	}


	if((Config_Ptr->mode)==FAST_PWM_ICR1)
	{
		TCCR1A |= (1<<COM1A1);
	}
	else
	{
		TCCR1A |= (1<<FOC1A) | (1<<FOC1B);
	}


	TCCR1A |= (GET_BIT((Config_Ptr->mode),0 ) << WGM10)
					 |(GET_BIT((Config_Ptr->mode),1 ) << WGM11);


	TCCR1B |=  ((Config_Ptr->prescaler & 0x07)<< CS10)

    	    						  |(GET_BIT((Config_Ptr->mode),2 ) << WGM12)
									  |(GET_BIT((Config_Ptr->mode),3 ) << WGM13);
}

void Timer1_deInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK &= ~(1<<TOIE1) &~(1<<OCIE1A) ;
}


void TIMER1_set_OCR1A(uint16 duty)
{
	Timer1_ConfigType timer1_config_ptr={0,duty ,19999,F_CPU_8_TIMER1,FAST_PWM_ICR1};
	/* Setup the two motor pins as output pins */
	Timer1_init(&timer1_config_ptr);
}


void Timer1_setCallBack(void(*a_ptr)(void))
{

	g_callBackPtr=a_ptr;
}
