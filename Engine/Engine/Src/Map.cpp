#include "Map.h"
#include "Game.h" //to get map file
#include <fstream>

Map::Map() {


}
Map::~Map() {

}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	//move through each tile
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			//convert char to int, but takes a reference of tile
			Game::AddTile(atoi(&tile),x * 32, y * 32);
			//ignores commas
			mapFile.ignore();
		}
	}

	mapFile.close();
}
