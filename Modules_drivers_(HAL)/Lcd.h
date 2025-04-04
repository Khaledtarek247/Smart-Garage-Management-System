/*
 * Lcd.h
 *
 * Created: 11/24/2023 2:42:33 PM
 *  Author: user
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "DIO.h"
#include "Lcd_configuration.h"
#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAY_ON 0x0e
#define CURSOR_ON_DISPLAY_BLINKING 0x0f
#define RETURN_HOME 0x02
#define  ENTRY_MODE 0x06
#if defined four_bit_mode
#define EN 0
#define RS 1
#define RW 2
#define FOUR_BITS 0x28
#elif defined eight_bit_mode
#define EN 0
#define RS 1
#define RW 2
#define EIGHT_BITS 0x38
#endif
void lcd_vinit(void);
static void send_falling_edge(void);
void lcd_vsend_cmd(char cmd);
void lcd_vsend_char(char data);
void lcd_vsend_string(char *data);
void lcd_CLRscreen(void);
void lcd_move_cursor(char row,char column);


#endif /* LCD_H_ */