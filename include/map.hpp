#ifndef map
#define map

#include <math.h>
#include <ctime>

class Mapa {
public:
    void initMap(int h,int w);
    int getHeight();
    int getWidth();
    int getTile(int i,int j);
    void randomizeMap(int fP);
    bool hasWaterNeighbour(int x,int y);
    int closestCreator(int x,int y);
private:
    int **mapa;
    int height;
    int width;
};

#endif
