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

//defines para os diferentes stats do jogo
#define CLOSE 0
#define MAINMENU 1
#define WORLDMAP 2
#define INGAME 3
#define OPTIONSMENU 4
#define INSIDE 5
#define INVENTORY 6


class GameLevel {
    
public:
    void handleinput();

    virtual void render()=0;
    virtual void update()=0;

protected:
    GameData * gameData;
};