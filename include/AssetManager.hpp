#pragma once

#include <map>
#include <string>
#include "ECS/ECS.hpp"
#include "Vector2D.hpp"
#include "SDL2/SDL.h"


class AssetManager {
public:
    AssetManager(Manager* manager);
    ~AssetManager();
    void addTexture(std::string texID,const char * path);
    SDL_Texture* getTexture(std::string textureID);
private:
    std::map<std::string,SDL_Texture*> textures;
    Manager* manager;
};