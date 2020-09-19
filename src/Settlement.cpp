#include "../include/Settlement.hpp"
#include "../include/Dungeon.hpp"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/*
double distanceBetweenPoints(int x1,int y1,int x2,int y2) {
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}
*/


Settlement::Settlement(int widthg,int heightg,bool villageg) { //width and height must be divisible by 2
    int i,j;
    width=widthg;
    height=heightg;
    village=villageg;
    map=(int**)malloc(sizeof(int*)*height);
    for (i=0;i<height;i++) {
        map[i]=(int*)malloc(sizeof(int)*width);
        for (j=0;j<width;j++) {
            map[i][j]=-1;
        }
    }
}

int ** Settlement::getMap() {
    return map;
}

int Settlement::getVersion(int buildID) {
    return versions[buildID];
}

void Settlement::buildWall() {
    int i,j,n;
    for (n=0;n<4;n++) {
        switch (n) {
            case 0:
            i=0;
            j=0;
            break;
            case 1:
            i=0;
            j=width-4;
            break;
            case 2:
            i=height-9;
            j=width-4;
            break;
            case 3:
            i=height-9;
            j=0;
            break;
        }
        map[i][j]=TORRECANTOSUPERIORESQUERDO;
        if (n>1) {
            map[i][j+1]=TORRECANTOINFERIORDIREITO;
            map[i][j+2]=TORRECANTOINFERIORESQUERDO;
        }
        else {
            map[i][j+1]=HORIZONTALSUPERIOR;
            map[i][j+2]=HORIZONTALSUPERIOR;
        }
        map[i][j+3]=TORRECANTOSUPERIORDIREITO;
        map[i+1][j+1]=CAMINHOA;
        map[i+1][j+2]=CAMINHOA;
        if (n==0 || n==3) {
            map[i+1][j+3]=TORRECANTOINFERIORESQUERDO;
            map[i+2][j+3]=TORRECANTOSUPERIORESQUERDO;
        }
        else {
            map[i+1][j+3]=VERTICALDIREITO;
            map[i+2][j+3]=VERTICALDIREITO;
        }
        if (n==1 || n==2) {
            map[i+1][j]=TORRECANTOINFERIORDIREITO;
            map[i+2][j]=TORRECANTOSUPERIORDIREITO;
        }
        else {
            map[i+1][j]=VERTICALESQUERDO;
            map[i+2][j]=VERTICALESQUERDO;
        }
        map[i+2][j+1]=CAMINHOA;
        map[i+2][j+2]=CAMINHOA;
        map[i+3][j]=TORRECANTOINFERIORESQUERDO;
        if (n==0 || n==1) {
            map[i+3][j+1]=TORRECANTOSUPERIORDIREITO;
            map[i+3][j+2]=TORRECANTOSUPERIORESQUERDO;
        }
        else {
            map[i+3][j+1]=HORIZONTALINFERIOR;
            map[i+3][j+2]=HORIZONTALINFERIOR;
        }
        map[i+3][j+3]=TORRECANTOINFERIORDIREITO;
        for (int k=0;k<5;k++) {
            map[i+4+k][j]=MURALHAESQ;
            map[i+4+k][j+1]=MURALHA;
            map[i+4+k][j+2]=MURALHA;
            map[i+4+k][j+3]=MURALHADIR;
        }
        for (j=4;j<width-4;j++) {
            map[1][j]=HORIZONTALSUPERIOR;
            map[2][j]=HORIZONTALINFERIOR;
            for (i=0;i<5;i++) {
                map[i+3][j]=MURALHA;
                map[height-6+i][j]=MURALHA;
            }
            map[height-7][j]=HORIZONTALINFERIOR;
            map[height-8][j]=HORIZONTALSUPERIOR;
        }
        for (i=4;i<height-9;i++) {
            map[i][1]=VERTICALESQUERDO;
            map[i][2]=VERTICALDIREITO;
            map[i][width-3]=VERTICALESQUERDO;
            map[i][width-2]=VERTICALDIREITO;
        }
    }
    int startofdoorx = (width-8)/2 + 1;
    int startofdoory = (height-1);
    for (i=0;i<6;i++) {
        for (j=0;j<4;j++) 
            map[startofdoory-j][startofdoorx+i]=CAMINHO;
    }
    map[startofdoory-1][startofdoorx]=ENTRADA1;
    map[startofdoory-2][startofdoorx]=ENTRADA2;
    map[startofdoory-3][startofdoorx]=ENTRADA3;
    map[startofdoory-3][startofdoorx+1]=ENTRADA4;
    map[startofdoory-4][startofdoorx+1]=ENTRADA5;
    map[startofdoory-5][startofdoorx+1]=ENTRADA6;
    map[startofdoory-4][startofdoorx+2]=ENTRADA7;
    map[startofdoory-5][startofdoorx+2]=ENTRADA8;
    map[startofdoory-4][startofdoorx+3]=ENTRADA9;
    map[startofdoory-5][startofdoorx+3]=ENTRADA10;
    map[startofdoory-3][startofdoorx+4]=ENTRADA11;
    map[startofdoory-4][startofdoorx+4]=ENTRADA12;
    map[startofdoory-5][startofdoorx+4]=ENTRADA13;
    map[startofdoory-1][startofdoorx+5]=ENTRADA14;
    map[startofdoory-2][startofdoorx+5]=ENTRADA15;
    map[startofdoory-3][startofdoorx+5]=ENTRADA16;
}

