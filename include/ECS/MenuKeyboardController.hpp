#pragma once 

#include "../GameData.hpp"
#include "../GameEngine.hpp"
#include "ECS.hpp"
#include "MenuPositionComponent.hpp"

class MenuKeyboardController : public Component {
public:
    MenuPositionComponent * transform;

    void init() override {
        transform=&entity->getComponent<MenuPositionComponent>();
    }

    void update() override {

        if (GameData::KEYS[SDLK_UP]) transform->velocity.y=-1;
        if (GameData::KEYS[SDLK_DOWN]) transform->velocity.y=1;
        if (!GameData::KEYS[SDLK_DOWN] && !GameData::KEYS[SDLK_UP]) transform->velocity.y=0;
        if (GameData::KEYS[SDLK_RETURN]) {
            switch ((int)transform->position.y)
            {
            case 0:
                GameEngine::change=2;
                break;
            case 1:
                GameEngine::change=3;
                break;
            case 2:
                GameEngine::change=4;
                break;
            case 3:
                GameEngine::change=0;
                break;
            default:
                break;
            }
            entity->destroy();
        }
    }
};