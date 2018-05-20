#pragma once
#include "Components.h"
#include "SDL.h" //for texture functions
#include "../TextureManager.h" 
#include "Animation.h"
#include <map>

class SpriteComponent : public Component {
private: 
	//where to draw on screen
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	//delay between frames in millisecs
	int speed = 100;

public:
	
	int animIndex = 0;

	//name and struct of animation
	std::map<const char*, Animation> animations;

	//flips picture for animation walking opposite way
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	//path to texture to use
	SpriteComponent(const char* path) {
		setTex(path);
	}
	SpriteComponent(const char * path, bool isAnimated) {
		animated = isAnimated;

		//index is x or row of large animation picture
		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);
		
		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");
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

		if (animated) {
			//remainder of frames left * width (which is 32)
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		//moves across large image by 32 at a time
		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName) {
		//change the current animation
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};