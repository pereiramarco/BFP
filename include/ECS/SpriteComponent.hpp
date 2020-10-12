#pragma once

#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include "../Game.hpp"
#include "../ConstantValues.hpp"
#include "Animation.hpp"

class SpriteComponent : public Component
{
private:
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;
	bool drawb=true;
	int skip=1;
	bool updating=true;
	bool animated=false;
	float widthPercentage;
	float heightPercentage;
	int xoverhead=0;
	int yoverhead=0;
	int frames=3;
	int speed=100;
	int index=0;
	std::map<const char*,Animation> animations;

public:

	SpriteComponent() = default;

	SpriteComponent(std::string text,bool upg,SDL_Rect r1,SDL_Rect r2) {
		this->texture=Game::textures->getTexture(text);
		updating=upg;
		srcRect=r1;
		destRect=r2;
	}

	SpriteComponent(std::string text) {
		this->texture=Game::textures->getTexture(text);
		srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
		srcRect.w = 32;
		srcRect.h = 32;
		destRect.w = ConstantValues::localTileW;
		destRect.h = ConstantValues::localTileH;
	}

	SpriteComponent(std::string text,bool anim) {
		this->texture=Game::textures->getTexture(text);
		animated=anim;
		srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
		srcRect.w = 32;
		srcRect.h = 32;
		destRect.w = ConstantValues::localTileW;
		destRect.h = ConstantValues::localTileH;
	}

	void addAnimation(const char * id,int index,int frames,int speed) {
		animations[id]=Animation(index,frames,speed);
	}

	void addStandardAnimations() {
		addAnimation("idle-down",0,3,200);
		addAnimation("idle-left",1,3,200);
		addAnimation("idle-right",2,3,200);
		addAnimation("idle-up",3,3,200);
		addAnimation("down",4,3,200);
		addAnimation("left",5,3,200);
		addAnimation("right",6,3,200);
		addAnimation("up",7,3,200);
	}

	void setUpdate(bool up) {
		updating = up;
	}

	void setSrc(SDL_Rect r) {
		srcRect=r;
	}

	void setTexture(std::string text) {
		this->texture=Game::textures->getTexture(text);
	}

	void setWidthPercentage(float p) {
		widthPercentage=p;
	}

	void setHeightPercentage(float p) {
		heightPercentage=p;
	}

	void setXOverhead(int t) {
		xoverhead=t;
	}

	void setYOverhead(int t) {
		yoverhead=t;
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

	void setSkip(int x) {
		skip=x;
	}

	int getDestx() {
		return destRect.x;
	}

	int getDesty() {
		return destRect.y;
	}

	void init() override {
		transform=&entity->getComponent<TransformComponent>();
		widthPercentage=1;
		heightPercentage=1;
	}

	void update() override
	{
		if (updating) {
			if (animated) {
				srcRect.x= srcRect.w * static_cast<int>((SDL_GetTicks()/speed)%frames);
				srcRect.y=index*srcRect.h;
			}
			destRect.x = skip*static_cast<int> (transform->position.x - Game::camera.x);
			destRect.y = skip*static_cast<int> (transform->position.y - Game::camera.y);
		}
	}

	void draw() override
	{
		if (drawb) {
			int sW=srcRect.w;
			int sH=srcRect.h;
			int dW=destRect.w;
			int dH=destRect.h;
			int ratiox=dW/sW;
			int ratioy=dH/sH;
			if (widthPercentage<1) {
				srcRect.w *= widthPercentage;
				destRect.w = srcRect.w*ratiox;
			}
			if (heightPercentage<1) {
				srcRect.h *= heightPercentage;
				destRect.h =srcRect.h*ratioy;
			}
			if (xoverhead) {
				srcRect.x+=xoverhead;
				srcRect.w-=xoverhead;
				destRect.x+=xoverhead*ratiox;
				destRect.w-=xoverhead*ratiox;
			}
			if (yoverhead) {
				srcRect.y+=yoverhead;
				srcRect.h-=yoverhead;
				destRect.y+=yoverhead*ratioy;
				destRect.h-=yoverhead*ratioy;
			}
			TextureManager::draw(texture, srcRect, destRect);
			if (xoverhead) {
				srcRect.x-=xoverhead;
				srcRect.w+=xoverhead;
				destRect.x-=xoverhead*ratiox;
				destRect.w+=xoverhead*ratiox;
				xoverhead=0;
			}
			if (yoverhead) {
				srcRect.y-=yoverhead;
				srcRect.h+=yoverhead;
				destRect.y-=yoverhead*ratioy;
				destRect.h+=yoverhead*ratioy;
				yoverhead=0;
			}
			srcRect.w=sW;
			destRect.w=dW;
			srcRect.h=sH;
			destRect.h=dH;
			widthPercentage=1;
			heightPercentage=1;
		}
	}

	void play(const char* animName) {
		if (animated) {
			frames=animations[animName].frames;
			speed=animations[animName].speed;
			index=animations[animName].index;
		}
	}

	void timesSpeed(int r) {
		speed/=r;
	}

};