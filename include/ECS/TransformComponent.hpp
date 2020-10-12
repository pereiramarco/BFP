#pragma once

#include "../Vector2D.hpp"
#include "../ConstantValues.hpp"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    float speed;
    int sentido=4; //0 north      //4 south
                   //1 northeast  //5 southwest
                   //2 east       //6 west
                   //3 southeast  //7 northwest

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