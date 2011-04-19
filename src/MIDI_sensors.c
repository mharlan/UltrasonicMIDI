
/*
	Enable each sensor by pulling a pin high.

	Sensor 1: PG0
	Sensor 2: PG1
 */

#include "MIDI_messages.h"
#include "MIDI_sensors.h"
#include "MIDI_map.h"
#include "timer.h"
#include "LED.h"
#include "adc.h"

#include <zneo.h>
#include <string.h>

#define NUM_SENSORS   2
#define SENSOR_CUTOFF 40 //ms

#define SENSOR1_PIN 0x01
#define SENSOR2_PIN 0x02

#define SENSOR_VELOCITY  0x45
#define SENSOR_CTRL1_VAL 0x66
#define SENSOR_CTRL2_VAL 0x67

#define DIST_TO_MAP(d) ((d - SENSOR_MIN) / SENSOR_DIV)

static unsigned char sensor_modes[NUM_SENSORS];
static unsigned char sensor_values[NUM_SENSORS];
static unsigned char sensor_channel;

static int sensor_timer;

static void midi_sensors_msg(unsigned char adc_channel, unsigned char distance);

void midi_sensors_adc_proc(unsigned char channel, short value)
{
	unsigned char distance;

	distance = (unsigned char)(value / 2);

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

	midi_sensors_msg(channel, distance);
}

void init_midi_sensors(unsigned char s1_mode, unsigned char s2_mode)
{
	sensor_timer = 0;
	sensor_channel = ADC_CH0;

	//set PG0 and PG1 as outputs
	PADD &= ~(SENSOR1_PIN | SENSOR2_PIN);
	PAAFL &= ~(SENSOR1_PIN | SENSOR2_PIN);
	PAAFH &= ~(SENSOR1_PIN | SENSOR2_PIN);

	PAOUT |= SENSOR1_PIN;
	PAOUT &= ~SENSOR2_PIN;

	memset(sensor_values, 0, NUM_SENSORS);

	sensor_modes[0] = s1_mode;
	sensor_modes[1] = s2_mode;

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

void midi_sensors_switch_mode(unsigned char s1_mode, unsigned char s2_mode)
{
	sensor_modes[0] = s1_mode;
	sensor_modes[1] = s2_mode;
}

static void midi_sensors_msg(unsigned char adc_channel, unsigned char distance)
{
	unsigned char previous;
	unsigned char current;

	current = DIST_TO_MAP(distance);

	if(sensor_values[adc_channel]) {
		previous = DIST_TO_MAP(sensor_values[adc_channel]);

		if(previous == current) {
			return;
		}
		else if(sensor_modes[adc_channel] == SENSOR_NOTES) {
			midi_msg_note_off(MIDI_CHANNEL10, midi_note_map[previous], SENSOR_VELOCITY);
		}

		sensor_values[adc_channel] = 0;
	}

	if((distance < SENSOR_MIN) || (distance >= SENSOR_MAX)) {
		return;
	}

	if(sensor_modes[adc_channel] == SENSOR_NOTES) {
		midi_msg_note_on(MIDI_CHANNEL10, midi_note_map[current], SENSOR_VELOCITY);

		led_display_int(current);
	}
	else if(sensor_modes[adc_channel] == SENSOR_CTRL_1) {
		midi_msg_ctrl_change(MIDI_CHANNEL10, SENSOR_CTRL1_VAL, midi_ctrl_map[current]);
	}
	else if(sensor_modes[adc_channel] == SENSOR_CTRL_2) {
		midi_msg_ctrl_change(MIDI_CHANNEL10, SENSOR_CTRL2_VAL, midi_ctrl_map[current]);
	}

	sensor_values[adc_channel] = distance;
}
