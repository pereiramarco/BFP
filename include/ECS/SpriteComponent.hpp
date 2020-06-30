#pragma once

#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"

class SpriteComponent : public Component
{
private:
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:

	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		setTexture(path);
		
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* path)
	{
		texture = TextureManager::loadTexture(path);
	}

	void init() override {
		transform=&entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
		srcRect.w = 32;
		srcRect.h = 32;
		destRect.w = 32;
		destRect.h = 32;
	}

	void update() override
	{
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect);
	}

};