 /******************************************************************************
 *
 * Module: Timer 1
 *
 * File Name: timer1.h
 *
 * Description: header file for the Timer1 driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

#include "../mcu_config/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK_TIMER1, F_CPU_CLOCK_TIMER1, F_CPU_8_TIMER1, F_CPU_64_TIMER1, F_CPU_256_TIMER1, F_CPU_1024_TIMER1

}Timer1_Prescaler;


typedef enum
{
	NORMAL , CTC=4 ,FAST_PWM_ICR1=14

}Timer1_Mode;

typedef struct
{
	uint16 initial_value; // Start count from this value
	uint16 compare_value; // it will be used in compare mode only.
	uint16 ICR1_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;

}Timer1_ConfigType;



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/




void Timer1_init(const Timer1_ConfigType *Config_Ptr);


void Timer1_deInit(void);

void TIMER1_set_OCR1A(uint16 duty);

void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
