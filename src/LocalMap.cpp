#include "../include/LocalMap.hpp"
#include "../include/TextureManager.hpp"

LocalMap::LocalMap(const char * name,SDL_Renderer* rend) {
    ren=rend;
    tex=TextureManager::loadTexture(name);
    for (int i=0;i<50;i++) {
        for (int j=0;j<50;j++)
            mapa[i][j]=-1;
    }
    randomizeTile();
}

void LocalMap::randomizeTile() {
    int i,j,r;
    for (i=0;i<50;i++) {
        for (j=0;j<50;j++) {
            if (mapa[i][j]==-1) {
                if (i!=49 && j!=49 && mapa[i][j+1]==-1 && mapa[i+1][j+1]==-1) r=rand()%101;
                else r=rand()%100;
                if (r>=100) {
                    mapa[i][j]=6;
                    mapa[i+1][j]=4;
                    mapa[i][j+1]=7;
                    mapa[i+1][j+1]=5;
                }
                else if (r>=98)
                    mapa[i][j]=2;
                else if (r>=96)
                    mapa[i][j]=3;
                else if (r>=48)
                    mapa[i][j]=1;
                else mapa[i][j]=0;
            }
        }
    }
}

void LocalMap::render() {
    srcR.h=32;
    srcR.w=32;
    srcR.y=0;
    destR.h=72;
    destR.w=96;
    destR.x=0;
    destR.y=0;
    for (int i=0;i<15;i++) {
        for (int j=0;j<20;j++,destR.x+=96) {
            srcR.x=mapa[i][j]*32;
            SDL_RenderCopy(ren,tex,&srcR,&destR);
        }
        destR.x=0;
        destR.y+=72;
    }
}