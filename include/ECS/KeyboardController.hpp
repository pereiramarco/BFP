#pragma once 

#include "../GameData.hpp"
#include "../GameEngine.hpp"
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "AttributesComponent.hpp"
#include "SpriteComponent.hpp"

class KeyboardController : public Component {
public:
    TransformComponent * transform;
    AttributesComponent * att;
    SpriteComponent * sprite;

    bool interact;

    void init() override {
        transform=&entity->getComponent<TransformComponent>();
        att=&entity->getComponent<AttributesComponent>();
        sprite=&entity->getComponent<SpriteComponent>();
        interact=false;
    }

    void update() override {
        int shift=1+GameData::KEYS[SDLK_LSHIFT];
        if (GameData::KEYS[SDLK_UP] && !GameData::KEYS[SDLK_DOWN]) {
            transform->velocity.y=-1*shift;
            sprite->timesSpeed(shift);
        }
        else 
            if (GameData::KEYS[SDLK_DOWN] && !GameData::KEYS[SDLK_UP]) {
                transform->velocity.y=1*shift;
                sprite->timesSpeed(shift);
            }
            else {
                transform->velocity.y=0;
            }
        if (GameData::KEYS[SDLK_LEFT] && !GameData::KEYS[SDLK_RIGHT]) {
            transform->velocity.x=-1*shift;
            sprite->timesSpeed(shift);
        }
        else 
            if (GameData::KEYS[SDLK_RIGHT] && !GameData::KEYS[SDLK_LEFT]) {
                transform->velocity.x=1*shift;
                sprite->timesSpeed(shift);
            }
            else {
                transform->velocity.x=0;
            }
        transform->updateSentido();
        if (shift-1 && !transform->isVel0()) { //player is running
            att->addToAttribute(3,att->getAttribute(9));
        }
        if (GameData::KEYS[SDLK_ESCAPE]) {
            GameEngine::change=1;
            entity->destroy();
        }
        if (GameData::KEYS[SDLK_e]) 
            interact=true;
        if (GameData::KEYS[SDLK_y])
            att->addToAttribute(1,2);
        if (GameData::KEYS[SDLK_t])
            att->addToAttribute(1,-2);
        if (GameData::KEYS[SDLK_h])
            att->addToAttribute(5,2);
        if (GameData::KEYS[SDLK_g])
            att->addToAttribute(5,-2);
        if (GameData::KEYS[SDLK_n])
            att->addToAttribute(3,2);
        if (GameData::KEYS[SDLK_b])
            att->addToAttribute(3,-2);
        if (GameData::KEYS[SDLK_x])
            att->addToAttribute(7,10);
    }
};