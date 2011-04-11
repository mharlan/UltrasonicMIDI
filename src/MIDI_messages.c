
#include "MIDI_out.h"
#include "MIDI_messages.h"

#define MIDI_STATUS_MASK 0x0F
#define MIDI_DATA_MASK   0x7F

#define MIDI_NOTE_ON     0x90
#define MIDI_NOTE_OFF    0x80

void midi_msg_note_on(unsigned char channel, unsigned char note)
{
	unsigned char status;
	unsigned char data;

	status = MIDI_NOTE_ON | (MIDI_STATUS_MASK & channel);
	data = (MIDI_DATA_MASK & note);

	while(midi_out_send_standard_msg(status, data, 0x45)) { ; }
}

void midi_msg_note_off(unsigned char channel, unsigned char note)
{
	unsigned char status;
	unsigned char data;

	status = MIDI_NOTE_OFF | (MIDI_STATUS_MASK & channel);
	data = (MIDI_DATA_MASK & note);

	while(midi_out_send_standard_msg(status, data, 0x45)) { ; }
}
