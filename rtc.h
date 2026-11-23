// rtc.h
#ifndef _RTC_H
#define _RTC_H
#include"types.h"
#include"utils.h"
void rtc_init(void);
void rtc_get_time(DATE_TIME *dt);			// read date and time
u8   rtc_set_time(const DATE_TIME *dt);		// write date and time, returns 0 if dt is not valid
#endif
