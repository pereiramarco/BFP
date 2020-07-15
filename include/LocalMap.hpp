#pragma once
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include <math.h>
#include <ctime>
#include <utility>
#include <map>


class LocalMap {
private:
    std::pair<char,int> **mapa;
    std::map<char,SDL_Texture*> textures;
    SDL_Renderer * ren;
    SDL_Rect srcR,destR;
public:
    LocalMap();
    LocalMap(SDL_Renderer * ren,std::map<char,SDL_Texture*> tex);
    void randomizeTile(char type);
    std::pair<char,int> getTile(int i,int j);
    void setTile(int i,int j,std::pair<char,int> par);
};



