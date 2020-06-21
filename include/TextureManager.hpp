#pragma once

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

class TextureManager {
    public:
    static SDL_Texture* loadTexture(const char * name,SDL_Renderer* renderer);
};