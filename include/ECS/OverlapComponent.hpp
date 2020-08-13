#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include <string>

class OverlapComponent : public Component {

private:
    SDL_Rect overlap;
    std::string tag;
    int width;
    int height;
    TransformComponent * trans;

public:

    OverlapComponent(int widthg,int heightg) {
        width=widthg;
        height=heightg;
    }

    SDL_Rect getRect() {
        return overlap;
    }

    void init () override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        trans=&(entity->getComponent<TransformComponent>());
        overlap={static_cast<int> (trans->position.x),static_cast<int> (trans->position.y),width,height};
    }

    void update() override {
        overlap.x=static_cast<int> (trans->position.x);
        overlap.y=static_cast<int> (trans->position.y);
    }

};
