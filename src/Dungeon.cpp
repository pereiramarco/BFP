#include "../include/Dungeon.hpp"
#include <stdio.h>
static int** matrix;

Dungeon::Dungeon(int w,int h,int rn) {
    int i,j;
    width=w/2;
    height=h/2;
    roomNumber=rn;
    matrix=(int**)malloc(sizeof(int*)*height);
    for (i=0;i<height;i++) {
        matrix[i]=(int*)malloc(sizeof(int)*width);
        for (j=0;j<width;j++) {
            matrix[i][j]=-20;
        }
    }
    map=(int**)malloc(sizeof(int*)*h);
    for (i=0;i<h;i++) {
        map[i]=(int*)malloc(sizeof(int)*w);
    }
    int r=rand()%2;
    int x,y;
    if (r) {
        y=rand()%(width-2)+1;//max is width-2 min is 1;
        x=(rand()%2)*(height-3)+1;
        if (x!=1) entrance.second=(x+1)*2+1;
        else entrance.second=0;
        entrance.first=y*2+1;
    }
    else {
        x=rand()%(height-2)+1;//^^^^^;
        y=(rand()%2)*(width-3)+1;
        if (y!=1) entrance.first=(y+1)*2+1;
        else entrance.first=0;
        entrance.second=x*2+1;
    }
    for (i=x-1;i<x+2;i++) {
        for (j=y-1;j<y+2;j++) {
            matrix[i][j]=1;
        }
    }
    std::pair<int,int> p(i-1,j-1);
    std::pair<int,int> p1(6,6);
    nodes[1]=p;
    info[1]=p1;
}

Dungeon::~Dungeon() {}

double distanceBetweenPoints(int x1,int y1,int x2,int y2) {
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

std::pair<int,int> Dungeon::getEntrance() {
    return entrance;
}

int Dungeon::getTile(int i,int j) {
    return this->map[i][j]*-1;
}

std::pair<int,int> Dungeon::getClosest(int to) {
    std::pair<int,int> res,aux1=nodes[to];
    double min=100000;
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            if (matrix[i][j]!=-20 && matrix[i][j]!=to) {
                double mm=distanceBetweenPoints(i,j,aux1.second,aux1.first);
                if (mm<min) {
                    min=mm;
                    res.second=i;
                    res.first=j;
                }
            }
        }
    }
    return res;
}

bool Dungeon::isSiding(int x,int y,int to) {
    bool b1=x>0,b2=y>0,b3=x<width-1,b4=y<height-1;
    if (b1 && matrix[y][x-1]==to) return true;
    if (b2 && matrix[y-1][x]==to) return true;
    if (b3 && matrix[y][x+1]==to) return true;
    if (b4 && matrix[y+1][x]==to) return true;
    return false;
}

void Dungeon::findPath(int to) {
    int r=0;
    std::pair<int,int> c1 = getClosest(to);
    std::pair<int,int> c2 = nodes[to];
    while (c1.first!=c2.first && !r) {
        if (isSiding(c1.first,c1.second,to)) break;
        if (c1.first>c2.first && matrix[c1.second][c1.first-1]!=to)
            matrix[c1.second][--c1.first]=2;
        else 
            if (c1.first<c2.first && matrix[c1.second][c1.first+1]!=to)
                matrix[c1.second][++c1.first]=2;
            else r=1;
    }
    r=0;
    while (c1.second!=c2.second && !r) {
        if (isSiding(c1.first,c1.second,to)) break;
        if (c1.second>c2.second && matrix[c1.second-1][c1.first]!=to)
            matrix[--c1.second][c1.first]=2;
        else 
            if (c1.second<c2.second && matrix[c1.second+1][c1.first]!=to)
                matrix[++c1.second][c1.first]=2;
            else r=1;
    }
}

