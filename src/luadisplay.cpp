#include <lua.hpp>
#include <iostream>

#include "luadisplay.h"

//LIBRARY FUNCTION
int open(lua_State* l){
	int opt = lua_tointeger(l,1);
	if (lua_gettop(l) && opt>-1 && opt<7) {
		// Setup OLED SPI
		if (display.oled_is_spi_proto(opts[opt].oled)) {
			// SPI change parameters to fit to your LCD
			if ( !display.init(OLED_SPI_DC,OLED_SPI_RESET,OLED_SPI_CS, opts[opt].oled) ) {
				lua_pushnumber(l,-1);
				return 1;
			}
		}
		else { 
			// I2C change parameters to fit to your LCD
			if ( !display.init(OLED_I2C_RESET,opts[opt].oled) ) {
				lua_pushnumber(l,-1);
				return 1;
			}
		}
		display.begin();
		lua_pushnumber(l,0);
	} else {
		lua_pushnumber(l,-1);
	}
	return 1;
}

int close(lua_State* l){
    display.close();
    return 0;
}
	 
int clear(lua_State* l){
    display.clearDisplay();
    return 0;
}

int do_display(lua_State* l){
    display.display();
    return 0;
}

int width(lua_State* l){
    lua_pushinteger(l,display.width());
    return 1;
}

int height(lua_State* l){
    lua_pushinteger(l,display.height());
    return 1;
}

int setCursor(lua_State* l){
	int x = lua_tointeger(l,1);
	int y = lua_tointeger(l,2);
	if (lua_gettop(l)==2) {
		display.setCursor(x,y);
	} 
	return 0;
}

int setTextSize(lua_State* l){
	int s = lua_tointeger(l,1);
	if (lua_gettop(l)==1) {
		display.setTextSize(s);
	} 
	return 0;
}

int setTextColor(lua_State* l){
	int c = lua_tointeger(l,1);
	if (lua_gettop(l)==1) {
		display.setTextColor(c);
	} 
	return 0;
}

int printf(lua_State* l){
	const char *s1 = lua_tostring(l,1);
	const char *s2 = lua_tostring(l,2);
	if (lua_gettop(l)==2) {
		display.printf(s1,s2);
	} else {
		display.printf(s1);
	}
	return 0;
}

int drawLine(lua_State* l){
	int x1 = lua_tointeger(l,1);
	int y1 = lua_tointeger(l,2);
	int x2 = lua_tointeger(l,3);
	int y2 = lua_tointeger(l,4);
	int c = lua_tointeger(l,5);
	if (lua_gettop(l)==5) {
		display.drawLine(x1, y1, x2, y2, c);
	} 
	return 0;
}

int drawFastVLine(lua_State* l){
	int x = lua_tointeger(l,1);
	int y = lua_tointeger(l,2);
	int h = lua_tointeger(l,3);
	int c = lua_tointeger(l,4);
	if (lua_gettop(l)==4) {
		display.drawFastVLine(x, y, h, c);
	} 
	return 0;
}

int drawFastHLine(lua_State* l){
	int x = lua_tointeger(l,1);
	int y = lua_tointeger(l,2);
	int w = lua_tointeger(l,3);
	int c = lua_tointeger(l,4);
	if (lua_gettop(l)==4) {
		display.drawFastHLine(x, y, w, c);
	} 
	return 0;
}

int drawRect(lua_State* l){
	int x = lua_tointeger(l,1);
	int y = lua_tointeger(l,2);
	int w = lua_tointeger(l,3);
	int h = lua_tointeger(l,4);
	int c = lua_tointeger(l,5);
	if (lua_gettop(l)==5) {
		display.drawRect(x, y, w, h, c);
	} 
	return 0;
}

int fillRect(lua_State* l){
	int x = lua_tointeger(l,1);
	int y = lua_tointeger(l,2);
	int w = lua_tointeger(l,3);
	int h = lua_tointeger(l,4);
	int c = lua_tointeger(l,5);
	if (lua_gettop(l)==5) {
		display.fillRect(x, y, w, h, c);
	} 
	return 0;
}

int drawHorizontalBargraph(lua_State* l){
	int x = lua_tointeger(l,1);
	int y = lua_tointeger(l,2);
	int w = lua_tointeger(l,3);
	int h = lua_tointeger(l,4);
	int c = lua_tointeger(l,5);
	int p = lua_tointeger(l,6);
	if (lua_gettop(l)==6) {
		display.drawHorizontalBargraph(x, y, w, h, c, p);
	} 
	return 0;
}

int drawVerticalBargraph(lua_State* l){
	int x = lua_tointeger(l,1);
	int y = lua_tointeger(l,2);
	int w = lua_tointeger(l,3);
	int h = lua_tointeger(l,4);
	int c = lua_tointeger(l,5);
	int p = lua_tointeger(l,6);
	if (lua_gettop(l)==6) {
		display.drawVerticalBargraph(x, y, w, h, c, p);
	} 
	return 0;
}

//OLED LIBRARY
static const struct luaL_Reg displayLib[] = {
    {"open", open},
	{"close", close},
	{"clear", clear},
	{"display", do_display},
	{"width", width},
	{"height", height},
	{"setCursor", setCursor},
	{"setTextSize", setTextSize},
	{"setTextColor", setTextColor},
	{"printf", printf},
	{"drawLine", drawLine},
	{"drawFastVLine", drawFastVLine},
	{"drawFastHLine", drawFastHLine},
	{"drawRect", drawRect},
	{"fillRect", fillRect},
	{"drawHorizontalBargraph", drawHorizontalBargraph},
	{"drawVerticalBargraph", drawVerticalBargraph},
	
    {NULL, NULL}
};

//LIBRARY OPEN FUNCTION
int luaopen_display (lua_State *L) {
	
     luaL_newlibtable(L, displayLib);
	 luaL_setfuncs(L, displayLib, 0);
	
    return 1;
}
