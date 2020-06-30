#pragma once
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include <math.h>
#include <ctime>

class LocalMap {
private:
    int mapa[50][50];
    SDL_Texture* tex;
    SDL_Renderer * ren;
    SDL_Rect srcR,destR;
public:
    LocalMap(const char *name,SDL_Renderer * ren);
    void render();
    void randomizeTile();
};



