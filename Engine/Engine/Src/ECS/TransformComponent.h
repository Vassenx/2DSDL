#pragma once
#include "Components.h"
#include "../Vector2D.h"
#include "../Game.h"

class TransformComponent : public Component {

public:
	Vector2D position;
	Vector2D velocity;
	
	int height = 32;
	int width = 32;
	int scale = 1;
	int speed = 3;

	TransformComponent();
	TransformComponent(int sc);
	TransformComponent(float x, float y);

	TransformComponent(float x, float y, int h, int w, int sc);

	void update() override;
	void init() override;
};