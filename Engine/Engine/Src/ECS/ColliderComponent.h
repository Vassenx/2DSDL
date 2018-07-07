#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {

public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture *tex;
	SDL_Rect srcR, destR;

	//TransformComponent *transform;
	
	ColliderComponent(std::string t);
	ColliderComponent(std::string t, int xPos, int yPos, int size);

	void init() override;

	void update() override;
	void draw() override;

private:
    TransformComponent *transform;
};