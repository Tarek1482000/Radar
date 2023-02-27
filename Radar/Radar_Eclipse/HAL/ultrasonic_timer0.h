 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the AVR ULTRASONIC driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "../mcu_config/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ULTRASONIC_TRIGGER_PORT_ID           PORTC_ID
#define ULTRASONIC_TRIGGER_PIN_ID            PIN0_ID




/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/


/*
 * Set ultrasonic setting
 * First initialize Icu
 * call back edge processing function
 * Set Triggre pin output
 */

void Ultrasonic_init(void);

/*
 * Send signal for 10us
 */

void Ultrasonic_Trigger(void);

/*
 * send 10us for ultrasonic trigger pin
 * wait until calculate edge  and calculate distance
 *return measured distance
 */
uint8 Ultrasonic_readDistance(void);



void Ultrasonic_edgeProcessing(void);



void Ultrasonic_detectedge(void);

#endif /* ULTRASONIC_H_ */
