#ifndef GFX_HEADER
#define GFX_HEADER
#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <memory>
//Texture wrapper structure
struct Texture {
public:
	SDL_Texture* texture;
	const char* name;
	SDL_Rect* source = NULL;
	SDL_Rect* dest = NULL;
	Texture(const char*, SDL_Texture*);
private:
	~Texture();
};
void luaopen_graphics(lua_State*);
#include "Game.h"
#endif