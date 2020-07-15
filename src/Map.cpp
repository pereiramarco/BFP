#include "../include/Map.hpp"
#include "../include/TextureManager.hpp"
#include "../include/Game.hpp"

Mapa::Mapa(SDL_Renderer * ren,int h,int w) {
    height=h;
    width=w;
    worldMap=(int**)malloc(sizeof(int*)*height);
    mapa=(LocalMap***)malloc(sizeof(LocalMap**)*height);
    for (int i=0;i<height;i++) {
        worldMap[i]=(int*)malloc(sizeof(int)*width);
        mapa[i]=(LocalMap**)malloc(sizeof(LocalMap*)*width);
        for (int j=0;j<width;j++) {
            mapa[i][j] = new LocalMap(this->renderer,this->mapOfTexs);
        }
    }
    randomizeMap(70);
    randomizeLocalMaps();
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            Game::addTile(i,j,true,worldMap[i][j],std::pair<char,int> ('a',0));
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

std::pair<char,int> Mapa::getLocalMapTile(int wI,int wJ,int i,int j) {
    return mapa[wI][wJ]->getTile(i,j);
}

double distanceBetweenPoints(int x1,int y1,int x2,int y2) {
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
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
                    Game::addTile(i,j,true,worldMap[i][j],std::pair<char,int>('.',-1));
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
    int i,j,r;
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            mapa[i][j]->randomizeTile(worldMap[i][j]+'a');
        }
    }
}