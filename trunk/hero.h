/*
* Hero.h
*/

#include "character.h"

class Hero : public Character
{
    public:
        Hero(string n, int hitpoints, double att, double def, int lev, string text);
        Hero(string n, int lev, string text);
        //getters
        bool getHasSwordOfKings();
        //setters
        void setHasSwordOfKings(bool hasSword);

    protected:
        bool hasSwordOfKings;
        
};
