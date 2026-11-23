// buzzer.c
// buzzer connected to port 0.21 (active high buzzer)
#include<LPC21xx.h>
#include"defines.h"
#include"project_defines.h"
#include"buzzer.h"

void buzzer_init(void)
{
	SETBIT(IODIR0,BUZZER_PIN);		// buzzer pin as output
	buzzer_off();
}
void buzzer_on(void)
{
	SETBIT(IOSET0,BUZZER_PIN);
}
void buzzer_off(void)
{
	SETBIT(IOCLR0,BUZZER_PIN);
}
