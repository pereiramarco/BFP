#pragma once

#include "GameLevel.hpp"
#include "GameData.hpp"

class GameLevelMenu : public GameLevel {

public:
    GameLevelMenu(GameData * gameData);

    virtual void update();
    virtual void render();

private:

};