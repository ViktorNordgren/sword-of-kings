/*
* Enemy.h
*/
#ifndef _DEFINED_enemy
#define _DEFINED_enemy

#include "character.h"
#include "common_game.h"

class Enemy : public Character
{
    public:
        Enemy();
        Enemy(string n, int hitpoints, double att, double def, int lev, string text, string id);
        Enemy(string n, int lev, string text, string id);
        //getters
        string getEnemyID();
        int getExp();
        //setters
        void setEnemyID(string);
        void setExp(int e);
        

    protected:
        string enemyID;
        int exp;
};

#endif

