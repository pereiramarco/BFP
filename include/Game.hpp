#pragma once

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "ECS/ECS.hpp"
#include "AssetManager.hpp"
#include "Map.hpp"
#include "LocalMap.hpp"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>


class Game {
    
public:
    Game(); //creator
    ~Game(); //destroyer
    void init(const char* title, int x, int y, int width, int height,bool fullscreen);
    void initSave(std::string savename);
    void render();
    void handleinput();
    void update();
    void updatePos();
    void updateCam();
    void loadLocal();
    void loadDungeon();
    void updateCollision(Entity * ent,int typeOfEnt,Vector2D lastPosition,Vector2D localPos,Vector2D worldPos);
    void updateCollisions(Vector2D playerpos,Vector2D localPos,Vector2D worldPos,std::map<Entity*,Vector2D> enemiePos);
    void updateOverlaps();
    void checkInteractions();
    void addTileLocal(float x,float y,std::pair<char,int> type,bool b);
    void addTileInside(float x,float y,int mos);
    void initUI();
    void updateUI();

    static void addTileWorld(float x,float y,int tile);
    static int statb4;
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
    static Manager manager;
    static Mapa * mapa;
    SDL_Window *window;
};