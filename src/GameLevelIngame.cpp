#include "../include/GameLevelIngame.hpp"
#include "../include/ECS/Components.hpp"
#include "../include/ConstantValues.hpp"
#include "../include/Collision.hpp"
#include <unordered_set>

GameLevelIngame::GameLevelIngame(GameData* gameDataG) {
    SDL_Rect camera = {0,0,(ConstantValues::mapW-1)*ConstantValues::localMapSizeW*ConstantValues::localTileW,(ConstantValues::mapH-1)*ConstantValues::localMapSizeH*ConstantValues::localTileH};
    gameData=gameDataG;
    gameData->setCamera(camera);
    gameData->setLocalPosition(new Vector2D(ConstantValues::playerLocalPosX-1,ConstantValues::playerLocalPosY-1));
    Vector2D * worldPosition = gameData->getWorldPosition();
    interact=false;
    //printf("WorldPosition x: %f y:%f\nLocalPosition x: %f y:%f\nCamera x:%d y:%d\n",worldPosition->x,worldPosition->y,Game::localPosition->x,Game::localPosition->y,camera.x,camera.y);
    auto& oldPlayer(gameData->addEntity());
    oldPlayer.addComponent<TransformComponent>();
    oldPlayer.addComponent<SpriteComponent>("hairy-dude",true);
    oldPlayer.getComponent<SpriteComponent>().addStandardAnimations();
    oldPlayer.addComponent<OverlapComponent>(64,50);
    oldPlayer.addComponent<ColliderComponent>(17,50,30,14,"player");
    oldPlayer.addComponent<AttributesComponent>(100,100,100,100,100,100,100,0,0,-0.3);
    oldPlayer.addComponent<KeyboardController>();
    oldPlayer.getComponent<TransformComponent>().position.x=((int)worldPosition->x)*ConstantValues::localMapSizeW*ConstantValues::localTileW+ConstantValues::screenSizeW/2;
    oldPlayer.getComponent<TransformComponent>().position.y=((int)worldPosition->y)*ConstantValues::localMapSizeH*ConstantValues::localTileH+ConstantValues::screenSizeH/2;
    oldPlayer.addGroup(GroupPlayers);
    player = &oldPlayer;

    auto& dog(gameData->addEntity());
    dog.addComponent<TransformComponent>();
    dog.getComponent<TransformComponent>().setSpeed(2);
    dog.addComponent<SpriteComponent>("Doggo",true);
    dog.getComponent<SpriteComponent>().addStandardAnimations();
    dog.addComponent<OverlapComponent>(64,50);
    dog.addComponent<ColliderComponent>(17,50,30,14,"doggo");
    dog.getComponent<TransformComponent>().position.x=((int)worldPosition->x)*ConstantValues::localMapSizeW*ConstantValues::localTileW+ConstantValues::screenSizeW/2;
    dog.getComponent<TransformComponent>().position.y=((int)worldPosition->y)*ConstantValues::localMapSizeH*ConstantValues::localTileH+ConstantValues::screenSizeH/2;
    dog.addComponent<WanderAroundComponent>(100);
    dog.addGroup(GroupEnemies);
    
    auto& monster(gameData->addEntity());
    monster.addComponent<TransformComponent>();
    monster.getComponent<TransformComponent>().setSpeed(8);
    monster.addComponent<SpriteComponent>("Pumpkin-dude",true);
    monster.getComponent<SpriteComponent>().addStandardAnimations();
    monster.addComponent<OverlapComponent>(64,50);
    monster.addComponent<ColliderComponent>(17,50,30,14,"player");
    monster.addComponent<AttributesComponent>(100,100,100,100,100,100,100,0,0,-0.3);
    monster.getComponent<TransformComponent>().position.x=((int)worldPosition->x)*ConstantValues::localMapSizeW*ConstantValues::localTileW+ConstantValues::screenSizeW/2;
    monster.getComponent<TransformComponent>().position.y=((int)worldPosition->y)*ConstantValues::localMapSizeH*ConstantValues::localTileH+ConstantValues::screenSizeH/2;
    monster.addComponent<FollowPlayerComponent>(&player->getComponent<TransformComponent>(),1,1);
    monster.addGroup(GroupEnemies);
    auto& monster2(gameData->addEntity());
    monster2.addComponent<TransformComponent>();
    monster2.getComponent<TransformComponent>().setSpeed(8);
    monster2.addComponent<SpriteComponent>("Skeleton-dude",true);
    monster2.getComponent<SpriteComponent>().addStandardAnimations();
    monster2.addComponent<OverlapComponent>(64,50);
    monster2.addComponent<ColliderComponent>(17,50,30,14,"player");
    monster2.addComponent<AttributesComponent>(100,100,100,100,100,100,100,0,0,-0.3);
    monster2.getComponent<TransformComponent>().position.x=((int)worldPosition->x)*ConstantValues::localMapSizeW*ConstantValues::localTileW+ConstantValues::screenSizeW/2;
    monster2.getComponent<TransformComponent>().position.y=((int)worldPosition->y)*ConstantValues::localMapSizeH*ConstantValues::localTileH+ConstantValues::screenSizeH/2;
    monster2.addComponent<FollowPlayerComponent>(&player->getComponent<TransformComponent>(),-1,4);
    monster2.addGroup(GroupEnemies);

    loadLocal();
    initUI();
}

