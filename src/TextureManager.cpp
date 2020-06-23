#include "../include/TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char * name,SDL_Renderer* renderer) {
    SDL_Surface* tmpSrfc = IMG_Load(name);
    if (tmpSrfc==NULL) printf("%s\n",name);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(renderer,tmpSrfc);
    SDL_FreeSurface(tmpSrfc);
    return tex;
}