/*
* Character.h
*/
#ifndef _DEFINED_character
#define _DEFINED_character
#include <string>
using namespace std;

class Character
{
    public:
        // Default constructor
        Character();
        
        Character(string n, int hitpoints, double att, double def, int lev, string text);
        Character(string n, int lev, string text);
        
        // Default destructor
        ~Character();
        
        //getters
        string getName();
        int getTotalHitPoints();
        int getRemainingHitPoints();
        double getAttack();
        double getDefense();
        int getLevel();
        string getTexture();
        int getHeight();
        int getWidth();
        
        //setters
        void setName(string n);
        void setTotalHitPoints(int total);
        void setRemainingHitPoints(int remaining);
        void setAttack(double attack);
        void setDefense(double defense);
        void setLevel(int l);
        void incrementLevel();
        void setTexture(string text);
        void setHeight(int h);
        void setWidth(int w);
       
    protected:
        
        //the name of this character
        string name;
        
        //total amount of life
        int totalHitPoints;
        
        //remaining life
        int remainingHitPoints;
        
        //amount of damage you do
        double attack;
        
        //amount of defense you have - how well you deflect blows
        double defense;
        
        //your current level
        int level;
        
        //the base texture for this character
        string texture;
        
        //the height of the character in grid units
        int height;
        
        //the width of the character in grid units
        int width;        
};
#endif
