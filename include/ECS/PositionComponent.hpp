#pragma once

#include "ECS.hpp"

class PositionComponent : public Component {
private:
    int xpos = 0;
    int ypos = 0;
public:
    PositionComponent() {
        xpos=0;
        ypos=0;
    }

    PositionComponent(int x,int y) {
        xpos=x;
        ypos=y;
    }

    int x() {return xpos;}

    void x(int x) {xpos=x;}

    int y() {return ypos;}

    void y(int y) {ypos=y;}

    void setPos(int x,int y) {
        xpos=x;
        ypos=y;
    }
};