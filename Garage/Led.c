/*
 * Led.c
 *
 * Created: 10/24/2023 8:15:26 AM
 *  Author: user
 */ 
#include "DIO.h"
void led_vinit(unsigned char port ,unsigned char pin)
{
	DIO_vsetPINDir(port,pin,1);
}
void led_vturnOn(unsigned char port ,unsigned char pin)
{
	DIO_vwritePIN(port,pin,1);
}
void led_vturnOff(unsigned char port ,unsigned char pin)
{
	DIO_vwritePIN(port,pin,0);
}
void led_vtoggle(unsigned char port ,unsigned char pin)
{
	DIO_vtogglePIN(port,pin);
}