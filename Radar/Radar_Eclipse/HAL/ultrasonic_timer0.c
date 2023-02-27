/******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the AVR ULTRASONIC driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#include "ultrasonic_timer0.h"
#include "../MCAL/int0.h" /* To use call back function and calculate edge */
#include "../MCAL/timer0.h" /* To use call back function and calculate edge */
#include "../MCAL/gpio.h"
#include "../MCAL/uart.h"
#include "../mcu_config/private.h"
#include <util/delay.h>/* To use delay in Trigger  function  */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/


static volatile uint16 g_timer_count = 0;
static volatile uint8  g_sensor_start = 0 , g_rising_edge=0;
volatile uint8 g_distance=0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Set Triggre pin output
 * Initialize timer0 and interrupt0 and set callback functions
 */
void Ultrasonic_init(void)
{
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, PIN_OUTPUT);

	Timer0_Ovf_Start();
	Timer0_setCallBack(Ultrasonic_edgeProcessing);/* To count the time that taken to send and receive signal  */


	INT0_init();
	INT0_setCallBack(Ultrasonic_detectedge);/* To detect ECHO signal */

	SREG |=0x80; /* To use timer0 and interrupt0 ISR */
}


/*
 * Send signal for 10us
 */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_us(15);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_LOW);
}


/*
 * send 10us for ultrasonic trigger pin
 * wait until calculate edge  and calculate distance
 * send distance by UART
 *return measured distance
 */

uint8 Ultrasonic_readDistance(void)
{
	if(g_sensor_start == 0)
	{
		Ultrasonic_Trigger();
		g_sensor_start=1;
	}
	UART_sendDecimal(g_distance);
	return g_distance;
}


/*
 * capture edge
 */

void Ultrasonic_detectedge(void)
{
	if(g_sensor_start==1)
	{
		/*
		 * start raising edge
		 * start the counter
		 */
		if(g_rising_edge==0)
		{
			TCNT0=0;
			g_rising_edge=1;
			g_timer_count=0;
		}

		/*
		 * The end of raising edge
		 * calculate the distance
		 */
		else
		{
			/*
			 * Distance = (Velocity of sound * Timer ) / 2
			 * Time = ( 1/ 8Mhz ) = 125 nS
			 * Distance = (34300 * ( 125 nS * Ticks ) ) / 2 = 2.14375 * 10^-3 ticks
			 * Distance = ticks / 466.47
			 * Distance = ( Timer Counter * 256 + ticks ) / 466.47
			 *
			 * ((g_timer_count*256)+ (TCNT0)) => completed overflow + remaining time
			 *
			 */
			g_distance=((uint16)(g_timer_count*256) + (TCNT0)) / (466);

			TCNT0 = 0;
			g_sensor_start=0;
			g_timer_count=0;
			g_rising_edge=0;
		}

	}

}

/*
 * Timer count until 550 (max distance 40cm)
 */
void Ultrasonic_edgeProcessing(void)
{
	g_timer_count++;

	if(g_timer_count > 550)
	{
		TCNT0=0;
		g_timer_count=0;
		g_sensor_start=0;
		g_rising_edge=0;
	}

}


