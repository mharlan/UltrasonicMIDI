
#include "bit_ops.h"

#include <limits.h>

unsigned char bit_ops_reverse_byte(unsigned char byte)
{
	unsigned char v;
	unsigned char r;
	unsigned char s;

	r = v = byte;                            // r will be reversed bits of v; first get LSB of v
	s = sizeof(v) * CHAR_BIT - 1; // extra shift needed at end
	
	for (v >>= 1; v; v >>= 1)
	{   
  		r <<= 1;
  		r |= v & 1;
  		s--;
	}
	r <<= s; // shift when v's highest bits are zero

	return r;
}