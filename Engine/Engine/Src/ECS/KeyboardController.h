#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	TransformComponent *transform;

	//keep transform as it is for the entity at the current time
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			//virtual code for the key
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				//negative addition is up
				transform->velocity.y = -1;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
			default: 
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			//reset back to 0 once done pressing
			case SDLK_w:
				//negative addition is up
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
			default:
				break;
			}
		}
	}
	
};