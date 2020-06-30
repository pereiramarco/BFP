#pragma once

#include "../Vector2D.hpp"
#include "ECS.hpp"

class MenuPositionComponent : public Component {
public:
    int noptions;
    Vector2D position;
    Vector2D velocity;
    float speed;

    MenuPositionComponent() {
        noptions=0;
        position.x=0;
        position.y=0;
        velocity.x=0;
        velocity.y=0;
        speed=0.13;
    }

    MenuPositionComponent(float x,float y,int noptions) {
        this->noptions=noptions;
        position.x=x;
        position.y=y;
        velocity.x=0;
        velocity.y=0;
        speed=0.13;
    }

    void update() override {
        position.y+=speed*velocity.y;
        while (position.y>=noptions)
            position.y-=noptions;
        while (position.y<0) {
            position.y+=noptions;
        }        
    }


};