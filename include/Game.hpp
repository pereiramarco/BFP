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

    static void addTile(int x,int y,bool mundo, int tile, std::pair<char,int> type);
    static void loadLocal();
    static int statb4;
    static int stat;
    static SDL_Renderer * renderer;
    static SDL_Event event;
    static AssetManager* textures;
    static Vector2D * worldPosition;
    static Vector2D * localPosition;
private:
    static Manager manager;
    static Mapa * mapa;
    SDL_Window *window;
};