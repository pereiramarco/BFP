#include "../include/GameLevelWorld.hpp"
#include "../include/ECS/Components.hpp"
#include "../include/ConstantValues.hpp"

#include <iostream>

GameLevelWorld::GameLevelWorld(GameData* gameDataG) {
    gameData=gameDataG;

    gameData->delGroup(GroupUI); //deletes the UI
    gameData->delGroup(GroupEnemies); //apaga os inimigos

    SDL_Rect camera={0,0,(ConstantValues::mapH-1)*ConstantValues::worldTileH,(ConstantValues::mapW-1)*ConstantValues::worldTileW};
    gameData->setCamera(camera);
    if (gameData->isFirst()) {
        gameData->initSave("nome");
        gameData->firstF(false);
    }
    auto& squareD(gameData->addEntity());
    squareD.addComponent<TransformComponent>();
    squareD.addComponent<SpriteComponent>("square");
    squareD.addComponent<KeyboardController>();
    SDL_Rect r; r.w=24;r.h=24; 
    squareD.getComponent<SpriteComponent>().setDest(r);
    squareD.getComponent<SpriteComponent>().setSkip(24);
    Vector2D* pos=gameData->getWorldPosition();
    squareD.getComponent<TransformComponent>().position.x=pos->x;
    squareD.getComponent<TransformComponent>().position.y=pos->y;
    squareD.getComponent<TransformComponent>().speed=0.25;
    squareD.addGroup(GroupPlayers);
    square = &squareD;
}

void GameLevelWorld::render() {
    auto tilesWorld = gameData->getGroup(GroupWorldMap);
    auto players = gameData->getGroup(GroupPlayers);

    gameData->clearRenderer();

    for (auto& i : tilesWorld) {
        i->draw();
    }
    
    for (auto& i : players) {
        i->draw();
    }
    gameData->renderPresent();
}

void GameLevelWorld::updatePos() {
    Vector2D * worldPos = new Vector2D();
    worldPos->x=square->getComponent<SpriteComponent>().getDestx()/ConstantValues::worldTileW;
    worldPos->y=square->getComponent<SpriteComponent>().getDesty()/ConstantValues::worldTileH;
    gameData->setWorldPosition(worldPos);
}

void GameLevelWorld::update() {
    updatePos();

    gameData->managerRefresh();
    gameData->managerUpdate();
}