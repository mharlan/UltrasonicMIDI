/*
	Author: Matthew Harlan
	Email:  mharlan@gwmail.gwu.edu
	
	Firmware for a MIDI controller that uses two analog ultrasonic
	distance sensors to generate MIDI events.
 */

#include "LED.h"
#include "MIDI_out.h"
#include "MIDI_sensors.h"
#include "oscillator.h"
#include "buttons.h"
#include "timer.h"
#include "macro.h"
#include "cli.h"

#include <zneo.h>
#include <stdio.h>

/*
	Intializes the hardware, loop on the CLI.
 */
void main(void)
{
	DI();

	//initialize the oscillator and global timer
	init_oscillator(OSC_5_52MHZ);
	init_timer(TIMER_2MS);

	init_midi_sensors(SENSOR_NOTES, SENSOR_CTRL_1);
	init_midi_out();
	init_buttons();
	init_leds();

	//initialize the command line interface
	init_cli();

	//enable interrupts
	EI();

	cli_loop();
}
