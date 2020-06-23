#include "../include/GameMenu.hpp"

GameMenu::GameMenu(const char* name, SDL_Renderer* ren) {
    this->renderer=ren;
    this->texture=TextureManager::loadTexture(name,renderer);
    destR.h=540;
    destR.w=960;
    srcR.h=540;
    srcR.w=960;
    destR.x=0;
    destR.y=0;
    srcR.x=0;
    srcR.y=0;
}

void GameMenu::render() {
    texture=TextureManager::loadTexture("assets/menu.png",renderer);
    SDL_RenderCopy(renderer,texture,&srcR,&destR);
}