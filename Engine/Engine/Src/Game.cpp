#include "Game.h"
#include "TextureManager.h" //textures
#include "Map.h"
#include "ECS/Components.h" //Components has all types of components included within
#include "Vector2D.h"
#include "Collision.h"

Map *map;
Manager manager;

//The game renderer, static 
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

bool Game::isRunning = false;

//adds a new player to the entities
auto& player(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer){
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	
	map = new Map("Assets/terrain_ss.png", 3, 32);
    map->LoadMap("Assets/map.map", 25, 20);

	//If scale of 2, as 32 x 32 -> 64 x 64
	player.addComponent<TransformComponent>(800.0f,640.0f,32,32,4);
	//true = isAnimated
	player.addComponent<SpriteComponent>("Assets/player_anims.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvents()
{
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

void Game::update(){
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	//where player is before he moves in update
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			std::cout << "Hit" << std::endl;
			//push the player back
			player.getComponent<TransformComponent>().position = playerPos;
			//player.getComponent<TransformComponent>().velocity * -1;
		}
	}

	//keep player in the middle
	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	//bounds
	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	//width/height should be length of map (25 by 20 times by 32 = 800 by 640)
	if (camera.x > camera.w) {
		camera.x = camera.w;
	}
	if (camera.y > camera.h) {
		camera.y = camera.h;
	}

	//scrolling instead of player in middle

	/*Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles) {
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	}
	*/
	//changing player's sprite
	//player.getComponent<SpriteComponent>().setTex("Assets/enemy.png");

}

void Game::render()
{
	SDL_RenderClear(renderer);
	//layer ordering
	for (auto& t : tiles) {
		t->draw();
	}
	//if want to show where the colliders and enemies are on the actual map
	for (auto& c : colliders) {
		c->draw();
	}
	for (auto& p : players) {
		p->draw();
	}

	/*for (auto& e : enemies) {
		e->draw();
	}*/
	SDL_RenderPresent(renderer);
}

void Game::clean()  
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
