
#include "adc.h"

#include <zneo.h>

#define ADC0CTL_START0 0x80
#define ADC0CTL_CVTRD0 0x40
#define ADC0CTL_REFEN  0x20
#define ADC0CTL_ADC0EN 0x10
#define ADC0CTL_ANA0   0x00
#define ADC0CTL_ANA1   0x01
#define ADC0CTL_ANA2   0x02
#define ADC0CTL_ANA3   0x03
#define ADC0CTL_ANA4   0x04
#define ADC0CTL_ANA5   0x05
#define ADC0CTL_ANA6   0x06
#define ADC0CTL_ANA7   0x07
#define ADC0CTL_ANA8   0x08
#define ADC0CTL_ANA9   0x09
#define ADC0CTL_ANA10  0x0A
#define ADC0CTL_ANA11  0x0B

void init_adc(void)
{
	PBAFL = 0x01;          // Enable Alt Fun 1 on PA0
    ADC0CTL = ADC0CTL_REFEN  + ADC0CTL_ADC0EN;
}


short adc_read(void)
{
	short value;

    ADC0CTL |= ADC0CTL_START0;

    // conversion takes time, wait for it
    while (ADC0CTL & 0x80);

    value = ADC0D >> 6;

    return value;	
}

