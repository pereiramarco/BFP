#pragma once
#include "GameLevel.hpp"
#include "GameLevelIngame.hpp"
#include "GameLevelWorld.hpp"
#include "GameLevelMenu.hpp"
#include "GameData.hpp"

class GameEngine {

public:
    bool isRunning();
    void init(const char* name,int x,int y,int width,int height,bool fullscreen);
    void update();
    void render();
    void handleinput();
    void changeState();

    static int change;

private:
    GameLevel* gameState;
    GameData* gameData;
    
};