#ifndef PIOTBOX_H
#define PIOTBOX_H

#define PRG_NAME        "pIOTbox" 
#define PRG_VERSION     "1.0"

#include <lua.hpp>

static volatile int keepRunning = 1; //for ctrl+c interrupt

int luaCall(lua_State *L, const char *script );
int luaFuncCall(lua_State *L, const char *func, int intpar );
int luaFuncCall2(lua_State *L, const char *func, int intpar1, int intpar2 );
int getButtonState(lua_State* l);




#endif