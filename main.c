// main.c
// Industrial Environmental Monitoring and Timestamp-Based Data Logging System
// LPC2148 : LM35 (ADC), RTC, 16x2 LCD, 4x4 keypad, buzzer, UART0 (MAX232), push button (EINT3)
#include<LPC21xx.h>
#include"project_defines.h"
#include"pll.h"
#include"delay.h"
#include"lcd.h"
#include"keypad.h"
#include"uart.h"
#include"adc.h"
#include"rtc.h"
#include"buzzer.h"
#include"eint.h"
#include"monitor.h"
#include"rtc_config.h"

int main(void)
{
#if USE_PLL_INIT
	pll_init();
#endif
	lcd_init();
	keypad_init();
	buzzer_init();
	uart0_init(UART_BAUD);
	adc_init();
	rtc_init();
	eint_init();

	lcd_row(0,(u8*)"ENV MONITOR");
	lcd_row(1,(u8*)"LPC2148 LOGGER");
	delay_s(1);
	uart0_string(LOG_HEADER);			// column heading for the log
	monitor_init();

	while(1)
	{
		if(eint_flag)					// push button pressed
		{
			delay_ms(50);				// switch bounce time
			eint_clear();
			rtc_config();				// change date and time
			delay_ms(100);
			eint_clear();				// ignore presses during config
		}
		monitor_task();					// temperature, lcd, log, buzzer
	}
}
