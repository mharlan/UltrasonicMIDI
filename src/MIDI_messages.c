
#include "MIDI_out.h"
#include "MIDI_messages.h"

#define MIDI_STATUS_MASK 0x0F
#define MIDI_DATA_MASK   0x7F

#define MIDI_NOTE_ON     0x90
#define MIDI_NOTE_OFF    0x80
#define MIDI_CTRL_CHANGE 0xB0

void midi_msg_note_on(unsigned char channel, unsigned char note, unsigned char velocity)
{
	unsigned char status;
	unsigned char data;
	unsigned char data2;

	status = MIDI_NOTE_ON | (MIDI_STATUS_MASK & channel);
	data = MIDI_DATA_MASK & note;
	data2 = MIDI_DATA_MASK & velocity;

	while(midi_out_send_standard_msg(status, data, data2)) { ; }
}

void midi_msg_note_off(unsigned char channel, unsigned char note, unsigned char velocity)
{
	unsigned char status;
	unsigned char data;
	unsigned char data2;

	status = MIDI_NOTE_OFF | (MIDI_STATUS_MASK & channel);
	data = MIDI_DATA_MASK & note;
	data2 = MIDI_DATA_MASK & velocity;

	while(midi_out_send_standard_msg(status, data, data2)) { ; }
}

void midi_msg_ctrl_change(unsigned char channel, unsigned char ctrl_num, unsigned char ctrl_val)
{
	unsigned char status;
	unsigned char data;
	unsigned char data2;

	status = MIDI_CTRL_CHANGE | (MIDI_STATUS_MASK & channel);
	data = MIDI_DATA_MASK & ctrl_num;
	data2 = MIDI_DATA_MASK & ctrl_val;

	while(midi_out_send_standard_msg(status, data, data2)) { ; }
}
