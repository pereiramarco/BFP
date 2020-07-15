#pragma once

#include "../Vector2D.hpp"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    int speed;

    TransformComponent() {
        position.x=960;
        position.y=540;
        velocity.x=0;
        velocity.y=0;
        speed=20;
    }

    TransformComponent(float x,float y) {
        position.x=960;
        position.y=540;
        velocity.x=0;
        velocity.y=0;
        speed=20;
    }

    void update() override {
        Game::localPosition->x+=speed*velocity.x/64.0;
        Game::localPosition->y+=speed*velocity.y/64.0;
        if (Game::localPosition->x>50)  {
            if (Game::worldPosition->x<79) 
            {
                Game::worldPosition->x+=1;
                Game::localPosition->x-=50.0;
                Game::loadLocal();
            }
            else Game::localPosition->x=49;
        }
        if (Game::localPosition->y>50)  {
            if (Game::worldPosition->y<44) {
                Game::worldPosition->y+=1;
                Game::localPosition->y-=50.0;
                Game::loadLocal();
            }
            else Game::localPosition->y=49;
        }
        if (Game::localPosition->x<0)  {
            if (Game::worldPosition->x>0) {
                Game::worldPosition->x-=1;
                Game::localPosition->x+=50;
                Game::loadLocal();
            }
            else Game::localPosition->x=0;
        }
        if (Game::localPosition->y<0)  {
            if (Game::worldPosition->y>0) {
                Game::worldPosition->y-=1;
                Game::localPosition->y+=50;
                Game::loadLocal();
            }
            else Game::localPosition->y=0;
        }
    }
};