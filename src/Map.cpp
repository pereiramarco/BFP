#include "../include/Map.hpp"
#include "../include/TextureManager.hpp"

Mapa::Mapa(const char * name,SDL_Renderer * ren,int h,int w) {
    height=h;
    width=w;
    mapa=(int**)malloc(sizeof(int*)*height);
    for (int i=0;i<height;i++) {
        mapa[i]=(int*)malloc(sizeof(int)*width);
    }
    renderer=ren;
    texture=TextureManager :: loadTexture(name);
    randomizeMap(60);
}

void Mapa::render() {
    destR.h=24;
    destR.w=24;
    srcR.h=16;
    srcR.w=16;
    destR.x=0;
    destR.y=0;
    srcR.x=0;
    srcR.y=0;
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++,destR.x+=24) {
            switch (mapa[i][j]) {
                case (0):
                    srcR.x=16;
                break;
                case (1):
                    srcR.x=0;
                break;
                case (2):
                    srcR.x=32;
                break;
                default:
                    if (hasWaterNeighbour(i,j)) srcR.x=32;
                        else srcR.x=0;
                    SDL_RenderCopy(renderer,texture,&srcR,&destR);
                    switch (mapa[i][j]) {
                        case (3):
                            srcR.x=80;
                        break;
                        case (4):
                            srcR.x=64;
                        break;
                        case (5):
                            srcR.x=48;
                        break;
                    }
                break;
            }
            SDL_RenderCopy(renderer,texture,&srcR,&destR);
        }
        destR.x=0;
        destR.y+=24;
    }
}

int Mapa::getHeight() {
    return height;
}


int Mapa::getWidth() {
    return width;
}

int Mapa::getTile(int i,int j) {
    return mapa[i][j];
}

double distanceBetweenPoints(int x1,int y1,int x2,int y2) {
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

int Mapa::closestCreator(int x,int y) {
    int tileMin=0,i,j; 
    double dmin=1000;
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (mapa[i][j]!=-1) {
                double d=distanceBetweenPoints(x,y,i,j);
                if (d<dmin) {
                    tileMin=mapa[i][j];
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
            if (i>=0 && i<height && j>=0 && j<width && mapa[i][j]==0)
                return true;
        }
    }
    return false;
}

void Mapa::randomizeMap(int fP) {
    int i,j,posx,posy,tile,tmpM[height][width];
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            this->mapa[i][j]=-1;
        }
    }
    srand((unsigned int)time(NULL)*rand());
    for (i=0;i<fP;i++) {
        posy=rand()%height;
        posx=rand()%width;
        tile=rand()%100>50 ? 1 : 0;
        mapa[posy][posx]=tile;
    }
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (mapa[i][j]==-1) {
                int tile=closestCreator(i,j);
                tmpM[i][j]=tile;
            }
            else tmpM[i][j]=mapa[i][j];
        }

    }
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            mapa[i][j]=tmpM[i][j];
        }
    }
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (mapa[i][j]==1 && hasWaterNeighbour(i,j))
                mapa[i][j]=2;
            if (mapa[i][j]!=0) {
                int r=rand()%101;
                if (r<=1) {
                    r=rand()%101;
                    if (r<=60) {
                        mapa[i][j]=3;
                    }
                    else if (r<=90) {
                        mapa[i][j]=4;
                    }
                    else {
                        mapa[i][j]=5;
                    }
                }
            }
        }
    }
}