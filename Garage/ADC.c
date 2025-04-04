/*
 * ADC.c
 *
 * Created: 4/12/2024 5:29:56 PM
 *  Author: AL AHLAWY
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include "std_macros.h"
void ADC_vinit(void)
{
	SET_BIT(ADCSRA,ADEN); //Enables ADC
	SET_BIT(ADMUX,REFS1); 
	SET_BIT(ADMUX,REFS0); // internal 2.56 volt
	// adjust the ADC clock for 8MHz/64 only 125 KHz needed (Successive approximation input clock frequency between 50kHz and 200kHz to get maximum resolution (10 bits).)
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
}

unsigned short ADC_u16read(void)
{
	unsigned short read_reg;
	SET_BIT(ADCSRA,ADSC); // start conversion
	while(READ_BIT(ADCSRA,ADSC)==1);
	read_reg=ADCL;
	read_reg|=(ADCH<<8);
	return read_reg;
	
	
}