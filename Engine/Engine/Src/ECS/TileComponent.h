#pragma once
#include "ECS.h"
#include "../Vector2D.h"
#include "../Game.h"
#include "../TextureManager.h"
#include "../AssetManager.h"

class TileComponent : public Component {

public:
	SDL_Texture * texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent();

	TileComponent(int srcX, int srcY, int xPos, int yPos, int tSize, int tScale, std::string id);

	void update() override;
	void draw() override;
};