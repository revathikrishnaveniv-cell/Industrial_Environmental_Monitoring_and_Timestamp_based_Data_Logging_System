// monitor.h
// monitoring task :- read temperature, show on lcd, send log to pc, alarm
#ifndef _MONITOR_H
#define _MONITOR_H
#include"types.h"
extern u8 config_mode;		// 1 while user is changing rtc (lcd is used by config screen)
extern u8 idle_sec;			// seconds since last key press in config mode
void monitor_init(void);
void monitor_task(void);	// call again and again, works once every second
#endif
