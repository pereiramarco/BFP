#include "../include/TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char * name) {
    SDL_Surface* tmpSrfc = IMG_Load(name);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(Game::renderer,tmpSrfc);
    SDL_FreeSurface(tmpSrfc);
    return tex;
}

void TextureManager::draw(SDL_Texture * tex,SDL_Rect src,SDL_Rect dest) {
        if (Game::stat==3) {
            dest.h=72;
            dest.w=72;
        }
        SDL_RenderCopy(Game::renderer,tex,&src,&dest);
}