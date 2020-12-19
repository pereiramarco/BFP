#pragma once

#include "../Vector2D.hpp"
#include "../ConstantValues.hpp"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    float speed;
    int sentido=0; //0 north      //4 south
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

    void setSpeed(float speedG) {
        speed = speedG;
    }

    void setPos(Vector2D posG) {
        position=posG;
    }

    void update() override {
        position.x+=speed*velocity.x;
        position.y+=speed*velocity.y;
    }

    bool isVel0() {
        return velocity.x==0 && velocity.y==0;
    }

    bool isVelClose0() {
        return velocity.x>=-0.3 && velocity.x<=0.3 && velocity.y>=-0.3 && velocity.y<=0.3;
    }

void updateSentido() {
    bool u=velocity.y>0.3,r=velocity.x>0.3,d=velocity.y<-0.3,l=velocity.x<-0.3,b=true;
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
        sentido=s;
}    
};