#include <map>
#include <stdlib.h>  
#include <math.h>
#include <ctime>

class Dungeon {
    private:
        int** map;
        std::map<int,std::pair<int,int>> nodes; // middle of room before double
        std::map<int,std::pair<int,int>> info; //width and height
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
};
