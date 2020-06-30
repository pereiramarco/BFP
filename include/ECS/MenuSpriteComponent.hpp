#pragma once

#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "MenuPositionComponent.hpp"

class MenuSpriteComponent : public Component
{
private:
	MenuPositionComponent * transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:

	MenuSpriteComponent() = default;

	MenuSpriteComponent(const char* path)
	{
		setTexture(path);
		
	}

	~MenuSpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* path)
	{
		texture = TextureManager::loadTexture(path);
	}

	void init() override {
		transform=&entity->getComponent<MenuPositionComponent>();
		srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
		srcRect.w = 960;
		srcRect.h = 540;
		destRect.w = 1920;
		destRect.h = 1080;
	}

	void update() override
	{
		srcRect.x = 960*(int)transform->position.y;
	}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect);
	}

};