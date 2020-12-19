#pragma once 

#include "../Game.hpp"
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
        int shift=1+Game::KEYS[SDLK_LSHIFT];
        if (Game::KEYS[SDLK_UP] && !Game::KEYS[SDLK_DOWN]) {
            transform->velocity.y=-1*shift;
            sprite->timesSpeed(shift);
        }
        else 
            if (Game::KEYS[SDLK_DOWN] && !Game::KEYS[SDLK_UP]) {
                transform->velocity.y=1*shift;
                sprite->timesSpeed(shift);
            }
            else {
                transform->velocity.y=0;
            }
        if (Game::KEYS[SDLK_LEFT] && !Game::KEYS[SDLK_RIGHT]) {
            transform->velocity.x=-1*shift;
            sprite->timesSpeed(shift);
        }
        else 
            if (Game::KEYS[SDLK_RIGHT] && !Game::KEYS[SDLK_LEFT]) {
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
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_e:
                interact=true;
                break;
            case SDLK_ESCAPE:
                Game::stat=1;
                entity->destroy();
                break;
            case SDLK_y:
                att->addToAttribute(1,2);
                break;
            case SDLK_t:
                att->addToAttribute(1,-2);
                break;
            case SDLK_h:
                att->addToAttribute(5,2);
                break;
            case SDLK_g:
                att->addToAttribute(5,-2);
                break;
            case SDLK_n:
                att->addToAttribute(3,2);
                break;
            case SDLK_b:
                att->addToAttribute(3,-2);
                break;
            case SDLK_x:
                att->addToAttribute(7,10);
                break;
            }
        }
    }
};