#pragma once

#include "TextureManager.hpp"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

class GameObject {
public:
    GameObject(const char* sheet,SDL_Renderer* renderer,int x,int y);
    ~GameObject();
    void update();
    void render();
private:
    SDL_Renderer* renderer;
    SDL_Texture * texture;
    SDL_Rect srcR,destR;
    double posx;
    double posy;
    double speed;

};