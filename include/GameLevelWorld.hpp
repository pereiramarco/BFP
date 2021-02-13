#pragma once

#include "GameLevel.hpp"
#include "GameData.hpp"

class GameLevelWorld : public GameLevel {

public:
    GameLevelWorld(GameData * gameData);

    virtual void handleinput();
    virtual void update();
    virtual void render();

    void loadWorld();

private:
    Entity * square;
    void addTileWorld(float x,float y,int tileId);

    void updatePos();

};