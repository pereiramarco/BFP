
#include "../include/game.hpp"

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
    mapa = new Mapa("assets/Tiles_Sheet-Sheet.png",renderer,50,50);
    player= new GameObject("assets/First dude-Sheet.png",renderer,0,0);
    menu= new GameMenu("assets/menu.png",renderer);
}

void Game::render() {
    SDL_RenderClear(renderer);
    switch (stat) {
        case 1: //user está no menu principal
            menu->render();
        break;
        case 2: //user está no mapa do mundo
            mapa->render();
        break;
        case 3: //user está a jogar
            player->render();
        break;
        default :
        break;
    }
    SDL_RenderPresent(renderer);
}

void Game::handleinput() {

}

void Game::update() {

}

