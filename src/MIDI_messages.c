
#include "MIDI_out.h"
#include "MIDI_messages.h"

#define MIDI_CTRL_MASK 0x0F
#define MIDI_MSG_MASK  0x7F

#define MIDI_NOTE_ON   0x90
#define MIDI_NOTE_OFF  0x80

void midi_msg_note_on(unsigned char channel, unsigned char note)
{
	unsigned char ctrl;
	unsigned char msg;

	ctrl = MIDI_NOTE_ON + (MIDI_CTRL_MASK & channel);
	msg = MIDI_MSG_MASK & note;

	while(midi_out_send_standard_msg(ctrl, msg, 0x64)) { ; }
}

void midi_msg_note_off(unsigned char channel, unsigned char note)
{
	unsigned char ctrl;
	unsigned char msg;

	ctrl = MIDI_NOTE_OFF + (MIDI_CTRL_MASK & channel);
	msg = MIDI_MSG_MASK & note;

	while(midi_out_send_standard_msg(ctrl, msg, 0x64)) { ; }
}