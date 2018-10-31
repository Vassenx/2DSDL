#pragma once

#include "ECS.h"
#include "../Game.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <iostream>

class SpriteComponent;

class KeyboardController : public Component {

public:
	TransformComponent *transform;
	SpriteComponent *sprite;

	//keep transform as it is for the entity at the current time
	void init() override;
	void update() override;
};
	