void GameLevelIngame::render() {
    auto tilesLocal = gameData->getGroup(GroupLocalMap);
    auto players = gameData->getGroup(GroupPlayers);
    auto enemies = gameData->getGroup(GroupEnemies);
    auto colliders = gameData->getGroup(GroupCollider);
    auto ui = gameData->getGroup(GroupUI);
    gameData->clearRenderer();
    for (auto& i : tilesLocal) {
        i->draw();
    }
    for (auto& i : overlap) {
        i->draw();
    }
    for (auto& i : enemies) {
        if (!overlap.count(i))
            i->draw();
    }
    for (auto& i : players) {
        if (!overlap.count(i))
            i->draw();
    }
    for (auto&i : colliders) {
        if (!overlap.count(i))
            i->draw();
    }
    for (auto&i : ui) {
        i->draw();
    }
    gameData->renderPresent();
}

void GameLevelIngame::handleinput() {
    SDL_Event event = gameData->getEvent();
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: 
                        GameEngine::change=1;
                    break;
                    case SDLK_e: 
                        interact=true;
                    break;
                }
                gameData->setKey(event.key.keysym.sym,true);
            break;
            case SDL_KEYUP:
                gameData->setKey(event.key.keysym.sym,false);
            break;
        }
    }
}


void GameLevelIngame::initUI() {

    SDL_Rect r1,r2;
    auto& HealthBar(gameData->addEntity());
    r1.x=0;
    r1.y=0;
    r1.w=160;
    r1.h=16;
    r2.x=ConstantValues::UIFRAMEx+57*2;//POSX
    r2.y=ConstantValues::UIFRAMEy;//POSY
    r2.w=2*160;
    r2.h=2*16;
    HealthBar.addComponent<SpriteComponent>("HealthBar",false,r1,r2);
    HealthBar.addGroup(GroupUI);
    auto& ManaBar(gameData->addEntity());
    r1.w=160;
    r1.h=16;
    r2.x=ConstantValues::UIFRAMEx+62*2;//POSX
    r2.y=ConstantValues::UIFRAMEy+16*2;//POSY
    r2.w=2*160;
    r2.h=2*16;
    ManaBar.addComponent<SpriteComponent>("ManaBar",false,r1,r2);
    ManaBar.addGroup(GroupUI);
    auto& StaminaBar(gameData->addEntity());
    r1.w=160;
    r1.h=16;
    r2.x=ConstantValues::UIFRAMEx+59*2;//POSX
    r2.y=ConstantValues::UIFRAMEy+32*2;//POSY
    r2.w=2*160;
    r2.h=2*16;
    StaminaBar.addComponent<SpriteComponent>("StaminaBar",false,r1,r2);
    StaminaBar.addGroup(GroupUI);

    auto& LevelProgressTopRight(gameData->addEntity());
    r1.x=32;
    r1.y=0;
    r1.w=31;
    r1.h=31;
    r2.x=ConstantValues::UIFRAMEx+32*2;
    r2.y=ConstantValues::UIFRAMEy;
    r2.w=31*2;
    r2.h=31*2;
    LevelProgressTopRight.addComponent<SpriteComponent>("XPBar",false,r1,r2);
    LevelProgressTopRight.addGroup(GroupUI);

    auto& LevelProgressBottomRight(gameData->addEntity());
    r1.x=32;
    r1.y=32;
    r1.w=31;
    r1.h=31;
    r2.x=ConstantValues::UIFRAMEx+32*2;
    r2.y=ConstantValues::UIFRAMEy+32*2;
    r2.w=31*2;
    r2.h=31*2;
    LevelProgressBottomRight.addComponent<SpriteComponent>("XPBar",false,r1,r2);
    LevelProgressBottomRight.addGroup(GroupUI);

    auto& LevelProgressBottomLeft(gameData->addEntity());
    r1.x=0;
    r1.y=32;
    r1.w=31;
    r1.h=31;
    r2.x=ConstantValues::UIFRAMEx;
    r2.y=ConstantValues::UIFRAMEy+32*2;
    r2.w=31*2;
    r2.h=31*2;
    LevelProgressBottomLeft.addComponent<SpriteComponent>("XPBar",false,r1,r2);
    LevelProgressBottomLeft.addGroup(GroupUI);

    auto& LevelProgressTopLeft(gameData->addEntity());
    r1.x=0;
    r1.y=0;
    r1.w=31;
    r1.h=31;
    r2.x=ConstantValues::UIFRAMEx;
    r2.y=ConstantValues::UIFRAMEy;
    r2.w=31*2;
    r2.h=31*2;
    LevelProgressTopLeft.addComponent<SpriteComponent>("XPBar",false,r1,r2);
    LevelProgressTopLeft.addGroup(GroupUI);

    auto& UIFrame(gameData->addEntity());
    r1.w=224;
    r1.h=64;
    r2.x=ConstantValues::UIFRAMEx;//POSX
    r2.y=ConstantValues::UIFRAMEy;//POSY
    r2.w=2*224;
    r2.h=2*64;
    UIFrame.addComponent<SpriteComponent>("UIFrame",false,r1,r2);
    UIFrame.addGroup(GroupUI);

    auto& LevelDigitOne(gameData->addEntity());
    r1.w=16;
    r1.h=16;
    r2.x=ConstantValues::UIFRAMEx+6*2;
    r2.y=ConstantValues::UIFRAMEy+26*2;
    r2.w=32;
    r2.h=32;
    LevelDigitOne.addComponent<SpriteComponent>("Numbers",false,r1,r2);
    LevelDigitOne.addGroup(GroupUI);
    
    auto& LevelDigitTwo(gameData->addEntity());
    r2.x=ConstantValues::UIFRAMEx+22*2;
    LevelDigitTwo.addComponent<SpriteComponent>("Numbers",false,r1,r2);
    LevelDigitTwo.addGroup(GroupUI);

    auto& LevelDigitThree(gameData->addEntity());
    r2.x=ConstantValues::UIFRAMEx+38*2;
    LevelDigitThree.addComponent<SpriteComponent>("Numbers",false,r1,r2);
    LevelDigitThree.addGroup(GroupUI);
}

