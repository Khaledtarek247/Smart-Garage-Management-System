/*
 * TIMER2.c
 *
 * Created: 5/15/2024 7:48:44 PM
 *  Author: Hossam Eldin Omar
 */ 
#define F_CPU 8000000UL
#include "std_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void timer2_overflow_mode(void)
{
	sei();
	TCCR2=0X07; // ENABLE TIMER2 IN OVERFLOW MODE WITH 1024 PRESCALING
	SET_BIT(TIMSK,TOIE2); // ENABLE TIMER 2 OVERFLOW INTERRUPT
}