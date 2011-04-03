#ifndef __MIDI_OUT_H
#define __MIDI_OUT_H

void init_midi_out(void);

void midi_out_enable(void);

void midi_out_disable(void);

unsigned char midi_out_send_standard_msg(unsigned char status, unsigned char data1, unsigned char data2);

unsigned char midi_out_send_small_msg(unsigned char status, unsigned char data);

unsigned char midi_out_send_msg(unsigned char status);

#endif
