// lcd_defines.h
// lcd command macros

//lcd_defines.h header gaurds
#ifndef _LCD_DEFINES_H
#define _LCD_DEFINES_H

// lcd command macros 
#define LCD_CLR				0x01   // lcd clear
#define GOTO_LINE1_POS0		0x80   // cursor at line 1 position 0
#define GOTO_LINE2_POS0		0xC0   // cursor at line 2 position 0
#define	MODE_8BIT_2LINE		0x38   // LCD MODE 8 BIT 2 LINE
#define	SHIFT_CUR_RIGHT		0x06   // SHIFT LCD CURSOR TO RIGHT
#define	DISP_ON_CUR_ON		0x0E   // DISPLAY ON CURSOR ON

// lcd pin configuration
#define RS			16	 // port 0.16		lcd pin RS, registor select	pin
#define EN			17	 // port 0.17		lcd pin EN, latch enable pin
#define RW			18	 // port 0.18		lcd pin RW, read write select pin
#define LCD_DATA	8	 // port 0.8-0.15	lcd data pins

#endif
