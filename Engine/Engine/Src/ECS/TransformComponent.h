#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {

public:

	Vector2D position;

	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void update() override {

	}

	/*getters and setters
	int x() { return xPos; }
	void x(int x) { xPos = x; }
	int y() { return yPos; }

	void setPos(int x, int y) {
		xPos = x;
		yPos = y;
	}*/

	//can use the update, draw, etc of Component base class

	//like Unity's onAwake
	/*void init() override {
		xPos = 0;
		yPos = 0;
	}*/

};