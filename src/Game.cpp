#include "../include/Game.hpp"
#include "../include/ECS/Components.hpp"
#include "../include/ConstantValues.hpp"

SDL_Renderer* Game::renderer = nullptr;
Entity* player = nullptr;
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
SDL_Rect Game::camera = {0,0,ConstantValues::mapH*ConstantValues::localMapSizeH*ConstantValues::localTileH,ConstantValues::mapW*ConstantValues::localMapSizeW*ConstantValues::localTileW};

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
    textures->addTexture("bald-dude","assets/First dude-Sheet.png");
    textures->addTexture("hairy-dude","assets/Male 02-2.png");
    textures->addTexture("beach-tiles","assets/Beach-Sheet.png");
    textures->addTexture("water-tiles","assets/Water-Sheet.png");
    textures->addTexture("plains-tiles","assets/Plains-Sheet.png");
    textures->addTexture("desert-tiles","assets/Desert-Sheet.png");
    textures->addTexture("dungeon-tiles","assets/Dungeon-Sheet.png");
    auto& menu(manager.addEntity());
    menu.addGroup(GroupMenus);
    menu.addComponent<MenuPositionComponent>(0,0,4);
    menu.addComponent<MenuSpriteComponent>("main-menu");
    menu.addComponent<MenuKeyboardController>();
}

