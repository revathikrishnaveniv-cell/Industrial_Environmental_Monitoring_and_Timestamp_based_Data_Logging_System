// eint.c
// push button on p0.20 = EINT3 (VIC channel 17), falling edge
#include<LPC21xx.h>
#include"defines.h"
#include"project_defines.h"
#include"eint.h"

volatile u8 eint_flag=0;

void eint3_isr(void) __irq		// interrupt service routine :- only set flag, work is done in main
{
	eint_flag=1;
	EXTINT=(1<<3);				// clear EINT3 interrupt flag
	VICVectAddr=0;				// end of interrupt
}
void eint_init(void)
{
	PINSEL1=(PINSEL1&~(3<<8))|(3<<8);	// p0.20 = EINT3
	EXTMODE|=(1<<3);					// edge sensitive
	EXTPOLAR&=~(1<<3);					// falling edge
	EXTINT=(1<<3);
	VICVectAddr0=(u32)eint3_isr;		// ISR address
	VICVectCntl0=0x20|17;				// enable slot 0, source = EINT3
	VICIntEnable=(1<<17);				// enable EINT3 in VIC
}
void eint_clear(void)
{
	eint_flag=0;
	EXTINT=(1<<3);
}
