#ifndef __ADC_H
#define __ADC_H

#define ADC_CH0   0x00
#define ADC_CH1   0x01
#define ADC_CH2   0x02
#define ADC_CH3   0x03
#define ADC_CH4   0x04
#define ADC_CH5   0x05
#define ADC_CH6   0x06
#define ADC_CH7   0x07
#define ADC_CH8   0x08
#define ADC_CH9   0x09
#define ADC_CH10  0x0A
#define ADC_CH11  0x0B

/*
	Initialize the ADC. Pass the ADC processing function in.

	Currently only runs in sample mode, not freerun.
 */
extern void init_adc(void (*adc_func)(unsigned char channel, short value));

/*
	Start an ADC conversion.
 */
extern void adc_start(unsigned char channel);

#endif