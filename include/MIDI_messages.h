#ifndef __MIDI_MESSAGES_H
#define __MIDI_MESSAGES_H

#define MIDI_CHANNEL1  0x00
#define MIDI_CHANNEL2  0x01
#define MIDI_CHANNEL3  0x02
#define MIDI_CHANNEL4  0x03
#define MIDI_CHANNEL5  0x04
#define MIDI_CHANNEL6  0x05
#define MIDI_CHANNEL7  0x06
#define MIDI_CHANNEL8  0x07
#define MIDI_CHANNEL9  0x08
#define MIDI_CHANNEL10 0x09
#define MIDI_CHANNEL11 0x0A
#define MIDI_CHANNEL12 0x0B
#define MIDI_CHANNEL13 0x0C
#define MIDI_CHANNEL14 0x0D
#define MIDI_CHANNEL15 0x0E
#define MIDI_CHANNEL16 0x0F

extern void midi_msg_note_on(unsigned char channel, unsigned char note, unsigned char velocity);

extern void midi_msg_note_off(unsigned char channel, unsigned char note, unsigned char velocity);

extern void midi_msg_ctrl_change(unsigned char channel, unsigned char ctrl_num, unsigned char ctrl_val);

#endif