#include "../include/LocalMap.hpp"
#include "../include/TextureManager.hpp"

LocalMap::LocalMap() {
    mapa=(std::pair<char,int> **)malloc(sizeof(std::pair<char,int>*)*50);
    for (int i=0;i<50;i++) {
        mapa[i]=(std::pair<char,int> *)malloc(sizeof(std::pair<char,int>)*50);
        for (int j=0;j<50;j++) {
            mapa[i][j].second=-1;
            mapa[i][j].first='.';
        }
    }
}

LocalMap::LocalMap(SDL_Renderer* rend,std::map<char,SDL_Texture*>text) {
    ren=rend;
    textures=text;
    mapa=(std::pair<char,int> **)malloc(sizeof(std::pair<char,int>*)*50);
    for (int i=0;i<50;i++) {
        mapa[i]=(std::pair<char,int> *)malloc(sizeof(std::pair<char,int>)*50);
        for (int j=0;j<50;j++) {
            mapa[i][j].second=-1;
            mapa[i][j].first='.';
        }
    }
}

std::pair<char,int> LocalMap::getTile(int i,int j) {
    return mapa[i][j];
}

void LocalMap::setTile(int i,int j,std::pair<char,int> par) {
    this->mapa[i][j]=par;
}

void LocalMap::randomizeTile(char type) {
    int i,j,r;
    for (i=0;i<50;i++) {
        for (j=0;j<50;j++) {
            mapa[i][j].first=type;
            if (mapa[i][j].second==-1) {
                if (i!=49 && j!=49 && mapa[i][j+1].second==-1 && mapa[i+1][j+1].second==-1) r=rand()%101;
                else r=rand()%100;
                if (r>=100) {
                    mapa[i][j].second=6;
                    mapa[i+1][j].second=4;
                    mapa[i][j+1].second=7;
                    mapa[i+1][j+1].second=5;
                }
                else if (r>=98)
                    mapa[i][j].second=2;
                else if (r>=96)
                    mapa[i][j].second=3;
                else if (r>=48)
                    mapa[i][j].second=1;
                else mapa[i][j].second=0;
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
            srcR.x=mapa[i][j].second*32;
            SDL_RenderCopy(ren,textures[mapa[i][j].first],&srcR,&destR);
        }
        destR.x=0;
        destR.y+=72;
    }
}