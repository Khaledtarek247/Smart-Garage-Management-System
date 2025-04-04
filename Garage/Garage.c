/*
 * Garage.c
 *
 * Created: 5/10/2024 9:59:59 AM
 *  Author: Hossam Eldin Omar
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Lcd.h"
#include "Servo.h"
#include "Sonic_INT0.h"
#include "TIMER2.h"
#include "Led.h"
#include "UART.h"
#include "Garage_configuration.h"
volatile unsigned int counter; // for timer 2 overflow ISR
int main(void)
{
	MCUCSR |=1<<JTD;
	MCUCSR |=1<<JTD;
	UART_vinit(9600);
	unsigned char x; // To read received data from UDR register
	led_vinit('D',7); //Gate indicator
	DIO_vsetPINDir('A',1,1); // BUZZER for fire alarms
	DIO_vsetPINDir('D',4,0); // Entrance gate
	DIO_vsetPINDir('D',6,0);// Exit gate
	DIO_vsetPINDir('C',2,0); // PL_1
	DIO_vsetPINDir('C',4,0); //PL_2
	//Pl_3 is the ultrasonic sensor which is connected to INT0 PORT D, PIN 2 (ECHO PIN) TRIGGER PIN = PORTD, PIN 3
	unsigned short temperature; // Temperature sensor connected to ADC0 PORT A, PIN 0 
	unsigned char distance_PL1;
	unsigned char distance_PL2;
	unsigned short distance_PL3;
	int shaft_pos;
	unsigned char ParkingCounter_PL1 = 0;
	unsigned char ParkingCounter_PL2 = 0;
	unsigned char ParkingCounter_PL3 = 0;
	unsigned char Free_slots = 3;
	unsigned char Entering_car = 0;
	unsigned char latest_slot_update = 0;
	unsigned char gate_closing=0;
	unsigned char flagIN = 0; // Flag raised when a car exits the garage
	unsigned char flagOUT = 0; // Flag raised when a car enters the garage
	UltraSOnic_vinit('D',3);
	ADC_vinit(); //
	// Servo motor is already connected to PORT D, PIN 5 the OC1A (output capture pin for timer 1 )
	lcd_vinit();
	lcd_vsend_string("MEASUREMENTS");
	_delay_ms(3000);
	led_vturnOn('D',7);
	for(shaft_pos=0;shaft_pos<=90;shaft_pos++)
	{
		Servo_move_degree(shaft_pos);
		 _delay_ms(5);
	}
	led_vturnOff('D',7);		 
	for(shaft_pos=90;shaft_pos>=0;shaft_pos--)
	{
		Servo_move_degree(shaft_pos);
		_delay_ms(5);
	}
	lcd_CLRscreen();
	timer2_overflow_mode();
	
	
    while(1)
    {
			temperature=(ADC_u16read()*0.25);
			distance_PL3 = UltraSOnic_vtrigger('D', 3);
			distance_PL1 = DIO_readPIN('C',2);
			distance_PL2 = DIO_readPIN('C',4);
		   if(temperature >= 60)
		   {
				DIO_vwritePIN('A',1,1); // Turn on buzzer
				led_vturnOn('D',7);
				for(shaft_pos=0;shaft_pos<=90;shaft_pos++)
				{
					
					Servo_move_degree(shaft_pos);
					_delay_ms(5);
				}   
				lcd_CLRscreen();
				lcd_vsend_string("Fire Alarm !");
				while(ADC_u16read()*0.25 >= 60);
				DIO_vwritePIN('A',1,0); // Turn off buzzer
				lcd_CLRscreen();
				while (DIO_readPIN('D',4)==0 || DIO_readPIN('D',6)==0);
				led_vturnOff('D',7);
					for(shaft_pos=90;shaft_pos>=0;shaft_pos--)
					{
							
						Servo_move_degree(shaft_pos);
						_delay_ms(5);
					}					
		   }
		   if(distance_PL3 <=10 )
		   {
			   if(distance_PL3 != 1)
			   {
					ParkingCounter_PL3 = 0;
			   }				   			   
		   }
		   else
		   {
			   ParkingCounter_PL3 = 1;
		   }
		   if (!distance_PL1)
		   {
			   ParkingCounter_PL1 = 0;
		   }
		   else
		   {
			   ParkingCounter_PL1 = 1;
		   }
		   if (!distance_PL2)
		   {
			   ParkingCounter_PL2 = 0;
		   }
		   else
		   {
			   ParkingCounter_PL2 = 1;
		   }
		   Free_slots = ParkingCounter_PL1 + ParkingCounter_PL2 + ParkingCounter_PL3 - Entering_car;
		  if(counter == 92 && Free_slots != latest_slot_update)
		   {
			   Entering_car=0;
			   latest_slot_update = Free_slots;
			   lcd_CLRscreen();
			   lcd_move_cursor(0,0);
			   lcd_vsend_string("Free slots : ");
			   lcd_move_cursor(0,12);
			   if(Free_slots>3)
			   {
				   Free_slots=3;
			   }
			   else if (Free_slots<0)
			   {
				   Free_slots=0;
			   }
			   lcd_vsend_char(Free_slots+48);
			   lcd_move_cursor(1,0);
			   lcd_vsend_string("temp = ");
			   lcd_vsend_char(temperature/10 +48);
			   lcd_vsend_char(temperature%10 +48);
		   }	
		   #if defined NO_UART	   
		   
		     if(DIO_readPIN('D',4)==0) 
		     {
			     gate_closing=0;
			     if(flagIN > 0) // A car has passed the exit gate, so the entrance sensor has detected a car which is still leaving
				 {
					 latest_slot_update = Free_slots+1;
					 led_vturnOff('D',7);
				     for(shaft_pos=90;shaft_pos>=0;shaft_pos-=1){
					     Servo_move_degree(shaft_pos);
					     _delay_ms(5);
				     }
				     while(DIO_readPIN('D',4)==0); // In case the car remains in front of the entrance sensor while leaving
				     flagIN=0; // The car passed the entrance sensor (gate)
				     gate_closing=1;
				 }				 
			     if((Free_slots>0)&&(gate_closing==0)) // There are free parking_slots and a car is entering
			     {
					 lcd_CLRscreen();
					 lcd_move_cursor(0,0);
					 lcd_vsend_string("Welcome :)");
					 Entering_car++; // In case two cars are entering back to back and there is only one free parking slot
				     flagOUT++; // A car has passed the entrance sensor
					 led_vturnOn('D',7);
				     for (shaft_pos = 0; shaft_pos <= 90; shaft_pos +=1 ) {
					     Servo_move_degree(shaft_pos);
					     _delay_ms(5);
				     }
				     while(DIO_readPIN('D',6)); // Do nothing until the exit sensor detects a car
			     }
			     else if((Free_slots<=0))
				 {
				     lcd_CLRscreen();
				     lcd_vsend_string("No free slots :(");
					 while(!DIO_readPIN('D',4)); // Do nothing until the car leaves
			     }
		     }		   
		   if(DIO_readPIN('D',6)==0)
		   {
			   if (flagOUT>0) // A car has passed the entrance gate, so the exit sensor has detected a car which is still entering
			   {
				   led_vturnOff('D',7);
				   for(shaft_pos=90;shaft_pos>=0;shaft_pos-=1){
					   Servo_move_degree(shaft_pos);
					   _delay_ms(5);
				   }
				   while(!DIO_readPIN('D',6)); // In case the car remains in front of the exit sensor while entering
				   flagOUT=0;
			   }

			   else if(flagOUT==0) // No car entered, so the sensor has detected a leaving car
			   {
				   lcd_CLRscreen();
				   lcd_move_cursor(0,0);
				   lcd_vsend_string("Bye :)");
				   flagIN++; // A car has passed the exit sensor
				   led_vturnOn('D',7);
				   for(shaft_pos=0;shaft_pos<=90;shaft_pos+=1){
					   Servo_move_degree(shaft_pos);
					   _delay_ms(5);
				   }
				   while(DIO_readPIN('D',4)); // Do nothing until the entrance sensor detects a car
			   }
		   }
		   #elif defined UART
		   if(DIO_readPIN('D',4)==0)
		   {
			   //while(UART_u8receiveData()!= 'c' && UART_u8receiveData()!= 'o');
			   if(flagIN > 0)
			   {
				   x = UART_u8receiveData();
					if(x == 'c')
					{
						latest_slot_update = Free_slots+1;
						led_vturnOff('D',7);
						for(shaft_pos=90;shaft_pos>=0;shaft_pos-=1){
							Servo_move_degree(shaft_pos);
							_delay_ms(5);
						}
						flagIN = 0;
						while(DIO_readPIN('D',4)==0); // In case the car remains in front of the entrance sensor while leaving
					}
			   }			   
			   else if(Free_slots > 0 && flagIN == 0 ) // A new car is entering
			   {
				   UART_vsendString("Welcome");
				   x = UART_u8receiveData();
				   if(x== 'o')
				   {
					   flagOUT = 1;
					   lcd_CLRscreen();
					   lcd_move_cursor(0,0);
					   lcd_vsend_string("Welcome :)");
					   Entering_car++; // In case two cars are entering back to back and there is only one free parking slot
					   led_vturnOn('D',7);
					   for(shaft_pos=0;shaft_pos<=90;shaft_pos+=1){
						   Servo_move_degree(shaft_pos);
						   _delay_ms(5);
					   }
					   while(DIO_readPIN('D',6)); // Do nothing until the exit sensor detects a car
				   }
			   }
			   else if((Free_slots<=0))
			   {
				   lcd_CLRscreen();
				   lcd_vsend_string("No free slots :(");
				   while(!DIO_readPIN('D',4)); // Do nothing until the car leaves
			   }				   				   
		   }
		   if(DIO_readPIN('D',6)==0)
		   {
			   //while(UART_u8receiveData()!= 'c' || UART_u8receiveData()!= 'o');
			   if(flagOUT > 0)
			   {
				   x = UART_u8receiveData();
				   if(x == 'c')
				   {
					   led_vturnOff('D',7);
					   for(shaft_pos=90;shaft_pos>=0;shaft_pos-=1){
						   Servo_move_degree(shaft_pos);
						   _delay_ms(5);
					   }
					   flagOUT = 0;
					   while(!DIO_readPIN('D',6)); // In case the car remains in front of the exit sensor while entering
				   }
			   }			   
			   else if(flagOUT == 0) // A car  is leaving the garage
			   {
					UART_vsendString("Bye");
					x = UART_u8receiveData();   
				   if(x == 'o')
				   {
					   flagIN = 1;
					   lcd_CLRscreen();
					   lcd_move_cursor(0,0);
					   lcd_vsend_string("Bye :)");
					   led_vturnOn('D',7);
					   for(shaft_pos=0;shaft_pos<=90;shaft_pos+=1){
						   Servo_move_degree(shaft_pos);
						   _delay_ms(5);
					   }
					   while(DIO_readPIN('D',4)); // Do nothing until the entrance sensor detects a car
				   }					   
			   }
		   }
		   #endif
		   
    }
	
}
ISR(TIMER2_OVF_vect)
{
	if(counter==92)
	{
		TCNT2=0;
		counter = 0;
	}
	counter++;
}