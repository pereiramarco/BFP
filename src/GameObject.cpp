
#include "../include/GameObject.hpp"

GameObject::GameObject(const char* sheet,SDL_Renderer* renderer,int x,int y) {
    this->renderer = renderer;
    this->texture = TextureManager::loadTexture(sheet,this->renderer);
    posx=x;
    posy=y;
    destR.x=0;
    destR.y=0;
    srcR.x=0;
    srcR.y=0;
    srcR.h=24;
    srcR.w=18;
    destR.w=18;
    destR.h=24;
}

void GameObject::update() {

}

void GameObject::render() {
    SDL_RenderCopy(renderer,texture,&srcR,&destR);
}
