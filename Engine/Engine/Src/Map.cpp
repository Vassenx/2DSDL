#include "Map.h"
#include "Game.h" //to get map file
#include <fstream>
#include "ECS\ECS.h"
#include "ECS\TileComponent.h"
#include "ECS\ColliderComponent.h"
#include <string>

//defined in Game.cpp
extern Manager manager;

Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts) {
	scaledSize = ms * ts;
}

Map::~Map() {
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	//int mapSizeY = sizeY;
	//int mapSizeX = sizeX;

	int srcX, srcY;

	//move through each tile
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			//character is position of tile as integers starting at 0
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;

			mapFile.get(c);
			
			srcX = atoi(&c) * tileSize;
			
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			//ignores commas
			mapFile.ignore();
		}
	}
	//ignore line between map layer and collision layer
	mapFile.ignore();

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			if (c == '1') {
				//create a new collider entity/component
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore(); 
		}
	}
	mapFile.close();
}
void Map::AddTile(int srcX, int srcY, int xPos, int yPos) {
	auto& tile(manager.addEntity());
	//id = type of tile to create
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, tileSize, mapScale, texID);
	tile.addGroup(Game::groupMap);
}
