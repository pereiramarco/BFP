#pragma once
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include <math.h>
#include <ctime>

class Mapa {
public:
    Mapa(const char * name,SDL_Renderer * renderer,int h,int w);
    ~Mapa();
    void render();
    int getHeight();
    int getWidth();
    int getTile(int i,int j);
    void randomizeMap(int fP);
    bool hasWaterNeighbour(int x,int y);
    int closestCreator(int x,int y);
private:
    SDL_Renderer * renderer;
    SDL_Texture * texture;
    SDL_Rect srcR,destR;
    int **mapa;
    int height;
    int width;
};
