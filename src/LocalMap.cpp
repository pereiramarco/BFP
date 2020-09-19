#include "../include/LocalMap.hpp"
#include "../include/TextureManager.hpp"
#include "../include/ConstantValues.hpp"

LocalMap::LocalMap() {
    mapa=(std::pair<char,int> **)malloc(sizeof(std::pair<char,int>*)*ConstantValues::localMapSizeW);
    mancha=(char**)malloc(sizeof(char*)*ConstantValues::localMapSizeW);
    for (int i=0;i<ConstantValues::localMapSizeW;i++) {
        mapa[i]=(std::pair<char,int> *)malloc(sizeof(std::pair<char,int>)*ConstantValues::localMapSizeH);
        mancha[i]=(char*)malloc(sizeof(char)*ConstantValues::localMapSizeH);
        for (int j=0;j<ConstantValues::localMapSizeH;j++) {
            mapa[i][j].second=-1;
            mapa[i][j].first='.';
        }
    }
}

LocalMap::LocalMap(std::string path,std::map<char,SDL_Texture*>text) {
    mapa=(std::pair<char,int> **)malloc(sizeof(std::pair<char,int>*)*ConstantValues::localMapSizeW);
    mancha=(char**)malloc(sizeof(char*)*ConstantValues::localMapSizeW);
    for (int i=0;i<ConstantValues::localMapSizeW;i++) {
        mapa[i]=(std::pair<char,int> *)malloc(sizeof(std::pair<char,int>)*ConstantValues::localMapSizeH);
        mancha[i]=(char*)malloc(sizeof(char)*ConstantValues::localMapSizeH);
        for (int j=0;j<ConstantValues::localMapSizeH;j++) {
            mapa[i][j].second=-1;
            mapa[i][j].first='.';
        }
    }
    textures=text;
    std::ifstream file (path);
    char valor;
    for (int i=0;i<ConstantValues::localMapSizeW;i++) {
        for (int j=0;j<ConstantValues::localMapSizeH;j++) {
            file.get(valor);
            mancha[i][j]=valor;
            file.get(valor);
        }
    }
}

std::pair<char,int> LocalMap::getTile(int i,int j) {
    std::pair<char,int> p =mapa[i][j];
    if (p.second<0) p.second*=-1;
    return p;
}

void LocalMap::setTile(int i,int j,std::pair<char,int> par) {
    this->mapa[i][j]=par;
}

void LocalMap::setTileMap(std::pair<char,int>**mapaa) {
    for (int i=0;i<50;i++) {
        free(mapa[i]);
    }
    free(mapa);
    mapa=mapaa;
}

void LocalMap::randomizeTile(char type0,char type1,char type2,char type3,char type4) {
    int i,j,r,l,k;
    for (i=0;i<ConstantValues::localMapSizeW;i++) {
        for (j=0;j<ConstantValues::localMapSizeH;j++) {
            if (mapa[i][j].first=='.') {
                switch (mancha[i][j]) {
                    case '0':
                        mapa[i][j].first=type0=='f'?'b':type0;
                        break;
                    case '1':
                        mapa[i][j].first=type1>'c'?'b':type1;
                        break;
                    case '2':
                        mapa[i][j].first=type2>'c'?'b':type2;
                        break;
                    case '3':
                        mapa[i][j].first=type3>'c'?'b':type3;
                        break;
                    case '4':
                        mapa[i][j].first=type4>'c'?'b':type4;
                        break;
                }
            }
            if (i==22 && j==22 && type0=='f') {
                for (k=-1;k<6;k++) {
                    for (l=-1;l<8;l++) {
                        if (k==-1 || k==5 || l==-1 || l==7) mapa[i+k][j+l].second=rand()%2;
                        else mapa[i+k][j+l].second=8+k*7 + l;
                    }
                }

            }
            if (mapa[i][j].second==-1) {
                if (i!=ConstantValues::localMapSizeW-1 && j!=ConstantValues::localMapSizeH-1 && mapa[i][j+1].second==-1 && mapa[i+1][j+1].second==-1) r=rand()%101;
                else r=rand()%100;
                if (r>=100) {
                    mapa[i][j].second=6;
                    mapa[i+1][j].second=4;
                    mapa[i][j+1].second=7;
                    mapa[i+1][j+1].second=5;
                    mapa[i+1][j+1].first=mapa[i+1][j].first=mapa[i][j+1].first=mapa[i][j].first;
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

void LocalMap::print() {
    int i,j;
    for (i=0;i<50;i++) {
        for (j=0;j<50;j++) {
            if (mapa[i][j].second==-1) printf("  ");
            else if (mapa[i][j].second>9) printf("%c ",mapa[i][j].second+55);
            else if (mapa[i][j].second<-9) printf("%c ",mapa[i][j].second*-1+55);
            else if (mapa[i][j].second<0) printf("%d ",mapa[i][j].second*-1);
            else printf("%d ",mapa[i][j].second);
        }
        puts("");
    }
    puts("");
}