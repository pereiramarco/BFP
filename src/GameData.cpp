#include "../include/GameData.hpp"
#include "../include/ConstantValues.hpp"
#include "../include/ECS/Components.hpp"


SDL_Renderer* GameData::renderer = nullptr;
Manager GameData::manager;
bool GameData::first;
bool GameData::xpadd;
int GameData::stat;
AssetManager * GameData::textures;
SDL_Event GameData::event;
Vector2D * GameData::worldPosition;
Vector2D * GameData::localPosition;
std::map<int,bool> GameData::KEYS;
SDL_Rect GameData::camera = {0,0,(ConstantValues::mapW-1)*ConstantValues::localMapSizeW*ConstantValues::localTileW,(ConstantValues::mapH-1)*ConstantValues::localMapSizeH*ConstantValues::localTileH};


GameData::GameData(const char* title, int x, int y, int width, int height,bool fullscreen) {
    int f= fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    worldPosition=new Vector2D(0,0);
    localPosition=new Vector2D(ConstantValues::playerLocalPosX-1,ConstantValues::playerLocalPosY-1);
    if (SDL_Init(SDL_INIT_EVERYTHING)==0) {
        window=SDL_CreateWindow(title,x,y,width,height,f);
        if (window) {
            renderer=SDL_CreateRenderer(window,-1,0);
            if (renderer)
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
        }
    }
    textures=new AssetManager(&manager);
    textures->addTexture("main-menu","assets/Main-Menu-Sheet.png");
    textures->addTexture("world-tiles","assets/Tiles-Sheet.png");
    textures->addTexture("square","assets/Portrait.png");
    textures->addTexture("hairy-dude","assets/Template-Dude.png");
    textures->addTexture("beach-tiles","assets/Beach-Sheet.png");
    textures->addTexture("water-tiles","assets/Water-Sheet.png");
    textures->addTexture("plains-tiles","assets/Plains-Sheet.png");
    textures->addTexture("desert-tiles","assets/Desert-Sheet.png");
    textures->addTexture("dungeon-tiles","assets/Dungeon-Sheet.png");
    textures->addTexture("wall-tiles","assets/Kingdom-Sheet.png");
    textures->addTexture("FortressV1-tiles","assets/FortressV1-Sheet.png");
    textures->addTexture("BlacksmithV0-tiles","assets/BlacksmithV0-Sheet.png");
    textures->addTexture("BlacksmithV1-tiles","assets/BlacksmithV1-Sheet.png");
    textures->addTexture("MageTowerV0-tiles","assets/MageTowerV0-Sheet.png");
    textures->addTexture("MageTowerV1-tiles","assets/MageTowerV1-Sheet.png");
    textures->addTexture("WitchCabinV0-tiles","assets/WitchCabinV0-Sheet.png");
    textures->addTexture("WitchCabinV1-tiles","assets/WitchCabinV1-Sheet.png");
    textures->addTexture("TavernV0-tiles","assets/TavernV0-Sheet.png");
    textures->addTexture("TavernV1-tiles","assets/TavernV1-Sheet.png");
    textures->addTexture("WellV0-tiles","assets/WellV0-Sheet.png");
    textures->addTexture("ChurchV0-tiles","assets/ChurchV0-Sheet.png");
    textures->addTexture("HouseV0-tiles","assets/HouseV0-Sheet.png");
    textures->addTexture("HouseV1-tiles","assets/HouseV1-Sheet.png");
    textures->addTexture("HouseV2-tiles","assets/HouseV2-Sheet.png");
    textures->addTexture("UIFrame","assets/GeneralUIFrame.png");
    textures->addTexture("HealthBar","assets/HealthBar.png");
    textures->addTexture("ManaBar","assets/ManaBar.png");
    textures->addTexture("StaminaBar","assets/StaminaBar.png");
    textures->addTexture("Numbers","assets/numbers.png");
    textures->addTexture("XPBar","assets/XPBar.png");
    textures->addTexture("Pumpkin-dude","assets/Pumpkin-dude.png");
    textures->addTexture("Skeleton-dude","assets/Skeleton-dude.png");
}

void GameData::initSave(std::string savename) {
    mapa = new Mapa(renderer,ConstantValues::mapH,ConstantValues::mapW);
}

bool GameData::isRunning() {
    return is_running;
}

void GameData::setRunning(bool b) {
    is_running=b;
}

void GameData::addTileWorld(float x,float y,int mos) {
    int r1,r2,d;
    auto& tile(manager.addEntity());
    r1=ConstantValues::worldTileH;
    r2=ConstantValues::worldTileW;
    d=16; //size inside sprite sheet
    tile.addComponent<TileComponent>(x,y,d,d,r2,r1,mos);
    tile.addGroup(GroupWorldMap);
}

bool GameData::isFirst() {
    return first;
}

void GameData::firstF(bool b) {
    first = b;
}

SDL_Event GameData::getEvent() {
    return event;
}

void GameData::setKey(int index,bool value) {
    KEYS[index]=value;
}

Entity& GameData::addEntity() {
    return manager.addEntity();
}

void GameData::delGroup(Group g) {
    manager.delGroup(g);
}

std::vector<Entity*> GameData::getGroup(Group g) {
    return manager.getGroup(g);
}

void GameData::managerRefresh() {
    manager.refresh();
}

void GameData::managerUpdate() {
    manager.update();
}

Vector2D * GameData::getWorldPosition() {
    return worldPosition;
}

void GameData::setWorldPosition(Vector2D * v) {
    worldPosition->x=v->x;
    worldPosition->y=v->y;
}


Vector2D * GameData::getLocalPosition() {
    return localPosition;
}

void GameData::setLocalPosition(Vector2D * v) {
    localPosition->x=v->x;
    localPosition->y=v->y;
}

void GameData::setCamera(SDL_Rect cam) {
    camera=cam;
}

SDL_Rect GameData::getCamera() {
    return camera;
}

void GameData::clearRenderer() {
    SDL_RenderClear(renderer);
}

void GameData::renderPresent() {
    SDL_RenderPresent(renderer);
}


Dungeon* GameData::getDungeon(std::pair<int,int> pos) {
    return mapa->getDungeon(pos);
}
int GameData::getSettlementBuildingV(int x,int y,int type) {
    return mapa->getSettlementBuildingV(x,y,type);
}
LocalMap * GameData::getLocalMap(int x,int y) {
    return mapa->getLocalMap(x,y);
}

