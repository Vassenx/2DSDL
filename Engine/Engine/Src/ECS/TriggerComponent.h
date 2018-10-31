#pragma once
#include "SDL.h"
#include "TransformComponent.h"
#include <string>

class TriggerComponent : public Component {
public:
	SDL_Rect collider;
	std::string tag;

	TriggerComponent(std::string t) : tag(t) {};
	TriggerComponent(std::string t, int xPos, int yPos, int size);
	void onTrigger(TransformComponent& tComp);

};