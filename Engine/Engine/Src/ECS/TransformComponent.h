#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {

public:

	Vector2D position;
	Vector2D velocity;
	
	int speed = 3;

	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	//like Unity's onAwake
	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}

	//can use the update, draw, etc of Component base class
	/*getters and setters
	int x() { return xPos; }
	void x(int x) { xPos = x; }
	int y() { return yPos; }

	void setPos(int x, int y) {
		xPos = x;
		yPos = y;
	}*/

};