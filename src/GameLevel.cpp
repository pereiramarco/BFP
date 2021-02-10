#include "../include/GameLevel.hpp"
#include "../include/ECS/Components.hpp"
#include "../include/ConstantValues.hpp"
#include "../include/Collision.hpp"
#include "../include/GameData.hpp"
#include <unordered_set>


void GameLevel::handleinput() {
    SDL_Event e = gameData->getEvent();
    SDL_PollEvent(&e);
    switch (e.type) {
        case SDL_QUIT:
            gameData->setRunning(false);
        break;
        case SDL_KEYDOWN:
            gameData->setKey(e.key.keysym.sym,true);
        break;
        case SDL_KEYUP:
            gameData->setKey(e.key.keysym.sym,false);
        break;
    }
}
