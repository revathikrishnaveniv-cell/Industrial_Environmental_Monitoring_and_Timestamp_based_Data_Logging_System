// delay.c
// To generate delay :- function definitions
#include"delay.h" 			// function declarations for delay generation header inclusion
void delay_s(u32 delay)		// function definition for 1 second delay generation
{
	for(delay*=12000000;delay>0;delay--);
}
void delay_ms(u32 delay)	// function definition for 1 milli second delay generation
{
	for(delay*=12000;delay>0;delay--);
}
void delay_us(u32 delay)	// function definition for 1 micro second delay generation
{
	for(delay*=12;delay>0;delay--);
}