void GameLevelIngame::addTileInside(float x,float y,int mos) {
    int r1,r2,d;
    auto& tile(gameData->addEntity());
    r1=ConstantValues::localTileW;
    r2=ConstantValues::localTileH;
    d=32; //size inside sprite sheet
    if (mos>3 && mos!=20) {
        if (mos>9) mos--;
        auto& tileO(gameData->addEntity());
        tileO.addComponent<TileComponent>(x,y,d,d,r2,r1,false,mos);
        switch (mos) {
            case 6:
                tileO.addComponent<ColliderComponent>(29,16,35,48,"bottom right corner");
            break;
            case 5:
                tileO.addComponent<ColliderComponent>(0,16,35,48,"bottom left corner");
            break;
            case 8:
                tileO.addComponent<ColliderComponent>(0,48,64,16,"wall horizontal");
            break;
            case 4:
            case 12:
                tileO.addComponent<ColliderComponent>(48,0,16,64,"wall right");
            break;
            case 7:
            case 11:
                tileO.addComponent<ColliderComponent>(0,0,16,64,"wall left");
            break;
            case 10:
                tileO.addComponent<ColliderComponent>(48,48,16,16,"bottom right corner");
            break;
            case 9:
                tileO.addComponent<ColliderComponent>(0,48,16,16,"bottom left corner");
            break;
            case 13:
                tileO.addComponent<ColliderComponent>(0,0,60,50,"chest");
            break;
            case 14:
            case 15:
                tileO.addComponent<ColliderComponent>(0,0,60,64,"object");
            break;
        }
        tileO.addGroup(GroupCollider);
        mos=0;
    }
    if (mos==20) mos=ROOMSTART-1;
    tile.addComponent<TileComponent>(x,y,d,d,r2,r1,false,mos);
    if (mos && mos!=ROOMSTART-1) {
        tile.addComponent<ColliderComponent>(0,0,64,64,"wall top");
        tile.addGroup(GroupCollider);
    }
    else
        tile.addGroup(GroupLocalMap);
}

