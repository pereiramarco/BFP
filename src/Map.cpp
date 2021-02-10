#include "../include/Map.hpp"
#include "../include/TextureManager.hpp"
#include "../include/GameData.hpp"

Mapa::Mapa(SDL_Renderer * ren,int h,int w) {
    height=h;
    width=w;
    worldMap=(int**)malloc(sizeof(int*)*height);
    mapa=(LocalMap***)malloc(sizeof(LocalMap**)*height);
    for (int i=0;i<height;i++) {
        worldMap[i]=(int*)malloc(sizeof(int)*width);
        mapa[i]=(LocalMap**)malloc(sizeof(LocalMap*)*width);
        for (int j=0;j<width;j++) {
            mapa[i][j] = new LocalMap("assets/mancha",this->mapOfTexs);
        }
    }
    randomizeMap(70);
    randomizeLocalMaps();
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            GameData::addTileWorld(i,j,worldMap[i][j]);
        }
    }
}

int Mapa::getHeight() {
    return height;
}


int Mapa::getWidth() {
    return width;
}

int Mapa::getTile(int i,int j) {
    return worldMap[i][j];
}

LocalMap* Mapa::getLocalMap(int i,int j) {
    return this->mapa[j][i];//recebe x e y mas na matriz está trocado
}

int Mapa::getSettlementBuildingV(int h,int w,int buildID) {
    std::pair<int,int> p(h,w);
    return settlements[p]->getVersion(buildID);
}

void Mapa::setLocalMapmap(int y,int x,int ** map,char d) {
    int i,j;
    std::pair<char,int> **mapinha;
    mapinha=(std::pair<char,int>**)malloc(sizeof(std::pair<char,int>*)*50);
    for (i=0;i<50;i++) {
        mapinha[i]=(std::pair<char,int>*)malloc(sizeof(std::pair<char,int>)*50);
        for (j=0;j<50;j++) {
            std::pair<char,int> p(d,map[i][j]);
            mapinha[i][j]=p;
        }
    }
    mapa[y][x]->setTileMap(mapinha);
}

Dungeon* Mapa::getDungeon(std::pair<int,int> p) {
     return this->dungeons[p];
 }

std::pair<char,int> Mapa::getLocalMapTile(int wI,int wJ,int i,int j) {
    return mapa[wI][wJ]->getTile(i,j);
}

int Mapa::closestCreator(int x,int y) {
    int tileMin=0,i,j; 
    double dmin=1000;
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (worldMap[i][j]!=-1) {
                double d=distanceBetweenPoints(x,y,i,j);
                if (d<dmin) {
                    tileMin=worldMap[i][j];
                    dmin=d;
                }
            }
        }
    }
    return tileMin;
}

bool Mapa::hasWaterNeighbour (int x,int y) {
    int i,j;
    for (i=x-1;i<x+2;i++) {
        for (j=y-1;j<y+2;j++) {
            if (i>=0 && i<height && j>=0 && j<width && worldMap[i][j]==0)
                return true;
        }
    }
    return false;
}

void Mapa::randomizeMap(int fP) {
    int i,j,posx,posy,tile,tmpM[height][width];
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (i==0 || i==height-1 || j==0 || j==width-1) 
                this->worldMap[i][j]=0;
            else
                this->worldMap[i][j]=-1;
        }
    }
    srand((unsigned int)time(NULL)*rand());
    for (i=0;i<fP;i++) {
        posy=rand()%height;
        posx=rand()%width;
        if (posy==0 || posy==height-1 || posx==0 || posx==width-1)
            i--;
        else {
            tile=rand()%100>40 ? 1 : 0;
            worldMap[posy][posx]=tile;
        }
    }
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (worldMap[i][j]==-1) {
                int tile=closestCreator(i,j);
                tmpM[i][j]=tile;
            }
            else tmpM[i][j]=worldMap[i][j];
        }

    }
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            worldMap[i][j]=tmpM[i][j];
        }
    }
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (worldMap[i][j]==1 && hasWaterNeighbour(i,j))
                worldMap[i][j]=2;
            if (worldMap[i][j]!=0) {
                int r=rand()%1001;
                if (r<=15) {
                    GameData::addTileWorld(i,j,worldMap[i][j]);
                    r=rand()%101;
                    if (r<=60) {
                        worldMap[i][j]=5;
                    }
                    else if (r<=90) {
                        worldMap[i][j]=4;
                    }
                    else {
                        worldMap[i][j]=3;
                    }
                }
            }
        }
    }
}

void Mapa::randomizeLocalMaps() {
    int i,j,esq,cima,dir,baixo;
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            srand((unsigned int)time(NULL)*i*j);
            cima=baixo=esq=dir=worldMap[i][j];
            if (i)
                cima=worldMap[i-1][j];
            if (i<height-1)
                baixo=worldMap[i+1][j];
            if (j)
                esq=worldMap[i][j-1];
            if (j<width-1)
                dir=worldMap[i][j+1];
            if (worldMap[i][j]==5) {
                std::pair<int,int> p(i,j);
                Dungeon *d = new Dungeon(120,80,30);
                d->randomizeRooms();
                d->polishDungeon();
                d->addExtras();
                dungeons[p]=d;
            }
            if (worldMap[i][j]==3) {
                std::pair<int,int> p(i,j);
                Settlement *s = new Settlement(50,50,true);
                s->makeSettlement();
                settlements[p]=s;
                setLocalMapmap(i,j,s->getMap(),'d');
            }
            else if (worldMap[i][j]==4) {
                std::pair<int,int> p(i,j);
                Settlement *s = new Settlement(50,50,false);
                s->makeSettlement();
                settlements[p]=s;
                setLocalMapmap(i,j,s->getMap(),'e');
                
            }
            else
                mapa[i][j]->randomizeTile(worldMap[i][j]+'a',cima+'a',dir+'a',baixo+'a',esq+'a');
        }
    }
}