void Settlement::addCastle() {
    int i,j,middlex=(width-8)/2+3,x=middlex-4,y=(height-26)/2+7;
    for (i=-1;i<11;i++) {
        for (j=-1;j<11;j++) {
            if (i==-1 || j==-1 || i==10 || j==10) map[y+i][x+j]=CAMINHO;
            else if (i==0 && j==0) map[y+i][x+j]=CASTELO;
            else map[y+i][x+j]=GROUND;
        }
    }
    for (i=0;i<12;i++) {
        map[height-9-i][middlex]=CAMINHO;
        map[height-9-i][middlex+1]=CAMINHO;
    }
}

std::pair<int,int> Settlement::getClosest(std::pair<int,int> to) {
    double min=1000000,at;
    std::pair<int,int> minp((height-1)/2,(width-1)/2);
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            if (map[i][j]!=CAMINHO) continue;
            at=distanceBetweenPoints(i,j,to.first,to.second);
            if (min>at) {
                min=at;
                minp.first=i;
                minp.second=j;
            }
        }
    }
    return minp;
}

bool Settlement::canGo(int sentido,std::pair<int,int> from) {
    bool r;
    switch (sentido) {
        case 1: //check down 
            r=(from.first+1<height) && (map[from.first+1][from.second]==CAMINHO || map[from.first+1][from.second]==-1);
        break;
        case 2: //check up
            r=(from.first>0) && (map[from.first-1][from.second]==CAMINHO || map[from.first-1][from.second]==-1);
        break;
        case 3: //check right
            r=(from.second+1<width) && (map[from.first][from.second+1]==CAMINHO || map[from.first][from.second+1]==-1);
        break;
        case 4: //check left
            r=(from.second>0) && (map[from.first][from.second-1]==CAMINHO || map[from.first][from.second-1]==-1);
        break;
    }
    return r;
}

