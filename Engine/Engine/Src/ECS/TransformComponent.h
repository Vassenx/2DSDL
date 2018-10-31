#pragma once
#include "ECS.h"
#include "../Vector2D.h"
#include "../Game.h"

class TransformComponent : public Component {

public:
	Vector2D position;
	Vector2D velocity;
	
	int height = 32;
	int width = 32;
	int scale = 1;
  
	bool gravity = false; 
	bool inWater = false;
	bool onWaterSurface = false;
	bool onLadder = false;
	bool onOneWay = false;


	TransformComponent();

	TransformComponent(int sc);
	TransformComponent(float x, float y);
	TransformComponent(float x, float y, int h, int w, int sc);
	TransformComponent(float x, float y, int h, int w, int sc, bool grav);

	void update() override {
		if (gravity)
			velocity.y += 1.5f; 
		if (inWater)
			velocity.y = 1.5f;
	}

	void updateX() {
		position.x += velocity.x;
	}

	void updateY() {
		position.y += velocity.y; 
	}
	void init() override;
};