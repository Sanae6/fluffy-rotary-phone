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
	double t = 0.0;
	double dt = 1 / 60.0;

	high_resolution_clock hrc = chrono::high_resolution_clock();
	high_resolution_clock::time_point current = hrc.now();
	duration<double> frametime;
	high_resolution_clock::time_point newtime = current;
	while (!game.shouldClose()) {
		newtime = hrc.now();
		frametime = duration_cast<duration<double>>(newtime - current);
		current = newtime;
		double ftc = frametime.count();
		long updatecount = 0;
		printf("time update %1.7f\n", ftc);
		while (ftc > 0.0) {
			double deltatime = std::fmin(ftc, dt);
			game.update(t, deltatime);
			frametime -= duration<double>(deltatime);
			ftc = frametime.count();
			t += frametime.count();
			updatecount++;
		}
		SDL_SetWindowTitle(game.window, toString(updatecount));
		game.render();
		if (game.shouldClose()) {
			lua_getglobal(ls, "closing");
			lua_call(ls, 0, 0);
		}
	}
}

