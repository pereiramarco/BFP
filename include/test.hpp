#ifndef test
#define test

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "map.hpp"
#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;

class Game {
    
public:
    Game(); //creator
    ~Game(); //destroyer
    void init(const char* title, int x, int y, int width, int height,bool fullscreen);
    void renderMap();
    void handleinput();
    void update();
    bool isRunning;
private:
    SDL_Window *window;
    SDL_Renderer * renderer;
    Mapa mapa;
};

#endif