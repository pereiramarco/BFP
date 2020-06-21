#include "../include/test.hpp"

int main() {
    Game *g=nullptr;
    g=new Game();
    g->init("Jogo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,800,false);
    while (g->isRunning) {
        g->renderMap();
        g->handleinput();
        g->update();
        if (getchar()=='\n') break;
    }
}