#include "Game.h"

// stolen from http ://www.lua.org/manual/5.2/manual.html#4.8
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
	SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_OPENGL, &window, &renderer);
	const std::unordered_map<const char*, Texture*, std::hash<const char*>, comp> f = std::unordered_map<const char*, Texture*, std::hash<const char*>, comp>();
	textures = const_cast<std::unordered_map<const char*, Texture*,std::hash<const char*>,comp>&>(f);
	ls = state;
	luaL_openlibs(ls);
	luaopen_graphics(ls);
	surf = SDL_GetWindowSurface(window);
	close = false;

}
Game::~Game() {
	IMG_Quit();
	SDL_Quit();
}
void Game::init() {
	int i = luaL_loadfile(ls, "data/menu.lua");
	if (i != LUA_OK) {
		fprintf(stderr, "%s\n", lua_tostring(ls, -1));
		lua_pop(ls, 1);
		lua_close(ls);
		exit(1);
	}
	lua_pcall(ls, 0, 0, 0);
	lua_getglobal(ls, "begin");
	lua_call(ls, 0, 0);
	printAllTexnames();
}
void Game::handleEvent() {
	if (evt.type == SDL_KEYDOWN || evt.type == SDL_QUIT) {
		setShouldClose(true);//their faces when bruh 
	}
}
void Game::update() {
	while (SDL_PollEvent(&evt)) handleEvent();
	lua_getglobal(ls, "update");
	lua_call(ls, 0, 0);
}
void Game::render() {
	SDL_FillRect(surf, 0, SDL_MapRGB(surf->format, 0xFF, 0xFF, 0xFF));
	lua_getglobal(ls, "draw");
	lua_call(ls, 0, 0);
	SDL_UpdateWindowSurface(window);
}
 