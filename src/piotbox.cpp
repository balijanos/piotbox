/******************************************************************
 Raspberry PI Simple Controller application
 (C) 2017, Hi-Project Ltd.
           hiproject.hu@gmail.com
 
	2017-11-28 Initial version

	Thanks to 
		Charles-Henri Hallard (http://hallard.me) for ArduPi_OLED library
		Andrew Stine for roraryencoder.c
		Gordon Henderson for wiringPi           
******************************************************************/
#include <string>
#include <vector>

extern "C" {
	   #include "compat.h"
       #include <wiringPi.h>
       #include <signal.h>
       #include <getopt.h>  
	   #include "luawpi.h"
	   #include "rotaryencoder.h"
       #include "buttons.h"
       #include "encoders.h"
}
#include "luadisplay.h"
#include "piotbox.h"

// -----------------------------------------------------

void intHandler(int sig)
{
   keepRunning = 0;
   fprintf(stderr,"\nctrl+c detected! exiting...\n");
}

int buttonChangeHandler(int i)
{  
   int changed = 0;
   if (ButtonState[i].value!=ButtonState[i].orig){ // changed
      unsigned int stime = millis ();
      changed = 1;
      if (ButtonState[i].value==0) { 
            // button pressed            
            ButtonState[i].orig = 0;
            ButtonState[i].pressed = 1;
            ButtonState[i].released = 0;
            ButtonState[i].ptime = stime;
            ButtonState[i].rtime = stime;
      } else {
            // button released            
            ButtonState[i].orig = 1;
            ButtonState[i].pressed = 0;
            ButtonState[i].released = 1;
            ButtonState[i].rtime = stime;
      }        
   }
   return changed;
}

int scanInputs(lua_State *L)
{  
	int exitCode = 1;	// keep running
    
	// Rotary encoder	
	updateEncoders();
	int i=0; 
	while (EncoderState[i].rotaryenc!=NULL) {
		int l = EncoderState[i].rotaryenc->value;
		int diff;
		if(l!=EncoderState[i].value) {
			EncoderState[i].value = l;        
			diff = EncoderState[i].value-EncoderState[i].orig;       
			// sensitive rotary for menu       
			if ((diff>EncoderState[i].sens || -diff>EncoderState[i].sens) && strlen(encoderCallback)!=0) {  
				// rotary changed
				luaFuncCall2(L, encoderCallback, i, diff);
				EncoderState[i].orig = l;
			}
		}	
		i++;
	}
    // Buttons
	i=0; 
    while (ButtonState[i].pin!=-1) {
        ButtonState[i].value = digitalRead(ButtonState[i].pin); 
        if (buttonChangeHandler(i)) {
			if (ButtonState[i].released && strlen(buttonCallback)!=0) {				
				// button released
				exitCode = luaFuncCall2(L,buttonCallback,i, ButtonState[i].rtime-ButtonState[i].ptime);
            }
        }  
		i++;
    }   
	return exitCode;
}

// Lua funcs

int luaExec(lua_State *L, const char *script ) {
   int ret=0;   
   if ( luaL_loadfile(L, script) || lua_pcall(L, 0, 0, 0) ) {	
		   return luaL_error(L, lua_tostring(L,-1));
    }
    return ret;
}

int luaFuncCall(lua_State *L, const char *func, int intpar ) {
	int ret;
	lua_getglobal(L, func);
	lua_pushinteger(L, intpar);    
	if (lua_pcall(L, 1, 1, 0) != 0)
		return luaL_error(L, "error calling lua function(...)");
	if (lua_isnumber(L, -1))
		ret = lua_tointeger(L, -1);
	lua_pop(L, 1);  
	return ret;
}

int luaFuncCall2(lua_State *L, const char *func, int intpar1, int intpar2 ) {
	int ret;
	lua_getglobal(L, func);
	lua_pushinteger(L, intpar1);  
	lua_pushinteger(L, intpar2);  
	if (lua_pcall(L, 2, 1, 0) != 0)
		return luaL_error(L, "error calling lua function(...)");
	ret = lua_tointeger(L, -1);
	lua_pop(L, 1);  
	return ret;
}

int getButtonState(lua_State* l){
	int b = lua_tointeger(l,1);
	if (lua_isnumber(l,1) && b>=0 && b<MAX_BUTTONS)
		lua_pushinteger(l, ButtonState[b].value);
	else
		lua_pushinteger(l, -1);
	return 1;
}

