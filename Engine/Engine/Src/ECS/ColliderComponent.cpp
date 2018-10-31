#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(TILE_TYPE t) {
	tag = t;
}

ColliderComponent::ColliderComponent(TILE_TYPE t, int xPos, int yPos, int size) : tag(t) {
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
	if (tag != TT_TERRAIN && tag != TT_WATER && tag != TT_LADDER && tag != TT_WATER_SURFACE && tag != TT_ONE_WAY) {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;

		destR.x = collider.x;
		destR.y = collider.y;
		destR.w = collider.w;
		destR.h = collider.h;
	}
	//make sure the collider keeps updating to correct spot on screen
	destR.x = collider.x - Game::camera.x;
	destR.y = collider.y - Game::camera.y;
}
void ColliderComponent::draw() {
	if (tag != TT_WATER) {
	    TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
}