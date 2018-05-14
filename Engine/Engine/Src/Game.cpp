#include "Game.h"
#include "TextureManager.h" //textures
#include "Map.h"
#include "ECS/Components.h" //Components has all types of components included within
#include "Vector2D.h"

Map *map;

//The game renderer, static 
SDL_Renderer *Game::renderer = nullptr;

//adds a new player to the entities
Manager manager;
auto& player(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	
	//creates player texture through GameObject and TextureManager
	//player = new GameObject("Assets/player.png", 0 ,0);
	//enemy = new GameObject("Assets/enemy.png", 50, 50);
	
	
	map = new Map();

	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("Assets/player.png");
	//starts at 500 500 position
   // player.getComponent<PositionComponent>().setPos(500, 500);
	

}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));
	if (player.getComponent<TransformComponent>().position.x > 100) {

		player.getComponent<SpriteComponent>().setTex("Assets/enemy.png");
	}
	std::cout << player.getComponent<TransformComponent>().position.y << std::endl;
/*	player->Update();
	//updates entities and thus updates all the components
	
	std::cout << newPlayer.getComponent<PositionComponent>().x() << "," <<
		newPlayer.getComponent<PositionComponent>().y() << std::endl;
	//map->LoadMap();
*/
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//source and destination rectangles -> use whole image and then to destR render frame
	//SDL_RenderCopy(renderer, playerTex, NULL, &destR);

	//TextureManager has Draw func that does a render copy
	map->DrawMap();
	manager.draw();
	//player->Render();

	SDL_RenderPresent(renderer);
}

void Game::clean()  
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}