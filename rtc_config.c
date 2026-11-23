// rtc_config.c
// RTC configuration mode (called from main when push button interrupt came)
// keys : 0-9 digit, * backspace, # confirm, C cancel
#include"types.h"
#include"lcd.h"
#include"keypad.h"
#include"delay.h"
#include"rtc.h"
#include"utils.h"
#include"monitor.h"
#include"project_defines.h"
#include"rtc_config.h"

#define DATE_FIELD	0
#define TIME_FIELD	1

static void show_entry(u8 field,char *buf)	// show typed digits like 29/09/20__
{
	char *tpl=(field==DATE_FIELD)?"__/__/____":"__:__:__";
	char line[12];
	u8 i=0,k=0;
	while(tpl[i])
	{
		if(tpl[i]=='_')
		{
			if(buf[k]!=0) line[i]=buf[k++];
			else          line[i]='_';
		}
		else
			line[i]=tpl[i];
		i++;
	}
	line[i]=0;
	lcd_row(1,(u8*)line);
}
// read 'max' digits from keypad, returns 1 = confirmed with #, 0 = cancelled / time out
static u8 read_field(u8 field,u8 max,char *buf)
{
	u8 n=0,key;
	buf[0]=0;
	idle_sec=0;
	if(field==DATE_FIELD) lcd_row(0,(u8*)"DATE:#=OK C=Quit");
	else                  lcd_row(0,(u8*)"TIME:#=OK C=Quit");
	show_entry(field,buf);
	while(1)
	{
		monitor_task();					// logging continues while user types
		if(idle_sec>=CFG_TIMEOUT_SEC)
			return 0;
		key=keypad_getkey();
		if(key==0)
			continue;
		idle_sec=0;
		if(key>='0' && key<='9')
		{
			if(n<max)
			{
				buf[n++]=key;
				buf[n]=0;
			}
		}
		else if(key=='*')				// backspace
		{
			if(n>0) n--;
			buf[n]=0;
		}
		else if(key=='C')				// cancel
			return 0;
		else if(key=='#' && n==max)		// confirm only when all digits typed
			return 1;
		show_entry(field,buf);
	}
}
void rtc_config(void)
{
	DATE_TIME dt;
	char buf[9];

	config_mode=1;
	rtc_get_time(&dt);

	while(1)							// step 1 : date
	{
		if(!read_field(DATE_FIELD,8,buf)) goto cancel;
		if(parse_date_digits(buf,&dt)) break;
		lcd_row(0,(u8*)"INVALID DATE");
		delay_s(1);
	}
	while(1)							// step 2 : time
	{
		if(!read_field(TIME_FIELD,6,buf)) goto cancel;
		if(parse_time_digits(buf,&dt)) break;
		lcd_row(0,(u8*)"INVALID TIME");
		delay_s(1);
	}
	rtc_set_time(&dt);					// date and time are valid here
	lcd_row(0,(u8*)"RTC UPDATED");
	lcd_row(1,(u8*)"");
	delay_s(1);
	config_mode=0;
	return;
cancel:
	lcd_row(0,(u8*)"CONFIG CANCELLED");
	lcd_row(1,(u8*)"");
	delay_s(1);
	config_mode=0;
}
