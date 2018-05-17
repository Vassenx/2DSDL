#pragma once
#include "SDL.h"

class Collision {
public:

	//Access allign bounding box
	static bool AABB(const SDL_Rect &recA, const SDL_Rect &recB);

};