std::pair<int,int> Settlement::goAround(int sen,std::pair<int,int> from,std::pair<int,int> to) {
    int r=-1,counter=1,n=0,t=1;
    std::pair<int,int> temp,tempt;
    if (sen==3 || sen==1) r=1;
    switch (sen) {
        case 1:
        case 2:
            if (from.second==to.second) {
                while (t) { //cycle that finds closest exit to continue path
                    temp=tempt=from;
                    for (int i=0;i<2 && t;i++) {
                        if (i==0) {
                            temp.second+=counter-1;
                            tempt.second+=counter;
                        }
                        else {
                            temp.second-=((counter-1)*2);
                            tempt.second-=counter*2;
                        }
                        if ((r==1 && canGo(3+i,temp) && canGo(1,tempt)) || (r==-1 && canGo(3+i,temp) && canGo(2,tempt))) {
                            n=(i+1)%2;
                            t=0;
                        }
                    }   
                    counter++;
                }
            }
            if (from.second<to.second || n) {
                while (!canGo(sen,from)) {
                    if (distanceBetweenPoints(to.first,to.second,from.first,from.second)==0) return from;
                    if (canGo(3,from)) 
                        map[from.first][++from.second]=CAMINHO;
                    else from=goAround(3,from,to);
                }
                map[from.first+r][from.second]=CAMINHO;
                from.first+=r;
            }
            else {
                while (!canGo(sen,from)) {
                    if (distanceBetweenPoints(to.first,to.second,from.first,from.second)==0) return from;
                    if (canGo(4,from)) 
                        map[from.first][--from.second]=CAMINHO;
                    else from=goAround(4,from,to);
                }
                map[from.first+r][from.second]=CAMINHO;
                from.first+=r;
            }
        break;
        case 3:
        case 4:
            if (from.first==to.first) {
                while (t) { //cycle that finds closest exit to continue path
                    temp=tempt=from;
                    for (int i=0;i<2 && t;i++) {
                        if (i==0) {
                            temp.first+=counter-1;
                            tempt.first+=counter;
                        }
                        else {
                            temp.first-=((counter-1)*2);
                            tempt.first-=counter*2;
                        }
                        if ((r==1 && canGo(1+i,temp) && canGo(3,tempt)) || (r==-1 && canGo(1+i,temp) && canGo(4,tempt))) {
                            n=(i+1)%2;
                            t=0;
                        }
                    }
                    counter++;
                }
            }
            if (from.first<to.first || n) {
                while (!canGo(sen,from)) {
                    if (distanceBetweenPoints(to.first,to.second,from.first,from.second)==0) return from;
                    if (canGo(1,from)) 
                        map[++from.first][from.second]=CAMINHO;
                    else from=goAround(1,from,to);
                }
                map[from.first][from.second+r]=CAMINHO;
                from.second+=r;
            }
            else {
                while (!canGo(sen,from)) {
                    if (distanceBetweenPoints(to.first,to.second,from.first,from.second)==0) return from;
                    if (canGo(2,from)) 
                        map[--from.first][from.second]=CAMINHO;
                    else from=goAround(2,from,to);
                }
                map[from.first][from.second+r]=CAMINHO;
                from.second+=r;
            }
        break;
    }
    return from;
}

void Settlement::buildRoad(int buildID) {
    std::pair<int,int> to = entrances[buildID];
    std::pair<int,int> from = getClosest(to);
    while (distanceBetweenPoints(to.first,to.second,from.first,from.second)>0) {
        if (to.first>from.first) {
            if (canGo(1,from))
                map[++from.first][from.second]=CAMINHO;
            else from=goAround(1,from,to);
            continue;
        }
        if (to.first<from.first) {
            if (canGo(2,from))
                map[--from.first][from.second]=CAMINHO;
            else from=goAround(2,from,to);
            continue;
        }
        if (to.second>from.second) {
            if (canGo(3,from))
                map[from.first][++from.second]=CAMINHO;
            else from=goAround(3,from,to);
            continue;
        }
        if (to.second<from.second) {
            if (canGo(4,from))
                map[from.first][--from.second]=CAMINHO;
            else from=goAround(4,from,to);
            continue;
        }
    }
}

