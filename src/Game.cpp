#include "../include/Game.hpp"
#include "../include/ECS/Components.hpp"

SDL_Renderer* Game::renderer = nullptr;
Manager Game::manager;
AssetManager * Game::textures;
SDL_Event Game::event;
Vector2D * Game::worldPosition;
Vector2D * Game::localPosition;
int Game::stat=0;
int Game::statb4=0;

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
    localPosition=new Vector2D(24,24);
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
    Vector2D topLeft=*(new Vector2D(0,0)),bottomRight=*(new Vector2D(0,0)),temp=*(new Vector2D(0,0));
    LocalMap *temporary;
    int num=0;
    std::pair<char,int> par;
    topLeft.x=localPosition->x-24;
    topLeft.y=localPosition->y-24;
    bottomRight.x=localPosition->x+25;
    bottomRight.y=localPosition->y+25;
    if (topLeft.x<0 && topLeft.y<0 && worldPosition->x!=0 && worldPosition->y!=0 ) {
        temporary=mapa->getLocalMap(worldPosition->x-1,worldPosition->y-1);
        temp.x=50+topLeft.x;
        temp.y=50+topLeft.y;
    }
    else 
        if (topLeft.x<0 && worldPosition->x!=0) {
            temporary=mapa->getLocalMap(worldPosition->x-1,worldPosition->y);
            temp.x=50+topLeft.x;
            temp.y=50-topLeft.y;
        }
        else 
            if (topLeft.y<0 && worldPosition->y!=0) {
                temporary=mapa->getLocalMap(worldPosition->x,worldPosition->y-1);
                temp.y=50+topLeft.y;
                temp.x=50-topLeft.x;
            }
            else {
                temporary=mapa->getLocalMap(worldPosition->x,worldPosition->y);
                temp.y=50-topLeft.y;
                temp.x=50-topLeft.x;
            }
    for(int i=temp.x;i<50;i++) {
        for (int j=temp.y;j<50;j++) {
            par=temporary->getTile(j,i);
            addTile(i-temp.x,j-temp.y,false,-1,par);
        }
    }
    if (topLeft.x<0 && bottomRight.y>49 && worldPosition->x!=0 && worldPosition->y!=44) {
        temporary=mapa->getLocalMap(worldPosition->x-1,worldPosition->y+1);
        temp.x=50+topLeft.x;
        temp.y=bottomRight.y-50;
    }
    else 
        if (topLeft.x<0 && worldPosition->x!=0) {
            temporary=mapa->getLocalMap(worldPosition->x-1,worldPosition->y);
            temp.x=50+topLeft.x;
            temp.y=50-bottomRight.y;
        }
        else 
            if (bottomRight.y>49 && worldPosition->y!=44) {
                temporary=mapa->getLocalMap(worldPosition->x,worldPosition->y+1);
                temp.y=bottomRight.y-50;
                temp.x=50-topLeft.x;
            }
            else {
                temporary=mapa->getLocalMap(worldPosition->x,worldPosition->y);
                temp.y=50-bottomRight.y;
                temp.x=50-topLeft.x;
            }
    for(int i=temp.x;i<50;i++) {
        for (int j=0;j<temp.y;j++) {
            par=temporary->getTile(j,i);
            addTile(i-temp.x,j+temp.y,false,-1,par);
            num++;
        }
    }
    if (bottomRight.x>49 && topLeft.y<0 && worldPosition->x!=79 && worldPosition->y!=0) {
        temporary=mapa->getLocalMap(worldPosition->x+1,worldPosition->y-1);
        temp.x=bottomRight.x-50;
        temp.y=50+topLeft.y;
    }
    else 
        if (bottomRight.x>49 && worldPosition->x!=79) {
            temporary=mapa->getLocalMap(worldPosition->x+1,worldPosition->y);
            temp.x=bottomRight.x-50;
            temp.y=50-topLeft.y;
        }
        else 
            if (topLeft.y<0 && worldPosition->y!=0) {
                temporary=mapa->getLocalMap(worldPosition->x,worldPosition->y-1);
                temp.y=50+topLeft.y;
                temp.x=50-bottomRight.x;
            }
            else {
                temporary=mapa->getLocalMap(worldPosition->x,worldPosition->y);
                temp.y=50-topLeft.y;
                temp.x=50-bottomRight.x;
            }
    for(int i=0;i<temp.x;i++) {
        for (int j=temp.y;j<50;j++) {
            par=temporary->getTile(j,i);
            addTile(i+temp.x,j-temp.y,false,-1,par);
        }
    }
    if (bottomRight.x>49 && bottomRight.y>49 && worldPosition->x!=79 && worldPosition->y!=45) {
        temporary=mapa->getLocalMap(worldPosition->x+1,worldPosition->y+1);
        temp.x=bottomRight.x-50;
        temp.y=bottomRight.y-50;
    }
    else 
        if (bottomRight.x>49 && worldPosition->x!=79) {
            temporary=mapa->getLocalMap(worldPosition->x+1,worldPosition->y);
            temp.x=bottomRight.x-50;
            temp.y=50-bottomRight.y;
        }
        else 
            if (bottomRight.y>49 && worldPosition->y!=45) {
                temporary=mapa->getLocalMap(worldPosition->x,worldPosition->y+1);
                temp.y=50-bottomRight.y;
                temp.x=bottomRight.x-50;
            }
            else {
                temporary=mapa->getLocalMap(worldPosition->x,worldPosition->y);
                temp.y=50-bottomRight.y;
                temp.x=50-bottomRight.x;
            }
    for(int i=0;i<temp.x;i++) {
        for (int j=0;j<temp.y;j++) {
            par=temporary->getTile(j,i);
            addTile(i+temp.x,j+temp.y,false,-1,par);
        }
    }
}

