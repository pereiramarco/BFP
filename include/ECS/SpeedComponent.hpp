#pragma once

#include "ECS.hpp"

class SpeedComponent : public Component {
private:
    int xSpeed = 0;
    int ySpeed = 0;
public:
    SpeedComponent() {
        xSpeed = 0;
        ySpeed = 0;
    }

    SpeedComponent(int x, int y) {
        xSpeed = x;
        ySpeed = y;
    }

    int speedX() {return xSpeed;}

    void speedX(int x) {xSpeed=x;}

    int speedY() {return ySpeed;}

    void speedY(int y) {ySpeed=y;}

    void setSpeed(int x,int y) {
        xSpeed=x;
        ySpeed=y;
    }
};