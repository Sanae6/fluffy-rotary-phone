#include "Window.hpp"

int setWindowTitle(lua_State* l) {
	int t = lua_gettop(l);
	if (t != 1) {
		lua_pushstring(l,"Argument count must be 1!");
		lua_error(l);
		return 1;
	}
	else if (!lua_isstring(l, -1)) {
		lua_pushstring(l, "Argument is not a string!");
		lua_error(l);
		return 1;
	}
	SDL_SetWindowTitle(g->window, lua_tostring(l,-1));
	return 0;
}

int setShouldClose(lua_State* l) {
	int t = lua_gettop(l);
	if (t != 1) {
		lua_pushstring(l, "Argument count must be 1!");
		lua_error(l);
		return 1;
	}
	else if (!lua_isboolean(l, -1)) {
		lua_pushstring(l, "Argument is not a boolean!");
		lua_error(l);
		return 1;
	}
	g->setShouldClose(lua_toboolean(l, -1));
	return 0;
}

void luaopen_window(lua_State* l) {
	lua_pushcfunction(l, setWindowTitle);
	lua_setglobal(l, "setTitle");
	lua_pushcfunction(l, setShouldClose);
	lua_setglobal(l, "setShouldClose");
}