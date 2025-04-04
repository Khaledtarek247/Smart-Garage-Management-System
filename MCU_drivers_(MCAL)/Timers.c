/*
 * Timer0.c
 *
 * Created: 5/4/2024 2:44:06 PM
 *  Author: Hossam Eldin Omar
 */ 
#define F_CPU 8000000UL
#include "std_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
void timer0_CTC_init_interrupt(void)
{
	SET_BIT(TCCR0,WGM01); 
	// CTC MODE SELECTED
	
	OCR0=80;
	// WHEN USING THE F_CPU = 8MHz IT TAKES 10ms UNTIL INTERRUPTED BY THE ISR
	
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	// PRESCALER SET TO 1024
	
	sei();
	SET_BIT(TIMSK,OCIE0);
	// INTERRUPT ENABLED 
		
}
void timer1_fast_PWM_wave(double value)
{
	SET_BIT(DDRD,5);
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1A,WGM11);
	// Timer 1 set to fast PWM mode and its TOP is the ICR1 registers
	OCR1A = value * 1000; // To calculate time values in milli seconds as the clock source is prescaled to 1MHz (It takes 1?s to increment the TCNT by 1)
	ICR1 = 19999; // For the servo motor as the signal fed to it is required to be of 20 ms Periodic Time (19999 as TCNT1 is cleared in the next clk cycle)
	SET_BIT(TCCR1B,CS11);
	// Prescaler = 8 as I'm using the 8MHz internal RC
	SET_BIT(TCCR1A,COM1A1);
	// Clear OC1A on compare match, OC1A at BOTTOM (TOP) (non-inverting mode)
	
}
