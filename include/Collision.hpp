#pragma once

#include "SDL2/SDL.h"

class Collision {
    public:
        static bool AABB (SDL_Rect r1,SDL_Rect r2) {
            return r1.x+r1.w>=r2.x && r2.x+r2.w>=r1.x && r2.y+r2.h>=r1.y && r1.y+r1.h>=r2.y;
        }
};