#ifndef GAME_HEADER
#define GAME_HEADER
#include <iostream>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.hpp"
struct comp {
	bool operator () (const char* lhs, const char* rhs) const {
		//printf(!strcmp(lhs, rhs) ? "true" : "false");
		return !strcmp(lhs, rhs);
	};
};
struct Game {
	bool close = false;
	lua_State* ls;
	std::unordered_map<const char*, Texture*, std::hash<const char*>, comp> textures;
	std::vector<Texture*> drawables = std::vector<Texture*>();
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
	Texture* getTexture(const char* name) {
		auto it = textures.find(name);
		if (it == textures.end())return NULL;
		else return it->second;
	}
};
extern Game* g;
#endif 