#pragma once

#include "../TextureManager.hpp"
#include "../GameData.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "SDL2/SDL.h"
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

class TileComponent : public Component {
    public:
    TransformComponent * pos;
    SpriteComponent * sprite;
    Vector2D position;

    bool world;
    std::string path;
    SDL_Rect src,dest;

    TileComponent() = default;

    TileComponent(float x,float y,int sH,int sW,int dH,int dW,int tileID) {
        world=true;
        position.x=y*dH;
        position.y=x*dW;
        dest.y=x*dW;
        dest.x=y*dH;
        dest.w=dW;
        dest.h=dH;
        src.w=sW;
        src.h=sH;
        src.y=0;
        path="world-tiles";
        src.x=tileID*16;
    }

    TileComponent(float x,float y,int sH,int sW,int dH,int dW,bool mundo,int tileID) {
        world=mundo;
        position.x=y*dH;
        position.y=x*dW;
        dest.y=x*dW;
        dest.x=y*dH;
        dest.w=dW;
        dest.h=dH;
        src.w=sW;
        src.h=sH;
        src.y=0;
        path="dungeon-tiles";
        src.x=32 *tileID;
    }

    TileComponent(float x,float y,int sH,int sW,int dH,int dW,std::pair<char,int> type) {
        world=false;
        position.x=y*dH;
        position.y=x*dW;
        dest.y=x*dW;
        dest.x=y*dH;
        dest.w=dW;
        dest.h=dH;
        src.w=sW;
        src.h=sH;
        src.y=0;
        switch (type.first) {
            case 'a':
                path="water-tiles";
                break;
            case 'c':
                path="beach-tiles";
                break;
            case 'b':
                path="plains-tiles";
                break;
            case 'd':
            case 'e':
                path="wall-tiles";
                break;
            default:
                break;
        }
        src.x=32*type.second;
    }

    TileComponent(float x,float y,int sH,int sW,int dH,int dW,std::string pathh,int sprite) {
        world=false;
        position.x=y*dH;
        position.y=x*dW;
        dest.y=x*dW;
        dest.x=y*dH;
        dest.w=dW;
        dest.h=dH;
        src.w=sW;
        src.h=sH;
        src.y=0;
        src.x=32*sprite;
        path=pathh;
    }

    void init() {
        pos=&entity->addComponent<TransformComponent>();
        sprite=&entity->addComponent<SpriteComponent>(path);
        pos->position.x=dest.x;
        pos->position.y=dest.y;
        sprite->setSrc(src);
        sprite->setDest(dest);
    }

    void update() override {
        if (GameData::stat!=2 && GameData::stat!=3) {
            sprite->setDraw(false);
        }
        else {
            sprite->setDraw((GameData::stat==2) == world);
        }
    }
};