/*
 * CFile1.c
 *
 * Created: 10/2/2023 10:12:41 PM
 *  Author: user
 */ 
#include "std_macros.h"
#include <avr/io.h>
void DIO_vsetPINDir(unsigned char port,unsigned char pin, unsigned char dir)
{
	switch(port)
	{
		case 'A':
		case 'a':
		if (dir==1)
		{
			SET_BIT(DDRA,pin);
		}
		else
		{
			CLR_BIT(DDRA,pin);
		}
		break;
		case 'B':
		case 'b':
		if (dir==1)
		{
			SET_BIT(DDRB,pin);
		}
		else
		{
			CLR_BIT(DDRB,pin);
		}
		break;
		case 'C':
		case 'c':
		if (dir==1)
		{
			SET_BIT(DDRC,pin);
		}
		else
		{
			CLR_BIT(DDRC,pin);
		}
		break;
		case 'D':
		case 'd':
		if (dir==1)
		{
			SET_BIT(DDRD,pin);
		}
		else
		{
			CLR_BIT(DDRD,pin);
		}
		break;
		default:
		break;
		
	}
	
}
void DIO_vwritePIN(unsigned char port,unsigned char pin, unsigned char valuee)
{
	switch(port)
	{
		case 'A':
		case 'a':
		if(valuee==1)
		{
			SET_BIT(PORTA,pin);
		}
		else
		{
			CLR_BIT(PORTA,pin);
		}
		break;
		case 'B':
		case 'b':
		if(valuee==1)
		{
			SET_BIT(PORTB,pin);
		}
		else
		{
			CLR_BIT(PORTB,pin);
		}
		break;
		case 'C':
		case 'c':
		if(valuee==1)
		{
			SET_BIT(PORTC,pin);
		}
		else
		{
			CLR_BIT(PORTC,pin);
		}
		break;
		case 'D':
		case 'd':
		if(valuee==1)
		{
			SET_BIT(PORTD,pin);
		}
		else
		{
			CLR_BIT(PORTD,pin);
		}
		break;
		default:
		break;
	}
}
void DIO_vtogglePIN(unsigned char port,unsigned char pin)
{
	switch(port)
	{
		case 'A':
		case 'a':
		TOG_BIT(PORTA,pin);
		break;
		case 'B':
		case 'b':
		TOG_BIT(PORTB,pin);
		break;
		case 'C':
		case 'c':
		TOG_BIT(PORTC,pin);
		break;
		case 'D':
		case 'd':
		TOG_BIT(PORTD,pin);
		break;
	}
}
unsigned char DIO_readPIN(unsigned char port,unsigned char pin)
{
	unsigned char return_val;
	switch(port)
	{
		case 'A':
		case 'a':
		return_val=READ_BIT(PINA,pin);
		break;
		case 'B':
		case 'b':
		return_val=READ_BIT(PINB,pin);
		break;
		case 'C':
		case 'c':
		return_val=READ_BIT(PINC,pin);
		break;
		case 'D':
		case 'd':
		return_val=READ_BIT(PIND,pin);
		break;
		default:
		break;
	}
	return return_val;
}
void DIO_vsetPORTDIR(unsigned char port,unsigned char dir)
{
	switch(port)
	{
		case 'A':
		case 'a':
		DDRA=dir;
		break;
		case 'B':
		case 'b':
		DDRB=dir;
		break;
		case 'C':
		case 'c':
		DDRC=dir;
		break;
		case 'D':
		case 'd':
		DDRD=dir;
		break;
		default:
		break;
	}
}
void DIO_vwritePORT(unsigned char port,unsigned char valuee)
{
	switch(port)
	{
		case 'A':
		PORTA=valuee;
		break;
		case 'B':
		case 'b':
		PORTB=valuee;
		break;
		case 'C':
		case 'c':
		PORTC=valuee;
		break;
		case 'D':
		case 'd':
		PORTD=valuee;
		break;
		default:
		break;
	}
}
unsigned char DIO_readPORT(unsigned char port)
{
	unsigned char return_val;
	switch(port)
	{
		case 'A':
		case 'a':
		return_val=PINA;
		break;
		case 'B':
		case 'b':
		return_val=PINB;
		break;
		case 'C':
		case 'c':
		return_val=PINC;
		break;
		case 'D':
		case 'd':
		return_val=PINB;
		break;
		default:
		break;
	}
	return return_val;
}
void DIO_vtogglePORT(unsigned char port)
{
	switch(port)
	{
		case 'A':
		case 'a':
		PORTA=~(PORTA); // PORTA=PORTA ^ 0XFF;
		break;
		case 'B':
		case 'b':
		PORTB=~(PORTB); // PORTB=PORTB ^ 0XFF;
		break;
		case 'C':
		case 'c':
		PORTC=~(PORTC); // PORTC=PORTC ^ 0XFF;
		break;
		case 'D':
		case 'd':
		PORTD=~(PORTD); // PORTD=PORTD ^ 0XFF;
		break;
	}
}
void DIO_vconnectpullup(char port ,char pin, char connect_pullup)
{
	switch(port)
	{
		case 'A':
		case 'a':
		if(connect_pullup==1)
		{
			SET_BIT(PORTA,pin);
		}
		else
		{
			CLR_BIT(PORTA,pin);
		}
		break;
		case 'B':
		case 'b':
		if(connect_pullup==1)
		{
			SET_BIT(PORTB,pin);
		}
		else
		{
			CLR_BIT(PORTB,pin);
		}
		break;
		case 'C':
		case 'c':
		if(connect_pullup==1)
		{
			SET_BIT(PORTC,pin);
			
		}
		else
		{
			CLR_BIT(PORTC,pin);
		}
		break;
		case 'D':
		case 'd':
		if(connect_pullup==1)
		{
			SET_BIT(PORTD,pin);
			
		}
		else
		{
			CLR_BIT(PORTD,pin);
		}
		break;
		
	}
}
void DIO_vwrite_low_nibble(unsigned char port , unsigned char valuee)
{
	valuee&=0x0f;
	switch(port)
	{
		case 'A':
		case 'a':
		PORTA&=0xf0;
		PORTA|=valuee;
		break;
		case 'B':
		case 'b':
		PORTB&=0xf0;
		PORTB|=valuee;
		break;
		case 'C':
		case 'c':
		PORTC&=0xf0;
		PORTC|=valuee;
		break;
		case 'D':
		case 'd':
		PORTD&=0xf0;
		PORTD|=valuee;
		break;
		default:
		break;
		
	}
}
void DIO_vwrite_high_nibble(unsigned char port , unsigned char valuee)
{
	valuee<<=4;
	switch(port)
	{
		case 'A':
		case 'a':
		PORTA&=0x0f;
		PORTA|=valuee;
		break;
		case 'B':
		case 'b':
		PORTB&=0x0f;
		PORTB|=valuee;
		break;
		case 'C':
		case 'c':
		PORTC&=0x0f;
		PORTC|=valuee;
		break;
		case 'D':
		case 'd':
		PORTD&=0x0f;
		PORTD|=valuee;
		break;
		default:
		break;
		
	}
}
