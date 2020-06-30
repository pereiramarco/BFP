#include "../include/Game.hpp"
#include "../include/ECS/Components.hpp"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
int Game::stat=0;
int Game::statb4=0;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int x, int y, int width, int height,bool fullscreen) {
    int f= fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    stat=1;
    statb4=1;
    if (SDL_Init(SDL_INIT_EVERYTHING)==0) {
        window=SDL_CreateWindow(title,x,y,width,height,f);
        if (window) {
            renderer=SDL_CreateRenderer(window,-1,0);
            if (renderer)
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
        }
    }
    mapa = new Mapa("assets/Tiles-Sheet.png",renderer,45,80);
    local = new LocalMap("assets/Desert-Sheet.png",renderer);
    auto& menu(manager.addEntity());
    menu.addComponent<MenuPositionComponent>(0,0,4);
    menu.addComponent<MenuSpriteComponent>("assets/Main-Menu-Sheet.png");
    menu.addComponent<MenuKeyboardController>();
}

void Game::render() {
    SDL_RenderClear(renderer);
    switch (stat) {
        case 1: //user está no menu principal
            manager.draw();
        break;
        case 2: //new game
            mapa->render();
            manager.draw();
        break;
        case 3: //load game
            local->render();
            manager.draw();
        break;
        default :
        break;
    }
    SDL_RenderPresent(renderer);
}

void Game::handleinput() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            stat=0;
        break;
        default:
        break;
    }
}

void Game::update() {
    if (statb4!=stat) {
        statb4=stat;
        if (stat==1) {
            mapa->randomizeMap(60);
            auto& menu(manager.addEntity());
            menu.addComponent<MenuPositionComponent>(0,0,4);
            menu.addComponent<MenuSpriteComponent>("assets/Main-Menu-Sheet.png");
            menu.addComponent<MenuKeyboardController>();
        }
        else if (stat==2) {
            auto& nPlayer(manager.addEntity());
            nPlayer.addComponent<TransformComponent>();
            nPlayer.addComponent<SpriteComponent>("assets/First dude-Sheet.png");
            nPlayer.addComponent<KeyboardController>();
        }
        else if (stat==3) {
            auto& oldPlayer(manager.addEntity());
            oldPlayer.addComponent<TransformComponent>();
            oldPlayer.addComponent<SpriteComponent>("assets/Male 02-2.png");
            oldPlayer.addComponent<KeyboardController>();
        }
        else if (stat==4) {
        }
    }
    manager.refresh();
    manager.update();
}

