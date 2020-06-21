#ifndef test
#define test

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <ctime>

using namespace std;

void map(int **map,int width,int height);

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
    int ** mapa;
    int heightM;
    int widthM;
};

#endif