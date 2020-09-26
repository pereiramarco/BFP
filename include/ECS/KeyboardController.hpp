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
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_UP:
                transform->velocity.y=-1;
                sprite->play("up");
                break;
            case SDLK_DOWN:
                transform->velocity.y=1;
                sprite->play("down");
                break;
            case SDLK_LEFT:
                transform->velocity.x=-1;
                sprite->play("left");
                break;
            case SDLK_RIGHT:
                transform->velocity.x=1;
                sprite->play("right");
                break;
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

        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_UP:
                transform->velocity.y=0;
                sprite->play("idle");
                break;
            case SDLK_DOWN:
                transform->velocity.y=0;
                sprite->play("idle");
                break;
            case SDLK_LEFT:
                transform->velocity.x=0;
                sprite->play("idle");
                break;
            case SDLK_RIGHT:
                transform->velocity.x=0;
                sprite->play("idle");
                break;
            }
        }
    }
};