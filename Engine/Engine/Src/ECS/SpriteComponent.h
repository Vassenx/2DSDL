#pragma once
#include "Components.h"
#include "SDL.h" //for texture functions
#include "../TextureManager.h" 

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

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

		//as previously scaled our texture by two
		destRect.w = destRect.h = 64;
	}

	void update() override {
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}
};