#pragma once 

#include "../Game.hpp"
#include "ECS.hpp"
#include "MenuPositionComponent.hpp"

class MenuKeyboardController : public Component {
public:
    MenuPositionComponent * transform;

    void init() override {
        transform=&entity->getComponent<MenuPositionComponent>();
    }

    void update() override {
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_UP:
                transform->velocity.y=-1;
                break;
            case SDLK_DOWN:
                transform->velocity.y=1;
                break;
            case SDLK_RETURN:
                Game::statb4=Game::stat;
                switch ((int)transform->position.y)
                {
                case 0:
                    Game::stat=2;
                    break;
                case 1:
                    Game::stat=3;
                    break;
                case 2:
                    Game::stat=4;
                    break;
                case 3:
                    Game::stat=0;
                    break;
                default:
                    break;
                }
                entity->destroy();
                break;
            default:
                break;
            }
        }

        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_UP:
                transform->velocity.y=0;
                break;
            case SDLK_DOWN:
                transform->velocity.y=0;
                break;
            }
        }
    }
};