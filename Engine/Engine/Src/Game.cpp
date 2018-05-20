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

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

//adds a new player to the entities
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

const char *mapFile = "Assets/terrain_ss.png";

enum groupLabels : std::size_t {
	//naming groups. up to 32
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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
    Map::LoadMap("Assets/map.map", 25, 20);

	//If scale of 2, as 32 x 32 -> 64 x 64
	player.addComponent<TransformComponent>(4);
	//true = isAnimated
	player.addComponent<SpriteComponent>("Assets/player_anims.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	/*wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("Assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);*/
}

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

void Game::update()
{
	manager.refresh();
	manager.update();

	Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles) {
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	}

	for (auto cc : colliders) {
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
		//creates a bounce type of thing
		//player.getComponent<TransformComponent>().velocity * -1;
	}
	
	//player.getComponent<SpriteComponent>().setTex("Assets/enemy.png");
/*	player->Update();
	//updates entities and thus updates all the components
	//map->LoadMap();
*/
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//layer ordering
	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	for (auto& e : enemies) {
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()  
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int srcX, int srcY, int xPos, int yPos){
	auto& tile(manager.addEntity());
	//id = type of tile to create
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, mapFile);
	tile.addGroup(groupMap);
}