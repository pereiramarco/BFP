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
    loadWorld();
}


void GameLevelWorld::addTileWorld(float x,float y,int mos) {
    int r1,r2,d;
    auto& tile(gameData->addEntity());
    r1=ConstantValues::worldTileH;
    r2=ConstantValues::worldTileW;
    d=16; //size inside sprite sheet
    tile.addComponent<TileComponent>(x,y,d,d,r2,r1,mos);
    tile.addGroup(GroupWorldMap);
}


void GameLevelWorld::loadWorld() {
    int height=gameData->getWorldMapHeight();
    int width=gameData->getWorldMapWidth();
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            int id=gameData->getWorldMapTile(i,j);
            addTileWorld(i,j,id);
        }
    }
    int id;
    for (auto& entry : gameData->getLocations()) {
        switch (entry.second) {
            case Location::Village:
                id=4;
            break;
            case Location::Kingdom:
                id=3;
            break;
            case Location::Dungeon:
                id=5;
            break;
        }
        addTileWorld(entry.first.first,entry.first.second,id);
    }
}

void GameLevelWorld::handleinput() {
    SDL_Event event = gameData->getEvent();
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: 
                        GameEngine::change=1;
                    break;
                }
                gameData->setKey(event.key.keysym.sym,true);
            break;
            case SDL_KEYUP:
                gameData->setKey(event.key.keysym.sym,false);
            break;
        }
    }
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