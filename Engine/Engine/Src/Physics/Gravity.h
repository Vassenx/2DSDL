#pragma once

#include "../Vector2D.h"
#include "../ECS/Components.h"

//F = ma
class Gravity : public Component {

public:
	void update() override;
	bool wantGravity = true;
	void init() override;

private:
	/*Vector2D force = Vector2D(0, 1);
	Vector2D mass = Vector2D(1, 1);
	Vector2D accl;
	float time_step = 1;*/

	float maxSpeed = 10.0f;
	float gravity = 0.8f;
	TransformComponent *transform;
};