int luaInit(lua_State* l) {
	// process PBOX_BUTTONS
	lua_getglobal(l, "PBOX_BUTTONS");
    if (lua_istable(l, -1)) {
		lua_pushnil(l); 
		int i = 0;
		while (lua_next(l, -2) != 0) {
			if (i<MAX_BUTTONS) {
				unsigned int pin = lua_tonumber(l, -1);
				unsigned int stime = millis ();
				pinMode(pin, INPUT); 
				pullUpDnControl(pin, PUD_UP); 
				ButtonState[i].pin = pin;
				ButtonState[i].value = 1;
				ButtonState[i].orig = 1;
				ButtonState[i].pressed = 0;
				ButtonState[i].released = 0;
				ButtonState[i].ptime = stime;
				ButtonState[i].rtime = stime;    
				lua_pop(l,1);
				i++;
				fprintf(stdout,"Button #%d pin: %d \n",i,pin);
			}
		}
	}
	// process PBOX_BUTTON_CALLBACK
	lua_getglobal(l, "PBOX_BUTTON_CALLBACK");
    if (lua_isstring(l, -1)) {
		strcpy(buttonCallback,lua_tostring(l,-1));
		fprintf(stdout,"ButtonCallback set to '%s'\n",buttonCallback);
	}
	// process PBOX_ENCODERS
	lua_getglobal(l, "PBOX_ENCODERS");
    if (lua_istable(l, -1)) {
		lua_pushnil(l);  
		int i = 0;
		while (lua_next(l, -2) != 0) {
			if (lua_istable(l,-1)) {
				lua_settop(l,-1);
				lua_pushnil(l); 
				unsigned int enc[2];
				unsigned int sens = 1;
				while (lua_next(l, -2) != 0) {
					if (strcmp(lua_tostring(l,-2),"sensitivity")==0)
						sens = lua_tointeger(l,-1);
					else if (strcmp(lua_tostring(l,-2),"clk")==0)
						enc[0] = lua_tointeger(l,-1);
					else if (strcmp(lua_tostring(l,-2),"dt")==0)
						enc[1] = lua_tointeger(l,-1);
					lua_pop(l,1);
				}
				if (i<MAX_ENCODERS) {
					EncoderState[i].rotaryenc = setupencoder(enc[0],enc[1]);
					EncoderState[i].sens = sens;
					fprintf(stdout,"Encoder #%d pins: %d %d sens: %d\n",i,enc[0],enc[1],sens);
				}
			}
			lua_pop(l, 1);
			i++;
		}
	}
	// process PBOX_ENCODER_CALLBACK
	lua_getglobal(l, "PBOX_ENCODER_CALLBACK");
    if (lua_isstring(l, -1)) {
		strcpy(encoderCallback,lua_tostring(l,-1));
		fprintf(stdout,"EncoderCallback set to '%s'\n",encoderCallback);
	}
		
	return 0;
}

const char *getLuaCallback(lua_State* l) {
	// process PBOX_CALLBACK
	lua_getglobal(l, "PBOX_CALLBACK");
    if (lua_isstring(l, -1)) {
		return lua_tostring(l,-1);
	}
	lua_pop(l,1);
	return NULL;
}

int main(int argc, char **argv)
{
	unsigned int i;
	int exitStatus;
	const char *cb;

	fprintf(stderr,"%s v%s\n", PRG_NAME, PRG_VERSION);
	//install sig handler
	signal(SIGINT, intHandler);

	if (wiringPiSetupGpio() == -1) {
	  fprintf(stderr,"wiringPi init failed\n");
	  return -1;
	}
  
	// LUA Initialization
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaL_requiref(L, "display", luaopen_display, 0);
	luaL_requiref(L, "wiringPi",luaopen_wiringPi, 0);
	
	lua_pushcfunction(L, getButtonState);
    lua_setglobal(L, "getButtonState");
	// lua_pushcfunction(L, getAnalogState);
    // lua_setglobal(L, "getAnalogState");

	if (luaL_dofile(L, "lua/piotbox.lua")) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
		return -1;
	}
	
	// read hardware config
	int err;
	if ((err=luaInit(L))!=0) {
		fprintf(stderr, "Error #%d reading configuration\n", err);
		return -1;
	}
	
	if (argc>1) {
		if ((err=luaExec(L,argv[1]))!=0) {
		  fprintf(stderr, "Error in user program %s\n", argv[1]);
		  return -1;
		}
		fprintf(stderr, "Executed user program %s\n", argv[1]);
	}
	
	//--------------------------------------
	// MAIN PROGRAM LOOP
	// -------------------------------------
	luaFuncCall(L, "initialize",0);
	while (keepRunning == 1) {
		scanInputs(L);         
		if ((cb=getLuaCallback(L))!=NULL) {
			keepRunning = luaFuncCall(L,cb,0);
		}
		delay(10);
	}
	exitStatus = luaFuncCall(L, "finalize",0); 
	// -------------------------------------
	fprintf(stderr, "%s exit: %d\n", PRG_NAME, exitStatus);
	return exitStatus;
}

