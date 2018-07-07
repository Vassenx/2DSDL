#include "KeyboardController.h"

	//keep transform as it is for the entity at the current time
	void KeyboardController::init()  {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		grav = &entity->getComponent<Gravity>();
		col = &entity->getComponent<ColliderComponent>();
	}

	void KeyboardController::update()  {
		if (Game::event.type == SDL_KEYDOWN) {
			//virtual code for the key
			switch (Game::event.key.keysym.sym) {

			case SDLK_w:
				//change speeds depending on swimming or walking
				//negative addition is up as 0,0 is top left corner
				if (grav->wantGravity == false) {
					transform->velocity.y = -1;
					sprite->Play("Walk");
					col->tag = "to";
					std::cout << col->collider.h;
				}
				break;

			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("Walk");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("Walk");
				break;
				//case SDLK_SPACE:   for swimming?

			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
				//reset back to 0 once done pressing
			case SDLK_w:
				if (transform->velocity.y < 0) {
					//negative addition is up
					transform->velocity.y = 0;
				}
				sprite->Play("Idle");
				break;
			case SDLK_a:
				if (transform->velocity.x < 0) {
					transform->velocity.x = 0;
				}
				sprite->Play("Idle");
				//resets horizontal flipping so walking isn't moonwalking
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				if (transform->velocity.x > 0) {
					transform->velocity.x = 0;
				}
				sprite->Play("Idle");
				break;
			case SDLK_s:
				if (transform->velocity.y > 0) {
					transform->velocity.y = 0;
				}
				sprite->Play("Idle");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}
		}
	}