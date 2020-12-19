#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include <string>

class ColliderComponent : public Component {

private:
    SDL_Rect collision;
    std::string tag;
    int xOverHead;
    int yOverHead;
    int width;
    int height;
    TransformComponent * trans;

public:

    ColliderComponent(int xoh,int yoh,int widthg,int heightg,std::string tagg) {
        xOverHead=xoh;
        yOverHead=yoh;
        width=widthg;
        height=heightg;
        tag=tagg;
    }

    SDL_Rect getRect() {
        return collision;
    }

    Vector2D getOverhead() {
        return Vector2D(xOverHead,yOverHead);
    }

    void setXY(Vector2D xy) {
        collision.x=xy.x;
        collision.y=xy.y;
    }

    ColliderComponent copy() {
        ColliderComponent c = ColliderComponent(xOverHead,yOverHead,width,height,tag);
        return c;
    }

    void init () override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        trans=&(entity->getComponent<TransformComponent>());
        collision={static_cast<int> (trans->position.x) + xOverHead,static_cast<int> (trans->position.y) + yOverHead,width,height};
    }

    void update() override {
        collision.x=static_cast<int> (trans->position.x) + xOverHead;
        collision.y=static_cast<int> (trans->position.y) + yOverHead;
    }

};