void Dungeon::hallClose(int i,int j) {
    if (j>1 && matrix[i][j-1]==-20 && matrix[i][j-2]>13) matrix[i][j-1]=2;
    if (i>1 && matrix[i-1][j]==-20 && matrix[i-2][j]>13) matrix[i-1][j]=2;
    if (j<width-2 && matrix[i][j+1]==-20 && matrix[i][j+2]>13) matrix[i][j+1]=2;
    if (i<height-2 && matrix[i+1][j]==-20 && matrix[i+2][j]>13) matrix[i+1][j]=2;
}

void Dungeon::fixHalls() {
    int i,j;
    bool up,down,right,left;
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (matrix[i][j]!=2) continue;
            up = i && matrix[i-1][j]!=-20; 
            left = j && matrix[i][j-1]!=-20;
            down = i<height-1 && matrix[i+1][j]!=-20;
            right = j<width-1 && matrix[i][j+1]!=-20;
            if (up && left && down && right) matrix[i][j]=3;
            else if (up && left && right) matrix[i][j]=10;
            else if (up && right && down) matrix[i][j]=11;
            else if (left && down && right) matrix[i][j]=12;
            else if (left && up && down) matrix[i][j]=13;
            else if (left && up) matrix[i][j]=6;
            else if (left && down) matrix[i][j]=7;
            else if (down && right) matrix[i][j]=8;
            else if (up && right) matrix[i][j]=9;
            else if (up && down) matrix[i][j]=4;
            else if (left && right) matrix[i][j]=5;
        }
    }
}

void Dungeon::doubleMap() {
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            map[2*i][2*j]=map[2*i+1][2*j]=map[2*i][2*j+1]=map[2*i+1][2*j+1]=matrix[i][j];
        }
    }
}

//width max 12 min 8
//height max 8 min 6

void Dungeon::randomizeRooms() {
    int r=1,p=0,i,j,k;
    for (i=ROOMSTART;i<ROOMSTART+roomNumber;r=1,p=0,i++) {//deixei o 2 pra room final
        while (r && p<15) {
            p++;
            r=0;
            int rw=rand()%(6-4+1)+4;
            int rh=rand()%(4-3+1)+3;
            int rx=rand()%(width-rw+1);
            int ry=rand()%(height-rh+1);
            for (j=-1;j<=rh && r==0;j++) {
                for (k=-1;k<=rw && r==0;k++) {
                    if (j+ry<0 || j+ry>=height || k+rx<0 || k+rx>=width)
                        continue;
                    if (matrix[j+ry][k+rx]!=-20) {
                        r=1;
                        break;
                    }
                }
            }
            if (r) continue;
            for (j=0;j<rh && r==0;j++) {
                for (k=0;k<rw && r==0;k++) {
                    matrix[j+ry][k+rx]=i;
                }
            }
            std::pair<int,int> m(rw*2,rh*2);
            std::pair<int,int> p(rx+rw/2,ry+rh/2);
            nodes[i]=p;
            info[i]=m;
            findPath(i);
        }
        if (r) {
            i--;
            roomNumber-=1;
        }
    }
    /*
    for (i=0;i<height;i++) {
        for (j=0;j<width;j++) {
            if (matrix[i][j]>13)
                hallClose(i,j);
        }
    }
    */
    fixHalls();
    doubleMap();
}

bool Dungeon::isEntrance(int x,int y) {
    bool b1=x>0,b2=y>0,b3=x<(width*2)-1,b4=y<(height*2)-1;
    if (b1 && map[y][x-1]>2 && map[y][x-1]<14) return true;
    if (b2 && map[y-1][x]>2 && map[y-1][x]<14) return true;
    if (b3 && map[y][x+1]>2 && map[y][x+1]<14) return true;
    if (b4 && map[y+1][x]>2 && map[y+1][x]<14) return true;
    return false;
}

