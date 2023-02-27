/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the AVR UART driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#include "../mcu_config/private.h"
#include "uart.h"
#include "../mcu_config/common_macros.h"

void UART_init(const UART_ConfigType *Config_Ptr)
{
	uint16 ubrr_value;

	UCSRA = (1<<U2X);

	UCSRB= (1<<TXEN) | (1<<RXEN)

			| ( GET_BIT((Config_Ptr->bit_data) ,2 ) <<UCSZ2);

	UCSRC= (1<<URSEL)

			 | ( GET_BIT((Config_Ptr->bit_data) ,0 ) <<UCSZ0) | ( GET_BIT((Config_Ptr->bit_data) ,1 ) <<UCSZ1)
		     | (GET_BIT((Config_Ptr->parity) , 0)<< UPM0)
			 | (GET_BIT((Config_Ptr->parity) , 1)<< UPM1)
			 | ((Config_Ptr->stop_bit) << USBS);


	ubrr_value=(uint16) ((F_CPU / ((Config_Ptr->baud_rate)* 8UL)) -1);

	UBRRH =ubrr_value>>8;
	UBRRL =ubrr_value;
}


void UART_sendByte(uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	UDR=data;
}


uint8 UART_recieveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	return UDR;
}


void UART_sendString(const uint8 *str)
{
	while(*str != '\0')
	{
		UART_sendByte(*str);
		str++;
	}
}


void UART_sendDecimal(uint32 ch)
{
	uint32 Local_u8Reversed = 1;

	if(0 == ch)
	{
		UART_sendByte('0');
	}

	/* ch=1234
	 *
	 * Local_u8Reversed =4321
	 */
	while(0 != ch){

		Local_u8Reversed = ((Local_u8Reversed * 10) + (ch % 10));
		ch /= 10;
	}

	/* '1'=49
	 * (1)Local_u8Reversed =4321
	 * (2)Local_u8Reversed =432
	 * (3)Local_u8Reversed =43
	 * (4)Local_u8Reversed =4
	 * (5)Local_u8Reversed =0
	 */
	while(1 != Local_u8Reversed)
	{

		UART_sendByte((Local_u8Reversed % 10 ) + 48);
		Local_u8Reversed /= 10;
	}
}



void UART_receiveString(uint8 *str)
{
	uint8 i=0;

	str[i]=UART_recieveByte();

	while(str[i] != '#')
	{
		i++;
		str[i]=UART_recieveByte();
	}
	str[i]='\0';
}