void GameLevelIngame::loadDungeon() {
    int i,j;
    gameData->delGroup(GroupLocalMap);
    gameData->delGroup(GroupCollider);
    Vector2D * worldPosition = gameData->getWorldPosition();
    std::pair<int,int> p(worldPosition->y,worldPosition->x);
    Dungeon * d = gameData->getDungeon(p);
    for (i=0;i<80;i++) {
        for (j=0;j<120;j++) {
            int x=d->getTile(i,j);
            addTileInside(i,j,x);
        }       
    }
}

void GameLevelIngame::updateCollision(Entity * ent,int typeOfEnt,Vector2D lastPosition,Vector2D localPos,Vector2D worldPos) {
    int retry=0;
    auto colliders = gameData->getGroup(GroupCollider);
    Vector2D entP = ent->getComponent<TransformComponent>().position.copy(),localPosB = gameData->getLocalPosition()->copy(),worldPosB = gameData->getWorldPosition()->copy();
    SDL_Rect entR = ent->getComponent<ColliderComponent>().getRect();
    ColliderComponent cx = ent->getComponent<ColliderComponent>().copy();
    ColliderComponent cy = cx.copy();
    Vector2D oH = cx.getOverhead();
    Vector2D ladoX = Vector2D(entP.x,lastPosition.y);
    cx.setXY(ladoX.copy().operator+=(oH));
    Vector2D ladoY = Vector2D(lastPosition.x,entP.y);
    cy.setXY(ladoY.copy().operator+=(oH));
    for (long unsigned int i=0;retry<3 && i<colliders.size();i++) {
        Entity* col=colliders[i];
        if (!col->hasComponent<ColliderComponent>()) continue;
        SDL_Rect collC=col->getComponent<ColliderComponent>().getRect();
        if (Collision::AABB(entR,collC)) {
            i=0;
            if (!retry) {
                ent->getComponent<TransformComponent>().position=ladoX;
            }
            else 
                if (retry==1) {
                    ent->getComponent<TransformComponent>().position=ladoY;
                }
                else ent->getComponent<TransformComponent>().position=lastPosition;
            ent->getComponent<ColliderComponent>().update();
            entR=ent->getComponent<ColliderComponent>().getRect();
            retry++;
        }
    }
    if (typeOfEnt==1) {
        switch (retry) {
            case 1:
                gameData->setLocalPosition(new Vector2D (localPosB.x,localPos.y));
                gameData->setWorldPosition(new Vector2D(worldPosB.x,worldPos.y));
            break;
            case 2:
                gameData->setLocalPosition(new Vector2D (localPos.x,localPosB.y));
                gameData->setWorldPosition(new Vector2D(worldPos.x,worldPosB.y));
            break;
            case 3:
                gameData->setLocalPosition(&localPos);
                gameData->setWorldPosition(&worldPos);
            break;
        }
    }
}

void GameLevelIngame::updateCollisions(Vector2D playerpos,Vector2D localPos,Vector2D worldPos,std::map<Entity*,Vector2D> enemiesPos) {
    updateCollision(player,1,playerpos,localPos,worldPos);
    auto enemies = gameData->getGroup(GroupEnemies);
    for (auto& enem : enemies) {
        updateCollision(enem,0,enemiesPos[enem],Vector2D(),Vector2D());
    }
}

