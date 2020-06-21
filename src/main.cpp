#include "../include/game.hpp"
#include "../include/map.hpp"

int main() {
    int n;
    Game *g=nullptr;
    g=new Game();
    g->init("Jogo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,800,false);
    while (g->isRunning) {
        g->renderMap();
        g->handleinput();
        g->update();
        cin >> n;
        if (n==1) break;
    }
    SDL_Quit();
}