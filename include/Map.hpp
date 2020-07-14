#pragma once
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "LocalMap.hpp"
#include <math.h>
#include <ctime>
#include <map>

class Mapa {
public:
    Mapa(SDL_Renderer * renderer,int h,int w);
    ~Mapa();
    void render();
    int getHeight();
    int getWidth();
    int getTile(int i,int j);
    LocalMap* getLocalMap(int i,int j);
    std::pair<char,int> getLocalMapTile(int wI,int wJ,int i,int j);
    void randomizeMap(int fP);
    bool hasWaterNeighbour(int x,int y);
    int closestCreator(int x,int y);
    void randomizeLocalMaps();
private:
    SDL_Renderer * renderer;
    SDL_Rect srcR,destR;
    int **worldMap;
    int height;
    int width;
    LocalMap ***mapa;
    std::map<char,SDL_Texture*> mapOfTexs;
};
