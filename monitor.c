// monitor.c
#include<LPC21xx.h>
#include<stdio.h>
#include"defines.h"
#include"project_defines.h"
#include"lcd.h"
#include"uart.h"
#include"rtc.h"
#include"buzzer.h"
#include"temperature.h"
#include"utils.h"
#include"monitor.h"

u8 config_mode=0;
u8 idle_sec=0;

static u8 last_sec=0xFF;		// rtc seconds of last run
static u8 log_count=LOG_INTERVAL;	// forces first log immediately
static u8 last_status=TEMP_NORMAL;

void monitor_init(void)
{
	last_sec=SEC;
	last_status=TEMP_NORMAL;
}
static void show_on_lcd(DATE_TIME *dt,s32 temp,u8 status)
{
	char d[12],t[12],tp[12],line[20];
	char *st="NORM ";
	if(status==TEMP_HIGH) st="HIGH!";
	if(status==TEMP_LOW)  st="LOW! ";
	format_date(dt,d);
	format_time(dt,t);
	format_temp(temp,tp);
	sprintf(line,"%s %s",d,st);
	lcd_row(0,(u8*)line);
	sprintf(line,"%s %s%cC",t,tp,LCD_DEGREE);
	lcd_row(1,(u8*)line);
}
void monitor_task(void)
{
	DATE_TIME now;
	s32 temp;
	u8 status;
	char line[50];

	if(SEC==last_sec)			// one second not completed
		return;
	last_sec=SEC;

	rtc_get_time(&now);
	temp=temperature_read();
	status=check_temp_limit(temp);

	if(status!=TEMP_NORMAL && (now.sec%2)==0)	// buzzer beeps every second while limit crossed
		buzzer_on();
	else
		buzzer_off();

	if(config_mode)
		idle_sec++;				// used for config time out
	else
		show_on_lcd(&now,temp,status);

	log_count++;
	if(log_count>=LOG_INTERVAL || status!=last_status)	// every interval or when alarm changes
	{
		format_log_line(&now,temp,status,line);
		uart0_string(line);
		log_count=0;
	}
	last_status=status;
}
