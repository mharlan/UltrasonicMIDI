
#include "adc.h"

#include <zneo.h>

#define ADC_CHANNELS 2
#define ADC_CH_MASK  0x0F

#define ADC_IRQ0_EN  0x01

#define ADC0CTL_START0 0x80
#define ADC0CTL_CVTRD0 0x40
#define ADC0CTL_REFEN  0x20
#define ADC0CTL_ADC0EN 0x10

static short adc_values[ADC_CHANNELS];

static void (*adc_proc)(unsigned char channel, short value);

void interrupt adc_read(void)
{
	unsigned char channel;
	short value;

	channel = ADC0CTL & ADC_CH_MASK;
    value = ADC0D >> 6;

    adc_proc(channel, value);
}

void init_adc(void (*adc_func)(unsigned char channel, short value))
{
	PBAFL |= 0x03;          // Enable Alt Fun 1 on PB0 and PB1

	IRQ0ENL &= ~ADC_IRQ0_EN;
	IRQ0ENH |= ADC_IRQ0_EN;

	SET_VECTOR(ADC, adc_read);

	adc_proc = adc_func;
}

void adc_start(unsigned char channel)
{
	ADC0CTL = ADC0CTL_ADC0EN | ADC0CTL_START0 | channel;
}
