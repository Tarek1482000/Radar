/*******************************************************************************
 *
 * Module: Radar
 *
 * File Name: radar.c
 *
 * Description: Source file for the AVR  Radar application
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#include "../HAL/servo_motor.h"
#include "../MCAL/uart.h"
#include "../HAL/ultrasonic_timer0.h"
#include "../HAL/lcd.h"
#include <util/delay.h>

void main(void)
{
	uint8 servo_angle=0,detected_distance=0 ;

	UART_ConfigType UartConfig_Ptr={EIGHT_BIT,DISABLE_PARITY,ONE_STOP_BIT,BAUD9600};

	LCD_init();

	UART_init(&UartConfig_Ptr);

	ServoMotor_Init();

	Ultrasonic_init();

	LCD_displayStringRowColumn(0, 5, "Welcome");
	LCD_displayStringRowColumn(1, 0, "Tarek's System");
	LCD_displayStringRowColumn(2, 0, "Servo Angle : ");
	LCD_displayStringRowColumn(3, 0, "Detected :   cm");

	for(;;)
	{
		/*
		 * rotate the motor from angle 10 to 170
		 * send the angle by UART
		 * send the distance calculated by ULTRASONIC
		 * view servo angle and me
		 */

		for(servo_angle=10 ;servo_angle<170;servo_angle++)
		{
			SERVO_set_angle(servo_angle);


			UART_sendDecimal(servo_angle);
			UART_sendByte(' ');
			UART_sendByte(',');
			detected_distance=Ultrasonic_readDistance();
			UART_sendByte('.');
			UART_sendByte(' ');


			/*
			 * LCD display SERVO angle
			 */
			LCD_moveCursor(2,13);
			if(servo_angle >=100)
			{
				LCD_intgerToString(servo_angle);
			}
			else if(servo_angle<100)
			{
				LCD_displayCharacter(' ');
				LCD_intgerToString(servo_angle);
			}


			/*
			 * LCD display measured distance
			 */
			LCD_moveCursor(3,10);
			if(detected_distance >= 10)
			{
				LCD_intgerToString(detected_distance);
			}
			else if(detected_distance < 10)
			{
				LCD_displayCharacter(' ');
				LCD_intgerToString(detected_distance);
			}


		}

		/*
		 * return the motor from angle 170 to 10
		 * send the angle by UART
		 * send the distance calculated by ULTRASONIC
		 */
		for(servo_angle=170 ;servo_angle>10;servo_angle--)
		{
			SERVO_set_angle(servo_angle);


			UART_sendDecimal(servo_angle);
			UART_sendByte(' ');
			UART_sendByte(',');
			detected_distance=Ultrasonic_readDistance();
			UART_sendByte('.');
			UART_sendByte(' ');


			/*
			 * LCD display SERVO angle
			 */
			LCD_moveCursor(2,13);
			if(servo_angle >=100)
			{
				LCD_intgerToString(servo_angle);
			}
			else if(servo_angle<100)
			{
				LCD_displayCharacter(' ');
				LCD_intgerToString(servo_angle);
			}


			/*
			 * LCD display measured distance
			 */
			LCD_moveCursor(3,10);
			if(detected_distance >= 10)
			{
				LCD_intgerToString(detected_distance);
			}
			else if(detected_distance < 10)
			{
				LCD_displayCharacter(' ');
				LCD_intgerToString(detected_distance);
			}
		}
	}
}
