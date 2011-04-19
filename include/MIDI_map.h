#ifndef __MIDI_MAP_H
#define __MIDI_MAP_H

#include "MIDI_sensors.h"

/*
	This file provides hard-coded maps for distances into 
	MIDI note or control values.

	Everything is set for a middle octave so an octave offset
	can be used.

	Eventually, this will be programmable.
 */

unsigned char midi_note_map[SENSOR_RANGE] = {
	60,  //1
	61,  //2
	62,  //3
	63,  //4
	64,  //5
	65,  //6
	66,  //7
	67,  //8
	68,  //9
	69,  //10
	70,  //11
	71,  //12
};

unsigned char midi_ctrl_map[SENSOR_RANGE] = {
	0,  //1
	11,  //2
	22,  //3
	33,  //4
	44,  //5
	55,  //6
	66,  //7
	77,  //8
	88,  //9
	99,  //10
	110, //11
	121, //12
};

/*
for use later

unsigned char midi_ctrl_map[MIDI_MAP_RANGE] = {
	3,   //0
	6,   //1
	9,   //2
	12,  //3
	15,  //4
	18,  //5
	21,  //6
	24,  //7
	27,  //8
	30,  //9
	33,  //10
	36,  //11
	39,  //12
	42,  //13
	45,  //14
	48,  //15
	51,  //16
	54,  //17
	57,  //18
	60,  //19
	63,  //10
	66,  //21
	69,  //22
	72,  //23
	75,  //24
	78,  //25
	81,  //26
	84,  //27
	87,  //28
	90,  //29
	93,  //30
	96,  //31
	99,  //32
	102, //33
	105, //34
	108, //35
	112, //36
	115, //37
	118, //38
	121  //39
};

unsigned char midi_ctrl_map[MIDI_MAP_RANGE] = {
	0, //0
	0, //1
	0, //2
	0, //3
	0, //4
	0, //5
	0, //6
	0, //7
	0, //8
	0, //9
	0, //10
	0, //11
	0, //12
	0, //13
	0, //14
	0, //15
	0, //16
	0, //17
	0, //18
	0, //19
	0, //10
	0, //21
	0, //22
	0, //23
	0, //24
	0, //25
	0, //26
	0, //27
	0, //28
	0, //29
	0, //30
	0, //31
	0, //32
	0, //33
	0, //34
	0, //35
	0, //36
	0, //37
	0, //38
	0  //39
};
*/

#endif