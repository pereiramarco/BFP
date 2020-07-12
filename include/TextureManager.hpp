#pragma once

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

class TextureManager {
public:
    static SDL_Texture* loadTexture(const char * path);
    static void draw(SDL_Texture * tex,SDL_Rect src,SDL_Rect dest);
};