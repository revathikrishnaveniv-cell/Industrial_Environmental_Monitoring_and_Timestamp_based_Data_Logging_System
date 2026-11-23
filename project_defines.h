// project_defines.h
// all project settings and pin numbers in one place

#ifndef _PROJECT_DEFINES_H
#define _PROJECT_DEFINES_H

// lcd pins are in lcd_defines.h  (P0.8-P0.15 data, P0.16 RS, P0.17 EN)

// pin configuration
#define BUZZER_PIN		21		// port 0.21	buzzer
#define EINT3_PIN		20		// port 0.20	push button (EINT3), switch to GND
#define LM35_PIN		28		// port 0.28	AD0.1 lm35 output
#define KEY_ROW_START	20		// port 1.20-1.23	keypad rows (output)
#define KEY_COL_START	16		// port 1.16-1.19	keypad columns (input)
#define KEY_ROW_MASK	(0xFu<<KEY_ROW_START)

// adc settings
#define ADC_CHANNEL		1			// AD0.1
#define ADC_CLKDIV		((PCLK/3750000)-1)	// adc clock must be <= 4.5 MHz
#define ADC_VREF_MV		3300u		// adc reference voltage in mV
#define ADC_FULL_SCALE	1023u		// 10 bit adc
#define ADC_SAMPLES		16			// samples for averaging

// temperature limits in 0.1 degree C (400 = 40.0 C)
#define TEMP_HIGH_LIMIT	400
#define TEMP_LOW_LIMIT	100
#define TEMP_NORMAL		0
#define TEMP_HIGH		1
#define TEMP_LOW		2

// logging and uart
#define UART_BAUD		9600
#define LOG_INTERVAL	60		// send log to pc every 60 seconds
#define LOG_HEADER		"Date       Time     Temperature\r\n"

// rtc configuration
#define DEFAULT_YEAR	2026
#define DEFAULT_MONTH	1
#define DEFAULT_DAY		1
#define CFG_TIMEOUT_SEC	30		// leave config mode if no key for 30 s
#define LCD_DEGREE		0xDF	// degree symbol of lcd rom

// 1 = call pll_init() from main, 0 = clock already set by startup file
#define USE_PLL_INIT	0

#endif