void GameLevelIngame::updateOverlaps() {
    bool b=false;
    overlap.clear();
    auto colliders = gameData->getGroup(GroupCollider);
    auto enemies = gameData->getGroup(GroupEnemies);
    SDL_Rect playerO = player->getComponent<OverlapComponent>().getRect();
    SDL_Rect playerC = player->getComponent<ColliderComponent>().getRect();
    for (auto& enem : enemies) {
        SDL_Rect enemyO = enem->getComponent<OverlapComponent>().getRect();
        SDL_Rect enemyC = enem->getComponent<ColliderComponent>().getRect();
        if (!b && Collision::AABB(enemyO,playerC)) {
            overlap.insert(player);
            b=true;
        }
        if (Collision::AABB(playerO,enemyC)) {
            overlap.insert(enem);
        }
    }
    b=false;
    for (auto& i : colliders) {
        if (!i->hasComponent<ColliderComponent>()) continue;
        SDL_Rect collC = i->getComponent<ColliderComponent>().getRect();
        if (Collision::AABB(playerO,collC)) {
            overlap.insert(i);
        }
        else
            for (auto& enem : enemies) {
                SDL_Rect enemyO = enem->getComponent<OverlapComponent>().getRect();
                if (Collision::AABB(enemyO,collC)) {
                    overlap.insert(i);
                    break;
                }
            }
    }
}

void GameLevelIngame::checkInteractions() {
    if (interact) {
        Vector2D* worldPosition=gameData->getWorldPosition();
        Vector2D* localPosition = gameData->getLocalPosition();
        SDL_Rect camera;
        std::pair<int,int> p(worldPosition->y,worldPosition->x);
        Dungeon * d = gameData->getDungeon(p);
        std::pair<int,int> pair=d->getEntrance();
        Vector2D playerpos=player->getComponent<TransformComponent>().position;
        if (!inside) {
            if (d && localPosition->x>23.5 && localPosition->x<24.5 && (int)localPosition->y==24) {
                inside=true;
                overlap.clear();
                camera={0,0,90*ConstantValues::localTileW,63*ConstantValues::localTileH}; //why 63 and 90?
                positionOutside=player->getComponent<TransformComponent>().position;
                player->getComponent<TransformComponent>().position.y=pair.second*ConstantValues::localTileW;
                player->getComponent<TransformComponent>().position.x=pair.first*ConstantValues::localTileH;
                loadDungeon();
            }
        }
        else {
            int p1=pair.first*ConstantValues::localTileW;
            int p2=pair.second*ConstantValues::localTileH;
            if (p1>=playerpos.x-0.5*ConstantValues::localTileH && p1<=playerpos.x+0.5*ConstantValues::localTileW && p2>=playerpos.y-0.5*ConstantValues::localTileH && p2<=playerpos.y+0.5*ConstantValues::localTileW) {
                inside=false;
                overlap.clear();
                camera = {0,0,(ConstantValues::mapW-1)*ConstantValues::localMapSizeW*ConstantValues::localTileW,(ConstantValues::mapH-1)*ConstantValues::localMapSizeH*ConstantValues::localTileH};
                player->getComponent<TransformComponent>().position=positionOutside;
                loadLocal();
            }
        }
        interact=false;
        gameData->setCamera(camera);
    }
}


