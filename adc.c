// adc.c
// adc0 channel 1 (p0.28) function definitions
// ADCR  : SEL bits 7:0, CLKDIV bits 15:8, PDN bit 21, START bits 26:24
// ADDR  : global data register, DONE bit 31, RESULT bits 15:6
// (if your header has no ADCR/ADDR use AD0CR/AD0GDR from LPC214x.h)
#include<LPC21xx.h>
#include"defines.h"
#include"project_defines.h"
#include"adc.h"

void adc_init(void)
{
	PCONP|=(1<<12);									// power for adc0
	PINSEL1=(PINSEL1&~(3<<24))|(1<<24);				// p0.28 = AD0.1
	ADCR=(1<<ADC_CHANNEL)|(ADC_CLKDIV<<8)|(1<<21);	// select channel, clock, power on adc
}
u32 adc_read(void)
{
	u32 wait=100000;
	ADCR&=~(7<<24);
	ADCR|=(1<<24);									// start conversion now
	while(READBIT(ADDR,31)==0 && wait)				// wait for DONE bit
		wait--;
	ADCR&=~(7<<24);									// stop
	return (ADDR>>6)&0x3FF;							// 10 bit result
}
