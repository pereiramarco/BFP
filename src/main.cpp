#include "../include/game.hpp"
#include "../include/map.hpp"
#include "../include/TextureManager.hpp"

int main() {
    int n;
    Game *g=nullptr;
    g=new Game();
    g->init("Jogo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,960,540,false);
    while (g->stat) {
        g->render();
        g->handleinput();
        g->update();
        cin >> n;
        if (n==1) break;
    }
    SDL_Quit();
}