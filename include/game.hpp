#pragma once

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "map.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
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
    int stat;

private:
    SDL_Window *window;
    SDL_Renderer * renderer;
    Mapa * mapa;
    GameObject * player;
    GameMenu * menu;
};