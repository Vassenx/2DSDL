#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(std::string t) {
	tag = t;
}

ColliderComponent::ColliderComponent(std::string t, int xPos, int yPos, int size) {
	tag = t;
	collider.x = xPos;
	collider.y = yPos;
	collider.h = collider.w = size;
}

void ColliderComponent::init() {
	//error checking
	if (!entity->hasComponent<TransformComponent>()) {
		entity->addComponent<TransformComponent>();
	}
	transform = &entity->getComponent<TransformComponent>();

	tex = TextureManager::LoadTexture("Assets/ColTex.png");
	srcR = { 0,0,32,32 };
	destR = { collider.x, collider.y, collider.w, collider.h };
}

void ColliderComponent::update() {
	if (tag != "terrain") {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}
	//make sure the collider keeps updating to correct spot on screen
	destR.x = collider.x - Game::camera.x;
	destR.y = collider.y - Game::camera.y;
}

void ColliderComponent::draw() {
	TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
}