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
    switch (GameEngine::change) {
        case 0:
           gameData->setRunning(false); 
        break;
        case 1: //Menu
            gameState=new GameLevelMenu(gameData);
            gameData->stat=1;
        break;
        case 2: //World
            gameState=new GameLevelWorld(gameData);
            gameData->stat=2;
        break;
        case 3: //Ingame
            gameState=new GameLevelIngame(gameData);
            gameData->stat=3;
        break;
    }
    GameEngine::change=-1;
}

