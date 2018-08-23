#pragma once
#include "Components.h"
#include "SDL.h" //for texture functions
#include "../TextureManager.h" 
#include "Animation.h"
#include <map>
#include "../AssetManager.h"

class TransformComponent;

class SpriteComponent : public Component {

public:
	int animIndex = 0;

	//name and struct of animation
	std::map<const char*, Animation> animations;

	//flips picture for animation walking opposite way
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	//path to texture to use
	SpriteComponent(std::string id) {
		setTex(id);
	}
	SpriteComponent(std::string id, bool isAnimated) {
		animated = isAnimated;

		/*
		//index is x or row of large animation picture
		Animation idle = Animation(0, 4, 100);
		Animation walk = Animation(1, 8, 100);
		
		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		*/

		//Play("Idle");
		setTex(id);
	}

	~SpriteComponent() {
	}

	void addAnimation(const char* anim_id, int index, int frames, int delay)
	{
		Animation anim = Animation(index, frames, delay);
		animations.emplace(anim_id, anim); 
	}

	void setTex(std::string id) {
		texture = Game::assets->GetTexture(id);
	}

	void init() override;
	void update() override;
	void draw() override;

	void Play(const char* animName);

private:
	//where to draw on screen
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	//delay between frames in millisecs
	int speed = 100;

};