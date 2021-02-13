#pragma once

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "ECS/ECS.hpp"
#include "GameData.hpp"
#include "AssetManager.hpp"
#include "Map.hpp"
#include "Groups.hpp"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>

class GameLevel {
    
public:
    virtual void handleinput()=0;
    virtual void render()=0;
    virtual void update()=0;

protected:
    GameData * gameData;
};