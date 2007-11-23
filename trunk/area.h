/*
* Area.h
*/

#include <vector>
#include <string>
#include "common_game.h"
#include "npc.h"

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
        int getID();
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
        vector<NPC*> getNPCs();
                
        //setters
        void setID(int i);
        void setNorth(int n);
        void setWest(int w);
        void setSouth(int s);
        void setEast(int e);
        void setEntryNorth(Point entryN);
        void setEntrySouth(Point entryS);
        void setEntryEast(Point entryE);
        void setEntryWest(Point entryW);
        void setMainTexture(string);
        void setImageMask(string);
        
        //add an npc
        void addNPC(NPC* npc);
        
        //test if areas exist around here
        bool canMoveNorth();
        bool canMoveSouth();
        bool canMoveEast();
        bool canMoveWest();

    protected:
        //the id of this area
        int id;
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
        //the list of NPCs in this area
        vector<NPC*> npcs;
        
        
        
};
