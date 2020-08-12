#pragma once

#include "../TextureManager.hpp"
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

    TileComponent(float x,float y,int sH,int sW,int dH,int dW,bool mundo, int tileID,std::pair<char,int> type) {
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
        if (mundo) {
            path="world-tiles";
            src.x=tileID*16;
        }
        else {
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
                case 'f':
                    path="dungeon-tiles";
                    break;
                default:
                    break;
            }
            src.x=32*type.second;
        }
    }

    void init() {
        pos=&entity->addComponent<TransformComponent>();
        sprite=&entity->addComponent<SpriteComponent>(path);
        pos->position.x=dest.x;
        pos->position.y=dest.y;
        sprite->setSrc(src);
        sprite->setDest(dest);
        if (world) sprite->setUpdt(false);
    }

    void update() override {
        if (Game::stat!=2 && Game::stat!=3) {
            sprite->setDraw(false);
        }
        else {
            sprite->setDraw((Game::stat==2) == world);
            if (!world) {
                dest.x=position.x-Game::camera.x;
                dest.y=position.y-Game::camera.y;
            }
        }
    }
};