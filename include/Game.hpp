#pragma once

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "ECS/ECS.hpp"
#include "Map.hpp"
#include "LocalMap.hpp"
#include "GameMenu.hpp"
#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;

class Game {
    
public:
    Game(); //creator
    ~Game(); //destroyer
    void init(const char* title, int x, int y, int width, int height,bool fullscreen);
    void render();
    void handleinput();
    void update();

    static int statb4;
    static int stat;
    static SDL_Renderer * renderer;
    static SDL_Event event;
private:
    SDL_Window *window;
    Manager manager;
    Mapa * mapa;
    LocalMap * local;
};