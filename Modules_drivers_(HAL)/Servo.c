/*
 * Servo.c
 *
 * Created: 5/9/2024 9:14:53 PM
 *  Author: Hossam Eldin Omar
 */ 
#include "DIO.h"

Servo_init(char port, char pin)
{
	DIO_vsetPINDir(port,pin,1);
}

Servo_move_degree(double value_dgr)
{	
	timer1_fast_PWM_wave(1.4999 + (value_dgr*0.0055555555555555));
}