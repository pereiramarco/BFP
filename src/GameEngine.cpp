#include "../include/GameEngine.hpp"
#include "../include/GameData.hpp"
#include "../include/ConstantValues.hpp"

int GameEngine::change=-1;

void GameEngine::update() {
    changeState();
    gameState->update();
}

void GameEngine::init(const char* name,int x,int y,int width,int height,bool fullscreen) {
    gameData=new GameData(name,x,y,width,height,fullscreen);
    gameData->firstF(true);
    gameData->setRunning(true);
    gameState=new GameLevelMenu(gameData);
}

void GameEngine::render() {
    gameState->render();
}

void GameEngine::handleinput() {
    gameState->handleinput();
}

bool GameEngine::isRunning() {
    return gameData->isRunning();
}

void GameEngine::changeState() {
    if (!GameEngine::change) {
        gameData->setRunning(false); 
        return;
    } 
    if (GameEngine::change==-1) return;
    gameData->clearManager();
    gameData->managerRefresh();
    switch (GameEngine::change) {
        case 1: //Menu
            gameState=new GameLevelMenu(gameData);
        break;
        case 2: //World
            gameState=new GameLevelWorld(gameData);
        break;
        case 3: //Ingame
            gameState=new GameLevelIngame(gameData);
        break;
    }
    gameData->stat=GameEngine::change;
    GameEngine::change=-1;
}

