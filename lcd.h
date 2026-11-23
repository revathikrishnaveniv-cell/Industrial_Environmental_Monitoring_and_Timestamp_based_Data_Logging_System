// lcd.h
// lcd header file :- lcd function declaration

// lcd.h header gaurds
#ifndef _LCD_H
#define _LCD_H

#include"types.h"			// typedef for datatypes header inclusion
#include"lcd_defines.h"		// lcd macros header inclusion
#include"defines.h"			// macros defines

void lcd_write(u8 data);   	// write data on lcd pins
void lcd_init(void);			// lcd initialization
void lcd_cmd(u8 cmd);		// write command on lcd 
void lcd_char(u8 ch);		// write character on lcd
void lcd_string(u8* str);	// write string on lcd
void lcd_goto(u8 row,u8 col);	// move cursor, row 0/1, col 0-15
void lcd_row(u8 row,u8* str);	// write full 16 char row (fills rest with spaces)

#endif
