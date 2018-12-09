#ifndef ROTARY_H
#define ROTARY_H

#include "lua.h"
#include "rotaryencoder.h"
#define MAX_ENCODERS max_encoders // defined in rotaryencoder.h

struct rot_wiring
{
	int clk;
	int dt;
};

struct rot_val
{
	struct encoder *rotaryenc;
	int sens=1;
	int value;
	int orig;
};	

static char encoderCallback[64] = "\0";

static struct rot_val EncoderState[MAX_ENCODERS];

#endif