#include "../include/TextureManager.hpp"
#include "../include/GameData.hpp"

SDL_Texture* TextureManager::loadTexture(const char * name) {
    SDL_Surface* tmpSrfc = IMG_Load(name);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(GameData::renderer,tmpSrfc);
    SDL_FreeSurface(tmpSrfc);
    return tex;
}

void TextureManager::draw(SDL_Texture * tex,SDL_Rect src,SDL_Rect dest) {
    SDL_RenderCopy(GameData::renderer,tex,&src,&dest);
}