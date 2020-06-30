#include "../include/Game.hpp"

int main() {
    int frametime;
    const int FPS=60;
    const int frameDelay = 1000/FPS;
    Uint32 framestart;
    Game *g=nullptr;
    g=new Game();
    g->init("BFP",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1920,1080,true);
    while (Game::stat) {
        framestart=SDL_GetTicks();
        g->render();
        g->handleinput();
        g->update();
        frametime=SDL_GetTicks()-framestart;
        if (frameDelay>frametime) {
            SDL_Delay(frameDelay-frametime);
        }
    }
    SDL_Quit();
}