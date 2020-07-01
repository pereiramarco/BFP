#pragma once

#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "SDL2/SDL.h"

class TileComponent : public Component {
    public:
    TransformComponent * pos;
    SpriteComponent * sprite;

    TileComponent() = default;

    TileComponent(int x,int y, const char* path) {
        if (!entity->hasComponent<TransformComponent>()) {
            &entity->addComponent<TransformComponent>();
        }
        pos=&entity->getComponent<TransformComponent>();
        pos->position.x=x;
        pos->position.y=y;
        if (!entity->hasComponent<SpriteComponent>()) {
            &entity->addComponent<SpriteComponent>();
        }
        sprite=&entity->getComponent<SpriteComponent>();
        sprite->setTexture(path);
    }

    void draw() override {
        sprite->draw();
    }
};