void Settlement::addBuilding(int buildID) {
    int rw,rh,rx,ry,r=1,j,k,p=0,entx,enty,t,version,rando;
    bool bbb;
    if (buildID>WELL) {
        rando=NODSV;
    }
    else if (buildID>=CHURCH)
        rando=NODSFV;
    else if (buildID==FILLER)
        rando=NODFV;
    else rando=NODHV;
    version=rand()%(rando);
    if ((buildID==BLACKSMITH) || (buildID==WITCHCABIN) || (buildID==TAVERN) || (buildID<CHURCH && version==2))
        rh=4;
    else if ((buildID==MAGETOWER && version==0))
        rh=5;
    else if ((buildID==MAGETOWER) || (buildID==CHURCH))
        rh=6;
    else if ((buildID<CHURCH))
        rh=3;
    else rh=2;
    if ((buildID==BLACKSMITH && version==1) || (buildID<CHURCH && version==2))
        rw=6;
    else if ((buildID==WITCHCABIN && version==2) || (buildID<CHURCH && version==1) || (buildID==MAGETOWER && version==1))
        rw=5;
    else if (buildID==TAVERN)
        rw=7;
    else if (buildID==WELL) 
        rw=2;
    else rw=3;
    while (r && p<15) {
        p++;
        r=0;
        rx=rand()%(width-rw+1);
        ry=rand()%(height-rh);
        entx=rx+1;
        enty=ry+rh-1;
        for (j=-1;j<=rh && r==0;j++) {
            for (k=-1;k<=rw && r==0;k++) {
                if (j+ry<0 || j+ry>=height || k+rx<0 || k+rx>=width)
                    continue;
                t = map[j+ry][k+rx];
                bbb = j==-1 || j==rh || k==-1 || k==rw;
                if (( bbb && t!=-1 && t!=CAMINHO) || (!bbb && t!=-1)) {
                    r=1;
                    break;
                }
            }
        }
        if (r) continue;
        for (j=0;j<rh;j++) {
            for (k=0;k<rw;k++) {
                if (j==0 && k==0)
                    map[j+ry][k+rx]=buildID;
                else map[j+ry][k+rx]=GROUND;
            }
        }
        //map[enty][entx]=9; // entrance to the building
        std::pair<int,int> ent = {enty+1,entx};
        std::pair<int,int> start = {ry,rx};
        std::pair<int,int> measures = {rw,rh};
        std::pair<std::pair<int,int>,std::pair<int,int>> p = {start,measures};
        buildings[buildID]=p;
        entrances[buildID]= ent;
        versions[buildID]=version;
        buildRoad(buildID);
    }
}

void Settlement::printMap() {
    int i,j;
    puts("#####\npolished\n#####");
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (map[i][j]==-1) printf("  ");
            else if (map[i][j]>9) printf("%c ",map[i][j]+55);
            else if (map[i][j]<-9) printf("%c ",map[i][j]*-1+55);
            else if (map[i][j]<0) printf("%d ",map[i][j]*-1);
            else printf("%d ",map[i][j]);
        }
        puts("");
    }
}

void Settlement::makeSettlement() {
    int r,i;
    if (village) {
        buildWall();
        addCastle();
        r=4;
    }
    else {
        map[(height-1)/2][(width-1)/2]=CAMINHO;
        r=2;
    }
    for (i=0;i<r;i++) {
        switch (i) {
            case 0:
            addBuilding(BLACKSMITH);
            break;
            case 1:
            addBuilding(MAGETOWER);
            break;
            case 2:
            addBuilding(WITCHCABIN);
            break;
            case 3:
            addBuilding(TAVERN);
            break;
        }
    }
    addBuilding(WELL);
    addBuilding(CHURCH);
    for (i=0;i<r*r*r;i++) {
        addBuilding(CHURCH-1-i);
    }
}

/*
int main() {
    srand(time(NULL)*getpid());
    Settlement *s = new Settlement(50,50,true);
    s->makeSettlement();
    s->printMap();
    puts("nao estourou");
    Settlement *t = new Settlement(50,50,false);
    t->makeSettlement();
    t->printMap();
}
*/
