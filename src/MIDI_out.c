/*
	Serial output on Port D5, AF as TXD1
 */

#include "MIDI_out.h"
//#include "bit_ops.h"

#include <zneo.h>

#define FREQ           5529600UL
#define MIDI_BAUDRATE  31250UL

#define PORTD_TXD1_AF  0x20

#define UART1_TXD_EN   0x80
#define UART1_TRAN_RDY 0x04

#define UART1_IRQ_EN   0x20

#define MIDI_MSG_BUFFER_SIZE 32

static unsigned char midi_msg_buffer[MIDI_MSG_BUFFER_SIZE];

static unsigned char msg_buffer_current = 0;
static unsigned char msg_buffer_size = 0;

void interrupt midi_out_transfer(void)
{
	if(msg_buffer_size) {
		U1TXD = midi_msg_buffer[msg_buffer_current];

		msg_buffer_current = (msg_buffer_current + 1) % MIDI_MSG_BUFFER_SIZE;
		msg_buffer_size--;
	}
}

void init_midi_out(void)
{
	PDAFH &= ~PORTD_TXD1_AF;
	PDAFL |= PORTD_TXD1_AF;

	U1BR = FREQ / (MIDI_BAUDRATE * 16UL);

	U1CTL0 = UART1_TXD_EN;
	U1CTL1 = 0;

	//set nominal priority
	IRQ2ENH |= UART1_IRQ_EN;
	IRQ2ENL &= ~UART1_IRQ_EN;

	PAIMUX |= UART1_IRQ_EN;	    //Port D5 (1) for interrupts
	PAIEDGE &= ~UART1_IRQ_EN;	//Port D5, negedge (0) interrupt

	SET_VECTOR(UART1_TX, midi_out_transfer);
}

void midi_out_disable(void)
{
	U1CTL0 &= ~(UART1_TXD_EN);
}

void midi_out_enable(void)
{
    U1CTL0 |= UART1_TXD_EN;
}

unsigned char midi_out_send_standard_msg(unsigned char status, unsigned char data1, unsigned char data2)
{
	unsigned char buffer_loc;

	if(msg_buffer_size < (MIDI_MSG_BUFFER_SIZE - 2)) {
		DI();
		
		buffer_loc = (msg_buffer_current + msg_buffer_size) % MIDI_MSG_BUFFER_SIZE;
		midi_msg_buffer[buffer_loc] = status;
		msg_buffer_size++;

		buffer_loc = (msg_buffer_current + msg_buffer_size) % MIDI_MSG_BUFFER_SIZE;
		midi_msg_buffer[buffer_loc] = data1;
		msg_buffer_size++;

		buffer_loc = (msg_buffer_current + msg_buffer_size) % MIDI_MSG_BUFFER_SIZE;
		midi_msg_buffer[buffer_loc] = data2;
		msg_buffer_size++;

		//trigger the interrupt if already ready to transmit
		if((U1STAT0 & UART1_TRAN_RDY) && 
		   ((IRQ2SET & UART1_IRQ_EN) == 0)) {
			IRQ2SET |= UART1_IRQ_EN;
		}

		EI();
	}
	else {
		return 1;
	}

	return 0;
}

unsigned char midi_out_send_small_msg(unsigned char status, unsigned char data)
{
	unsigned char buffer_loc;

	if(msg_buffer_size < (MIDI_MSG_BUFFER_SIZE - 2)) {
		DI();
		
		buffer_loc = (msg_buffer_current + msg_buffer_size) % MIDI_MSG_BUFFER_SIZE;
		midi_msg_buffer[buffer_loc] = status;
		msg_buffer_size++;

		buffer_loc = (msg_buffer_current + msg_buffer_size) % MIDI_MSG_BUFFER_SIZE;
		midi_msg_buffer[buffer_loc] = data;
		msg_buffer_size++;

		//trigger the interrupt if already ready to transmit
		if((U1STAT0 & UART1_TRAN_RDY) && 
		   ((IRQ2SET & UART1_IRQ_EN) == 0)) {
			IRQ2SET |= UART1_IRQ_EN;
		}

		EI();
	}
	else {
		return 1;
	}

	return 0;
}

unsigned char midi_out_send_msg(unsigned char status)
{
	unsigned char buffer_loc;

	if(msg_buffer_size < MIDI_MSG_BUFFER_SIZE) {
		DI();
		
		buffer_loc = (msg_buffer_current + msg_buffer_size) % MIDI_MSG_BUFFER_SIZE;
		midi_msg_buffer[buffer_loc] = status;
		msg_buffer_size++;

		//trigger the interrupt if already ready to transmit
		if((U1STAT0 & UART1_TRAN_RDY) && 
		   ((IRQ2SET & UART1_IRQ_EN) == 0)) {
			IRQ2SET |= UART1_IRQ_EN;
		}

		EI();
	}
	else {
		return 1;
	}

	return 0;
}