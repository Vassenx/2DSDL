#include "ProjectileComponent.h"

void ProjectileComponent::init() {
	transform = &entity->getComponent<TransformComponent>();
	transform->velocity = velocity;
	//std::cout << "Made" << transform->position.x  << transform->position.y << std::endl;
}
void ProjectileComponent::update() {

	distance += speed;

	if (distance > range) {
		//std::cout << "Out of range" << std::endl;
		entity->destroy();
	}
	//out of right side of screen, etc.
	else if (transform->position.x > Game::camera.x + Game::camera.w ||
		transform->position.x < Game::camera.x ||
		transform->position.y > Game::camera.y + Game::camera.h ||
		transform->position.y < Game::camera.y)
	{
		//std::cout << "Out of bounds" << Game::camera.w << Game::camera.h << std::endl;
		entity->destroy();
	}
}