#include "SDL.h"
#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[]) {

	game = new Game();
	game->init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, true);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();

	}

	game->clean();
	
	
	/*SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	//-1 = index, 0 = flag
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	
	//color green
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);

	//show screen for 3 seconds
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	*/

	return 0;
}