// utils.c
// hardware independent function definitions
#include<stdio.h>
#include<string.h>
#include"utils.h"

static const u8 month_days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
static const u8 month_start[12]={0,3,2,5,0,3,5,1,4,6,2,4};	// table for day of week
static const u32 cum_days[12]={0,31,59,90,120,151,181,212,243,273,304,334};

u8 is_leap_year(u32 year)
{
	if(year%400==0) return 1;
	if(year%100==0) return 0;
	if(year%4==0)   return 1;
	return 0;
}
u8 days_in_month(u32 year,u8 month)
{
	if(month<1 || month>12) return 0;
	if(month==2 && is_leap_year(year)) return 29;
	return month_days[month-1];
}
u8 validate_date(u8 day,u8 month,u32 year)
{
	if(year<2000 || year>2099) return 0;
	if(month<1 || month>12)    return 0;
	if(day<1 || day>days_in_month(year,month)) return 0;
	return 1;
}
u8 validate_time(u8 hour,u8 min,u8 sec)
{
	if(hour>23 || min>59 || sec>59) return 0;
	return 1;
}
u8 get_day_of_week(u32 year,u8 month,u8 day)
{
	if(month<3) year--;
	return (u8)((year+year/4-year/100+year/400+month_start[month-1]+day)%7);
}
u32 get_day_of_year(u32 year,u8 month,u8 day)
{
	u32 doy=cum_days[month-1]+day;
	if(month>2 && is_leap_year(year)) doy++;
	return doy;
}
static u32 digits_to_num(const char *s,u8 n)	// "2026" -> 2026, returns 99999 if non digit
{
	u32 v=0;
	u8 i;
	for(i=0;i<n;i++)
	{
		if(s[i]<'0' || s[i]>'9') return 99999;
		v=v*10+(s[i]-'0');
	}
	return v;
}
u8 parse_date_digits(const char *d,DATE_TIME *dt)
{
	u32 day=digits_to_num(d,2);
	u32 month=digits_to_num(d+2,2);
	u32 year=digits_to_num(d+4,4);
	if(day>31 || month>12 || year>9999) return 0;
	if(!validate_date((u8)day,(u8)month,year)) return 0;
	dt->day=(u8)day; dt->month=(u8)month; dt->year=year;
	return 1;
}
u8 parse_time_digits(const char *d,DATE_TIME *dt)
{
	u32 h=digits_to_num(d,2);
	u32 m=digits_to_num(d+2,2);
	u32 s=digits_to_num(d+4,2);
	if(h>23 || m>59 || s>59) return 0;
	dt->hour=(u8)h; dt->min=(u8)m; dt->sec=(u8)s;
	return 1;
}
s32 adc_to_temp(u32 adc_sum,u8 count)
{
	u32 den;
	if(count==0) return 0;
	// lm35 gives 10 mV per degree C, so 1 mV = 0.1 C
	// mV = adc * Vref / 1023  (+ half of divider for rounding)
	den=(u32)count*ADC_FULL_SCALE;
	return (s32)((adc_sum*ADC_VREF_MV+den/2)/den);
}
u8 check_temp_limit(s32 temp)
{
	if(temp>TEMP_HIGH_LIMIT) return TEMP_HIGH;
	if(temp<TEMP_LOW_LIMIT)  return TEMP_LOW;
	return TEMP_NORMAL;
}
void format_date(const DATE_TIME *dt,char *s)
{
	sprintf(s,"%02d/%02d/%04d",(int)dt->day,(int)dt->month,(int)dt->year);
}
void format_time(const DATE_TIME *dt,char *s)
{
	sprintf(s,"%02d:%02d:%02d",(int)dt->hour,(int)dt->min,(int)dt->sec);
}
void format_temp(s32 temp,char *s)
{
	if(temp<0) temp=0;				// lm35 basic circuit cannot measure below 0 C
	sprintf(s,"%d.%d",(int)(temp/10),(int)(temp%10));
}
void format_log_line(const DATE_TIME *dt,s32 temp,u8 status,char *s)
{
	char d[12],t[12],tp[12];
	format_date(dt,d);
	format_time(dt,t);
	format_temp(temp,tp);
	sprintf(s,"%s %s %s\xC2\xB0" "C",d,t,tp);		// UTF-8 degree sign
	if(status==TEMP_HIGH) strcat(s," [HIGH]");
	if(status==TEMP_LOW)  strcat(s," [LOW]");
	strcat(s,"\r\n");
}
