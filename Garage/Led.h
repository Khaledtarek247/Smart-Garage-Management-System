/*
 * Led.h
 *
 * Created: 10/24/2023 8:11:10 AM
 *  Author: user
 */ 


#ifndef LED_H_
#define LED_H_

void led_vinit(unsigned char port ,unsigned char pin);

void led_vturnOn(unsigned char port ,unsigned char pin);

void led_vturnOff(unsigned char port ,unsigned char pin);

void led_vtoggle(unsigned char port ,unsigned char pin);

#endif /* LED_H_ */