void GameLevelIngame::updateUI() {
    auto r=gameData->getGroup(GroupUI);
    int it=0,lvl,fD,sD,tD;
    AttributesComponent a = player->getComponent<AttributesComponent>();
    float h=(float)a.getAttribute(1)/a.getAttribute(0);
    float s=(float)a.getAttribute(3)/a.getAttribute(2);
    float m=(float)a.getAttribute(5)/a.getAttribute(4);
    float x=(float)a.getAttribute(7)/a.getAttribute(6);
    lvl = a.getAttribute(8);
    fD=lvl/100;
    lvl%=100;
    sD=lvl/10;
    lvl%=10;
    tD=lvl;
    for (auto&i : r) {
        switch (it) {
            case 0:
            i->getComponent<SpriteComponent>().setWidthPercentage(h);
            break;
            case 1:
            i->getComponent<SpriteComponent>().setWidthPercentage(m);
            break;
            case 2:
            i->getComponent<SpriteComponent>().setWidthPercentage(s);
            break;
            case 3:
            if (x<0.25) {
                if (x<0.13) {
                    i->getComponent<SpriteComponent>().setWidthPercentage((x*((float)25/31))/0.12);
                    i->getComponent<SpriteComponent>().setHeightPercentage(0.5);
                }
                else {
                    i->getComponent<SpriteComponent>().setHeightPercentage(0.5+(x-0.13)*0.5/0.12);
                }
            }
            break;
            case 4:
            if (x>0.25) {
                if (x<0.5) {
                    if (x<0.38) {
                        i->getComponent<SpriteComponent>().setHeightPercentage((x-0.25)*0.5/0.12);
                    }
                    else {
                        i->getComponent<SpriteComponent>().setXOverhead((1-(x-0.38)*(1/0.12))*23);
                    }
                }
            }
            else i->getComponent<SpriteComponent>().setWidthPercentage(0);
            break;
            case 5:
            if (x>0.5) {
                if (x<0.75) {
                    if (x<0.63) {
                        i->getComponent<SpriteComponent>().setYOverhead(16);
                        i->getComponent<SpriteComponent>().setXOverhead(7+(1-(x-0.5)*(1/0.12))*24);
                    }
                    else {
                        i->getComponent<SpriteComponent>().setYOverhead(16-((x-0.63)*(1/0.12)*16));
                    }
                }
            }
            else i->getComponent<SpriteComponent>().setWidthPercentage(0);
            break;
            case 6:
            if (x>0.75) {
                if (x<1) {
                    if (x<0.88) {
                        i->getComponent<SpriteComponent>().setYOverhead(16+(1-(x-0.75)*(1/0.12))*16);
                    }
                    else {
                        i->getComponent<SpriteComponent>().setWidthPercentage((float)7/31+(x-0.88)*(((float)24/31)/0.12));
                    }
                }

            }
            else i->getComponent<SpriteComponent>().setWidthPercentage(0);
            break;
            case 8:
            i->getComponent<SpriteComponent>().setSrc(0,fD*16,0);
            break;
            case 9:
            i->getComponent<SpriteComponent>().setSrc(0,sD*16,0);
            break;
            case 10:
            i->getComponent<SpriteComponent>().setSrc(0,tD*16,0);
            break;
        }
        it++;
    }
}


