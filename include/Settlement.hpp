#include <math.h>
#include <ctime>
#include <map>
#include <stdlib.h>

#define CAMINHO 0
#define CAMINHOA -6
#define TORRECANTOSUPERIORESQUERDO -2
#define TORRECANTOSUPERIORDIREITO -3
#define TORRECANTOINFERIORESQUERDO -4
#define TORRECANTOINFERIORDIREITO -5
#define HORIZONTALSUPERIOR -7
#define HORIZONTALINFERIOR -8
#define VERTICALESQUERDO -9
#define VERTICALDIREITO -10
#define MURALHA -11
#define MURALHAESQ -12
#define MURALHADIR -13
#define ENTRADA1 -14
#define ENTRADA2 -15
#define ENTRADA3 -16
#define ENTRADA4 -17
#define ENTRADA5 -18
#define ENTRADA6 -19
#define ENTRADA7 -20
#define ENTRADA8 -21
#define ENTRADA9 -22
#define ENTRADA10 -23
#define ENTRADA11 -24
#define ENTRADA12 -25
#define ENTRADA13 -26
#define ENTRADA14 -27
#define ENTRADA15 -28
#define ENTRADA16 -29
#define GROUND -30
#define CASTELO -31
#define BLACKSMITH -32
#define MAGETOWER -33
#define WITCHCABIN -34
#define TAVERN -35
#define WELL -36
#define CHURCH -37
#define FILLER 23456
#define NODHV 3 //number of different house versions
#define NODSV 2 //number of different special (buildings) versions
#define NODFV 1 //number of different fillers(Trees and stuff) versions
#define NODSFV 1 // number of different special fillers(church and well) versions

//double distanceBetweenPoints(int x1,int y1,int x2,int y2);

class Settlement {
    private:
        int **map;
        int width;
        int height;
        bool village;
        std::map<int,std::pair<std::pair<int,int>,std::pair<int,int>>> buildings;
        std::map<int,std::pair<int,int>> entrances;
        std::map<int,int> versions;
    public:
        Settlement(int width,int height,bool village);
        ~Settlement();
        int ** getMap();
        void buildWall();
        void addCastle();
        std::pair<int,int> getClosest(std::pair<int,int> to);
        bool canGo(int sentido,std::pair<int,int> from);
        std::pair<int,int>  goAround(int sen,std::pair<int,int> from,std::pair<int,int> to);
        void buildRoad(int buildID); 
        void addBuilding(int buildID);
        void printMap();
        void makeSettlement();
        int getVersion(int buildID);
};