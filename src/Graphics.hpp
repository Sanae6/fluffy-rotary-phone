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
	int width,height;
	double angle = 0;//clockwise
	SDL_Point* center = NULL;//defaults to center of texture
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	Texture(const char*, SDL_Texture*);
private:
	~Texture();
};
void luaopen_graphics(lua_State*);
#include "Game.hpp"
#endif