/* 
-------------------------
-- LuaWiringPi v1.0
-- wiringPi Lua interface
-------------------------
-- Lua version 5.2
-- Copyright (C) 2016 Hi.Project Ltd.
--
-- based on lua-wpi library by wizgrav (https://github.com/wizgrav/lua-wpi)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lua.h"
#include "lauxlib.h"
#include "compat.h"
#include <wiringPi.h>
#include <wiringShift.h>
#include <wiringPiI2C.h>
#include <softPwm.h>

#define ARGCHECK(n)\
	if(lua_gettop(L) != n){\
		 luaL_error(L,"Invalid number of arguments.");\
	}\
	lcd_handle *l = luaL_checkudata(L,1,"wpi.lcd");\
	if(!l) luaL_error(L,"First argument must be an lcd handle.")
 
// Setup

static int wpi_setup (lua_State *L) {
  if ( wiringPiSetup() == -1) luaL_error(L,"piBoardRev: Unable to determine board revision from /proc/cpuinfo");
	return 0;
}

static int wpi_setup_gpio (lua_State *L) {
  if ( wiringPiSetupGpio () == -1) luaL_error(L,"piBoardRev: Unable to determine board revision from /proc/cpuinfo");  
	return 0;
}

static int wpi_setup_phys (lua_State *L) {
  if ( wiringPiSetupPhys  () == -1) luaL_error(L,"piBoardRev: Unable to determine board revision from /proc/cpuinfo");
	return 0;
}

static int wpi_setup_sys (lua_State *L) {
  if ( wiringPiSetupSys   () == -1) luaL_error(L,"piBoardRev: Unable to determine board revision from /proc/cpuinfo");
	return 0;
}

// Core GPIO

static int wpi_mode (lua_State *L) {
	if(lua_gettop(L) != 2) luaL_error(L,"Invalid number of arguments.");
	int pin = lua_tointeger(L,1);
	int mode = lua_tointeger(L,2);
	pinMode (pin,mode);
	return 0;
}

static int wpi_pud (lua_State *L) {
	if(lua_gettop(L) != 2) luaL_error(L,"Invalid number of arguments.");
	int pin = lua_tointeger(L,1);
	int pud = lua_tointeger(L,2);
	pullUpDnControl (pin,pud);
	return 0;
}

static int wpi_read (lua_State *L) {
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
	int pin = lua_tointeger(L,1);
	lua_settop(L,0);
	lua_pushinteger(L,digitalRead(pin));
	return 1;
}

static int wpi_write (lua_State *L) {
	if(lua_gettop(L) != 2) luaL_error(L,"Invalid number of arguments.");
	int pin = lua_tointeger(L,1);
	int value = lua_tointeger(L,2);
	digitalWrite(pin,value);
	return 0;
}

// Raspberry Pi specific

static int wpi_writebyte (lua_State *L) {
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
	int value = lua_tointeger(L,1);
	digitalWriteByte(value);
	return 0;
}

static int wpi_readbyte (lua_State *L) {		
	lua_pushinteger(L,digitalReadByte());
	return 1;
}

static int wpi_pwmmode (lua_State *L) {
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
	int mode = lua_tointeger(L,1);
	pwmSetMode(mode);
	return 0;
}

static int wpi_pwmrange (lua_State *L) {
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
	unsigned int range = (unsigned int) lua_tointeger(L,1);
	pwmSetRange(range);
	return 0;
}

static int wpi_pwmclock (lua_State *L) {
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
	int divisor = lua_tointeger(L,1);
	pwmSetClock(divisor);
	return 0;
}

static int wpi_rev (lua_State *L) {		
	lua_pushinteger(L,piBoardRev());
	return 1;
}

static int wpi_pin2gpio (lua_State *L) {
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
	int pin = lua_tointeger(L,1);
	lua_settop(L,0);
	lua_pushinteger(L,wpiPinToGpio(pin));
	return 1;
}

static int wpi_physpin2gpio (lua_State *L) {
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
	int pin = lua_tointeger(L,1);
	lua_settop(L,0);
	lua_pushinteger(L,physPinToGpio (pin));
	return 1;
}

// Timing

static int wpi_millis (lua_State *L) {
	if(lua_gettop(L)) luaL_error(L,"Invalid number of arguments.");
	lua_pushnumber(L,(double) millis());
	return 1;
}

static int wpi_micros (lua_State *L) {
	if(lua_gettop(L)) luaL_error(L,"Invalid number of arguments.");
	lua_pushnumber(L,(double) micros());
	return 1;
}

static int wpi_delay (lua_State *L) {
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
	unsigned int value = (unsigned int) lua_tonumber(L,1);
	delay(value);
	return 0;
}

static int wpi_msdelay (lua_State *L) {
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
	unsigned int value = (unsigned int) lua_tonumber(L,1);
	delayMicroseconds(value);
	return 0;
}

// Shift

static int wpi_shiftin (lua_State *L) {
	if(lua_gettop(L) != 3) luaL_error(L,"Invalid number of arguments.");
	unsigned char pin = (unsigned char) lua_tointeger(L,1);
	unsigned char cpin = (unsigned char) lua_tointeger(L,2);
	unsigned char order = (unsigned char)( lua_toboolean(L,3)? LSBFIRST:MSBFIRST);
	lua_pushinteger(L,(lua_Integer) shiftIn(pin,cpin,order));
	return 1;
}

static int wpi_shiftout (lua_State *L) {
	if(lua_gettop(L) != 4) luaL_error(L,"Invalid number of arguments.");
	unsigned char pin = (unsigned char) lua_tointeger(L,1);
	unsigned char cpin = (unsigned char) lua_tointeger(L,2);
	unsigned char order = (unsigned char)( lua_toboolean(L,3)? LSBFIRST:MSBFIRST);
	unsigned char value = (unsigned char) lua_tointeger(L,4);
	shiftOut(pin,cpin,order,value);
	return 0;
}

// I2C

static int wpi_setupi2c (lua_State *L) {
  if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
  int devId = lua_tointeger(L,1);
	int res = wiringPiI2CSetup(devId);
  if ( res == -1) luaL_error(L,"piI2C: Unable to open I2C device");
  lua_pushinteger(L,res);
	return 1;
}

static int wpi_setupi2cif (lua_State *L) {
  if(lua_gettop(L) != 2) luaL_error(L,"Invalid number of arguments.");
  size_t l;
  const char *device = luaL_checklstring(L, 1, &l);
  int devId = lua_tointeger(L,2);
	int res = wiringPiI2CSetupInterface(device,devId);
  if ( res == -1) luaL_error(L,"piI2C: Unable to open I2C device");
  lua_pushinteger(L,res);
	return 1;
}

static int wpi_i2cread (lua_State *L) {
  if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
  int fd = lua_tointeger(L,1);
  lua_pushinteger(L,wiringPiI2CRead(fd));
	return 1;
}

static int wpi_i2cwrite (lua_State *L) {
  if(lua_gettop(L) != 2) luaL_error(L,"Invalid number of arguments.");
  int fd = lua_tointeger(L,1);
  int data = lua_tointeger(L,2);
  lua_pushinteger(L,wiringPiI2CWrite(fd,data));
	return 1;
}

static int wpi_i2cwriter8 (lua_State *L) {
  if(lua_gettop(L) != 2) luaL_error(L,"Invalid number of arguments.");
  int fd = lua_tointeger(L,1);
  int reg = lua_tointeger(L,2);
  int data = lua_tointeger(L,3);
  lua_pushinteger(L,wiringPiI2CWriteReg8(fd,reg,data));
	return 1;
}

static int wpi_i2cwriter16 (lua_State *L) {
  if(lua_gettop(L) != 2) luaL_error(L,"Invalid number of arguments.");
  int fd = lua_tointeger(L,1);
  int reg = lua_tointeger(L,2);
  int data = lua_tointeger(L,3);
  lua_pushinteger(L,wiringPiI2CWriteReg16(fd,reg,data));
	return 1;
}

static int wpi_i2creadr8 (lua_State *L) {
  if(lua_gettop(L) != 2) luaL_error(L,"Invalid number of arguments.");
  int fd = lua_tointeger(L,1);
  int reg = lua_tointeger(L,2);
  lua_pushinteger(L,wiringPiI2CReadReg8(fd,reg));
	return 1;
}

static int wpi_i2creadr16 (lua_State *L) {
  if(lua_gettop(L) != 2) luaL_error(L,"Invalid number of arguments.");
  int fd = lua_tointeger(L,1);
  int reg = lua_tointeger(L,2);
  lua_pushinteger(L,wiringPiI2CReadReg16(fd,reg));
	return 1;
}

// Soft Pwm
static int wpi_pwm (lua_State *L) {
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");
	int pin = lua_tointeger(L,1);
	softPwmCreate(pin,10,100);
	return 0;
}

static int wpi_freq (lua_State *L) {
	if(lua_gettop(L) != 2) luaL_error(L,"Invalid number of arguments.");
	int pin = lua_tointeger(L,1);
	int value = lua_tointeger(L,2);
	softPwmWrite(pin,value);
	return 0;
}

// ISR

struct ISRLuaCb{       
       lua_State *L;
       int luaFunc;
} ISRLuaCb;

static struct ISRLuaCb ISRLuaCallback[40];

static void ISRInterrupt(int pin){
   lua_State *L = ISRLuaCallback[pin-1].L;
   int luaFunc = ISRLuaCallback[pin-1].luaFunc;   
   lua_rawgeti(L, LUA_REGISTRYINDEX, luaFunc);   
   lua_pcall(L, 0, 0, 0);
}

static void IFC1(void){ISRInterrupt(1);}
static void IFC2(void){ISRInterrupt(2);}
static void IFC3(void){ISRInterrupt(3);}
static void IFC4(void){ISRInterrupt(4);}
static void IFC5(void){ISRInterrupt(5);}
static void IFC6(void){ISRInterrupt(6);}
static void IFC7(void){ISRInterrupt(7);}
static void IFC8(void){ISRInterrupt(8);}
static void IFC9(void){ISRInterrupt(9);}
static void IFC10(void){ISRInterrupt(10);}

static void IFC11(void){ISRInterrupt(11);}
static void IFC12(void){ISRInterrupt(12);}
static void IFC13(void){ISRInterrupt(13);}
static void IFC14(void){ISRInterrupt(14);}
static void IFC15(void){ISRInterrupt(15);}
static void IFC16(void){ISRInterrupt(16);}
static void IFC17(void){ISRInterrupt(17);}
static void IFC18(void){ISRInterrupt(18);}
static void IFC19(void){ISRInterrupt(19);}
static void IFC20(void){ISRInterrupt(20);}

static void IFC21(void){ISRInterrupt(21);}
static void IFC22(void){ISRInterrupt(22);}
static void IFC23(void){ISRInterrupt(23);}
static void IFC24(void){ISRInterrupt(24);}
static void IFC25(void){ISRInterrupt(25);}
static void IFC26(void){ISRInterrupt(26);}
static void IFC27(void){ISRInterrupt(27);}
static void IFC28(void){ISRInterrupt(28);}
static void IFC29(void){ISRInterrupt(29);}
static void IFC30(void){ISRInterrupt(30);}

static void IFC31(void){ISRInterrupt(31);}
static void IFC32(void){ISRInterrupt(32);}
static void IFC33(void){ISRInterrupt(33);}
static void IFC34(void){ISRInterrupt(34);}
static void IFC35(void){ISRInterrupt(35);}
static void IFC36(void){ISRInterrupt(36);}
static void IFC37(void){ISRInterrupt(37);}
static void IFC38(void){ISRInterrupt(38);}
static void IFC39(void){ISRInterrupt(39);}
static void IFC40(void){ISRInterrupt(40);}

static int wpi_isr (lua_State *L) {
	if(lua_gettop(L) != 3) luaL_error(L,"Invalid number of arguments.");
	unsigned int pin = (unsigned int) lua_tointeger(L,1);
  if (pin<1 || pin>40) luaL_error(L,"Invalid ISR pin number");
	int edgeType = lua_tointeger(L,2);
  int index = 3;
  int res = -1;
  if (lua_isfunction(L,index)) {
      int top = lua_gettop(L);
      lua_settop(L,index);
      int luaFunc = luaL_ref(L, LUA_REGISTRYINDEX);      
      lua_settop(L,top);
      ISRLuaCallback[pin-1].L = L;
      ISRLuaCallback[pin-1].luaFunc = luaFunc;
      
      void (*fptr)();
      switch(pin) {
        case 1: fptr = IFC1; break;
        case 2: fptr = IFC2; break;
        case 3: fptr = IFC3; break;
        case 4: fptr = IFC4; break;
        case 5: fptr = IFC5; break;
        case 6: fptr = IFC6; break;
        case 7: fptr = IFC7; break;
        case 8: fptr = IFC8; break;
        case 9: fptr = IFC9; break;
        case 10: fptr = IFC10; break;
        case 11: fptr = IFC11; break;
        case 12: fptr = IFC12; break;
        case 13: fptr = IFC13; break;
        case 14: fptr = IFC14; break;
        case 15: fptr = IFC15; break;
        case 16: fptr = IFC16; break;
        case 17: fptr = IFC17; break;
        case 18: fptr = IFC18; break;
        case 19: fptr = IFC19; break;
        case 20: fptr = IFC20; break;
        case 21: fptr = IFC21; break;
        case 22: fptr = IFC22; break;
        case 23: fptr = IFC23; break;
        case 24: fptr = IFC24; break;
        case 25: fptr = IFC25; break;
        case 26: fptr = IFC26; break;
        case 27: fptr = IFC27; break;
        case 28: fptr = IFC28; break;
        case 29: fptr = IFC29; break;
        case 30: fptr = IFC30; break;
        case 31: fptr = IFC31; break;
        case 32: fptr = IFC32; break;
        case 33: fptr = IFC33; break;
        case 34: fptr = IFC34; break;
        case 35: fptr = IFC35; break;
        case 36: fptr = IFC36; break;
        case 37: fptr = IFC37; break;
        case 38: fptr = IFC38; break;
        case 39: fptr = IFC39; break;
        case 40: fptr = IFC40; break;
        default: break;
      }
      res = wiringPiISR(pin,edgeType,fptr) ;
  } else luaL_error(L,"Invalid ISR callback function");
  lua_pushinteger(L,res);
	return 1;
}

// RASPBERRY TOOLS
// piBoardId (&model, &rev, &mem, &maker, &overVolted) ;
static int wpi_piboardid (lua_State *L) {
	int model, rev, mem, maker, overVolted;
	piBoardId (&model, &rev, &mem, &maker, &overVolted);
	lua_pushinteger(L,model);
	lua_pushinteger(L,rev);
	lua_pushinteger(L,mem);
	lua_pushinteger(L,maker);
	lua_pushinteger(L,overVolted);
	return 5;
}

static char *physNames [64] = 
{
  NULL,

  "   3.3v", "5v     ",
  "  SDA.1", "5V     ",
  "  SCL.1", "0v     ",
  "GPIO. 7", "TxD    ",
  "     0v", "RxD    ",
  "GPIO. 0", "GPIO. 1",
  "GPIO. 2", "0v     ",
  "GPIO. 3", "GPIO. 4",
  "   3.3v", "GPIO. 5",
  "   MOSI", "0v     ",
  "   MISO", "GPIO. 6",
  "   SCLK", "CE0    ",
  "     0v", "CE1    ",
  "  SDA.0", "SCL.0  ",
  "GPIO.21", "0v     ",
  "GPIO.22", "GPIO.26",
  "GPIO.23", "0v     ",
  "GPIO.24", "GPIO.27",
  "GPIO.25", "GPIO.28",
  "     0v", "GPIO.29",
       NULL, NULL,
       NULL, NULL,
       NULL, NULL,
       NULL, NULL,
       NULL, NULL,
  "GPIO.17", "GPIO.18",
  "GPIO.19", "GPIO.20",
   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
};
static char *alts [] = { "IN", "OUT", "ALT5", "ALT4", "ALT0", "ALT1", "ALT2", "ALT3" };
extern int wpMode;
static int physToWpi [64] = 
{
  -1,           // 0
  -1, -1,       // 1, 2
   8, -1,
   9, -1,
   7, 15,
  -1, 16,
   0,  1,
   2, -1,
   3,  4,
  -1,  5,
  12, -1,
  13,  6,
  14, 10,
  -1, 11,       // 25, 26
  30, 31,	// Actually I2C, but not used
  21, -1,
  22, 26,
  23, -1,
  24, 27,
  25, 28,
  -1, 29,
  -1, -1,
  -1, -1,
  -1, -1,
  -1, -1,
  -1, -1,
  17, 18,
  19, 20,
  -1, -1, -1, -1, -1, -1, -1, -1, -1
};
// Physical pin number required!
static int wpi_pininfo (lua_State *L) {	
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");	
	int physPin = lua_tointeger(L,1);
	lua_settop(L,0);
	// Pin physical number
	lua_pushinteger(L,physPin) ;
	// BCM | wPi 
	if (physPinToGpio (physPin) == -1) {
		lua_pushinteger(L,-1);
		lua_pushinteger(L,-1);
	} else {
		lua_pushinteger(L,physPinToGpio (physPin));
		lua_pushinteger(L,physToWpi [physPin]);
	}
    // Name
	lua_pushstring(L,physNames [physPin]);
	// Mode | Value
	if (physToWpi [physPin] == -1) {
		lua_pushnil(L);
		lua_pushinteger(L,-1);
	} else {
		lua_pushstring(L,alts [getAlt (physPin)]) ;
		lua_pushinteger(L,digitalRead (physPin)) ;
	}	
	return 6;
}

static int wpi_phystogpio (lua_State *L) {
	if(lua_gettop(L) != 1) luaL_error(L,"Invalid number of arguments.");	
	int pin = lua_tointeger(L,1);
	lua_settop(L,0);	
	lua_pushinteger(L,physPinToGpio(pin)) ;
	return 6;
}

// ---------------------------------------------------------------------

static const struct luaL_Reg wpilib[] = {

// SETUP
{"setup", wpi_setup},
{"setupGpio", wpi_setup_gpio},
{"setupPhys", wpi_setup_phys},
{"setupSys", wpi_setup_sys},

// RPI

{"writeByte", wpi_writebyte},
{"readByte", wpi_readbyte},
{"pwmmode", wpi_pwmmode},
{"pwmrange", wpi_pwmrange},
{"pwmclock", wpi_pwmclock},
{"rev", wpi_rev},
{"pin2gpio", wpi_pin2gpio},
{"physpin2gpio", wpi_physpin2gpio},

// GPIO
{"mode", wpi_mode},
{"pud", wpi_pud},
{"read", wpi_read},
{"write", wpi_write},

// TIMING
{"millis", wpi_millis},
{"micros", wpi_micros},
{"delay", wpi_delay},
{"msdelay", wpi_msdelay},

// SHIFT
{"shiftin", wpi_shiftin},
{"shiftout", wpi_shiftout},

// I2C
{"i2csetup", wpi_setupi2c},
{"i2csetupif", wpi_setupi2cif},
{"i2cread", wpi_i2cread},
{"i2cwrite", wpi_i2cwrite},
{"i2cwriter8", wpi_i2cwriter8},
{"i2cwriter16", wpi_i2cwriter16},
{"i2creadr8", wpi_i2creadr8},
{"i2creadr16", wpi_i2creadr16},

// SOFT PWM
{"pwm", wpi_pwm},
{"freq", wpi_freq},

// ISR
{"isr", wpi_isr},

// TOOLS
{"piboardid", wpi_piboardid},
{"pininfo", wpi_pininfo},
{"phystogpio", wpi_phystogpio},

{NULL, NULL}
};

int luaopen_wiringPi (lua_State *L) {
  luaL_newlib(L, wpilib);
  return 1;
}
