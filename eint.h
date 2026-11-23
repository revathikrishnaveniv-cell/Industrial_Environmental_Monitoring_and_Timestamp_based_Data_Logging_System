// eint.h
#ifndef _EINT_H
#define _EINT_H
#include"types.h"
extern volatile u8 eint_flag;	// set to 1 by interrupt when button is pressed
void eint_init(void);
void eint_clear(void);			// clear flag and pending interrupt
#endif
