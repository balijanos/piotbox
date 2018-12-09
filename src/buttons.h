#ifndef BUTTONS_H
#define BUTTONS_H

#define MAX_BUTTONS 28

#include "lua.h"

struct but_val
{
	int pin=-1;
	int value=-1;
	int orig=-1;
	int pressed;
	int released;
	unsigned int ptime; // pressed at (msec)
	unsigned int rtime; // released at (msec)
};

static char buttonCallback[64] = "\0";

static struct but_val ButtonState[MAX_BUTTONS];

#endif