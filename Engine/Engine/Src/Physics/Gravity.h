#pragma once

#include "../ECS/ECS.h"
#include "../ECS/ColliderComponent.h"
#include "../ECS/TransformComponent.h"
#include "../ECS/SpriteComponent.h"

class Gravity : public Component {
private:
	/*Vector2D force = Vector2D(0, 1);
	Vector2D mass = Vector2D(1, 1);
	Vector2D accl;
	float time_step = 1;*/

	float maxSpeed = 10.0f;
	float gravity = 0.8f;
	TransformComponent *transform;
	ColliderComponent *cp;

public:
	Gravity() 
	{
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		cp = &entity->getComponent<ColliderComponent>();
		SpriteComponent* sprite = &entity->getComponent<SpriteComponent>(); 
		SDL_Rect rect = cp->collider; 
		int ind = sprite->animIndex; 
		int t_height = transform->height; 
	}

	void update() override {
		//for multiple forces later on, Euler method
		//accl = force / mass;
		//transform->velocity += (accl * time_step);
		//transform->position += (transform->velocity * time_step);
		
		std::cout << cp->tag;
		if (wantGravity) {
			//std::cout << cp->tag; 
			transform->velocity.y += gravity;
            //capping the velocity 
			transform->velocity.y = fminf(transform->velocity.y, maxSpeed);
			std::cout << "Gravity" << std::endl; 

			//SDL_Rect playerCol = collider->collider;
			
			//for (auto& c : colliders) {
				//SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
				/*
				if (Collision::AABB(cCol, playerCol)) {
					std::cout << "Y-Hit" << std::endl;
				}*/
			//}
		}
		else {
			transform->velocity.y = 0; 
			std::cout << "No Gravity" << std::endl;
		}
	}
  
	bool wantGravity = true;
	void init() override;


};