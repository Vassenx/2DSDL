#pragma once
#include "../ECS/Components.h"
#include "../Vector2D.h"
#include "../ECS/ECS.h"

//F = ma
class Gravity : public Component {
public:
	void update() override {
		
		accl = force / mass;
		transform->velocity += (accl * time_step);
		transform->position += (transform->velocity * time_step);
	}
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}

private:
	Vector2D force = Vector2D(0, 1);
	float time_step = 1;
	Vector2D mass = Vector2D(1, 1);
	Vector2D accl;
	TransformComponent *transform;
};