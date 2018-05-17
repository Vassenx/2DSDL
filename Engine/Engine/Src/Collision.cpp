#include "Collision.h"

//is static so no object, just one
bool AABB(const SDL_Rect &recA, const SDL_Rect &recB) {
	//A.x + A.w >= B.x and same for ys then collision. (overlap) or opposite
	//A.x is the top left side of the rectangle
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		) 
	{
		return true;
	}
	return false;
}