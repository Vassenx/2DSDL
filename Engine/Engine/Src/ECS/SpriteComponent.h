#pragma once
#include "Components.h"
#include "SDL.h" //for textures

class SpriteComponent : public Component {
private: 
	//where to draw on screen
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:
	
	SpriteComponent() = default;
	//path to texture to use
	SpriteComponent(const char* path) {
		setTex(path);
	}
	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;

		//as previously scaled our texture by two
		destRect.w = destRect.h = 64;
	}

	void update() override {
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}
};