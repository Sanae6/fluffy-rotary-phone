#include "Graphics.hpp"

int loadTexture(lua_State* l) {//loadTexture(location, name)
	int top = lua_gettop(l);
	if (top != 2 || !lua_isstring(l, -1) || !lua_isstring(l, -2)) {
		lua_error(l);
		return false;
	}
	const char* location = lua_tostring(l, -2);
	SDL_Surface* surf = IMG_Load(location);
	const char* name = lua_tostring(l, -1);
	SDL_Texture* t = SDL_CreateTextureFromSurface(g->renderer, surf);
	int w,h;
	SDL_QueryTexture(t,NULL,NULL,&w,&h);
	Texture* tex = new Texture(name, t);
	g->addTexture(name, tex);
	Texture* b = g->getTexture(name);
	if (b != tex) {
		SDL_TriggerBreakpoint();
	}
	return true;
}

bruh drawTexture(lua_State* l) {//drawTexture(name, x, y)
	int top = lua_gettop(l);
	if (top != 3) {
		lua_pushstring(l, "Argument count isn't 3");
		lua_error(l);
		return false;
	}
	if (!lua_isstring(l, -3) || !lua_isnumber(l, -2) || !lua_isnumber(l, -1)) {
		lua_pushstring(l, "An argument has a mismatched type");
		lua_error(l);
		return false;
	}
	else {
		const char* name = lua_tostring(l,-3);
		if (g->hasTexture(name)){
			Texture *t = g->getTexture(name);
			SDL_Rect dest = {lua_tonumber(l,-2),lua_tonumber(l,-1),t->width,t->height};
			SDL_RenderCopy(g->renderer, t->texture, t->source, &dest);
			return true;
		}else {
			return false;
		}
	}
}
Texture::Texture(const char* name, SDL_Texture* tex) {
	this->name = name;
	texture = tex;
	SDL_QueryTexture(tex, NULL, NULL, &width, &height);
}
Texture::~Texture() {
	printf("Bruh");
}

void luaopen_graphics(lua_State* L) {
	lua_pushcfunction(L, loadTexture);
	lua_setglobal(L, "loadTexture");
	lua_pushcfunction(L, drawTexture);
	lua_setglobal(L, "drawTexture");
}