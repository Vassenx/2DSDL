#pragma once
#include "TransformComponent.h"
#include "ECS.h"
#include "SDL.h" //for SDL_Rect

class TileComponent : public Component {
public:
	SDL_Texture * texture;
	SDL_Rect srcRect, destRect;

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcX, int srcY, int xPos, int yPos, const char* path) {
		
		texture = TextureManager::LoadTexture(path);
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;
		destRect.x = xPos;
		destRect.y = yPos;
		//map class scale needs to me changed if changed here as well
		destRect.w = destRect.h = 64;


		/*tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
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

	/*void init() override {
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();
		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}*/

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};