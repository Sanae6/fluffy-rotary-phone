#include "Graphics.hpp"

int loadTexture(lua_State* l) {//loadTexture(location, name)
	int top = lua_gettop(l);
	if (top != 2 || !lua_isstring(l, -1) || !lua_isstring(l, -2)) {
		lua_error(l);
		return false;
	}
	const char* location = lua_tostring(l, -2);
	//printf(location);
	SDL_Surface* surf = IMG_Load(location);
	const char* name = lua_tostring(l, -1);
	SDL_Texture* t = SDL_CreateTextureFromSurface(g->renderer, surf);
	//printf("loaded surf: %s(w=%d,h=%d) ", name,surf->w,surf->h);
	int w,h;
	SDL_QueryTexture(t,NULL,NULL,&w,&h);
	//printf("tex: %s(w=%d,h=%d)\n", name, w, h);
	Texture* tex = new Texture(name, t);
	g->addTexture(name, tex);
	Texture* b = g->getTexture(name);
	if (b != tex) {
		SDL_TriggerBreakpoint();
	}
	return true;
}
int textureLocations(lua_State* l) {//texLoc(name,sx,sy,sw,sh,dx,dy,dw,dh) - name, source, destination positions
	//todo
	int top = lua_gettop(l);
	if (top != 9) {
		lua_error(l);
		lua_pushstring(l, "Argument count isn't 9");
		return false;
	}
	if (!lua_isstring(l, -9) || !lua_isnumber(l, -8) || !lua_isnumber(l, -7) || !lua_isnumber(l, -6) || !lua_isnumber(l, -5)
		|| !lua_isnumber(l, -4) || !lua_isnumber(l, -3) || !lua_isnumber(l, -2) || !lua_isnumber(l, -1)) {
		lua_error(l);
		lua_pushstring(l,"An argument has a mismatched type");
		return false;
	}
}
bruh drawTexture(lua_State* l) {//drawTexture(name)
	int top = lua_gettop(l);
	if (top != 1 || !lua_isstring(l,-1)) {
		lua_error(l);
		return false;
	}
	else {
		const char* name = lua_tostring(l,-1);
		if (g->hasTexture(name)){
			Texture *t = g->getTexture(name);
			SDL_RenderCopy(g->renderer,t->texture,t->source,t->dest);
			return true;
		}else {
			return false;
		}
	}
}
Texture::Texture(const char* name, SDL_Texture* tex) {
	this->name = name;
	//printf(name);
	texture = tex;
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