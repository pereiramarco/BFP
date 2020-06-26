#pragma once

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

class GameMenu {
public:
    GameMenu(const char * name, SDL_Renderer * ren);
    ~GameMenu();
    void render();
    void update();
    void handleinput();
private:
    SDL_Renderer * renderer;
    SDL_Texture * texture;
    SDL_Rect srcR,destR;
};