void Game::initSave(std::string savename) {
    //int i,j,k,l;
    mapa = new Mapa(renderer,ConstantValues::mapH,ConstantValues::mapW);
    /*
    std::ofstream saveFile (savename);
    for (i=0;i<45;i++) {
        for (j=0;j<80;j++) {
            saveFile<<std::to_string(mapa->getTile(i,j));
            if (j!=Constantvalues) saveFile<<",";
            else saveFile<<"\n";
        }
    }
    saveFile<<"\n";
    for (i=0;i<45;i++) {
        for (j=0;j<80;j++) {
            for (k=0;k<ConstantValues::localMapSizeW;k++) {
                for (l=0;l<ConstantValues::localMapSizeW;l++) {
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
    int r,d,i,ii,j,jj,maxI,maxJ;
    LocalMap *temporary;
    //printf("WorldPosition:\nX = %f\nY = %f\n",worldPosition->x,worldPosition->y);
    for (int k=0;k<9;k++) {
        ii=0;jj=0;maxI=ConstantValues::localMapSizeH;maxJ=ConstantValues::localMapSizeW;
        temporary=NULL;
        switch (k) {
            case 0:
                if (worldPosition->x<=0 || worldPosition->y<=0) break;
                //puts("loading top left");
                ii=35;
                jj=35;
                r=worldPosition->x-1;
                d=worldPosition->y-1;
                temporary = mapa->getLocalMap(worldPosition->x-1,worldPosition->y-1);
            break;
            case 1:
                if (worldPosition->x<=0) break;
                //puts("loading top center");
                jj=35;
                r=worldPosition->x-1;
                d=worldPosition->y;
                temporary = mapa->getLocalMap(worldPosition->x-1,worldPosition->y);
            break;
            case 2:
                if (worldPosition->x<=0 || worldPosition->y>=ConstantValues::mapW-1) break;
                //puts("loading top right");
                maxI=16;
                jj=35;
                r=worldPosition->x-1;
                d=worldPosition->y+1;
                temporary = mapa->getLocalMap(worldPosition->x-1,worldPosition->y+1);
            break;
            case 3:
                if (worldPosition->y<=0) break;
                //puts("loading center left");
                ii=35;
                r=worldPosition->x;
                d=worldPosition->y-1;
                temporary = mapa->getLocalMap(worldPosition->x,worldPosition->y-1);
            break;
            case 4:
                //puts("loading center");
                r=worldPosition->x;
                d=worldPosition->y;
                temporary = mapa->getLocalMap(worldPosition->x,worldPosition->y);
            break;
            case 5:
                if (worldPosition->y>=ConstantValues::mapW-1) break;
                //puts("loading center right");
                maxI=15;
                r=worldPosition->x;
                d=worldPosition->y+1;
                temporary = mapa->getLocalMap(worldPosition->x,worldPosition->y+1);
            break;
            case 6:
                if (worldPosition->x>=ConstantValues::mapH-1 || worldPosition->y<=0) break;
                //puts("loading bottom left");
                ii=35;
                maxJ=16;
                r=worldPosition->x+1;
                d=worldPosition->y-1;
                temporary = mapa->getLocalMap(worldPosition->x+1,worldPosition->y-1);
            break;
            case 7:
                if (worldPosition->x>=ConstantValues::mapH-1) break;
                //puts("loading bottom center");
                maxJ=16;
                r=worldPosition->x+1;
                d=worldPosition->y;
                temporary = mapa->getLocalMap(worldPosition->x+1,worldPosition->y);
            break;
            case 8:
                if (worldPosition->x>=ConstantValues::mapH-1 || worldPosition->y>=ConstantValues::mapW-1) break;
                //puts("loading bottom right");
                maxI=15;
                maxJ=16;
                r=worldPosition->x+1;
                d=worldPosition->y+1;
                temporary = mapa->getLocalMap(worldPosition->x+1,worldPosition->y+1);
            break;
        }
        if (temporary) {
            for (i=ii;i<maxI;i++) {
                for (j=jj;j<maxJ;j++) {
                    addTile(i+ConstantValues::localMapSizeH*d,j+ConstantValues::localMapSizeW*r,false,-1,temporary->getTile(i,j));
                }
            }
        }
    }
}

void Game::updateCamAndPos() {
    float s=player->getComponent<TransformComponent>().speed;
    Vector2D v = player->getComponent<TransformComponent>().velocity;
    if (Game::stat==3) {
        localPosition->x+=s*v.x/ConstantValues::localTileW;
        localPosition->y+=s*v.y/ConstantValues::localTileH;
        
        if (localPosition->x>ConstantValues::localMapSizeW)  {
            if (worldPosition->x<ConstantValues::mapW-1)
            {
                worldPosition->x+=1;
                localPosition->x-=ConstantValues::localMapSizeW;
                loadLocal();
            }
            else localPosition->x=ConstantValues::localMapSizeW;
        }
        if (localPosition->y>ConstantValues::localMapSizeH)  {
            if (worldPosition->y<ConstantValues::mapH-1) {
                worldPosition->y+=1;
                localPosition->y-=ConstantValues::localMapSizeH;
                loadLocal();
            }
            else localPosition->y=ConstantValues::localMapSizeW;
        }
        if (localPosition->x<0)  {
            if (worldPosition->x>0) {
                worldPosition->x-=1;
                localPosition->x+=ConstantValues::localMapSizeW;
                loadLocal();
            }
            else localPosition->x=0;
        }
        if (localPosition->y<0)  {
            if (worldPosition->y>0) {
                worldPosition->y-=1;
                localPosition->y+=ConstantValues::localMapSizeH;
                loadLocal();
            }
            else localPosition->y=0;
        }
        camera.x=player->getComponent<TransformComponent>().position.x-ConstantValues::screenSizeW/2;
        camera.y=player->getComponent<TransformComponent>().position.y-ConstantValues::screenSizeH/2;
        if (camera.x<0)
            camera.x=0;
        if (camera.x>camera.w) 
            camera.x=camera.w;
        if (camera.y<0)
            camera.y=0;
        if (camera.y>camera.h) 
            camera.y=camera.h;
    }
    else {
        worldPosition->x+=(int) s * v.x/24;
        worldPosition->y+=(int) s * v.y/24;
    }
}

void Game::addTile(float x,float y,bool mundo, int mos, std::pair<char,int> type) {
    int r1,r2,d;
    auto& tile(manager.addEntity());
    if (mundo) {
        r1=r2=24;
        d=16;
    }
    else {
        r1=ConstantValues::localTileW;
        r2=ConstantValues::localTileH;
        d=32;
    }
    tile.addComponent<TileComponent>(x,y,d,d,r2,r1,mundo,mos,type);
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
    //printf("Local: (%f,%f)\nWorld: (%f,%f)\n",Game::localPosition->x,Game::localPosition->y,Game::worldPosition->x,Game::worldPosition->y);
    if (statb4!=stat) {
        statb4=stat;
        if (stat==1) {
            auto& menu(manager.addEntity());
            menu.addGroup(GroupMenus);
            menu.addComponent<MenuPositionComponent>(0,0,4);
            menu.addComponent<MenuSpriteComponent>("main-menu");
            menu.addComponent<MenuKeyboardController>();
            player=NULL;
        }
        else if (stat==2) {
            if (first==0) {
                initSave("nome");
                first=1;
            }
            auto& nPlayer(manager.addEntity());
            nPlayer.addComponent<TransformComponent>();
            nPlayer.addComponent<SpriteComponent>("bald-dude");
            nPlayer.addComponent<KeyboardController>();
            SDL_Rect r; r.w=24;r.h=24; 
            nPlayer.getComponent<SpriteComponent>().setDest(r);
            nPlayer.getComponent<TransformComponent>().position.x=worldPosition->x*24;
            nPlayer.getComponent<TransformComponent>().position.y=worldPosition->y*24;
            nPlayer.addGroup(GroupPlayers);
            player = &nPlayer;
        }
        else if (stat==3) {
            auto& oldPlayer(manager.addEntity());
            oldPlayer.addComponent<TransformComponent>();
            oldPlayer.addComponent<SpriteComponent>("hairy-dude");
            oldPlayer.addComponent<KeyboardController>();
            oldPlayer.addGroup(GroupPlayers);
            player = &oldPlayer;
            loadLocal();
        }
        else if (stat==4) {
        }
    }
    if (player) updateCamAndPos();
    manager.refresh();
    manager.update();
}

