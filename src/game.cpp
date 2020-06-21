
#include "../include/game.hpp"


SDL_Texture * tiles;
SDL_Rect srcR,destR;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int x, int y, int width, int height,bool fullscreen) {
    int f= fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    isRunning=true;
    if (SDL_Init(SDL_INIT_EVERYTHING)==0) {
        window=SDL_CreateWindow(title,x,y,width,height,f);
        if (window) {
            renderer=SDL_CreateRenderer(window,-1,0);
            if (renderer)
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
        }
    }
    SDL_Surface* tmpSrfc = IMG_Load("assets/Tiles_Sheet-Sheet.png");
    tiles=SDL_CreateTextureFromSurface(renderer,tmpSrfc);
    SDL_FreeSurface(tmpSrfc);
    destR.h=16;
    destR.w=16;
    srcR.h=16;
    srcR.w=16;
    destR.x=0;
    destR.y=0;
    srcR.x=0;
    srcR.y=0;
    mapa.initMap(50,50);
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
            SDL_RenderCopy(renderer,tiles,&srcR,&destR);
        }
        destR.x=0;
        destR.y+=16;
    }
    SDL_RenderPresent(renderer);
}

void Game::handleinput() {

}

void Game::update() {

}

