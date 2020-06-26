#include "../include/Game.hpp"


SDL_Renderer* Game::renderer = nullptr;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int x, int y, int width, int height,bool fullscreen) {
    int f= fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    stat=2;
    if (SDL_Init(SDL_INIT_EVERYTHING)==0) {
        window=SDL_CreateWindow(title,x,y,width,height,f);
        if (window) {
            renderer=SDL_CreateRenderer(window,-1,0);
            if (renderer)
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
        }
    }
    auto& nPlayer(manager.addEntity());
    mapa = new Mapa("assets/Tiles_Sheet-Sheet.png",renderer,45,80);
    menu = new GameMenu("assets/menu.png",renderer);
    nPlayer.addComponent<SpriteComponent>("assets/First dude-Sheet.png");
    nPlayer.addComponent<PositionComponent>();
}

void Game::render() {
    SDL_RenderClear(renderer);
    switch (stat) {
        case 1: //user está no menu principal
            menu->render();
        break;
        case 2: //user está no mapa do mundo
            mapa->render();
            manager.draw();
        break;
        case 3: //user está a jogar
            manager.draw();
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

