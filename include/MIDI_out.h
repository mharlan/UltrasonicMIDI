#ifndef __MIDI_OUT_H
#define __MIDI_OUT_H

extern void init_midi_out(void);

extern void midi_out_enable(void);

extern void midi_out_disable(void);

extern unsigned char midi_out_send_standard_msg(unsigned char status, unsigned char data1, unsigned char data2);

extern unsigned char midi_out_send_small_msg(unsigned char status, unsigned char data);

extern unsigned char midi_out_send_msg(unsigned char status);

#endif
