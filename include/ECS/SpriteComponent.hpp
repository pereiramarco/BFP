#pragma once

#include "SDL2/SDL.h"
#include "../TextureManager.hpp"

class SpriteComponent : public Component
{
private:
	PositionComponent * pos;
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

	void init() override
	{
		pos=&entity->getComponent<PositionComponent>();
		srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
		srcRect.w = 18;
		srcRect.h = 24;
		destRect.w = 32;
		destRect.h = 32;
	}

	void update() override
	{
		destRect.x = pos->x();
		destRect.y = pos->y();
	}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect);
	}

};