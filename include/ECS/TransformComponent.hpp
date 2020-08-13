#pragma once

#include "../Vector2D.hpp"
#include "../ConstantValues.hpp"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    int speed;

    TransformComponent() {
        position.x= ConstantValues::screenSizeW/2;
        position.y= ConstantValues::screenSizeH/2;
        velocity.x=0;
        velocity.y=0;
        speed=10;
    }

    void update() override {
        position.x+=speed*velocity.x;
        position.y+=speed*velocity.y;
    }
};