/*
 * IncFile1.h
 *
 * Created: 10/2/2023 9:54:36 PM
 *  Author: user
 */ 


#ifndef DIO_H_
#define DIO_H_
void DIO_vsetPINDir(unsigned char port,unsigned char pin, unsigned char dir);

void DIO_vwritePIN(unsigned char port,unsigned char pin, unsigned char valuee);

void DIO_vtogglePIN(unsigned char port,unsigned char pin);

unsigned char DIO_readPIN(unsigned char port,unsigned char pin);

void DIO_vsetPORTDIR(unsigned char port,unsigned char dir);

void DIO_vwritePORT(unsigned char port,unsigned char valuee);

unsigned char DIO_readPORT(unsigned char port);

void DIO_vtogglePORT(unsigned char port);

void DIO_vconnectpullup(unsigned char port ,unsigned char pin, unsigned char connect_pullup);
void DIO_vwrite_low_nibble(unsigned char port , unsigned char valuee);
void DIO_vwrite_high_nibble(unsigned char port , unsigned char valuee);
#endif /* DIO_H_x */