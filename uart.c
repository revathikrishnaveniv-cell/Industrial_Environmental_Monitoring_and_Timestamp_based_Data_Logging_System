// uart.c
// uart0 function definitions, 8 data bits, no parity, 1 stop bit
#include<LPC21xx.h>
#include"defines.h"
#include"uart.h"

void uart0_init(u32 baud)
{
	u32 div;
	PINSEL0=(PINSEL0&~0x0F)|0x05;			// p0.0 = TXD0, p0.1 = RXD0
	div=(PCLK+(8*baud))/(16*baud);			// baud rate divisor (rounded)
	U0LCR=0x83;								// 8N1, DLAB = 1
	U0DLL=div&0xFF;
	U0DLM=(div>>8)&0xFF;
	U0LCR=0x03;								// DLAB = 0
}
void uart0_tx(u8 ch)
{
	while(!(U0LSR&(1<<5)));					// wait till transmit register empty
	U0THR=ch;
}
void uart0_string(char *str)
{
	while(*str)
		uart0_tx(*str++);
}
