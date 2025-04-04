/*
 * Sonic_INT0.c
 *
 * Created: 5/15/2024 3:31:59 PM
 *  Author: Hossam Eldin Omar
 */ 
#define F_CPU 8000000UL
#define SOUND_SPEED 34600 // cm/sec
#include "DIO.h"
#include "Timers.h"
#include "std_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile unsigned char pulse_flag = 0;
volatile unsigned char rising_edge=0;
volatile unsigned int timer_counter=0;
volatile unsigned short distance;

void UltraSOnic_vinit(char trigport,char trigpin)
{
	DIO_vsetPINDir(trigport,trigpin,1); // Set the sensor's trigger pin to be an output pin.
	sei();// Enable global interrupt.
	SET_BIT(GICR,INT0); // Enable interrupt 0.
	SET_BIT(MCUCR,ISC00); // Any logical change on INT0 generates an interrupt request.
}

unsigned short UltraSOnic_vtrigger(char trigport,char trigpin)
{
	if(pulse_flag == 0){
		DIO_vwritePIN(trigport, trigpin,1);
		_delay_us(15);
		DIO_vwritePIN(trigport, trigpin,0);
		pulse_flag=1;
		TCCR0=0X01; // Set timer0 to overflow mode with no prescaler
		SET_BIT(TIMSK,TOIE0); // Enable timer0 interrupt
		return distance;
	}
}
ISR(INT0_vect)
{
	if(pulse_flag == 1){
		if(rising_edge==0){
			TCNT0=0x00;
			rising_edge=1;
			timer_counter=0;
		}
		else
		{
			distance = (((timer_counter*256+TCNT0)*SOUND_SPEED)/(2*F_CPU));  // 2*F_CPU BECAUSE THE SIGNAL TRAVELED FROM THE ULTRASONIC AND THEN BACK TO IT
			_delay_ms(15);
			timer_counter=0;
			rising_edge=0;
		}
	}
}

ISR(TIMER0_OVF_vect)
{	
	timer_counter++;
	if(timer_counter == 1000) // To send a pulse every (1/(8x10^6)*256*1000) 32 milli seconds
	{
		TCNT0=0x00;
		pulse_flag=0;
		rising_edge=0;
		timer_counter=0;
	}
}
