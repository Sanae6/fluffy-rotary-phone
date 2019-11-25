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
	if (!lua_isnumber(ls, -3)) {
		fprintf(stderr, "Window width is not a number!");
		lua_close(ls);
		exit(1);
	};
	if (!lua_isnumber(ls, -2)) {
		fprintf(stderr, "Window height is not a number!");
		lua_close(ls);
		exit(1);
	};
	if (!lua_isstring(ls, -1)) {
		fprintf(stderr, "Window title is not a string!");
		lua_close(ls);
		exit(1);
	};
	int w = lua_tonumber(ls, -3);
	int h = lua_tonumber(ls, -2);
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
	if (evt.type == SDL_KEYDOWN) {
		keys[evt.key.keysym.sym] = true;
		lua_getglobal(ls, "keydown");
		lua_pushinteger(ls, evt.key.keysym.sym);
		lua_call(ls, 1, 0);
	}

	if (evt.type == SDL_KEYUP) {
		int k = evt.key.keysym.sym;
		keys[k] = false;
	}
}
void Game::update() {
	while (SDL_PollEvent(&evt)&&(!shouldClose())) handleEvent();
	if (shouldClose())return;
	lua_getglobal(ls, "update");
	lua_call(ls, 0, 0);
}
void Game::render() {
	if (shouldClose())return;
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, 0);
	lua_getglobal(ls, "draw");
	lua_call(ls, 0, 0);
	SDL_RenderPresent(renderer);
}
 