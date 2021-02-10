#include "../include/GameEngine.hpp"
#include "../include/ConstantValues.hpp"

int main() {
    int frametime;
    const int FPS=60;
    const int frameDelay = 1000/FPS;
    Uint32 framestart;
    GameEngine *g=nullptr;
    g=new GameEngine();
    g->init("BFP",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,ConstantValues::screenSizeW,ConstantValues::screenSizeH,true);
    while (g->isRunning()) {
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