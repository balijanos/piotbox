#ifndef LUADISPLAY_H
#define LUADISPLAY_H

#include <lua.hpp>
#include "ArduiPi_OLED_lib.h"
#include "Adafruit_GFX.h"
#include "ArduiPi_OLED.h"

static ArduiPi_OLED display;

struct s_opts
{
	int oled;
};

static s_opts opts[7] = {
	{ OLED_ADAFRUIT_SPI_128x32 },
	{ OLED_ADAFRUIT_SPI_128x64 },
	{ OLED_ADAFRUIT_I2C_128x32 },
	{ OLED_ADAFRUIT_I2C_128x64 },
	{ OLED_SEEED_I2C_128x64 },
	{ OLED_SEEED_I2C_96x96 },
	{ OLED_SH1106_I2C_128x64 }
};

int luaopen_display (lua_State *L);

#endif