// pll.c
// pll setup :- use only if startup file does not already set 60 MHz (USE_PLL_INIT)
#include<LPC21xx.h>
#include"pll.h"

void pll_init(void)
{
	PLLCFG=0x24;			// M=5 (4), P=2 (01<<5)
	PLLFEED=0xAA;PLLFEED=0x55;
	PLLCON=0x01;			// enable pll
	PLLFEED=0xAA;PLLFEED=0x55;
	while(!(PLLSTAT&(1<<10)));	// wait for pll lock
	MAMCR=0;MAMTIM=4;MAMCR=2;	// flash memory accelerator
	PLLCON=0x03;			// connect pll
	PLLFEED=0xAA;PLLFEED=0x55;
	VPBDIV=0x00;			// pclk = cclk/4
}
