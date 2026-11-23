// keypad.c
// 4x4 keypad: rows p1.16-1.19 (output), columns p1.20-1.23 (input, external pull-up)
#include<LPC21xx.h>
#include"defines.h"
#include"project_defines.h"
#include"delay.h"
#include"keypad.h"

static const u8 keymap[4][4]=
{
	{'1','2','3','4'},
	{'5','6','7','8'},
	{'9','0','*','#'},
	{'A','B','C','D'}
};

void keypad_init(void)
{
	IODIR1|=KEY_ROW_MASK;		// rows as output
	IOSET1=KEY_ROW_MASK;		// all rows high
}
u8 keypad_scan(void)
{
	u8 r,c;
	for(r=0;r<4;r++)
	{
		IOSET1=KEY_ROW_MASK;				// all rows high
		IOCLR1=1<<(KEY_ROW_START+r);		// make one row low
		delay_us(10);
		for(c=0;c<4;c++)
		{
			if(READBIT(IOPIN1,(KEY_COL_START+c))==0)	// column low = key pressed
			{
				IOSET1=KEY_ROW_MASK;
				return keymap[r][c];
			}
		}
	}
	IOSET1=KEY_ROW_MASK;
	return 0;
}
u8 keypad_getkey(void)
{
	static u8 last=0;
	u8 key=keypad_scan();
	if(key!=0 && key!=last)
	{
		delay_ms(20);					// debounce
		if(keypad_scan()==key)
		{
			last=key;
			return key;
		}
		return 0;
	}
	if(key==0)
		last=0;							// key released
	return 0;
}
