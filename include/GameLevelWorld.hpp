#pragma once

#include "GameLevel.hpp"
#include "GameData.hpp"

class GameLevelWorld : public GameLevel {

public:
    GameLevelWorld(GameData * gameData);

    virtual void update();
    virtual void render();

private:
    Entity * square;

    void updatePos();

};