void Dungeon::makeEntrance(int x,int y) {
    bool c1=y>0,c2=x>0,c3=y<(height*2)-1,c4=x<(width*2)-1,b1=x<width*2-2 && isEntrance(x+1,y),b3 =(x>width*2-4 || map[y][x+2]!=-20),b2=y<height*2-2 && isEntrance(x,y+1),b4 = (y>height*2-4 || map[y+2][x]!=-20);
    bool left=false,up=false,right=false,down=false;//where there are Halls
    bool l=false,u=false,r=false,d=false;//where there is nothing
    if (c1 && map[y-1][x]>2 && map[y-1][x]<14) 
        up=true;
    else if (c1 && map[y-1][x]==-20) 
        u=true;
    if (c2 && map[y][x-1]>2 && map[y][x-1]<14)
        left=true;
    else if (c2 && map[y][x-1]==-20)
        l=true;
    if (c3 && map[y+1][x]>2 && map[y+1][x]<14)
        down=true;
    else if (c3 && map[y+1][x]==-20)
        d=true;
    if (c4 && map[y][x+1]>2 && map[y][x+1]<14)
        right=true;
    else if (c4 && map[y][x+1]==-20)
        r=true;
    if ((up && l) || (l && down)) {
        map[y][x]=LEFTWALL;       
        if (b1 && b3) {
            if (up) map[y][x+1]=UPRIGHTCORNER;
            else map[y][x+1]=RIGHTDOWNCORNER;
        }
    }
    else if ((u && left) || (u && right)) {
        map[y][x]=TOPWALL;
        if (b2 && b4 && left)
            map[y+1][x]=DOWNLEFTCORNER;
    }
    else if ((down && r) || (up && r)) // não se mexe no ant
        map[y][x]=RIGHTWALL;
    else if ((d && right) || (d && left )) {
        map[y][x]=BOTTOMWALL;
    }
    else if (up) {
        if (!b1) map[y][x]=UPRIGHTCORNER;
        else map[y][x]=LEFTUPCORNER;
        if (b1 && b3) map[y][x+1]=UPRIGHTCORNER;
    }   
    else if (left) {
        if (!b2) map[y][x]=DOWNLEFTCORNER;
        else map[y][x]=LEFTUPCORNER;
        if (b2 && b4) map[y+1][x]=DOWNLEFTCORNER;
    }
    else if (down) {
        if (!b1) map[y][x]=RIGHTDOWNCORNER;
        else map[y][x]=DOWNLEFTCORNER;
        if (b1 && b3) map[y][x+1]=RIGHTDOWNCORNER;
    }
    else if (right) {
        if (!b2) map[y][x]=RIGHTDOWNCORNER;
        else map[y][x]=UPRIGHTCORNER;
        if (b2 && b4) map[y+1][x]=RIGHTDOWNCORNER;
    }
}

void Dungeon::polishRoom(int y,int x,int num) {
    int w=info[num].first;
    int h=info[num].second;
    for (int i=0;i<h;i++) {
        for (int j=0;j<w;j++) {
            if (map[i+y][j+x]!=num) continue;
            if (i && i!=h-1 && j && j!=w-1) map[i+y][j+x]=0;
            else if (isEntrance(j+x,i+y)) makeEntrance(j+x,i+y);
            else if (!i && !j) map[i+y][j+x]=TOPRIGHTCORNER;
            else if (!i && j==w-1) map[i+y][j+x]=TOPLEFTCORNER;
            else if (i==h-1 && !j) map[i+y][j+x]=BOTTOMLEFTCORNER;
            else if (!i) map[i+y][j+x]=TOPWALL;
            else if (!j) map[i+y][j+x]=LEFTWALL;
            else if (i==h-1 && j==w-1) map[i+y][j+x]=BOTTOMRIGHTCORNER;
            else if (j==w-1) map[i+y][j+x]=RIGHTWALL;
            else map[i+y][j+x]=BOTTOMWALL;
        }
    }
}

