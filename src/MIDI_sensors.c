
/*
	Enable each sensor by pulling a pin high.

	Sensor 1: PG0
	Sensor 2: PG1
 */

#include "MIDI_sensors.h"
#include "timer.h"
#include "LED.h"
#include "adc.h"

#include <zneo.h>

#define NUM_SENSORS   2
#define SENSOR_CUTOFF 20 //ms

#define SENSOR1_PIN 0x01
#define SENSOR2_PIN 0x02

static unsigned char sensor_values[NUM_SENSORS];
static unsigned char sensor_channel;

static int sensor_timer;

void midi_sensors_adc_proc(unsigned char channel, short value)
{
	if(channel == ADC_CH0) {
		PAOUT &= ~SENSOR1_PIN;
		PAOUT |= SENSOR2_PIN;

		sensor_channel = ADC_CH1;
	}
	else if(channel == ADC_CH1) {
		PAOUT |= SENSOR1_PIN;
		PAOUT &= ~SENSOR2_PIN;

		sensor_channel = ADC_CH0;
	}
}

void init_midi_sensors(void)
{
	sensor_timer = 0;
	sensor_channel = ADC_CH0;

	//set PG0 and PG1 as outputs
	PADD &= ~(SENSOR1_PIN | SENSOR2_PIN);
	PAAFL &= ~(SENSOR1_PIN | SENSOR2_PIN);
	PAAFH &= ~(SENSOR1_PIN | SENSOR2_PIN);

	PAOUT |= SENSOR1_PIN;
	PAOUT &= ~SENSOR2_PIN;

	init_adc(midi_sensors_adc_proc);
}

/*
	Start the ADC conversion.
 */
void midi_sensors_event(void)
{
	sensor_timer += timer_interval_int();

	if(sensor_timer >= SENSOR_CUTOFF) {
		sensor_timer = 0;

		adc_start(sensor_channel);
	}
}
