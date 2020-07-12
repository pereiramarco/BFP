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

    bool world;
    char type;
    int tileID;
    std::string path;
    SDL_Rect src,dest;

    TileComponent() = default;

    TileComponent(int x,int y,int sH,int sW,int dH,int dW,bool mundo, int tileID,std::pair<char,int> type) {
        world=mundo;
        dest.y=x*dW;
        dest.x=y*dH;
        dest.w=dW;
        dest.h=dH;
        src.w=sW;
        src.h=sH;
        src.y=0;
        this->tileID=tileID;
        if (mundo) {
            path="world-tiles";
            src.x=tileID*16;
        }
        else {
            switch (type.first) {
                case 'a':
                    path="water-tiles";
                    break;
                case 'b':
                    path="beach-tiles";
                    break;
                case 'c':
                    path="plains-tiles";
                    break;
                case 'd':
                    path="desert-tiles";
                    break;
                default:
                    break;
            }
            src.x=32*type.second;
        }
    }

    void init() {
        &entity->addComponent<TransformComponent>(dest.x,dest.y);
        &entity->addComponent<SpriteComponent>(path);
        pos=&entity->getComponent<TransformComponent>();
        sprite=&entity->getComponent<SpriteComponent>();
        sprite->setSrc(src);
        sprite->setDest(dest);
    }

    void update() override {
        if (Game::stat!=2 && Game::stat!=3) {
            entity->destroy();
        }
        else sprite->setDraw((Game::stat==2) == world);
    }
};