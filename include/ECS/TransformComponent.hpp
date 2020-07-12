#pragma once

#include "../Vector2D.hpp"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    int speed;

    TransformComponent() {
        position.x=0;
        position.y=0;
        velocity.x=0;
        velocity.y=0;
        speed=6;
    }

    TransformComponent(float x,float y) {
        position.x=x;
        position.y=y;
        velocity.x=0;
        velocity.y=0;
        speed=6;
    }

    void update() override {
        position.x+=speed*velocity.x;
        position.y+=speed*velocity.y;
    }


};