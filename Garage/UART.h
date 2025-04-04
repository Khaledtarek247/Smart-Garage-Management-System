/*
 * UART.h
 *
 * Created: 4/28/2024 7:45:40 PM
 *  Author: Hossam Eldin Omar
 */ 


#ifndef UART_H_
#define UART_H_

void UART_vinit(unsigned long baudrate);

void UART_vsendData(char data);

char UART_u8receiveData(void);

void UART_vsendString(char *data);




#endif /* UART_H_ */