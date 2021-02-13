#pragma once

#include "GameLevel.hpp"
#include "GameData.hpp"
#include "unordered_set"

class GameLevelIngame : public GameLevel {

public:
    GameLevelIngame(GameData * gameData);
    
    virtual void handleinput();
    virtual void update();
    virtual void render();

private:
    Entity* player;
    bool inside;
    Vector2D positionOutside;
    std::unordered_set<Entity*> overlap;
    bool interact;

    void initUI();
    void updatePos();
    void updateUI();
    void updateCollision(Entity * ent,int typeOfEnt,Vector2D lastPosition,Vector2D localPos,Vector2D worldPos);
    void updateCollisions(Vector2D playerpos,Vector2D localPos,Vector2D worldPos,std::map<Entity*,Vector2D> enemiePos);
    void updateOverlaps();
    void checkInteractions();
    void updateCam();
    void loadLocal();
    void loadDungeon();
    void addTileLocal(float x,float y,std::pair<char,int> type,bool b);
    void addTileInside(float x,float y,int mos);
};