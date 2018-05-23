#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {

public:

	Vector2D position;
	Vector2D velocity;
	
	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent() {
		position.Zero();
	}
	TransformComponent(int sc) {
		//position.Zero();
		//middle of screen
		position.x = 400;
		position.y = 320; 
		scale = sc;
	}
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	//like Unity's onAwake
	void init() override {
		velocity.Zero();
	}
};