#pragma once

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "ECS/ECS.hpp"
#include "AssetManager.hpp"
#include "Map.hpp"
#include "Groups.hpp"

class GameData {

public:

    GameData(const char* title, int x, int y, int width, int height,bool fullscreen);
    bool isRunning();
    void setRunning(bool running);
    void firstF(bool b);
    bool isFirst();
    void initSave(std::string savename);
    SDL_Event getEvent();
    void setKey(int index,bool value);
    void delGroup(Group g);
    Entity& addEntity();
    std::vector<Entity*> getGroup(Group g);
    void managerUpdate();
    void managerRefresh();
    void setWorldPosition(Vector2D * worldPos);
    Vector2D * getWorldPosition();
    void setLocalPosition(Vector2D * localPos);
    Vector2D * getLocalPosition();
    SDL_Rect getCamera();
    void setCamera(SDL_Rect camera);
    void clearRenderer();
    void renderPresent();
    Dungeon* getDungeon(std::pair<int,int> pos);
    int getSettlementBuildingV(int x,int y,int type);
    LocalMap * getLocalMap(int x,int y);
    

    static void addTileWorld(float x,float y,int tile);

    static int stat;
    static bool xpadd;
    static SDL_Renderer * renderer;
    static SDL_Event event;
    static AssetManager* textures;
    static Vector2D * worldPosition;
    static Vector2D * localPosition;
    static SDL_Rect camera;
    static std::map<int,bool> KEYS;

private:
    
    static bool first;
    bool is_running;
    static Manager manager;
    Mapa * mapa;
    SDL_Window *window;
    
};