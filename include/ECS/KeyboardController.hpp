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

    void updateSentido() {
        bool u=Game::KEYS[SDLK_UP],r=Game::KEYS[SDLK_RIGHT],d=Game::KEYS[SDLK_DOWN],l=Game::KEYS[SDLK_LEFT],b=true;
        int s;
        if (u && r) s=1;
        else if (u && l) s=7;
        else if (u) s=0;
        else if (r && d) s=3;
        else if (r) s=2;
        else if (d && l) s=5;
        else if (d) s=4;
        else if (l) s=6;
        else b=false;
        if (b)
            transform->sentido=s;
    }

    void update() override {
        bool r=false;
        int shift=1+Game::KEYS[SDLK_LSHIFT];
        if (Game::KEYS[SDLK_UP] && !Game::KEYS[SDLK_DOWN]) {
            r=true;
            transform->velocity.y=-1*shift;
            sprite->play("up");
            sprite->timesSpeed(shift);
        }
        else 
            if (Game::KEYS[SDLK_DOWN] && !Game::KEYS[SDLK_UP]) {
                r=true;
                transform->velocity.y=1*shift;
                sprite->play("down");
                sprite->timesSpeed(shift);
            }
            else {
                transform->velocity.y=0;
            }
        if (Game::KEYS[SDLK_LEFT] && !Game::KEYS[SDLK_RIGHT]) {
            r=true;
            transform->velocity.x=-1*shift;
            sprite->play("left");
            sprite->timesSpeed(shift);
        }
        else 
            if (Game::KEYS[SDLK_RIGHT] && !Game::KEYS[SDLK_LEFT]) {
                r=true;
                transform->velocity.x=1*shift;
                sprite->play("right");
                sprite->timesSpeed(shift);
            }
        else {
            transform->velocity.x=0;
        }
        updateSentido();
        if (!r) {
            int s=transform->sentido;
            if (s==0) sprite->play("idle-up");
            else if (s==4) sprite->play("idle-down");
            else if (s<4) sprite->play("idle-right");
            else sprite->play("idle-left");
        }
        if (shift-1 && (transform->velocity.x || transform->velocity.y)) { //player is running
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