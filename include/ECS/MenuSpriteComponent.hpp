#pragma once

#include "SDL2/SDL.h"
#include "../AssetManager.hpp"
#include "../TextureManager.hpp"
#include "MenuPositionComponent.hpp"
#include "../GameData.hpp"
#include "../ConstantValues.hpp"

class MenuSpriteComponent : public Component
{
private:
	MenuPositionComponent * transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:

	MenuSpriteComponent() = default;

	MenuSpriteComponent(std::string path)
	{
		setTexture(path);
		
	}

	void setTexture(std::string path)
	{
		texture = GameData::textures->getTexture(path);
	}

	void init() override {
		transform=&entity->getComponent<MenuPositionComponent>();
		srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
		srcRect.w = 960;
		srcRect.h = 540;
		destRect.w = ConstantValues::screenSizeW;
		destRect.h = ConstantValues::screenSizeH;
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