// rtc.c
// on-chip rtc function definitions
// CTIME0 : SEC bits 5:0, MIN bits 13:8, HOUR bits 20:16
// CTIME1 : DAY bits 4:0, MONTH bits 11:8, YEAR bits 27:16
#include<LPC21xx.h>
#include"defines.h"
#include"project_defines.h"
#include"rtc.h"

void rtc_get_time(DATE_TIME *dt)
{
	u32 t0,t1,t0b;
	do							// read again if seconds changed while reading
	{
		t0=CTIME0;
		t1=CTIME1;
		t0b=CTIME0;
	}while(t0!=t0b);
	dt->sec=t0&0x3F;
	dt->min=(t0>>8)&0x3F;
	dt->hour=(t0>>16)&0x1F;
	dt->day=t1&0x1F;
	dt->month=(t1>>8)&0x0F;
	dt->year=(t1>>16)&0xFFF;
}
u8 rtc_set_time(const DATE_TIME *dt)
{
	if(!validate_date(dt->day,dt->month,dt->year)) return 0;
	if(!validate_time(dt->hour,dt->min,dt->sec))   return 0;
	CCR=0x02;					// stop rtc and reset clock counter
	SEC=dt->sec;
	MIN=dt->min;
	HOUR=dt->hour;
	DOM=dt->day;
	MONTH=dt->month;
	YEAR=dt->year;
	DOW=get_day_of_week(dt->year,dt->month,dt->day);
	DOY=get_day_of_year(dt->year,dt->month,dt->day);
	CCR=0x01;					// start rtc
	return 1;
}
void rtc_init(void)
{
	DATE_TIME dt;
	PREINT=(PCLK/32768)-1;							// prescaler for pclk based rtc clock
	PREFRAC=PCLK-((PREINT+1)*32768);
	CCR=0x01;										// enable rtc
	rtc_get_time(&dt);
	if(!validate_date(dt.day,dt.month,dt.year) || !validate_time(dt.hour,dt.min,dt.sec))
	{												// rtc content not valid (first power on) -> load default
		dt.year=DEFAULT_YEAR; dt.month=DEFAULT_MONTH; dt.day=DEFAULT_DAY;
		dt.hour=0; dt.min=0; dt.sec=0;
		rtc_set_time(&dt);
	}
}
