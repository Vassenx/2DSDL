#include "TileComponent.h"
#include "../AssetManager.h"
#include "../TextureManager.h"

TileComponent::~TileComponent() {
	SDL_DestroyTexture(texture);
}
TileComponent::TileComponent(int srcX, int srcY, int xPos, int yPos, int tSize, int tScale, std::string id) {
	texture = Game::assets->GetTexture(id);

	position.x = (float)(xPos);
	position.y = (float)(yPos);

	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = srcRect.h = tSize;
	destRect.x = xPos;
	destRect.y = yPos;
	//map class scale needs to me changed if changed here as well
	destRect.w = destRect.h = tSize * tScale;

	/*
	tileID = id;

	switch (tileID) {

	case 0:
	path = "Assets/dirt.png";
	break;
	case 1:
	path = "Assets/grass.png";
	break;
	case 2:
	path = "Assets/water.png";
	break;
	default:
	break;
	}*/
}
void TileComponent::update() {
	destRect.x = static_cast<int>(position.x - Game::camera.x);
	destRect.y = static_cast<int>(position.y - Game::camera.y);
}
void TileComponent::draw() {
	TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
}