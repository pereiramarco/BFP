
#include "../include/game.hpp"


SDL_Texture * texture;
SDL_Rect srcR,destR;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int x, int y, int width, int height,bool fullscreen) {
    int f= fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    stat=1;
    if (SDL_Init(SDL_INIT_EVERYTHING)==0) {
        window=SDL_CreateWindow(title,x,y,width,height,f);
        if (window) {
            renderer=SDL_CreateRenderer(window,-1,0);
            if (renderer)
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
        }
    }
    destR.h=540;
    destR.w=960;
    srcR.h=540;
    srcR.w=960;
    destR.x=0;
    destR.y=0;
    srcR.x=0;
    srcR.y=0;
    mapa.initMap(50,50);
}

void Game::renderMain() {
    SDL_RenderClear(renderer);
    texture=TextureManager::loadTexture("assets/menu.png",renderer);
    SDL_RenderCopy(renderer,texture,&srcR,&destR);
    SDL_RenderPresent(renderer);
}

void Game::renderMap() {
    destR.h=16;
    destR.w=16;
    srcR.h=16;
    srcR.w=16;
    destR.x=0;
    destR.y=0;
    srcR.x=0;
    srcR.y=0;
    texture=TextureManager :: loadTexture("assets/Tiles_Sheet-Sheet.png",renderer);
    mapa.randomizeMap(30);
    SDL_RenderClear(renderer);
    for (int i=0;i<mapa.getHeight();i++) {
        for (int j=0;j<mapa.getWidth();j++,destR.x+=16) {
            switch (mapa.getTile(i,j)) {
                case (0):
                    srcR.x=16;
                break;
                case (1):
                    srcR.x=0;
                break;
                case (2):
                    srcR.x=32;
                break;
                default:
                break;
            }
            SDL_RenderCopy(renderer,texture,&srcR,&destR);
        }
        destR.x=0;
        destR.y+=16;
    }
    SDL_RenderPresent(renderer);
}

void Game::render() {
    switch (stat) {
        case 1: //user está no menu principal
            renderMain();
        break;
        default :
        break;
    }

}

void Game::handleinput() {

}

void Game::update() {

}

