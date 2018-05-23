#pragma once
#include "TransformComponent.h"
#include "ECS.h"
#include "SDL.h" //for SDL_Rect

class TileComponent : public Component {
public:
	SDL_Texture * texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcX, int srcY, int xPos, int yPos, int tSize, int tScale, const char* path) {
		
		texture = TextureManager::LoadTexture(path);
		position.x = xPos;
		position.y = yPos;

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
	void update() override {
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};