#pragma once

#include "../Vector2D.h"
#include "../ECS/Components.h"

//F = ma
class Gravity : public Component {
public:
	void update() override {
		//for multiple forces later on, Euler method
		//accl = force / mass;
		//transform->velocity += (accl * time_step);
		//transform->position += (transform->velocity * time_step);

		if (wantGravity) {
			transform->velocity.y += gravity;
            //capping the velocity 
			transform->velocity.y = fminf(transform->velocity.y, maxSpeed);
		}
	}
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}
	bool wantGravity = true;

private:
	/*Vector2D force = Vector2D(0, 1);
	Vector2D mass = Vector2D(1, 1);
	Vector2D accl;
	float time_step = 1;*/

	float maxSpeed = 10.0f;
	float gravity = 0.8f;
	TransformComponent *transform;
};