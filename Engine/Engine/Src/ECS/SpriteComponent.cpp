#include "SpriteComponent.h"
#include "TransformComponent.h"
  
SpriteComponent::SpriteComponent(std::string id) {
    setTex(id);
}
SpriteComponent::SpriteComponent(std::string id, bool isAnimated) {
	animated = isAnimated;

	setTex(id);
}
void SpriteComponent::setTex(std::string id) {
	texture = Game::assets->GetTexture(id);
}

void SpriteComponent::init() {
	transform = &entity->getComponent<TransformComponent>();

	srcRect.x = srcRect.y = 0;
	srcRect.w = transform->width;
	srcRect.h = transform->height;

	//as previously scaled our texture by two
	destRect.w = destRect.h = 64;
}

void SpriteComponent::update() {

	if (animated) {
		//remainder of frames left * width (which is 32)
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
	}

	//moves across large image by 32 at a time
	srcRect.y = animIndex * transform->height;

	destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
	destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
	destRect.w = transform->width * transform->scale;
	destRect.h = transform->height * transform->scale;
}

void SpriteComponent::draw() {
	TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
}

void SpriteComponent::Play(const char* animName) {
	//change the current animation
	frames = animations[animName].frames;
	animIndex = animations[animName].index;
	speed = animations[animName].speed;
}