void GameLevelIngame::addTileLocal(float x,float y,std::pair<char,int> type,bool b) {
    int r1,r2,d,h=0,w=0,v;
    std::string path;
    auto& tile(gameData->addEntity());
    r1=ConstantValues::localTileW;
    r2=ConstantValues::localTileH;
    d=32; //size inside sprite sheet
    if (type.second>1 || ((type.first=='d' || type.first=='e') && type.second!=GROUND*-1 && type.second>1)) {
        if (type.first=='d' || type.first=='e') {
            if (type.second<GROUND*-1) {
                auto& tileO(gameData->addEntity());
                tileO.addComponent<TileComponent>(x,y,d,d,r2,r1,type);
                if (b) {
                    tileO.addComponent<ColliderComponent>(0,0,r1,r2,"kingdom");
                    type.second=1;
                }
                else {
                    type.second=0;
                }
                tileO.addGroup(GroupCollider);
            }
            else {
                switch (type.second) {
                    case CASTELO*-1:
                    h=10;
                    w=10;
                    path="FortressV1-tiles";
                    b=true;
                    break;
                    case BLACKSMITH*-1:
                    v=gameData->getSettlementBuildingV((int)x/ConstantValues::localMapSizeH,(int)y/ConstantValues::localMapSizeW,type.second*-1);
                    switch (v) {
                        case 0:
                        h=4;
                        w=3;
                        path="BlacksmithV0-tiles";
                        break;
                        case 1:
                        h=4;
                        w=6;
                        path="BlacksmithV1-tiles";
                        break;
                    }
                    break;
                    case MAGETOWER*-1:
                    v=gameData->getSettlementBuildingV((int)x/ConstantValues::localMapSizeH,(int)y/ConstantValues::localMapSizeW,type.second*-1);
                    switch (v) {
                        case 0:
                        h=5;
                        w=3;
                        path="MageTowerV0-tiles";
                        break;
                        case 1:
                        h=6;
                        w=5;
                        path="MageTowerV1-tiles";
                        break;
                    }
                    break;
                    case WITCHCABIN*-1:
                    v=gameData->getSettlementBuildingV((int)x/ConstantValues::localMapSizeH,(int)y/ConstantValues::localMapSizeW,type.second*-1);
                    switch (v) {
                        case 0:
                        h=4;
                        w=3;
                        path="WitchCabinV0-tiles";
                        break;
                        case 1:
                        h=4;
                        w=5;
                        path="WitchCabinV1-tiles";
                        break;
                    }
                    break;
                    case TAVERN*-1:
                    v=gameData->getSettlementBuildingV((int)x/ConstantValues::localMapSizeH,(int)y/ConstantValues::localMapSizeW,type.second*-1);
                    switch (v) {
                        case 0:
                        h=4;
                        w=7;
                        path="TavernV0-tiles";
                        break;
                        case 1:
                        h=4;
                        w=7;
                        path="TavernV1-tiles";
                        break;
                    }
                    break;
                    case WELL*-1:
                    v=gameData->getSettlementBuildingV((int)x/ConstantValues::localMapSizeH,(int)y/ConstantValues::localMapSizeW,type.second*-1);
                    switch (v) {
                        case 0:
                        h=2;
                        w=2;
                        path="WellV0-tiles";
                        break;
                    }
                    break;
                    case CHURCH*-1:
                    v=gameData->getSettlementBuildingV((int)x/ConstantValues::localMapSizeH,(int)y/ConstantValues::localMapSizeW,type.second*-1);
                    switch (v) {
                        case 0:
                        h=6;
                        w=3;
                        path="ChurchV0-tiles";
                        break;
                    }
                    break;
                    default:
                    if (type.second==GROUND*-1) break;
                    v=gameData->getSettlementBuildingV((int)x/ConstantValues::localMapSizeH,(int)y/ConstantValues::localMapSizeW,type.second*-1);
                    switch (v) {
                        case 0:
                        h=3;
                        w=3;
                        path="HouseV0-tiles";
                        break;
                        case 1:
                        h=3;
                        w=5;
                        path="HouseV1-tiles";
                        break;
                        case 2:
                        h=4;
                        w=6;
                        path="HouseV2-tiles";
                        break;
                    }
                    break;
                }
                for (int i=0;i<h;i++) {
                    for (int j=0;j<w;j++) {
                        auto& tilep(gameData->addEntity());
                        tilep.addComponent<TileComponent>(x+i,y+j,d,d,r2,r1,path,i*w+j);
                        tilep.addComponent<ColliderComponent>(0,0,r1,r2,"kingdom");
                        tilep.addGroup(GroupCollider);
                        type.second=1;
                    }
                }
            }
        }
        else {
            auto& tileO(gameData->addEntity());
            tileO.addComponent<TileComponent>(x,y,d,d,r2,r1,type);
            switch (type.second) {
                case 38:
                case 39:
                case 40:
                case 2:
                case 3:
                    tileO.addComponent<ColliderComponent>(0,0,r1,r2,"small object");
                    tileO.addGroup(GroupCollider);
                    type.second=1;
                    break;
                case 4:
                    tileO.addComponent<ColliderComponent>(40,40,24,24,"tree");
                    tileO.addGroup(GroupCollider);
                    type.second=0;
                    break;
                case 5:
                    tileO.addComponent<ColliderComponent>(0,40,24,24,"tree");
                    tileO.addGroup(GroupCollider);
                    type.second=1;
                    break;
                default:
                    tileO.addGroup(GroupCollider);
                    type.second=0;
                    break;
            }
        }
    }
    if (((type.first=='d' || type.first=='e') && type.second==GROUND*-1)) type.second=1;
    tile.addComponent<TileComponent>(x,y,d,d,r2,r1,type);
    tile.addGroup(GroupLocalMap);
}


