/*
* NPC.h
*/
#ifndef _DEFINED_npc
#define _DEFINED_npc
#include <string>
#include "character.h"
#include "common_game.h"
using namespace std;

class NPC
{
    public:
        // Default constructor
        NPC();
        NPC(string n);
        NPC(string n, string text);
        
        // Default destructor
        ~NPC();
        
        // getters
        string getName();
        string getTexture();
        Point getLocation();
        
        // setters
        void setName(string n);
        void setTexture(string text);
        void setLocation(Point loc);

    protected:
        string name;
        string texture;
        Point location;
};
#endif
