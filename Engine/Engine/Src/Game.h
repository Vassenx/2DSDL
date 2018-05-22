#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	enum groupLabels : std::size_t {
		//naming groups. up to 32
		groupMap,
		groupPlayers,
		//groupEnemies,
		groupColliders
	};

	//static: shared by all objects
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;

private:

	int cnt = 0;
	SDL_Window *window;
};