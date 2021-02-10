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

void GameLevelMenu::update() {
    gameData->managerRefresh();
    gameData->managerUpdate();
}