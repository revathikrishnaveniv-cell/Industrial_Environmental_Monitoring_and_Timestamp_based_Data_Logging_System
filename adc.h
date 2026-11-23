// adc.h
#ifndef _ADC_H
#define _ADC_H
#include"types.h"
void adc_init(void);
u32  adc_read(void);		// one conversion, result 0 - 1023
#endif
