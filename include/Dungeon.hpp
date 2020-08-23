#include <map>
#include <stdlib.h>  
#include <math.h>
#include <ctime>
#define TOPRIGHTCORNER -1
#define TOPWALL -2
#define TOPLEFTCORNER -3
#define RIGHTWALL -4
#define BOTTOMRIGHTCORNER -6
#define BOTTOMLEFTCORNER -5
#define LEFTWALL -7
#define BOTTOMWALL -8
#define RIGHTDOWNCORNER -11 // -11 e -17
#define DOWNLEFTCORNER -10 // -10 e -15
#define LEFTUPCORNER -12 // -12 e -14
#define UPRIGHTCORNER -13 // -13 e -16

double distanceBetweenPoints(int x1,int y1,int x2,int y2);

class Dungeon {
    private:
        int** map;
        std::map<int,std::pair<int,int>> nodes; // middle of room before double
        std::map<int,std::pair<int,int>> info; //width and height
        std::pair<int,int> entrance;
        int width;
        int height;
        void doubleMap();
        void findPath(int to);
        std::pair<int,int> getClosest(int to);
        void hallClose(int i,int j);
        void fixHalls();
        void polishHall(int i,int j); 
        void polishRoom(int y,int x,int num);
        bool isSiding(int x,int y,int to);
        bool isEntrance(int x,int y);
        void makeEntrance(int x,int y);
    public:
        Dungeon(int widthg,int heightg,int RoomNumberg);
        ~Dungeon();
        
        int roomNumber;
        void randomizeRooms();
        void randomizeDungeon();
        void polishDungeon();
        int getTile(int i,int j);
        std::pair<int,int> getEntrance();
};
