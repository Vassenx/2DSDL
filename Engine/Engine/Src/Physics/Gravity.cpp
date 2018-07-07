#include "Gravity.h"

void Gravity::update()  {
	//for multiple forces later on, Euler method
	//accl = force / mass;
	//transform->velocity += (accl * time_step);
	//transform->position += (transform->velocity * time_step);
	//SDL_Rect *playerCol = &entity->getComponent<ColliderComponent>().collider;
	//playerCol->h += 1;

	if (wantGravity) {
		transform->velocity.y += gravity;
		//capping the velocity 
		transform->velocity.y = fminf(transform->velocity.y, maxSpeed);
	}
}

void Gravity::init()  {
	transform = &entity->getComponent<TransformComponent>();
}

