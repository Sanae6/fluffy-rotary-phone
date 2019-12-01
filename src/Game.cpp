#include "Game.hpp"

// stolen from http://www.lua.org/manual/5.2/manual.html#4.8
static void* l_alloc(void* ud, void* ptr, size_t osize,
	size_t nsize) {
	(void)ud;  (void)osize;  /* not used */
	if (nsize == 0) {
		free(ptr);
		return NULL;
	}
	else
		return realloc(ptr, nsize);
}
Game::Game(lua_State* state) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP) < 0) {
		printf("SDL2 could not initialize: \nSDL ERROR: %s\nSDLIMG ERROR: %s", SDL_GetError(), IMG_GetError());
		exit(1);
	}
	ls = state;
	luaL_openlibs(ls);
	luaopen_graphics(ls);
	luaopen_window(ls);
	close = false;
	int i = luaL_loadfile(ls, "game/define.lua");
	if (i != LUA_OK) {
		fprintf(stderr, "%s\n", lua_tostring(ls, -1));
		lua_pop(ls, 1);
		lua_close(ls);
		exit(1);
	}
	lua_pcall(ls, 0, 0, 0);
	lua_getglobal(ls, "settings");
	lua_getfield(ls, lua_gettop(ls), "width");
	lua_getfield(ls, lua_gettop(ls)-1, "height");
	lua_getfield(ls, lua_gettop(ls)-2, "title");
	if (!lua_isinteger(ls, -3)) {
		fprintf(stderr, "Window width is not an integer!");
		lua_close(ls);
		exit(1);
	};
	if (!lua_isinteger(ls, -2)) {
		fprintf(stderr, "Window height is not an integer!");
		lua_close(ls);
		exit(1);
	};
	if (!lua_isstring(ls, -1)) {
		fprintf(stderr, "Window title is not a string!");
		lua_close(ls);
		exit(1);
	};
	long w = lua_tointeger(ls, -3);
	long h = lua_tointeger(ls, -2);
	printf("window size: %d,%d\n", w, h);
	SDL_CreateWindowAndRenderer(w,h, SDL_WINDOW_OPENGL, &window, &renderer);
	SDL_SetWindowTitle(window, lua_tostring(ls,-1));
	surf = SDL_GetWindowSurface(window);
}
Game::~Game() {
	lua_getglobal(ls, "stopped");
	lua_call(ls, 0, 0);
	IMG_Quit();
	SDL_Quit();
}
void Game::init() {
	int i = luaL_dofile(ls, "game/menu.lua");
	if (i != LUA_OK) {
		fprintf(stderr, "%s\n", lua_tostring(ls, -1));
		lua_pop(ls, 1);
		lua_close(ls);
		exit(1);
	}
	lua_getglobal(ls, "begin");
	lua_call(ls, 0, 0);
	//printAllTexnames();
}
void Game::handleEvent() {//temporary escape button
	if ((evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE) || evt.type == SDL_QUIT) {
		setShouldClose(true);//their faces when bruh
		return;
	}
	if (evt.type == SDL_KEYDOWN||evt.type == SDL_KEYUP) {
		int k = evt.key.keysym.sym;
		keys[k] = evt.type == SDL_KEYDOWN;
		lua_getglobal(ls, keys[k]?"keydown":"keyup");
		lua_pushinteger(ls, k);
		lua_call(ls, 1, 0);
	}
}
void Game::update(double t, double dt) {
	while (SDL_PollEvent(&evt)&&(!shouldClose())) handleEvent();
	if (shouldClose())return;
	lua_getglobal(ls, "update");
	lua_pushnumber(ls, t);
	lua_pushnumber(ls, dt);
	lua_call(ls, 2, 0);
}
void Game::render() {
	if (shouldClose())return;
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, 0);
	lua_getglobal(ls, "draw");
	lua_call(ls, 0, 0);
	SDL_RenderPresent(renderer);
}
 