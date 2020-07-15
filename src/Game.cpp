#include "../include/Game.hpp"
#include "../include/ECS/Components.hpp"

SDL_Renderer* Game::renderer = nullptr;
Manager Game::manager;
Mapa * Game::mapa;
AssetManager * Game::textures;
SDL_Event Game::event;
Vector2D * Game::worldPosition;
Vector2D * Game::localPosition;
int Game::stat=0;
int Game::statb4=0;
static int first=0;
static int loaded=0;

enum groupLabels : std::size_t {
    GroupWorldMap,
    GroupLocalMap,
    GroupPlayers,
    GroupEnemies,
    GroupMenus
};

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int x, int y, int width, int height,bool fullscreen) {
    int f= fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    stat=1;
    statb4=1;
    worldPosition=new Vector2D(20,20);
    localPosition=new Vector2D(14,7.4375);
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
    textures->addTexture("bald-dude","assets/First dude-Sheet.png");
    textures->addTexture("hairy-dude","assets/Male 02-2.png");
    textures->addTexture("beach-tiles","assets/Beach-Sheet.png");
    textures->addTexture("water-tiles","assets/Desert-Sheet.png");
    textures->addTexture("plains-tiles","assets/Plains-Sheet.png");
    textures->addTexture("desert-tiles","assets/Desert-Sheet.png");
    auto& menu(manager.addEntity());
    menu.addGroup(GroupMenus);
    menu.addComponent<MenuPositionComponent>(0,0,4);
    menu.addComponent<MenuSpriteComponent>("main-menu");
    menu.addComponent<MenuKeyboardController>();
}

void Game::initSave(std::string savename) {
    int i,j,k,l;
    mapa = new Mapa(renderer,45,80);
    /*
    std::ofstream saveFile (savename);
    for (i=0;i<45;i++) {
        for (j=0;j<80;j++) {
            saveFile<<std::to_string(mapa->getTile(i,j));
            if (j!=79) saveFile<<",";
            else saveFile<<"\n";
        }
    }
    saveFile<<"\n";
    for (i=0;i<45;i++) {
        for (j=0;j<80;j++) {
            for (k=0;k<50;k++) {
                for (l=0;l<50;l++) {
                    std::pair<char,int> pair=mapa->getLocalMapTile(i,j,k,l);
                    saveFile<<pair.first<<"-"<<pair.second;
                    if (l!=49) saveFile<<"|";
                }
                saveFile<<"\n";
            }
            saveFile<<"\n";
        }
        saveFile<<"\n";
    }
    */
}

void Game::loadLocal() {
    manager.delGroup(GroupLocalMap);
    int r,d;
    LocalMap *temporary;
    for (int k=0;k<9;k++) {
        switch (k) {
            case 0:
                r=-50;
                d=-50;
                temporary = mapa->getLocalMap(worldPosition->x-1,worldPosition->y-1);
            break;
            case 1:
                r=0;
                d=-50;
                temporary = mapa->getLocalMap(worldPosition->x-1,worldPosition->y);
            break;
            case 2:
                r=50;
                d=-50;
                temporary = mapa->getLocalMap(worldPosition->x-1,worldPosition->y+1);
            break;
            case 3:
                r=-50;
                d=0;
                temporary = mapa->getLocalMap(worldPosition->x,worldPosition->y-1);
            break;
            case 4:
                r=0;
                d=0;
                temporary = mapa->getLocalMap(worldPosition->x,worldPosition->y);
            break;
            case 5:
                r=50;
                d=0;
                temporary = mapa->getLocalMap(worldPosition->x,worldPosition->y+1);
            break;
            case 6:
                r=-50;
                d=50;
                temporary = mapa->getLocalMap(worldPosition->x+1,worldPosition->y-1);
            break;
            case 7:
                r=0;
                d=50;
                temporary = mapa->getLocalMap(worldPosition->x+1,worldPosition->y);
            break;
            case 8:
                r=50;
                d=50;
                temporary = mapa->getLocalMap(worldPosition->x+1,worldPosition->y+1);
            break;
        }
        for (int i=0;i<50;i++ ) {
            for (int j=0;j<50;j++) {
                addTile(i-localPosition->y+7.4375+r,j-localPosition->x+14+d,false,-1,temporary->getTile(i,j));
            }
        }
    }
}

void Game::addTile(float x,float y,bool mundo, int mos, std::pair<char,int> type) {
    int r,d;
    auto& tile(manager.addEntity());
    if (mundo) {
        r=24;
        d=16;
    }
    else {
        r=64;
        d=32;
    }
    tile.addComponent<TileComponent>(x,y,d,d,r,r,mundo,mos,type);
    if (mundo) 
        tile.addGroup(GroupWorldMap);
    else 
        tile.addGroup(GroupLocalMap);
}

void Game::render() {
    auto tilesWorld = manager.getGroup(GroupWorldMap);
    auto tilesLocal = manager.getGroup(GroupLocalMap);
    auto players = manager.getGroup(GroupPlayers);
    auto enemies = manager.getGroup(GroupEnemies);
    auto menus = manager.getGroup(GroupMenus);
    SDL_RenderClear(renderer);
    for (auto& i : menus) {
        i->draw();
    }
    for (auto& i : tilesWorld) {
        i->draw();
    }
    for (auto& i : tilesLocal) {
        i->draw();
    }
    for (auto& i : players) {
        i->draw();
    }
    for (auto& i : enemies) {
        i->draw();
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
            auto& menu(manager.addEntity());
            menu.addGroup(GroupMenus);
            menu.addComponent<MenuPositionComponent>(0,0,4);
            menu.addComponent<MenuSpriteComponent>("main-menu");
            menu.addComponent<MenuKeyboardController>();
        }
        else if (stat==2) {
            auto& nPlayer(manager.addEntity());
            nPlayer.addComponent<TransformComponent>();
            nPlayer.addComponent<SpriteComponent>("bald-dude");
            nPlayer.addComponent<KeyboardController>();
            SDL_Rect r; r.w=24;r.h=24; 
            nPlayer.getComponent<SpriteComponent>().setDest(r);
            nPlayer.getComponent<TransformComponent>().position.x=worldPosition->x*24;
            nPlayer.getComponent<TransformComponent>().position.y=worldPosition->y*24;
            nPlayer.addGroup(GroupPlayers);
        }
        else if (stat==3) {
            if (first==0) initSave("nome");
            first=1;
            auto& oldPlayer(manager.addEntity());
            oldPlayer.addComponent<TransformComponent>();
            oldPlayer.addComponent<SpriteComponent>("hairy-dude");
            oldPlayer.addComponent<KeyboardController>();
            oldPlayer.addGroup(GroupPlayers);
            loadLocal();
        }
        else if (stat==4) {
        }
    }
    manager.refresh();
    manager.update();
    //printf("Local: (%f,%f)\nWorld: (%f,%f)\n",Game::localPosition->x,Game::localPosition->y,Game::worldPosition->x,Game::worldPosition->y);
    if (!manager.getGroup(GroupPlayers).empty()){
        Vector2D velocity = manager.getGroup(GroupPlayers).front()->getComponent<TransformComponent>().velocity;
        int speed = manager.getGroup(GroupPlayers).front()->getComponent<TransformComponent>().speed;
        for (auto& tile : manager.getGroup(GroupLocalMap)) {
            tile->getComponent<TransformComponent>().position.x-=speed*velocity.x;
            tile->getComponent<TransformComponent>().position.y-=speed*velocity.y;
        }
    }
}

