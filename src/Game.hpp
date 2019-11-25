#ifndef GAME_HEADER
#define GAME_HEADER
#include <iostream>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.hpp"
#include "Window.hpp"
struct comp {
	bool operator () (const char* lhs, const char* rhs) const {
		return !strcmp(lhs, rhs);
	};
};
struct Game {
	bool close = false;
	lua_State* ls;
	std::unordered_map<const char*, Texture*, std::hash<const char*>, comp> textures = 
		std::unordered_map<const char*, Texture*, std::hash<const char*>, comp>();
	std::unordered_map<int, bool> keys = std::unordered_map<int, bool>();
	
	SDL_Window* window;
	SDL_Surface* surf;
	SDL_Renderer* renderer;
	SDL_Event evt;
	Game(lua_State*);
	void init();
	~Game();
	void update();
	bool shouldClose() {
		return close;
	}
	void render();
	void handleEvent();
	void setShouldClose(bool close) {
		this->close = close;
	}
	void addTexture(const char* name, Texture* tex) {
		textures[name] = tex;
	}
	bool hasTexture(const char* name){
		return textures.contains(name);
	}
	void printAllTexnames() {
		for (auto i : textures) {
			printf("%s:%s\n", i.first, i.second->name);
		}
	}
	bool isKeyPressed(int key) {
		if (keys.contains(key)) {
			auto it = keys.find(key);
			if (it == keys.end())return NULL;
			else return it->second;
		}
		else return false;
	}
	Texture* getTexture(const char* name) {
		auto it = textures.find(name);
		if (it == textures.end())return NULL;
		else return it->second;
	}
};
extern Game* g;
typedef int bruh; //i'm genuinely tempted to replace all ints in my source with bruh not joking i could do this and nobody could stop me
#endif 