// utils.h
// hardware independent functions (date check, temperature calculation, text formats)
// these functions are tested on PC, see tests/test_utils.c

#ifndef _UTILS_H
#define _UTILS_H

#include"types.h"
#include"project_defines.h"

typedef struct
{
	u32 year;		// 2000 - 2099
	u8  month;		// 1 - 12
	u8  day;		// 1 - 31
	u8  hour;		// 0 - 23
	u8  min;		// 0 - 59
	u8  sec;		// 0 - 59
}DATE_TIME;

u8  is_leap_year(u32 year);							// 1 = leap year
u8  days_in_month(u32 year,u8 month);				// 0 if month wrong
u8  validate_date(u8 day,u8 month,u32 year);		// 1 = valid
u8  validate_time(u8 hour,u8 min,u8 sec);			// 1 = valid
u8  get_day_of_week(u32 year,u8 month,u8 day);		// 0 = sunday
u32 get_day_of_year(u32 year,u8 month,u8 day);		// 1 - 366

u8  parse_date_digits(const char *d,DATE_TIME *dt);	// "DDMMYYYY" -> dt (only if valid)
u8  parse_time_digits(const char *d,DATE_TIME *dt);	// "HHMMSS"   -> dt (only if valid)

s32 adc_to_temp(u32 adc_sum,u8 count);				// sum of adc samples -> temperature in 0.1 C
u8  check_temp_limit(s32 temp);						// TEMP_NORMAL / TEMP_HIGH / TEMP_LOW

void format_date(const DATE_TIME *dt,char *s);		// "29/09/2026"  (min 11 bytes)
void format_time(const DATE_TIME *dt,char *s);		// "09:30:00"    (min 9 bytes)
void format_temp(s32 temp,char *s);					// "27.8"        (min 8 bytes)
// "29/09/2026 09:30:00 27.8<deg>C\r\n"  (+ " [HIGH]" or " [LOW]")   (min 48 bytes)
void format_log_line(const DATE_TIME *dt,s32 temp,u8 status,char *s);

#endif