void Dungeon::polishHall(int i,int j) {
    switch (map[i][j]) {
        case 3:
            map[i][j]=LEFTUPCORNER;
            map[i][j+1]=UPRIGHTCORNER;
            map[i+1][j]=DOWNLEFTCORNER;
            map[i+1][j+1]=RIGHTDOWNCORNER;
        break;
        case 4:
            map[i][j]=LEFTWALL;
            map[i][j+1]=RIGHTWALL;
            map[i+1][j]=LEFTWALL;
            map[i+1][j+1]=RIGHTWALL;
        break;
        case 5:
            map[i][j]=TOPWALL;
            map[i][j+1]=TOPWALL;
            map[i+1][j]=BOTTOMWALL;
            map[i+1][j+1]=BOTTOMWALL;
        break;
        case 6:
            map[i][j]=LEFTUPCORNER;
            map[i][j+1]=RIGHTWALL;
            map[i+1][j]=BOTTOMWALL;
            map[i+1][j+1]=BOTTOMRIGHTCORNER;
        break;
        case 7:
            map[i][j]=TOPWALL;
            map[i][j+1]=TOPLEFTCORNER;
            map[i+1][j]=DOWNLEFTCORNER;
            map[i+1][j+1]=RIGHTWALL;
        break;
        case 8:
            map[i][j]=TOPRIGHTCORNER;
            map[i][j+1]=TOPWALL;
            map[i+1][j]=LEFTWALL;
            map[i+1][j+1]=RIGHTDOWNCORNER;
        break;
        case 9:
            map[i][j]=LEFTWALL;
            map[i][j+1]=UPRIGHTCORNER;
            map[i+1][j]=BOTTOMLEFTCORNER;
            map[i+1][j+1]=BOTTOMWALL;
        break;
        case 10:
            map[i][j]=LEFTUPCORNER;
            map[i][j+1]=UPRIGHTCORNER;
            map[i+1][j]=BOTTOMWALL;
            map[i+1][j+1]=BOTTOMWALL;
        break;
        case 11:
            map[i][j]=LEFTWALL;
            map[i][j+1]=UPRIGHTCORNER;
            map[i+1][j]=LEFTWALL;
            map[i+1][j+1]=RIGHTDOWNCORNER;
        break;
        case 12:
            map[i][j]=TOPWALL;
            map[i][j+1]=TOPWALL;
            map[i+1][j]=DOWNLEFTCORNER;
            map[i+1][j+1]=RIGHTDOWNCORNER;
        break;
        case 13:
            map[i][j]=LEFTUPCORNER;
            map[i][j+1]=RIGHTWALL;
            map[i+1][j]=DOWNLEFTCORNER;
            map[i+1][j+1]=RIGHTWALL;
        break;
    }
}

void Dungeon::polishDungeon() {
    int i,j;
    for (i=0;i<height*2;i++) {
        for (j=0;j<width*2;j++) {
            if (map[i][j]>13 || map[i][j]==1) {
                polishRoom(i,j,map[i][j]);
            }
        }
    }
    for (i=0;i<height*2;i+=2) {
        for (j=0;j<width*2;j+=2) {
            polishHall(i,j);
        }
    }
    map[entrance.second][entrance.first]=-19;
}

void Dungeon::showDungeon() {
    int i,j;
    for (i=0;i<height*2;i++) {
        for (j=0;j<width*2;j++) {
            if (!map[i][j] || map[i][j]==-20) printf("  ");
            else if (map[i][j]<-9) printf("%c ",map[i][j]*-1+55);
            else if (map[i][j]<0) printf("%d ",map[i][j]*-1);
            else printf("%d ",map[i][j]);
        }
        puts("");
    }
    printf("Number of Rooms: %d\n",roomNumber+1);
}

/*
int main() {
    srand(time(NULL));
    for (int i=0;i<1;i++) {
        Dungeon* d = new Dungeon(100,60,30);// must be divisible by 2
        d->randomizeRooms();
        d->polishDungeon();
        d->addExtras();
        d->showDungeon();
    }
}
*/

void Dungeon::addExtras() {
    for (int i=0;i<height*2;i++) {
        for (int j=0;j<width*2;j++) {
            if (!map[i][j] && map[i-1][j]==-2 && map[i][j-1]!=-10 && map[i][j+1]!=-11 && rand()%10>7) 
                map[i][j]=-14;
            if (!map[i][j] && ((!map[i-1][j] && !map[i+1][j]) && (!map[i][j-1] && !map[i][j+1])) && rand()%10>8)
                map[i][j]=-15-rand()%2;
        }
    }

}