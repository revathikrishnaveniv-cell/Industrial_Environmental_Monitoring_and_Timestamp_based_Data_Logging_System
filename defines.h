// defines.h
// common macros

#ifndef _DEFINES_H
#define _DEFINES_H

#define	WRITEBYTE(REG,SBITPOS,DATA) (REG=((REG&~(0xFF<<SBITPOS))|(DATA<<SBITPOS)))
#define SETBIT(REG,BITPOS)			(REG|=(1<<BITPOS))
#define CLRBIT(REG,BITPOS)			(REG&=~(1<<BITPOS))
#define READBIT(REG,BITPOS)			((REG>>BITPOS)&1)

// clock settings (set by startup file / pll_init) :- CHANGE if your board is different
#define FOSC	12000000		// crystal 12 MHz
#define CCLK	60000000		// cpu clock 60 MHz  (PLL M=5)
#define PCLK	15000000		// peripheral clock 15 MHz (CCLK/4)

#endif
