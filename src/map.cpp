#include "../include/map.hpp"


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
    srand((unsigned int)time(NULL));
    for (i=0;i<80;i++) {
        if (rand()%100<fP) {
            posy=rand()%height;
            posx=rand()%width;
            tile=rand()%100>50 ? 1 : 0;
            mapa[posy][posx]=tile;
        }
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
        for (j=0;j<width;j++)
            mapa[i][j]=tmpM[i][j];
    }
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (mapa[i][j]==1 && hasWaterNeighbour(i,j))
                mapa[i][j]=2;
        }
    }
}

void Mapa::initMap(int h,int w) {
    height=h;
    width=w;
    mapa=(int**)malloc(sizeof(int*)*height);
    for (int i=0;i<height;i++) {
        mapa[i]=(int*)malloc(sizeof(int)*width);
    }
}