/*
* Area.h
*/

#include <vector>
#include <string>
#include "common_game.h"
using namespace std;

class Area
{
    public:
       // Default constructor
        Area();
        Area(string mainText, string imMask, int n, int s, int e, int w);
        // Default destructor
        ~Area();
        
        //getters
        string getMainTexture();
        string getImageMask();
        int getNorth();
        int getWest();
        int getSouth();
        int getEast();
        Point getEntryNorth();
        Point getEntrySouth();
        Point getEntryEast();
        Point getEntryWest();
                
        //setters
        void setNorth(int n);
        void setWest(int w);
        void setSouth(int s);
        void setEast(int e);
        void setEntryNorth(Point entryN);
        void setEntrySouth(Point entryS);
        void setEntryEast(Point entryE);
        void setEntryWest(Point entryW);

    protected:
        //the main image to display
        string mainTexture;
        //invisible image to do collision
        string imageMask;
        //id to images around this one
        int north;
        int west;
        int south;
        int east;
        //these are the points on the map to place the character when entering
        Point entryNorth;
        Point entrySouth;
        Point entryEast;
        Point entryWest;
        
        
        
};
