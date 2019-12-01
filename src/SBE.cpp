#include "SBE.hpp"
#include <chrono>
using namespace std::chrono;

using namespace std;

Game* g;
char* toString(long integer) {
	char* array = new char[64];
	int myInteger = 4711;
	sprintf(array, "%d", integer);
	return array;
}

int main(int argc, char* argv[])
{
	lua_State* ls = luaL_newstate();
	Game game = Game(ls);
	g = &game;
	printf("Compiled on %s\n", __DATE__);
	game.init();
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;
	while (!game.shouldClose()) {
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		game.update(NOW, deltaTime);
		game.render();
		if (game.shouldClose()) {
			lua_getglobal(ls, "closing");
			lua_call(ls, 0, 0);
		}
	}
}

