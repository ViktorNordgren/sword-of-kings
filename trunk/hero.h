/*
* Hero.h
*/

#include "character.h"
#include <string>
using namespace std;



class Hero : public Character
{
    public:
        Hero();
        Hero(string n, int hitpoints, double att, double def, int lev, string text);
        Hero(string n, int lev, string text);
        //getters
        bool getHasSwordOfKings();
        string getNorthNormalTexture();
        string getNorthRightTexture();
        string getNorthLeftTexture();
        string getSouthNormalTexture();
        string getSouthRightTexture();
        string getSouthLeftTexture();
        string getEastNormalTexture();
        string getEastRightTexture();
        string getEastLeftTexture();
        string getWestNormalTexture();
        string getWestRightTexture();
        string getWestLeftTexture();
        //setters
        void setHasSwordOfKings(bool hasSword);

    protected:
        bool hasSwordOfKings;
        int expToNextLevel;
               
        
};
