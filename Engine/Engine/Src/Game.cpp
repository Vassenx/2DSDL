#pragma once

#include "Game.h"
#include "TextureManager.h" //textures
#include "Map.h"
#include "ECS/Components.h" //Components has all types of components included within
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

Map *map;
Manager manager;

//The game renderer, static 
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

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
	
	assets->AddTexture("terrain", "Assets/terrain_ss.png");
	assets->AddTexture("player", "Assets/player_anims.png");
	assets->AddTexture("projectile", "Assets/enemy.png");

	//uses id from AssetManager
	map = new Map("terrain", 3, 32);
    map->LoadMap("Assets/map.map", 25, 20);

	//If scale of 2, as 32 x 32 -> 64 x 64
	player.addComponent<TransformComponent>(800.0f,640.0f,32,32,4);
	//true = isAnimated
	//uses id from AssetManager
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<Gravity>();
	//change this for water zones
	player.getComponent<Gravity>().wantGravity = true;
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	assets->CreateProjectile(Vector2D(600.0f, 600.0f),Vector2D(2,0), 200, 2, "projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

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

	std::cout << player.getComponent<TransformComponent>().velocity.y << std::endl;

	manager.refresh();
	manager.update();

	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			std::cout << "Hit" << std::endl;


			//BUG: The collision is being detected again before the player can move away, which
			//means the collision happens a few times.

			//player.getComponent<TransformComponent>().position = playerPos;
			player.getComponent<Gravity>().wantGravity = false;
			player.getComponent<TransformComponent>().velocity.y 
				+= player.getComponent<TransformComponent>().velocity.y * -5;
		}
	}

	for (auto& pr : projectiles) {
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, pr->getComponent<ColliderComponent>().collider)) {
			pr->destroy();
		}
	}

	//keep player in the middle
	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

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
	//over top of players is projectiles
	for (auto& pr : projectiles) {
		pr->draw();
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
