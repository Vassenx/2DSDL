#pragma once

#include "Game.h"
#include "TextureManager.h" //textures
#include "Map.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "../Src/ECS/ColliderComponent.h"
#include "../Src/ECS/SpriteComponent.h"
#include "../Src/Physics/Gravity.h"
#include "../Src/ECS/KeyboardController.h"

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
auto& enemy(manager.addEntity()); 
auto& jellyfish(manager.addEntity()); 

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
	assets->AddTexture("mermaid", "Assets/MermaidSheet.png"); 
	assets->AddTexture("jellyfish", "Assets/JellyV3coloured.png");

	//uses id from AssetManager
	map = new Map("terrain", 3, 32);
    map->LoadMap("Assets/map.map", 25, 20);

	//If scale of 2, as 32 x 32 -> 64 x 64
	player.addComponent<TransformComponent>(600.0f,640.0f,32,32,4, true);

	//true = isAnimated
	//uses id from AssetManager
	player.addComponent<SpriteComponent>("player", true);

	SpriteComponent& PlayerSpriteComponent = player.getComponent<SpriteComponent>(); 

	PlayerSpriteComponent.addAnimation("Idle", 0, 3, 100);
	PlayerSpriteComponent.addAnimation("Walk", 1, 8, 100);
	PlayerSpriteComponent.Play("Idle");
	//player.addComponent<Gravity>();
	//change this for water zones
	//player.getComponent<Gravity>().wantGravity = false;
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	//player.addComponent<Gravity>(); 
	
	player.addGroup(groupPlayers);

	//Create test enemy
	enemy.addComponent<TransformComponent>(800.0f, 700.0f, 64, 64, 2, false); 
	enemy.addComponent<SpriteComponent>("mermaid", true); 
	enemy.addComponent<ColliderComponent>("enemy"); 
	enemy.getComponent<SpriteComponent>().addAnimation("Idle", 0, 8, 100); 
	enemy.getComponent<SpriteComponent>().Play("Idle"); 
	enemy.addGroup(groupPlayers); 

	jellyfish.addComponent<TransformComponent>(600.0f, 500.0f, 64, 64, 2, false); 
	jellyfish.addComponent<ColliderComponent>("jellyfish"); 
	jellyfish.addComponent<SpriteComponent>("jellyfish", true); 
	
	SpriteComponent& JFishSpriteComponent = jellyfish.getComponent<SpriteComponent>(); 
	JFishSpriteComponent.addAnimation("Idle", 0, 7, 100); 
	JFishSpriteComponent.Play("Idle"); 
	jellyfish.addGroup(groupPlayers); 


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
	//SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	//where player is before he moves in update
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	TransformComponent& playerTransform = player.getComponent<TransformComponent>(); 

	//float lastFramePlayerPos = playerTransform.position.x; 
	//float lastFramePlayerY = playerTransform.position.y; 
	//std::cout << player.getComponent<TransformComponent>().velocity.y << std::endl;
	//player.getComponent<Gravity>().wantGravity ? std::cout << "true" << std::endl : std::cout << "false" << std::endl; 

	manager.refresh();
	manager.update();

	/*
	float currentFramePlayerPos = playerTransform.position.x; 
	float currentFramePlayerY = playerTransform.position.y; 

	bool collision = false; 
	
	float directionX = currentFramePlayerPos - lastFramePlayerPos; 
	float directionY = currentFramePlayerY - lastFramePlayerY;
	*/
	
	bool collision = false;

	ColliderComponent& playerComp = player.getComponent<ColliderComponent>();
	SDL_Rect& playerCol = playerComp.collider;

	float lastPlayerPosX = playerTransform.position.x;
	playerTransform.updateX(); 
	playerComp.update(); 
	float currentPlayerPosX = playerTransform.position.x; 
	float directionX = currentPlayerPosX - lastPlayerPosX;

	for (auto& c : colliders) {
		ColliderComponent cComp = c->getComponent<ColliderComponent>();
		SDL_Rect cCol = cComp.collider;

		if (Collision::AABB(cCol, playerCol)) {
			collision = true;

			std::cout << "X Components: " << std::endl;
			//std::cout << cComp;
			if (directionX < 0) {
				playerTransform.position.x = cCol.x + cCol.w;
				std::cout << "Player Pos X: " << playerTransform.position.x << std::endl;
				playerComp.update();
				std::cout << "Player Collider Pos X: " << playerCol.x << std::endl;
			}

			if (directionX > 0) {
				playerTransform.position.x = cCol.x - playerCol.w;
				std::cout << "Player Pos X: " << playerTransform.position.x << std::endl;
				playerComp.update();
			}
		}
	}

	float lastPlayerPosY = playerTransform.position.y;
	playerTransform.updateY();
	
	float currentPlayerPosY = playerTransform.position.y;
	float directionY = currentPlayerPosY - lastPlayerPosY;

	playerComp.update(); 

	for (auto& c : colliders) {
		ColliderComponent cComp = c->getComponent<ColliderComponent>(); 
		SDL_Rect cCol = cComp.collider;

	
		if (Collision::AABB(cCol, playerCol)) {
			collision = true; 
			std::cout << "Y Components: " << std::endl; 
			//std::cout << cComp; 
			if (playerTransform.gravity)
				playerTransform.velocity.y = 0; 

			if (directionY < 0) {
				playerTransform.position.y = cCol.y + cCol.h;
				std::cout << "Player Pos Y: " << playerTransform.position.y << std::endl; 
				playerComp.update();
				std::cout << "Player Collider Pos Y: " << playerCol.y << std::endl;
			}

			if (directionY > 0) {
				playerTransform.position.y = cCol.y - playerCol.h;
				playerComp.update(); 
			}
		}
	}


	if (collision)
		std::cout << "--------------------------------" << std::endl; 

	//std::cout << "(" << playerTransform.position.x << ", " << playerTransform.position.y << ")" << std::endl;
	//std::cout << collision << std::endl; 


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
		p->getComponent<ColliderComponent>().draw(); 
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
