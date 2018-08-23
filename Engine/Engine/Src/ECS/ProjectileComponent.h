#pragma once
#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component {

public:
	ProjectileComponent(int rge, int sp, Vector2D vel) : range(rge), speed(sp), velocity(vel) {
	}
	~ProjectileComponent() {
	}
	
	void init() override;
	void update() override;
	
private:
	TransformComponent *transform;
	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;
};