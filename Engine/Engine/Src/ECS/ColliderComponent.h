#pragma once
#include <string>
#include "SDL.h"
//#include "Components.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "../TextureManager.h"

enum TILE_TYPE {
	TT_WATER,
	TT_TERRAIN,
	TT_PLAYER,
	TT_JFISH,
	TT_ENEMY,
	TT_PROJECTILE,
	TT_LADDER,
	TT_WATER_SURFACE,
	TT_ONE_WAY
};

class ColliderComponent : public Component {

public:
	SDL_Rect collider;
	TILE_TYPE tag;

	SDL_Texture *tex;
	SDL_Rect srcR, destR;
  
	TransformComponent *transform;
  
	ColliderComponent(TILE_TYPE t);
	ColliderComponent(TILE_TYPE t, int xPos, int yPos, int size);

	friend std::ostream& operator<< (std::ostream& out, const ColliderComponent cc) {
		out << "Collider Position (" << cc.collider.x << ", " << cc.collider.y << ")" << std::endl;
		return out;
	}

	void init() override;

	void update() override;
	void draw() override;

};