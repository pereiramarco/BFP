#pragma once

#include <map>
#include <string>
#include "SDL2/SDL.h"
#include "ECS.hpp"
#include "TransformComponent.hpp"


class WanderAroundComponent : public Component {
public:
    TransformComponent * transform;
    Vector2D initialPos;
    float maxDistance;
    int maxTicks=0;
    int sense1;
    int sense2;
    float x;
    float y;

    WanderAroundComponent(float maxDistanceG){
        maxDistance=maxDistanceG;
    }

    void update() {
        if (maxTicks==0) {
            x=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            y=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            sense1=rand()%2?1:-1;
            sense2=rand()%2?1:-1;
            maxTicks=80;
        }
        if (x<=0.2) x=0.2;
        if (y<=0.2) y=0.2;
        if (x>=0.7) x=0.7;
        if (y>=0.7) y=0.7;
        x*=sense1;
        y*=sense2;
        Vector2D * d =new Vector2D(x,y);
        Vector2D maybeFinal=transform->position.copy()+=(*d).operator*(transform->speed);
        if (distanceBetweenPoints(maybeFinal.x,maybeFinal.y,initialPos.x,initialPos.y)<=maxDistance) {
            transform->velocity=*d;
            transform->updateSentido();
        }
        else transform->velocity.zero();
        maxTicks--;
    }

    void init() override {
        transform=&entity->getComponent<TransformComponent>();
        initialPos=transform->position.copy();
    }

private:

    double distanceBetweenPoints(int x1,int y1,int x2,int y2) {
        return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    }
};