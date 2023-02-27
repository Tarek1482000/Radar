/*
 * int0.h
 *
 *  Created on: Feb 24, 2023
 *      Author: tarek
 */

#ifndef MCAL_INT0_H_
#define MCAL_INT0_H_


#include "../mcu_config/std_types.h"

void INT0_init(void);



void INT0_setCallBack(void(*a_ptr)(void));


#endif /* MCAL_INT0_H_ */
