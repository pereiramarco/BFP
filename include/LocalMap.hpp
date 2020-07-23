#pragma once
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include <math.h>
#include <ctime>
#include <utility>
#include <map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>

class LocalMap {
private:
    std::pair<char,int> **mapa;
    std::map<char,SDL_Texture*> textures;
    char**mancha;

public:
    LocalMap();
    LocalMap(std::string,std::map<char,SDL_Texture*> tex);
    void randomizeTile(char type0,char type1,char type2,char type3,char type4);
    std::pair<char,int> getTile(int i,int j);
    void setTile(int i,int j,std::pair<char,int> par);
};



