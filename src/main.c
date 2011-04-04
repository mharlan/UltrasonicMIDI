/*
	Author: Matthew Harlan
	Email:  mharlan@gwmail.gwu.edu
	Class:  CSCI-4415
	Date: 	March 29th, 2011
	Lab:    Final Project
	
	Description: This program drives a MIDI output port.

	Other files: adc.c adc. h bit_ops.c bit_ops.h buttons.c buttons.h cli.c cli.h delay.c delay.h 
	info.c info.h LED.c LED.h LED_ascii.h macro.c macro.h MIDI_out.c MIDI_out.h MIDI_messages.c 
	MIDI_messages.h oscillator.c oscillator.h ports.c ports.h timer.c timer.h uart.c uart.h

	Compile: Set the user include path to the include directory.
	
	Problems: The MIDI output specification is very confusing.

	Comments: 

	Enhancements: None.
 */

#include "LED.h"
#include "MIDI_out.h"
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

	init_midi_out();
	init_buttons();
	init_leds();

	//initialize the command line interface
	init_cli();

	//enable interrupts
	EI();

	cli_loop();
}