void Game::refreshLocal() {
    //printf("Local: (%f,%f)\nWorld: (%f,%f)\n",localPosition->x,localPosition->y,worldPosition->x,worldPosition->y);
    if (manager.getGroup(GroupLocalMap).empty()) return;
    SDL_Rect destTL = manager.getGroup(GroupLocalMap).front()->getComponent<TileComponent>().dest;
    SDL_Rect destBR = manager.getGroup(GroupLocalMap).back()->getComponent<TileComponent>().dest;
    //printf("TOP LEFT: (%d,%d)\nBOTTOM RIGHT: (%d,%d)\n",destTL.x,destTL.y,destBR.x,destBR.y);
    if (destTL.x>0 || destTL.y>0 || destBR.x < 1920 || destBR.y < 1080 ) {
        manager.delGroup(GroupLocalMap);
        loadLocal();
        manager.getGroup(GroupPlayers).front()->getComponent<TransformComponent>().position.x=24*16;
        manager.getGroup(GroupPlayers).front()->getComponent<TransformComponent>().position.y=24*16;
    }
}

void Game::addTile(int x,int y,bool mundo, int mos, std::pair<char,int> type) {
    int r,d;
    auto& tile(manager.addEntity());
    if (mundo) {
        r=24;
        d=16;
    }
    else {
        r=16;
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
    printf("sao: %d\n",tilesLocal.size());
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
            initSave("nome");
            auto& nPlayer(manager.addEntity());
            nPlayer.addComponent<TransformComponent>();
            nPlayer.addComponent<SpriteComponent>("bald-dude");
            nPlayer.addComponent<KeyboardController>();
            nPlayer.addGroup(GroupPlayers);
        }
        else if (stat==3) {
            initSave("nome");
            auto& oldPlayer(manager.addEntity());
            oldPlayer.addComponent<TransformComponent>(23*16,23*16);
            oldPlayer.addComponent<SpriteComponent>("hairy-dude");
            oldPlayer.addComponent<KeyboardController>();
            oldPlayer.addGroup(GroupPlayers);
            loadLocal();
        }
        else if (stat==4) {
        }
    }
    refreshLocal();
    manager.refresh();
    manager.update();


    if (!manager.getGroup(GroupPlayers).empty()){
        Vector2D velocity = manager.getGroup(GroupPlayers).front()->getComponent<TransformComponent>().velocity;
        int speed = manager.getGroup(GroupPlayers).front()->getComponent<TransformComponent>().speed;
        for (auto tile : manager.getGroup(GroupLocalMap)) {
            tile->getComponent<TileComponent>().dest.x-=speed*velocity.x;
            tile->getComponent<TileComponent>().dest.y+=speed*velocity.y;
        }
    }
}

