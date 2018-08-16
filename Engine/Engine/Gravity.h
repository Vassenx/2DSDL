#pragma once
#include "Vector2D.h"
#include "Collision.h"
#include "Components.h"

//F = ma
class Gravity : public Component {
public:
	Gravity(std::vector<Entity*>& clders) : colliders(clders)
	{
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		playerColliderComponent = &entity->getComponent<ColliderComponent>();
		ColliderComponent cc = *playerColliderComponent;
	}

	void update() override {
		//for multiple forces later on, Euler method
		//accl = force / mass;
		//transform->velocity += (accl * time_step);
		//transform->position += (transform->velocity * time_step);


		if (wantGravity) {
			transform->velocity.y += gravity;
			//capping the velocity 
			transform->velocity.y = fminf(transform->velocity.y, maxSpeed);
			std::cout << "Gravity" << std::endl;

			SDL_Rect playerCol = playerColliderComponent->collider;

			for (auto& c : colliders) {
				SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
				/*
				if (Collision::AABB(cCol, playerCol)) {
				std::cout << "Y-Hit" << std::endl;
				}*/
			}
		}
		else {
			transform->velocity.y = 0;
			std::cout << "No Gravity" << std::endl;
		}
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
	ColliderComponent *playerColliderComponent;

	std::vector<Entity*>& colliders;
};