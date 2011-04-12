#ifndef __MIDI_SENSORS_H
#define __MIDI_SENSORS_H

#define SENSOR_NOTES  0x01
#define SENSOR_CTRL_1 0x02
#define SENSOR_CTRL_2 0x04

#define SENSOR_MIN   7  //inches
#define SENSOR_MAX   43
#define SENSOR_DIV   2

//18 (1 full octave plus extra)
#define SENSOR_RANGE ((SENSOR_MAX - SENSOR_MIN) / SENSOR_DIV)

void init_midi_sensors(void);

void midi_sensors_event(void);

#endif