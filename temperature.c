// temperature.c
// read lm35 : take average of many adc samples then convert
#include"adc.h"
#include"utils.h"
#include"temperature.h"

s32 temperature_read(void)
{
	u32 sum=0;
	u8 i;
	for(i=0;i<ADC_SAMPLES;i++)
		sum+=adc_read();
	return adc_to_temp(sum,ADC_SAMPLES);
}
