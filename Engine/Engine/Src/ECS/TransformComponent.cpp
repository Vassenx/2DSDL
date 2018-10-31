#include "TransformComponent.h"
#include "ECS.h"

TransformComponent::TransformComponent() {
	position.Zero();
	velocity.Zero();
}

TransformComponent::TransformComponent(int sc) {
	//position.Zero();
	//middle of screen
	position.x = 400;
	position.y = 320;
	scale = sc;
}

TransformComponent::TransformComponent(float x, float y) {
	position.x = x;
	position.y = y;
}

TransformComponent::TransformComponent(float x, float y, int h, int w, int sc) {
	position.x = x;
	position.y = y;
	height = h;
	width = w;
	scale = sc;
}

TransformComponent::TransformComponent(float x, float y, int h, int w, int sc, bool grav) {
	position.x = x;
	position.y = y;
	height = h;
	width = w;
	scale = sc;
	gravity = grav;
}

//like Unity's onAwake
void TransformComponent::init() {
	velocity.Zero();
}