#pragma once

#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include "../Game.hpp"

class SpriteComponent : public Component
{
private:
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;
	bool drawb;

public:

	SpriteComponent() = default;

	SpriteComponent(std::string text) {
		this->texture=Game::textures->getTexture(text);
		drawb=true;
	}

	void setSrc(SDL_Rect r) {
		srcRect=r;
	}

	void setDest(SDL_Rect r) {
		destRect=r;
	}

	void setSrc(int t,int x,int y) {
		switch (t) {
			case 0:
				srcRect.x=x;
			break;
			case 1:
				srcRect.y=y;
			break;
			case 2:
				srcRect.x=x;
				srcRect.y=y;
			break;
		}
	}

	void setDraw(bool t) {
		drawb=t;
	}

	void init() override {
		transform=&entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
		srcRect.w = 32;
		srcRect.h = 32;
		destRect.w = 64;
		destRect.h = 64;
		drawb=true;
	}

	void update() override
	{
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override
	{
		if (drawb)
			TextureManager::draw(texture, srcRect, destRect);
	}

};