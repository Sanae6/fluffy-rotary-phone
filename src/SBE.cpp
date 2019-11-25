#include "SBE.hpp"

using namespace std;

Game* g;

int main(int argc, char* argv[])
{
	lua_State* ls = luaL_newstate();
	Game game = Game(ls);
	g = &game;
	printf("Compiled on %s\n", __DATE__);
	game.init();
	while (!game.shouldClose()) {
		game.update();
		game.render();
		if (game.shouldClose()) {
			lua_getglobal(ls, "closing");
			lua_call(ls, 0, 0);
		}
	}
}

