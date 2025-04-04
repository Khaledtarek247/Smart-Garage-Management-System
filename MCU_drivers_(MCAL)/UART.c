/*
 * UART.c
 *
 * Created: 4/28/2024 7:45:50 PM
 *  Author: Hossam Eldin Omar
 */ 
#include "std_macros.h"
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void UART_vinit(unsigned long baudrate)
{
	unsigned short UBRR;
	UBRR=(F_CPU/(16*baudrate))-1;
	UBRRH=(unsigned char)(UBRR>>8);
	UBRRL=(unsigned char)(UBRR);
	//Enable USART sender and receiver
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	//Set it to send 8 bits of data, 1 stop bit, and no parity bits
	UCSRC=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

void UART_vsendData(char data)
{
	//Wait for UDR transmit buffer to be empty 
	while(READ_BIT(UCSRA,UDRE)==0);
	//Send data to UDR transmit buffer
	UDR=data;
}

char UART_u8receiveData(void)
{	
	//Wait for UDR receive buffer to be full
	while(READ_BIT(UCSRA,RXC)==0);
	//Read data from UDR receive buffer
	return UDR;		
}

void UART_vsendString(char *ptr)
{
	while(*ptr!=0)
	{
		UART_vsendData(*ptr);
		ptr++;
		_delay_ms(100);
	}
}