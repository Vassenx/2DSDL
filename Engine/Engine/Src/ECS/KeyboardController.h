#pragma once

#include "../Game.h"
#include "Components.h"

class Gravity;
class SpriteComponent;

class KeyboardController : public Component {

public:
	TransformComponent *transform;
	SpriteComponent *sprite;
	Gravity *grav;
	ColliderComponent *col;

	//keep transform as it is for the entity at the current time
	void init() override;
	void update() override;
};
