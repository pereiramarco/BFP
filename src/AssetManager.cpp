#include "../include/AssetManager.hpp"
#include "../include/TextureManager.hpp"

AssetManager::AssetManager(Manager * man) {
    manager=man;
}

AssetManager::~AssetManager() {
    for (std::map<std::string,SDL_Texture*>::iterator it=this->textures.begin();it!=textures.end();it++) {
        SDL_DestroyTexture(it->second);
    }
}

void AssetManager::addTexture(std::string texID,const char * path) {
    textures.emplace(texID,TextureManager::loadTexture(path));
}

SDL_Texture* AssetManager::getTexture(std::string id) {
    return textures[id];
}