#pragma once

#include "../Vector2D.hpp"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    int speed;

    TransformComponent() {
        position.x=965;
        position.y=450;
        velocity.x=0;
        velocity.y=0;
        speed=6;
    }

    TransformComponent(float x,float y) {
        position.x=965;
        position.y=450;
        velocity.x=0;
        velocity.y=0;
        speed=6;
    }

    void update() override {
        Game::localPosition->x+=speed*velocity.x;
        Game::localPosition->y+=speed*velocity.y;

        if (Game::localPosition->x>49)  {
            if (Game::worldPosition->x<79) 
            {
                Game::worldPosition->x+=1;
                Game::localPosition->x=0;
            }
            else Game::localPosition->x=49;
        }
        if (Game::localPosition->y>49)  {
            if (Game::worldPosition->y<44) {
            Game::worldPosition->y+=1;
            Game::localPosition->y=0;
            }
            else Game::localPosition->y=49;
        }
        if (Game::localPosition->x<0)  {
            if (Game::worldPosition->x>0) {
                Game::worldPosition->x-=1;
                Game::localPosition->x=49;
            }
            else Game::localPosition->x=0;
        }
        if (Game::localPosition->y<0)  {
            if (Game::worldPosition->y>0) {
                Game::worldPosition->y-=1;
                Game::localPosition->y=49;
            }
            else Game::localPosition->y=0;
        }
    }


};