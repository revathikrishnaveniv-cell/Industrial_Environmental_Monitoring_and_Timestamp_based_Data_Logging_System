// uart.h
// uart0 function declarations (P0.0 TXD0, P0.1 RXD0 -> MAX232 -> PC)
#ifndef _UART_H
#define _UART_H
#include"types.h"
void uart0_init(u32 baud);
void uart0_tx(u8 ch);
void uart0_string(char *str);
#endif
