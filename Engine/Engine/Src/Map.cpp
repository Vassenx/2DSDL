#include "Map.h"
#include "Game.h" //to get map file
#include <fstream>

Map::Map() {


}
Map::~Map() {

}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	//move through each tile
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			//character is position of tile as integers starting at 0
			mapFile.get(c);
			srcY = atoi(&c) * 32;

			mapFile.get(c);
			srcX = atoi(&c) * 32;

			//doubling size of tiles 
			Game::AddTile(srcX, srcY, x * 64, y * 64);
			//ignores commas
			mapFile.ignore();
		}
	}

	mapFile.close();
}
