
#include "../include/test.hpp"


int getSurroundingTiles(int ** map,int x, int y) {
    int tiles=0;
    for (int i=x-1;i<x+2;i++) {
        for (int j=y-1;j<y+2;j++) {
            if (i!=x && j!=y && i>=0 && i<50 && j>=0 && j<50)
                tiles+=map[i][j];
        }
    }
    return tiles;
}

void map (int **map,int width,int height,int fP) {
    int i,j;
    int tmpM[width][height];
    for (i=0;i<width;i++) {
        for (j=0;j<height;j++) {
            srand(0);
            map[i][j]= rand()%100<fP? 0 : 1;
            printf("%d",map[i][j]);
        }
        printf("\n");
    }
    for (int t=0;t<2;t++) {
        for (i=0;i<width;i++) {
            for (j=0;j<height;j++) {
                int sT=getSurroundingTiles(map,i,j);
                if (i==0 || j==0 || i==width-1 || j==height-1)
                    tmpM[i][j]=0;
                else if (sT > 4)
			    	tmpM[i][j] = 1;
			    else if (sT < 4)
			        tmpM[i][j] = 0;
            }
        }
        for (i=0;i<width;i++) {
            for (j=0;j<height;j++)
                map[i][j]=tmpM[i][j];
        }
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
    map(mapa,50,50,50);
    SDL_RenderClear(renderer);
    for (int i=0;i<50;i++) {
        for (int j=0;j<50;j++) {
            if (mapa[i][j]==0) srcR.x=16;
            else srcR.x=0;
            SDL_RenderCopy(renderer,tiles,&srcR,&destR);
            destR.x+=16;
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

