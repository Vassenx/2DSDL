#pragma once
#include <string>
#include "SDL.h"
//#include "Components.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {

public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture *tex;
	SDL_Rect srcR, destR;
  
	TransformComponent *transform;
  
	ColliderComponent(std::string t);
	ColliderComponent(std::string t, int xPos, int yPos, int size);

	void init() override;

	void update() override;
	void draw() override;

	friend std::ostream& operator<< (std::ostream& out, const ColliderComponent cc) {
		out << "Collider Position (" << cc.collider.x << ", " << cc.collider.y << ")" << std::endl; 
		return out; 
	}

	void update() override {
		if (tag != "terrain") {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;

			destR.x = collider.x; 
			destR.y = collider.y; 
			destR.w = collider.w; 
			destR.h = collider.h; 
		}
		//make sure the collider keeps updating to correct spot on screen
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;
	}
	void draw() override {
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};