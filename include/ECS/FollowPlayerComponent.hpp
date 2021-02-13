#pragma once

#include <map>
#include <string>
#include "SDL2/SDL.h"
#include "TransformComponent.hpp"


class FollowPlayerComponent : public Component {
public:
    TransformComponent * target;
    TransformComponent * enemy;
    float close;
    int run;

    FollowPlayerComponent(TransformComponent* tC,int rG,int closeG){
        target = tC;
        run = rG;
        close = closeG*64;
    }

    void update() {
        Vector2D targetPos = target->position;
        Vector2D enemyPos = enemy->position;
        float dist = distanceBetweenPoints(targetPos.x,targetPos.y,enemyPos.x,enemyPos.y);
        if (dist && ((run==1 && dist>close) || (run==-1 && dist<close))) {
            enemy->velocity=(targetPos.operator-=(enemyPos).operator/(dist)).operator*(run);
            enemy->updateSentido();
        }
        else enemy->velocity.zero();
    }

    void init() override {
        enemy=&entity->getComponent<TransformComponent>();
    }

private:
    
};