void GameLevelIngame::loadLocal() {
    gameData->delGroup(GroupLocalMap);
    gameData->delGroup(GroupCollider);
    int r,d,i,ii,j,jj,maxI,maxJ,posx=static_cast<int>(ConstantValues::playerLocalPosX);
    LocalMap *temporary;
    Vector2D * worldPosition = gameData->getWorldPosition();
    for (int k=0;k<9;k++) {
        ii=0;jj=0;maxI=ConstantValues::localMapSizeH;maxJ=ConstantValues::localMapSizeW;
        temporary=NULL;
        switch (k) {
            case 0:
                if (worldPosition->x<=0 || worldPosition->y<=0) break;
                //puts("loading top left");
                ii=ConstantValues::localMapSizeW-posx;
                jj=ConstantValues::localMapSizeH-posx;
                r=worldPosition->x-1;
                d=worldPosition->y-1;
                temporary = gameData->getLocalMap(worldPosition->x-1,worldPosition->y-1);
            break;
            case 1:
                if (worldPosition->x<=0) break;
                //puts("loading center left");
                jj=ConstantValues::localMapSizeH-posx;
                r=worldPosition->x-1;
                d=worldPosition->y;
                temporary = gameData->getLocalMap(worldPosition->x-1,worldPosition->y);
            break;
            case 2:
                if (worldPosition->x<=0 || worldPosition->y>=ConstantValues::mapH-1) break;
                //puts("loading bottom left");
                maxI=posx;
                jj=ConstantValues::localMapSizeH-posx;
                r=worldPosition->x-1;
                d=worldPosition->y+1;
                temporary = gameData->getLocalMap(worldPosition->x-1,worldPosition->y+1);
            break;
            case 3:
                if (worldPosition->y<=0) break;
                //puts("loading top center");
                ii=ConstantValues::localMapSizeW-posx;
                r=worldPosition->x;
                d=worldPosition->y-1;
                temporary = gameData->getLocalMap(worldPosition->x,worldPosition->y-1);
            break;
            case 4:
                //puts("loading center");
                r=worldPosition->x;
                d=worldPosition->y;
                temporary = gameData->getLocalMap(worldPosition->x,worldPosition->y);
            break;
            case 5:
                if (worldPosition->y>=ConstantValues::mapH-1) break;
                //puts("loading bottom center");
                maxI=posx;
                r=worldPosition->x;
                d=worldPosition->y+1;
                temporary = gameData->getLocalMap(worldPosition->x,worldPosition->y+1);
            break;
            case 6:
                if (worldPosition->x>=ConstantValues::mapW-1 || worldPosition->y<=0) break;
                //puts("loading top right");
                ii=ConstantValues::localMapSizeW-posx;
                maxJ=posx+128/ConstantValues::localTileH;
                r=worldPosition->x+1;
                d=worldPosition->y-1;
                temporary = gameData->getLocalMap(worldPosition->x+1,worldPosition->y-1);
            break;
            case 7:
                if (worldPosition->x>=ConstantValues::mapW-1) break;
                //puts("loading center right");
                maxJ=posx+128/ConstantValues::localTileH;
                r=worldPosition->x+1;
                d=worldPosition->y;
                temporary = gameData->getLocalMap(worldPosition->x+1,worldPosition->y);
            break;
            case 8:
                if (worldPosition->x>=ConstantValues::mapW-1 || worldPosition->y>=ConstantValues::mapH-1) break;
                //puts("loading bottom right");
                maxI=posx;
                maxJ=posx+128/ConstantValues::localTileH;
                r=worldPosition->x+1;
                d=worldPosition->y+1;
                temporary = gameData->getLocalMap(worldPosition->x+1,worldPosition->y+1);
            break;
        }
        bool b=true;
        if (temporary) {
            for (i=ii;i<maxI;i++) {
                for (j=jj;j<maxJ;j++) {
                    if ((j>((50-8)/2)) && (j < ((50-8)/2+4)+3) && i>50-9 && i<50-1 ) b=false;
                    else b=true;
                    addTileLocal(i+ConstantValues::localMapSizeH*d,j+ConstantValues::localMapSizeW*r,temporary->getTile(i,j),b);
                }
            }
        }
    }
}

void GameLevelIngame::updatePos() {
    float s=player->getComponent<TransformComponent>().speed;
    Vector2D v = player->getComponent<TransformComponent>().velocity;
    Vector2D * localPosition = gameData->getLocalPosition();
    Vector2D * worldPosition = gameData->getWorldPosition();
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
}

void GameLevelIngame::updateCam() {
    SDL_Rect camera=gameData->getCamera();
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
    gameData->setCamera(camera);
}

void GameLevelIngame::update() {
    Vector2D playerpos,localPos,worldPos;
    std::map<Entity*,Vector2D> enemiesPos;
    playerpos = player->getComponent<TransformComponent>().position.copy();
    localPos = gameData->getLocalPosition()->copy();
    worldPos = gameData->getWorldPosition()->copy();
    if (!inside) updatePos();
    updateCam();

    for (auto& enem : gameData->getGroup(GroupEnemies)) {
        enemiesPos[enem]=enem->getComponent<TransformComponent>().position.copy();
    }

    gameData->managerRefresh();
    gameData->managerUpdate();

    updateUI();
    updateCollisions(playerpos,localPos,worldPos,enemiesPos);
    updateOverlaps();
    checkInteractions();
}