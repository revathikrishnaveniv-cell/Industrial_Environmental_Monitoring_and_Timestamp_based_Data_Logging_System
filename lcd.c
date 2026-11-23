// lcd.c
// lcd function definitions
#include<LPC21xx.h>
#include"delay.h"		// delay generation header inclusion
#include"lcd.h"			// lcd function declaration header inclusion
//#include"lcd_defines.h"

void lcd_write(u8 data)		// write 1 byte data on lcd
{
	WRITEBYTE(IOPIN0,LCD_DATA,data);   // write 8 bit data on data pins p0.8 - 0.15
	IOSET0=1<<EN;		// port 0.17 set pin EN 
	delay_us(1);	    // latching delay 1 us
	IOCLR0=1<<EN;		// port 0.17 clear pin EN
	delay_ms(2);		// delay 2 ms
}
void lcd_cmd(u8 cmd)	// write command on lcd
{
	IOCLR0=1<<RS;		// port 0.16 clear pin RS for command
	lcd_write(cmd);
}
void lcd_init()			// lcd initialization
{
	WRITEBYTE(IODIR0,LCD_DATA,0xFF);	// p0.8-0.15	set lcd data pin as output pins
	IODIR0|=((1<<RS)|(1<<EN));			// p0.16 & 0.17	set RS & En pins as output pins
	// IODIR0|=1<<RW; 					// p0.18 		set RW pin as output pin
	lcd_cmd(0X30);		// check unknown mode of lcd
	delay_ms(15);	   // powen up delay for lcd
	lcd_cmd(0X30);	   // check unknown mode of lcd
	delay_ms(4);	   // 4.1 ms delay
	delay_us(100);
	lcd_cmd(0X30);			// check unknown mode of lcd
	delay_us(100);				// 100 us delay
	lcd_cmd(MODE_8BIT_2LINE);		// mode 8 bit 1 line
	lcd_cmd(DISP_ON_CUR_ON); 		// display on cursor on
	lcd_cmd(SHIFT_CUR_RIGHT);		// shift cursor to right
	lcd_cmd(LCD_CLR);				// clear display
}
void lcd_char(u8 ch)	 // write character on lcd
{
	IOSET0=1<<RS;		// port 0.16 set pin RS to send character
	lcd_write(ch);
}
void lcd_string(u8* str)  // write string on lcd
{
	while(*str)
		lcd_char(*str++);
}



void lcd_goto(u8 row,u8 col)	// move cursor
{
	if(row==0)
		lcd_cmd(GOTO_LINE1_POS0+col);
	else
		lcd_cmd(GOTO_LINE2_POS0+col);
}
void lcd_row(u8 row,u8* str)	// write one full row, extra characters are filled with spaces
{
	u8 i=0;
	lcd_goto(row,0);
	while(str[i] && i<16)
		lcd_char(str[i++]);
	while(i<16)
	{
		lcd_char(' ');
		i++;
	}
}
