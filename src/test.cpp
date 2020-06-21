
#include "../include/test.hpp"

double distanceBetweenPoints(int x1,int y1,int x2,int y2) {
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

int closestCreator(int **map,int x,int y,int width,int height) {
    int tileMin=0,i,j; 
    double dmin=1000;
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (map[i][j]!=-1) {
                double d=distanceBetweenPoints(x,y,i,j);
                if (d<dmin) {
                    tileMin=map[i][j];
                    dmin=d;
                }
            }
        }
    }
    return tileMin;
}

void map(int **map,int width,int height,int fP) {
    int i,j,posx,posy,tile,tmpM[height][width];
    for (i=0;i<width;i++) {
        for (j=0;j<height;j++) {
            map[i][j]=-1;
        }
    }
    srand((unsigned int)time(NULL));
    for (i=0;i<80;i++) {
        if (rand()%100<30) {
            posx=rand()%width;
            posy=rand()%height;
            tile=rand()%100>50 ? 1 : 0;
            map[posx][posy]=tile;
        }
    }
    for (i=0;i<width;i++) {
        for (j=0;j<height;j++) {
            if (map[i][j]==-1) {
                int tile=closestCreator(map,i,j,width,height);
                tmpM[i][j]=tile;
            }
            else tmpM[i][j]=map[i][j];
        }

    }
    for (i=0;i<width;i++) {
        for (j=0;j<height;j++)
            map[i][j]=tmpM[i][j];
    }
}


SDL_Texture * tiles;
SDL_Rect srcR,destR;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int x, int y, int width, int height,bool fullscreen) {
    int f= fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    isRunning=true;
    if (SDL_Init(SDL_INIT_EVERYTHING)==0) {
        window=SDL_CreateWindow(title,x,y,width,height,f);
        if (window) {
            renderer=SDL_CreateRenderer(window,-1,0);
            if (renderer)
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
        }
    }
    SDL_Surface* tmpSrfc = IMG_Load("assets/Tiles_Sheet-Sheet.png");
    tiles=SDL_CreateTextureFromSurface(renderer,tmpSrfc);
    SDL_FreeSurface(tmpSrfc);
    destR.h=16;
    destR.w=16;
    srcR.h=16;
    srcR.w=16;
    destR.x=0;
    destR.y=0;
    srcR.x=0;
    srcR.y=0;
    mapa=(int**)malloc(sizeof(int*)*50);
    for (int i=0;i<50;i++) {
        mapa[i]=(int*)malloc(sizeof(int)*50);
    }
}

void Game::renderMap() {
    destR.h=16;
    destR.w=16;
    srcR.h=16;
    srcR.w=16;
    destR.x=0;
    destR.y=0;
    srcR.x=0;
    srcR.y=0;
    map(mapa,50,50,6);
    SDL_RenderClear(renderer);
    for (int i=0;i<50;i++) {
        for (int j=0;j<50;j++,destR.x+=16) {
            if (mapa[i][j]==0) srcR.x=16;
            else if (mapa[i][j]==1) srcR.x=0;
            else continue;
            SDL_RenderCopy(renderer,tiles,&srcR,&destR);
        }
        destR.x=0;
        destR.y+=16;
    }
    SDL_RenderPresent(renderer);
}

void Game::handleinput() {

}

void Game::update() {

}

