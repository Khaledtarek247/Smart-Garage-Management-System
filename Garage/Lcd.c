/*
 * LCd.c
 *
 * Created: 11/24/2023 2:42:42 PM
 *  Author: user
 */ 
#define F_CPU 8000000UL
#include "Lcd.h"
#include "DIO.h"
#include <util/delay.h>
void lcd_vinit(void)
{
	_delay_ms(200);
	#if defined eight_bit_mode
	DIO_vsetPINDir('A',0,1);
	DIO_vsetPINDir('A',1,1);
	DIO_vsetPINDir('A',2,1);
	DIO_vsetPINDir('A',3,1);
	DIO_vsetPINDir('A',4,1);
	DIO_vsetPINDir('A',5,1);
	DIO_vsetPINDir('A',6,1);
	DIO_vsetPINDir('A',7,1);
	DIO_vsetPINDir('B',EN,1);
	DIO_vsetPINDir('B',RW,1);
	DIO_vsetPINDir('B',RS,1);
	// SET THE LCD TO THE WRITE MODE
	DIO_vwritePIN('B',RW,0);
	//SEND THE HEX 0X38 TO THE IR TO INITIALIZE THE 8-BIT MODE
	lcd_vsend_cmd(EIGHT_BITS);
	_delay_ms(1);
	lcd_vsend_cmd(CURSOR_ON_DISPLAY_BLINKING);
	_delay_ms(1);
	lcd_vsend_cmd(CLR_SCREEN);
	_delay_ms(10);
	lcd_vsend_cmd(ENTRY_MODE);
	_delay_ms(1);
	
	#elif defined four_bit_mode
	DIO_vsetPINDir('A',4,1);
	DIO_vsetPINDir('A',5,1);
	DIO_vsetPINDir('A',6,1);
	DIO_vsetPINDir('A',7,1);
	DIO_vsetPINDir('B',EN,1);
	DIO_vsetPINDir('B',RW,1);
	DIO_vsetPINDir('B',RS,1);
	// SET THE LCD TO THE WRITE MODE
	DIO_vwritePIN('B',RW,0);
	//RETURNS THE CURSOR TO THE TOP LEFT CORNER OF THE LCD WITHOUT CHANGING THE DDRAM DATA
	lcd_vsend_cmd(RETURN_HOME);
	_delay_ms(10);
	lcd_vsend_cmd(FOUR_BITS);
	_delay_ms(1);
	lcd_vsend_cmd(CURSOR_ON_DISPLAY_BLINKING);
	_delay_ms(1);
	lcd_vsend_cmd(CLR_SCREEN);
	_delay_ms(10);
	lcd_vsend_cmd(ENTRY_MODE);
	_delay_ms(1);	
	#endif
}

static void send_falling_edge(void)
{
	DIO_vwritePIN('B',EN,1);
	_delay_ms(2);
	DIO_vwritePIN('B',EN,0);
	_delay_ms(2);
}

void lcd_vsend_cmd(char cmd)
{
	#if defined eight_bit_mode
	DIO_vwritePORT('A',cmd);
	DIO_vwritePIN('B',RS,0);
	send_falling_edge();
	
	#elif defined four_bit_mode
	DIO_vwrite_high_nibble('A',cmd>>4);
	DIO_vwritePIN('B',RS,0);
	send_falling_edge();
	DIO_vwrite_high_nibble('A',cmd);
	DIO_vwritePIN('B',RS,0);
	send_falling_edge();
	#endif
	_delay_ms(1);
}

void lcd_vsend_char(char data)
{
	#if defined eight_bit_mode
	DIO_vwritePORT('A',data);
	DIO_vwritePIN('B',RS,1);
	send_falling_edge();
	
	#elif defined four_bit_mode
	DIO_vwrite_high_nibble('A',data>>4);
	DIO_vwritePIN('B',RS,1);
	send_falling_edge();
	DIO_vwrite_high_nibble('A',data);
	DIO_vwritePIN('B',RS,1);
	send_falling_edge();
	#endif
	_delay_ms(1);
}

void lcd_vsend_string(char *data)
{
	for(int i=0;data[i]!='\0';i++)
	{
		lcd_vsend_char(data[i]);
	}
}

void lcd_CLRscreen(void)
{
	lcd_vsend_cmd(CLR_SCREEN);
	_delay_ms(10);
}

void lcd_move_cursor(char row,char column)
{
	char data;
	if(row>1||row<0||column>15||column<0)
	{
		data=0x80;
	}
	else if(row==0)
	{
		data=0x80+column;
	}
	else if(row==1)
	{
		data=0xc0+column;
	}
	//SETS THE ADDRESS COUNTER THAT POINT AT THE DDRAM TO THE SPECIFIED LOCATION ON THE LCD
	lcd_vsend_cmd(data);
	_delay_ms(1);
}
