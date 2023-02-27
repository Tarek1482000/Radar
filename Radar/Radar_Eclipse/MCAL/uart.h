 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the AVR UART driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../mcu_config/std_types.h"


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	FIVE_BIT , SIX_BIT , SEVEN_BIT , EIGHT_BIT  ,NINE_BIT=7

}UART_BitData;


typedef enum
{
	DISABLE_PARITY,REVERSED,EVEN_PARITY,ODD_PARITY

}UART_Parity;


typedef enum
{
	ONE_STOP_BIT , TWO_STOP_BIT

}UART_StopBit;


typedef enum
{

	BAUD9600=9600

}UART_BaudRate;


typedef struct{
UART_BitData bit_data;
UART_Parity parity;
UART_StopBit stop_bit;
UART_BaudRate baud_rate;
}UART_ConfigType;




/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr);



/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(uint8 data);


/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);


/*
 * Description :
 * Send the required decimal number through UART to the other UART device.
 */
void UART_sendDecimal(uint32 ch);


/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *str);


/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *str);

#endif /* UART_H_ */
