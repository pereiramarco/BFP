#include "../include/GameLevelMenu.hpp"
#include "../include/ECS/Components.hpp"
#include "../include/ConstantValues.hpp"

GameLevelMenu::GameLevelMenu(GameData* gameDataG) {
    gameData=gameDataG;
    gameData->delGroup(GroupUI); //deletes the UI
    gameData->delGroup(GroupEnemies); //apaga os inimigos
    auto& menu(gameData->addEntity());
    menu.addGroup(GroupMenus);
    menu.addComponent<MenuPositionComponent>(0,0,4);
    menu.addComponent<MenuSpriteComponent>("main-menu");
    menu.addComponent<MenuKeyboardController>();
}

void GameLevelMenu::render() {
    gameData->clearRenderer();
    auto menus = gameData->getGroup(GroupMenus);
    for (auto& i : menus) {
        i->draw();
    }
    gameData->renderPresent();
}

void GameLevelMenu::handleinput() {
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

void GameLevelMenu::update() {
    gameData->managerRefresh();
    gameData->managerUpdate();
}