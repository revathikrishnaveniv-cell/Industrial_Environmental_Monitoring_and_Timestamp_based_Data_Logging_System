// keypad.h
// 4x4 matrix keypad function declarations
#ifndef _KEYPAD_H
#define _KEYPAD_H
#include"types.h"
void keypad_init(void);
u8   keypad_scan(void);		// key now pressed, 0 if no key
u8   keypad_getkey(void);	// debounced, gives key only once per press, 0 if no key
#endif
